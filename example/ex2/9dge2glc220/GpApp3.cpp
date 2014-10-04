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

#include "GameObject.h"
#include "GpApp.h"


void CGpApp::ShieldPulse()
{
	m_ShieldTransparency = FLOAT(m_ShieldEnergy) / FLOAT(SHIELDENERGYmax);



	DOUBLE TimeCur = (DOUBLE)LcAux_TimeGetTime();

	if(TimeCur < (m_ShieldTimeDelta+ m_ShieldTimeBgn))
		return;


	m_ShieldTimeBgn = TimeCur;


	m_ShieldRatio += m_ShieldExtend * 0.02F;

	if(m_ShieldRatio >= SHIELDRATIOmax)
	{
		m_ShieldExtend = SHIELDRATIOmax;
		m_ShieldExtend = -1.F;
	}

	if(m_ShieldRatio < SHIELDRATIOmin)
	{
		m_ShieldExtend = SHIELDRATIOmin;
		m_ShieldExtend = +1.F;
	}
}


void CGpApp::ShieldRecharge()
{
	m_ShieldEnergy = SHIELDENERGYmax;
}


INT CGpApp::ShieldProtect(INT damage)
{
	INT protect = LC_TRUE;

	m_ShieldEnergy -= damage;

	if(0 > m_ShieldEnergy)
	{
		protect = LC_FALSE;

		m_ShieldEnergy = 0;
	}

	return protect;
}



void CGpApp::DrawMissile()
{
	INT i=0;

	for(i=0; i != MISSILEMAX; ++i)
	{
		if (LC_TRUE != m_PlayerMissiles[i].nAlive)
			continue;

		m_pSpt->Draw(m_pTex[m_PlayerMissiles[i].m_nTex], NULL, &m_PlayerMissiles[i].m_pos);
	}

	for(i=0; i != MISSILEMAX; ++i)
	{
		if (LC_TRUE != m_EnemyMissiles[i].nAlive)
			continue;

		m_EnemyMissiles[i].Draw(m_pSpt, m_pTex);
	}

	for(i=0; i != ENEMIESMAX; ++i)
	{
		if (LC_TRUE != m_Enemies[i].nAlive)
			continue;

		m_Enemies[i].Draw(m_pSpt, m_pTex);
	}
}


void CGpApp::DrawPlayer()
{
	if (PLAYER_STATUS_ALIVE == m_PlayerStatus || PLAYER_STATUS_GHOST == m_PlayerStatus)
		m_pSpt->Draw(m_pTex[m_Player.m_nTex], &m_Cells[m_CellSelect], &m_Player.m_pos);
}


void CGpApp::DrawShield()
{
	LCXCOLOR	color(0,1, 1, m_ShieldTransparency);
	LCXVECTOR3	vcScl(1,1,1);
	LCXVECTOR3	vcTrn;

	vcScl *= (FLOAT)fabs(m_ShieldRatio);
	vcTrn = m_Player.m_pos - vcScl * 32.f + LCXVECTOR3(PLAYER_WIDTH /2.F, PLAYER_HEIGHT /2.F, 0.0F);

	m_pSpt->DrawEx(m_pTex[4], NULL, &vcTrn, &vcScl, NULL, 0, &color);
}


void CGpApp::DrawEnergyBar()
{
	LCXRECT	rc1(0,0,  (FLOAT)INT(1.5F * ENERGYBARmax), 16);
	LCXRECT	rc2(0,0,  (FLOAT)INT(1.5F * ENERGYBARmax * m_ShieldEnergy / SHIELDENERGYmax), 16);
	LCXVECTOR3	vcTrn(0, m_nScnH - 20.0F, 0.0F);
	LCXCOLOR	col2(1,0,0,0.7F);
	LCXCOLOR	col1(0,0,1,0.7F);

	m_pSpt->DrawEx(NULL, &rc1, &vcTrn, NULL, NULL, 0, &col1);
	m_pSpt->Draw(NULL, &rc2, &vcTrn, NULL, &col2);
}




