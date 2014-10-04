//
// Program Start.
//
////////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER) && _MSC_VER > 1000
  #pragma warning( disable : 4786)
  #pragma warning( disable : 4996)
#endif


#if defined(_MSC_VER)
  #pragma comment(linker, "/subsystem:console")
  #pragma comment(linker, "/NODEFAULTLIB:library")

#if defined(_DEBUG)
  #pragma comment(lib, "lgpwn_a30_.lib")
  #pragma comment(lib, "lgpwn_b30_.lib")
  #pragma comment(lib, "lgpwn_c30_.lib")
  #pragma comment(lib, "lgpwn_d30_.lib")
  #pragma comment(lib, "lgpwn_n30_.lib")
  #pragma comment(lib, "lgpwn_e30_.lib")
  #pragma comment(lib, "dstrmbase_.lib")
#else

  #pragma comment(lib, "lgpwn_a30.lib")
  #pragma comment(lib, "lgpwn_b30.lib")
  #pragma comment(lib, "lgpwn_c30.lib")
  #pragma comment(lib, "lgpwn_d30.lib")
  #pragma comment(lib, "lgpwn_n30.lib")
  #pragma comment(lib, "lgpwn_e30.lib")
  #pragma comment(lib, "dstrmbase.lib")
#endif

  #pragma comment(lib, "OpenGL32.lib")
  #pragma comment(lib, "Imm32.lib")
  #pragma comment(lib, "winmm.lib")
  #pragma comment(lib, "dxguid.lib")
  #pragma comment(lib, "ws2_32.lib")
  #pragma comment(lib, "comctl32.lib")
#endif


#if defined(_MSC_VER)
  #define _CRTDBG_MAP_ALLOC
  #include <crtdbg.h>
#endif


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#if defined(__ANDROID__)
  #include <jni.h>
#endif

#include <LcType.h>
#include <LcBase.h>
#include <LcCore.h>
#include <LcAux.h>
#include <LcStdev.h>
#include <LcxMedia.h>



#if defined(_MSC_VER)

int main(int argc, char* argv[])
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(262);


	char*			appPath = NULL;
	char*			luaFile = NULL;

	TLC_ARGS		appArg	= {0, };
	PLC_APPFRAME	pApp	= NULL;
	INT				hr		= LC_OK;


#if defined(_MSC_VER)
	if(2<argc)
	{
		appPath = argv[1];
		luaFile = argv[2];
		printf("Path:%s-------------------\n", appPath);
		printf("Lua :%s-------------------\n", luaFile);

		MAKE_ARG2(appArg, appPath, luaFile);
	}
#endif


	// Init GLC Library
	hr = LcSys_Init(&appArg);
	if(LC_FAILED(hr))
	{
		LOGE("LcSys Init Failed. ----------------------\n");
		return LC_EFAIL;
	}


	hr = LcSys_CreateAppFrame(NULL, &pApp, &appArg);
	if(LC_FAILED(hr))
		goto END;


	hr = pApp->Run(NULL);

	LcSys_DestroyAppFrame();

	LcSys_Close();						// Release GLC Library
	LcAux_Sleep(300);
END:
	hr = LcLog_ErrCount();
	while(hr)
	{
		char sbuf[128]={0};

		printf("Program error count: %d\n", hr);

		//printf(	"If you would like to continue,"
		//			" try to press the Return Key!!\n");
		printf("check the error message\nPress the Return Key to exit program!!!\n");
		fgets(sbuf, 120, stdin);
		break;
	}

	//_CrtDumpMemoryLeaks( );
	return LC_OK;
}

#endif // _MSC_VER




///////////////////////////////////////////////////////////////////////////////
// JNIs for Android system

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
	LOGI("Create App Frame::%d\n", hr);
	return hr;
}

// Destroy App Frame
jint Java_gpack_JniGlue_DestroyFrame(JNIEnv* env, jclass claz)
{
	LcSys_DestroyAppFrame();
	LOGI("Destroy App Frame\n");
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


