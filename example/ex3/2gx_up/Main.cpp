// Implementation of the CMain class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


CMain::CMain()
{
	m_pInput	= NULL;
	m_pCam		= NULL;
	m_pXYZ		= NULL;
	m_pGrid		= NULL;
}


INT	CMain::Init()
{
	// Input 持失
	if(LC_FAILED(LcxEnt_CreateInput(NULL, &m_pInput)))
		return LC_EFAIL;

	TLC_ARGS	args;

	// Camera 持失
	TXDSC_CAMERA	tCam =
	{
		LCX_CAM_FIRST,
		LCXToRadian(45.0F),
		1.0F,
		5000.0F,

		FLOAT(m_nScnW),
		FLOAT(m_nScnH),
	

		LCXVECTOR3(30, -100, 30),
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

	// front face
	m_pIdx[ 0] = LC3D::VtxFce16(2,1,3);
	m_pIdx[ 1] = LC3D::VtxFce16(1,3,0);

	// back face
	m_pIdx[ 2] = LC3D::VtxFce16(5,6,4);
	m_pIdx[ 3] = LC3D::VtxFce16(6,4,7);

	// top face
	m_pIdx[ 4] = LC3D::VtxFce16(6,2,7);
	m_pIdx[ 5] = LC3D::VtxFce16(2,7,3);

	// bottom face
	m_pIdx[ 6] = LC3D::VtxFce16(1,5,0);
	m_pIdx[ 7] = LC3D::VtxFce16(5,0,4);

	// left face
	m_pIdx[ 8] = LC3D::VtxFce16(3,0,7);
	m_pIdx[ 9] = LC3D::VtxFce16(0,7,4);

	// right face
	m_pIdx[10] = LC3D::VtxFce16(6,5,2);
	m_pIdx[11] = LC3D::VtxFce16(5,2,1);


	// Setup Vertex buffer for Object1
	LC3D::Vtx*	pVtx1 = new LC3D::Vtx[8];

	pVtx1[0].p = LCXVECTOR3(-20,-10,-5);
	pVtx1[1].p = LCXVECTOR3(+20,-10,-5);
	pVtx1[2].p = LCXVECTOR3(+20,+10,-5);
	pVtx1[3].p = LCXVECTOR3(-20,+10,-5);
	pVtx1[4].p = LCXVECTOR3(-20,-10,+5);
	pVtx1[5].p = LCXVECTOR3(+20,-10,+5);
	pVtx1[6].p = LCXVECTOR3(+20,+10,+5);
	pVtx1[7].p = LCXVECTOR3(-20,+10,+5);

	m_pObj1.pIdx = m_pIdx;
	m_pObj1.pVtx = pVtx1;


	// Setup Vertex buffer for Object2
	LC3D::VtxD* pVtx2 = new LC3D::VtxD[8];

	pVtx2[0].p = LCXVECTOR3(-10,-10,-10);
	pVtx2[1].p = LCXVECTOR3(+10,-10,-10);
	pVtx2[2].p = LCXVECTOR3(+10,+10,-10);
	pVtx2[3].p = LCXVECTOR3(-10,+10,-10);
	pVtx2[4].p = LCXVECTOR3(-10,-10,+10);
	pVtx2[5].p = LCXVECTOR3(+10,-10,+10);
	pVtx2[6].p = LCXVECTOR3(+10,+10,+10);
	pVtx2[7].p = LCXVECTOR3(-10,+10,+10);

	pVtx2[0].d = LC_COLORB(255,   0,   0, 255);
	pVtx2[1].d = LC_COLORB(  0, 255,   0, 255);
	pVtx2[2].d = LC_COLORB(  0,   0, 255, 255);
	pVtx2[3].d = LC_COLORB(255, 255,   0, 255);
	pVtx2[4].d = LC_COLORB(  0, 255, 255, 255);
	pVtx2[5].d = LC_COLORB(255,   0, 255, 255);
	pVtx2[6].d = LC_COLORB(255,   0,   0, 255);
	pVtx2[7].d = LC_COLORB(  0, 255,   0, 255);

	m_pObj2.pIdx = m_pIdx;
	m_pObj2.pVtx = pVtx2;

	return LC_OK;
}

INT	CMain::Destroy()
{
	if(m_pObj1.pVtx)
	{
		LC3D::Vtx*	 pVtx = (LC3D::Vtx*)m_pObj1.pVtx;
		delete [] pVtx;
		m_pObj1.pVtx = NULL;
	}

	if(m_pObj2.pVtx)
	{
		LC3D::VtxD* pVtx = (LC3D::VtxD*)m_pObj2.pVtx;
		delete [] pVtx;
		m_pObj2.pVtx = NULL;
	}

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
	const BYTE*	pMts = m_pInput->MtsMap();

	if(pKey[LCIK_ESCAPE])
		return LC_EFAIL;


	// Move, Rotation Speed
	FLOAT speed = (FLOAT)m_TimeElps;
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


	SAFE_UPDATE(	m_pCam	);



	// Setup World Matrix
	static int k =0;
	++k;

	LCXMATRIX	mtRotX;
	LCXMATRIX	mtRotZ;

	mtRotZ.RotationZ( LCXToRadian(k*3.5f));
	mtRotX.RotationX( LCXToRadian(k*3.5f));

	m_pObj1.mtWld = mtRotZ * mtRotX;
	m_pObj1.mtWld._41 = 10;
	m_pObj1.mtWld._42 = -10;



	mtRotZ.RotationZ( LCXToRadian(k*2.5f));
	mtRotX.RotationX( LCXToRadian(-k*1.5f));

	m_pObj2.mtWld = mtRotZ * mtRotX;
	m_pObj2.mtWld._41 = 40;
	m_pObj2.mtWld._42 = 10;


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


	m_pDev->SetTransform(LC_TM_WORLD, &m_pObj1.mtWld);
	m_pDev->SetFVF(LC3D::Vtx::FVF);

	LCXCOLOR col(1,1,1,1);

	col = LCXCOLOR(1,0,0,1);	m_pDev->SetTcolor(&col);	m_pDev->DrawIndexedPrimitiveUP(LC_PT_TRIANGLE_LIST, 2* 3, &m_pIdx[0*2], LC_FMT_WORD, m_pObj1.pVtx, sizeof(LC3D::Vtx));
	col = LCXCOLOR(0,1,0,1);	m_pDev->SetTcolor(&col);	m_pDev->DrawIndexedPrimitiveUP(LC_PT_TRIANGLE_LIST, 2* 3, &m_pIdx[1*2], LC_FMT_WORD, m_pObj1.pVtx, sizeof(LC3D::Vtx));
	col = LCXCOLOR(0,0,1,1);	m_pDev->SetTcolor(&col);	m_pDev->DrawIndexedPrimitiveUP(LC_PT_TRIANGLE_LIST, 2* 3, &m_pIdx[2*2], LC_FMT_WORD, m_pObj1.pVtx, sizeof(LC3D::Vtx));
	col = LCXCOLOR(1,1,0,1);	m_pDev->SetTcolor(&col);	m_pDev->DrawIndexedPrimitiveUP(LC_PT_TRIANGLE_LIST, 2* 3, &m_pIdx[3*2], LC_FMT_WORD, m_pObj1.pVtx, sizeof(LC3D::Vtx));
	col = LCXCOLOR(0,1,1,1);	m_pDev->SetTcolor(&col);	m_pDev->DrawIndexedPrimitiveUP(LC_PT_TRIANGLE_LIST, 2* 3, &m_pIdx[4*2], LC_FMT_WORD, m_pObj1.pVtx, sizeof(LC3D::Vtx));
	col = LCXCOLOR(1,0,1,1);	m_pDev->SetTcolor(&col);	m_pDev->DrawIndexedPrimitiveUP(LC_PT_TRIANGLE_LIST, 2* 3, &m_pIdx[5*2], LC_FMT_WORD, m_pObj1.pVtx, sizeof(LC3D::Vtx));

	m_pDev->SetTcolor(NULL);


	m_pDev->SetTransform(LC_TM_WORLD, &m_pObj2.mtWld);
	m_pDev->SetFVF(LC3D::VtxD::FVF);
	m_pDev->DrawIndexedPrimitiveUP(LC_PT_TRIANGLE_LIST, 6*2*3, m_pIdx, LC_FMT_WORD, m_pObj2.pVtx, sizeof(LC3D::VtxD));

	m_pDev->SetTransform(LC_TM_WORLD_IDENTITY, NULL);



	m_pDev->EndScene();

	return LC_OK;
}




