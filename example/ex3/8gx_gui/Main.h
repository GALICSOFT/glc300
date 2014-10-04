// Interface for the CMain class.
//
////////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER)
  #pragma once
#endif

#ifndef _CMain_H_
#define _CMain_H_


class CMain : public CAppGame
{
protected:
	PLCX_INPUT		m_pInput;		// Input
	PLCX_ENTITY		m_pXYZ	;		// X, Y, Z Axis Line

	PLCX_UI			m_pUi0	;		// Sprite animation ui

public:
	CMain();

	virtual INT		Init();
	virtual INT		Destroy();
	virtual INT		FrameMove();
	virtual INT		Render();
};

extern	CMain*	g_pApp;
#define	GMAIN	g_pApp

#endif


