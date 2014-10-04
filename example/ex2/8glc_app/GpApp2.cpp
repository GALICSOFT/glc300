// Implementation of the CGpApp class.
//  Created by Heesung Oh
//  Copyright GALIC SOFT Inc. All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER) && _MSC_VER >= 1200
  #pragma warning( disable : 4786)
  #pragma warning( disable : 4996)
#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#include <LcType.h>
#include <LcBase.h>
#include <LcMath.h>
#include <LcEuclid.h>
#include <LcCore.h>
#include <LcAux.h>
#include <LcStdev.h>
#include <LcxEntity.h>
#include <LcxMedia.h>

#include "GpApp.h"


INT CGpApp::Init()
{
	TLC_ARGS args;
	INT hr = 0;

	LOGI("CGpApp::Init::Begin---------------------------------------------\n");

	// font
	TLC_FONT	tFont("data/mwg_b.otf", LC_FONT_AN_INTERNAL, 32);
	MAKE_ARG2(args, (LC_HANDLE)&tFont, (LC_HANDLE)m_pSpt);
	if(LC_FAILED(LcDev_CreateFont(NULL, &m_pFontApp, &args)))
		return LC_EFAIL;


	// Create Texture
	UINT	cKey= 0xFF00FFFF;
	UINT	fmt	= 0;
	INT		mip = 1;

	MAKE_ARG4(args, (char*)"data/bg512x256.png", fmt, cKey, mip);
	if(LC_FAILED(LcDev_CreateTextureFromFile(NULL, &m_pTex0, &args)))
		return LC_EFAIL;

	MAKE_ARG4(args, (char*)"data/star128.tga", fmt, cKey, mip);
	if(LC_FAILED(LcDev_CreateTextureFromFile(NULL, &m_pTex1, &args)))
		return LC_EFAIL;

	MAKE_ARG4(args, (char*)"data/galic.png", fmt, cKey, mip);
	if(LC_FAILED(LcDev_CreateTextureFromFile(NULL, &m_pTex2, &args)))
		return LC_EFAIL;


	// sound: Default- 22050 Hz, 16 bit mono
	MAKE_ARG2(args, (UINT)LC_SRC_T_FILE, (char*)"data/theme.ogg");
	if(LC_FAILED(LcxSmd_CreateSound(NULL, &m_pSnd0, &args)))
		return LC_EFAIL;


	MAKE_ARG2(args, (UINT)LC_SRC_T_FILE, (char*)"data/ding.ogg");
	if(LC_FAILED(LcxSmd_CreateSound(NULL, &m_pSnd1, &args)))
		return LC_EFAIL;

	MAKE_ARG2(args, (UINT)LC_SRC_T_FILE, (char*)"data/snd3.ogg");
	if(LC_FAILED(LcxSmd_CreateSound(NULL, &m_pSnd2, &args)))
		return LC_EFAIL;

	MAKE_ARG2(args, (UINT)LC_SRC_T_FILE, (char*)"data/asm_bgm.wav");
	if(LC_FAILED(LcxSmd_CreateSound(NULL, &m_pSnd3, &args)))
		return LC_EFAIL;

	MAKE_ARG2(args, (UINT)LC_SRC_T_FILE, (char*)"data/asm_fire.wav");
	if(LC_FAILED(LcxSmd_CreateSound(NULL, &m_pSnd4, &args)))
		return LC_EFAIL;


	m_pSnd0->SetRepeat();
	m_pSnd0->Play();

	m_pSnd3->SetRepeat();
	m_pSnd3->Play();


	m_score	= 0;

	// read score from file
	PLC_FILE fp = NULL;
	hr = LcFile_Open(NULL, &fp, (char*)"data/save_info.txt", (char*)"rt");
	if(LC_FAILED(hr))
		return LC_EFAIL;

	char sline[128]={0};
	fp->ReadLine(sline, 120);
	sscanf(sline, "%d", &m_score);
	SAFE_RELEASE(	fp	);

	LOGI("CGpApp::Init::End  ---------------------------------------------\n");

	return LC_OK;
}


INT CGpApp::Destroy()
{
	// release the game resource
	SAFE_RELEASE(	m_pFontApp	);
	SAFE_RELEASE(	m_pTex0		);
	SAFE_RELEASE(	m_pTex1		);
	SAFE_RELEASE(	m_pTex2		);
	SAFE_RELEASE(	m_pSnd0		);
	SAFE_RELEASE(	m_pSnd1		);
	SAFE_RELEASE(	m_pSnd2		);
	SAFE_RELEASE(	m_pSnd3		);
	SAFE_RELEASE(	m_pSnd4		);

	return LC_OK;
}


