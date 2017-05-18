#include <jni.h>
#include <string>
#include "android/log.h"
#include <assert.h>

#ifndef _Included_HELLO_TestJni
#define _Included_HELLO_TestJni

#define  LOG_TAG    "cunnar-version-update"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)


#define CLASS_NAME "com/zhangy/dudu/voicechatwithjni/JNIWrapper"

//#define SUFFIX_METHOD(rettype, name)  \
//   extern "C" JNIEXPORT rettype JNICALL Java_com_zhangy_dudu_voicechatwithjni_JNIWrapper_##name
//
//
////静态JNI注册的方式，按照JNI规则，包名+类名+方法名来注册本地方法
//
//SUFFIX_METHOD(jstring, stringFromJNI)(JNIEnv* env, jobject) {
//    std::string hello = "Hello from C++";
//    LOGI("hello string from jni ===%s,count %d",hello.c_str());
//    return env->NewStringUTF(hello.c_str());
//}

//动态JNI注册方式

static jstring native_hello(JNIEnv* env,jobject thiz){
    return env->NewStringUTF("动态注册JNI");
}

//方法对应表
static JNINativeMethod gMethods[] = {
        {"stringFromJNI","()Ljava/lang/String",(void*)native_hello},
};

/*
* 为某一个类注册本地方法
*/
static int registerNativeMethods(JNIEnv* env
        , const char* className
        , JNINativeMethod* gMethods, int numMethods) {
    jclass clazz;
    clazz = env->FindClass(className);
    if (clazz == NULL) {
        return JNI_FALSE;
    }
    if (env->RegisterNatives(clazz, gMethods, numMethods) < 0) {
        return JNI_FALSE;
    }


    return JNI_TRUE;
}

/*
* 为所有类注册本地方法
*/
static int registerNatives(JNIEnv* env) {
    const char* kClassName = CLASS_NAME;//指定要注册的类
    return registerNativeMethods(env, kClassName, gMethods,
                                 sizeof(gMethods) / sizeof(gMethods[0]));
}

/*
* System.loadLibrary("lib")时调用
* 如果成功返回JNI版本, 失败返回-1
*/
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    JNIEnv* env = NULL;
    jint result = -1;
    LOGI("jni onload call ");
    if (vm -> GetEnv((void**) &env,JNI_VERSION_1_4) != JNI_OK) {
        return -1;
    }
    assert(env != NULL);
    if (!registerNatives(env)) {//注册
        return -1;
    }
    //成功
    result = JNI_VERSION_1_4;
    return result;
}
#endif _Included_HELLO_TestJni




