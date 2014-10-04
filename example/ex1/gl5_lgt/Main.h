// Interface for the CMain class.
//
////////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER) && _MSC_VER > 1000
	#pragma once
#endif

#ifndef _CMain_H_
#define _CMain_H_



//Structure to hold the optimized mesh data for rendering
struct FixedMesh
{
	GLshort		indexCounter;
	GLshort		vertexCounter;

	GLshort*	Indices;
	GLfloat*	pos;
	GLfloat*	nor;
	GLfloat*	TexCoord;
};



class CMain : public CAppGame
{
protected:
	FixedMesh*	m_pMesh;

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
	LCXMATRIX	m_mtWVP;	// world * view * projection
	LCXMATRIX	m_mtRot;

protected:
	PLC_EFFECT	m_pEft;
};

extern	CMain*	g_pApp;
#define	GMAIN	g_pApp

#endif


