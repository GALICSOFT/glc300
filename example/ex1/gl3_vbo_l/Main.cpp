// Implementation of the CMain class.
//
// VBO와 관련된 함수
//
//	- glBindBuffer
//	- glBufferData
//	- glBufferSubData
//	- glDeleteBuffers
//	- glGenBuffers
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"

#define MEDIA_DIR	"../../media/"


static char g_CurrentDir[260]={0};



CMain::CMain()
{
	LcAux_GetCurrentDir( g_CurrentDir, 260);

	m_mtWld.Identity();
	m_mtViw.Identity();
	m_mtPrj.Identity();

	m_pEft = NULL;
	m_pVB  = NULL;

	for(int n=0; n<6; ++n)
		m_pIB[n] =  NULL;
}



// 정점 데이터(position(float3) + color(byte4:rgba))
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


// Index 데이터
WORD front [] = {2,1,3,0};	// front face
WORD back  [] = {5,6,4,7};	// back face
WORD top   [] = {6,2,7,3};	// top face
WORD bottom[] = {1,5,0,4};	// bottom face
WORD left  [] = {3,0,7,4};	// left face
WORD right [] = {6,5,2,1};	// right face



int	CMain::Init()
{
	int hr =0;

	LcAux_SetCurrentDir( g_CurrentDir);


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
	m_mtPrj.PerspectiveD3dRH( LCXToRadian(45.F), Aspect, Near, Far);


	TLC_ARGS args;


	char* attlist[] ={"at_pos", "at_dif", NULL};
	MAKE_ARG3(args, (char*)MEDIA_DIR"shader/06sl_vs.glsl", (char*)MEDIA_DIR"shader/06sl_fs.glsl", (char**)attlist);

	hr = LcDev_CreateEffectFromTxtFile(NULL, &m_pEft, m_pDev, &args);
	if(LC_FAILED(hr))
		return LC_EFAIL;



	////////////////////////////////////////////////////////////////////////////
	// VBO(Vertex Buffer Object) 1개를 생성

	MAKE_ARG3(args, (UINT)(LC_FVF_XYZ|LC_FVF_DIFFUSE), (char*)vtx_src, (int)sizeof(vtx_src));

	hr = LcDev_CreateVB(NULL, &m_pVB, &args);
	if(LC_FAILED(hr))
		return LC_EFAIL;


	////////////////////////////////////////////////////////////////////////////
	// IBO(Index Buffer Object) 생성

	MAKE_ARG3(args, (UINT)LC_FMT_WORD, (char*)front , (int)sizeof(front ));	hr = LcDev_CreateIB(NULL, &m_pIB[0], &args);
	MAKE_ARG3(args, (UINT)LC_FMT_WORD, (char*)back  , (int)sizeof(back  ));	hr = LcDev_CreateIB(NULL, &m_pIB[1], &args);
	MAKE_ARG3(args, (UINT)LC_FMT_WORD, (char*)top   , (int)sizeof(top   ));	hr = LcDev_CreateIB(NULL, &m_pIB[2], &args);
	MAKE_ARG3(args, (UINT)LC_FMT_WORD, (char*)bottom, (int)sizeof(bottom));	hr = LcDev_CreateIB(NULL, &m_pIB[3], &args);
	MAKE_ARG3(args, (UINT)LC_FMT_WORD, (char*)left  , (int)sizeof(left  ));	hr = LcDev_CreateIB(NULL, &m_pIB[4], &args);
	MAKE_ARG3(args, (UINT)LC_FMT_WORD, (char*)right , (int)sizeof(right ));	hr = LcDev_CreateIB(NULL, &m_pIB[5], &args);

	return LC_OK;
}


int	CMain::Destroy()
{
	SAFE_RELEASE(	m_pEft	);
	SAFE_RELEASE(	m_pVB	);

	for(int n=0; n<6; ++n)
	{
		SAFE_RELEASE(	m_pIB[n]	);
	}
	

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

	return LC_OK;
}


int	CMain::Render()
{
	glEnable( GL_DEPTH_TEST);
	glDisable( GL_CULL_FACE );

	glClearColor(0.9f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	static int c =0;
	++c;

	LCXMATRIX	mtZ, mtX, mtY;
	mtZ.RotationZ( LCXToRadian((float)(c) ));
	mtX.RotationX( LCXToRadian((float)(c) ));
	mtY.RotationY( LCXToRadian((float)(c) ));
	m_mtWld = mtZ * mtX * mtY;



	m_pEft->Begin();

	m_pEft->Matrix4("um_Wld", &m_mtWld);
	m_pEft->Matrix4("um_Viw", &m_mtViw);
	m_pEft->Matrix4("um_Prj", &m_mtPrj);


	int stride = m_pVB->Stride();
	int offset = 0;

	m_pVB->Bind();

	offset = m_pVB->Offset(LC_FVF_XYZ);
	if(0<=offset)
	{
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)offset);
	}

	offset = m_pVB->Offset(LC_FVF_DIFFUSE);
	if(0<=offset)
	{
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, stride, (void*)offset);
	}

	m_pEft->Float4("uv_Dif", 1,0,0,1);	m_pIB[0]->Bind();	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, 0);	m_pIB[0]->Bind(0);
	m_pEft->Float4("uv_Dif", 0,1,0,1);	m_pIB[1]->Bind();	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, 0);	m_pIB[1]->Bind(0);
	m_pEft->Float4("uv_Dif", 0,0,1,1);	m_pIB[2]->Bind();	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, 0);	m_pIB[2]->Bind(0);
	m_pEft->Float4("uv_Dif", 1,1,0,1);	m_pIB[3]->Bind();	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, 0);	m_pIB[3]->Bind(0);
	m_pEft->Float4("uv_Dif", 0,1,1,1);	m_pIB[4]->Bind();	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, 0);	m_pIB[4]->Bind(0);
	m_pEft->Float4("uv_Dif", 1,0,1,1);	m_pIB[5]->Bind();	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, 0);	m_pIB[5]->Bind(0);

	// bind 0
	m_pVB->Bind(0);

	glDisableVertexAttribArray(0);

	m_pEft->End();

	return LC_OK;
}


