#include <jni.h>
#include <string>
#include "KittyMemory/KittyMemory.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_internal_asp1rin_launcher_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++ with KittyMemory";
    return env->NewStringUTF(hello.c_str());
}
