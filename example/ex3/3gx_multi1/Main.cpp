// Implementation of the CMain class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


#define MEDIA_DIR	"../../media/"


CMain::CMain()
{
	m_pInput	= NULL;
	m_pTex0		= NULL;
	m_pTex1		= NULL;
}


INT	CMain::Init()
{
	TLC_ARGS	args;
	INT	hr = 0;

	// Input »ý¼º
	if(LC_FAILED(LcxEnt_CreateInput(NULL, &m_pInput)))
		return LC_EFAIL;



	MAKE_ARG1(args, (char*)MEDIA_DIR"tex/multi_tex0.tga");
	hr = LcDev_CreateTextureFromFile(NULL, &m_pTex0, &args);
	if(LC_FAILED(hr))
		return LC_EFAIL;

	MAKE_ARG1(args, (char*)MEDIA_DIR"tex/multi_tex1.tga");
	hr = LcDev_CreateTextureFromFile(NULL, &m_pTex1, &args);
	if(LC_FAILED(hr))
		return LC_EFAIL;


	char* attlist[] = {"at_pos", "at_tx0", NULL};
	MAKE_ARG3(args, (char*)"./sl_vs.glsl", (char*)"./sl_fs.glsl", (char**)attlist);
	hr = LcDev_CreateEffectFromTxtFile(NULL, &m_pEft, m_pDev, &args);
	if(LC_FAILED(hr))
		return LC_EFAIL;


	return LC_OK;
}


int	CMain::Destroy()
{
	SAFE_RELEASE(	m_pInput	);
	SAFE_RELEASE(	m_pTex0		);
	SAFE_RELEASE(	m_pTex1		);
	SAFE_RELEASE(	m_pEft		);

	return LC_OK;
}


int	CMain::FrameMove()
{
#if defined(_WIN32)
	LcAux_Sleep(10);
#endif

	static INT c=0;
	++c;

	//	if(c>20*60*20)
	if(c>8*60*20)
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



	return LC_OK;
}



int	CMain::Render()
{
	INT hr = 0;

	m_pDev->BeginScene();

	UINT	dColor = 0xFF006699;
	m_pDev->SetRenderState(LC_RS_CLEAR_COLOR, dColor);
	m_pDev->Clear(LC_CLEAR_COLOR_BUFFER | LC_CLEAR_DEPTH_BUFFER);

	m_pDev->SetRenderState(LC_RS_CULL_FACE, LC_ST_DISABLE);
	m_pDev->SetRenderState(LC_RS_LIGHTING , LC_ST_DISABLE);
	m_pDev->SetRenderState(LC_RS_CULL_FACE, LC_ST_DISABLE);


	m_pDev->SetRenderState(LC_RS_BLEND, LC_ST_ENABLE, LC_ST_SRC_ALPHA, LC_ST_SRC_INV_ALPHA);


	// Setup Vertex Data
	LCXVECTOR2	Pos[4];
	LCXVECTOR2	Tex[4];

	Pos[0] = LCXVECTOR2(-0.5F, -0.5F);
	Pos[1] = LCXVECTOR2( 0.5F, -0.5F);
	Pos[2] = LCXVECTOR2( 0.5F,  0.5F);
	Pos[3] = LCXVECTOR2(-0.5F,  0.5F);

	Tex[0] = LCXVECTOR2(0.0F, 0.0F);
	Tex[1] = LCXVECTOR2(1.0F, 0.0F);
	Tex[2] = LCXVECTOR2(1.0F, 1.0F);
	Tex[3] = LCXVECTOR2(0.0F, 1.0F);


	m_pEft->Begin();

	hr = m_pEft->Texture("us_t0", 0, m_pTex0);
	hr = m_pEft->Texture("us_t1", 1, m_pTex1);

	m_pDev->SetStream(0, Pos, LC_FMT_FLOAT, 2, 0, 0);
	m_pDev->SetStream(1, Tex, LC_FMT_FLOAT, 2, 0, 0);
	m_pDev->DrawPrimitive(LC_PT_TRIANGLE_FAN , 0, 4);

	m_pEft->End();


	m_pDev->SetStream (0, NULL);
	m_pDev->SetStream (1, NULL);
	m_pDev->SetTexture(0, NULL);
	m_pDev->SetTexture(1, NULL);

	return LC_OK;
}


