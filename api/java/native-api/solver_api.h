/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class it_cnr_istc_ratio_api_Solver */

#ifndef _Included_it_cnr_istc_ratio_api_Solver
#define _Included_it_cnr_istc_ratio_api_Solver
#ifdef __cplusplus
extern "C" {
#endif
    /*
     * Class:     it_cnr_istc_ratio_api_Solver
     * Method:    read
     * Signature: (Ljava/lang/String;)Z
     */
    JNIEXPORT jboolean JNICALL Java_it_cnr_istc_ratio_api_Solver_read__Ljava_lang_String_2
    (JNIEnv *, jobject, jstring);

    /*
     * Class:     it_cnr_istc_ratio_api_Solver
     * Method:    read
     * Signature: ([Ljava/lang/String;)Z
     */
    JNIEXPORT jboolean JNICALL Java_it_cnr_istc_ratio_api_Solver_read___3Ljava_lang_String_2
    (JNIEnv *, jobject, jobjectArray);

    /*
     * Class:     it_cnr_istc_ratio_api_Solver
     * Method:    solve
     * Signature: ()Z
     */
    JNIEXPORT jboolean JNICALL Java_it_cnr_istc_ratio_api_Solver_solve
    (JNIEnv *, jobject);

    /*
     * Class:     it_cnr_istc_ratio_api_Solver
     * Method:    initialise
     * Signature: ()J
     */
    JNIEXPORT jlong JNICALL Java_it_cnr_istc_ratio_api_Solver_initialise
    (JNIEnv *, jobject);

    /*
     * Class:     it_cnr_istc_ratio_api_Solver
     * Method:    dispose
     * Signature: ()V
     */
    JNIEXPORT void JNICALL Java_it_cnr_istc_ratio_api_Solver_dispose
    (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif
