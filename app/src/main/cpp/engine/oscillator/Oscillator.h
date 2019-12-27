//
// Created by Andrea Liut on 2019-12-19.
//

#ifndef SIMPLESYNTH_OSCILLATOR_H
#define SIMPLESYNTH_OSCILLATOR_H


#include <stdint.h>
#include <atomic>

class Oscillator {
public:
    void setWaveOn(bool isWaveOn);

    void setSampleRate(int32_t sampleRate);

    void setFrequency(double frequency);

    void render(float *audioData, int32_t numFrames);

private:
    std::atomic<bool> isWaveOn_{false};
    double phase_ = 0.0;
    double phaseIncrement_ = 0.0;
    double frequency_ = 440.0;
    double sampleRate_ = 0;

    void updatePhaseIncrement();
};


#endif //SIMPLESYNTH_OSCILLATOR_H
