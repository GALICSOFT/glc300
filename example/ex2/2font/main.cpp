//
//
//
////////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER) && _MSC_VER >= 1200
  #pragma warning( disable : 4005)
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


#define _CRTDBG_MAP_ALLOC

#include <crtdbg.h>
#include <stdlib.h>

#include <stdio.h>

#include <LcType.h>
#include <LcBase.h>
#include <LcMath.h>
#include <LcEuclid.h>
#include <LcCore.h>
#include <LcAux.h>
#include <LcxEntity.h>
#include <LctEntity.h>


#define MEDIA_DIR	"../../media/"
#define GAME_MAX_FONT	8


PLC_DEVICE	m_pDev		= NULL;		// Device
PLC_SPRITE	m_pSpt		= NULL;		// 2D Sprite

PLC_FONT	m_pFont1	= NULL;		// font 1
PLC_FONT	m_pFont2	= NULL;		// Font 2

std::vector<PLC_FONT > m_vFont;


DOUBLE GetAppFrame();



// Main Loop
INT LC_CALLBACK Run(LC_HANDLE)
{
#if defined(_WIN32)
	LcAux_Sleep(10);
#endif

	m_pDev->Query(LC_QUERY_INVALID, NULL);
	m_pDev->Query(LC_QUERY_RESTORE, NULL);

	static INT c=0;
	++c;

//	if(c>20*60*20)
	if(c>10*60*10)
	{
		printf("Game Process Terminated\n");
		return LC_EFAIL;
	}



	FLOAT fFrame = (FLOAT)GetAppFrame();


	static INT	Bgn = 0;
	static INT	End = -1;

	static INT n=0;
	++n;

	if(n>25)
	{
		++Bgn;

		if(Bgn>20)
			Bgn = 0;

		printf("%f\n", fFrame);
		n = 0;
	}


	int		i = 0;
	char	str[128]={0};


	LCXVECTOR3	vcPos(0.0F, 0.0F, 0.0F);
	LCXVECTOR3	vcScl(1.F, 1.F, 1.F);
	LCXCOLOR	color(0.5F, 1.F, 0.5F, 1.F);

	sprintf(str, "갈릭 ABCDEF game joy @!#$ 12345678");
	m_pFont1->Position(&vcPos);
	m_pFont1->Color(&color);
	m_pFont1->String(str);



	vcPos = LCXVECTOR3(20.0F, 40.0F, 0.0F);
	color = LCXCOLOR  (1.F, 1.F, 0.F, 1.F);

	sprintf(str, "안녕하세요. Hello world");
	m_pFont2->Position(&vcPos);
	m_pFont2->Color(&color);
	m_pFont2->Scaling(&vcScl);
	m_pFont2->String(str);

	// Set string to Font
	color= LCXCOLOR(1, 1, 0, 1);
	for(i=0; i<(int)m_vFont.size(); ++i)
	{
		PLC_FONT  pFont = m_vFont[i];
		sprintf(str, "GLC 폰트: %d, Count: %d, Frame: %.f", 12+i*2, c, fFrame);
		pFont->String(str);

		// Setting position and color
		LCXVECTOR3 vcPos(40.0F*(i+1), 150.0F+ 30*i, 0.0F);

		pFont->Position(&vcPos);
		pFont->Color(&LCXCOLOR(1, 1, 1, 1));
	}



	// Prepare Rendering...
	m_pDev->BeginScene();

	// Clear Backbuffer
	m_pDev->Clear(LC_CLEAR_COLOR_BUFFER | LC_CLEAR_DEPTH_BUFFER);


	// Sprite Begin
	m_pSpt->Begin();


	// simple font
	m_pFont1->DrawTxt();



	// draw character in string
	INT nCnt = 0;
	m_pFont2->GetAttrib(LC_FONT_CHAR_COUNT, &nCnt);
	m_pFont2->DrawTxt();

	LCXCOLOR	color2(1, 0.3F, 0.8F, 1);
	vcPos = LCXVECTOR3(20, 75, 0.0F);
	m_pFont2->Position(&vcPos);
	m_pFont2->DrawTxt(NULL, Bgn, Bgn, NULL, &color2);

	vcPos = LCXVECTOR3(20, 110, 0.0F);
	m_pFont2->DrawTxt(NULL, Bgn, Bgn, &vcPos, &color2);


	// Draw Font List
	for(i=0; i<(int)m_vFont.size(); ++i)
	{
		PLC_FONT  pFont = m_vFont[i];
		pFont->DrawTxt();
	}


	// Sprite End
	m_pSpt->End();


	// Post Rendering...
	m_pDev->EndScene();

	return LC_OK;
}



// Main Program
int main(int argc, char* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//	_CrtSetBreakAlloc(548);

	TLC_ARGS args;

	int		hr = 0;
	int		i =0;


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



	// Create Default Font
	{
		TLC_FONT	tFont(LCCMD_DEFAULT, LC_FONT_AN_INTERNAL, 26);
		MAKE_ARG2(args, (LC_HANDLE)&tFont, (LC_HANDLE)m_pSpt);
		if(LC_FAILED(LcDev_CreateFont(NULL, &m_pFont1, &args)))
			goto End;
	}


	{
		TLC_FONT	tFont(LCCMD_DEFAULT, LC_FONT_AN_FTF, 40);
		MAKE_ARG2(args, (LC_HANDLE)&tFont, (LC_HANDLE)m_pSpt);
		if(LC_FAILED(LcDev_CreateFont(NULL, &m_pFont2, &args)))
			goto End;
	}

	// Create font from file
	for(i=0; i<GAME_MAX_FONT; ++i)
	{
		PLC_FONT	pFont;
		TLC_FONT	tFont((char*)MEDIA_DIR"font/SourceHanSansKR-Medium.otf", LC_FONT_AN_FTF, 12+i*2);
		MAKE_ARG2(args, (LC_HANDLE)&tFont, (LC_HANDLE)m_pSpt);
		if(LC_FAILED(LcDev_CreateFont(NULL, &pFont, &args)))
			goto End;

		m_vFont.push_back(pFont);
	}


	// Run Program
	while(1)
	{
		if(LC_FAILED(LcSys_Run()))
			break;

		// Flipping
		m_pDev->Present(0,0,0,0);
	}



End:
	// Release font Instance
	SAFE_RELEASE(	m_pFont1	);

	SAFE_RELEASE(	m_pFont2	);
	for(int i=0; i< (int)m_vFont.size(); ++i)
	{
		PLC_FONT	pFont = m_vFont[i];

		if(NULL == pFont)
			continue;

		(pFont)->Release();
	}
	m_vFont.clear();


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

	_CrtDumpMemoryLeaks( );

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

