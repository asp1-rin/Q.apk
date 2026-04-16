#include <jni.h>
#include <string>
#include <pthread.h>
#include <unistd.h>
#include "KittyInclude.hpp"
#include "offsets.h"

// 외부 모듈 함수 연결
extern void ApplyBypass();
extern void SetupWeapon();
extern void ToggleNoRecoil(bool enable);
extern void ToggleNoSpread(bool enable);
extern void UpdateAimbot(uintptr_t localPlayer, uintptr_t enemyList[], int enemyCount);

// 전역 변수
uintptr_t g_LocalPlayer = 0;
extern bool isAimbotEnabled; // Aimbot.cpp에 정의됨

// 메인 핵 루프
void* HackMainThread(void*) {
    ProcMap gameMap;

    // 보안 우회 및 라이브러리 대기
    ApplyBypass();
    do {
        gameMap = KittyMemory::getLibraryMap(G_LIB);
        usleep(500000);
    } while (!gameMap.isValid());

    // 기능 초기화
    SetupWeapon();

    while (true) {
        // 자동 탐색: position-base (0x7ABE28) 활용
        uintptr_t posBaseAddr = gameMap.startAddress + 0x7ABE28;
        g_LocalPlayer = *(uintptr_t*)posBaseAddr;

        if (g_LocalPlayer != 0 && isAimbotEnabled) {
            // 에임봇 업데이트 (적 리스트 로직은 추후 보완)
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
    // JNI 함수 이름이 패키지명 com.internal.asp1rin.launcher에 맞춰 수정됨
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
}
