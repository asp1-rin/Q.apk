#include <jni.h>
#include <string>
#include <math.h>
#include <unistd.h>
#include <pthread.h>
#include "dobby.h"

bool is_authorized = false;
bool feature_enabled = false;
float FOV_RADIUS = 150.0f;

int (*old_Xign1)(void*, void*, void*, void*, void*) = nullptr;
int (*old_Xign2)(void*, void*, void*, void*, void*) = nullptr;
int (*old_Xign3)(void*, void*, void*, void*, void*) = nullptr;
void (*old_Shake)(void*, float*) = nullptr;
float (*old_Spread)(void*) = nullptr;

int fake_Xign(void* a, void* b, void* c, void* d, void* e) {
    return 0;
}

void fake_Shake(void* i, float* v) {
    if (is_authorized && feature_enabled) return;
    old_Shake(i, v);
}

float fake_Spread(void* i) {
    if (is_authorized && feature_enabled) return 0.0f;
    return old_Spread(i);
}

void* init_thread(void*) {
    while (!DobbySymbolResolver("libxigncode.so", "Java_com_wellbia_xigncode_XigncodeClientSystem_ZCWAVE_1Initialize")) { usleep(100000); }
    DobbyHook(DobbySymbolResolver("libxigncode.so", "Java_com_wellbia_xigncode_XigncodeClientSystem_ZCWAVE_1Initialize"), (void*)fake_Xign, (void**)&old_Xign1);
    DobbyHook(DobbySymbolResolver("libxigncode.so", "Java_com_wellbia_xigncode_XigncodeClientSystem_ZCWAVE_1InitializeEx"), (void*)fake_Xign, (void**)&old_Xign2);
    DobbyHook(DobbySymbolResolver("libxigncode.so", "Java_com_wellbia_xigncode_XigncodeClientSystem_ZCWAVE_1InitializeExEx"), (void*)fake_Xign, (void**)&old_Xign3);

    while (!DobbySymbolResolver("libMyGame.so", "_ZN6Recoil11ShakeCameraERKf")) { usleep(100000); }
    DobbyHook(DobbySymbolResolver("libMyGame.so", "_ZN6Recoil11ShakeCameraERKf"), (void*)fake_Shake, (void**)&old_Shake);
    DobbyHook(DobbySymbolResolver("libMyGame.so", "_ZN6Spread19GetAimGapByCurStateEv"), (void*)fake_Spread, (void**)&old_Spread);
    return nullptr;
}

extern "C" JNIEXPORT void JNICALL
Java_com_internal_asp1rin_launcher_MainActivity_activateSystem(JNIEnv* env, jobject thiz) {
    is_authorized = true;
    pthread_t t;
    pthread_create(&t, nullptr, init_thread, nullptr);
}

extern "C" JNIEXPORT void JNICALL
Java_com_internal_asp1rin_launcher_MainActivity_toggleFeature(JNIEnv* env, jobject thiz, jboolean enabled) {
    feature_enabled = enabled;
}
