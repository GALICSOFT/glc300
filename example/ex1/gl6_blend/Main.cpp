// Implementation of the CMain class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


static char g_CurrentDir[260]={0};



#define MEDIA_DIR	"../../media/"


CMain::CMain()
{
	LcAux_GetCurrentDir( g_CurrentDir, 260);

	m_pEft = NULL;

	m_pTex = NULL;
}


int	CMain::Init()
{
	int hr =0;

	LcAux_SetCurrentDir( g_CurrentDir);


	m_mtViw.Identity();
//	LCXVECTOR3	eye(0, 40, 20);
//	LCXVECTOR3	look(0,0,0);
//	LCXVECTOR3	up(0,0,1);
//	m_mtViw.View3DMax(&eye, &look, &up, LC_TRUE);


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

	char* attlist[] = {"at_pos", "at_tex", NULL};
	MAKE_ARG3(args, (char*)MEDIA_DIR"shader/13sl_vs.glsl", (char*)MEDIA_DIR"shader/13sl_fs.glsl", (char**)attlist);
	hr = LcDev_CreateEffectFromTxtFile(NULL, &m_pEft, m_pDev, &args);
	if(LC_FAILED(hr))
		return LC_EFAIL;


	m_pEft->Owner(this);


	// texture 0
	MAKE_ARG4(args, (char*)(MEDIA_DIR"tex/star128.tga"), 0, 0, (INT)1);

	hr = LcDev_CreateTextureFromFile(NULL, &m_pTex, &args);
	if(LC_FAILED(hr))
		return LC_EFAIL;



	// Create Particle
	for(int n=0; n<MAX_STAR_NUM; ++n)
	{
		m_pStar[n].angle= n /float(MAX_STAR_NUM-1) * 720.F;
		m_pStar[n].dist=((float)n/MAX_STAR_NUM)* 5.0f;
		m_pStar[n].r = (rand() % 256 )/255.F;
		m_pStar[n].g = (rand() % 256 )/255.F;
		m_pStar[n].b = (rand() % 256 )/255.F;
		m_pStar[n].radius = float(100 + rand() % 101) *  0.015f;
	}

	return LC_OK;
}


int	CMain::Destroy()
{
	m_pEft->Owner(NULL);
	SAFE_RELEASE(	m_pEft	);

	SAFE_RELEASE(	m_pTex	);

	return LC_OK;
}

int	CMain::FrameMove()
{
#if defined(_WIN32)
	LcAux_Sleep(20);
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
	glDisable( GL_DEPTH_TEST);
	glDisable( GL_CULL_FACE );

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);




	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);


	static float spin=0;

	float texcoords[4][2];
	float vertices[4][3];




	m_pEft->Begin();

	m_pEft->Matrix4("um_Viw", &m_mtViw);
	m_pEft->Matrix4("um_Prj", &m_mtPrj);

	m_pEft->Texture("uf_tex", 0, m_pTex);


	glEnableVertexAttribArray(0);	glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, vertices);
	glEnableVertexAttribArray(1);	glVertexAttribPointer(1, 2, GL_FLOAT, 0, 0, texcoords);


	m_pTex->BindTexture(0, LC_TRUE, GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT);

	glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);


	for(int n=0; n<MAX_STAR_NUM; n++)
	{
		LCXMATRIX	mtWld;

		LCXMATRIX mtTn1; mtTn1.Translation(0.0f, 0.0f, -12);

		LCXMATRIX mtX1;  mtX1.RotationX( LCXToRadian(90));
		LCXMATRIX mtY1;  mtY1.RotationY( LCXToRadian(m_pStar[n].angle));

		LCXMATRIX mtTn2; mtTn2.Translation(m_pStar[n].dist, 0.0f, 0.0f);
		LCXMATRIX mtY2;  mtY2.RotationY( LCXToRadian(-m_pStar[n].angle));
		LCXMATRIX mtX2;  mtX2.RotationX( LCXToRadian(-90));
		LCXMATRIX mtZ2;  mtZ2.RotationZ( LCXToRadian(spin));

		mtWld = mtTn1 * mtX1 * mtY1 * mtTn2 * mtY2 * mtX2 * mtZ2;

		m_pEft->Matrix4("um_Wld", &mtWld);
		m_pEft->Float4 ("uf_dif", m_pStar[n].r, m_pStar[n].g, m_pStar[n].b, 1.0f);
		m_pEft->Float  ("uv_scl", m_pStar[n].radius);

		texcoords[0][0]=0.0f; texcoords[0][1]=0.0f;		vertices[0][0]=-1.0f; vertices[0][1]=-1.0f; vertices[0][2]=0.0f;
		texcoords[1][0]=1.0f; texcoords[1][1]=0.0f;		vertices[1][0]= 1.0f; vertices[1][1]=-1.0f; vertices[1][2]=0.0f;
		texcoords[2][0]=1.0f; texcoords[2][1]=1.0f;		vertices[2][0]= 1.0f; vertices[2][1]= 1.0f; vertices[2][2]=0.0f;
		texcoords[3][0]=0.0f; texcoords[3][1]=1.0f;		vertices[3][0]=-1.0f; vertices[3][1]= 1.0f; vertices[3][2]=0.0f;


		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);


		spin+=0.02f;

		m_pStar[n].angle+=(float)n/MAX_STAR_NUM;

		m_pStar[n].dist-=0.01f;


		if (m_pStar[n].dist<0.0f)
		{
			m_pStar[n].dist+=5.0f;
			m_pStar[n].r= (rand()%256)/255.F;
			m_pStar[n].g= (rand()%256)/255.F;
			m_pStar[n].b= (rand()%256)/255.F;
		}
	}





	// Unbinding texture...
	m_pTex->BindTexture(0, 0);


	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	m_pEft->End();


	return LC_OK;
}



