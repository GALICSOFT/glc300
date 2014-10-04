// Implementation of the CGpApp class.
//  Created by Heesung Oh
//  Copyright GALIC SOFT Inc. All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER) && _MSC_VER >= 1200
  #pragma warning( disable : 4786)
  #pragma warning( disable : 4996)
#endif


#include <vector>
#include <list>
#include <set>
#include <map>
using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include <LcType.h>
#include <LcBase.h>
#include <LcMath.h>
#include <LcEuclid.h>
#include <LcCore.h>
#include <LcAux.h>
#include <LcStdev.h>
#include <LcxEntity.h>
#include <LcxMedia.h>

#include "GpApp.h"


CGpApp* CGpApp::m_pApp = NULL;


CGpApp::CGpApp()
{
	vector<int > t_vector;		// for importing std::vector
	t_vector.push_back(0);
	t_vector.clear();

	list<int > t_list;			// for importing std::list
	t_list.push_back(0);
	t_list.clear();

	map<int, int > t_map;		// for importing std::map
	t_map.insert(pair<int, int>(0xCC, 0xDD));
	t_map.clear();

	set<int> t_set;				// for importing std::set
	t_set.insert(0xFF);
	t_set.clear();


	memset(m_sCls, 0, sizeof m_sCls);
	strcpy(m_sCls, "GaLic G-pack");

	m_nScnW		= 800		;
	m_nScnH		= 480		;
	m_nScnD		= 16		;
	m_nScnX		= -1		;
	m_nScnY		= -1		;
	m_bShowSt	= LC_TRUE	;

	m_pDev		= NULL		;
	m_pSpt		= NULL		;
	m_pInput	= NULL		;
	m_TimeFPS	= 120		;
	m_TimeElps	= 1000./m_TimeFPS;		// Ellapsed time
	m_pFont		= NULL		;

	memset(m_pSnd, 0, sizeof(PLCX_SOUND) * MAX_SND);
}


INT CGpApp::Create(PLC_ARGS pArg)
{
	TLC_ARGS args;
	INT	hr	= LC_OK;


	// Set Main procedure Function Pointer
	if(LC_FAILED(LcSys_SetMainRunFunc(CGpApp::Run3D)))
		return LC_EFAIL;


	// Create Window
	hr = LcSys_CreateWindow(CGpApp::WndProc, m_sCls, m_nScnW, m_nScnH, m_nScnX, m_nScnY);
	if(LC_FAILED(hr))
	{
		LOGE("Create Window Failed. -------------------\n");
		return LC_EFAIL;
	}


	// Create GLC Rendering Device
	hr = LcDev_CreateDevice(NULL, &m_pDev);
	if(LC_FAILED(hr))
	{
		LOGE("Create Device Failed. -------------------\n");
		return LC_EFAIL;
	}

	// get the default Rendering 2D sprite
	m_pSpt = (PLC_SPRITE)LcVar_ReadP(LC_VAR_SPRITE);


	// Create Input
	if(LC_FAILED(LcxEnt_CreateInput(NULL, &m_pInput)))
	{
		LOGE("Create Input Failed. --------------------\n");
		return LC_EFAIL;
	}


	////////////////////////////////////////////////////////////////////////////
	// Test Default Font...
	// Create Font
	TLC_FONT	tFont(LCCMD_DEFAULT, LC_FONT_AN_INTERNAL, 12);
	LCXVECTOR3	vcPos(10, 420, 0.0F);
	LCXCOLOR	dCol(1.0F, 1.0F, 0.0F, 1);
	MAKE_ARG2(args, (LC_HANDLE)&tFont, (LC_HANDLE)m_pSpt);
	if(LC_FAILED(LcDev_CreateFont(NULL, &m_pFont, &args)))
	{
		LOGE("Create System Font Failed. --------------\n");
		return LC_EFAIL;
	}
	m_pFont->String("System Starting...");
	m_pFont->Position(&vcPos);
	m_pFont->Color(&dCol);


	m_pDev->SetRenderState(LC_RS_CLEAR_COLOR, 0xFF006699);
	m_pDev->SetRenderState(LC_RS_DEPTH_TEST, LC_ST_ENABLE);
	m_pDev->SetRenderState(LC_RS_CULL_FACE, LC_ST_ENABLE);



	// Create Sound Device: must be created after device creating
	if(LC_FAILED(LcxSmd_SoundDeviceOpen()))
	{
		LOGE("Create Sound Device Failed. -------------\n");
		return LC_EFAIL;
	}


	// Init Game Data
	if(LC_FAILED(Init()))
	{
		LOGE("Game Data Init Failed. ------------------\n");
		return LC_EFAIL;
	}


	return LC_OK;
}


INT CGpApp::Cleanup()
{
	INT	hr = 0;

	if(NULL == m_pDev)
		return LC_OK;


	Destroy();


	SAFE_RELEASE( m_pFont   );		// Release Font
	SAFE_RELEASE( m_pInput	);		// Release Input


	LcxSmd_SoundDeviceClose();			// Sound Device Release

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


	LcAux_Sleep(200);

	return LC_OK;
}