void CGpApp::ObjectInitialize()
{
	INT i;
	INT	_x, _y, _w, _h;		// position x, y, width, height

	m_Player.m_nTex = 1;

	m_Player.m_pos.x =	(m_nScnW - PLAYER_WIDTH ) / 2.0F;
	m_Player.m_pos.y =	(m_nScnH - PLAYER_HEIGHT) / 2.0F;

	m_PlayerStatus = PLAYER_STATUS_ALIVE;

	for(INT cellCount = 0; cellCount != CELLNUMBER; ++cellCount)
	{
		_x = (cellCount * PLAYER_WIDTH);
		_y = 0;
		_w = PLAYER_WIDTH;
		_h = PLAYER_HEIGHT;

		m_Cells[cellCount].x = FLOAT(_x);
		m_Cells[cellCount].y = FLOAT(_y);
		m_Cells[cellCount].w = FLOAT(_w);
		m_Cells[cellCount].h = FLOAT(_h);
	}

	for(i=0; i != MISSILEMAX; ++i)
	{
		m_PlayerMissiles[i].m_nTex = 2;
		m_PlayerMissiles[i].nAlive = LC_FALSE;
		m_EnemyMissiles[i].m_nTex = 2;
		m_EnemyMissiles[i].nAlive = LC_FALSE;
	}

	for(i=0; i != ENEMIESMAX; ++i)
	{
		m_Enemies[i].m_nTex = 3;
		m_Enemies[i].nAlive = LC_FALSE;
	}

}




void CGpApp::PlayerRevive()
{
	if ((PLAYER_STATUS_DEAD == m_PlayerStatus) && (0 < m_Player.nAlive))
	{
		--m_Player.nAlive;

		m_PlayerStatus = PLAYER_STATUS_GHOST;

		m_Player.m_pos.x = m_nScnW / 2.0F;
		m_Player.m_pos.y = m_nScnH - 50.0F;
	}
}

void CGpApp::PlayerDead()
{
	m_PlayerStatus = PLAYER_STATUS_DEAD;

	if(m_Player.nAlive <= 0)
		return;

	PlayerRevive();
}

void CGpApp::UpdatePlayerMissiles()
{
	INT i;

	for(i=0; i != MISSILEMAX; ++i)
	{
		if (LC_TRUE == m_PlayerMissiles[i].nAlive)
		{
			m_PlayerMissiles[i].m_pos += m_PlayerMissiles[i].m_vlc;

			if (m_PlayerMissiles[i].m_pos.y <= -MISSILE_HEIGHT)
			{
				m_PlayerMissiles[i].nAlive = LC_FALSE;
			}
		}
	}
}

void CGpApp::UpdateEnemyMissiles()
{
	INT i;

	for(i=0; i != MISSILEMAX; ++i)
	{
		if (LC_TRUE == m_EnemyMissiles[i].nAlive)
		{
			m_EnemyMissiles[i].m_pos += m_EnemyMissiles[i].m_vlc;

			if (m_EnemyMissiles[i].m_pos.y >= m_nScnH)
			{
				m_EnemyMissiles[i].nAlive = LC_FALSE;
			}
		}
	}
}

void CGpApp::FirePlayerMissile()
{
	INT i;

	for(i=0; i != MISSILEMAX; ++i)
	{
		if (LC_FALSE == m_PlayerMissiles[i].nAlive)
		{
			m_PlayerMissiles[i].nAlive = LC_TRUE;

			m_PlayerMissiles[i].m_pos.x = m_Player.m_pos.x +  (PLAYER_WIDTH - MISSILE_WIDTH) / 2;
			m_PlayerMissiles[i].m_pos.y = m_Player.m_pos.y +  (PLAYER_HEIGHT) / 4;

			m_PlayerMissiles[i].m_vlc.y = UPDIRECTION * MISSILESPEED * (FLOAT)this->GetElapsedTimeD();

			m_pSnd[1]->Stop();
			m_pSnd[1]->Play();

			return;
		}
	}
}

void CGpApp::FireEnemyMissile(LCXVECTOR3 position, LCXVECTOR3 direction, FLOAT rotation)
{
	INT i;

	FLOAT delta = (FLOAT)this->GetElapsedTimeD();

	for(i=0; i != MISSILEMAX; ++i)
	{
		if (LC_FALSE == m_EnemyMissiles[i].nAlive)
		{
			m_EnemyMissiles[i].nAlive = LC_TRUE;

			m_EnemyMissiles[i].m_pos.x = position.x + (ENEMY_WIDTH + MISSILE_WIDTH) / 2;
			m_EnemyMissiles[i].m_pos.y = position.y + (ENEMY_HEIGHT+ MISSILE_HEIGHT) / 2;

			m_EnemyMissiles[i].m_vlc = direction * MISSILESPEED * delta;
			m_EnemyMissiles[i].m_rot = rotation;

			m_pSnd[1]->Stop();
			m_pSnd[1]->Play();

			return;
		}
	}
}

