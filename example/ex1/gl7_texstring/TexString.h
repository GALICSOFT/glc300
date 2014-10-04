// Interface for the CTexString class.
//
////////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER) && _MSC_VER > 1000
	#pragma once
#endif

#ifndef _TexString_H_
#define _TexString_H_


class CTexString
{
public:
	struct Tvector2
	{
		float x, y;
	};

	struct TvtxChar
	{
		Tvector2	v[6];	// Position or Texture Coordiante
	};


protected:
	PLC_TEXTURE		m_pTex;								// Texture ID

	float			m_Red, m_Green, m_Blue, m_Alpha;	// Font color
	float			m_X, m_Y;							// Font Draw Position

	float			m_Hgt;								// String Height

	char*			m_Str;								// String Data
	int				m_VtxC;								// Character Number
	TvtxChar*		m_VtxP;								// Vertex Position List
	TvtxChar*		m_VtxT;								// Vertex Texture Coordinate List

	PLC_EFFECT		m_pEft;

public:
	CTexString();
	virtual ~CTexString();

	int		Create(char* sTexture, int Height);
	void	Destroy();


	void	String(char* Str);
	void	Position(float x, float y);
	void	Color(float r, float g, float, float a=1.F);
	int		DrawTxt();

	void	Effect(PLC_EFFECT v)
	{
		m_pEft = v;
	}

protected:
	void	SetupVertex();
	void	ClearVertex();
	void	SetupVtxChar(int n, int c);

public:
	static TvtxChar	m_CharL[8 * 16]; //save char uv, 8 = rows, 16 = columns
	static int		m_CharI;		// Original Character List Intialized

protected:
	void InitChar();
};

#endif


