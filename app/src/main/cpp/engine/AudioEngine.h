//
// Created by Andrea Liut on 2019-12-19.
//

#ifndef SIMPLESYNTH_AUDIOENGINE_H
#define SIMPLESYNTH_AUDIOENGINE_H

#include <oboe/Oboe.h>
#include "oscillator/Oscillator.h"

class AudioEngine {
public:
    AudioEngine();

    void beginStreams();

    virtual ~AudioEngine();

    oboe::Result startStreams();

    oboe::Result stopStreams();

    void setToneOn(bool isToneOn);

    void setFrequency(double frequency);

private:
    void openOutStream();

    static oboe::AudioStreamBuilder defaultBuilder();

    void createCallback();

    void createOscillator();

    oboe::ManagedStream outStream_;
    std::unique_ptr<oboe::AudioStreamCallback> callback_;

    Oscillator *oscillator_;
};


#endif //SIMPLESYNTH_AUDIOENGINE_H
