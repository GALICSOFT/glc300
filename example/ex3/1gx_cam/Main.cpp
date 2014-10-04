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


	// Camera 持失
	TLC_ARGS	args;

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

	return LC_OK;
}

INT	CMain::Destroy()
{
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
	printf("FPS: %3.f\n", m_TimeFPS);



	// Input Update
	m_pInput->Update();

	const BYTE*	pKey = m_pInput->KeyMap();
	const BYTE*	pMts = m_pInput->MtsMap();

	if(pKey[LCIK_ESCAPE])
		return LC_EFAIL;


	// Move, Rotation Speed
	FLOAT speed = (FLOAT)m_TimeElps;
	speed *=.1f;


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

	return LC_OK;
}


INT	CMain::Render()
{
	m_pDev->BeginScene();

	m_pDev->Clear(LC_CLEAR_COLOR_BUFFER | LC_CLEAR_DEPTH_BUFFER);

	m_pCam->TransformViw();
	m_pCam->TransformPrj();



	m_pDev->SetRenderState(LC_RS_CULL_FACE, LC_ST_ENABLE);

	m_pXYZ->Render();
	m_pGrid->Render();


	m_pDev->EndScene();

	return LC_OK;
}



