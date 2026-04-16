#include <jni.h>
#include <pthread.h>
#include <unistd.h>
#include "KittyInclude.hpp"
#include "offset.h"

extern void ApplyBypass();
extern void SetupWeapon();
extern void ToggleNoRecoil(bool enable);
extern void ToggleNoSpread(bool enable);
extern void UpdateAimbot(uintptr_t local, uintptr_t* enemies, int count);

bool isAimbotOn = false;

void* HackLoop(void*) {
    ProcMap gMap;
    ApplyBypass();
    do {
        gMap = KittyMemory::getLibraryMap(G_LIB);
        usleep(500000);
    } while (!gMap.isValid());

    SetupWeapon();

    while (true) {
        uintptr_t local = *(uintptr_t*)(gMap.startAddress + 0x7ABE28);
        if (local && isAimbotOn) {
            UpdateAimbot(local, nullptr, 0);
        }
        usleep(10000);
    }
    return nullptr;
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* res) {
    pthread_t t;
    pthread_create(&t, nullptr, HackLoop, nullptr);
    return JNI_VERSION_1_6;
}

extern "C" {
    JNIEXPORT void JNICALL Java_com_internal_asp1rin_launcher_MainActivity_setNoRecoil(JNIEnv* env, jobject obj, jboolean en) { ToggleNoRecoil(en); }
    JNIEXPORT void JNICALL Java_com_internal_asp1rin_launcher_MainActivity_setNoSpread(JNIEnv* env, jobject obj, jboolean en) { ToggleNoSpread(en); }
    JNIEXPORT void JNICALL Java_com_internal_asp1rin_launcher_MainActivity_setAimbotState(JNIEnv* env, jobject obj, jboolean en) { isAimbotOn = en; }
}
