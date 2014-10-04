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

	m_pTex		= NULL;

	m_pEps2d1	= NULL;
	m_pEps2d2	= NULL;
	m_pEps2d3	= NULL;
	m_pEps2d4	= NULL;
	m_pEps3d1	= NULL;
	m_pEps3d2	= NULL;

	m_pEta0		= NULL;
	m_pEta1		= NULL;
	m_pEtb0		= NULL;
	m_pEtb1		= NULL;
}


INT	CMain::Init()
{
	TLC_ARGS	args;
	INT			hr = LC_OK;


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

		LCXVECTOR3(140, 90,800),
		LCXVECTOR3( 90, 40,  0),
		LCXVECTOR3( 0,   0,  1),
	};
	MAKE_ARG1(args, (LC_HANDLE)&tCam);
	if(LC_FAILED(LcxEnt_CreateCamera(NULL, &m_pCam, &args)))
		return LC_EFAIL;




	if(LC_FAILED(LcxEnt_CreateEntity(LCXCMD_ENTITY_AXIS, &m_pXYZ)))
		return LC_EFAIL;

	if(LC_FAILED(LcxEnt_CreateEntity(LCXCMD_ENTITY_GRID, &m_pGrid)))
		return LC_EFAIL;



	{
		//INT			nTexW  = 128;
		//COLOR32*	pxlDst = (COLOR32*)LcMem_Alloc(nTexW*nTexW* sizeof(COLOR32));
	
		//TDSC_IMAGE tex_inf=
		//{
		//	(UINT)LC_SRC_T_BUF	,	//	img_s;
		//	(UINT)LC_UNKNOWN	,	//	img_k;
		//	(UINT)LC_IMG_UBYTE	,	//	img_t;	// GL_UNSIGNED_BYTE
		//	(UINT)LC_FMT_RGBA	,	//	img_f;	// GL_RGBA
		//	(INT )nTexW			,	//	img_w;
		//	(INT )nTexW			,	//	img_h;
		//	(INT )4				,	//	img_d;
		//	(UINT)0x00000000	,	//	img_c;
		//	(BYTE*)pxlDst		,	//	img_p;
		//};

		//INT	nMip  = 0;
		//FLOAT	alpha = 0.0F;
		//FLOAT	hTexW = nTexW/2.0F;

		//for(int y=0; y<nTexW; ++y)
		//{
		//	for(int x=0; x<nTexW; ++x)
		//	{
		//		alpha  = (hTexW - x) * (hTexW - x) + (hTexW - y) * (hTexW - y);
		//		alpha  = pow(alpha, 0.6F );

		//		alpha *= 4.00F;
		//		alpha /= hTexW;

		//		if(0.0F == alpha)
		//			alpha = 1.0F;
		//		else
		//			alpha  = 1.0F/alpha;

		//		pxlDst[y*nTexW + x] = LCXCOLOR(alpha, alpha, alpha, alpha);
		//	}
		//}
		//MAKE_ARG4(args, (char*)"default particle ball", (LC_HANDLE)&tex_inf, nMip, (INT)0);
		//hr = LcDev_CreateTextureFromBuffer(NULL, &m_pTex, &args);
		//SAFE_FREE( pxlDst);

		MAKE_ARG1(args, (char*)MEDIA_DIR"tex/ball2.png");
		LcDev_CreateTextureFromFile(NULL, &m_pTex, &args);
	}


	// create particle effect
	{
		INT ScnW, ScnH;
		LcVar_WindowSize(&ScnW, &ScnH);

		TXDSC_EPS inf;
		INT	nPartNum = 200;

		inf.prt_num  = nPartNum;
		inf.prt_clzz = LCXE_PARTICLE_2D;
		inf.prt_rtype= LCXE_REN_QUAD;
		inf.prt_strd = sizeof(MyEft2D1);
		inf.prt_lst  = new MyEft2D1[nPartNum];								// it will be removed automatically when it will be bound with Particle Effect.;
		inf.prt_tex  = m_pTex;												// Texture Pointer

		inf.rc_bnd   = LC_FLOAT8 (0.0F,0.0F, FLOAT(ScnW), FLOAT(ScnH) );	// boundary region
		inf.tm_pos   = LCXVECTOR3(100, 620 ,0);								// Initial position
		inf.it_dif	 = LCXCOLOR  (1, 0.5F, 0, 1);							// Initial COLOR
		inf.it_mag   = LCXVECTOR2(4.0F, 4.0F);

		MAKE_ARG1(args, &inf);
		hr = LcxEnt_CreateParticle(NULL, &m_pEps2d1, &args);
		if(LC_FAILED(hr))
			return hr;


		inf.prt_num  = nPartNum;
		inf.prt_clzz = LCXE_PARTICLE_2D;
		inf.prt_rtype= LCXE_REN_QUAD;
		inf.prt_strd = sizeof(MyEft2D2);
		inf.prt_lst  = new MyEft2D2[nPartNum];
		inf.prt_tex  = m_pTex;

		inf.rc_bnd   = LC_FLOAT8 (0.0F,0.0F, FLOAT(ScnW), FLOAT(ScnH) );
		inf.tm_pos   = LCXVECTOR3(250, 620 ,0);
		inf.it_mag   = LCXVECTOR2(2.0F, 2.0F);

		MAKE_ARG2(args, &inf, m_pSpt);
		hr = LcxEnt_CreateParticle(NULL, &m_pEps2d2, &args);
		if(LC_FAILED(hr))
			return hr;


		inf.prt_num  = nPartNum;
		inf.prt_clzz = LCXE_PARTICLE_2D;
		inf.prt_rtype= LCXE_REN_QUAD;
		inf.prt_strd = sizeof(MyEft2D3);
		inf.prt_lst  = new MyEft2D3[nPartNum];
		inf.prt_tex  = m_pTex;

		inf.rc_bnd   = LC_FLOAT8 (0.0F,0.0F, FLOAT(ScnW), FLOAT(ScnH) );
		inf.it_mag   = LCXVECTOR2(2.0F, 2.0F);

		MAKE_ARG1(args, &inf);
		hr = LcxEnt_CreateParticle(NULL, &m_pEps2d3, &args);
		if(LC_FAILED(hr))
			return hr;



		inf.prt_num  = nPartNum;
		inf.prt_clzz = LCXE_PARTICLE_2D;
		inf.prt_rtype= LCXE_REN_QUAD;
		inf.prt_strd = sizeof(MyEft2D1);
		inf.prt_lst  = new MyEft2D1[nPartNum];
		inf.prt_tex  = m_pTex;

		inf.rc_bnd   = LC_FLOAT8 (0.0F,0.0F, FLOAT(ScnW), FLOAT(ScnH) );
		inf.tm_pos   = LCXVECTOR3(400, 620 ,0);
		inf.it_dif	 = LCXCOLOR  (0, 0.5F, 1, 1);
		inf.it_mag   = LCXVECTOR2(2.0F, 2.0F);

		MAKE_ARG2(args, &inf, m_pSpt);
		hr = LcxEnt_CreateParticle(NULL, &m_pEps2d4, &args);
		if(LC_FAILED(hr))
			return hr;



		//++5++++1+++++++++2+++++++++3+++++++++

		inf.prt_num  = nPartNum;
		inf.prt_clzz = LCXE_PARTICLE_3D;
		inf.prt_rtype= LCXE_REN_QUAD;
		inf.prt_strd = sizeof(MyEft3D1);
		inf.prt_lst  = new MyEft3D1[nPartNum];								// it will be removed automatically when it will be bound with Particle Effect.;
		inf.prt_tex  = m_pTex;												// Texture Pointer

		inf.rc_bnd   = LC_FLOAT8 (0.0F,0.0F, FLOAT(ScnW), FLOAT(ScnH) );	// boundary region
		inf.tm_pos   = LCXVECTOR3(-32, 0 ,0);								// Initial position
		inf.it_dif	 = LCXCOLOR  (1, 0.5F, 0, 1);							// Initial COLOR
		inf.it_mag   = LCXVECTOR2(6.0F, 6.0F);

		MAKE_ARG1(args, &inf);
		hr = LcxEnt_CreateParticle(NULL, &m_pEps3d1, &args);
		if(LC_FAILED(hr))
			return hr;


		inf.prt_num  = nPartNum;
		inf.prt_clzz = LCXE_PARTICLE_3D;
		inf.prt_rtype= LCXE_REN_QUAD;
		inf.prt_strd = sizeof(MyEft3D2);
		inf.prt_lst  = new MyEft3D2[nPartNum];
		inf.prt_tex  = m_pTex;

		inf.rc_bnd   = LC_FLOAT8 (0.0F,0.0F, FLOAT(ScnW), FLOAT(ScnH) );
		inf.tm_pos   = LCXVECTOR3(32, 0 ,0);
		inf.it_mag   = LCXVECTOR2(4.0F, 4.0F);

		MAKE_ARG2(args, &inf, m_pSpt);
		hr = LcxEnt_CreateParticle(NULL, &m_pEps3d2, &args);
		if(LC_FAILED(hr))
			return hr;
	}


	MAKE_ARG1(args, (char*)MEDIA_DIR"effect/attack.xml");
	LcxEnt_CreateEta(NULL, &m_pEta0, &args);


	LCXVECTOR3	pos(100, 10, 10);
	LCXVECTOR3	scl(1.0F, 0.5F, 1.0F);

	m_pEta0->Position(&pos);
	m_pEta0->Scaling(&scl);


	MAKE_ARG1(args, (char*)MEDIA_DIR"effect/attack.xml");
	LcxEnt_CreateEta(NULL, &m_pEta1, &args);


	pos = LCXVECTOR3(-200, 10, 10);
	scl = LCXVECTOR3(3.F, 3.0F, 3.0F);

	m_pEta1->Position(&pos);
	m_pEta1->Scaling(&scl);
	

	{
		MAKE_ARG1(args, (char*)MEDIA_DIR"effect/char_attack.etb");
		LcxEnt_CreateEtb(NULL, &m_pEtb0, &args);


		pos = LCXVECTOR3(-20, 10, 0);
		m_pEtb0->Position(&pos);
		m_pEtb0->Scaling(&scl);
	}

	{
		MAKE_ARG1(args, (char*)MEDIA_DIR"effect/char_attack.etb");
		LcxEnt_CreateEtb(NULL, &m_pEtb1, &args);

		pos = LCXVECTOR3( 20, 10, 0);
		m_pEtb1->Position(&pos);
	}
	
	return LC_OK;
}



