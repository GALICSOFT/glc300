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
#include <memory.h>
#include <math.h>
#include <time.h>

#include <LcType.h>
#include <LcBase.h>
#include <LcMath.h>
#include <LcEuclid.h>
#include <LcCore.h>
#include <LcAux.h>
#include <LcStdev.h>
#include <LcxEntity.h>
#include <LcxMedia.h>


#define MEDIA_DIR	"../../media/"
#define MAX_SOUND	4


PLC_DEVICE	m_pDev	= NULL;		// Device
PLC_SPRITE	m_pSpt	= NULL;		// 2D Sprite

PLCX_INPUT	m_pInput= NULL;		// Input
PLC_FONT	m_pFont	= NULL;		// Font

vector<PLCX_SOUND > m_vSnd(0);	// Sound Instance


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
		LOGI("Game Process Terminated\n");
		return LC_EFAIL;
	}

	FLOAT fFrame = (FLOAT)GetAppFrame();


	static INT n=0;
	++n;

	if(n>5)
	{
		LOGI("%f\n", fFrame);
		n = 0;
	}

	char sbuf[128]={0};
	LCXVECTOR3	vcPos(5, 5, 0);
	LCXCOLOR	color(1, 1, 0, 1);

	sprintf(sbuf, "Try to presss F_A(left), F_B(right), or F_Y(up) button.");
	m_pFont->Position(&vcPos);
	m_pFont->Color(&color);
	m_pFont->String(sbuf);



	// Input Update
	m_pInput->Update();


	if(m_pInput->KeyDown(LCIK_ESCAPE))
		return LC_EFAIL;


	// Play Sound
	if(m_pInput->KeyDown(LCIK_LEFT))
	{
		for(int i=2; i< (int)m_vSnd.size(); ++i)
			m_vSnd[i]->Play();
	}

	// Play ding.wav
	if(m_pInput->KeyDown(LCIK_RIGHT))
	{
		m_vSnd[0]->Stop();
		m_vSnd[0]->Play();
	}


	// Play ding.wav
	if(m_pInput->KeyDown(LCIK_UP))
		m_vSnd[1]->Play();



	// Prepare Rendering...
	m_pDev->BeginScene();

	// Clear Backbuffer
	m_pDev->Clear(LC_CLEAR_COLOR_BUFFER | LC_CLEAR_DEPTH_BUFFER);


	// Sprite Begin
	m_pSpt->Begin();


	// Draw buffer
	m_pFont->DrawTxt();


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
	INT		i;

	UINT		dClearColor = 0xFF006699;
	char*		sFont1 = LCCMD_DEFAULT;
	TLC_FONT	tFont(sFont1, LC_FONT_AN_INTERNAL, 20);


	char* soundfile[] =
	{
		(char*)MEDIA_DIR"sound/ding.ogg",
		(char*)MEDIA_DIR"sound/snd2.wav",
		(char*)MEDIA_DIR"sound/snd3.wav",
		NULL,
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


	// Set Clear Color
	m_pDev->SetRenderState(LC_RS_CLEAR_COLOR, dClearColor);


	// get the default Rendering 2D sprite
	m_pSpt = (PLC_SPRITE)LcVar_ReadP(LC_VAR_SPRITE);


	// Create Input
	if(LC_FAILED(LcxEnt_CreateInput(NULL, &m_pInput)))
		goto End;


	// Create Font Instance
	MAKE_ARG2(args, (LC_HANDLE)&tFont, (LC_HANDLE)m_pSpt);
	if(LC_FAILED(LcDev_CreateFont(NULL, &m_pFont, &args)))
		goto End;


	// Create Sound Object from buffer
	{
		PLCX_SOUND	pSnd;

		BYTE*	buf		= NULL;
		ULONG	len		= 0;
		char*	sZip	= (char*)MEDIA_DIR"sound/raw.zip";
		char*	sName	= (char*)"smd/theme.ogg";

		hr = Lzip_SimpleUnZip(&buf, &len, sZip, sName);
		if(LC_FAILED(hr))
			return LC_CANNT_ALLOC;


		MAKE_ARG4(args, (UINT)LC_SRC_T_MEM, sName, buf, len);
		hr = LcxSmd_CreateSound(NULL, &pSnd, &args);
		LcMem_Free((LC_HANDLE*)&buf);

		if(LC_FAILED(hr))
			return LC_CANNT_ALLOC;

		m_vSnd.push_back(pSnd);
	}


	// Create Sound Object from file
	for(i=0; NULL != soundfile[i]; ++i)
	{
		PLCX_SOUND	pSnd;
		MAKE_ARG2(args, (UINT)LC_SRC_T_FILE, soundfile[i]);
		hr = LcxSmd_CreateSound(NULL, &pSnd, &args);
		if(LC_FAILED(hr))
			goto End;

		m_vSnd.push_back(pSnd);

		if(0 == i)
			pSnd->SetVolume(1.8F);			// set the sound volume
		else
			pSnd->SetVolume(0.1F);			// set the sound volume

		pSnd->SetRepeat(1);					// set the repeat count
	}

	m_vSnd[0]->SetVolume(0.1F);				// set the repeat count
	m_vSnd[0]->SetRepeat(LC_INFINITE);		// set the repeat count
	m_vSnd[0]->Play();						// play

	LOGI("Sound Load Complete\n");


	LcLog_SetSate(LC_FALSE);



	// Run Program
	while(1)
	{
		if(LC_FAILED(LcSys_Run()))
			break;

		// Flipping
		m_pDev->Present(0,0,0,0);
	}


End:

	for(i=0; i<(INT)m_vSnd.size(); ++i)	// Release sound object
		m_vSnd[i]->Release();

	m_vSnd.clear();			// Clear sound container


	m_pFont->Release();		// Release Font Instance

	m_pInput->Release();	// Release Input

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

