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
  #pragma comment(lib, "lgpwn_a30_.lib")
  #pragma comment(lib, "lgpwn_b30_.lib")
  #pragma comment(lib, "lgpwn_c30_.lib")
  #pragma comment(lib, "lgpwn_d30_.lib")
  #pragma comment(lib, "lgpwn_i30_.lib")
  #pragma comment(lib, "lgpwn_n30_.lib")
  #pragma comment(lib, "lgpwn_e30_.lib")

  #pragma comment(lib, "OpenGL32.lib")
  #pragma comment(lib, "Imm32.lib")
  #pragma comment(lib, "winmm.lib")
  #pragma comment(lib, "dxguid.lib")
  #pragma comment(lib, "ws2_32.lib")
#endif


#if defined(_MSC_VER)
  #define _CRTDBG_MAP_ALLOC
  #include <crtdbg.h>
#endif


#include <stdio.h>

#include <LcType.h>
#include <LcBase.h>
#include <LcMath.h>
#include <LcEuclid.h>
#include <LcCore.h>
#include <LcAux.h>


PLC_DEVICE		m_pDev = NULL;		// Device


DOUBLE GetAppFrame();


// Main Loop
INT LC_CALLBACK Run(LC_HANDLE)
{
#if defined(_WIN32)
	LcAux_Sleep(10);
#endif

	static INT c=0;
	++c;

//	if(c>20*60*20)
	if(c>8*60*2)
	{
		printf("Game Process Terminated\n");
		return LC_EFAIL;
	}


	//m_pDev->Query(LC_QUERY_INVALID, NULL);
	//m_pDev->Query(LC_QUERY_RESTORE, NULL);


	FLOAT fFrame = (FLOAT)GetAppFrame();

	static LCXCOLOR ClearColor(1,1,1,1);

	static int n=0;
	++n;

	if(n>60)
	{
		printf("%f\n", fFrame);
		n = 0;

		ClearColor.r = (LcAux_Rand(100, 155))/255.0f;
		ClearColor.g = (LcAux_Rand(100, 155))/255.0f;
		ClearColor.b = (LcAux_Rand(100, 155))/255.0f;

		// Set Clear Color
		UINT dColor = ClearColor;
		m_pDev->SetRenderState(LC_RS_CLEAR_COLOR, dColor);
		m_pDev->Clear(LC_CLEAR_COLOR_BUFFER | LC_CLEAR_DEPTH_BUFFER);
	}


	// Prepare Rendering...
	m_pDev->BeginScene();

	// Clear Backbuffer
	m_pDev->Clear(LC_CLEAR_COLOR_BUFFER | LC_CLEAR_DEPTH_BUFFER);



	// Post Rendering...
	m_pDev->EndScene();

	return LC_OK;
}


// Main Program
int main(int argc, char* argv[])
{
//	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


	int hr;
	// Initialize GLC Library.
	LcSys_Init();

	printf("LcSys_Init\n");

	// Set Main procedure Function Pointer
	LcSys_SetMainRunFunc(Run);

	// Create Window
	hr = LcSys_CreateWindow(NULL, (char*)"LC_Tutorial");
	if(LC_FAILED(hr))
	{
		printf("LcSys_CreateWindow Failed\n");
		return LC_EFAIL;
	}

	// Create GLC Rendering Device
	if(LC_FAILED(LcDev_CreateDevice(NULL, &m_pDev)))
	{
		printf("LcDev_CreateDevice Failed\n");
		return LC_EFAIL;
	}




	// Run Program
	while(1)
	{
		if(LC_FAILED(LcSys_Run()))
			break;

		// Flipping
		m_pDev->Present(0,0,0,0);
	}

	// Release Device
	SAFE_RELEASE( m_pDev );

	// Release Window
	LcSys_DestroyWindow();

	// Release GLC
	LcSys_Close();

	hr = LcVar_RefCountObject();
	if(0 == hr)
		printf(
				"Remain: %d\n"
				"release success.\n"
				, hr
				);
	else
		printf(
				"Remain: %d\n"
				"The non-zero reference count means that\n"
				"there is something object not cleaned up.\n"
				, hr
				);


//	_CrtDumpMemoryLeaks( );
	return LC_OK;
}



DOUBLE GetAppFrame()
{
#if defined(_WIN32)
	static INT		MaxCount = 60;
#else
	static INT		MaxCount = 10;
#endif

	static DOUBLE	fFps = 0.;
	static INT		iCnt = 0;
	static DINT		dBgn = ::LcAux_TimeGetTime();
	DINT			dCur = ::LcAux_TimeGetTime();

	++iCnt;

	if(iCnt>=MaxCount)
	{
		fFps = DOUBLE(dCur-dBgn);
		fFps = iCnt*1000./fFps;
		iCnt = 0;
		dBgn = dCur;
	}

	return fFps;
}

