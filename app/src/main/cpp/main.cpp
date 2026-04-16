#include <jni.h>
#include <string>
#include <pthread.h>
#include <unistd.h>
#include "KittyInclude.hpp"
#include "offsets.h"

extern void ApplyBypass();
extern void SetupWeapon();
extern void ToggleNoRecoil(bool enable);
extern void ToggleNoSpread(bool enable);
extern void UpdateAimbot(uintptr_t localPlayer, uintptr_t enemyList[], int enemyCount);

uintptr_t g_LocalPlayer = 0;
bool isAimbotEnabled = false;

void* HackMainThread(void*) {
    ProcMap gameMap;
    ApplyBypass();
    do {
        gameMap = KittyMemory::getLibraryMap(G_LIB);
        usleep(500000);
    } while (!gameMap.isValid());

    SetupWeapon();

    while (true) {
        uintptr_t posBaseAddr = gameMap.startAddress + 0x7ABE28;
        g_LocalPlayer = *(uintptr_t*)posBaseAddr;

        if (g_LocalPlayer != 0 && isAimbotEnabled) {
            UpdateAimbot(g_LocalPlayer, nullptr, 0);
        }
        usleep(10000);
    }
    return nullptr;
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    pthread_t ptid;
    pthread_create(&ptid, nullptr, HackMainThread, nullptr);
    return JNI_VERSION_1_6;
}

extern "C" {
    JNIEXPORT void JNICALL
    Java_com_internal_asp1rin_launcher_MainActivity_setNoRecoil(JNIEnv* env, jobject thiz, jboolean enable) {
        ToggleNoRecoil(enable);
    }

    JNIEXPORT void JNICALL
    Java_com_internal_asp1rin_launcher_MainActivity_setNoSpread(JNIEnv* env, jobject thiz, jboolean enable) {
        ToggleNoSpread(enable);
    }

    JNIEXPORT void JNICALL
    Java_com_internal_asp1rin_launcher_MainActivity_setAimbotState(JNIEnv* env, jobject thiz, jboolean enable) {
        isAimbotEnabled = enable;
    }

    JNIEXPORT void JNICALL
    Java_com_internal_asp1rin_launcher_MainActivity_setAimbotFov(JNIEnv* env, jobject thiz, jfloat fov) {
        // Aimbot.cpp의 fov 변수와 연결
    }
}
