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

#include <LcType.h>
#include <LcBase.h>
#include <LcMath.h>
#include <LcEuclid.h>
#include <LcCore.h>
#include <LcAux.h>

#include <LcStdev.h>
#include <LcxEntity.h>


#define MEDIA_DIR	"../../media/"


PLC_DEVICE	m_pDev	= NULL;		// Device
PLC_SPRITE	m_pSpt	= NULL;		// 2D Sprite

PLC_FONT	m_pFont	= NULL;		// Font


DOUBLE GetAppFrame();


INT LC_CALLBACK Run(LC_HANDLE)
{
#if defined(_WIN32)
	LcAux_Sleep(10);
#endif


	static INT c=0;
	++c;

	if(c>18*60*20)
	{
		printf("Game Process Terminated\n");
		return LC_EFAIL;
	}


//	FLOAT fFrame = (FLOAT)GetAppFrame();
//	static INT n=0;
//	++n;

//	if(n>5)
//	{
//		printf("%3.f\n", fFrame);
//		n = 0;
//	}




	BYTE			Keypad[LC_MAX_KEY]={0};
	TLC_INPUT_TS	mts[4]={0};


	LcStv_InputReadKey(Keypad);				// Read Keypad data
	LcStv_InputReadMts(0, &mts[0]);			// Read Touch Screen or left
	LcStv_InputReadMts(1, &mts[1]);			// Read Touch Screen or right
	LcStv_InputReadMts(2, &mts[2]);			// Read Touch Screen or middle


	if(Keypad[LCIK_ESCAPE])
		return LC_EFAIL;



	char sbuf[128]={0};

	sprintf(sbuf, "Try to presss buttons.");

	for(int i=0; i<LC_MAX_KEY; ++i)
	{
		if(Keypad[i])
		{
			sprintf(sbuf, "You Pressed %d: state: %d ::", i, Keypad[i]);
		}
	}


	LCXVECTOR3	vcPos(5, 5, 0);
	LCXCOLOR	color(1, 1, 0, 1);

	m_pFont->Position(&vcPos);
	m_pFont->Color(&color);
	m_pFont->String(sbuf);


	// Prepare Rendering...
	m_pDev->BeginScene();

	// Clear Backbuffer
	m_pDev->Clear(LC_CLEAR_COLOR_BUFFER | LC_CLEAR_DEPTH_BUFFER);


	// Sprite Begin
	m_pSpt->Begin();


	// Draw buffer
	m_pFont->DrawTxt();

	m_pSpt->End();


	m_pSpt->Begin();
	{
		sprintf(sbuf, "Touch pos:(%3d %3d) st(%3d, %3d)", mts[0].x, mts[0].y, mts[0].t, mts[1].t);

		vcPos = LCXVECTOR3(5, 35, 0);
		color = LCXCOLOR(0, 1, 1, 1);

		m_pFont->Position(&vcPos);
		m_pFont->Color(&color);
		m_pFont->String(sbuf);

		m_pFont->DrawTxt();
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
	TLC_ARGS args;

	INT		hr = 0;


	UINT	dClearColor = 0xFF006699;

	char		sFont1[] = MEDIA_DIR"font/mwg_b.otf";
	TLC_FONT	tFont(sFont1, LC_FONT_AN_INTERNAL, 20);

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
	m_pDev->SetRenderState(LC_RS_CLEAR_COLOR, dClearColor);


	// get the default Rendering 2D sprite
	m_pSpt = (PLC_SPRITE)LcVar_ReadP(LC_VAR_SPRITE);



	// Create Input20
	if(LC_FAILED(LcStv_InputOpen()))
		goto End;

	printf("LcxEnt_CreateInput Success\n");



	// Create Font Instance
	MAKE_ARG2(args, (LC_HANDLE)&tFont, (LC_HANDLE)m_pSpt);
	if(LC_FAILED(LcDev_CreateFont(NULL, &m_pFont, &args)))
		goto End;





	// Run Program
	while(1)
	{
		if(LC_FAILED(LcSys_Run()))
			break;

		// Flipping
		m_pDev->Present(0,0,0,0);
	}


End:


	// Release font instance
	m_pFont->Release();

	
	// Release Input
	LcStv_InputClose();


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
