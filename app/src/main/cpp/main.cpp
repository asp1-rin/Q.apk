#include <jni.h>
#include <string>
#include <pthread.h>
#include <unistd.h>
#include <vector>
#include "KittyInclude.hpp"
#include "offsets.h"

// --- 외부 모듈 함수 선언 (extern) ---
// Bypass.cpp
extern void ApplyBypass();

// Weapon.cpp
extern void SetupWeapon();
extern void ToggleNoRecoil(bool enable);
extern void ToggleNoSpread(bool enable);

// Aimbot.cpp
extern void UpdateAimbot(uintptr_t localPlayer, uintptr_t enemyList[], int enemyCount);
// Aimbot 내부 전역 변수 조절용 JNI 함수들은 Aimbot.cpp에 이미 포함됨

// --- 전역 변수 및 포인터 관리 ---
uintptr_t g_LocalPlayer = 0;
uintptr_t g_EnemyManager = 0; // 게임 엔진의 엔티티 매니저 주소 필요

// --- 로그 뮤트 (시스템 로그 차단) ---
void MuteLogging() {
    void* log_print = dlsym(RTLD_DEFAULT, "__android_log_print");
    if (log_print) {
        // 실제 운영 시에는 여기에 로그 함수 후킹 로직을 추가하여 
        // 보안 모듈이 로그를 남기지 못하게 합니다.
    }
}

// --- 메인 해킹 루프 스레드 ---
void* HackMainThread(void*) {
    ProcMap gameMap;

    // 1. 게임 라이브러리 로드 대기
    do {
        gameMap = KittyMemory::getLibraryMap(G_LIB);
        usleep(500000); // 0.5초 간격으로 확인
    } while (!gameMap.isValid());

    // 2. 보안 우회 실행 (libxigncode.so 감시 및 패치)
    ApplyBypass();

    // 3. 무기 핵 초기화 (메모리 패치 객체 생성)
    SetupWeapon();

    // 4. 무한 루프: 실시간 에임봇 및 데이터 업데이트
    // 실제 구현 시 enemyList와 enemyCount는 게임 엔진의 객체 관리자에서 읽어와야 합니다.
    while (true) {
        if (g_LocalPlayer != 0) {
            // 여기에 실시간으로 적 리스트를 갱신하는 로직 추가
            // UpdateAimbot(g_LocalPlayer, enemies, count);
        }
        usleep(10000); // 약 100fps 속도로 루프 실행
    }

    return nullptr;
}

// --- JNI 엔트리 포인트 ---
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    JNIEnv* env;
    if (vm->GetEnv((void**)&env, JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }

    // 로그 차단
    MuteLogging();

    // 백그라운드 스레드 시작
    pthread_t ptid;
    pthread_create(&ptid, nullptr, HackMainThread, nullptr);

    return JNI_VERSION_1_6;
}

// --- 자바 UI 연동 인터페이스 (JNI) ---
// 주의: 패키지명(com_example_milkchoco)은 실제 안드로이드 프로젝트와 일치해야 합니다.

extern "C" {

    // 무반동 토글
    JNIEXPORT void JNICALL
    Java_com_example_milkchoco_MainActivity_setNoRecoil(JNIEnv* env, jobject thiz, jboolean enable) {
        ToggleNoRecoil(enable);
    }

    // 탄퍼짐 제거 토글
    JNIEXPORT void JNICALL
    Java_com_example_milkchoco_MainActivity_setNoSpread(JNIEnv* env, jobject thiz, jboolean enable) {
        ToggleNoSpread(enable);
    }

    // 로컬 플레이어 포인터 업데이트 (자바 레이어에서 감지 시 전달)
    JNIEXPORT void JNICALL
    Java_com_example_milkchoco_MainActivity_updateLocalPlayer(JNIEnv* env, jobject thiz, jlong ptr) {
        g_LocalPlayer = (uintptr_t)ptr;
    }

} // extern "C" 종료
