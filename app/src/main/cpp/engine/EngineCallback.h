//
// Created by Andrea Liut on 2019-12-27.
//


#ifndef SIMPLESYNTH_ENGINECALLBACK_H
#define SIMPLESYNTH_ENGINECALLBACK_H

#include <oboe/Oboe.h>
#include "oscillator/Oscillator.h"

class EngineCallback : public oboe::AudioStreamCallback {
public:
    EngineCallback(
            Oscillator *oscillator,
            std::function<void(void)> restartFun
    ) : oscillator_(oscillator), restartFun_(restartFun) {}

    oboe::DataCallbackResult
    onAudioReady(oboe::AudioStream *oboeStream, void *audioData, int32_t numFrames) override {
        oscillator_->render(static_cast<float *>(audioData), numFrames);
        return oboe::DataCallbackResult::Continue;
    }

    void onErrorAfterClose(oboe::AudioStream *stream, oboe::Result result) override {
        if (result == oboe::Result::ErrorDisconnected) {
            restartFun_();
        }
    }

private:
    Oscillator *oscillator_;
    std::function<void(void)> restartFun_;
};


#endif //SIMPLESYNTH_ENGINECALLBACK_H
