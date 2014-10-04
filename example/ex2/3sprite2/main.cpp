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

vector<PLC_TEXTURE > m_vTex;	// Texture List


extern INT Initsimple();
extern void DestroySimple();
extern void DrawSimple();


DOUBLE GetAppFrame();

INT InitMassObj()
{
	TLC_ARGS	args;
	INT			hr = 0;

	PLC_TEXTURE	pTex = NULL;
	UINT		colorKey = 0xFF00FFFF;
	char		sFile[LC_MAX_PATH]={0};
	INT			i;

	sprintf(sFile, (char*)MEDIA_DIR"tex/bg512x256.png");
	MAKE_ARG4(args, sFile, (UINT)0, (UINT)colorKey, (UINT)1);
	hr = LcDev_CreateTextureFromFile(NULL, &pTex, &args);
	if(LC_FAILED(hr))
		return LC_EFAIL;


	m_vTex.push_back(pTex);

	for(i=1;i<10; ++i)
	{
		sprintf(sFile, (char*)MEDIA_DIR"tex/t0%d.tga", i);
		MAKE_ARG4(args, sFile, (UINT)0, (UINT)0, (UINT)1);
		hr = LcDev_CreateTextureFromFile(NULL, &pTex, &args);
		if(LC_FAILED(hr))
			return LC_EFAIL;

		m_vTex.push_back(pTex);
	}

	return LC_OK;
}


void DestroyMassObj()
{	
	// Release Texture
	for(vector<PLC_TEXTURE>::iterator t= m_vTex.begin(); t != m_vTex.end(); ++t)
		(*t)->Release();

	m_vTex.clear();
}


void DrawMassObj()
{
	

	INT zbias = 0;
	zbias = -20;
	m_pSpt->SetRenderState(LC_RS_ZBIAS, zbias);
	m_pSpt->Draw(m_vTex[0], NULL, NULL, NULL);

	zbias = +20;
	m_pSpt->SetRenderState(LC_RS_ZBIAS, zbias);

	LCXRECT		rc;
	LCXVECTOR3	s;
	LCXVECTOR3	r;
	LCXVECTOR3	t;
	LCXCOLOR	d;


	rc = LCXRECT(  0,   0, 128, 128);	LCXRect2Region(&rc); t = LCXVECTOR3( 150, 150, 0);
	m_pSpt->Draw(m_vTex[1], NULL, &t, NULL, NULL);

	rc = LCXRECT(128,   0, 256, 128);	LCXRect2Region(&rc); t = LCXVECTOR3( 200, 100, 0);	d = LCXCOLOR(1,0,0,1);
	m_pSpt->Draw(m_vTex[2], NULL, &t, NULL, &d);

	rc = LCXRECT(  0, 128, 128, 256);	LCXRect2Region(&rc); t = LCXVECTOR3( 310, 138, 0);	d = LCXCOLOR(0,1,0,1);
	m_pSpt->Draw(m_vTex[3], NULL, &t, NULL, &d);

	rc = LCXRECT(128, 128, 256, 256);	LCXRect2Region(&rc); t = LCXVECTOR3( 438, 138, 0);	d = LCXCOLOR(0,0,1,1);
	m_pSpt->Draw(m_vTex[4], NULL, &t, NULL, &d);


	m_pSpt->SetRenderState(LC_CLEAR_DEPTH_BUFFER);	// same device::Clear(LC_CLEAR_DEPTH_BUFFER);


	for(INT i=5; i<10; ++i)
	{
		FLOAT X = FLOAT(rand()%320)-60;
		FLOAT Y = FLOAT(rand()%240)-60;

		t = LCXVECTOR3(X, Y, 0);
		m_pSpt->Draw(m_vTex[i], NULL, &t, NULL);
	}


	static INT cc=0;
	++cc;

	float a = LCXToRadian(cc*2.F);

	FLOAT w = (FLOAT)m_vTex[9]->ImgW();
	FLOAT h = (FLOAT)m_vTex[9]->ImgH();

	rc  = LCXRECT(w, 0, -w, h);
	s	= LCXVECTOR3( 2.f, 2.f, 1.0f);
	t	= LCXVECTOR3(100, 100, 0.0F);

	r	= t + LCXVECTOR3( fabsf(w)* s.x, fabs(h)*s.y, 0.0F) * 0.5F;

	d	= LCXCOLOR(0,1,1,0.5f);

	zbias = -40;
	m_pSpt->SetRenderState(LC_RS_ZBIAS, zbias);
	m_pSpt->DrawEx(m_vTex[9], &rc, &t, &s, &r, a, &d);
	zbias = +40;
	m_pSpt->SetRenderState(LC_RS_ZBIAS, zbias);


	// Sprite End
	m_pSpt->DrawFlush();
}


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

	static INT n=0;
	++n;

	if(n>5)
	{
		printf("%f\n", fFrame);
		n = 0;
	}


	// Prepare Rendering...
	m_pDev->BeginScene();

	// Clear Backbuffer
	m_pDev->Clear(LC_CLEAR_COLOR_BUFFER | LC_CLEAR_DEPTH_BUFFER);

	// Sprite Begin
	m_pSpt->Begin();


//	m_pSpt->SetRenderState(LC_RS_DISPLAY_MONO, LC_TRUE);

	DrawMassObj();

	m_pSpt->SetRenderState(LC_RS_DISPLAY_MONO, LC_FALSE);

	DrawSimple();

	m_pSpt->End();


	// Post Rendering...
	m_pDev->EndScene();


	return LC_OK;
}




// Main Program
int main(int argc, char* argv[])
{
	INT		hr = 0;
	UINT	dClearColor = 0xFF006699;
	INT		spt_type = 0;

	spt_type = LC_OBJ_MODEL2D;		// sprite for model coordinate
	spt_type = LC_OBJ_GUI;			// sprite for gui coordinate


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


	if(LC_FAILED(InitMassObj() ))
		goto End;

	if(LC_FAILED(Initsimple() ))
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
	DestroyMassObj();
	DestroySimple();


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