INT CGpApp::FrameMove()
{
#if defined(_MSC_VER)

	LcAux_Sleep(10);
#endif



	INT hr =0;

	// Input Update
	hr = m_pInput->Update();

	if (LC_FAILED(hr))
		return LC_EFAIL;


	LCXVECTOR3	vcMtsPos = m_pInput->MtsPosition();
	//LC_STATE	nMtsState= m_pInput->MtsState();
	const BYTE*	pKey = m_pInput->KeyMap();
	const BYTE*	pMts = m_pInput->MtsMap();

	// Home Key
	if(pKey[LCIK_ESCAPE])
		return LC_EFAIL;


	static int ccc = 0;
	++ccc;


	//if(LCIK_KEYDOWN == pMts[0])
	//{
	//	// write score to file
	//	m_score	+= 1000;
	//	m_score	*= 4;

	//	PLC_FILE fp = NULL;
	//	INT hr = 0;

	//	hr = LcFile_Open(NULL, &fp, (char*)"data/save_info.txt", (char*)"wt");
	//	if(LC_FAILED(hr))
	//		return LC_EFAIL;

	//	char sline[128]={0};
	//	sprintf(sline, "%d\n", m_score);
	//	fp->WriteByte(sline, strlen(sline));
	//	SAFE_RELEASE(	fp	);
	//}


	//if(pMts[0] && LCIK_KEYDOWN == pMts[1])
	//{
	//	m_pSnd1->Play();
	//	m_pSnd2->Play();
	//	m_pSnd4->Play();
	//}

	if(5 == ccc)
	{
		ccc = 0;
		char	sbuf[128]	= {0};
		sprintf(sbuf, "GALIC: m: %.f %.f %d, %.1fFPS(%.2f)"
				, vcMtsPos.x, vcMtsPos.y, pMts[0], m_TimeFPS, m_TimeElps);

		m_misFont->String(sbuf);
	}


	return LC_OK;
}



INT CGpApp::Render()
{
	m_pDev->SetRenderState(LC_RS_CLEAR_COLOR, 0xFF006699);
	
	m_pDev->BeginScene();	// Prepare Rendering...
	m_pDev->Clear(LC_CLEAR_COLOR_BUFFER | LC_CLEAR_DEPTH_BUFFER);	// Clear Backbuffer

	m_pSpt->Begin();				// Sprite Begin


	static FLOAT c=0;
	c += 1.1F;

	LCXVECTOR2	rc;
	LCXVECTOR3	s;
	LCXVECTOR3	r;
	LCXVECTOR3	t;
	LCXCOLOR	d;

	float fRadian = LCXToRadian(c);

	rc.x  = (FLOAT)m_pTex1->ImgW();
	rc.y  = (FLOAT)m_pTex1->ImgH();

	s	= LCXVECTOR3(2.0F, 2.0F, 1.0F);
	r	= LCXVECTOR3(0   ,    0, 0.0F);
	t	= LCXVECTOR3(200 ,   25, -100.0F);
	d	= LCXCOLOR  (1.0F, 1.0F, 1.0F, 0.5F);

	r  = t + LCXVECTOR3(rc.x/2.F * s.x, rc.y/2.F * s.y, 0.0F);

	m_pSpt->DrawEx(m_pTex1, NULL, &t, &s, &r, fRadian, &d);

	t	= LCXVECTOR3(0 ,   0, -50.0F);
	m_pSpt->Draw(m_pTex0, NULL, &t);



	s = LCXVECTOR3(1.3F, 1.2F, 1.0F);
	t = LCXVECTOR3(200, 160, 10.0F);
	d = LCXCOLOR  (0.6F,1.0F,1.0F, 1.0F);

	m_pSpt->Draw(m_pTex0, NULL, &t, &s, &d);

	t = LCXVECTOR3(430, 210, 20.0F);
	m_pSpt->Draw(m_pTex2, NULL, &t, &s, &d);


	if(m_bShowSt)
		m_misFont->DrawTxt();


	t = LCXVECTOR3(10, 10, 0.0F);
	d = LCXCOLOR(0.0F, 1.0F, 1.0F, 1.0F);
	char	sbuf[128]	= {0};

	sprintf(sbuf, "Á¡¼ö:: %d", m_score);
	m_pFontApp->String(sbuf);
	m_pFontApp->Position(&t);
	m_pFontApp->Color(&d);
	m_pFontApp->DrawTxt();


	m_pSpt->End();				// Sprite End

	m_pDev->EndScene();			// Post Rendering...

	return LC_OK;
}


INT CGpApp::Invalid()
{
	m_pFontApp->Query(LC_QUERY_INVALID, NULL);
	m_pTex0->Query(LC_QUERY_INVALID, NULL);
	m_pTex1->Query(LC_QUERY_INVALID, NULL);
	m_pTex2->Query(LC_QUERY_INVALID, NULL);
	m_pSnd0->Query(LC_QUERY_INVALID, NULL);
	m_pSnd1->Query(LC_QUERY_INVALID, NULL);
	m_pSnd2->Query(LC_QUERY_INVALID, NULL);
	m_pSnd3->Query(LC_QUERY_INVALID, NULL);
	m_pSnd4->Query(LC_QUERY_INVALID, NULL);

	m_misFont->Query(LC_QUERY_INVALID, NULL);
	m_pDev->Query(LC_QUERY_INVALID, NULL);

	return LC_OK;
}


INT CGpApp::Restore()
{
	m_pDev->Query(LC_QUERY_RESTORE, NULL);
	m_misFont->Query(LC_QUERY_RESTORE, NULL);

	m_pFontApp->Query(LC_QUERY_RESTORE, NULL);
	m_pTex0->Query(LC_QUERY_RESTORE, NULL);
	m_pTex1->Query(LC_QUERY_RESTORE, NULL);
	m_pTex2->Query(LC_QUERY_RESTORE, NULL);
	m_pSnd0->Query(LC_QUERY_RESTORE, NULL);
	m_pSnd1->Query(LC_QUERY_RESTORE, NULL);
	m_pSnd2->Query(LC_QUERY_RESTORE, NULL);
	m_pSnd3->Query(LC_QUERY_RESTORE, NULL);
	m_pSnd4->Query(LC_QUERY_RESTORE, NULL);

	return LC_OK;
}