void CGpApp::UpdatePlayer()
{
	LCXVECTOR3	playerMoveDirection(0,0, 0.0F);


	if (m_pInput->KeyState(LCIK_W) || m_pInput->KeyState(LCIK_Q) || m_pInput->KeyState(LCIK_E))
	{
		playerMoveDirection.y += UPDIRECTION;
	}

	if (m_pInput->KeyState(LCIK_S) || m_pInput->KeyState(LCIK_Z) || m_pInput->KeyState(LCIK_X))
	{
		playerMoveDirection.y += DOWNDIRECTION;
	}

	if (m_pInput->KeyState(LCIK_A) || m_pInput->KeyState(LCIK_Q) || m_pInput->KeyState(LCIK_Z))
	{
		playerMoveDirection.x += LEFTDIRECTION;
	}

	if (m_pInput->KeyState(LCIK_D) || m_pInput->KeyState(LCIK_E) || m_pInput->KeyState(LCIK_X))
	{
		playerMoveDirection.x += RIGHTDIRECTION;
	}

	if (m_pInput->KeyState(LCIK_UP) && m_bIsFilre == LC_FALSE)
	{
		FirePlayerMissile();
		m_bIsFilre = LC_TRUE;
	}


	// 터치 입력 확인
	LCXVECTOR3	vcTsbPos = m_pInput->MtsPosition();
	LC_STATE	nTsbState= m_pInput->MtsState();


	if (nTsbState)
	{
		if(m_pInput->IsInRect(m_Player.m_pos.x, m_Player.m_pos.y, PLAYER_WIDTH, PLAYER_HEIGHT) )
		{
			if(m_bIsFilre == LC_FALSE)
			{
				FirePlayerMissile();

				m_bIsFilre = LC_TRUE;
			}
		}
		else
		{
			playerMoveDirection.x = vcTsbPos.x - (m_Player.m_pos.x + PLAYER_WIDTH * 0.5f);
			playerMoveDirection.y = vcTsbPos.y - (m_Player.m_pos.y + PLAYER_HEIGHT * 0.5f);
		}
	}
	else if(m_pInput->KeyState(LCIK_UP) == 0)
	{
		m_bIsFilre = LC_FALSE;
	}

	playerMoveDirection.Normalize();

	m_Player.m_vlc = playerMoveDirection * PLAYERSPEED * (FLOAT)this->GetElapsedTimeD();
	m_Player.m_pos+= m_Player.m_vlc;

	m_Player.m_pos.x = lc_clamp(m_Player.m_pos.x, 0.F,	(FLOAT)(m_nScnW - PLAYER_WIDTH  ) );
	m_Player.m_pos.y = lc_clamp(m_Player.m_pos.y, 0.F,	(FLOAT)(m_nScnH - PLAYER_HEIGHT) );

	++m_CellDisplayTime;

	if(CELLCHANGETIME <= m_CellDisplayTime)
	{
		++m_CellSelect;
		m_CellSelect = m_CellSelect % CELLNUMBER;
		m_CellDisplayTime = 0;
	}

	if(PLAYER_STATUS_GHOST == m_PlayerStatus)
	{
		++m_GhostDuration;

		if(GHOSTDURATIONmax <= m_GhostDuration)
		{
			m_PlayerStatus = PLAYER_STATUS_ALIVE;

			m_GhostDuration = 0;

			ShieldRecharge();
		}
	}
}

void CGpApp::UpdateEnemies()
{
	INT i;

	for(i=0; i != ENEMIESMAX; ++i)
	{
		if (LC_TRUE == m_Enemies[i].nAlive)
		{
			m_Enemies[i].m_pos += m_Enemies[i].m_vlc;

			if (m_Enemies[i].m_pos.y >= m_nScnH)
				m_Enemies[i].nAlive = LC_FALSE;


			if(1 > m_Random.Next(0, 100))
				FireEnemyMissile(m_Enemies[i].m_pos, m_Enemies[i].m_dir, m_Enemies[i].m_rot);
		}
		else
		{
			m_Enemies[i].nAlive = LC_TRUE;

			m_Enemies[i].m_pos.x = (FLOAT)(m_Random.Next(ENEMY_WIDTH, m_nScnW - ENEMY_WIDTH));
			m_Enemies[i].m_pos.y = -ENEMY_HEIGHT;

			LCXVECTOR3 direction = m_Player.m_pos - m_Enemies[i].m_pos;
			direction.Normalize();

			FLOAT speed = m_Random.Next(ENEMYSPEEDmin, ENEMYSPEEDmax) * 0.01F;

			m_Enemies[i].m_dir = direction;
			m_Enemies[i].m_vlc = direction * speed * (FLOAT)this->GetElapsedTimeD();

			m_Enemies[i].m_rot = (FLOAT)atan2(direction.y, direction.x) + FLOAT(LCX_PI/2.F);
		}
	}
}

