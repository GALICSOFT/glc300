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

	m_pIdx		= NULL;
	m_pVtx		= NULL;

	m_pObj1		= NULL;
	m_pObj2		= NULL;
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
	

		LCXVECTOR3(60, -100, 60),
		LCXVECTOR3(30,   0,  0),
		LCXVECTOR3( 0,   0,  1),
	};

	MAKE_ARG1(args, (LC_HANDLE)&tCam);
	if(LC_FAILED(LcxEnt_CreateCamera(NULL, &m_pCam, &args)))
		return LC_EFAIL;



	if(LC_FAILED(LcxEnt_CreateEntity(LCXCMD_ENTITY_AXIS, &m_pXYZ)))
		return LC_EFAIL;

	if(LC_FAILED(LcxEnt_CreateEntity(LCXCMD_ENTITY_GRID, &m_pGrid)))
		return LC_EFAIL;


	// Setup Index Buffer
	m_pIdx = new LC3D::VtxFce16[12];


	// the front face index data
	m_pIdx[0] = LC3D::VtxFce16(0, 1, 2);
	m_pIdx[1] = LC3D::VtxFce16(0, 2, 3);

	// the back face index data
	m_pIdx[2] = LC3D::VtxFce16(4, 5, 6);
	m_pIdx[3] = LC3D::VtxFce16(4, 6, 7);

	// the top face index data
	m_pIdx[4] = LC3D::VtxFce16( 8,  9, 10);
	m_pIdx[5] = LC3D::VtxFce16( 8, 10, 11);

	// the bottom face index data
	m_pIdx[6] = LC3D::VtxFce16(12, 13, 14);
	m_pIdx[7] = LC3D::VtxFce16(12, 14, 15);

	// the left face index data
	m_pIdx[8] = LC3D::VtxFce16(16, 17, 18);
	m_pIdx[9] = LC3D::VtxFce16(16, 18, 19);

	// the right face index data
	m_pIdx[10] = LC3D::VtxFce16(20, 21, 22);
	m_pIdx[11] = LC3D::VtxFce16(20, 22, 23);



	// Setup Vertex Data
	m_pVtx = new VtxUV1[24];


	// the front face vertex data
	m_pVtx[ 0] = VtxUV1(-1.0F, -1.0F, -1.0F,  0.0F, 1.0F);
	m_pVtx[ 1] = VtxUV1(-1.0F,  1.0F, -1.0F,  0.0F, 0.0F);
	m_pVtx[ 2] = VtxUV1( 1.0F,  1.0F, -1.0F,  1.0F, 0.0F);
	m_pVtx[ 3] = VtxUV1( 1.0F, -1.0F, -1.0F,  1.0F, 1.0F);

	// the back face vertex data
	m_pVtx[ 4] = VtxUV1(-1.0F, -1.0F, +1.0F,  0.0F, 1.0F);
	m_pVtx[ 5] = VtxUV1( 1.0F, -1.0F, +1.0F,  0.0F, 0.0F);
	m_pVtx[ 6] = VtxUV1( 1.0F,  1.0F, +1.0F,  1.0F, 0.0F);
	m_pVtx[ 7] = VtxUV1(-1.0F,  1.0F, +1.0F,  1.0F, 1.0F);

	// the top face vertex data
	m_pVtx[ 8] = VtxUV1(-1.0F, +1.0F, -1.0F,  0.0F, 1.0F);
	m_pVtx[ 9] = VtxUV1(-1.0F, +1.0F,  1.0F,  0.0F, 0.0F);
	m_pVtx[10] = VtxUV1( 1.0F, +1.0F,  1.0F,  1.0F, 0.0F);
	m_pVtx[11] = VtxUV1( 1.0F, +1.0F, -1.0F,  1.0F, 1.0F);

	// the bottom face vertex data
	m_pVtx[12] = VtxUV1(-1.0F, -1.0F, -1.0F,  0.0F, 1.0F);
	m_pVtx[13] = VtxUV1( 1.0F, -1.0F, -1.0F,  0.0F, 0.0F);
	m_pVtx[14] = VtxUV1( 1.0F, -1.0F,  1.0F,  1.0F, 0.0F);
	m_pVtx[15] = VtxUV1(-1.0F, -1.0F,  1.0F,  1.0F, 1.0F);

	// the left face vertex data
	m_pVtx[16] = VtxUV1(-1.0F, -1.0F,  1.0F,  0.0F, 1.0F);
	m_pVtx[17] = VtxUV1(-1.0F,  1.0F,  1.0F,  0.0F, 0.0F);
	m_pVtx[18] = VtxUV1(-1.0F,  1.0F, -1.0F,  1.0F, 0.0F);
	m_pVtx[19] = VtxUV1(-1.0F, -1.0F, -1.0F,  1.0F, 1.0F);

	// the right face vertex data
	m_pVtx[20] = VtxUV1( 1.0F, -1.0F, -1.0F,  0.0F, 1.0F);
	m_pVtx[21] = VtxUV1( 1.0F,  1.0F, -1.0F,  0.0F, 0.0F);
	m_pVtx[22] = VtxUV1( 1.0F,  1.0F,  1.0F,  1.0F, 0.0F);
	m_pVtx[23] = VtxUV1( 1.0F, -1.0F,  1.0F,  1.0F, 1.0F);


	// Texture Coordinate
	m_pVtx[0].t = LCXVECTOR2(-0,-0);
	m_pVtx[1].t = LCXVECTOR2(+1,-0);
	m_pVtx[2].t = LCXVECTOR2(+1,+1);
	m_pVtx[3].t = LCXVECTOR2(-0,+1);
	m_pVtx[4].t = LCXVECTOR2(-0,-0);
	m_pVtx[5].t = LCXVECTOR2(+1,-0);
	m_pVtx[6].t = LCXVECTOR2(+1,+1);
	m_pVtx[7].t = LCXVECTOR2(-0,+1);




	m_pObj1 = new CRndObj;
	MAKE_ARG1(args, (char*)MEDIA_DIR"tex/galic.png");
	if(LC_FAILED(m_pObj1->Create(&args)))
	{
		delete m_pObj1;
		return LC_EFAIL;
	}

	m_pObj1->SetIdx(m_pIdx, 6 * 2);
	m_pObj1->SetVtx(m_pVtx);


	m_pObj2 = new CRndObj;
	MAKE_ARG1(args, (char*)MEDIA_DIR"tex/bg256x256.bmp");
	if(LC_FAILED(m_pObj2->Create(&args)))
	{
		delete m_pObj2;
		return LC_EFAIL;
	}

	m_pObj2->SetIdx(m_pIdx, 6 * 2);
	m_pObj2->SetVtx(m_pVtx);


	return LC_OK;
}

