//
//
//
////////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER) && _MSC_VER >= 1200
  #pragma warning( disable : 4786)
  #pragma warning( disable : 4996)
#endif


#if defined(_MSC_VER)
  #pragma comment(linker, "/subsystem:console")
  #pragma comment(lib, "lgpwn_a30_.lib")
  #pragma comment(lib, "lgpwn_b30_.lib")
  #pragma comment(lib, "lgpwn_c30_.lib")
  #pragma comment(lib, "lgpwn_d30_.lib")
  #pragma comment(lib, "lgpwn_i30_.lib")
  #pragma comment(lib, "lgpwn_n30_.lib")
  #pragma comment(lib, "lgpwn_e30_.lib")

  #pragma comment(lib, "OpenGL32.lib")
  #pragma comment(lib, "Imm32.lib")
  #pragma comment(lib, "winmm.lib")
  #pragma comment(lib, "dxguid.lib")
  #pragma comment(lib, "ws2_32.lib")
#endif


#include <vector>
using namespace std;


#include <stdio.h>

#include <LcType.h>
#include <LcBase.h>
#include <LcMath.h>
#include <LcEuclid.h>
#include <LcCore.h>
#include <LcAux.h>
#include <LcStdev.h>
#include <LcxEntity.h>
#include <LcxMedia.h>


PLC_DEVICE	m_pDev	= NULL;		// Device
PLC_SPRITE	m_pSpt	= NULL;		// 2D Sprite

PLCX_INPUT		m_pInput;		// Input

LCXVECTOR3		m_rec0[90];
LCXVECTOR3		m_rec1[5];

INT				m_bCollision;


DOUBLE GetAppFrame();



void InitGame()
{
	if(LC_FAILED(LcxEnt_CreateInput(NULL, &m_pInput)))
		return;


	int i = 0;

	// Setup Vertex buffer for Object1

	FLOAT a = 12;
	FLOAT b =  7;

	for(i=0; i<90; ++i)
	{
		FLOAT	fRadian = -LCXToRadian(i*4);
		FLOAT	fCos    = LCXMathCos(fRadian);
		FLOAT	fSin	= LCXMathSin(fRadian);

		m_rec0[i] = LCXVECTOR3(a*fCos, b*fSin, 0.0F) * 20;
		m_rec0[i]+= LCXVECTOR3( +310, +300, 0.0F);
		m_rec0[i] *= 0.7F;
	}


	m_rec1[0] = LCXVECTOR3( 320, -220, 0.0F) + LCXVECTOR3( +300, +300, 0.0F);
	m_rec1[1] = LCXVECTOR3( 230,   80, 0.0F) + LCXVECTOR3( +300, +300, 0.0F);
	m_rec1[2] = LCXVECTOR3( 560,  240, 0.0F) + LCXVECTOR3( +300, +300, 0.0F);
	m_rec1[3] = LCXVECTOR3( 700, -140, 0.0F) + LCXVECTOR3( +300, +300, 0.0F);
	m_rec1[4] = LCXVECTOR3( 600, -270, 0.0F) + LCXVECTOR3( +300, +300, 0.0F);

	


	for(i=0; i<5; ++i)
		m_rec1[i] *= 0.7F;
}


