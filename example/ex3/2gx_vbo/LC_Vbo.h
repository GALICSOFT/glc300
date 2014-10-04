// Interface for LCX Vertex Buffer Object.
//
////////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER) && _MSC_VER > 1000
	#pragma once
#endif

#ifndef _ILC_VB_H_
#define	_ILC_VB_H_

#include <LcType.h>


interface ILC_VB
{
	LC_CLASS_DESTROYER(	ILC_VB	);

	virtual INT		Fill(LC_HANDLE pBuf, INT nBufSize, BOOL bReCreateVB=FALSE)=0;	// Fill Buffer
	virtual INT		Bind(BOOL bBind=FALSE)=0;										// Bind Buffer

	virtual	void	SetOwner(LC_HANDLE)=0;	// Setting Owner. if Owner Exist. Texture instance cannot be destroyed.
	virtual	void*	GetOwner()=0;
};


typedef	ILC_VB*	PLC_VB;


// Create Vertex Buffer Instance
INT LC_CreateVB(char* sCmd
				   , PLC_VB* pData
				   , LC_HANDLE p1			// PLC_DEVICE
				   , LC_HANDLE p2			// Input FVF
				   , LC_HANDLE p3 = NULL	// Input Buffer pointer
				   , LC_HANDLE p4 = NULL	// Input Buffer Size(Byte)
					 );

// Destroy VB Instance
INT LC_DestroyVB(PLC_VB* pData);




#endif




