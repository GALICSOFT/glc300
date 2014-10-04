// JNIs for Android system
//
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <LcType.h>
#include <LcBase.h>
#include <LcMath.h>
#include <LcEuclid.h>
#include <LcCore.h>
#include <LcAux.h>
#include <LcStdev.h>
#include <LctEntity.h>


#ifdef __cplusplus
extern "C" {
#endif


// setup the java environment
jint Java_gpack_JniGlue_SetupSys      (JNIEnv* e,jobject o,jstring pck)
{
	//LOGI("Call::Java_gpack_JniGlue_SetupSys. -------------\n");
	static LC_HANDLE gmethod = LctJni_FindMethod("SetupSys");
	TLC_ARGS		 args;

	MAKE_ARG3(args, (LC_HANDLE)e, (LC_HANDLE)o, (LC_HANDLE)pck);

	if(NULL == gmethod)
	{
		LOGW("Call::Java_gpack_JniGlue_SetupSys::LC_INVALID_CALL\n");
		return LC_INVALID_CALL;
	}

	return LctJni_ExecMethod(gmethod, &args);
}

// opengl pixel format
jint Java_gpack_JniGlue_SetupPxlFmt   (JNIEnv* e,jobject o,jintArray fmt)
{
	//LOGI("Call::Java_gpack_JniGlue_SetupPxlFmt. -------------\n");
	static LC_HANDLE gmethod = LctJni_FindMethod("SetupPxlFmt");
	TLC_ARGS		 args;

	MAKE_ARG3(args, (LC_HANDLE)e, (LC_HANDLE)o, (LC_HANDLE)fmt);

	if(NULL == gmethod)
	{
		LOGW("Call::Java_gpack_JniGlue_SetupPxlFmt::LC_INVALID_CALL\n");
		return LC_INVALID_CALL;
	}

	return LctJni_ExecMethod(gmethod, &args);
}

// touch event process
jint Java_gpack_JniGlue_SetupTouch    (JNIEnv* e,jobject o,jint idx, jint t, jint x, jint y)
{
	//LOGI("Call::Java_gpack_JniGlue_SetupTouch. -------------\n");
	static LC_HANDLE gmethod = LctJni_FindMethod("SetupTouch");
	TLC_ARGS		 args;

	MAKE_ARG6(args, (LC_HANDLE)e, (LC_HANDLE)o, (INT)idx, (INT)t, (INT)x, (INT)y);

	if(NULL == gmethod)
	{
		LOGW("Call::Java_gpack_JniGlue_SetupTouch::LC_INVALID_CALL\n");
		return LC_INVALID_CALL;
	}

	return LctJni_ExecMethod(gmethod, &args);
}

// keypad event
jint Java_gpack_JniGlue_SetupKeypad   (JNIEnv* e,jobject o,jint idx, jint t)
{
	//LOGI("Call::Java_gpack_JniGlue_SetupKeypad. -------------\n");
	static LC_HANDLE gmethod = LctJni_FindMethod("SetupKeypad");
	TLC_ARGS		 args;

	MAKE_ARG4(args, (LC_HANDLE)e, (LC_HANDLE)o, (INT)idx, (INT)t);
	if(NULL == gmethod)
	{
		LOGW("Call::Java_gpack_JniGlue_SetupKeypad::LC_INVALID_CALL\n");
		return LC_INVALID_CALL;
	}

	return LctJni_ExecMethod(gmethod, &args);
}

// sensor process
jint Java_gpack_JniGlue_SetupSensor   (JNIEnv* e,jobject o,jint idx, jfloat x, jfloat y, jfloat z)
{
	//LOGI("Call::Java_gpack_JniGlue_SetupSensor. -------------\n");
	static LC_HANDLE gmethod = LctJni_FindMethod("SetupSensor");
	TLC_ARGS		 args;

	MAKE_ARG6(args, (LC_HANDLE)e, (LC_HANDLE)o, (INT)idx, (FLOAT)x, (FLOAT)y, (FLOAT)z);
	if(NULL == gmethod)
	{
		LOGW("Call::Java_gpack_JniGlue_SetupSensor::LC_INVALID_CALL\n");
		return LC_INVALID_CALL;
	}

	return LctJni_ExecMethod(gmethod, &args);
}

// font process
jint Java_gpack_JniGlue_SetupFontPixel(JNIEnv* e,jobject o,jint w,jint h,jbyteArray a,jfloatArray s)
{
	//LOGI("Call::Java_gpack_JniGlue_SetupFontPixel. -------------\n");
	static LC_HANDLE gmethod = LctJni_FindMethod("SetupFontPixel");
	TLC_ARGS		 args;

	MAKE_ARG6(args, (LC_HANDLE)e, (LC_HANDLE)o, (INT)w, (INT)h, (LC_HANDLE)a, (LC_HANDLE)s);
	if(NULL == gmethod)
	{
		LOGW("Call::Java_gpack_JniGlue_SetupFontPixel::LC_INVALID_CALL\n");
		return LC_INVALID_CALL;
	}

	return LctJni_ExecMethod(gmethod, &args);
}

// Imm Process
jint Java_gpack_JniGlue_SetupImeString(JNIEnv* e,jobject o, jint n,jbyteArray a)
{
	//LOGI("Call::Java_gpack_JniGlue_SetupImeString. -------------\n");
	static LC_HANDLE gmethod = LctJni_FindMethod("SetupImeString");
	TLC_ARGS		 args;

	MAKE_ARG4(args, (LC_HANDLE)e, (LC_HANDLE)o, (INT)n, (LC_HANDLE)a);
	if(NULL == gmethod)
	{
		LOGW("Call::Java_gpack_JniGlue_SetupImeString::LC_INVALID_CALL\n");
		return LC_INVALID_CALL;
	}

	return LctJni_ExecMethod(gmethod, &args);
}

// Net Process
jint Java_gpack_JniGlue_SetupBtMsg    (JNIEnv* e,jobject o,jint a, jint c, jint n, jbyteArray s)
{
	//LOGI("Call::Java_gpack_JniGlue_SetupBtMsg. -------------\n");
	static LC_HANDLE gmethod = LctJni_FindMethod("SetupBtMsg");
	TLC_ARGS		 args;

	MAKE_ARG6(args, (LC_HANDLE)e, (LC_HANDLE)o, (INT)a, (INT)c, (INT)n, (LC_HANDLE)s);
	if(NULL == gmethod)
	{
		LOGW("Call::Java_gpack_JniGlue_SetupBtMsg::LC_INVALID_CALL\n");
		return LC_INVALID_CALL;
	}

	return LctJni_ExecMethod(gmethod, &args);
}

#ifdef __cplusplus
}
#endif

