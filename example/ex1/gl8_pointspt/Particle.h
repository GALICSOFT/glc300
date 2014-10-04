// Interface for the CParticle class.
//
////////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER) && _MSC_VER > 1000
	#pragma once
#endif

#ifndef _Particle_H_
#define _Particle_H_


class CParticle
{
public:
	struct Tptc	// particle
	{
		LCXVECTOR2		pos1;		// Position
		LCXCOLOR		col;		// color
		FLOAT			size;
		LCXVECTOR2		vec;		// velocity
	};

	struct VtxDUV
	{
		LCXVECTOR2		p;			// position
		LCXCOLORB		d;			// color
		LCXVECTOR2		t;			// Texture coordinate
	};

protected:
	PLC_TEXTURE		m_pTex;			// Texture ID

	int				m_PtcN;			// Number of Particle
	Tptc*			m_Ptc;			// Particle
	VtxDUV*			m_vtx;			// vertex buffer

	PLC_EFFECT		m_pEft[16];

	int				m_bHardware;

public:
	CParticle();
	virtual ~CParticle();

	int		Create(char* sTexture, int ParticleNumber);
	void	Destroy();

	int		FrameMove();
	void	Render();

	void	SetEffect(PLC_EFFECT* v, int count)
	{
		int n=0; 
		for(; n<count; ++n)
			m_pEft[n] = v[n];


		for(; n<16; ++n)
			m_pEft[n] = NULL;
	}
	
protected:
	void	InitPtc(int n);
};

#endif