void CGpApp::UpdateStatus()
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


////////////////////////////////////////////////////////////////////////////////


LRESULT LC_WINAPI CGpApp::WndProc(LC_HWND, UINT, WPARAM, LPARAM)
{
	return LC_TRUE;
}


// Run Program
INT CGpApp::Run(LC_HANDLE)
{
#if defined(__APPLE__) || defined(__IPHONE__)

	return LcSys_Run();

#else

	while(1)
	{
		if(LC_FAILED(LcSys_Run()))
			break;
	}

	Cleanup();

#endif

	return LC_OK;
}


INT	CGpApp::Proc(LC_HANDLE)
{
	//LOGE("Proc-----------------------------------------------------------\n");

	if(LC_FAILED(FrameMove()))
		return LC_EFAIL;


	if(LC_FAILED(Render()))
		return LC_EFAIL;


	m_pDev->Present(0,0,0,0);

	UpdateStatus();

	return LC_OK;
}


INT	LC_CALLBACK CGpApp::Run3D(LC_HANDLE pData)
{
	if(CGpApp::m_pApp)
		return CGpApp::m_pApp->Proc(pData);

	return LC_OK;
}


INT CGpApp::Query(char* sCmd, LC_HANDLE pData)
{
	INT hr = LC_OK;


	if(0 == LcStr_Stricmp((char*)"Get Script File Package", sCmd) )
		return LC_EFAIL;

	else if(0 == LcStr_Stricmp((char*)"Window Resize", sCmd) )
		hr = m_pDev->SetRenderState(LC_RS_EAGL_RESIZE, pData);		// Resize Need CAEAGLLayer*

	
	else if(0 == LcStr_Stricmp((char*)"Set Show Status", sCmd) )
		m_bShowSt = *((INT*)pData);

	else if(0 == LcStr_Stricmp((char*)"Set Screen Position X", sCmd) )
		m_nScnX = *((INT*)pData);

	else if(0 == LcStr_Stricmp((char*)"Set Screen Position Y", sCmd) )
		m_nScnY = *((INT*)pData);

	else if(0 == LcStr_Stricmp((char*)"Set Screen Width", sCmd) )
		m_nScnW = *((INT*)pData);

	else if(0 == LcStr_Stricmp((char*)"Set Screen Height", sCmd) )
		m_nScnH = *((INT*)pData);

	else if(0 == LcStr_Stricmp((char*)"Set Class Name", sCmd) )
		strcpy(m_sCls, (char*)pData);

	else
		return LC_EFAIL;


	return hr;
}


INT CGpApp::SetAttrib(UINT nCmd, LC_HANDLE pData)
{
	return LC_EFAIL;
}



INT CGpApp::GetAttrib(UINT nCmd, LC_HANDLE pData)
{
	return LC_EFAIL;
}



////////////////////////////////////////////////////////////////////////////////


// get the main app
PLC_APPFRAME LcSys_GetMainApp()
{
	return CGpApp::m_pApp;
}

// GameApp Instance
INT LcSys_CreateAppFrame(char* sCmd					// Create  the main application instance. It must be implemented in program start.
					, PLC_APPFRAME* pOut
					, PLC_ARGS pArg
					)
{
	PLC_APPFRAME pObj = NULL;

	if(NULL != CGpApp::m_pApp)
	{
		*pOut = CGpApp::m_pApp;
		return LC_FILE_ALREADY_OPEN;
	}


	*pOut = NULL;
	pObj = new CGpApp;
	LcVar_WriteP(LC_VAR_APP_MAIN, pObj);			//save the main application instance

	if(0 > pObj->Create(pArg))
	{
		LcVar_WriteP(LC_VAR_APP_MAIN, NULL);		//save the main application instance
		delete pObj;
		return LC_EFAIL;
	}

	CGpApp::m_pApp = (CGpApp*)pObj;
	*pOut = pObj;
	return LC_OK;
}


INT LcSys_DestroyAppFrame()
{
	if(NULL == CGpApp::m_pApp)
		return LC_OK;

	CGpApp::m_pApp->Cleanup();

	delete (CGpApp::m_pApp);
	CGpApp::m_pApp = NULL;

	return LC_OK;
}


INT LcSys_ProcAppFrame(LC_HANDLE)
{
	INT hr = 0;

	if(NULL == CGpApp::m_pApp)
		return LC_EFAIL;

	hr = CGpApp::m_pApp->Proc(NULL);
	return hr;
}


INT LcSys_ExecAppFrame(char* sCmd, LC_HANDLE pData)
{
	if     (0 == LcStr_Stricmp(sCmd, LC_QUERY_INVALID))
	{
		return CGpApp::m_pApp->Invalid();
	}
	else if(0 == LcStr_Stricmp(sCmd, LC_QUERY_RESTORE))
	{
		return CGpApp::m_pApp->Restore();
	}

	return LC_EFAIL;
}
