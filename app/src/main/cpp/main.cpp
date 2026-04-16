#include <jni.h>
#include <string>
#include <pthread.h>
#include <unistd.h>
#include <vector>
#include "KittyInclude.hpp"
#include "offsets.h"

// --- 외부 모듈 함수 연결 ---
extern void ApplyBypass();
extern void SetupWeapon();
extern void ToggleNoRecoil(bool enable);
extern void ToggleNoSpread(bool enable);
extern void UpdateAimbot(uintptr_t localPlayer, uintptr_t enemyList[], int enemyCount);

// --- 내부 전역 변수 ---
uintptr_t g_LocalPlayer = 0;
uintptr_t g_EnemyManager = 0;

// --- 자동 탐색 엔진 (핵심) ---
void* HackMainThread(void*) {
    ProcMap gameMap;

    // 1. 보안 우회 즉시 실행 (libxigncode.so 로드 대기)
    ApplyBypass();

    // 2. 게임 라이브러리 로드 대기
    do {
        gameMap = KittyMemory::getLibraryMap(G_LIB);
        usleep(500000); 
    } while (!gameMap.isValid());

    // 3. 무기 패치 초기화
    SetupWeapon();

    // 4. [자동 탐색 루프]
    // 게임이 실행 중일 때 실시간으로 내 포인터와 적 리스트를 찾아냅니다.
    while (true) {
        // 제공해주신 position-base(0x7ABE28)를 활용하여 자동 획득
        uintptr_t posBaseAddr = gameMap.startAddress + 0x7ABE28;
        
        // 실제 인게임에 들어갔을 때만 주소가 유효해지므로 실시간 체크
        g_LocalPlayer = *(uintptr_t*)posBaseAddr; 

        if (g_LocalPlayer != 0) {
            // 에임봇 업데이트 호출
            // 실제 적 리스트를 관리하는 매니저 오프셋이 있다면 여기에 추가 연결
            UpdateAimbot(g_LocalPlayer, nullptr, 0);
        }

        usleep(10000); // 약 100fps 속도로 감시
    }

    return nullptr;
}

// --- JNI 엔트리 포인트 ---
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    pthread_t ptid;
    pthread_create(&ptid, nullptr, HackMainThread, nullptr);
    return JNI_VERSION_1_6;
}

// --- 자바 UI 연동 (토글 스위치들) ---
extern "C" {

    JNIEXPORT void JNICALL
    Java_com_example_milkchoco_MainActivity_setNoRecoil(JNIEnv* env, jobject thiz, jboolean enable) {
        ToggleNoRecoil(enable);
    }

    JNIEXPORT void JNICALL
    Java_com_example_milkchoco_MainActivity_setNoSpread(JNIEnv* env, jobject thiz, jboolean enable) {
        ToggleNoSpread(enable);
    }

    // 에임봇 On/Off 스위치 (Aimbot.cpp 내의 전역 변수 조절용)
    extern bool isAimbotEnabled; 
    JNIEXPORT void JNICALL
    Java_com_example_milkchoco_MainActivity_setAimbotState(JNIEnv* env, jobject thiz, jboolean enable) {
        isAimbotEnabled = enable;
    }

} // extern "C"