INT	CMain::Destroy()
{
	SAFE_RELEASE(	m_pEta0	);
	SAFE_RELEASE(	m_pEta1	);

	SAFE_RELEASE(	m_pEtb0	);
	SAFE_RELEASE(	m_pEtb1	);

	SAFE_RELEASE(	m_pEps2d1	);
	SAFE_RELEASE(	m_pEps2d2	);
	SAFE_RELEASE(	m_pEps2d3	);
	SAFE_RELEASE(	m_pEps2d4	);
	SAFE_RELEASE(	m_pEps3d1	);
	SAFE_RELEASE(	m_pEps3d2	);

	SAFE_RELEASE(	m_pTex		);

	SAFE_RELEASE(	m_pXYZ		);
	SAFE_RELEASE(	m_pGrid		);
	SAFE_RELEASE(	m_pCam		);
	SAFE_RELEASE(	m_pInput	);

	return LC_OK;
}


INT	CMain::FrameMove()
{
#if defined(_WIN32)
	LcAux_Sleep(5);
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
		//printf("FPS: %3.f\n", m_TimeFPS);
		n = 0;
	}



	// Input Update
	m_pInput->Update();

	const BYTE*  pKey = m_pInput->KeyMap();
	const BYTE*  pMts = m_pInput->MtsMap();
	if(pKey[LCIK_ESCAPE])
		return LC_EFAIL;



	// Move, Rotation Speed
	FLOAT speed = (FLOAT)this->GetElapsedTime();
	speed *=0.1f;


	// Translation
	if(pKey[LCIK_W])
		m_pCam->MoveForward(+speed);

	if(pKey[LCIK_S])
		m_pCam->MoveForward(-speed);

	if(pKey[LCIK_A])
		m_pCam->MoveSideward(-speed);

	if(pKey[LCIK_D])
		m_pCam->MoveSideward(+speed);


	// Rotation
	float fAngle_degree = 2.0f;

	if(pKey[LCIK_LEFT])
		m_pCam->RotateYaw(fAngle_degree, speed);

	if(pKey[LCIK_RIGHT])
		m_pCam->RotateYaw(fAngle_degree, -speed);

	if(pKey[LCIK_UP])
		m_pCam->RotatePitch(fAngle_degree, speed);

	if(pKey[LCIK_DOWN])
		m_pCam->RotatePitch(fAngle_degree, -speed);


	m_pCam->Update();


	if(pMts[0] && m_pEps2d4)
	{
		LCXVECTOR2	MtsPos = m_pInput->MtsPosition();
		TXDSC_EPS	inf;
		m_pEps2d4->GetAttrib(LCXE_INFO, &inf);
		inf.tm_pos	= LCXVECTOR3(MtsPos.x, MtsPos.y, 0);
		m_pEps2d4->SetAttrib(LCXE_INFO, &inf);
	}


	SAFE_FRAMEMOVE(m_pEps2d1);
	SAFE_FRAMEMOVE(m_pEps2d2);
	SAFE_FRAMEMOVE(m_pEps2d3);
	SAFE_FRAMEMOVE(m_pEps2d4);

	SAFE_FRAMEMOVE(m_pEps3d1);
	SAFE_FRAMEMOVE(m_pEps3d2);


	if(m_pInput->KeyDown(LCIK_RSHIFT))
	{
		if(m_pEta0)
		{
			m_pEta0->State(LC_LOOP_RESET);
		}
	}

	if(m_pEta0)
		m_pEta0->FrameMove();



	if(m_pInput->KeyDown(LCIK_RSHIFT))
	{
		if(m_pEta1)
		{
			m_pEta1->State(LC_LOOP_RESET);
		}
	}

	if(m_pEta1)
		m_pEta1->FrameMove();



	if(m_pInput->KeyDown(LCIK_RSHIFT))
	{
		if(m_pEtb0)
		{
			m_pEtb0->State(LC_LOOP_RESET);
		}
	}


	if(m_pEtb0)
		m_pEtb0->FrameMove();



	if(m_pInput->KeyDown(LCIK_LSHIFT))
	{
		if(m_pEtb1)
		{
			m_pEtb1->State(LC_LOOP_RESET);
		}
	}

	if(m_pEtb1)
	{
		LCXVECTOR3	pos(50.0F, 0.0F, 0.F);
		m_pEtb1->Position(&pos);
		m_pEtb1->FrameMove();
	}

	return LC_OK;
}