INT	CMain::Destroy()
{
	SAFE_DELETE(	m_pObj1	);
	SAFE_DELETE(	m_pObj2	);

	SAFE_DELETE_ARRAY(	m_pIdx	);
	SAFE_DELETE_ARRAY(	m_pVtx	);


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


	// Input Update
	m_pInput->Update();

	const BYTE*	pKey = m_pInput->KeyMap();

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

	if(m_pInput->KeyPress(LCIK_LEFT))
		m_pCam->RotateYaw(fAngle_degree, speed);

	if(m_pInput->KeyPress(LCIK_RIGHT))
		m_pCam->RotateYaw(fAngle_degree, -speed);

	if(m_pInput->KeyPress(LCIK_UP))
		m_pCam->RotatePitch(fAngle_degree, speed);

	if(m_pInput->KeyPress(LCIK_DOWN))
		m_pCam->RotatePitch(fAngle_degree, -speed);


	m_pCam->Update();



	// Setup World Matrix
	static int k =0;
	++k;

	LCXMATRIX	mtWld;
	LCXMATRIX	mtScl;
	LCXMATRIX	mtRotX;
	LCXMATRIX	mtRotZ;

	mtScl.Scaling(9.5F, 9.5F, 9.5F);
	mtRotZ.RotationZ( LCXToRadian(k*0.5f));
	mtRotX.RotationX( LCXToRadian(k*0.5f));

	mtWld = mtScl * mtRotZ * mtRotX;
	mtWld._41 = 10;
	mtWld._42 = -10;
	m_pObj1->SetMatrix(&mtWld);



	mtScl.Scaling(12.5F, 12.5F, 12.5F);
	mtRotZ.RotationZ( LCXToRadian( k*0.5f));
	mtRotX.RotationX( LCXToRadian(-k*0.5f));
	mtWld = mtScl * mtRotZ * mtRotX;
	mtWld._41 = 40;
	mtWld._42 = 80;
	m_pObj2->SetMatrix(&mtWld);


	return LC_OK;
}


INT	CMain::Render()
{
	m_pDev->BeginScene();

	m_pDev->Clear(LC_CLEAR_COLOR_BUFFER | LC_CLEAR_DEPTH_BUFFER);

	m_pDev->SetRenderState(LC_RS_CULL_FACE, LC_ST_DISABLE);

	m_pCam->TransformViw();
	m_pCam->TransformPrj();

	m_pXYZ->Render();
	m_pGrid->Render();


	m_pObj1->Render();
	m_pObj2->Render();



	m_pDev->EndScene();

	return LC_OK;
}



