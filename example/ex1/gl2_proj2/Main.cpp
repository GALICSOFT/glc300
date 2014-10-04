// Implementation of the CMain class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"

#define MEDIA_DIR	"../../media/"


int CMain::SetupShader()
{
	int hr =0;
	GLint bLinked;

	TLC_ARGS args;

	MAKE_ARG2(args, (UINT)GL_VERTEX_SHADER, (char*)MEDIA_DIR"shader/03sl_vs.glsl");

	hr = LcDev_CreateShaderFromTxtFile(&m_VsShader, &args);
	if(0>hr)
		return -1;

	MAKE_ARG2(args, (UINT)GL_FRAGMENT_SHADER, (char*)MEDIA_DIR"shader/03sl_fs.glsl");
	hr = LcDev_CreateShaderFromTxtFile(&m_FgShader, &args);
	if(0>hr)
		return -1;

	m_program = glCreateProgram();

    glAttachShader(m_program, m_FgShader);
    glAttachShader(m_program, m_VsShader);

    glBindAttribLocation(m_program, 0, "at_pos");

    glLinkProgram(m_program);

	glGetProgramiv(m_program, GL_LINK_STATUS, &bLinked);
	if (!bLinked)
	{
		int i32InfoLogLength;
		int i32CharsWritten;
		glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &i32InfoLogLength);
		char* pszInfoLog = new char[i32InfoLogLength];
		glGetProgramInfoLog(m_program, i32InfoLogLength, &i32CharsWritten, pszInfoLog);

		LOGE("Shader Link Err: %s\n", i32InfoLogLength ? pszInfoLog : "");
		delete[] pszInfoLog;
		return -1;
	}

	return 0;
}


static char g_CurrentDir[260]={0};


CMain::CMain()
{
	LcAux_GetCurrentDir( g_CurrentDir, 260);
}


int	CMain::Init()
{
	LcAux_SetCurrentDir( g_CurrentDir);

	SetupShader();

	m_bOrtho = LC_FALSE;

	return LC_OK;
}



int	CMain::Destroy()
{
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



	static QWORD startTime = LcAux_TimeGetTime();
	static DOUBLE frames = 1800;

	QWORD t = LcAux_TimeGetTime();
	QWORD interval = t - startTime;

	if(interval < 0)
		interval *= -1;

	if( interval > 2000 )
	{
		m_bOrtho ^= 1;
		startTime = t;
	}


	return LC_OK;
}



// Rendering vertex data
static float pCube[] =
{
	-10,-10,-10,  +10,-10,-10, +10,+10,-10, -10,+10,-10,
	-10,-10,+10,  +10,-10,+10, +10,+10,+10, -10,+10,+10
};

//      7 +----------+ 6
//       /|         /|
//      / |        / |
//     /  |       /  |
//  3 +----------+ 2 |
//    |   |      |   |
//    | 4 +------|---+ 5
//    |  /       |  /
//    | /        | /
//    |/         |/
//  0 +----------+ 1

static WORD front[]  = {2,1,3,0};
static WORD back[]   = {5,6,4,7}; //back face
static WORD top[]    = {6,2,7,3}; //top face
static WORD bottom[] = {1,5,0,4}; //bottom face
static WORD left[]   = {3,0,7,4}; //left face
static WORD right[]  = {6,5,2,1}; //right face



int	CMain::Render()
{
	// Setting Rendering pipeline
	glEnable( GL_DEPTH_TEST);
	glEnable( GL_CULL_FACE );

	glClearColor(0.9f, 1.0f, 1.0f, 1.0f);

	// Clear Color buffer and Depth Buffer.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glUseProgram(m_program);

	INT	nUsWld = glGetUniformLocation(m_program, "um_Wld");
	INT	nUsViw = glGetUniformLocation(m_program, "um_Viw");
	INT	nUsPrj = glGetUniformLocation(m_program, "um_Prj");
	INT	nUsDif = glGetUniformLocation(m_program, "uv_Dif");


	LCXMATRIX	mtZ, mtX, mtY;
	LCXVECTOR3	pos(0, 0, 0);

	static int c =0;
	++c;

	mtZ.RotationZ( LCXToRadian((float)(c) ));
	mtX.RotationX( LCXToRadian((float)(c) ));
	mtY.RotationY( LCXToRadian((float)(c) ));
	m_mtWld = mtZ * mtX * mtY;


	LCXVECTOR3	eye(0, 40, 20);
	LCXVECTOR3	look(0,0,0);
	LCXVECTOR3	up(0,0,1);
	m_mtViw.ViewGl(&eye, &look, &up);


	// set up projection matrix in 3d pipeline
	float	temp[16]={0};
	float	width, height;
	glGetFloatv(GL_VIEWPORT, temp);		// get viewport to set the screen width and height.
	width = temp[2];
	height= temp[3];
	float	Aspect = (float)width/height;
	float	Near = 1.F;
	float	Far	 = 1000.F;

	m_mtPrjPers.PerspectiveD3dRH( LCXToRadian(45.F), Aspect, Near, Far);
	m_mtPrjOrth.OrthoGl(-24.0F, 24.0F, -18.0F, 18.0F, -100.0F, 100.0F);

	
	glUniformMatrix4fv(nUsWld, 1, 0, (GLfloat*)&m_mtWld);
	glUniformMatrix4fv(nUsViw, 1, 0, (GLfloat*)&m_mtViw);

	if(m_bOrtho)
		glUniformMatrix4fv(nUsPrj, 1, 0, (GLfloat*)&m_mtPrjOrth);
	else
		glUniformMatrix4fv(nUsPrj, 1, 0, (GLfloat*)&m_mtPrjPers);


	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, pCube);

	LCXCOLOR v1(1,0,0,1);	glUniform4fv(nUsDif, 1, (GLfloat*)&v1);	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, front);
	LCXCOLOR v2(0,1,0,1);	glUniform4fv(nUsDif, 1, (GLfloat*)&v2);	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, back);
	LCXCOLOR v3(0,0,1,1);	glUniform4fv(nUsDif, 1, (GLfloat*)&v3);	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, top);
	LCXCOLOR v4(1,1,0,1);	glUniform4fv(nUsDif, 1, (GLfloat*)&v4);	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, bottom);
	LCXCOLOR v5(0,1,1,1);	glUniform4fv(nUsDif, 1, (GLfloat*)&v5);	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, left);
	LCXCOLOR v6(1,0,1,1);	glUniform4fv(nUsDif, 1, (GLfloat*)&v6);	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, right);

	glDisableVertexAttribArray(0);


	return LC_OK;
}


