#include <jni.h>
#include <string>
#include <android/input.h>
#include <android/log.h>

#include "engine/AudioEngine.h"
#include "engine/utils/utils.cpp"

#define WAVES_COUNT 10

static AudioEngine *audioEngine = nullptr;

extern "C" {

JNIEXPORT void JNICALL
Java_it_aliut_simplesynth_MainActivity_touchEvent(
        JNIEnv *env,
        jobject obj,
        jint pointerId,
        jint action
) {
    switch (action) {
        case AMOTION_EVENT_ACTION_DOWN:
            audioEngine->setToneOn(true);
            break;
        case AMOTION_EVENT_ACTION_UP:
            audioEngine->setToneOn(false);
            audioEngine->setFrequency(pointerId, 0);
            break;
        default:
            break;
    }
}

JNIEXPORT void JNICALL
Java_it_aliut_simplesynth_MainActivity_startEngine(
        JNIEnv *env,
        jobject /* this */
) {
    audioEngine = new AudioEngine(WAVES_COUNT);
}

JNIEXPORT void JNICALL
Java_it_aliut_simplesynth_MainActivity_stopEngine(
        JNIEnv *env,
        jobject /* this */
) {
    if (audioEngine != nullptr) {
        delete audioEngine;
        audioEngine = nullptr;
    }
}

JNIEXPORT void JNICALL
Java_it_aliut_simplesynth_MainActivity_setFrequency(
        JNIEnv *env,
        jobject  /* this */,
        jint pointerId,
        jdouble freqPercentage
) {
    if (pointerId < 0 || pointerId >= WAVES_COUNT) {
        __android_log_print(ANDROID_LOG_ERROR,
                            "AudioEngine",
                            "Invalid pointer id: %d",
                            pointerId);
        return;
    }

    double frequency = percentageToFrequency(freqPercentage);

    __android_log_print(ANDROID_LOG_DEBUG,
                        "AudioEngine",
                        "pointerId: %d, freqPercentage: %f, frequency: %f",
                        pointerId, freqPercentage, frequency);

    audioEngine->setFrequency(pointerId, frequency);
}

}

