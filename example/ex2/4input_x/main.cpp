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
#include <LcxEntity.h>
#include <LcStdev.h>
#include <LcxMedia.h>


#define MEDIA_DIR	"../../media/"


PLC_DEVICE	m_pDev	= NULL;		// Device
PLC_SPRITE	m_pSpt	= NULL;		// 2D Sprite

PLCX_INPUT	m_pInput= NULL;		// Input
PLC_FONT	m_pFont1= NULL;		// Font1
PLC_FONT	m_pFont2= NULL;		// Font2

char		m_sMsg[1024]={0};

DOUBLE GetAppFrame();


LONG LC_CALLBACK MsgPrc(LC_HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	INT hr = LcStv_ImeCallback((LC_HANDLE)hWnd, (LC_HANDLE)uMsg, (LC_HANDLE)wParam, (LC_HANDLE)lParam);

	return hr;
}




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



	// Input Update
	m_pInput->Update();


	LCXVECTOR3	vcTsbPos0 = m_pInput->MtsPosition();
	LCXVECTOR3	vcTsbPos1 = m_pInput->MtsPosition(1);

	LC_STATE	nTsbSt0 = m_pInput->MtsState();
	LC_STATE	nTsbSt1 = m_pInput->MtsState(1);
	const BYTE*	pKey = m_pInput->KeyMap();
	const BYTE*	pTsb = m_pInput->MtsMap();



	if(pKey[LCIK_ESCAPE])
		return LC_EFAIL;



	if(LCIK_KEYDOWN == m_pInput->MtsDown(0))
	{
		memset(m_sMsg, 0, sizeof(m_sMsg));
		sprintf(m_sMsg, "Ime Message: ");
		LcStv_ImeOpen(0);
	}


	memset(m_sMsg, 0, sizeof(m_sMsg));
	sprintf(m_sMsg, "Ime Message: ");

	if( LcStv_ImeState() )
	{
		LcStv_ImeString(m_sMsg + strlen(m_sMsg), '_');
	}
	//else
	//{
	//	int len = strlen(m_sMsg);
	//	if('_' == m_sMsg[len-1])
	//		m_sMsg[len-1]=0;
	//}



	LCXVECTOR3	vcPos(5, 80, 0);
	LCXCOLOR	color(1, 1, 0, 1);

	m_pFont1->Position(&vcPos);
	m_pFont1->Color(&color);
	m_pFont1->String(m_sMsg);


	vcPos	= LCXVECTOR3(5, 110, 0);
	color	= LCXCOLOR  (0.7F, 0.8F, 1, 1);

	memset(m_sMsg, 0, sizeof(m_sMsg));
	LcStv_ImeString(m_sMsg);

	if( LcStv_ImeEvent(LC_TRUE) )
	{
		m_pFont2->Position(&vcPos);
		m_pFont2->Color(&color);
		m_pFont2->String(m_sMsg);

		LcStv_ImeClear();
	}


	// Prepare Rendering...
	m_pDev->BeginScene();

	// Clear Backbuffer
	m_pDev->Clear(LC_CLEAR_COLOR_BUFFER | LC_CLEAR_DEPTH_BUFFER);


	// Sprite Begin
	m_pSpt->Begin();


	// Draw buffer
	m_pFont1->DrawTxt();
	m_pFont2->DrawTxt();

	m_pSpt->End();




	m_pSpt->Begin();
	{
		char sbuf[128]={0};
		sprintf(sbuf, "Touch pos(%.f %.f) state(%d, %d)", vcTsbPos0.x, vcTsbPos0.y, nTsbSt0, nTsbSt1);

		vcPos = LCXVECTOR3(5, 25, 0);
		color = LCXCOLOR(0, 1, 1, 1);

		m_pFont1->Position(&vcPos);
		m_pFont1->Color(&color);
		m_pFont1->String(sbuf);

		m_pFont1->DrawTxt();
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
	hr = LcSys_CreateWindow(MsgPrc, (char*)"LC_Tutorial");
	if(0 > hr)
		goto End;


	// Create GLC Rendering Device
	if(LC_FAILED(LcDev_CreateDevice(NULL, &m_pDev)))
		goto End;

	// Set Clear Color
	m_pDev->SetRenderState(LC_RS_CLEAR_COLOR, dClearColor);


	// get the default Rendering 2D sprite
	m_pSpt = (PLC_SPRITE)LcVar_ReadP(LC_VAR_SPRITE);



	// Create Input
	if(LC_FAILED(LcxEnt_CreateInput(NULL, &m_pInput)))
		goto End;

	printf("LcxEnt_CreateInput Success\n");




	// Create Font Instance
	MAKE_ARG2(args, (LC_HANDLE)&tFont, (LC_HANDLE)m_pSpt);
	if(LC_FAILED(LcDev_CreateFont(NULL, &m_pFont1, &args)))
		goto End;


	if(LC_FAILED(LcDev_CreateFont(NULL, &m_pFont2, &args)))
		goto End;



	sprintf(m_sMsg, "IME Test. try to click the left button\n");


	// Run Program
	while(1)
	{
		if(LC_FAILED(LcSys_Run()))
			break;

		// Flipping
		m_pDev->Present(0,0,0,0);
	}


End:

	// Release Font
	m_pFont1->Release();
	m_pFont2->Release();

	// Release Input
	m_pInput->Release();


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
