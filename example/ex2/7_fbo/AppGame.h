// Interface for the CAppGame class.
//
////////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER) && _MSC_VER > 1000
	#pragma once
#endif

#ifndef _AppGame_H_
#define _AppGame_H_


class CAppGame
{
protected:
	PLC_DEVICE		m_pDev		;				// LC_DEVICE
	PLC_SPRITE		m_pSpt		;				// 2D Spritem_pSpt

	char			m_sCls[128]	;				// Program Class Name

	INT				m_nScnW		;				// Screen Width
	INT				m_nScnH		;				// Screen Height

	DOUBLE			m_TimeElps	;				// Elapsed Time
	DOUBLE			m_TimeFPS	;				// Frame Per Second

public:
	virtual INT		Init()		{	return 0;	}
	virtual INT		Destroy()	{	return 0;	}
	virtual INT		FrameMove()	{	return 0;	}
	virtual INT		Render()	{	return 0;	}

	virtual INT		Create(PLC_ARGS pArg=NULL);
	virtual INT		Run(LC_HANDLE);

	virtual INT		Proc(LC_HANDLE);

public:
	CAppGame();
	static CAppGame*	m_pAppGame;
	static INT	   LC_CALLBACK Run3D(LC_HANDLE);			// Main Processing
protected:
	INT		Cleanup();
	void	UpdateStatus();

public:
	DOUBLE	GetFPS()			{	return m_TimeFPS;	}
	DOUBLE	GetElapsedTime()	{	return m_TimeElps;	}
};


#endif

