// RndObj.cpp: implementation of the CRndObj class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


CRndObj::CRndObj()
{
	m_pDev	= NULL;
	m_pTex	= NULL;

	m_nFce	= 0;
	m_pIdx	= NULL;
	m_pVtx	= NULL;
}

CRndObj::~CRndObj()
{
	Destroy();
}

void CRndObj::Destroy()
{
	SAFE_RELEASE(	m_pTex	);
}


INT CRndObj::Create(PLC_ARGS pArg)
{
	TLC_ARGS	args;
	INT		hr = 0;
	char*	sFile= pArg->_0;

	if(NULL == sFile)
		return LC_EFAIL;

	MAKE_ARG4(args, sFile, (UINT)LC_FMT_W565, (UINT)0, (INT)0);
	hr = LcDev_CreateTextureFromFile(NULL, &m_pTex, &args);

	if(LC_FAILED(hr))
		return LC_EFAIL;


	m_pDev	= (PLC_DEVICE)LcVar_ReadP(LC_VAR_GLDEV);
	return LC_OK;
}

INT CRndObj::FrameMove()
{
	return LC_OK;
}

void CRndObj::Render()
{
	m_pDev->SetTextureAddressS (0, LC_TS_REPEAT);
	m_pDev->SetTextureAddressT (0, LC_TS_REPEAT);
	m_pDev->SetTextureFilterMin(0, LC_TS_NEAREST_MIPMAP_LINEAR);
	m_pDev->SetTextureFilterMag(0, LC_TS_LINEAR_MIPMAP_LINEAR);
	m_pDev->SetTextureStageOp  (0, LC_TS_MODULATE);

	m_pDev->SetTexture(0, m_pTex);
	m_pDev->SetTransform(LC_TM_WORLD, &m_mtWld);
	m_pDev->SetFVF(LC3D::VtxUV1::FVF);
	m_pDev->DrawIndexedPrimitiveUP(LC_PT_TRIANGLE_LIST
						, m_nFce* 3
						, m_pIdx
						, LC_FMT_WORD
						, m_pVtx
						, sizeof(LC3D::VtxUV1));

	m_pDev->SetTransform(LC_TM_WORLD_IDENTITY, NULL);
	m_pDev->SetTexture(0, 0);
}


void CRndObj::SetMatrix(const LCXMATRIX* v)
{
	m_mtWld = *v;
}


void CRndObj::SetIdx(const void* v, INT nFace)
{
	m_nFce = nFace;
	m_pIdx = (LC3D::VtxFce16*)v;
}

void CRndObj::SetVtx(const void* v)
{
	m_pVtx = (LC3D::VtxUV1*)v;
}



