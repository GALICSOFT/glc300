// Implementation of the CMain class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"

static char g_CurrentDir[260]={0};


#define MEDIA_DIR	"../../media/"


CMain::CMain()
{
	LcAux_GetCurrentDir( g_CurrentDir, 260);

	m_pEftTxt  = NULL;
	m_pEftPtc[0] = NULL;
	m_pEftPtc[1] = NULL;

	m_pPtc	= NULL;
	m_pStr	= NULL;
}


int	CMain::Init()
{
	int hr =0;

	LcAux_SetCurrentDir( g_CurrentDir);


	{
		TLC_ARGS args;
		char* attlist[] = {"at_pos", NULL};
		char* glslist[] = {MEDIA_DIR"shader/slvs_txt.glsl", MEDIA_DIR"shader/slfs_txt.glsl", NULL};

		MAKE_ARG3(args, glslist[0], glslist[1], (char**)attlist);
		hr = LcDev_CreateEffectFromTxtFile(NULL, &m_pEftTxt, m_pDev, &args);
		if(LC_FAILED(hr))
			return LC_EFAIL;


		m_pEftTxt->Owner(this);
	}




	m_pStr = new CTexString;
	if(LC_FAILED(m_pStr->Create( (char*)MEDIA_DIR"tex/font256x128.tga", 14)))
	{
		delete m_pStr;
		return LC_EFAIL;
	}

	m_pStr->Effect(m_pEftTxt);


	

	{
		TLC_ARGS args;
		char* attlist[] = {"at_pos", "at_dif", "at_psize", NULL};
		char* glslist[] = {MEDIA_DIR"shader/slvs_ptc1.glsl", MEDIA_DIR"shader/slfs_ptc1.glsl", NULL};

		MAKE_ARG3(args, glslist[0], glslist[1], (char**)attlist);
		hr = LcDev_CreateEffectFromTxtFile(NULL, &m_pEftPtc[0], m_pDev, &args);
		if(LC_FAILED(hr))
			return LC_EFAIL;

		m_pEftPtc[0]->Owner(this);
	}

	{
		TLC_ARGS args;
		char* attlist[] = {"at_pos", "at_dif", "at_tex", NULL};
		char* glslist[] = {MEDIA_DIR"shader/slvs_ptc2.glsl", MEDIA_DIR"shader/slfs_ptc2.glsl", NULL};

		MAKE_ARG3(args, glslist[0], glslist[1], (char**)attlist);
		hr = LcDev_CreateEffectFromTxtFile(NULL, &m_pEftPtc[1], m_pDev, &args);
		if(LC_FAILED(hr))
			return LC_EFAIL;

		m_pEftPtc[1]->Owner(this);
	}




	m_pPtc = new CParticle;
	if(LC_FAILED(m_pPtc->Create( (char*)MEDIA_DIR"tex/ball2.png", 120)))
	{
		delete m_pPtc;
		return LC_EFAIL;
	}

	m_pPtc->SetEffect(m_pEftPtc, 2);


	return LC_OK;
}


int	CMain::Destroy()
{
	SAFE_DELETE(	m_pPtc	);
	SAFE_DELETE(	m_pStr	);

	m_pEftTxt->Owner(NULL);
	SAFE_RELEASE(	m_pEftTxt	);


	for(int n=0; n<2; ++n)
	{
		m_pEftPtc[n]->Owner(NULL);
		SAFE_RELEASE(	m_pEftPtc[n]	);
	}



	return LC_OK;
}


int	CMain::FrameMove()
{
#if defined(_WIN32)
	LcAux_Sleep(10);
#endif


	static int c=0;
	++c;

	//	if(c>20*60*20)
	if(c>8*60*2)
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



	m_pPtc->FrameMove();


	m_pStr->String("Point Sprite Example");
	m_pStr->Position(10, 10);
	m_pStr->Color(1, 1, 0, 1);

	return LC_OK;
}


int	CMain::Render()
{
	// Setting Rendering pipeline
	glDisable( GL_DEPTH_TEST);
	glDisable( GL_CULL_FACE );

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//glClearColor(0.0f, 0.4f, 0.6f, 0.0f);

	// Clear Color buffer and Depth Buffer.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	m_pPtc->Render();
	m_pStr->DrawTxt();


	return LC_OK;
}





