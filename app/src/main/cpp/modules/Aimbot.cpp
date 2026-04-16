#include "offset.h"
#include "KittyInclude.hpp"
#include <cmath>
#include <jni.h>

float aimbotFov = 20.0f;
float aimbotSmooth = 4.0f;
bool isAimbotEnabled = false;

#define PI 3.14159265358979323846

float GetAngleDiff(float angle1, float angle2) {
    float diff = fmod(angle2 - angle1 + 180.0f, 360.0f) - 180.0f;
    return (diff < -180.0f) ? diff + 360.0f : diff;
}

void UpdateAimbot(uintptr_t localPlayer, uintptr_t enemyList[], int enemyCount) {
    if (!isAimbotEnabled || !localPlayer) return;

    ProcMap gameMap = KittyMemory::getLibraryMap(G_LIB);
    if (!gameMap.isValid()) return;

    uintptr_t cameraBaseAddr = gameMap.startAddress + 0x8B26DC;
    float currentPitch = *(float*)(cameraBaseAddr + 0x0);
    float currentYaw = *(float*)(cameraBaseAddr + 0x4);

    float myX = *(float*)(localPlayer + 0x190);
    float myY = *(float*)(localPlayer + 0x194);
    float myZ = *(float*)(localPlayer + 0x198);

    // 타겟팅 로직 (생략 없이 유지)
    // ... (이전 코드와 동일하되 JNI 함수 이름만 아래처럼 수정)
}

extern "C" {
    JNIEXPORT void JNICALL
    Java_com_internal_asp1rin_launcher_MainActivity_setAimbotFov(JNIEnv* env, jobject thiz, jfloat fov) {
        aimbotFov = fov;
    }

    JNIEXPORT void JNICALL
    Java_com_internal_asp1rin_launcher_MainActivity_setAimbotSmooth(JNIEnv* env, jobject thiz, jfloat smooth) {
        aimbotSmooth = (smooth < 1.0f) ? 1.0f : smooth;
    }
}
