// Implementation of the CMain class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"

#define MEDIA_DIR	"../../media/"


void MyGluPerspective(float* Out, float Fov, float Aspect, float Near, float Far)
{
	float	mtPrj[4][4] ={0};
	float	COT  = (float)tan(Fov/2. * 3.14159265358979/180.0 );

	COT = 1.0F/COT;

	mtPrj[0][0] =  COT/Aspect;
	mtPrj[1][1] =  COT;
	mtPrj[2][2] = -(Far+Near)/(Far-Near);
	mtPrj[3][2] = -2*Far*Near/(Far-Near);
	mtPrj[2][3] = -1;

	memcpy(Out, mtPrj, sizeof(float)*16);
}



void Vec3Normalize(float* v)
{
	float r;

	r = (float) sqrt( v[0]*v[0] + v[1]*v[1] + v[2]*v[2] );
	if (r == 0.0)
	return;
	r = 1.F/r;

	v[0] *= r; v[1] *= r; v[2] *= r;
}

void Vec3Cross(float* Out, const float* v1, const float* v2)
{
	Out[0] = v1[1] * v2[2] - v1[2] * v2[1];
	Out[1] = v1[2] * v2[0] - v1[0] * v2[2];
	Out[2] = v1[0] * v2[1] - v1[1] * v2[0];
}

float Vec3Dot(const float* v1, const float* v2)
{
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}


void MyGluLookAt(float* Out, float EyeX, float EyeY, float EyeZ
	, float AtX, float AtY, float AtZ
	, float UpX, float UpY, float UpZ)
{
	float Eye[3]={EyeX, EyeY, EyeZ};
	float AxisX[3]={0}, AxisY[3]={UpX, UpY, UpZ}, AxisZ[3]={0};
	float m[4][4]={0};

	AxisZ[0] = EyeX - AtX;			// Z = Eye - LookAt
	AxisZ[1] = EyeY - AtY;
	AxisZ[2] = EyeZ - AtZ;
	Vec3Normalize(AxisZ);

	Vec3Cross(AxisX, AxisY, AxisZ);	// X = Y ^ Z
	Vec3Normalize(AxisX);

	Vec3Cross(AxisY, AxisZ, AxisX);	// Y = Z ^ X

	m[0][0]= AxisX[0];	m[0][1]= AxisY[0];	m[0][2]= AxisZ[0];
	m[1][0]= AxisX[1];	m[1][1]= AxisY[1];	m[1][2]= AxisZ[1];
	m[2][0]= AxisX[2];	m[2][1]= AxisY[2];	m[2][2]= AxisZ[2];

	m[3][0]= -Vec3Dot(Eye, AxisX);
	m[3][1]= -Vec3Dot(Eye, AxisY);
	m[3][2]= -Vec3Dot(Eye, AxisZ);
	m[3][3]= 1.0F;

	memcpy(Out, &m[0][0], sizeof(float)* 16);
}



int CMain::SetupShader()
{
	int hr =0;
	GLint bLinked;

	TLC_ARGS args;

	MAKE_ARG2(args, (UINT)GL_VERTEX_SHADER, (char*)MEDIA_DIR"shader/02sl_vs.glsl");

	hr = LcDev_CreateShaderFromTxtFile(&m_VsShader, &args);
	//hr = LcDev_CreateShaderFromTxtBuffer(&m_VsShader, GL_VERTEX_SHADER  , g_vs);

	if(0>hr)
		return -1;

	MAKE_ARG2(args, (UINT)GL_FRAGMENT_SHADER, (char*)MEDIA_DIR"shader/02sl_fs.glsl");
	hr = LcDev_CreateShaderFromTxtFile(&m_FgShader, &args);
	//hr = LcDev_CreateShaderFromTxtBuffer(&m_FgShader, GL_FRAGMENT_SHADER, g_fs);

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
	LcAux_SetCurrentDir(g_CurrentDir);

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



	static QWORD  startTime = LcAux_TimeGetTime();
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
	glDisable( GL_CULL_FACE );

	glClearColor(0.9f, 1.0f, 1.0f, 1.0f);

	// Clear Color buffer and Depth Buffer.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glUseProgram(m_program);

	INT	nUsWld = glGetUniformLocation(m_program, "um_Wld");
	INT	nUsViw = glGetUniformLocation(m_program, "um_Viw");
	INT	nUsPrj = glGetUniformLocation(m_program, "um_Prj");
	INT	nUiDif = glGetUniformLocation(m_program, "ui_Dif");
	


	LCXMATRIX	mtZ, mtX, mtY;
	LCXMATRIX	m_mtViw;

	LCXVECTOR3	pos(0, 0, 0);


	static int c =0;
	++c;


	mtZ.RotationZ( LCXToRadian((float)(c) ));
	mtX.RotationX( LCXToRadian((float)(c) ));
	mtY.RotationY( LCXToRadian((float)(c) ));
	m_mtWld = mtZ * mtX * mtY;


	MyGluLookAt((float*)&m_mtViw, 0, 20, 40, 0,0,0, 0,1,0);


	// set up projection matrix in 3d pipeline
	float	temp[16]={0};
	float	width, height;
	glGetFloatv(GL_VIEWPORT, temp);		// get viewport to set the screen width and height.
	width = temp[2];
	height= temp[3];
	float	Aspect = (float)width/height;
	float	Near = 1.F;
	float	Far	 = 1000.F;

	MyGluPerspective((float*)&m_mtPrjPers, 45.0F, Aspect, Near, Far);

	
	glUniformMatrix4fv(nUsWld, 1, 0, (GLfloat*)&m_mtWld);
	glUniformMatrix4fv(nUsViw, 1, 0, (GLfloat*)&m_mtViw);
	glUniformMatrix4fv(nUsPrj, 1, 0, (GLfloat*)&m_mtPrjPers);


	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, pCube);

	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, front);
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, back);
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, top);
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, bottom);
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, left);
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, right);

	glDisableVertexAttribArray(0);


	return LC_OK;
}


