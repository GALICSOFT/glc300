// Implementation of the CGpApp class.
//  Written by Heesung Oh
//  Copyright GALIC SOFT Inc. All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER) && _MSC_VER >= 1200
  #pragma warning( disable : 4786)
  #pragma warning( disable : 4996)
#endif


#include <stdio.h>
#include <stdlib.h>
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

#include "GameObject.h"
#include "GpApp.h"


INT CGpApp::Init()
{
	TLC_ARGS args;
	INT hr = 0;

	LOGI("CGpApp::Init::Begin\n");

	
	////////////////////////////////////////////////////////////////////////////
	// Create Texture from File: Mipmap Level = 0, Color Key = 0x0

	UINT	colorKey= 0x0;
	UINT	use16	= 0x0;
	INT		mip		= 1;

	MAKE_ARG4(args, (char*)"data/atx_background.bmp", use16, colorKey, mip);
	if(LC_FAILED(LcDev_CreateTextureFromFile(NULL, &m_pTex[0], &args)))
		return LC_EFAIL;

	MAKE_ARG4(args, (char*)"data/atx_ship.png", use16, colorKey, mip);
	if(LC_FAILED(LcDev_CreateTextureFromFile(NULL, &m_pTex[1], &args)))
		return LC_EFAIL;

	MAKE_ARG4(args, (char*)"data/atx_photon.png", use16, colorKey, mip);
	if(LC_FAILED(LcDev_CreateTextureFromFile(NULL, &m_pTex[2], &args)))
		return LC_EFAIL;

	MAKE_ARG4(args, (char*)"data/atx_villain.png", use16, colorKey, mip);
	if(LC_FAILED(LcDev_CreateTextureFromFile(NULL, &m_pTex[3], &args)))
		return LC_EFAIL;

	MAKE_ARG4(args, (char*)"data/atx_shield.png", use16, colorKey, mip);
	if(LC_FAILED(LcDev_CreateTextureFromFile(NULL, &m_pTex[4], &args)))
		return LC_EFAIL;

	MAKE_ARG4(args, (char*)"data/atx_bar.png", use16, colorKey, mip);
	if(LC_FAILED(LcDev_CreateTextureFromFile(NULL, &m_pTex[5], &args)))
		return LC_EFAIL;


	////////////////////////////////////////////////////////////////////////////
	// Create Background, Effect Sound Instance.
	// (Default- 22050 Hz, 16 bit stereo)

	MAKE_ARG2(args, (UINT)LC_SRC_T_FILE, (char*)"data/asm_bgm.wav");
	if(LC_FAILED(LcxSmd_CreateSound(NULL, &m_pSnd[0], &args)))
		return LC_EFAIL;

	MAKE_ARG2(args, (UINT)LC_SRC_T_FILE, (char*)"data/asm_fire.wav");
	if(LC_FAILED(LcxSmd_CreateSound(NULL, &m_pSnd[1], &args)))
		return LC_EFAIL;

	MAKE_ARG2(args, (UINT)LC_SRC_T_FILE, (char*)"data/asm_explosion.wav");
	if(LC_FAILED(LcxSmd_CreateSound(NULL, &m_pSnd[2], &args)))
		return LC_EFAIL;


	////////////////////////////////////////////////////////////////////////////
	// Create Font Instance with Sprite

	TLC_FONT	tFont("data/mwg_b.otf", LC_FONT_AN_INTERNAL, 14);		// font name: 문화고딕, Height: 14
	MAKE_ARG2(args, (LC_HANDLE)&tFont, (LC_HANDLE)m_pSpt);
	if(LC_FAILED(LcDev_CreateFont(NULL, &m_pFontScore, &args)))
		return LC_EFAIL;


	m_pSnd[0]->SetRepeat();
	m_pSnd[0]->Play();


	LoadHighScore();
	ObjectInitialize();
	DrawScore();

	LOGI("CGpApp::Init::End\n");

	return LC_OK;
}


