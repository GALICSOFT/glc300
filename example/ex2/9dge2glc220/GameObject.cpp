// Implementation of the CGpApp class.
//  Written by Heesung Oh
//  Copyright GALIC SOFT Inc. All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER) && _MSC_VER >= 1200
  #pragma warning( disable : 4786)
  #pragma warning( disable : 4996)
#endif


#include <stdio.h>

#include <LcType.h>
#include <LcBase.h>
#include <LcMath.h>
#include <LcEuclid.h>
#include <LcCore.h>
#include <LcAux.h>


#include "GameObject.h"


GameObject::GameObject()
{
	m_nTex		= -1;
	m_pos		= LCXVECTOR3(0,0,0);
	m_vlc		= LCXVECTOR3(0,0,0);
	m_dir		= LCXVECTOR3(0,0,0);
	m_rot		= 0;		// ȸ��
	nAlive		= 0;		// ���� ����
}

// ȭ�� ���
void GameObject::Draw(PLC_SPRITE pSpt, PLC_TEXTURE* pTex)
{
	// ���� ���� Ȯ��
	if(0 >= nAlive)
		return;


	// ����ִ� ���
	PLC_TEXTURE	tex = pTex[m_nTex];
	FLOAT		fRot= FLOAT(m_rot+ LCX_PI);
	INT			ImgW= tex->ImgW();
	INT			ImgH= tex->ImgH();


	LCXVECTOR3		vTrn = m_pos;//(100, 100);// = ;
	LCXVECTOR3		vRot = vTrn + LCXVECTOR3(ImgW * 0.5F, ImgH * 0.5F, 0.0F);

	pSpt->DrawEx(tex, NULL, &vTrn, NULL, &vRot, fRot);
}

