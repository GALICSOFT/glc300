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
	unsigned int	m_TexID0;
	unsigned int	m_TexID1;
	
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

protected:
	PLC_EFFECT	m_pEft;
};

extern	CMain*	g_pApp;
#define	GMAIN	g_pApp

#endif


