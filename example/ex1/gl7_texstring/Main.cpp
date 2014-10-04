// Implementation of the CMain class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"

static char g_CurrentDir[260]={0};


#define MEDIA_DIR	"../../media/"


CMain::CMain()
{
	LcAux_GetCurrentDir( g_CurrentDir, 260);

	m_pEft = NULL;

	m_pStr1 = NULL;
	m_pStr2 = NULL;
	m_pStr3 = NULL;
}


int	CMain::Init()
{
	int hr =0;

	LcAux_SetCurrentDir( g_CurrentDir);


	{
		TLC_ARGS args;
		char* attlist[] = {"at_pos", NULL};
		char* glslist[] = {MEDIA_DIR"shader/14sl_vs.glsl", MEDIA_DIR"shader/14sl_fs.glsl", NULL};

		MAKE_ARG3(args, glslist[0], glslist[1], (char**)attlist);
		hr = LcDev_CreateEffectFromTxtFile(NULL, &m_pEft, m_pDev, &args);
		if(LC_FAILED(hr))
			return LC_EFAIL;


		m_pEft->Owner(this);
	}


	{
		CTexString*	pStr;
		pStr = new CTexString;

		if(LC_FAILED( hr = pStr->Create( (char*)MEDIA_DIR"tex/font256x128.tga", 12)))
		{
			delete pStr;
			return LC_EFAIL;
		}

		pStr->Effect(m_pEft);
		m_pStr1 = pStr;
	}

	{
		CTexString*	pStr;
		pStr = new CTexString;

		if(LC_FAILED( hr = pStr->Create( (char*)MEDIA_DIR"tex/font256x128.tga", 14)))
		{
			delete pStr;
			return LC_EFAIL;
		}

		pStr->Effect(m_pEft);
		m_pStr2 = pStr;
	}

	{
		CTexString*	pStr;
		pStr = new CTexString;

		if(LC_FAILED( hr = pStr->Create( (char*)MEDIA_DIR"tex/font256x128.tga", 18)))
		{
			delete pStr;
			return LC_EFAIL;
		}

		pStr->Effect(m_pEft);
		m_pStr3 = pStr;
	}


	return LC_OK;
}


int	CMain::Destroy()
{
	SAFE_DELETE(	m_pStr1	);
	SAFE_DELETE(	m_pStr2	);
	SAFE_DELETE(	m_pStr3	);

	m_pEft->Owner(NULL);
	SAFE_RELEASE(	m_pEft	);

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



	m_pStr1->String((char*)"Hello world !!!");
	m_pStr1->Position(10, 50);
	m_pStr1->Color(1, 1, 0, 1);

	m_pStr2->String((char*)"This is a sample texture string");
	m_pStr2->Position(15, 80);
	m_pStr2->Color(1, 0, 1, 1);

	m_pStr3->String((char*)"Using font256x128.tga");
	m_pStr3->Position(20, 110);
	m_pStr3->Color(0, 1, 1, 1);


	return LC_OK;
}


int	CMain::Render()
{
	// Setting Rendering pipeline
	glDisable( GL_DEPTH_TEST);
	glDisable( GL_CULL_FACE );

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);


	// Clear Color buffer and Depth Buffer.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_pStr1->DrawTxt();
	m_pStr2->DrawTxt();
	m_pStr3->DrawTxt();

	return LC_OK;
}


