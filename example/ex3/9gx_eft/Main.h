// Interface for the CMain class.
//
////////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER)
  #pragma once
#endif

#ifndef _CMain_H_
#define _CMain_H_


struct MyEft2D1 : public TLCX_EPS_ELM
{
	virtual INT Init  (LC_HANDLE _init);
	virtual INT Reset (LC_HANDLE _init);
	virtual INT Update(LC_HANDLE _init);
};


struct MyEft2D2 : public TLCX_EPS_ELM
{
	virtual INT Init  (LC_HANDLE _init);
	virtual INT Reset (LC_HANDLE _init);
	virtual INT Update(LC_HANDLE _init);
};


struct MyEft2D3 : public TLCX_EPS_ELM
{
	virtual INT Init  (LC_HANDLE _init);
	virtual INT Reset (LC_HANDLE _init);
	virtual INT Update(LC_HANDLE _init);
};


struct MyEft3D1 : public TLCX_EPS_ELM
{
	virtual INT Init  (LC_HANDLE _init);
	virtual INT Reset (LC_HANDLE _init);
	virtual INT Update(LC_HANDLE _init);
};


struct MyEft3D2 : public TLCX_EPS_ELM
{
	virtual INT Init  (LC_HANDLE _init);
	virtual INT Reset (LC_HANDLE _init);
	virtual INT Update(LC_HANDLE _init);
};

class CMain : public CAppGame
{
protected:
	PLCX_INPUT		m_pInput	;		// Input
	PLCX_CAMERA		m_pCam		;		// Camera Instance

	PLCX_ENTITY		m_pXYZ		;		// X, Y, Z Axis Line
	PLCX_ENTITY		m_pGrid		;		// Grid Instance

	PLC_TEXTURE		m_pTex		;		// Extern Texture

	PLCX_EPS		m_pEps2d1	;
	PLCX_EPS		m_pEps2d2	;
	PLCX_EPS		m_pEps2d3	;
	PLCX_EPS		m_pEps2d4	;

	PLCX_EPS		m_pEps3d1	;
	PLCX_EPS		m_pEps3d2	;

	PLCX_ETA		m_pEta0		;
	PLCX_ETA		m_pEta1		;

	PLCX_ETB		m_pEtb0		;
	PLCX_ETB		m_pEtb1		;

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


