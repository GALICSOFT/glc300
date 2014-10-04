// Implementation of the LCX Vertex Buffer Object.
//
//
//
////////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER) && _MSC_VER >= 1200
  #pragma warning( disable : 4786)
  #pragma warning( disable : 4996)
#endif


#if defined(_MSC_VER) && _MSC_VER >= 1200
  #include <windows.h>
#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <gles/gl2.h>

#include <LcType.h>
#include <LcBase.h>


#include "LC_vbo.h"


class CLC_VB : public ILC_VB
{
protected:
	PLC_DEVICE		m_pDev;
	UINT			m_nID;

	UINT			m_dFVF;

	void*			m_pOwner;				// Owner

public:
	CLC_VB();
	virtual ~CLC_VB();

	virtual INT		Fill(LC_HANDLE pBuf, INT nBufSize, BOOL bReCreateVB=LC_FALSE);
	virtual INT		Bind(BOOL bBind=LC_FALSE);

	virtual	void	SetOwner(LC_HANDLE p){	m_pOwner = p;	}
	virtual	void*	GetOwner()		{	return m_pOwner;}



public:
	INT		Create(LC_HANDLE =NULL, LC_HANDLE =NULL, LC_HANDLE =NULL, LC_HANDLE =NULL);
	void	Destroy();
};



CLC_VB::CLC_VB()
{
	m_pDev		= NULL;
	m_nID		= 0;
	m_dFVF		= 0;

	m_pOwner	= NULL;
}


CLC_VB::~CLC_VB()
{
	Destroy();
}

void CLC_VB::Destroy()
{
	if(0 == m_nID)
		return;

	glDeleteBuffers(1, &m_nID);
	m_nID = 0;
}


INT CLC_VB::Create(void* p1, void* p2, void* p3, void* p4)
{
	char*	pBuf = NULL;
	INT		nBuf = 0;

	if(NULL ==p1)
		return LC_ECANNOTALLOCATED;


	m_pDev = (PLC_DEVICE)p1;

	pBuf = (char*)p2;

	if(p3)
		nBuf = *(INT*)p3;


	glGenBuffers(1, &m_nID);

	if(0 == m_nID)
		return LC_ECANNOTALLOCATED;


	return Fill(pBuf, nBuf);
}




INT CLC_VB::FillBuffer(void* pBuf, int nBufSize, BOOL bReCreateVB)
{
	UINT	nID = m_nID;

	if(LC_FALSE == bReCreateVB)
	{
		if(0 == nID)
			return LC_ECANNOTALLOCATED;
	}
	else
	{
		glGenBuffers(1, &nID);
	}


	glBindBuffer(GL_ARRAY_BUFFER, nID);								// VBO 연결 시작


	if(pBuf)
	{
		glBufferData(GL_ARRAY_BUFFER, nBufSize, pBuf, GL_STATIC_DRAW);		// 시스템 메모리에 저장된 정점 데이터를 VBO에 연결

	//	int nSize = 0;
	//	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &nSize);

	}


	if(bReCreateVB)
	{
		if(m_nID)
			glDeleteBuffers(1, &m_nID);

		m_nID = nID;
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);								// VBO 연결 해제

	return LC_OK;
}



INT CLC_VB::BindBuffer(BOOL bBind)
{
	if(bBind)
		glBindBuffer(GL_ARRAY_BUFFER, m_nID);
	else
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	return LC_OK;
}




INT LcDev_CreateVB(char* sCmd
			   , PLC_VB* pData
			   , LC_HANDLE p1		// PLC_DEVICE
			   , LC_HANDLE p2		// FVF
			   , LC_HANDLE p3		// Input Buffer
			   , LC_HANDLE p4		// Input Buffer Size(Byte)
				)
{
	INT			hr = 0;
	CLC_VB*	pObj = NULL;

	*pData	= NULL;
	pObj	= new CLC_VB;

	hr = pObj->Create(p1, p2, p3, p4);

	if(LC_FAILED(hr))
	{
		delete pObj;
		return hr;
	}

	*pData = pObj;
	return LC_OK;
}


INT LC_DestroyVB(PLC_VB* pData)
{
	if(NULL == *pData)
		return LC_OK;


	if(NULL != (*pData)->GetOwner())	// 소유주가 활성화 되어 있으면 해제를 못하게 함.
		return LC_EFAIL;

	delete *pData;
	(*pData) = NULL;
	return LC_OK;
}



