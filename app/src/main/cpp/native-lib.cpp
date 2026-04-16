#include <jni.h>
#include <string>
#include <unistd.h>
#include <pthread.h>
#include "KittyMemory/KittyMemory.hpp"
#include "KittyMemory/MemoryPatch.hpp"

bool is_authorized = false;
MemoryPatch recoilPatch, spreadPatch;

// 백그라운드에서 게임 라이브러리가 로드될 때까지 감시
void* hack_thread(void*) {
    ProcMap gMap;
    do {
        gMap = KittyMemory::getLibraryMap("libMyGame.so"); // 실제 게임 라이브러리 명칭
        usleep(500000);
    } while (!gMap.isValid());

    // 0x123456 같은 주소값은 추후 실제 분석값으로 수정 예정
    recoilPatch = MemoryPatch::createWithHex("libMyGame.so", 0x123456, "00 00 A0 E3 1E FF 2F E1");
    spreadPatch = MemoryPatch::createWithHex("libMyGame.so", 0x654321, "00 00 A0 E3 1E FF 2F E1");
    return nullptr;
}

extern "C" JNIEXPORT void JNICALL
Java_com_internal_asp1rin_launcher_MainActivity_activateSystem(JNIEnv* env, jobject thiz) {
    is_authorized = true;
    pthread_t t;
    pthread_create(&t, nullptr, hack_thread, nullptr);
}

extern "C" JNIEXPORT void JNICALL
Java_com_internal_asp1rin_launcher_MainActivity_toggleFeature(JNIEnv* env, jobject thiz, jboolean enabled) {
    if (is_authorized && enabled) {
        recoilPatch.Modify(); // 기능 ON
        spreadPatch.Modify();
    } else {
        recoilPatch.Restore(); // 기능 OFF
    }
}
