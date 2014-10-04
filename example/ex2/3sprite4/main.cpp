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
#include <stdlib.h>
#include <string.h>

#include <LcType.h>
#include <LcBase.h>
#include <LcMath.h>
#include <LcEuclid.h>
#include <LcCore.h>
#include <LcAux.h>


#define MEDIA_DIR	"../../media/"



PLC_DEVICE	m_pDev	= NULL;		// Device
PLC_SPRITE	m_pSpt	= NULL;		// 2D Sprite

PLC_TEXTURE	m_pTex	= NULL;		// Texture List


DOUBLE GetAppFrame();


INT LC_CALLBACK Run(LC_HANDLE)
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


	FLOAT fFrame = (FLOAT)GetAppFrame();


	static INT n=0;
	++n;

	if(n>5)
	{
		printf("%f\n", fFrame);
		n = 0;
	}


	struct AniSeq
	{
		float	x, y, w, h, oX, oY;		// x, y, width,height, offset x, offset y
	};

	AniSeq sq[]=
	{
		{	269,   1,  90, 153,	   3,	63.5},
		{	360,   1, 110, 152,	  13,	63  },
		{	  0, 201, 103, 152,	 9.5,	63  },
		{	197, 201,  91, 151,	 3.5,	62.5},
		{	394, 201, 115, 147,	15.5,	60.5},

		{	289, 201, 104, 148,	10	,	61  },
	};

	// Prepare Rendering...
	m_pDev->BeginScene();

	// Clear Backbuffer
	m_pDev->Clear(LC_CLEAR_COLOR_BUFFER | LC_CLEAR_DEPTH_BUFFER);

	// Sprite Begin
	m_pSpt->Begin();

	static int		Idx = 0;
	static QWORD	dBgn = LcAux_TimeGetTime();
	QWORD			dCur = LcAux_TimeGetTime();


	if(dCur-dBgn>67)
	{
		++Idx;
		Idx %= 6;

		dBgn = dCur;
	}

	LCXRECT		rc(sq[Idx].x, sq[Idx].y, sq[Idx].w, sq[Idx].h);

	LCXVECTOR3	vcDelta=  LCXVECTOR3(-sq[Idx].w*.5F, -sq[Idx].h*.5F, 0.0F)
						+ LCXVECTOR3(sq[Idx].oX    , -sq[Idx].oY   , 0.0F );


	LCXVECTOR3	vcpos;
	LCXVECTOR3	vcScl = LCXVECTOR3(1.06F, 1.06F, 1.0F);
	LCXCOLOR	df(1.0F, 0.0F, 1.0F, 1.0F);

	vcpos =  LCXVECTOR3(160.0F, 200.0F, 0.0F) + vcDelta - LCXVECTOR3( 3.0F, 3.0F, 0.0F);

	m_pSpt->SetRenderState(LC_RS_DISPLAY_MONO, LC_TRUE);

	m_pSpt->Draw(m_pTex, &rc, &vcpos, &vcScl, &df);

	m_pSpt->SetRenderState(LC_RS_DISPLAY_MONO, LC_FALSE);

	vcpos = LCXVECTOR3(160, 200, 0.0F) + vcDelta;
	m_pSpt->Draw(m_pTex, &rc, &vcpos, NULL);

	// Sprite End
	m_pSpt->End();


	// Post Rendering...
	m_pDev->EndScene();


	return LC_OK;
}




// Main Program
int main(int argc, char* argv[])
{
	TLC_ARGS args;

	INT		hr = 0;

	UINT	dClearColor = 0xFF006699;

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


	printf("LcDev_CreateDevice Success\n");


	// Set Clear Color
	m_pDev->SetRenderState(LC_RS_CLEAR_COLOR, dClearColor);


	// get the default Rendering 2D sprite
	m_pSpt = (PLC_SPRITE)LcVar_ReadP(LC_VAR_SPRITE);


	MAKE_ARG4(args, (char*)MEDIA_DIR"model2d/character02.png", (UINT)0, (UINT)0, (UINT)1);
	if(LC_FAILED(LcDev_CreateTextureFromFile(NULL, &m_pTex, &args)))
		goto End;


	printf("LcDev_CreateTextureFromFile Success\n");


	// Run Program
	while(1)
	{
		if(LC_FAILED(LcSys_Run()))
			break;

		// Flipping
		m_pDev->Present(0,0,0,0);
	}


End:
	m_pTex->Release();
	

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
	static INT		MaxCount = 60;
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
