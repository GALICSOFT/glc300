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
	PLCX_CAMERA		m_pCam	;		// Camera Instance

	PLCX_ENTITY		m_pXYZ	;		// X, Y, Z Axis Line
	PLCX_ENTITY		m_pGrid	;		// Grid Instance

	PLC_TEXTURE		m_pTex	;		// star128.tga
	PLCX_MOSQC		m_pMoSqc;		// Motion sequence

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


