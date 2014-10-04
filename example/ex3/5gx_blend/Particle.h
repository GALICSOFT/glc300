// Interface for the Particle class.
//
////////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER) && _MSC_VER > 1000
	#pragma once
#endif

#ifndef _CParticle_H_
#define _CParticle_H_

class CParticle
{
public:
	struct VtxUV1 : public LC3D::VtxUV1
	{
		VtxUV1()
		{
			p.x = 0; p.y = 0; p.z = 0;
			t.x = 0; t.y = 0;
		}

		VtxUV1(FLOAT X,FLOAT Y,FLOAT Z,FLOAT U,FLOAT V)
		{
			p.x = X; p.y = Y; p.z = Z;
			t.x = U; t.y = V;
		}
	};

	struct TPart
	{
		LCXCOLOR	d;	// Color
		FLOAT		a;	// Angle(Degree)
		FLOAT		r;	// Radius
	};


protected:
	PLC_DEVICE		m_pDev	;			// LC_DEVICE
	PLC_TEXTURE		m_pTex	;			// Texture 0

	INT				m_nPrt	;
	TPart*			m_pPrt	;

public:
	CParticle();
	virtual ~CParticle();

	INT		Create();
	void	Destroy();
	INT		FrameMove();
	void	Render();

protected:
	void	PartSetup(INT nIdx);
	void	PartReset(INT nIdx);
};

#endif



