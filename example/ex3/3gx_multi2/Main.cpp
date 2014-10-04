// Implementation of the CMain class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


#define MEDIA_DIR	"../../media/"


CMain::CMain()
{
	m_pInput	= NULL;
	m_pCam		= NULL;
	m_pXYZ		= NULL;
	m_pGrid		= NULL;

	m_pTex0		= NULL;
	m_pTex1		= NULL;
}


INT	CMain::Init()
{
	TLC_ARGS	args;
	INT	hr = 0;

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

		LCXVECTOR3(0, -38, 0),
		LCXVECTOR3(0,   0,  0),
		LCXVECTOR3(0,   0,  1),
	};

	MAKE_ARG1(args, (LC_HANDLE)&tCam);
	if(LC_FAILED(LcxEnt_CreateCamera(NULL, &m_pCam, &args)))
		return LC_EFAIL;


	if(LC_FAILED(LcxEnt_CreateEntity(LCXCMD_ENTITY_AXIS, &m_pXYZ)))
		return LC_EFAIL;

	if(LC_FAILED(LcxEnt_CreateEntity(LCXCMD_ENTITY_GRID, &m_pGrid)))
		return LC_EFAIL;

	MAKE_ARG4(args, (char*)MEDIA_DIR"tex/stones.png", (UINT)0, (UINT)0, (INT)1);
	hr = LcDev_CreateTextureFromFile(NULL, &m_pTex0, &args);
	if(LC_FAILED(hr))
		return LC_EFAIL;

	MAKE_ARG4(args, (char*)MEDIA_DIR"tex/env0.png", (UINT)0, (UINT)0, (INT)1);
	hr = LcDev_CreateTextureFromFile(NULL, &m_pTex1, &args);
	if(LC_FAILED(hr))
		return LC_EFAIL;

	return LC_OK;
}


INT	CMain::Destroy()
{
	SAFE_RELEASE(	m_pTex0		);
	SAFE_RELEASE(	m_pTex1		);

	SAFE_RELEASE(	m_pXYZ		);
	SAFE_RELEASE(	m_pGrid		);
	SAFE_RELEASE(	m_pCam		);
	SAFE_RELEASE(	m_pInput	);

	return LC_OK;
}

INT	CMain::FrameMove()
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


	m_pCam->Update();


	return LC_OK;
}




INT	CMain::Render()
{
	m_pDev->BeginScene();

	UINT	dColor = 0xFF006699;
	m_pDev->SetRenderState(LC_RS_CLEAR_COLOR, dColor);
	m_pDev->Clear(LC_CLEAR_COLOR_BUFFER | LC_CLEAR_DEPTH_BUFFER);

	m_pDev->SetRenderState(LC_RS_CULL_FACE, LC_ST_DISABLE);

	m_pCam->TransformViw();
	m_pCam->TransformPrj();

//	m_pXYZ->Render();
//	m_pGrid->Render();



	// Color
	LCXCOLOR	pColor[3][3];

	pColor[0][0] = LCXCOLOR(1, 0, 0, 1);	pColor[0][1] = LCXCOLOR(0, 1, 0, 1);	pColor[0][2] = LCXCOLOR(0, 1, 1, 1);
	pColor[1][0] = LCXCOLOR(0, 1, 0, 1);	pColor[1][1] = LCXCOLOR(1, 1, 1, 1);	pColor[1][2] = LCXCOLOR(1, 1, 1, 1);
	pColor[2][0] = LCXCOLOR(1, 0, 1, 1);	pColor[2][1] = LCXCOLOR(1, 1, 0, 1);	pColor[2][2] = LCXCOLOR(1, 0, 0, 1);


	INT	nTexOp[3][3][2]=
	{
		{	{ LC_TS_TOP_ONE , LC_TS_TOP_NONE},	{ LC_TS_TOP_NONE, LC_TS_TOP_ONE },	{ LC_TS_TOP_MUL , LC_TS_TOP_NONE},	},
		{	{ LC_TS_TOP_NONE, LC_TS_TOP_MUL },	{ LC_TS_TOP_SUB , LC_TS_TOP_NONE},	{ LC_TS_TOP_NONE, LC_TS_TOP_SUB },	},
		{	{ LC_TS_TOP_MUL , LC_TS_TOP_MUL },	{ LC_TS_TOP_MUL , LC_TS_TOP_SUB },	{ LC_TS_TOP_ONE , LC_TS_TOP_ADS },	},
	};

	// Set Vertex Data
	VtxUV1		pVtx[4];

	pVtx[0].t = LCXVECTOR2(0.0F, 0.0F);
	pVtx[1].t = LCXVECTOR2(1.0F, 0.0F);
	pVtx[2].t = LCXVECTOR2(1.0F, 1.0F);
	pVtx[3].t = LCXVECTOR2(0.0F, 1.0F);

	pVtx[0].p = LCXVECTOR3(-30.0F, 0.0F, -20.0F);
	pVtx[1].p = LCXVECTOR3( 30.0F, 0.0F, -20.0F);
	pVtx[2].p = LCXVECTOR3( 30.0F, 0.0F,  20.0F);
	pVtx[3].p = LCXVECTOR3(-30.0F, 0.0F,  20.0F);



	m_pDev->SetRenderState(LC_RS_FUNC_ALPHA, LC_TRUE, 0, 0);


	m_pDev->SetTextureAddressS (0, LC_TS_REPEAT);
	m_pDev->SetTextureAddressT (0, LC_TS_REPEAT);
	m_pDev->SetTextureFilterMin(0, LC_TS_LINEAR);
	m_pDev->SetTextureFilterMag(0, LC_TS_LINEAR);

	m_pDev->SetTextureAddressS (1, LC_TS_REPEAT);
	m_pDev->SetTextureAddressT (1, LC_TS_REPEAT);
	m_pDev->SetTextureFilterMin(1, LC_TS_LINEAR);
	m_pDev->SetTextureFilterMag(1, LC_TS_LINEAR);
	//m_pDev->SetTextureStageOp(0, LC_TS_TOP_ONE);
	m_pDev->SetTexture(0, m_pTex0);
	m_pDev->SetTexture(1, m_pTex1);
	m_pDev->SetFVF(VtxUV1::FVF);
//	m_pDev->DrawPrimitiveUP(LC_PT_TRIANGLE_FAN, 0, 4, pVtx, sizeof(VtxUV1) );

	for(int k=0; k<3; ++k)
	{
		for(int i=0; i<3; ++i)
		{
			float	x = (i - 1.5f)*17.F;
			float	z = (0.5F-k)*10.0F;

			pVtx[0].p = LCXVECTOR3(      x, 0.0F, z    );
			pVtx[1].p = LCXVECTOR3( x+17.F, 0.0F, z    );
			pVtx[2].p = LCXVECTOR3( x+17.F, 0.0F, z+10.F);
			pVtx[3].p = LCXVECTOR3(      x, 0.0F, z+10.F);

			m_pDev->SetTextureStageOp (0, nTexOp[k][i][0]);
			m_pDev->SetTextureStageOp (1, nTexOp[k][i][1]);

			m_pDev->SetTcolor(&pColor[k][i]);
			m_pDev->DrawPrimitiveUP(LC_PT_TRIANGLE_FAN, 0, 4, pVtx, sizeof(VtxUV1) );
		}
	}



	m_pDev->SetTexture(1, NULL);
	m_pDev->SetTexture(0, NULL);

	m_pDev->SetTcolor(NULL);

	m_pDev->EndScene();

	return LC_OK;
}





