// Implementation of the CMain class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


#define MEDIA_DIR	"res/"


CMain::CMain()
{
	m_pLyr		= NULL;
	m_pInput	= NULL;
	m_pXYZ		= NULL;

	m_pTds0		= NULL;
	m_pTds1		= NULL;
}


INT	CMain::Init()
{
	TLC_ARGS	args;
	INT			hr = LC_OK;

	// Create Sprite Layer
	MAKE_ARG1(args, (UINT)LC_OBJ_MODEL2D);
	if(LC_FAILED(LcDev_CreateSprite(NULL, &m_pLyr, &args)))
		return LC_EFAIL;


	// Input »ý¼º
	if(LC_FAILED(LcxEnt_CreateInput(NULL, &m_pInput)))
		return LC_EFAIL;

	if(LC_FAILED(LcxEnt_CreateEntity(LCXCMD_ENTITY_AXIS, &m_pXYZ)))
		return LC_EFAIL;


	char	sFileTds  [] = MEDIA_DIR"boss01.tds";


	MAKE_ARG2(args, sFileTds, (LC_HANDLE)m_pLyr);
	hr = LcxEnt_CreateTds(NULL, &m_pTds0, &args);
	if(LC_FAILED(hr))
		return LC_EFAIL;


	MAKE_ARG2(args, sFileTds, (LC_HANDLE)m_pLyr);
	hr = LcxEnt_CreateTds(NULL, &m_pTds1, &args);
	if(LC_FAILED(hr))
		return LC_EFAIL;


	LCXVECTOR2	vcPos0(-240.0F, -40.F);
	LCXVECTOR2	vcPos1( 240.0F,  40.F);
	
	m_pTds0->Position(&vcPos0);
	m_pTds1->Position(&vcPos1);

	return LC_OK;
}



INT	CMain::Destroy()
{
	SAFE_RELEASE(	m_pTds0	);
	SAFE_RELEASE(	m_pTds1	);

	SAFE_RELEASE(	m_pXYZ		);
	SAFE_RELEASE(	m_pInput	);
	SAFE_RELEASE(	m_pLyr		);

	return LC_OK;
}


INT	CMain::FrameMove()
{
#if defined(_WIN32)
	LcAux_Sleep(10);
#endif

	static INT c=0;
	++c;

	if(c>20*60*120)
	//if(c>8*60*2)
	{
		printf("Game Process Terminated\n");
		return LC_EFAIL;
	}


	static int n = 0;
	++n;

	if(n>5)
	{
		n = 0;
	}

	// Input Update
	m_pInput->Update();

	const BYTE*	pKey = m_pInput->KeyMap();

	if(pKey[LCIK_ESCAPE])
		return LC_EFAIL;



	m_pTds0	->FrameMove();
	m_pTds1	->FrameMove();


	return LC_OK;
}


INT	CMain::Render()
{
	m_pDev->BeginScene();

	m_pDev->Clear(LC_CLEAR_COLOR_BUFFER | LC_CLEAR_DEPTH_BUFFER);

	m_pDev->SetRenderState(LC_RS_CULL_FACE, LC_ST_DISABLE);
	m_pDev->SetRenderState(LC_RS_LIGHTING, LC_ST_DISABLE);

	m_pXYZ->Render();

	m_pLyr->Begin();
		
		m_pTds0	->Render();
		m_pTds1	->Render();

	m_pLyr->End();

	m_pDev->EndScene();

	return LC_OK;
}

