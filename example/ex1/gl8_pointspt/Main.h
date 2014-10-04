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
	CParticle*		m_pPtc;
	CTexString*		m_pStr;

public:
	CMain();

	virtual int		Init();
	virtual int		Destroy();
	virtual int		FrameMove();
	virtual int		Render();

protected:
	PLC_EFFECT	m_pEftTxt;
	PLC_EFFECT	m_pEftPtc[2];
};

extern	CMain*	g_pApp;
#define	GMAIN	g_pApp

#endif


