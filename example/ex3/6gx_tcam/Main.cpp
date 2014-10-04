// Implementation of the CMain class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


#define MEDIA_DIR	"../../media/"


CMain::CMain()
{
	m_pLyr		= NULL;

	m_pInput	= NULL;
	m_pCam	= NULL;
	m_pXYZ		= NULL;
	m_pGrid		= NULL;

	m_pTdm		= NULL;
	m_mtWld.Identity();
}


INT	CMain::Init()
{
	TLC_ARGS	args;
	INT			hr = LC_OK;

	// Create Sprite Layer
	MAKE_ARG1(args, (UINT)LC_OBJ_MODEL2D);
	if(LC_FAILED(LcDev_CreateSprite(NULL, &m_pLyr, &args)))
		return LC_EFAIL;


	// Input 持失
	if(LC_FAILED(LcxEnt_CreateInput(NULL, &m_pInput)))
		return LC_EFAIL;


	// Camera 持失
	TXDSC_CAMERA	tCam =
	{
		LCX_CAM_FIRST,
		LCXToRadian(45.0F),
		1.0F,
		5000.0F,

		FLOAT(m_nScnW),
		FLOAT(m_nScnH),
	
		LCXVECTOR3(0, -100, 0),
		LCXVECTOR3(0,    0, 0),
		LCXVECTOR3(0,    0, 1),
	};
	MAKE_ARG1(args, (LC_HANDLE)&tCam);
	if(LC_FAILED(LcxEnt_CreateCamera(NULL, &m_pCam, &args)))
		return LC_EFAIL;



	if(LC_FAILED(LcxEnt_CreateEntity(LCXCMD_ENTITY_AXIS, &m_pXYZ)))
		return LC_EFAIL;

	if(LC_FAILED(LcxEnt_CreateEntity(LCXCMD_ENTITY_GRID, &m_pGrid)))
		return LC_EFAIL;



	m_pTdm = Setup2dModel((char*)(MEDIA_DIR"model2d/boss01.tdt"));
	if(NULL == m_pTdm)
		return LC_EFAIL;



	LCXVECTOR2	vcT(0.0F, 0.F);
	hr = m_pTdm->SetAttrib(LCXM_ANIMATION, "move");
	hr = m_pTdm->Position(&vcT);


	return LC_OK;
}



INT	CMain::Destroy()
{
	ItTex _F = m_vTex.begin();
	ItTex _L = m_vTex.end();

	for(; _F != _L; ++_F )
	{
		PLC_TEXTURE pTex = (*_F).second;

		if(pTex)
			pTex->Release();
	}

	m_vTex.clear();

	m_pTdm->Release();


	SAFE_RELEASE(	m_pXYZ		);
	SAFE_RELEASE(	m_pGrid		);
	SAFE_RELEASE(	m_pCam		);
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
		printf("FPS: %3.f\n", m_TimeFPS);
		n = 0;
	}

	// Input Update
	m_pInput->Update();

	const BYTE*	pKey = m_pInput->KeyMap();

	if(pKey[LCIK_ESCAPE])
		return LC_EFAIL;



	// Move, Rotation Speed
	FLOAT speed = (FLOAT)this->GetElapsedTime();
	speed *=0.1f;


	// Translation
	if(pKey[LCIK_DOWN])
		m_mtWld._42 -=speed;

	if(pKey[LCIK_UP])
		m_mtWld._42 += speed;

	if(pKey[LCIK_RIGHT])
		m_mtWld._41 += speed;

	if(pKey[LCIK_LEFT])
		m_mtWld._41 -= speed;


	m_pCam->Update();


	m_pTdm->FrameMove();


	return LC_OK;
}


INT	CMain::Render()
{
	m_pCam->TransformViw();
	m_pCam->TransformPrj();

	m_pDev->BeginScene();

	m_pDev->Clear(LC_CLEAR_COLOR_BUFFER | LC_CLEAR_DEPTH_BUFFER);

	//m_pCam->TransformPrj();
	//m_pCam->TransformViw();


	m_pDev->SetRenderState(LC_RS_CULL_FACE, LC_ST_DISABLE);
	m_pDev->SetRenderState(LC_RS_LIGHTING, LC_ST_DISABLE);


	m_pXYZ->Render();
	m_pGrid->Render();



	// 2D Model Rendering
	m_pLyr->Begin();
	{
		m_pLyr->SetTransform(LC_TM_WORLD_EXT, &m_mtWld);

		LCXVECTOR2	vcPos(50, 50);
		m_pTdm->Position(&vcPos);
		m_pTdm->Render();

	}
	m_pLyr->End();



	m_pDev->EndScene();

	return LC_OK;
}



PLC_TEXTURE CMain::FindTex(char* sName)
{
	TLC_ARGS	args;
	PLC_TEXTURE	pTex = NULL;

	ItTex it = m_vTex.find( sName );

	if( it == m_vTex.end() )
	{
		char sFile	[LC_MAX_PATH ]={0};
		char drive	[LC_MAX_DRIVE]={0};
		char dir	[LC_MAX_DIR  ]={0};
		char fname	[LC_MAX_FNAME]={0};
		char ext	[LC_MAX_EXT  ]={0};

		LcStr_SplitPath( sName, drive, dir, fname, ext );

		sprintf(sFile, MEDIA_DIR"model2d/%s%s", fname, ext);

		MAKE_ARG4(args, sFile, (UINT)0, (UINT)0, (INT)1);
		if(LC_FAILED(LcDev_CreateTextureFromFile(NULL, &pTex, &args)))
		{
			printf("Cannot Read Model Texture: %s\n", sFile);
			return NULL;
		}

		if(pTex)
			m_vTex.insert(ItTex::value_type(sName, pTex) );
	}

	else
	{
		pTex = (*it).second;
	}


	return pTex;
}



PLCX_TDM CMain::Setup2dModel(char* sModel)
{
	TLC_ARGS		args;
	INT				hr = LC_OK;

	INT				nTexList = 0;
	INT				i = 0;

	char**			s = NULL;
	PLC_TEXTURE*	t = NULL;
	PLCX_TDM		pTdm = NULL;

	MAKE_ARG2(args, sModel, (LC_HANDLE)m_pLyr);
	hr = LcxEnt_CreateTdm(NULL, &pTdm, &args);

	if(LC_FAILED(hr))
		return NULL;


	nTexList = 0;
	pTdm->GetAttrib(LCXM_TEXTURE_LIST_NUMBER, &nTexList);


	s = (char**)malloc( (nTexList+1) * sizeof(char*) );
	t = (PLC_TEXTURE*)malloc((nTexList+1) * sizeof(PLC_TEXTURE*) );
	memset(s, 0, (nTexList+1) * sizeof(char*));
	memset(t, 0, (nTexList+1) * sizeof(PLC_TEXTURE*));


	pTdm->GetAttrib(LCXM_TEXTURE_LIST_NAME, &s);
	for(i=0; i<nTexList; ++i)
	{
		//1. Find Texture
		char*	sName = s[i];
		PLC_TEXTURE pTex = this->FindTex(sName);

		if(NULL == pTex)
			return NULL;

		t[i] = pTex;
	}

	pTdm->SetAttrib(LCXM_TEXTURE_LIST_POINTER, t);

	free(s);
	free(t);

	return pTdm;
}


