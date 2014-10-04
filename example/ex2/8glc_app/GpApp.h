// Interface for the CGpApp class.
//
//  Created by Heesung Oh on 2011. 01. 19.
//  Copyright GALIC SOFT Inc. All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER)
  #pragma once
#endif

#ifndef _GpApp_H_
#define _GpApp_H_


class CGpApp : public ILC_AppFrame
{
// for system data
protected:
	char			m_sCls		[LC_MAX_PATH];

	INT				m_nScnW		;		// Screen Width
	INT				m_nScnH		;		// Screen Height
	INT				m_nScnD		;		// Depth Buffer bit
	INT				m_nScnX		;		// Screen Position X
	INT				m_nScnY		;		// Screen Position Y
	INT				m_bShowSt	;		// show state enable

	PLC_DEVICE		m_pDev		;		// LC_DEVICE
	PLC_SPRITE		m_pSpt		;		// 2D Sprite
	PLCX_INPUT		m_pInput	;		// Input
	DOUBLE			m_TimeFPS	;		// Frame Per Second
	DOUBLE			m_TimeElps	;		// Ellapsed time

// miscellany
protected:
	PLC_FONT		m_misFont	;		// Test Font

// game data
protected:
	INT				m_score		;		// test score
	PLC_FONT		m_pFontApp	;		// for game application font
	PLC_TEXTURE		m_pTex0		;		// for game application texture 0
	PLC_TEXTURE		m_pTex1		;		// for game application texture 1
	PLC_TEXTURE		m_pTex2		;		// for game application texture 2
	PLCX_SOUND		m_pSnd0		;		// ogg background sound
	PLCX_SOUND		m_pSnd1		;		// ogg sound 1
	PLCX_SOUND		m_pSnd2		;		// ogg sound 2
	PLCX_SOUND		m_pSnd3		;		// wave sound 3
	PLCX_SOUND		m_pSnd4		;		// wave sound 4

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
};


#endif
