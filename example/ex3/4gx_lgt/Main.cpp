
// Implementation of the CMain class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


#define MEDIA_DIR	"../../media/"



INT_PTR CALLBACK WndDlg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static	WPARAM	wparHi;
	static	WPARAM	wparLo;

	wparHi = HIWORD(wParam);
	wparLo = LOWORD(wParam);

	switch( uMsg )
	{
	case WM_INITDIALOG:
		{
			return TRUE;
		}

	case WM_CLOSE:
		{
			break;
		}
	}

	return(FALSE);
}



CMain::CMain()
{
	m_pInput	= NULL;
	m_pCam		= NULL;
	m_pXYZ		= NULL;
	m_pGrid		= NULL;
	m_pTex		= NULL;

	m_pMRC		= NULL;
}


INT	CMain::Init()
{
	TLC_ARGS	args;
	INT			hr = 0;

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
	
		LCXVECTOR3(20.0F,-130.0F, 120.0F),
		LCXVECTOR3( 0.0F,  0.0F, 5.0F),
		LCXVECTOR3( 0.0F,  0.0F, 1.0F),
	};
	MAKE_ARG1(args, (LC_HANDLE)&tCam);
	if(LC_FAILED(LcxEnt_CreateCamera(NULL, &m_pCam, &args)))
		return LC_EFAIL;



	if(LC_FAILED(LcxEnt_CreateEntity(LCXCMD_ENTITY_AXIS, &m_pXYZ)))
		return LC_EFAIL;

	if(LC_FAILED(LcxEnt_CreateEntity(LCXCMD_ENTITY_GRID, &m_pGrid)))
		return LC_EFAIL;


	MAKE_ARG4(args, (char*)MEDIA_DIR"tex/wood.png", (UINT)0, (UINT)0, (INT)1);
	hr = LcDev_CreateTextureFromFile(NULL, &m_pTex, &args);
	if(LC_FAILED(hr))
		return LC_EFAIL;



	LC_HWND hWnd   = (LC_HWND  )LcVar_ReadP(LC_VAR_WIN_HANDLE  );
	LC_HWND hWndDlg = CreateDialog( GetModuleHandle(NULL),MAKEINTRESOURCE(IDD_SUB_WIN), hWnd ,WndDlg);
	ShowWindow(hWndDlg, SW_SHOW);


	MAKE_ARG1(args, (LC_HANDLE)hWndDlg);
	hr = LcDev_CreateMRC(NULL, &m_pMRC, &args);

	return LC_OK;
}

INT	CMain::Destroy()
{
	SAFE_RELEASE(	m_pXYZ		);
	SAFE_RELEASE(	m_pGrid		);
	SAFE_RELEASE(	m_pCam		);
	SAFE_RELEASE(	m_pInput	);

	SAFE_RELEASE(	m_pTex		);

	SAFE_RELEASE(	m_pMRC		);

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

	if(n>50)
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


	// Camera Translation
	if(pKey[LCIK_W])
		m_pCam->MoveForward(+speed);

	if(pKey[LCIK_S])
		m_pCam->MoveForward(-speed);

	if(pKey[LCIK_A])
		m_pCam->MoveSideward(-speed);

	if(pKey[LCIK_D])
		m_pCam->MoveSideward(+speed);


	// Camera Rotation
	FLOAT fAngle_degree = 2.0f;

	if(m_pInput->KeyPress(LCIK_LEFT))
		m_pCam->RotateYaw(fAngle_degree, speed);

	if(m_pInput->KeyPress(LCIK_RIGHT))
		m_pCam->RotateYaw(fAngle_degree, -speed);

	if(m_pInput->KeyPress(LCIK_UP))
		m_pCam->RotatePitch(fAngle_degree, speed);

	if(m_pInput->KeyPress(LCIK_DOWN))
		m_pCam->RotatePitch(fAngle_degree, -speed);


	m_pCam->Update();



	return LC_OK;
}


extern unsigned short* GetIdx();
extern float* GetVtx();

extern int GetIdxCount();
extern int GetVtxCount();



