// Interface for the CMain class.
//
////////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER) && _MSC_VER > 1000
	#pragma once
#endif

#ifndef _CMain_H_
#define _CMain_H_



#pragma pack(push, 2)

struct TvtxNUV1 : LC3D::VtxNUV1
{
	TvtxNUV1()
	{
		p.x = 0; p.y = 0; p.z = 0;
		n.x = 0; n.y = 0; n.z = 0;
		t.x = 0; t.y = 0;
	}

	TvtxNUV1( FLOAT X, FLOAT Y, FLOAT Z
			, FLOAT Nx, FLOAT Ny, FLOAT Nz
			, FLOAT U, FLOAT V)
	{
		p.x = X; p.y = Y; p.z = Z;
		n.x = Nx; n.y = Ny; n.z = Nz;
		t.x = U; t.y = V;
	}
};

struct TvtxIdx
{
	WORD a, b, c;
};

#pragma pack(pop)


class CMain : public CAppGame
{
protected:
	PLCX_INPUT		m_pInput;	// Input
	PLCX_CAMERA		m_pCam	;	// Camera Instance

	PLCX_ENTITY		m_pXYZ	;	// X, Y, Z Axis Line
	PLCX_ENTITY		m_pGrid	;	// Grid for Test

	LCXMATRIX		m_mtWld	;
	PLC_TEXTURE		m_pTex	;	// wood

	PLC_MRC			m_pMRC	;		// sub rendering context pointer
public:
	CMain();

	virtual INT	Init();
	virtual INT	Destroy();
	virtual INT	FrameMove();
	virtual INT	Render();

protected:
	void	Draw();
};

extern	CMain*	g_pApp;
#define	GMAIN	g_pApp

#endif


