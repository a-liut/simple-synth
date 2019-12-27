//
// Created by Andrea Liut on 2019-12-19.
//

#ifndef SIMPLESYNTH_AUDIOENGINE_H
#define SIMPLESYNTH_AUDIOENGINE_H

#include <aaudio/AAudio.h>
#include "Oscillator.h"

class AudioEngine {
public:
    bool start();

    void stop();

    void restart();

    void setToneOn(bool isToneOn);

    void setFrequency(double frequency);

private:
    Oscillator oscillator_;
    AAudioStream *stream_;
};


#endif //SIMPLESYNTH_AUDIOENGINE_H
