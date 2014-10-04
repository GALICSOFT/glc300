// RndObj.h: interface for the CRndObj class.
//
////////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER) && _MSC_VER > 1000
	#pragma once
#endif

#ifndef _RndObj_H_
#define _RndObj_H_


class CRndObj
{
protected:
	PLC_DEVICE			m_pDev;			// Rendering Device
	LCXMATRIX			m_mtWld;		// Object world Matrix
	PLC_TEXTURE			m_pTex;			// Texture

	INT					m_nFce;			// Face Number
	LC3D::VtxFce16*		m_pIdx;			// Common Index Data
	LC3D::VtxUV1*		m_pVtx;			// Vertex Data

public:
	CRndObj();
	virtual ~CRndObj();

	INT		Create(PLC_ARGS pArg);
	void	Destroy();

	INT		FrameMove();
	void	Render();

	void	SetMatrix(const LCXMATRIX* v);
	void	SetIdx(const void* v, INT nFace);
	void	SetVtx(const void* v);
};

#endif



