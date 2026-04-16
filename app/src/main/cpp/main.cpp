#include <jni.h>
#include <string>
#include <pthread.h>
#include <unistd.h>
#include "KittyInclude.hpp"
#include "offsets.h"

// 외부 모듈 함수 선언 (modules/ 폴더에 정의된 함수들)
extern void ApplyBypass();
extern void SetupWeapon();
extern void ToggleNoRecoil(bool enable);

// 1. 로그 뮤트 (흔적 지우기)
void MuteLogging() {
    void* log_print = dlsym(RTLD_DEFAULT, "__android_log_print");
    if (log_print) {
        // KittyMemory나 Dobby 등을 사용하여 로그 함수를 무력화
        // 여기서는 간단히 로그 함수를 스킵하도록 구성할 수 있습니다.
    }
}

// 2. 메인 해킹 스레드
// 게임 라이브러리가 로드될 때까지 기다렸다가 패치를 적용합니다.
void* HackThread(void*) {
    ProcMap gameMap;
    
    // libMyGame.so가 메모리에 올라올 때까지 무한 루프 (대기)
    do {
        gameMap = KittyMemory::getLibraryMap(G_LIB);
        sleep(1);
    } while (!gameMap.isValid());

    // 보안 우회 적용 (libxigncode.so 감시 및 패치)
    ApplyBypass();

    // 무기 핵 초기화 (오프셋 준비)
    SetupWeapon();

    // 기본적으로 기능을 켜고 싶다면 여기서 바로 호출
    // ToggleNoRecoil(true);

    return nullptr;
}

// 3. JNI_OnLoad (APK가 로드될 때 가장 먼저 실행되는 곳)
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    JNIEnv* env;
    if (vm->GetEnv((void**)&env, JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }

    // 로그 차단 실행
    MuteLogging();

    // 게임 로직을 방해하지 않도록 별도의 스레드에서 핵 로직 실행
    pthread_t ptid;
    pthread_create(&ptid, nullptr, HackThread, nullptr);

    return JNI_VERSION_1_6;
}

// 4. 자바(UI)에서 버튼을 눌렀을 때 호출될 인터페이스
extern "C" JNIEXPORT void JNICALL
Java_com_example_milkchoco_MainActivity_setNoRecoil(JNIEnv* env, jobject thiz, jboolean enable) {
    ToggleNoRecoil(enable);
}
