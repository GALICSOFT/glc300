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


#define MEDIA_DIR	"../../media/"


PLC_DEVICE	m_pDev	= NULL;		// Device
PLC_SPRITE	m_pSpt	= NULL;		// 2D Sprite

PLC_TEXTURE	m_pTex1 = NULL;		// Texture 1
PLC_TEXTURE	m_pTex2 = NULL;		// Texture 2
PLC_TEXTURE	m_pTexR = NULL;		// Texture 3

INT				g_ImgW = 480;
INT				g_ImgH = 320;


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

	LCXCOLOR r(0,0,1,1);
	m_pDev->SetRenderState(LC_RS_CLEAR_COLOR, &r);



	////////////////////////////////////////////////////////////////////////////
	// Rendering to Frame Buffer Process



	m_pDev->BeginScene();			// Prepare Rendering...
	m_pDev->Clear(LC_CLEAR_COLOR_BUFFER | LC_CLEAR_DEPTH_BUFFER);	// Clear Backbuffer



	static int angle = 0;
	LCXVECTOR3 pos(260, 260, 0);
	LCXVECTOR3 rot(320/2.F, 240/2.F, 0);
	LCXVECTOR3 scl(4.0F, 4.0F, 1.0F);
	float fRad = 0;

	LCXCOLOR color(1,1,1, (float)(cos(fRad) * cos(fRad)));


	++angle;
	fRad = LCXToRadian(angle);


	m_pSpt->Begin();


	TLC_VIEWPORT vptOld;

	TLC_VIEWPORT vptNew = {0.0F,0.0F, (FLOAT)g_ImgW, (FLOAT)g_ImgH, 0.0F, 1.0F};

	m_pDev->GetRenderState(LC_RS_VIEWPORT, &vptOld);	// save the current viewport
	m_pDev->SetRenderState(LC_RS_VIEWPORT, &vptNew);	// replace to new viewpoirt

	m_pSpt->Draw(m_pTex1, NULL, NULL, &scl);
	m_pSpt->DrawEx(m_pTex2, NULL, &pos, &scl, &rot, fRad, &color);


	m_pDev->SetRenderState(LC_RS_VIEWPORT, &vptOld);	// restore current viewport
	m_pSpt->End();										// Sprite End
	m_pDev->EndScene();									// Post Rendering...


	////////////////////////////////////////////////////////////////////////////
	// Copy From Frame Buffer

	m_pTexR->CopyTexImage2D();



	////////////////////////////////////////////////////////////////////////////
	// Rendering to Frame Buffer with saved pixel from framebuffer


	m_pDev->BeginScene();			// Prepare Rendering...
	m_pDev->Clear(LC_CLEAR_COLOR_BUFFER | LC_CLEAR_DEPTH_BUFFER);	// Clear Backbuffer



	m_pSpt->Begin();


	for(int i=10; i>=0; --i)
	{
		scl = LCXVECTOR3( i/10.F, i/10.F, 1.0F);
		pos = LCXVECTOR3( (10-i)*16.0F, (10-i)* 12.0F, 0.0F);
		m_pSpt->DrawEx(m_pTexR, NULL, &pos, &scl, NULL, 0.0F, &LCXCOLOR(1.0F, 1.0F, 1.0F, i/10.F));
	}

	m_pSpt->End();						// Sprite End
	m_pDev->EndScene();						// Post Rendering...


	return LC_OK;
}




// Main Program
int main(int argc, char* argv[])
{
	TLC_ARGS args;

	int	hr = 0;

	char sFile1 [] = MEDIA_DIR"tex/bg256x256x256.bmp";
	char sFile2 [] = MEDIA_DIR"tex/fire128.tga";

	TDSC_IMAGE	t=
	{
		  LC_FMT_RGB
		, LC_FMT_UBYTE
		, g_ImgW
		, g_ImgH
	};

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


	// get the default Rendering 2D sprite
	m_pSpt = (PLC_SPRITE)LcVar_ReadP(LC_VAR_SPRITE);



	MAKE_ARG4(args, sFile1, (UINT)0, (UINT)0, (UINT)1);
	if(LC_FAILED(LcDev_CreateTextureFromFile(NULL, &m_pTex1, &args)))
		goto End;


	MAKE_ARG4(args, sFile2, (UINT)0, (UINT)0, (UINT)1);
	if(LC_FAILED(LcDev_CreateTextureFromFile(NULL, &m_pTex2, &args)))
		goto End;


	// for rendering copy texture
	MAKE_ARG2(args, g_ImgW, g_ImgH);
	if(LC_FAILED(LcDev_CreateTextureTarget(NULL, &m_pTexR, &args)))
		goto End;



	printf("LcDev_CreateTexture Success\n");


	// Run Program
	while(1)
	{
		if(LC_FAILED(LcSys_Run()))
			break;

		// Flipping
		m_pDev->Present(0,0,0,0);
	}


End:
	// Release Texture
	m_pTex1->Release();
	m_pTex2->Release();
	m_pTexR->Release();

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
