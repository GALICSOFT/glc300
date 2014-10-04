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


#define MEDIA_DIR	"../../media/"


INT CGpApp::Init()
{
	TLC_ARGS args;
	INT hr = 0;

	LOGI("CGpApp::Init::Begin---------------------------------------------\n");


	struct __TTsound
	{
		char*	s;
		int		rpt;
		int		play;
	} 
	soundFile[] =
	{
		{ (char*)MEDIA_DIR"sound/armor_not_pierced_by_player_1.wav"	,	1, 0,},
		{ (char*)MEDIA_DIR"sound/armor_not_pierced_by_player_1.wav"	,	1, 0,},
		{ (char*)MEDIA_DIR"sound/armor_not_pierced_by_player_2.wav"	,	1, 0,},
		{ (char*)MEDIA_DIR"sound/armor_not_pierced_by_player_2.wav"	,	1, 0,},
		{ (char*)MEDIA_DIR"sound/armor_not_pierced_by_player_4.wav"	,	1, 0,},
		{ (char*)MEDIA_DIR"sound/armor_not_pierced_by_player_4.wav"	,	1, 0,},
		{ (char*)MEDIA_DIR"sound/armor_pierced_by_player_1.wav"		,	1, 0,},
		{ (char*)MEDIA_DIR"sound/armor_pierced_by_player_2.wav"		,	1, 0,},
		{ (char*)MEDIA_DIR"sound/armor_pierced_by_player_3.wav"		,	1, 0,},
		{ (char*)MEDIA_DIR"sound/armor_pierced_by_player_4.wav"		,	1, 0,},
		{ (char*)MEDIA_DIR"sound/armor_pierced_by_player_6.wav"		,	1, 0,},
		{ (char*)MEDIA_DIR"sound/armor_pierced_by_player_7.wav"		,	1, 0,},
		{ (char*)MEDIA_DIR"sound/armor_pierced_by_player_8.wav"		,	1, 0,},
		{ (char*)MEDIA_DIR"sound/cash_register_.wav"				,	1, 0,},
		{ (char*)MEDIA_DIR"sound/explode_01.wav"					,	1, 0,},
		{ (char*)MEDIA_DIR"sound/se_kick.wav"						,	1, 0,},
		{ (char*)MEDIA_DIR"sound/swd_0001.wav"						,	1, 0,},
		{ (char*)MEDIA_DIR"sound/swd_0001.wav"						,	1, 0,},
		{ (char*)MEDIA_DIR"sound/swd_0002.wav"						,	1, 0,},
		{ (char*)MEDIA_DIR"sound/swd_0002.wav"						,	1, 0,},
		{ (char*)MEDIA_DIR"sound/swd_0003.wav"						,	1, 0,},
		{ (char*)MEDIA_DIR"sound/swd_0003.wav"						,	1, 0,},
		{ (char*)MEDIA_DIR"sound/ding.ogg"							,	1, 0,},
		{ (char*)MEDIA_DIR"sound/snd3.ogg"							,	1, 0,},
		{ (char*)MEDIA_DIR"sound/theme.ogg"							,  -1, 1,},

		{ (char*)NULL										,	0, 0,},
	};


	for(int i=0; NULL != soundFile[i].s; ++i)
	{
		PLCX_SOUND	pSound;
		// sound: Default- 22050 Hz, 16 bit mono
		MAKE_ARG2(args, (UINT)LC_SRC_T_FILE, soundFile[i].s);
		if(LC_FAILED(LcxSmd_CreateSound(NULL, &pSound, &args)))
		{
			LOGE("Load sound Err:%s", soundFile[i]);
			return LC_EFAIL;
		}

		m_pSnd[i] = pSound;
		pSound->SetRepeat(soundFile[i].rpt);

		if(soundFile[i].play)
			pSound->Play();
	}


	LOGI("CGpApp::Init::End  ---------------------------------------------\n");

	return LC_OK;
}


INT CGpApp::Destroy()
{
	// release the game resource
	for(int i=0; i<MAX_SND; ++i)
	{
		SAFE_RELEASE(	m_pSnd[i]	);
	}

	return LC_OK;
}