void CGpApp::SaveHighScore()
{
	PLC_FILE fp = NULL;
	INT hr = 0;

	m_ScoreH = 200;

	//hr = LcFile_Open(NULL, &fp, (char*)"data/save_info.dat", (char*)"wt");
	//if(LC_FAILED(hr))
	//	return;


	//char sline[128]={0};
	//sprintf(sline, "%d\n", m_ScoreH);

	//printf("Write score: %s\n", sline);
	//fp->WriteByte(sline, strlen(sline));
	//SAFE_RELEASE(	fp	);
}


void CGpApp::LoadHighScore()
{
	PLC_FILE fp = NULL;
	INT hr = 0;
	
	m_ScoreH = 200;

	//hr = LcFile_Open(NULL, &fp, (char*)"data/save_info.dat", (char*)"rt");
	//if(LC_FAILED(hr))
	//	return;


	//char sline[128]={0};

	//fp->ReadLine(sline, 120);

	//sscanf(sline, "%d", &m_ScoreH);
	//SAFE_RELEASE(	fp	);
}


void CGpApp::UpdateHighScore()
{
	if (m_ScoreH < m_Score)
	{
		m_ScoreH = m_Score;
	}
}



void CGpApp::DrawPlayerLife()
{
	if (0 < m_Player.nAlive)
	{
		FLOAT scale = 0.5f;

		LCXVECTOR3 scl(scale, scale, 1.0F);

		INT marginWidth = (INT)(PLAYER_WIDTH * (1.0f - scale) * 0.5f);
		INT marginHeight = (INT)(PLAYER_HEIGHT * (1.0f - scale) * 0.5f);

		LCXVECTOR3 position(0,0,0);
		position.x = (FLOAT)(-marginWidth);
		position.y = (FLOAT)(m_nScnH - (PLAYER_HEIGHT - marginHeight));

		for (INT count = 0; count < m_Player.nAlive; ++count)
		{
			m_pSpt->DrawEx(m_pTex[m_Player.m_nTex], &m_Cells[3], &position, &scl, NULL, 0, NULL);
			position.x = position.x + PLAYER_WIDTH - (marginWidth * 2);
		}
	}
}

void CGpApp::ScrollBackground()
{
	switch (m_ScrollDirection)
	{
	case SCROLL_DIRECTION_LEFT:
		{
			m_BgPosition.x -= SCROLLSPEED * (FLOAT)this->GetElapsedTimeD();

			break;
		}
	case SCROLL_DIRECTION_RIGHT:
		{
			m_BgPosition.x += SCROLLSPEED * (FLOAT)this->GetElapsedTimeD();

			break;
		}
	case SCROLL_DIRECTION_UP:
		{
			m_BgPosition.y -= SCROLLSPEED * (FLOAT)this->GetElapsedTimeD();

			break;
		}
	case SCROLL_DIRECTION_DOWN:
		{
			m_BgPosition.y += SCROLLSPEED * (FLOAT)this->GetElapsedTimeD();

			break;
		}
	}

	while (-m_nScnH >= m_BgPosition.y)
	{
		m_BgPosition.y += m_nScnH;
	}
	while (0 < m_BgPosition.y)
	{
		m_BgPosition.y -= m_nScnH;
	}
	while (m_nScnW >= m_BgPosition.x)
	{
		m_BgPosition.x += m_nScnW;
	}
	while (0 < m_BgPosition.x)
	{
		m_BgPosition.x -= m_nScnW;
	}
}

void CGpApp::DrawBackground()
{
	LCXVECTOR3 repeatPosition(0,0,0);
	repeatPosition.x = m_BgPosition.x;
	repeatPosition.y = m_BgPosition.y;

	while (m_nScnH > repeatPosition.y)
	{
		while(m_nScnW > repeatPosition.x)
		{
			m_pSpt->Draw(m_pTex[0], NULL, &repeatPosition);

			repeatPosition.x += m_nScnW;
		}

		repeatPosition.x = m_BgPosition.x;
		repeatPosition.y += m_nScnH;
	}
}