INT	CMain::Render()
{
	m_pDev->BeginScene();

	m_pDev->Clear(LC_CLEAR_COLOR_BUFFER | LC_CLEAR_DEPTH_BUFFER);

	m_pCam->TransformViw();
	m_pCam->TransformPrj();

	LCXCOLOR dclear(0, 0.4F, 0.6F, 1);
	m_pDev->SetRenderState(LC_RS_CLEAR_COLOR, &dclear);


	m_pDev->SetRenderState(LC_RS_CULL_FACE, LC_ST_DISABLE);
	m_pDev->SetRenderState(LC_RS_LIGHTING, LC_ST_DISABLE);


	m_pXYZ->Render();
	m_pGrid->Render();


	m_pDev->SetRenderState(LC_RS_BLEND, LC_TRUE, LC_ST_SRC_ALPHA, LC_ST_ONE);
	m_pDev->SetRenderState(LC_RS_CULL_FACE   , LC_FALSE);
	m_pDev->SetRenderState(LC_RS_DEPTH_WRITE , LC_FALSE);

	SAFE_RENDER(m_pEps3d1);
	SAFE_RENDER(m_pEps3d2);

	SAFE_RENDER(m_pEta0);
	SAFE_RENDER(m_pEta1);

	SAFE_RENDER(m_pEtb0);
	SAFE_RENDER(m_pEtb1);


	m_pDev->SetRenderState(LC_RS_BLEND, LC_TRUE, LC_ST_SRC_ALPHA, LC_ST_SRC_INV_ALPHA);
	m_pDev->SetRenderState(LC_RS_CULL_FACE   , LC_FALSE);
	m_pDev->SetRenderState(LC_RS_DEPTH_WRITE , LC_TRUE);

	m_pDev->SetRenderState(LC_RS_BLEND, LC_FALSE, LC_ST_SRC_ALPHA, LC_ST_SRC_INV_ALPHA);


	m_pSpt->Begin();
		m_pSpt->SetRenderState(LC_RS_BLEND, LC_TRUE, LC_ST_SRC_ALPHA, LC_ST_ONE);
		SAFE_RENDER(m_pEps2d1);
		SAFE_RENDER(m_pEps2d2);
		SAFE_RENDER(m_pEps2d3);
		SAFE_RENDER(m_pEps2d4);
	m_pSpt->End();


	m_pDev->EndScene();

	return LC_OK;
}


