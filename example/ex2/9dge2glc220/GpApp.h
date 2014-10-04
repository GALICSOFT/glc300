// Interface for the CGpApp class.
//
//  Written by Heesung Oh on 2011. 01. 19.
//  Copyright GALIC SOFT Inc. All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER)
  #pragma once
#endif

#ifndef _GpApp_H_
#define _GpApp_H_


#define	PLAYER_WIDTH		64
#define	PLAYER_HEIGHT		64

#define	PLAYERSPEED			1.4F
#define PLAYERINITLIFE		3

#define	MISSILE_WIDTH		7
#define	MISSILE_HEIGHT		4

#define	ENEMY_WIDTH			41
#define	ENEMY_HEIGHT		40

#define	SHIELD_WIDTH		64
#define	SHIELD_HEIGHT		64

#define	GAME_MAX_TEXTURE	8
#define	GAME_MAX_SOUND		4

#define	GHOSTDURATIONmax	180
#define	CELLNUMBER			4
#define	CELLCHANGETIME		30


#define LEFTDIRECTION		-1.0f
#define RIGHTDIRECTION		+1.0f
#define UPDIRECTION			-1.0f
#define DOWNDIRECTION		+1.0f

#define	MISSILESPEED		3.0F
#define	MISSILEMAX			3

#define ENEMYSPEEDmin		50
#define ENEMYSPEEDmax		100
#define	ENEMIESMAX			10

#define SCROLLSPEED			1.0F
#define SHIELDRATIOmax		1.8f
#define SHIELDRATIOmin		1.2f
#define	SHIELDENERGYmax		100
#define	ENERGYBARmax		160


enum PLAYER_STATUS
{
	PLAYER_STATUS_ALIVE,
	PLAYER_STATUS_DEAD,
	PLAYER_STATUS_GHOST,
};


enum SCROLL_DIRECTION
{
	SCROLL_DIRECTION_LEFT,
	SCROLL_DIRECTION_RIGHT,
	SCROLL_DIRECTION_UP,
	SCROLL_DIRECTION_DOWN,
};



class CGpApp : public ILC_AppFrame
{
// for system data
protected:
	char			m_sCls[LC_MAX_PATH];

	INT				m_nScnW		;		// Screen Width
	INT				m_nScnH		;		// Screen Height
	INT				m_nScnD		;		// Depth Buffer bit
	INT				m_nScnX		;		// Screen Position X
	INT				m_nScnY		;		// Screen Position Y
	INT				m_bShowSt	;		// Screen Position Y

	PLC_DEVICE		m_pDev		;		// LC_DEVICE
	PLC_SPRITE		m_pSpt		;		// 2D Sprite
	PLCX_INPUT		m_pInput	;		// Input
	DOUBLE			m_TimeFPS	;		// Frame Per Second
	DOUBLE			m_TimeElps	;		// Ellapsed time
	PLC_FONT		m_pFont		;		// Test Font

// game data
protected:
	PLC_FONT		m_pFontScore;		// Font Score
	PLC_TEXTURE		m_pTex[GAME_MAX_TEXTURE];
	PLCX_SOUND		m_pSnd[GAME_MAX_SOUND]	;

	TLC_RAND	m_Random;
	INT			m_PlayerStatus;
	INT			m_bIsFilre;
	GameObject	m_Player;

	INT			m_GhostDuration;

	LCXRECT		m_Cells[CELLNUMBER];
	INT			m_CellSelect;
	INT			m_CellDisplayTime;

	GameObject	m_PlayerMissiles[MISSILEMAX];
	GameObject	m_EnemyMissiles[MISSILEMAX];
	GameObject	m_Enemies[ENEMIESMAX];

	INT			m_Score;
	INT			m_ScoreH;			// High Score
	char		m_sScore[256];

	FLOAT		m_Volume;

	LCXVECTOR2	m_BgPosition;				// Back ground Position
	INT			m_ScrollDirection;

	FLOAT		m_ShieldRatio;
	INT			m_ShieldTimeDelta;
	DOUBLE		m_ShieldTimeBgn;
	FLOAT		m_ShieldExtend;
	FLOAT		m_ShieldTransparency;
	INT			m_ShieldEnergy;

	INT			m_nSkip;



public:
	CGpApp();
	virtual ~CGpApp(){}

	virtual INT		Query(char*, LC_HANDLE);
	virtual INT		Release()	{ return LC_EFAIL;	}

	virtual INT		Create(PLC_ARGS =NULL);
	virtual INT		Cleanup();

	virtual INT		Run(LC_HANDLE  =NULL);
	virtual INT		Proc(LC_HANDLE  =NULL);

	virtual INT		SetAttrib(UINT, LC_HANDLE);
	virtual INT		GetAttrib(UINT, LC_HANDLE);

	virtual INT		Init();
	virtual INT		Destroy();
	virtual INT		FrameMove();
	virtual INT		Render();

public:
	static CGpApp*	m_pApp;
	static INT	   LC_CALLBACK Run3D(LC_HANDLE);					// Main Processing
	static LRESULT LC_WINAPI   WndProc(LC_HWND,UINT,WPARAM,LPARAM);	// Window Procedure

public:
	DOUBLE		GetFPS()		{	return m_TimeFPS;		}
	DOUBLE		GetElapsedTime(){	return m_TimeElps;		}		// per millisecond
	DOUBLE		GetElapsedTimeS(){	return m_TimeElps/1000.;}		// per second
	DOUBLE		GetElapsedTimeD(){	return m_TimeElps/10.;	}		// per deci-second
	PLC_DEVICE	GetDevice()		{	return m_pDev;			}
	INT			Invalid();
	INT			Restore();

protected:
	void	UpdateStatus();




public:
	void SystemControl();
	void UpdatePlayer();
	void UpdatePlayerMissiles();
	void UpdateEnemies();
	void UpdateEnemyMissiles();
	void UpdateHighScore();

	void CollisionPlayerMissilesAndEnemies();
	void CollisionPlayerAndEnemies();
	void CollisionEnemyMissilesAndPlayer();

	void ShieldPulse();
	void ShieldRecharge();
	INT  ShieldProtect(INT damage);
	void ScrollBackground();

	void DrawBackground();
	void DrawMissile();
	void DrawPlayer();
	void DrawShield();
	void DrawEnergyBar();
	void DrawPlayerLife();
	void DrawScore();

	void ObjectInitialize();

	void LoadHighScore();
	void SaveHighScore();


	void PlayerRevive();
	void PlayerDead();

	void FirePlayerMissile();
	void FireEnemyMissile(LCXVECTOR3 position, LCXVECTOR3 direction, FLOAT rotation);

	void SetVolume();
};


#endif

