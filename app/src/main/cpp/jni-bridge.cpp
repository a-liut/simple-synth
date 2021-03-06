#include <jni.h>
#include <string>
#include "engine/AudioEngine.h"
#include <android/input.h>

static AudioEngine *audioEngine = nullptr;

extern "C" {

JNIEXPORT void JNICALL
Java_it_aliut_simplesynth_MainActivity_touchEvent(
        JNIEnv *env,
        jobject obj,
        jint action
) {
    switch (action) {
        case AMOTION_EVENT_ACTION_DOWN:
            audioEngine->setToneOn(true);
            break;
        case AMOTION_EVENT_ACTION_UP:
            audioEngine->setToneOn(false);
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
    audioEngine = new AudioEngine();
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
        jdouble frequency
) {
    audioEngine->setFrequency(frequency);
}

}

