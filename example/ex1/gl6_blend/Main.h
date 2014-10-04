// Interface for the CMain class.
//
////////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER) && _MSC_VER > 1000
	#pragma once
#endif

#ifndef _CMain_H_
#define _CMain_H_


#define MAX_STAR_NUM 90


class CMain : public CAppGame
{
public:
	struct Tpaticle
	{
		float r, g, b;			// color
		float dist;				// Distance from center
		float angle;			// Angle
		float radius;
	};

protected:
	Tpaticle		m_pStar[MAX_STAR_NUM];
	PLC_TEXTURE		m_pTex;

public:
	CMain();

	virtual int		Init();
	virtual int		Destroy();
	virtual int		FrameMove();
	virtual int		Render();
	
protected:
	LCXMATRIX	m_mtViw;
	LCXMATRIX	m_mtPrj;

protected:
	PLC_EFFECT	m_pEft;
};

extern	CMain*	g_pApp;
#define	GMAIN	g_pApp

#endif


