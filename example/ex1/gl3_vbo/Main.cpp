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
	{
		glGenBuffers(1, &m_Vtx);


		// VBO binding 시작
		glBindBuffer(GL_ARRAY_BUFFER,m_Vtx);

		// 시스템 메모리에 저장된 정점 데이터를 VBO에 binding
		glBufferData(GL_ARRAY_BUFFER, sizeof(vtx_src), vtx_src, GL_STATIC_DRAW);


		// 정점 데이터가 VBO에 설정되어 있어서 malloc, new로 생성된 메모리를
		// 여기서 release해도 된다.
		// 정점 버퍼 release...
		//

		// VBO binding release
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}


	////////////////////////////////////////////////////////////////////////////
	// IBO(Index Buffer Object) 생성 <- IBO도 VBO 임. 구분을 위해서 임으로 이름을 정함.
	{
		// 6면에 대한 IBO 6 개를 생성
		glGenBuffers(6, &m_Idx[0]);


		// IBO와 인덱스 데이터 binding
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Idx[0]);	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(front ), front , GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Idx[1]);	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(back  ), back  , GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Idx[2]);	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(top   ), top   , GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Idx[3]);	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(bottom), bottom, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Idx[4]);	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(left  ), left  , GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Idx[5]);	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(right ), right , GL_STATIC_DRAW);

		// IBO binding release
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}


	return LC_OK;
}

int	CMain::Destroy()
{
	// VBO release
	if(m_Vtx)
	{
		glDeleteBuffers(1, &m_Vtx);
		m_Vtx =0;
	}

	// IBO release
	if(m_Idx[0])
	{
		glDeleteBuffers(6, &m_Idx[0]);
		memset(m_Idx, 0, 6 * sizeof(LC_IB) );
	}


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


int	CMain::Render()
{
	glEnable( GL_DEPTH_TEST);
	glDisable( GL_CULL_FACE );

	glClearColor(0.9f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	static int c =0;
	++c;

	LCXMATRIX	mtZ, mtX, mtY;
	mtZ.RotationZ( LCXToRadian((float)(c*2) ));
	mtX.RotationX( LCXToRadian((float)(c) ));
	mtY.RotationY( LCXToRadian((float)(c) ));
	m_mtWld = mtZ * mtX * mtY;



	m_pEft->Begin();

	m_pEft->Matrix4("um_Wld", &m_mtWld);
	m_pEft->Matrix4("um_Viw", &m_mtViw);
	m_pEft->Matrix4("um_Prj", &m_mtPrj);

	int stride = sizeof(float) * 3 + sizeof(unsigned char)*4;	// position(float3) + color(byte4)
	int offset = 0;


	// the integer stream needs normalize in glVertexAttribPointer.
	glBindBuffer(GL_ARRAY_BUFFER, m_Vtx);
	glEnableVertexAttribArray(0);	glVertexAttribPointer(0, 3, GL_FLOAT        , GL_FALSE, stride, (void*)offset); offset += sizeof(float) * 3;
	glEnableVertexAttribArray(1);	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE , stride, (void*)offset);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Idx[0]);	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Idx[1]);	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Idx[2]);	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Idx[3]);	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Idx[4]);	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Idx[5]);	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, 0);

	// bind 0
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	m_pEft->End();

	return LC_OK;
}


