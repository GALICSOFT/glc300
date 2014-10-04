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

PLC_TEXTURE	m_pTex = NULL;		// Texture List


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


	// invalid / restore test..
	LcSys_ManagedObjectInvalid();
	LcSys_ManagedObjectRestore();



	LCXCOLOR r(0, .4F, .6F,1);
	m_pDev->SetRenderState(LC_RS_CLEAR_COLOR, &r);

	// Prepare Rendering...
	m_pDev->BeginScene();

	// Clear Backbuffer
	m_pDev->Clear(LC_CLEAR_COLOR_BUFFER | LC_CLEAR_DEPTH_BUFFER);

	LCXMATRIX mtScl;
	mtScl.Identity();
	mtScl.Scaling(2,2,1);

	mtScl._41 = 100;
	//mtScl._42 = 0;

	// Sprite Begin
	m_pSpt->Begin();

	m_pSpt->SetTransform(LC_TM_WORLD, &mtScl);


	LCXMATRIX mtWld;
	LCXMATRIX mtViw;
	LCXMATRIX mtPrj;
	LCXMATRIX mtWVP;

	m_pSpt->GetTransform(LC_TM_WORLD, &mtWld);
	m_pSpt->GetTransform(LC_TM_VIEW, &mtViw);
	m_pSpt->GetTransform(LC_TM_PROJ, &mtPrj);

	mtWVP = mtWld * mtViw * mtPrj;

	LCXVECTOR3 vcPos0(  0,   0, 0);
	LCXVECTOR3 vcPos1(480,   0, 0);
	LCXVECTOR3 vcPos2(480, 320, 0);
	LCXVECTOR3 vcPos3(  0, 320, 0);

	mtWVP.TransformCoord(&vcPos0, &vcPos0);
	mtWVP.TransformCoord(&vcPos1, &vcPos1);
	mtWVP.TransformCoord(&vcPos2, &vcPos2);
	mtWVP.TransformCoord(&vcPos3, &vcPos3);


	LCXVECTOR3	vcTrn(20, 25, 0.0F);
	LCXCOLOR	color(1,1, 0, 1.0F);
	LCXRECT		rc(50,50,300,300);


	//m_pSpt->SetRenderState(LC_RS_DISPLAY_MONO, LC_TRUE);
	m_pSpt->Draw(m_pTex, &rc, &vcTrn, NULL, &color);
	m_pSpt->SetRenderState(LC_RS_DISPLAY_MONO, LC_FALSE);


	// Sprite End
	m_pSpt->End();


	// Post Rendering...
	m_pDev->EndScene();


	return LC_OK;
}



////////////////////////////////////////////////////////////////////////////////
// Main Program
int main(int argc, char* argv[])
{
	TLC_ARGS args;

	INT	hr = 0;


	char sFile [] = MEDIA_DIR"tex/bg512x256.png";

	UINT dColorKey = 0xFF00FFFF;
	UINT Use16 = LC_FMT_W4444;


	// Init GLC Library
	if(LC_FAILED(LcSys_Init()))
		return LC_OK;

	// Set Main procedure Function Pointer
	if(LC_FAILED(LcSys_SetMainRunFunc(Run)))
		goto End;


	// Create Window
	hr = LcSys_CreateWindow(NULL, (char*)"LC_Tutorial", 800, 480);
	if(0 > hr)
		goto End;

	// Create GLC Rendering Device
	if(LC_FAILED(LcDev_CreateDevice(NULL, &m_pDev)))
		goto End;


	// get the default Rendering 2D sprite
	m_pSpt = (PLC_SPRITE)LcVar_ReadP(LC_VAR_SPRITE);


	MAKE_ARG4(args, sFile, Use16, dColorKey, (INT)1);
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
	// Release Texture
	//LC_DestroyTexture(&m_pTex);
	//LcSys_DestroyObject((PLC_OBJECT*)&m_pTex);
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
