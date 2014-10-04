// Interface for the CMain class.
//
////////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER) && _MSC_VER > 1000
	#pragma once
#endif

#ifndef _CMain_H_
#define _CMain_H_


#define FBO_SCN_W	1024


class CMain : public CAppGame
{
protected:
	PLC_EFFECT		m_pEft	;
	PLC_TEXTURE		m_pTex	;		// Texture

	PLC_FBO			m_pFbo	;		// Frame buffer object

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

