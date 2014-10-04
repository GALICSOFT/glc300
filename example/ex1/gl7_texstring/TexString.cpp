// Implementation of the CTexString class.
//
//
//
////////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER) && _MSC_VER >= 1200
  #pragma warning( disable : 4786)
  #pragma warning( disable : 4996)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <gles/gl2.h>

#include <LcType.h>
#include <LcBase.h>
#include <LcMath.h>
#include <LcEuclid.h>
#include <LcCore.h>
#include <LcAux.h>

#include "TexString.h"


CTexString::TvtxChar CTexString::m_CharL[];
int					 CTexString::m_CharI =0;


CTexString::CTexString()
{
	m_pTex	= NULL;
	m_Red	= 1.F;
	m_Green	= 1.F;
	m_Blue	= 1.F;
	m_Alpha	= 1.F;

	m_X		= 0;
	m_Y		= 0;

	m_Hgt	= 12;

	m_Str	= NULL;
	m_VtxC	= 0;
	m_VtxP	= NULL;
	m_VtxT	= NULL;

	m_pEft	= NULL;
}


CTexString::~CTexString()
{
	Destroy();
}


void CTexString::Destroy()
{
	if(m_Str)
	{
		delete [] m_Str;
		m_Str = NULL;
	}

	ClearVertex();

	SAFE_RELEASE(	m_pTex	);
	SAFE_RELEASE(	m_pEft	);
}


int CTexString::Create(char* sTexture, int Height)
{
	int	hr = 0;


	int	ImgW	= 0;
	int	ImgH	= 0;
	int	ImgC	= 0;
	int	ImgF	= 0;
	unsigned char* pPxl = NULL;


	TLC_ARGS args;

	MAKE_ARG4(args, (char*)sTexture, 0, 0, (INT)1);
	hr = LcDev_CreateTextureFromFile(NULL, &m_pTex, &args);
	if(0>hr)
		return LC_EFAIL;



	m_Hgt = (float)Height;


	if(!CTexString::m_CharI)
		InitChar();

	return LC_OK;
}

void CTexString::String(char* Str)
{
	// Clear String
	if(NULL == Str ||
		(Str && (*Str == '\0' || *Str == '\n' || *Str == '\r')  )
		)
	{
		if(m_Str)
			delete m_Str;

		m_Str = NULL;

		ClearVertex();
		return;
	}

	// Is same to m_Str?
	if(m_Str && 0 == strcmp(m_Str, Str) )
		return;


	int nStr = strlen(Str);

	nStr = ( (nStr + 3)/4 +1)*4;		// make  multiple of 4.

	// delete String, remake and copy string
	if(m_Str)
		delete [] m_Str;

	m_Str = new char[nStr];
	memset(m_Str, 0, sizeof(char) * nStr);
	strcpy(m_Str, Str);

	// Clear vertex List
	ClearVertex();

	// remake vertex List
	SetupVertex();
}




void CTexString::Position(float x, float y)
{
	m_X = x;
	m_Y = y;
}

void CTexString::Color(float r, float g, float b, float a)
{
	m_Red  = r;
	m_Green= g;
	m_Blue = b;
	m_Alpha= a;
}



int CTexString::DrawTxt()
{
	if(0 == m_VtxC)
		return LC_OK;


	glEnable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	LCXMATRIX	mtPrj;
	LCXMATRIX	mtWld;

	float	temp[16]={0};
	float	w, h;
	glGetFloatv(GL_VIEWPORT, temp);
	w = temp[2];
	h = temp[3];
	
	mtPrj.OrthoGl(0.F,   w
					,   h, 0.F
					, -1.0F, 1.0F);

	mtWld.Translation(m_X, m_Y, 0);

	m_pEft->Begin();

	m_pEft->Matrix4("uf_Wld", &mtWld);
	m_pEft->Matrix4("uf_Prj", &mtPrj);
	m_pEft->Float4 ("uf_dif", m_Red, m_Green, m_Blue, m_Alpha);
	m_pEft->Texture("uf_tex", 0, m_pTex);


	glEnableVertexAttribArray(0);	glVertexAttribPointer(0, 2, GL_FLOAT, 0, 0, m_VtxP);
	glEnableVertexAttribArray(1);	glVertexAttribPointer(1, 2, GL_FLOAT, 0, 0, m_VtxT);

	m_pTex->BindTexture(0, LC_TRUE);

	glDrawArrays(GL_TRIANGLES, 0, m_VtxC * 6);

	m_pTex->BindTexture(0, LC_FALSE);


	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	m_pEft->End();


	return LC_OK;
}




void CTexString::SetupVertex()
{
	char* s = m_Str;

	// setup char count
	int		n = 0;
	while ( *s != '\0' && *s != '\n' && *s != '\r')
	{
		++n;
		++s;
	}

	// Triangle list
	m_VtxC = n;

	// Fill Vertex and UV
	m_VtxP = new CTexString::TvtxChar[m_VtxC];
	m_VtxT = new CTexString::TvtxChar[m_VtxC];


	s = m_Str;
	for(n = 0; n<m_VtxC; ++n)
	{
		SetupVtxChar(n, *s);
		++s;
	}
}



void CTexString::ClearVertex()
{
	m_VtxC	= 0;

	if(m_VtxP)
	{
		delete [] m_VtxP;
		m_VtxP = NULL;
	}

	if(m_VtxT)
	{
		delete [] m_VtxT;
		m_VtxT = NULL;
	}
}



void CTexString::SetupVtxChar(int n, int c)
{
	c -= 32;

	if(0>c)
		return;


	CTexString::TvtxChar* pVtxS = &CTexString::m_CharL[c];
	CTexString::TvtxChar* pVtxP = &m_VtxP[n];
	CTexString::TvtxChar* pVtxT = &m_VtxT[n];

	memcpy(pVtxT, pVtxS, sizeof(CTexString::TvtxChar));


	float	h = m_Hgt;
	float	w = h * 0.95F;

	pVtxP->v[0].x = (n + 0) * w;	pVtxP->v[0].y = h;
	pVtxP->v[1].x = (n + 1) * w;	pVtxP->v[1].y = h;
	pVtxP->v[2].x = (n + 0) * w;	pVtxP->v[2].y = 0;
	pVtxP->v[3].x = (n + 1) * w;	pVtxP->v[3].y = 0;

	pVtxP->v[4]   = pVtxP->v[2];
	pVtxP->v[5]   = pVtxP->v[1];

	c  =c;
}



void CTexString::InitChar()
{
	float row = 8.0F;
	float col = 16.0F;

	float epX = 1.5F/row;		// Epsilon X
	float epY = 0.F/col;		// Epsilon Y


	for(int i=0;i<128; ++i)
	{
		CTexString::TvtxChar* pChar = &CTexString::m_CharL[i];

		float x = (float)(i % 16);
		float y = col - (float)(i / 16);

		pChar->v[0].x = (x + 0.F + epX)/(col + 0.01f);
		pChar->v[0].y = (y - 1.F - epY)/(row + 0.01f);

		pChar->v[1].x = (x + 1.F - epX)/(col + 0.01f);
		pChar->v[1].y = (y - 1.F - epY)/(row + 0.01f);

		pChar->v[2].x = (x + 0.F + epX)/(col + 0.01f);
		pChar->v[2].y = (y - 0.F + epY)/(row + 0.01f);

		pChar->v[3].x = (x + 1.F - epX)/(col + 0.01f);
		pChar->v[3].y = (y - 0.F + epY)/(row + 0.01f);

		pChar->v[4] = pChar->v[2];
		pChar->v[5] = pChar->v[1];
	}
}