void CMain::Draw()
{
	LCXCOLOR	clearColor(0.4f, 0.8f, 0.99f, 1.0f);

	m_pDev->SetRenderState(LC_RS_CLEAR_COLOR, (COLOR32)clearColor);
	m_pDev->Clear(LC_CLEAR_COLOR_BUFFER | LC_CLEAR_DEPTH_BUFFER);

	m_pDev->SetRenderState(LC_RS_DEPTH_TEST, LC_ST_ENABLE);		// Enable Depth Test
	m_pDev->SetRenderState(LC_RS_CULL_FACE, LC_ST_ENABLE);		// Enable Culling


	m_pDev->SetRenderState(LC_RS_LIGHTING, LC_ST_ENABLE);			// Enable lighting computations
	m_pDev->SetRenderState(LC_RS_FOG, LC_ST_ENABLE);				// Enable Fog


	m_pXYZ->Render();
	m_pGrid->Render();



	// Fog Setting
	TLC_FOG fog;
	{
		fog.Col = clearColor;
		fog.Bgn = 60.F;
		fog.Rng	= 100.F;
		fog.Pow = 2.0F;
		fog.Act	= 1.0F;
	};

	m_pDev->SetRenderState(LC_RS_FOG_DATA, &fog);



	LCXVECTOR3	lgtAmb(0,0,0);
	LCXVECTOR4	lgtDir[4];
	LCXCOLOR	lgtDif[4];
	LCXCOLOR	lgtSpc[4];


	lgtDir[0] = LCXVECTOR4( 1.0F,  1.0F,  1.0F,  1.0F);
	lgtDir[1] = LCXVECTOR4(-1.0F,  1.0F,  1.0F,  1.0F);
	lgtDir[2] = LCXVECTOR4( 0.0F,  1.0F,  1.0F,  1.0F);
	lgtDir[3] = LCXVECTOR4( 0.0F, -1.0F,  0.0F,  1.0F);
	lgtDif[0] = LCXCOLOR( 1.0F,  0.0F,  0.0F,  1.0F);
	lgtDif[1] = LCXCOLOR( 0.0F,  1.0F,  0.0F,  1.0F);
	lgtDif[2] = LCXCOLOR( 0.4F,  0.0F,  1.0F,  1.0F);
	lgtDif[3] = LCXCOLOR( 0.0F,  0.4F,  0.8F,  1.0F);

	lgtSpc[0] = LCXCOLOR( 2.0F,  0.0F,  0.0F,  8.0F);
	lgtSpc[1] = LCXCOLOR( 0.0F,  2.0F,  0.0F,  8.0F);

	for(int i=0; i<4; ++i)
		LCXVec3Normalize((LCXVECTOR3*)&lgtDir[i], (LCXVECTOR3*)&lgtDir[i]);



	// Lighting Setting
	TLC_LIGHT lgt0;
	memset(&lgt0, 0, sizeof(TLC_LIGHT));
	{
		lgt0.Dif = lgtDif[0];
		lgt0.Spc = lgtSpc[0];
		lgt0.Dir = lgtDir[0];
	};

	m_pDev->SetRenderState(LC_RS_LIGHT0_DATA, &lgt0);
	m_pDev->SetRenderState(LC_RS_LIGHT0, LC_ST_ENABLE);			// Enable Light0


	TLC_LIGHT lgt1;
	memset(&lgt1, 0, sizeof(TLC_LIGHT));
	{
		lgt1.Dif = lgtDif[1];
		lgt1.Spc = lgtSpc[1];
		lgt1.Dir = lgtDir[1];
	};

	m_pDev->SetRenderState(LC_RS_LIGHT1_DATA, &lgt1);
	m_pDev->SetRenderState(LC_RS_LIGHT1, LC_ST_ENABLE);			// Enable Light1


	TLC_LIGHT lgt2;
	memset(&lgt2, 0, sizeof(TLC_LIGHT));
	{
		lgt2.Dif = lgtDif[2];
		lgt2.Dir = lgtDir[2];
	};

	m_pDev->SetRenderState(LC_RS_LIGHT2_DATA, &lgt2);
	m_pDev->SetRenderState(LC_RS_LIGHT2, LC_ST_ENABLE);			// Enable Light2


	TLC_LIGHT lgt3;
	memset(&lgt3, 0, sizeof(TLC_LIGHT));
	{
		lgt3.Dif = lgtDif[3];
		lgt3.Dir = lgtDir[3];
	};

	m_pDev->SetRenderState(LC_RS_LIGHT3_DATA, &lgt3);
	m_pDev->SetRenderState(LC_RS_LIGHT3, LC_ST_ENABLE);			// Enable Light2



	// Set Model position
	static FLOAT fRot = 0;
	fRot +=0.4f;

	LCXMATRIX	mtS;
	LCXMATRIX	mtRot;

	mtS.Scaling(5, 5, 5);
	mtRot.RotationZ( LCXToRadian(fRot));

	mtRot = mtS * mtRot;
	m_pDev->SetTransform(LC_TM_WORLD, &mtRot);




	USHORT* pIdx = GetIdx();
	char*   pVtx = (char*)GetVtx();
	int     nIdx = GetIdxCount();
	int     nVtx = GetVtxCount();

	m_pDev->SetFVF(TvtxNUV1::FVF);
	m_pDev->SetTexture(0, m_pTex);


	m_pDev->DrawIndexedPrimitiveUP(LC_PT_TRIANGLE_LIST, nIdx, pIdx, LC_FMT_WORD, pVtx, sizeof(TvtxNUV1));


	m_pDev->SetTexture(0, NULL);

	m_pDev->SetTransform(LC_TM_WORLD_IDENTITY, NULL);


	m_pDev->SetRenderState(LC_RS_LIGHTING, LC_ST_DISABLE);			// Disable lighting computations
	m_pDev->SetRenderState(LC_RS_FOG, LC_ST_DISABLE);					// Disable Fog

	m_pDev->SetRenderState(LC_RS_DEPTH_TEST, LC_ST_DISABLE);
	m_pDev->SetRenderState(LC_RS_CULL_FACE, LC_ST_DISABLE);
	m_pDev->SetRenderState(LC_RS_LIGHTING, LC_ST_DISABLE);
}




INT	CMain::Render()
{
	m_pCam->TransformViw();
	m_pCam->TransformPrj();

	if(LC_SUCCEEDED(m_pMRC->Begin() ))
	{
		Draw();
		m_pMRC->End();
	}


	m_pDev->BeginScene();

		Draw();

	m_pDev->EndScene();

	return LC_OK;
}



