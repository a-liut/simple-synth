//
// Created by Andrea Liut on 2019-12-19.
//

#include <android/log.h>
#include "AudioEngine.h"
#include "EngineCallback.h"

AudioEngine::AudioEngine(int oscillatorsCount) {
    oscillatorsCount_ = oscillatorsCount;
    createOscillators();
    beginStreams();
}

AudioEngine::~AudioEngine() {
    delete oscillators_;
}

oboe::AudioStreamBuilder AudioEngine::defaultBuilder() {
    return *oboe::AudioStreamBuilder()
            .setPerformanceMode(oboe::PerformanceMode::LowLatency)
            ->setSharingMode(oboe::SharingMode::Exclusive);
}

void AudioEngine::beginStreams() {
    createCallback();
    openOutStream();

    oboe::Result result = startStreams();
    if (result != oboe::Result::OK) stopStreams();
    else {
        for (int i = 0; i < oscillatorsCount_; i++) {
            oscillators_[i]->setSampleRate(outStream_->getSampleRate());
        }
    }
}

void AudioEngine::openOutStream() {
    defaultBuilder()
            .setDirection(oboe::Direction::Output)
            ->setFormat(oboe::AudioFormat::Float)
            ->setCallback(callback_.get())
            ->setChannelCount(oboe::ChannelCount::Mono)
            ->openManagedStream(outStream_);
}


oboe::Result AudioEngine::startStreams() {
    oboe::Result result = outStream_->requestStart();
    int64_t timeoutNanos = 500 * 1000000; // arbitrary 1/2 second
    auto currentState = outStream_->getState();
    auto nextState = oboe::StreamState::Unknown;
    while (result == oboe::Result::OK && currentState != oboe::StreamState::Started) {
        result = outStream_->waitForStateChange(currentState, &nextState, timeoutNanos);
        currentState = nextState;
    }

    return result;
}

void AudioEngine::createCallback() {
    callback_ = std::make_unique<EngineCallback>(
            oscillators_,
            oscillatorsCount_,
            std::bind(&AudioEngine::beginStreams, this)
    );
}

void AudioEngine::createOscillators() {
    oscillators_ = new Oscillator *[oscillatorsCount_];
    for (int i = 0; i < oscillatorsCount_; i++) {
        oscillators_[i] = new Oscillator();
    }
}

oboe::Result AudioEngine::stopStreams() {
    return outStream_->requestStop();
}

void AudioEngine::setToneOn(bool isToneOn) {
    for (int i = 0; i < oscillatorsCount_; i++) {
        oscillators_[i]->setWaveOn(isToneOn);
    }
}

void AudioEngine::setFrequency(int channelId, double frequency) {
    for (int i = 0; i < oscillatorsCount_; i++) {
        oscillators_[i]->setFrequency(channelId, frequency);
    }
}
