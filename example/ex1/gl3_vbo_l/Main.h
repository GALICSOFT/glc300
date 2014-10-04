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

public:
	CMain();

	virtual int		Init();
	virtual int		Destroy();
	virtual int		FrameMove();
	virtual int		Render();

protected:
	LCXMATRIX	m_mtWld;
	LCXMATRIX	m_mtViw;
	LCXMATRIX	m_mtPrj;

	PLC_EFFECT	m_pEft;
	PLC_VB		m_pVB;
	PLC_IB		m_pIB[6];
};

extern	CMain*	g_pApp;
#define	GMAIN	g_pApp

#endif


