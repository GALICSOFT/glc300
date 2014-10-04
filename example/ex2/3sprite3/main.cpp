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



PLC_DEVICE				m_pDev	= NULL;		// Device
PLC_SPRITE				m_pSpt	= NULL;		// 2D Sprite

vector<PLC_TEXTURE  >	m_vTex;				// Texture list
vector<PLC_SPRITE_C >	m_vTdm;				// Sprite collector list


DOUBLE GetAppFrame();


INT LC_CALLBACK Run(LC_HANDLE)
{
#if defined(_WIN32)
//	LcAux_Sleep(10);
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


	// Prepare Rendering...
	m_pDev->BeginScene();

	// Clear Backbuffer
	m_pDev->Clear(LC_CLEAR_COLOR_BUFFER | LC_CLEAR_DEPTH_BUFFER);

	// Sprite Begin
	m_pSpt->Begin();

	//m_pSpt->Draw(m_vTex[0], NULL, NULL, NULL, NULL);

//	m_pSpt->SetRenderState(LC_RS_DISPLAY_MONO, LC_TRUE);


	for(INT i=0; i<(int)m_vTdm.size(); ++i)
	{
		PLC_SPRITE_C	pTdm = m_vTdm[i];
		LCXMATRIX mtWld;
		mtWld.Identity();
		mtWld._41 = i* 100.0F;	// x
		mtWld._42 = i* 50.0F;	// y

		m_pSpt->SetTransform(LC_TM_WORLD, &mtWld);

		pTdm->Draw();
	}


	//m_pSpt->SetRenderState(LC_RS_DISPLAY_MONO, LC_FALSE);

	m_pSpt->SetTransform(LC_TM_WORLD, NULL);
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

	PLC_TEXTURE	pTex = NULL;
	char		sFile[128]={0};
	UINT		colorKey = 0xFF00FFFF;
	INT		i=0;


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


	for(i=0;i<=5; ++i)
	{
		sprintf(sFile, (char*)MEDIA_DIR"tex/t0%d.tga", i);
		MAKE_ARG4(args, sFile, (UINT)0, (UINT)0, (UINT)1);
		hr = LcDev_CreateTextureFromFile(NULL, &pTex, &args);
		if(LC_FAILED(hr))
			goto End;

		m_vTex.push_back(pTex);

		PLC_SPRITE_C pSpc = NULL;

		MAKE_ARG1(args, (LC_HANDLE)pTex);
		hr = LcDev_CreateSpriteC(NULL, &pSpc, &args);

		m_vTdm.push_back(pSpc);
	}

	printf("LcDev_CreateTextureFromFile Success\n");



	// collector test
	for(i=0; i< (int)m_vTex.size(); ++i)
	{
		PLC_SPRITE_C pSpc = NULL;

		MAKE_ARG1(args, (LC_HANDLE)pTex);
		hr = LcDev_CreateSpriteC(NULL, &pSpc, &args);

		m_vTdm.push_back(pSpc);
	}

	printf("LcDev_CreateSpriteC Success\n");


	// test code for collector
	for(i=0;i< (int)m_vTdm.size(); ++i)
	{
		int maxRc = 50 + rand()%200;

		for(int j=0;j<maxRc; ++j)
		{
			float X = FLOAT(rand()%320)-80;
			float Y = FLOAT(rand()%240)-80;
			LCXVECTOR3 pos(X, Y, 0);

			m_vTdm[i]->AddRect(NULL, &pos, NULL, NULL, 0, NULL);
		}
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
	for(vector<PLC_SPRITE_C>::iterator t= m_vTdm.begin(); t != m_vTdm.end(); ++t)
		(*t)->Release();

	m_vTdm.clear();


	for(vector<PLC_TEXTURE>::iterator t = m_vTex.begin(); t != m_vTex.end(); ++t)
		(*t)->Release();


	m_vTex.clear();


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
