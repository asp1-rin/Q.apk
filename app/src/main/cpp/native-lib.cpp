#include <jni.h>
#include <string>
#include "KittyMemory.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_internal_asp1rin_launcher_MainActivity_stringFromJNI(
        JNIEnv* env, jobject /* this */) {
    
    // KittyMemory 함수 호출 테스트용
    std::string info = KittyMemory::getVersion();
    
    return env->NewStringUTF(info.c_str());
}