// Main Loop
INT LC_CALLBACK Run(LC_HANDLE)
{
#if defined(_WIN32)
	LcAux_Sleep(10);
#endif


	static INT c=0;
	++c;

//	if(c>20*60*20)
	if(c>8*60*20)
	{
		printf("Game Process Terminated\n");
		return LC_EFAIL;
	}



	FLOAT fFrame = (FLOAT)GetAppFrame();


	// Input Update
	m_pInput->Update();

	const BYTE*	pKey = m_pInput->KeyMap();
	const BYTE*	pMts = m_pInput->MtsMap();

	if(pKey[LCIK_ESCAPE])
		return LC_EFAIL;


	// Move, Rotation Speed
	FLOAT speed = 2.0f;


	int i = 0;
	if(pKey[LCIK_LEFT])
	{
		for(i=0; i<90; ++i)
		m_rec0[i].x -= speed;
	}

	if(pKey[LCIK_RIGHT])
	{
		for(i=0; i<90; ++i)
		m_rec0[i].x += speed;
	}

	if(pKey[LCIK_UP])
	{
		for(i=0; i<90; ++i)
		m_rec0[i].y -= speed;
	}

	if(pKey[LCIK_DOWN])
	{
		for(i=0; i<90; ++i)
		m_rec0[i].y += speed;
	}


	// Prepare Rendering...
	m_pDev->BeginScene();

	// Clear Backbuffer
	m_pDev->Clear(LC_CLEAR_COLOR_BUFFER | LC_CLEAR_DEPTH_BUFFER);


	//LCXMATRIX	mtWld;
	//mtWld.Scaling(0.3F, 0.3F, 1.0F);
	//m_pSpt->SetTransform(LC_TM_WORLD, &mtWld);


	// Sprite Begin
	m_pSpt->Begin();


	m_bCollision =(0 <= LCXCollisionOBB2D((LCXVECTOR2*)m_rec0, sizeof(LCXVECTOR3), 90
										, (LCXVECTOR2*)m_rec1, sizeof(LCXVECTOR3),  5
											)
					);

	LCXCOLOR col(1,1,1,1);

	col = (m_bCollision)? LCXCOLOR(1,0,1,1) : LCXCOLOR(0.5F, 0, 0.5F, 1);
	m_pSpt->DrawLine(LC_PT_LINE_LOOP, m_rec0, 20.0F, &col, 90);

	col = (m_bCollision)? LCXCOLOR(0,1,1,1) : LCXCOLOR(0, 0.5F, 0.5F, 1);
	m_pSpt->DrawLine(LC_PT_LINE_LOOP, m_rec1, 20.0F, &col, 5);


	LCXVECTOR3	pos(350, 300, 0);
	FLOAT		rcW = 150;
	FLOAT		rcH = 100;
	col = LCXCOLOR(0.8F, 0.8F, 0, 1.0f);
	m_pSpt->DrawRect(&pos, rcW, rcH, 40.0F, &col);


	LCXVECTOR3	center(600, 300, 0.0F);
	FLOAT	rA = 100;
	FLOAT	rB = 200;
	col		= LCXCOLOR(0, 0.8F, 0.4F, 1.0F);

	m_pSpt->DrawEllipsoid(&center, rA, rB, 20.0F, &col);


	// Sprite End
	m_pSpt->End();


	// Post Rendering...
	m_pDev->EndScene();

	return LC_OK;
}



// Main Program
int main(int argc, char* argv[])
{
	int		hr = 0;


	// Init GLC Library
	if(LC_FAILED(LcSys_Init()))
		return LC_OK;

	// Set Main procedure Function Pointer
	if(LC_FAILED(LcSys_SetMainRunFunc(Run)))
		goto End;


	// Create Window
	hr = LcSys_CreateWindow(NULL, (char*)"LC_Tutorial");
	if(0 > hr)
		goto End;

	// Create GLC Rendering Device
	if(LC_FAILED(LcDev_CreateDevice(NULL, &m_pDev)))
		goto End;

	// Set Clear Color
	m_pDev->SetRenderState(LC_RS_CLEAR_COLOR, (UINT)0xFF006699);



	// get the default Rendering 2D sprite
	m_pSpt = (PLC_SPRITE)LcVar_ReadP(LC_VAR_SPRITE);


	InitGame();


	// Run Program
	while(1)
	{
		if(LC_FAILED(LcSys_Run()))
			break;

		// Flipping
		m_pDev->Present(0,0,0,0);
	}


//	free(buf);

End:

	// Release Device
	SAFE_RELEASE( m_pDev );

	// Release Window
	LcSys_DestroyWindow();

	// Release GLC
	LcSys_Close();

	hr = LcVar_RefCountObject();
	if(0 == hr)
		printf(
				"Remain: %d\n"
				"release success.\n"
				, hr
				);
	else
		printf(
				"Remain: %d\n"
				"The non-zero reference count means that\n"
				"there is something object not cleaned up.\n"
				, hr
				);

	return LC_OK;

}


DOUBLE GetAppFrame()
{
#if defined(_WIN32)
	static INT		MaxCount = 10;
#else
	static INT		MaxCount = 10;
#endif

	static DOUBLE	fFps = 0.;
	static INT		iCnt = 0;
	static DINT		dBgn = ::LcAux_TimeGetTime();
	DINT			dCur = ::LcAux_TimeGetTime();

	++iCnt;

	if(iCnt>=MaxCount)
	{
		fFps = DOUBLE(dCur-dBgn);
		fFps = iCnt*1000./fFps;
		iCnt = 0;
		dBgn = dCur;
	}

	return fFps;
}