INT CGpApp::Destroy()
{
	SaveHighScore();

	INT i;

	// Release Texture
	for(i=0; i<GAME_MAX_TEXTURE; ++i)
		SAFE_RELEASE(	m_pTex[i]	);

	// Release Sound Instance
	for(i=0; i<GAME_MAX_SOUND; ++i)
		SAFE_RELEASE(	m_pSnd[i]	);


	SAFE_RELEASE(	m_pFontScore	);		// Release Font Instance

	return LC_OK;
}


INT CGpApp::FrameMove()
{
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


	if(8>m_nSkip)
	{
		++m_nSkip;
		return 0;
	}


	SystemControl();

	if (PLAYER_STATUS_DEAD != m_PlayerStatus)
		UpdatePlayer();

	UpdatePlayerMissiles();
	UpdateEnemies();
	UpdateEnemyMissiles();

	CollisionPlayerMissilesAndEnemies();
	CollisionPlayerAndEnemies();
	CollisionEnemyMissilesAndPlayer();
	ScrollBackground();

	ShieldPulse();


	if(0>=m_Player.nAlive)
		return LC_EFAIL;


	
	if(m_bShowSt)
	{
		char sbuf[128]={0};
		DOUBLE fFPS		   = m_TimeFPS;
		DOUBLE fElasedTime = m_TimeElps;

		sprintf(sbuf, "갈릭: m: %.f %.f %d, %.f(%.1f)F"
				, vcMtsPos.x, vcMtsPos.y, pMts[0], fFPS, fElasedTime);

		m_pFont->String(sbuf);
	}

	return LC_OK;
}



INT CGpApp::Render()
{
	if(8>m_nSkip)
		return 0;

	m_pDev->SetRenderState(LC_RS_CLEAR_COLOR, 0xFF006699);
	
	m_pDev->BeginScene();	// Prepare Rendering...
	m_pDev->Clear(LC_CLEAR_COLOR_BUFFER | LC_CLEAR_DEPTH_BUFFER);	// Clear Backbuffer

	
	m_pSpt->Begin();				// Sprite Begin

	// Draw Game Play

	DrawBackground();
	DrawMissile();
	DrawShield();
	DrawPlayer();
	DrawEnergyBar();
	DrawPlayerLife();

	m_pFontScore->DrawTxt();

	if(m_bShowSt)
		m_pFont->DrawTxt();




//	LCXRECT	rc;
//	LCXVECTOR2 vcPos;
//
//	vcPos = m_pFont->GetPosition();
//	m_pFont->GetAttrib(LC_FONT_RECT_SCALEUP, &rc);
//	vcPos.x += rc.w;
//
//	m_pFont->GetRect(&rc, 10);
//	vcPos.x = rc.x;
//	vcPos.y = rc.y;
//	m_pFont->DrawTxt(NULL, 0, -1, &vcPos);


	m_pSpt->End();				// Sprite End

	m_pDev->EndScene();			// Post Rendering...


	return LC_OK;
}


INT CGpApp::Invalid()
{
	INT i;

	m_pFont->Query(LC_QUERY_INVALID, NULL);


	for(i=0; i<GAME_MAX_TEXTURE; ++i)
	{
		if(!m_pTex[i])
			continue;

		m_pTex[i]->Query(LC_QUERY_INVALID, NULL);
	}

	for(i=0; i<GAME_MAX_SOUND; ++i)
	{
		if(!m_pSnd[i])
			continue;

		m_pSnd[i]->Query(LC_QUERY_INVALID, NULL);
	}


	m_pFontScore->Query(LC_QUERY_INVALID, NULL);

	return LC_OK;
}


INT CGpApp::Restore()
{
	INT i;

	m_pFont->Query(LC_QUERY_RESTORE, NULL);


	for(i=0; i<GAME_MAX_TEXTURE; ++i)
	{
		if(!m_pTex[i])
			continue;

		m_pTex[i]->Query(LC_QUERY_RESTORE, NULL);
	}

	for(i=0; i<GAME_MAX_SOUND; ++i)
	{
		if(!m_pSnd[i])
			continue;

		m_pSnd[i]->Query(LC_QUERY_RESTORE, NULL);
	}


	m_pFontScore->Query(LC_QUERY_RESTORE, NULL);

	return LC_OK;
}
