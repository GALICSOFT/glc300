#if defined(_MSC_VER) && _MSC_VER >= 1400
  #pragma warning(disable: 4996)
#endif


#include <vector>
using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <LcType.h>
#include <LcBase.h>
#include <LcMath.h>
#include <LcEuclid.h>
#include <LcCore.h>
#include <LcAux.h>

#define MEDIA_DIR	"../../media/"


extern PLC_DEVICE	m_pDev;
extern PLC_SPRITE	m_pSpt;

PLC_TEXTURE	m_pTexSimple	= NULL;		// Texture List
float		m_rot2	= 0;


void DrawSimple()
{
	static INT n=0;
	++n;

	if(n>5)
	{
		// texture query test
		m_pTexSimple->Query(LC_QUERY_INVALID, NULL);	// release the texture
		m_pTexSimple->Query(LC_QUERY_RESTORE, NULL);	// restore the texture
		n = 0;
	}

	static int c = 0;
	++c;

	INT		zbias = -1000;
	m_pSpt->SetRenderState(LC_RS_ZBIAS, zbias);

	{
		LC_RECTF	rc;
		LCXVECTOR3	s;
		LCXVECTOR3	r;
		LCXVECTOR3	t;
		LCXCOLOR	d;

		float fRadian = LCXToRadian(c * .5);


		rc  = LC_RECTF(50,50, 150, 150);
		s	= LCXVECTOR3(2.f, 2.f, 1.0F);
		r	= LCXVECTOR3(0, 0, 0);
		t	= LCXVECTOR3(100, 25, 0);
		d	= LCXCOLOR(1,1,1,0.4F);

		r  = t + LCXVECTOR3(rc.w/2.F * s.x, rc.h/2.F * s.y, 0.0F);

		m_pSpt->DrawEx(m_pTexSimple, &rc, &t, &s, &r, fRadian, &d);
		//m_pSpt->Draw(m_pTexSimple, NULL, &t, NULL, &d);
	}

	zbias =  1000;
	m_pSpt->SetRenderState(LC_RS_ZBIAS, zbias);
	{
		LCXMATRIX mtScl;
		LCXMATRIX mtRot;
		LCXMATRIX mtW;

		m_rot2 += 0.01f;

		mtScl.Scaling(1.3F, 1.3F, 1.F);
		mtRot.RotationZ(m_rot2);

		mtW = mtScl * mtRot;

		m_pSpt->SetTransform(LC_TM_WORLD, &mtW);

		LCXVECTOR3	t( 150,  150, 0);
		LCXCOLOR	d(1,1, 1, 1.0F);
		LCXRECT		rc(50,50,200,200);
		LCXVECTOR3	s(1.3F,1.3F, 1.0F);

		m_pSpt->DrawEx(m_pTexSimple, &rc, &t, &s, &t, m_rot2, &d);
		//m_pSpt->Draw(m_pTexSimple, NULL, &t, NULL, &d);

		m_pSpt->SetTransform(LC_TM_WORLD, NULL);
	}

	zbias = 0;
	m_pSpt->SetRenderState(LC_RS_ZBIAS, zbias);
}



// Main Program
INT Initsimple()
{
	TLC_ARGS args;

	INT hr = 0;
	INT spt_type = LC_OBJ_MODEL2D;	// sprite for model coordinate
	UINT dClearColor = 0xFF006699;


	char sFile [] = MEDIA_DIR"tex/bg256x256.bmp";
	UINT dColorKey = 0xFFFF0000;
	UINT Use16 = LC_FMT_W4444;

	MAKE_ARG4(args, sFile, Use16, dColorKey, (INT)1);
	if(LC_FAILED(LcDev_CreateTextureFromFile(NULL, &m_pTexSimple, &args)))
	{
		hr = LC_EFAIL;
		goto End;
	}


	hr = LC_OK;

End:
	return hr;
}



void DestroySimple()
{
	SAFE_RELEASE(	m_pTexSimple	);
}

