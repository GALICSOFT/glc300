// Particle.cpp: implementation of the CParticle class.
//
//
//
////////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER) && _MSC_VER >= 1200
  #pragma warning( disable : 4786)
  #pragma warning( disable : 4996)
#endif


#if defined(_WIN32)
	#include <Windows.h>
#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <LcType.h>
#include <LcBase.h>
#include <LcMath.h>
#include <LcEuclid.h>
#include <LcCore.h>
#include <LcAux.h>


#include "Particle.h"


#define MEDIA_DIR	"../../media/"


CParticle::CParticle()
{
	m_pDev		= NULL;
	m_pTex		= NULL;

	m_nPrt		= 40;
	m_pPrt		= NULL;
}

CParticle::~CParticle()
{
	Destroy();
}

void CParticle::Destroy()
{
	SAFE_DELETE_ARRAY(	m_pPrt	);

	m_pTex->Release();
}

INT CParticle::Create()
{
	TLC_ARGS	args;
	INT hr;

	m_pDev	= (PLC_DEVICE)LcVar_ReadP(LC_VAR_GLDEV);

	MAKE_ARG4(args, (char*)MEDIA_DIR"tex/star128.tga", (UINT)0, (UINT)0, (INT)1);
	hr = LcDev_CreateTextureFromFile(NULL, &m_pTex, &args);
	if(LC_FAILED(hr))
		return LC_EFAIL;



	// Create The Particle
	m_pPrt = new TPart[m_nPrt];

	for(int i=0; i<m_nPrt; ++i)
		PartSetup(i);

	return LC_OK;
}


INT CParticle::FrameMove()
{
	INT i=0;

	for(i=0; i<m_nPrt; ++i)
	{
		m_pPrt[i].a += .8F;
		m_pPrt[i].r -= 0.06f;

		if(m_pPrt[i].r<0.0f)
			PartReset(i);
	}


	return LC_OK;
}


void CParticle::Render()
{
	int i;
	VtxUV1	pVtx[4];
	LCXMATRIX	mtW;
	LCXMATRIX	mtT;
	LCXMATRIX	mtS;

	LCXMATRIX	mtV;
	LCXMATRIX	mtB;
	LCXMATRIX	mtR;

	LCXVECTOR3	vcRot;


	m_pDev->GetTransform(LC_TM_VIEW, &mtV);

	// ������� ����Ŀ� _41, _42, _43 ������ �ϸ� ������ ����� �ȴ�.
	mtB.Inverse(NULL, &mtV, LC_FALSE);
	mtB._41 = 0;
	mtB._42 = 0;
	mtB._43 = 0;

	// ȸ���� �� ��� OpenGL�� y���� �ϴ��� �ٶ󺸰� �ְ� (-z)���� ���� �����̹Ƿ�
	// �� ����� _13, _23, _33�� �̿��Ѵ�
	vcRot = -LCXVECTOR3(mtV._13, mtV._23, mtV._33);


	m_pDev->SetRenderState(LC_RS_CULL_FACE, LC_ST_DISABLE);
	m_pDev->SetRenderState(LC_RS_DEPTH_TEST, LC_ST_DISABLE);

	m_pDev->SetRenderState(LC_RS_BLEND, LC_ST_ENABLE, LC_ST_SRC_ALPHA, LC_ST_ONE);


// ������ ����� ������� ������ x, z ��鿡 ��ƼŬ�� ���� ��ġ�� �����.
//	pVtx[0] = VtxUV1(-1.0f, 0.0f, -1.0f,  0.0f,  0.0f);
//	pVtx[1] = VtxUV1( 1.0f, 0.0f, -1.0f,  1.0f,  0.0f);
//	pVtx[2] = VtxUV1( 1.0f, 0.0f,  1.0f,  1.0f,  1.0f);
//	pVtx[3] = VtxUV1(-1.0f, 0.0f,  1.0f,  0.0f,  1.0f);

	// OpenGL�� y���� �ϴ��� �ٶ󺸰� �����Ƿ� �����尡 ����Ƿ���
	// x, y ������� ��ƼŬ�� ���� ��ġ�� ������ �Ѵ�.
	pVtx[0] = VtxUV1(-1.0f, -1.0f, 0.0f,  0.0f,  0.0f);
	pVtx[1] = VtxUV1( 1.0f, -1.0f, 0.0f,  1.0f,  0.0f);
	pVtx[2] = VtxUV1( 1.0f,  1.0f, 0.0f,  1.0f,  1.0f);
	pVtx[3] = VtxUV1(-1.0f,  1.0f, 0.0f,  0.0f,  1.0f);


	m_pDev->SetTexture(0, m_pTex);
	m_pDev->SetTextureAddressS(0, LC_TS_REPEAT);
	m_pDev->SetTextureAddressT(0, LC_TS_REPEAT);
	m_pDev->SetTextureFilterMin(0, LC_TS_LINEAR);
	m_pDev->SetTextureFilterMag(0, LC_TS_LINEAR);

	m_pDev->SetFVF(VtxUV1::FVF);
	m_pDev->SetTexture(0, m_pTex);


	mtS.Scaling(13, 13, 13);


	for(i=0; i<m_nPrt; ++i)
	{
		FLOAT	fRadius = m_pPrt[i].r;
		FLOAT	fTheta = LCXToRadian(m_pPrt[i].a);
		FLOAT	fCos = (FLOAT)cos(fTheta);
		FLOAT	fSin = (FLOAT)sin(fTheta);

		LCXVECTOR3	pos(fRadius * fCos, -10 + (-2)*fRadius, fRadius * fSin);


		mtT.Translation( &pos);
		mtR.RotationAxis(&vcRot, fTheta*2);

		mtW = mtB * mtS * mtR * mtT;

		m_pDev->SetTcolor(&m_pPrt[i].d);
		m_pDev->SetTransform(LC_TM_WORLD, &mtW);
		m_pDev->DrawPrimitiveUP(LC_PT_TRIANGLE_FAN, 0, 4, pVtx, sizeof(VtxUV1) );

	}


	m_pDev->SetTcolor(NULL);
	m_pDev->SetTexture(0, NULL);

	m_pDev->SetTransform(LC_TM_WORLD_IDENTITY, NULL);

	m_pDev->SetRenderState(LC_RS_BLEND, LC_ST_DISABLE);
	m_pDev->SetRenderState(LC_RS_CULL_FACE, LC_ST_ENABLE);
	m_pDev->SetRenderState(LC_RS_DEPTH_TEST, LC_ST_ENABLE);
}


void CParticle::PartSetup(INT nIdx)
{
	LCXCOLOR d( FLOAT(rand()%256), FLOAT(rand()%256), FLOAT(rand()%256), 255);
	d *= (1.F/255.F);

	m_pPrt[nIdx].a = 4 * 360 * nIdx/FLOAT(m_nPrt);

	m_pPrt[nIdx].r = 30 * nIdx/FLOAT(m_nPrt);
	m_pPrt[nIdx].d = d;
}

void CParticle::PartReset(INT nIdx)
{
	LCXCOLOR d( FLOAT(rand()%256), FLOAT(rand()%256), FLOAT(rand()%256), 255);
	d *= (1.F/255.F);

	m_pPrt[nIdx].a = 4 * 360 * nIdx/FLOAT(m_nPrt);
	m_pPrt[nIdx].r = 30;
	m_pPrt[nIdx].d = d;
}



