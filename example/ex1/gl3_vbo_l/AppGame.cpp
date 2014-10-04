// Implementation of the CAppGame class.
//
//
//
////////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER) && _MSC_VER >= 1200
  #pragma warning( disable : 4786)
  #pragma warning( disable : 4996)
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


#include "AppGame.h"


CAppGame* CAppGame::m_pAppGame = NULL;


CAppGame::CAppGame()
{
	CAppGame::m_pAppGame = this;

	m_pDev		= NULL;

	memset(m_sCls, 0, sizeof(m_sCls));
	strcpy(m_sCls,"LC_Tutorial");


	m_nScnW		= 0;
	m_nScnH		= 0;

	m_TimeElps	= 0;
	m_TimeFPS		= 30.0;
}


INT CAppGame::Create(PLC_ARGS pArg)
{
	INT		hr = 0;
	UINT	dClearColor = 0xFF006699;


	// Init GLC Library
	if(LC_FAILED(LcSys_Init()))
		return LC_OK;

	// Set Main procedure Function Pointer
	if(LC_FAILED(LcSys_SetMainRunFunc(CAppGame::Run3D)))
		goto End;


	// Create Window
	hr = LcSys_CreateWindow(NULL, m_sCls);
	if(LC_FAILED(hr))
		goto End;


	// Create GLC Rendering Device
	if(LC_FAILED(LcDev_CreateDevice(NULL, &m_pDev)))
		goto End;


	// get the window size
	LcVar_WindowSize(&m_nScnW, &m_nScnH);

	//save the main application instance
	LcVar_WriteP(LC_VAR_APP_MAIN, this);


	// setup the rendering state
	m_pDev->SetRenderState(LC_RS_CLEAR_COLOR, dClearColor);
	m_pDev->SetRenderState(LC_RS_DEPTH_TEST, LC_ST_ENABLE);
	m_pDev->SetRenderState(LC_RS_CULL_FACE, LC_ST_ENABLE);


	// init game data
	if(LC_FAILED(Init()))
		goto End;


	return LC_OK;


End:
	Cleanup();
	return LC_OK;
}


INT CAppGame::Run(LC_HANDLE)
{
	while(1)	// Run Program
	{
		if(LC_FAILED(LcSys_Run()))
			break;

	}

	Cleanup();

	return LC_OK;
}


INT	CAppGame::Proc(LC_HANDLE)
{
	if(LC_FAILED(FrameMove()))
		return LC_EFAIL;


	if(LC_FAILED(Render()))
		return LC_EFAIL;

	m_pDev->Present();

	UpdateStatus();


	return LC_OK;
}


INT	LC_CALLBACK CAppGame::Run3D(LC_HANDLE v)
{
	if(CAppGame::m_pAppGame)
		return CAppGame::m_pAppGame->Proc(v);

	return LC_OK;
}


INT CAppGame::Cleanup()
{
	int hr = 0;


	Destroy();

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

	return LC_OK;
}



void CAppGame::UpdateStatus()
{
	static INT	MaxCnt = 16;
	static INT	dFrame = 0;
	static DINT	dBgn = ::LcAux_TimeGetTime();
	DINT		dCur = ::LcAux_TimeGetTime();


	LcVar_TimeStored(&dCur, 1);						// Save the Last Time

	++dFrame;

	if(dFrame>=MaxCnt)
	{
		m_TimeElps = DOUBLE(dCur-dBgn)/dFrame;
		m_TimeFPS = 1000./m_TimeElps;
		dFrame = 0;
		dBgn = dCur;


		LcVar_TimeElapsed(&m_TimeElps, 1);			// Save Elapsed average Time
		LcVar_TimeFrameRate(&m_TimeFPS, 1);		// Save the frame rate

		if     (2048< m_TimeFPS) MaxCnt = 512;
		else if(1024< m_TimeFPS) MaxCnt = 256;
		else if( 512< m_TimeFPS) MaxCnt = 128;
		else if( 256< m_TimeFPS) MaxCnt =  64;
		else if( 128< m_TimeFPS) MaxCnt =  32;
		else if(  64< m_TimeFPS) MaxCnt =  16;
		else if(  32< m_TimeFPS) MaxCnt =   8;
		else                     MaxCnt =   4;
	}
}




