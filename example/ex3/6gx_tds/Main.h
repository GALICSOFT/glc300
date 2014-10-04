// Interface for the CMain class.
//
////////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER) && _MSC_VER > 1000
	#pragma once
#endif

#ifndef _CMain_H_
#define _CMain_H_


class CMain : public CAppGame
{
protected:
	PLC_SPRITE		m_pLyr		;		// sprite Layer
	PLCX_INPUT		m_pInput	;		// Input
	PLCX_ENTITY		m_pXYZ		;		// X, Y, Z Axis Line

	PLCX_TDS		m_pTds0		;		// 2D Model Sequence
	PLCX_TDS		m_pTds1		;		// 2D Model Sequence

public:
	CMain();

	virtual INT	Init();
	virtual INT	Destroy();
	virtual INT	FrameMove();
	virtual INT	Render();

protected:

};

extern	CMain*	g_pApp;
#define	GMAIN	g_pApp

#endif


