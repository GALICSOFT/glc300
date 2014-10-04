// Interface for the CGpMain class.
//
////////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER) && _MSC_VER > 1000
	#pragma once
#endif

#ifndef _GpMain_H_
#define _GpMain_H_

#define MAX_NUM 4

class CGpMain : public CGpApp
{
public:
	char			m_sMsg		[512];

	PLCX_ENTITY		m_pGrid		;					// Grid Instance

	PLCX_SHOW		m_avObj		[MAX_NUM]	;



public:
	CGpMain();
	virtual ~CGpMain(){};

	virtual INT		Query(char*, LC_HANDLE);
	virtual INT		SetAttrib(UINT, LC_HANDLE);
	virtual INT		GetAttrib(UINT, LC_HANDLE);

	virtual INT		Init();
	virtual INT		Destroy();
	virtual INT		FrameMove();
	virtual INT		Render();

	virtual INT		Invalid();
	virtual INT		Restore();
};

#endif
