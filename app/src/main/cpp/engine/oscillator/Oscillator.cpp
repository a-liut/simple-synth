//
// Created by Andrea Liut on 2019-12-19.
//

#include "Oscillator.h"
#include <cmath>

#define TWO_PI (3.14159 * 2)
#define AMPLITUDE 3

void Oscillator::updatePhaseIncrement() {
    phaseIncrement_ = (TWO_PI * frequency_) / sampleRate_;
}

void Oscillator::setSampleRate(int32_t sampleRate) {
    sampleRate_ = (double) sampleRate;
    updatePhaseIncrement();
}

void Oscillator::setWaveOn(bool isWaveOn) {
    isWaveOn_.store(isWaveOn);
}

void Oscillator::render(float *audioData, int32_t numFrames) {
    if (!isWaveOn_.load()) phase_ = 0;

    for (int i = 0; i < numFrames; i++) {
        if (isWaveOn_.load()) {
            audioData[i] = (float) (sin(phase_) * AMPLITUDE);

            phase_ += phaseIncrement_;

            if (phase_ > TWO_PI) phase_ -= TWO_PI;
        } else {
            audioData[i] = 0;
        }
    }
}

void Oscillator::setFrequency(double frequency) {
    frequency_ = frequency;
    updatePhaseIncrement();
}
