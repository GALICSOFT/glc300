// Implementation of the CGpMain class.
//
////////////////////////////////////////////////////////////////////////////////


#pragma warning(disable:4005)

#include "_StdAfx.h"

#if defined _MSC_VER
  #include <Windows.h>
#endif


#define MEDIA_DIR	"../../media/"


#if defined(__ANDROID__)
char* file[]=
{
	(char*)"av/skiing.ts",
	(char*)"av/chess.ts",
	(char*)"av/skiing.ts",
	(char*)"av/chess.ts",
	NULL
};
#else

char* file[]=
{
	(char*)MEDIA_DIR"av/skiing.avi",
	(char*)MEDIA_DIR"av/chess.avi",
	(char*)MEDIA_DIR"av/skiing.avi",
	(char*)MEDIA_DIR"av/chess.avi",
	NULL
};

#endif

struct _TavRect
{
	FLOAT x, y, w, h;
}
g_rctShow[][MAX_NUM] = 
{
	{{10,  20, 120, 50}, {180,  20, 120, 50}, {350,  20, 120, 50}, {500,  20, 120, 150},},
	{{10, 140, 120, 50}, {180, 140, 120, 50}, {350, 140, 120, 50}, {500, 140, 120, 150},},
	{{10, 260, 120, 50}, {180, 260, 120, 50}, {350, 260, 120, 50}, {500, 260, 120, 150},},
	{{10, 380, 120, 50}, {180, 380, 120, 50}, {350, 380, 120, 50}, {500, 380, 120, 150},},
};


CGpMain::CGpMain()
{
	m_pGrid		= NULL;

	for(int i=0; i<MAX_NUM; ++i)
		m_avObj[i] = NULL;
}


INT	CGpMain::Init()
{
	TLC_ARGS	args;
	INT			hr = LC_OK;

	hr = LcxEnt_CreateEntity(LCXCMD_ENTITY_GRID, &m_pGrid);
	if(LC_FAILED(hr))
		return LC_EFAIL;


	for(int i=0; i<MAX_NUM; ++i)
	{
		MAKE_ARG2(args, (UINT)LC_SRC_T_FILE, file[i]);
		hr = LcxSmd_CreateShow(NULL, &m_avObj[i], &args);
		if(LC_FAILED(hr))
			return LC_EFAIL;
	}

	

	return LC_OK;
}



INT	CGpMain::Destroy()
{
	for(int i=0; i<MAX_NUM; ++i)
	{
		SAFE_RELEASE(	m_avObj[i]);
	}

	SAFE_RELEASE(	m_pGrid		);

	return LC_OK;
}


INT CGpMain::FrameMove()
{
#if defined _MSC_VER
//	LcAux_Sleep(10);
#endif

	//m_pDev->Query(LC_QUERY_INVALID, NULL);									// release,
	//m_pDev->Query(LC_QUERY_RESTORE, NULL);									// restore performance test


	static int n = 0;
	++n;

	if(n>150)
	{
		sprintf(m_sMsg, "FPS: %3.f\n", m_TimeFPS);
		n = 0;
	}

	SAFE_UPDATE(	m_pInput	);													// Update Input

	LCXVECTOR3	vcMtsPos = m_pInput->MtsPosition();
	const BYTE*	pKey = m_pInput->KeyMap();
	const BYTE*	pMts = m_pInput->MtsMap();


	if(pKey[LCIK_ESCAPE])
		return LC_EFAIL;


	FLOAT x,y, w,h;

	if(LCIK_KEYDOWN == pMts[0])
	{
		for(int j=0; j<MAX_NUM; ++j)
		{
			x = g_rctShow[j][0].x;
			y = g_rctShow[j][0].y;
			w = g_rctShow[j][0].w;
			h = g_rctShow[j][0].h;

			if(m_pInput->IsInRect(x, y, w, h ) )
				m_avObj[j]->Play();


			x = g_rctShow[j][1].x;
			y = g_rctShow[j][1].y;
			w = g_rctShow[j][1].w;
			h = g_rctShow[j][1].h;

			if(m_pInput->IsInRect(x, y, w, h ) )
				m_avObj[j]->Stop();


			x = g_rctShow[j][2].x;
			y = g_rctShow[j][2].y;
			w = g_rctShow[j][2].w;
			h = g_rctShow[j][2].h;

			if(m_pInput->IsInRect(x, y, w, h ) )
				m_avObj[j]->Pause();
		}
	}




	for(int i=0; i<MAX_NUM; ++i)
	{
		if(m_avObj[i])
			m_avObj[i]->FrameMove();
	}




	{
		char sbuf[128]={0};
		DOUBLE fFPS		   = m_TimeFPS;
		DOUBLE fElasedTime = (DOUBLE)m_TimeElps;

		sprintf(sbuf, "°¥¸¯: %.f(%.1f)F", fFPS, fElasedTime);

		m_misFont->String(sbuf);
	}


	return LC_OK;
}


INT CGpMain::Render()
{
	if( LC_FAILED( m_pDev->BeginScene() ) )
		return LC_EFAIL;


	m_pDev->Clear(LC_CLEAR_COLOR_BUFFER | LC_CLEAR_DEPTH_BUFFER);


	m_pDev->SetRenderState(LC_RS_CULL_FACE, LC_ST_DISABLE);
	m_pDev->SetRenderState(LC_RS_LIGHTING, LC_ST_DISABLE);
	m_pDev->SetRenderState(LC_RS_CULL_MODE, LC_ST_CCW);
	m_pDev->SetRenderState(LC_RS_CULL_FACE, LC_ST_BACK);


	m_pSpt->Begin();



	LCXVECTOR3	t;
	LCXCOLOR	d(1,1,1,1);
	PLC_TEXTURE pTex = NULL;


	for(int j=0; j<MAX_NUM; ++j)
	{
		pTex = m_avObj[j]->Texture();
		t = LCXVECTOR3(g_rctShow[j][3].x, g_rctShow[j][3].y, 0);

		if(pTex)
			m_pSpt->Draw(pTex, NULL, &t, NULL, &d);

		for(int i=0; i<3; ++i)
		{
			t = LCXVECTOR3(g_rctShow[j][i].x, g_rctShow[j][i].y, 0);
			m_pSpt->DrawRect( &t, g_rctShow[j][i].w, g_rctShow[j][i].h, 2.0F, &d);
		}
	}


	m_misFont->DrawTxt();
	m_pSpt->End();

	m_pDev->EndScene();

	return LC_OK;
}



INT CGpMain::Invalid()
{
	for(int j=0; j<MAX_NUM; ++j)
		m_avObj[j]->Query(LC_QUERY_INVALID, NULL);

	m_pGrid		->Query(LC_QUERY_INVALID, NULL);

	CGpApp::Invalid();

	return LC_OK;
}


INT CGpMain::Restore()
{
	CGpApp::Restore();

	m_pGrid		->Query(LC_QUERY_RESTORE, NULL);

	for(int j=0; j<MAX_NUM; ++j)
		m_avObj[j]->Query(LC_QUERY_RESTORE, NULL);

	return LC_OK;
}


INT CGpMain::Query(char* sCmd, LC_HANDLE pData)
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


INT CGpMain::SetAttrib(UINT, LC_HANDLE)
{
	return LC_OK;
}


INT CGpMain::GetAttrib(UINT, LC_HANDLE)
{
	return LC_OK;
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
	pObj = new CGpMain;

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