INT CGpApp::FrameMove()
{
#if defined(_MSC_VER)
	LcAux_Sleep(10);
#endif


	//static int c=0;
	//++c;
	//if(100<c)
	//	return LC_EFAIL;


	INT hr =0;

	hr = m_pInput->Update();

	if (LC_FAILED(hr))
		return LC_EFAIL;

	LCXVECTOR3	vMts0 = m_pInput->MtsPosition();
	const BYTE*	pKey = m_pInput->KeyMap();
	const BYTE*	pMts = m_pInput->MtsMap();


	if(pKey[LCIK_ESCAPE])
		return LC_EFAIL;


	if(LCIK_KEYDOWN == pMts[0])
	{
		for(int i=0; i<MAX_SND; ++i)
		{
			PLCX_SOUND	pSound = m_pSnd[i];

			if(NULL == m_pSnd[i])
				continue;

			FLOAT		w = 150.0F;
			FLOAT		h =  40.0F;
			FLOAT		e = 25.0F;
			FLOAT		x =  40.F + (i/6) * (w+e);
			FLOAT		y =  20.F + (i%6) * (h+e);

			LCXVECTOR3	pos(x, y, 0.0F);

			if(m_pInput->IsInRect(x, y, w, h ) )
			{
				INT	rpt = m_pSnd[i]->GetRepeat();
				INT	st = m_pSnd[i]->Status();

				pSound->Stop();

				if(LCX_AV_PLAY != st)
				{
					if(LCX_AV_INFINITE != rpt) pSound->SetRepeat(1);
					else                       pSound->SetRepeat(LCX_AV_INFINITE);

					pSound->Play();
				}

				break;
			}
		}
	}


	static int ccc = 0;
	++ccc;

	if(5 == ccc)
	{
		ccc = 0;
		char	sbuf[128]	= {0};
		sprintf(sbuf, "GALIC: m: %.f %.f %d, %.1fFPS(%.2f)"
				, vMts0.x, vMts0.y, pMts[0], m_TimeFPS, m_TimeElps);

		m_pFont->String(sbuf);
	}

	return LC_OK;
}



INT CGpApp::Render()
{
	m_pDev->SetRenderState(LC_RS_CLEAR_COLOR, 0xFF006699);
	
	m_pDev->BeginScene();
	m_pDev->Clear(LC_CLEAR_COLOR_BUFFER | LC_CLEAR_DEPTH_BUFFER);

	m_pSpt->Begin();


	for(int i=0; i<MAX_SND; ++i)
	{
		PLCX_SOUND	pSound = m_pSnd[i];

		if(NULL == m_pSnd[i])
				continue;

		FLOAT		w = 150.0F;
		FLOAT		h =  40.0F;
		FLOAT		e = 25.0F;
		FLOAT		x =  40.F + (i/6) * (w+e);
		FLOAT		y =  20.F + (i%6) * (h+e);

		LCXVECTOR3	pos(x, y, 0.0F);

		LCXCOLOR	col((COLOR32)0xFF00FF00);

		INT			st = pSound->Status();

		if(LCX_AV_PLAY != st)
			col = (COLOR32)0xFF0000FF;

		m_pSpt->DrawRect(&pos, w, h, 2.0F, &col);
	}


	m_pFont->DrawTxt();

	m_pSpt->End();

	m_pDev->EndScene();

	return LC_OK;
}


INT CGpApp::Invalid()
{
	for(int i=0; i<MAX_SND; ++i)
	{
		if(NULL == m_pSnd[i])
			continue;

		m_pSnd[i]->Query(LC_QUERY_INVALID, NULL);
	}


	m_pFont->Query(LC_QUERY_INVALID, NULL);
	m_pDev->Query(LC_QUERY_INVALID, NULL);

	return LC_OK;
}


INT CGpApp::Restore()
{
	m_pDev->Query(LC_QUERY_RESTORE, NULL);
	m_pFont->Query(LC_QUERY_RESTORE, NULL);

	for(int i=0; i<MAX_SND; ++i)
	{
		if(NULL == m_pSnd[i])
			continue;

		m_pSnd[i]->Query(LC_QUERY_RESTORE, NULL);
	}

	return LC_OK;
}

