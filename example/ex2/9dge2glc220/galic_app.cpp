// Program Start.
//
//
//
////////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER) && _MSC_VER >= 1200
  #pragma warning( disable : 4786)
  #pragma warning( disable : 4996)
#endif


#if defined(_MSC_VER)
  #pragma comment(linker, "/subsystem:console")
  #pragma comment(linker, "/NODEFAULTLIB:library")

  #pragma comment(lib, "lgpwn_a30_.lib")
  #pragma comment(lib, "lgpwn_b30_.lib")
  #pragma comment(lib, "lgpwn_c30_.lib")
  #pragma comment(lib, "lgpwn_d30_.lib")
  #pragma comment(lib, "lgpwn_n30_.lib")
  #pragma comment(lib, "lgpwn_e30_.lib")

  #pragma comment(lib, "OpenGL32.lib")
  #pragma comment(lib, "Imm32.lib")
  #pragma comment(lib, "winmm.lib")
  #pragma comment(lib, "dxguid.lib")
  #pragma comment(lib, "ws2_32.lib")
#endif


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
#include <LcxMedia.h>



#if defined(_MSC_VER)

int main(int argc, char* argv[])
{
	PLC_APPFRAME	pApp	= NULL;
	INT				hr		= LC_OK;


	// Init GLC Library
	hr = LcSys_Init();
	if(LC_FAILED(hr))
	{
		LOGE("LcSys Init Failed. ----------------------\n");
		return LC_EFAIL;
	}


	hr = LcSys_CreateAppFrame(NULL, &pApp);
	if(LC_FAILED(hr))
		goto END;


	hr = pApp->Run(NULL);

	LcSys_DestroyAppFrame();

	LcSys_Close();						// Release GLC Library
	LcAux_Sleep(200);

END:
	hr = LcLog_ErrCount();
	while(hr)
	{
		char sbuf[128]={0};

		printf("Press the Return Key to exit program!!!\n");
		fgets(sbuf, 120, stdin);
		break;
	}

	return LC_OK;
}

#endif // _MSC_VER




///////////////////////////////////////////////////////////////////////////////
// JNIs for Android system

#if defined(__ANDROID__)
#include <jni.h>
#ifdef __cplusplus
extern "C" {
#endif


////////////////////////////////////////////////////////////////////////////////

// create the App Frame
jint Java_gpack_JniGlue_CreateFrame(JNIEnv* env, jclass claz)
{
	PLC_APPFRAME pApp= NULL;
	INT			 hr  = LC_OK;

	hr = LcSys_CreateAppFrame(NULL, &pApp);
	LOGW("Create App Frame::%d\n", hr);
	return hr;
}

// Destroy App Frame
jint Java_gpack_JniGlue_DestroyFrame(JNIEnv* env, jclass claz)
{
	LcSys_DestroyAppFrame();
	LOGW("Destroy App Frame\n");
	return LC_OK;
}

// Procedure Frame
jint Java_gpack_JniGlue_ProcFrame(JNIEnv* env, jclass claz)
{
	INT	hr = LcSys_ProcAppFrame(NULL);
	return hr;
}

// Invalid Frame
jint Java_gpack_JniGlue_InvalidFrame(JNIEnv* env, jclass claz)
{
	INT	hr = LcSys_ExecAppFrame(LC_QUERY_INVALID, NULL);
	return hr;
}


// Restore Frame
jint Java_gpack_JniGlue_RestoreFrame(JNIEnv* env, jclass claz)
{
	INT	hr = LcSys_ExecAppFrame(LC_QUERY_RESTORE, NULL);
	return hr;
}


#ifdef __cplusplus
}
#endif

#endif //__ANDROID__

