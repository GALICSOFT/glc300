// Implementation of the CMain class.
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
}


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

	char* attlist[] ={"at_pos", NULL};

	MAKE_ARG3(args, (char*)MEDIA_DIR"shader/05sl_vs.glsl", (char*)MEDIA_DIR"shader/05sl_fs.glsl", (char**)attlist);

	hr = LcDev_CreateEffectFromTxtFile(NULL, &m_pEft, m_pDev, &args);
	if(LC_FAILED(hr))
		return LC_EFAIL;


	return LC_OK;
}



int	CMain::Destroy()
{
	SAFE_RELEASE(	m_pEft	);

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


	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, pCube);


	//m_pEft->Float4("uv_Dif", 1,0,0,1);	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, front);
	//m_pEft->Float4("uv_Dif", 0,1,0,1);	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, back);
	//m_pEft->Float4("uv_Dif", 0,0,1,1);	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, top);
	//m_pEft->Float4("uv_Dif", 1,1,0,1);	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, bottom);
	//m_pEft->Float4("uv_Dif", 0,1,1,1);	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, left);
	//m_pEft->Float4("uv_Dif", 1,0,1,1);	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, right);


	LCXCOLOR v1(1,0,0,1);
	LCXCOLOR v2(0,1,0,1);
	LCXCOLOR v3(0,0,1,1);
	LCXCOLOR v4(1,1,0,1);
	LCXCOLOR v5(0,1,1,1);
	LCXCOLOR v6(1,0,1,1);


	m_pEft->Color("uv_Dif", &v1);	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, front);
	m_pEft->Color("uv_Dif", &v2);	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, back);
	m_pEft->Color("uv_Dif", &v3);	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, top);
	m_pEft->Color("uv_Dif", &v4);	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, bottom);
	m_pEft->Color("uv_Dif", &v5);	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, left);
	m_pEft->Color("uv_Dif", &v6);	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, right);

	glDisableVertexAttribArray(0);

	m_pEft->End();

	return LC_OK;
}


