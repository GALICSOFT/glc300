// Interface for the CMain class.
//
////////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER) && _MSC_VER > 1000
	#pragma once
#endif

#ifndef _CMain_H_
#define _CMain_H_


#define MAX_NUM 16

class CMain : public CAppGame
{
protected:
	PLCX_INPUT		m_pInput;				// Input
	PLCX_CAMERA		m_pCam;					// Camera Instance

	PLCX_ENTITY		m_pXYZ	;				// X, Y, Z Axis Line
	PLCX_ENTITY		m_pGrid	;				// Grid Instance

	PLCX_MDL		m_pMdl[MAX_NUM];		// Original


public:
	CMain();

	virtual INT	Init();
	virtual INT	Destroy();
	virtual INT	FrameMove();
	virtual INT	Render();
};

extern	CMain*	g_pApp;
#define	GMAIN	g_pApp

#endif


