// Implementation of the CMain class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


#if !defined(_MSC_VER) && !defined(_PC_LINUX_)
#define GLSL_ENABLE_PRECISION
#endif

#if defined GLSL_ENABLE_PRECISION
	#define PRECI_HIP	" highp "
	#define PRECI_MIP	" mediump "
	#define PRECI_LOP	" lowp "
#else
	#define PRECI_HIP	" "
	#define PRECI_MIP	" "
	#define PRECI_LOP	" "
#endif



static char	glsl_vs[]=
"#define MAX_UNIFORM	32									\n"	// 1
"															\n"	// 2
"attribute" PRECI_HIP "vec4   at_pos;						\n"	// 3
"attribute" PRECI_MIP "vec4   at_dif;						\n"	// 4
"attribute" PRECI_MIP "vec4   at_iwg;						\n"	// 5
"															\n"	// 6
"varying  " PRECI_MIP "vec4    vr_dif;						\n"	// 7
"															\n"	// 8
"uniform  " PRECI_HIP "mat4    um_VP;						\n"	// 9	// view * projection matrix
"uniform  " PRECI_HIP "mat4    um_Atm[MAX_UNIFORM];			\n"	//10	// Vertex blending matrix list
"															\n"	// 1
" void main(){												\n"	// 2
	PRECI_LOP "vec3    pos  = vec3(0.0);					\n"	// 3
"															\n"	// 4
	PRECI_LOP "int   n1 = int(at_iwg.x);					\n"	// 5
	PRECI_LOP "int   n2 = int(at_iwg.y);					\n"	// 6
	PRECI_LOP "float g1 = at_iwg.z;							\n"	// 7
	PRECI_LOP "float g2 = 1.0 - at_iwg.z;					\n"	// 8
"															\n"	// 9
"	pos  = vec3(um_Atm[n1] * at_pos) * g1;					\n"	//20
"	pos += vec3(um_Atm[n2] * at_pos) * g2;					\n"	// 1
"															\n"	// 2
"   gl_Position  = um_VP * vec4(pos, 1.0);					\n"	// 3
"	gl_PointSize = 9.0;										\n"	// 4
"															\n"	// 5
"	vr_dif = at_dif;										\n"	// 6
"}															\n"	// 7
;

static char glsl_fs[]=
"varying  " PRECI_MIP "vec4    vr_dif;						\n"
"															\n"
"void main() {												\n"
"	gl_FragColor = vr_dif;									\n"
"}															\n"
;



#define MAX_UNIFORM	32

int				g_nVtx = 0;
LCXVECTOR3*		g_pos;
LCXCOLOR*		g_dif;
LCXVECTOR4*		g_iwg;

LCXMATRIX	um_Atm[MAX_UNIFORM];	// Vertex blending matrix


CMain::CMain()
{
	g_nVtx = MAX_UNIFORM*2;

	g_pos = new LCXVECTOR3[g_nVtx];
	g_dif = new LCXCOLOR  [g_nVtx];
	g_iwg = new LCXVECTOR4[g_nVtx];

	float w = 5.0F;

	for(int n=0; n<MAX_UNIFORM; ++n)
	{
		g_pos[2*n +0] = LCXVECTOR3( (MAX_UNIFORM/2.0F-n)*w, 0.0F, +15.0F);
		g_pos[2*n +1] = LCXVECTOR3( (MAX_UNIFORM/2.0F-n)*w, 0.0F, -15.0F);
		g_dif[2*n +0] = LCXCOLOR( 1.0F, 1.0F, 1.0F, 1.0F);
		g_dif[2*n +1] = LCXCOLOR( 0.4F, 0.4F, 0.4F, 1.0F);

		g_iwg[2*n +0] = LCXVECTOR4(float(n%MAX_UNIFORM), float(n%MAX_UNIFORM), 1.0F, 0.0F);
		g_iwg[2*n +1] = LCXVECTOR4(float(n%MAX_UNIFORM), float(n%MAX_UNIFORM), 1.0F, 0.0F);

		//g_iwg[2*n +0] = LCXVECTOR4(float(n%MAX_UNIFORM), float(n%MAX_UNIFORM), 1.0F, 0.0F);
		//g_iwg[2*n +1] = LCXVECTOR4(float(n%MAX_UNIFORM), float(n%MAX_UNIFORM), 1.0F, 0.0F);
	}


	m_pInput	= NULL;
	m_pCam		= NULL;
	m_pXYZ		= NULL;
	m_pGrid		= NULL;

	m_pEft		= NULL;
}


INT	CMain::Init()
{
	INT hr = 0;

	
	TLC_ARGS args;

	char* attlist[] = {"at_pos", "at_dif", "at_iwg", NULL};

	MAKE_ARG3(args, (char*)glsl_vs, (char*)glsl_fs, (char**)attlist);
	hr = LcDev_CreateEffectFromTxtBuffer(NULL, &m_pEft, m_pDev, &args);
	if(LC_FAILED(hr))
		return LC_EFAIL;


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
	
		LCXVECTOR3(4, -100, 20),
		LCXVECTOR3(4,   0,  0),
		LCXVECTOR3(0,   0,  1),
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

	SAFE_RELEASE(	m_pEft		);

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
	if(c>8*60*200)
	{
		printf("Game Process Terminated\n");
		return LC_EFAIL;
	}



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
	int n = 0;

	LCXMATRIX	mtViw;
	LCXMATRIX	mtPrj;
	LCXMATRIX	um_VP;

	m_pDev->BeginScene();

	m_pDev->Clear(LC_CLEAR_COLOR_BUFFER | LC_CLEAR_DEPTH_BUFFER);


	m_pCam->TransformViw();
	m_pCam->TransformPrj();


	m_pDev->SetRenderState(LC_RS_CULL_FACE, LC_ST_ENABLE);

	m_pXYZ->Render();
	m_pGrid->Render();



	// sume device needs this...
	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
	glEnable( GL_POINT_SPRITE );



	FLOAT	fAngle = LcAux_TimeGetTime() * 0.2f;



	for(n=0; n<MAX_UNIFORM; ++n)
	{
		float fTheta = fAngle + n * (360.f/25);

		float	x =  4.0F * LCXMathCos(LCXToRadian(fTheta));
		float	y = 10.0F * LCXMathSin(LCXToRadian(fTheta));

		um_Atm[n].Identity();
		um_Atm[n]._41 = x;
		um_Atm[n]._43 = y;
	}


	m_pDev->GetTransform(LC_TM_VIEW, &mtViw);
	m_pDev->GetTransform(LC_TM_PROJ, &mtPrj);

	um_VP = mtViw * mtPrj;
	
	m_pEft->Begin();

	m_pEft->Mat4v  ("um_Atm", um_Atm, MAX_UNIFORM);
	m_pEft->Matrix4("um_VP" , &um_VP);


	glEnableVertexAttribArray(0);	glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, g_pos);
	glEnableVertexAttribArray(1);	glVertexAttribPointer(1, 4, GL_FLOAT, 0, 0, g_dif);
	glEnableVertexAttribArray(2);	glVertexAttribPointer(2, 4, GL_FLOAT, 0, 0, g_iwg);

	glDrawArrays(GL_POINTS, 0, g_nVtx);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	m_pEft->End();


	glDisable( GL_POINT_SPRITE );

	m_pDev->EndScene();

	return LC_OK;
}



