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
public:
	CMain();

	virtual int		Init();
	virtual int		Destroy();
	virtual int		FrameMove();
	virtual int		Render();

protected:
	LCXMATRIX		m_mtViw;
	LCXMATRIX		m_mtPrj;

	GL_SHADER		m_VsShader;
	GL_SHADER		m_FgShader;
	GL_PROGRAM		m_program;

	int SetupShader();
};

extern	CMain*	g_pApp;
#define	GMAIN	g_pApp

#endif


