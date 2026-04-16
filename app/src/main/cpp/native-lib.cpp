#include <jni.h>
#include <string>
#include "KittyMemory.h" // 나중에 파일 채우면 자동 연결됨

extern "C" JNIEXPORT jstring JNICALL
Java_com_internal_asp1rin_launcher_MainActivity_stringFromJNI(
        JNIEnv* env, jobject /* this */) {
    std::string hello = "Hello from Q.apk";
    return env->NewStringUTF(hello.c_str());
}
