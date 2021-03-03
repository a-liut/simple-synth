//
// Created by Andrea Liut on 2019-12-19.
//

#ifndef SIMPLESYNTH_AUDIOENGINE_H
#define SIMPLESYNTH_AUDIOENGINE_H

#include <oboe/Oboe.h>
#include "oscillator/Oscillator.h"

class AudioEngine {
public:
    AudioEngine(int oscillatorsCount);

    void beginStreams();

    virtual ~AudioEngine();

    oboe::Result startStreams();

    oboe::Result stopStreams();

    void setToneOn(bool isToneOn);

    void setFrequency(int channelId, double frequency);

private:
    void openOutStream();

    static oboe::AudioStreamBuilder defaultBuilder();

    void createCallback();

    void createOscillators();

    oboe::ManagedStream outStream_;
    std::unique_ptr<oboe::AudioStreamCallback> callback_;

    Oscillator *oscillators_[];
    int oscillatorsCount_;
};


#endif //SIMPLESYNTH_AUDIOENGINE_H
