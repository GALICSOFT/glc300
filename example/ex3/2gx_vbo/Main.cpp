// Implementation of the CMain class.
//
// VBO客 包访等 窃荐
//
//	- glBindBuffer
//	- glBufferData
//	- glBufferSubData
//	- glDeleteBuffers
//	- glGenBuffers
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
	TLC_ARGS	args;

	// Input 积己
	if(LC_FAILED(LcxEnt_CreateInput(NULL, &m_pInput)))
		return LC_EFAIL;


	// Camera 积己
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




	////////////////////////////////////////////////////////////////////////////
	UINT i=0;


	// 沥痢 单捞磐(position(float3) + color(byte4:rgba))
	struct Tvtx
	{
		float			x, y, z;
		unsigned char	r, g, b, a;
	}

	vtx_src[] =
	{
		{-10,-10,-10, 255,  0,  0,255},
		{+10,-10,-10,   0,  0,255,255},
		{+10,+10,-10,   0,255,255,255},
		{-10,+10,-10,   0,255,255,255},
		{-10,-10,+10,   0,255,  0,255},
		{+10,-10,+10, 255,255,  0,255},
		{+10,+10,+10, 255,  0,255,255},
		{-10,+10,+10, 255,255,  0,255}
	};


	for(i=0; i< sizeof(vtx_src)/sizeof(vtx_src[0]); ++i)
		vtx_src[i] = vtx_src[i];


	UINT	dFVF = LC_FVF_XYZ|LC_FVF_DIFFUSE;
	INT		nSize = sizeof(vtx_src);

	MAKE_ARG3(args, dFVF, (LC_HANDLE)vtx_src, nSize);
	if(LC_FAILED(LcDev_CreateVB(NULL, &m_pVB, &args)))
		return LC_EFAIL;




	dFVF = LC_FMT_WORD;
	nSize = sizeof(WORD) * 4;

	for(i=0;i<6; ++i)
	{
		MAKE_ARG3(args, dFVF, (LC_HANDLE)NULL, nSize);
		if(LC_FAILED(LcDev_CreateIB(NULL, &m_pIB[i], &args)))
			return LC_EFAIL;
	}

	// Index 单捞磐
	WORD front [] = {2,1,3,0};	// front face
	WORD back  [] = {5,6,4,7};	// back face
	WORD top   [] = {6,2,7,3};	// top face
	WORD bottom[] = {1,5,0,4};	// bottom face
	WORD left  [] = {3,0,7,4};	// left face
	WORD right [] = {6,5,2,1};	// right face

	m_pIB[0]->Fill(front , nSize);
	m_pIB[1]->Fill(back  , nSize);
	m_pIB[2]->Fill(top   , nSize);
	m_pIB[3]->Fill(bottom, nSize);
	m_pIB[4]->Fill(left  , nSize);
	m_pIB[5]->Fill(right , nSize);

	return LC_OK;
}


INT	CMain::Destroy()
{
	INT i=0;

	m_pVB->Release();

	for(i=0; i<6; ++i)
	{
		if(m_pIB[i])
			m_pIB[i]->Release();
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

	if(m_pInput->KeyPress(LCIK_LEFT))
		m_pCam->RotateYaw(fAngle_degree, speed);

	if(m_pInput->KeyPress(LCIK_RIGHT))
		m_pCam->RotateYaw(fAngle_degree, -speed);

	if(m_pInput->KeyPress(LCIK_UP))
		m_pCam->RotatePitch(fAngle_degree, speed);

	if(m_pInput->KeyPress(LCIK_DOWN))
		m_pCam->RotatePitch(fAngle_degree, -speed);


	SAFE_UPDATE(	m_pCam	);


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



	static int c =0;
	++c;

	LCXMATRIX	mtRotX;
	LCXMATRIX	mtRotZ;
	LCXMATRIX	mtWld;
	mtRotZ.RotationZ( LCXToRadian(c*5.5f));
	mtRotX.RotationX( LCXToRadian(c*3.5f));

	mtWld = mtRotZ * mtRotX;

	mtWld._41 = 10;
	mtWld._42 = -10;
	m_pDev->SetTransform(LC_TM_WORLD, &mtWld);

	m_pDev->SetFVF( m_pVB->Fmt() );
	m_pDev->SetStreamSource(m_pVB);


	LCXCOLOR col(1,1,1,1);

	col = LCXCOLOR(1,0,1,1);	m_pDev->SetTcolor(&col);	m_pDev->SetIndices(m_pIB[0]);	m_pDev->DrawIndexedPrimitiveUP(LC_PT_TRIANGLE_STRIP, 4);
	col = LCXCOLOR(0,1,1,1);	m_pDev->SetTcolor(&col);	m_pDev->SetIndices(m_pIB[1]);	m_pDev->DrawIndexedPrimitiveUP(LC_PT_TRIANGLE_STRIP, 4);
	col = LCXCOLOR(1,0,1,1);	m_pDev->SetTcolor(&col);	m_pDev->SetIndices(m_pIB[2]);	m_pDev->DrawIndexedPrimitiveUP(LC_PT_TRIANGLE_STRIP, 4);
	col = LCXCOLOR(1,1,0,1);	m_pDev->SetTcolor(&col);	m_pDev->SetIndices(m_pIB[3]);	m_pDev->DrawIndexedPrimitiveUP(LC_PT_TRIANGLE_STRIP, 4);
	col = LCXCOLOR(0,1,1,1);	m_pDev->SetTcolor(&col);	m_pDev->SetIndices(m_pIB[4]);	m_pDev->DrawIndexedPrimitiveUP(LC_PT_TRIANGLE_STRIP, 4);
	col = LCXCOLOR(1,0,1,1);	m_pDev->SetTcolor(&col);	m_pDev->SetIndices(m_pIB[5]);	m_pDev->DrawIndexedPrimitiveUP(LC_PT_TRIANGLE_STRIP, 4);

	m_pDev->SetTcolor(NULL);

	m_pDev->SetFVF(0);
	m_pDev->SetStreamSource(NULL);
	m_pDev->SetIndices(NULL);

	m_pDev->SetTransform(LC_TM_WORLD_IDENTITY, NULL);


	m_pDev->EndScene();

	return LC_OK;
}