void CGpApp::CollisionPlayerMissilesAndEnemies()
{
	for (INT sourceIndex = 0; sourceIndex != MISSILEMAX; ++sourceIndex)
	{
		if (LC_TRUE == m_PlayerMissiles[sourceIndex].nAlive)
		{
			for (INT targetIndex = 0; targetIndex != ENEMIESMAX; ++targetIndex)
			{
				if (LC_TRUE == m_Enemies[targetIndex].nAlive)
				{
					if (LC_OK <= LCXCollisionRect2RectLTWH(
						m_PlayerMissiles[sourceIndex].m_pos.x, m_PlayerMissiles[sourceIndex].m_pos.y,
						(FLOAT)MISSILE_WIDTH, (FLOAT)MISSILE_HEIGHT,
						m_Enemies[targetIndex].m_pos.x, m_Enemies[targetIndex].m_pos.y,
						(FLOAT)ENEMY_WIDTH, (FLOAT)ENEMY_HEIGHT))
					{
						m_PlayerMissiles[sourceIndex].nAlive = LC_FALSE;
						m_Enemies[targetIndex].nAlive = LC_FALSE;

						m_Score += 100;

						UpdateHighScore();

						DrawScore();

						m_pSnd[2]->Stop();
						m_pSnd[2]->Play();

						break;
					}
				}
			}
		}
	}
}

void CGpApp::CollisionPlayerAndEnemies()
{
	INT i;

	if (PLAYER_STATUS_ALIVE == m_PlayerStatus)
	{
		for(i=0; i != ENEMIESMAX; ++i)
		{
			if (LC_TRUE == m_Enemies[i].nAlive)
			{
				if (LC_OK <= LCXCollisionRect2RectLTWH(
					m_Enemies[i].m_pos.x, m_Enemies[i].m_pos.y,
					(FLOAT)ENEMY_WIDTH, (FLOAT)ENEMY_HEIGHT,
					m_Player.m_pos.x, m_Player.m_pos.y,
					(FLOAT)PLAYER_WIDTH,(FLOAT)PLAYER_HEIGHT))
				{
					m_Enemies[i].nAlive = LC_FALSE;

					if(LC_FALSE == ShieldProtect(30))
					{
						PlayerDead();
					}

					m_pSnd[2]->Stop();
					m_pSnd[2]->Play();

					break;
				}
			}
		}
	}
}

void CGpApp::CollisionEnemyMissilesAndPlayer()
{
	INT i;

	if (PLAYER_STATUS_ALIVE != m_PlayerStatus)
		return;


	for(i=0; i != MISSILEMAX; ++i)
	{

		if (LC_TRUE == m_EnemyMissiles[i].nAlive)
		{
			if (LC_OK <= LCXCollisionRect2RectLTWH(
				m_EnemyMissiles[i].m_pos.x, m_EnemyMissiles[i].m_pos.y,
				(FLOAT)MISSILE_WIDTH, (FLOAT)MISSILE_HEIGHT,
				m_Player.m_pos.x, m_Player.m_pos.y,
				(FLOAT)PLAYER_WIDTH, (FLOAT)PLAYER_HEIGHT))
			{
				m_EnemyMissiles[i].nAlive = LC_FALSE;

				if(LC_FALSE == ShieldProtect(10))
				{
					PlayerDead();
				}

				m_pSnd[2]->Stop();
				m_pSnd[2]->Play();

				break;
			}
		}
	}
}



void CGpApp::SetVolume()
{
	if(m_pInput->KeyDown(LCIK_F8))
	{
		m_Volume +=0.1f;
		m_Volume = lc_clamp(m_Volume, 0.F, 2.F);

		m_pSnd[0]->SetVolume(m_Volume);
		m_pSnd[1]->SetVolume(m_Volume);
		m_pSnd[2]->SetVolume(m_Volume);
	}
	else if (m_pInput->KeyPress(LCIK_F7))
	{
		m_Volume -=0.1f;
		m_Volume = lc_clamp(m_Volume, 0.F, 2.F);

		m_pSnd[0]->SetVolume(m_Volume);
		m_pSnd[1]->SetVolume(m_Volume);
		m_pSnd[2]->SetVolume(m_Volume);
	}
}


void CGpApp::SystemControl()
{
	if(m_pInput->KeyDown(LCIK_ESCAPE))
	{
		m_Player.nAlive = 0;
	}

	SetVolume();
}



void CGpApp::DrawScore()
{
	memset(m_sScore, 0, 256);
	sprintf(m_sScore, "Score : %d / HighScore : %d", m_Score, m_ScoreH);

	LCXCOLOR	color(1,0,0,1);
	LCXVECTOR3	vcPos(5,5,0);

	m_pFontScore->Color(&color);
	m_pFontScore->Position(&vcPos);
	m_pFontScore->String(m_sScore);
}




