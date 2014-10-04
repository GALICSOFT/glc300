// GalicSoft Game Library Collection. Copyright(C) GALICSOFT. All rights reserved.
//
// GLC SDK Auxiliary Program
//
////////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER)
  #pragma once
#endif

#ifndef _LcAxx_H_
#define _LcAxx_H_

#include <algorithm>
#include <functional>

#include <vector>
#include <set>
#include <map>

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
//#include <chrono>
using namespace std;

#include <LcType.h>
#include <LcBase.h>
#include <LcMath.h>
#include <LcEuclid.h>


//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// work sequential

struct TLXX_WRKS
{
	char				cmd[LC_RSC_SID];										// command
	UDINT				grp;													// group
	vector<TLC_ARGS >	svd;													// saved data
	TLC_ARGS			ztc0;													// aux0
	TLC_ARGS			ztc1;													// aux1

	TLXX_WRKS();
	TLXX_WRKS(const char* _cmd, UDINT _grp);
};


//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// simple rect

struct TXSQC_RECT
{
	char        name	[LC_DEFAULT_NAME];										// sequence name
	LCXRECT     rc		;														// dest rect
	LCXRECT     rc_o	;														// original rect
	FLOAT       rot		;														// rotation

	TXSQC_RECT();
	TXSQC_RECT(const TXSQC_RECT&);
	TXSQC_RECT(const char* _name
			, const LCXRECT* _rc_dst = NULL
			, const LCXRECT* _rc_org = NULL
			, const FLOAT _rot = 0.0F);

	TXSQC_RECT& operator=(const TXSQC_RECT&);
};


//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// xml atlas parser

struct TXML_ATLAS
{
	char        name	[LC_DEFAULT_NAME];										// for attribute "n"
	char        file	[LC_DEFAULT_NAME];										// for attribute "file"
	LCXRECT     rc		;														// for attribute "x", "y", "w", "h"
	LCXRECT     rc_o	;														// for attribute "oX", "oY, "oW", "oH"
	FLOAT       rot		;														// for rotation "r" "y" then 1.0F

	TXML_ATLAS();
	TXML_ATLAS(const TXML_ATLAS&);
	TXML_ATLAS(const char* _name
			 , LCXRECT* _rc, LCXRECT* _rc_o = NULL, FLOAT _r=0.0F);

	TXML_ATLAS(const char* _name, const char* _file
			 , LCXRECT* _rc, LCXRECT* _rc_o = NULL, FLOAT _r=0.0F);

	TXML_ATLAS& operator=(const TXML_ATLAS&);
};


//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// extended basic type

typedef vector<INT         >  lsINT     ;   typedef lsINT   ::iterator itINT   ;
typedef vector<FLOAT       >  lsFLOAT   ;   typedef lsFLOAT ::iterator itFLOAT ;
typedef vector<DOUBLE      >  lsDOUBLE  ;   typedef lsDOUBLE::iterator itDOUBLE;
typedef vector<UINT        >  lsUINT    ;   typedef lsUINT  ::iterator itUINT  ;
typedef vector<BYTE        >  lsBYTE    ;   typedef lsBYTE  ::iterator itBYTE  ;
typedef vector<SHORT       >  lsSHORT   ;   typedef lsSHORT ::iterator itSHORT ;
typedef vector<WORD        >  lsWORD    ;   typedef lsWORD  ::iterator itWORD  ;
typedef vector<DWORD       >  lsDWORD   ;   typedef lsDWORD ::iterator itDWORD ;
typedef vector<QWORD       >  lsQWORD   ;   typedef lsQWORD ::iterator itQWORD ;

typedef vector<LC_HANDLE   >  lsHANDLE  ;   typedef lsHANDLE::iterator itHANDLE;
typedef vector<PLC_OBJECT  >  lsOBJECT  ;   typedef lsOBJECT::iterator itOBJECT;
typedef vector<TLC_ARGS    >  lsARGS    ;   typedef lsARGS  ::iterator itARGS  ;


typedef set<INT            >  stINT     ;   typedef stINT   ::iterator tsINT   ;
typedef set<FLOAT          >  stFLOAT   ;   typedef stFLOAT ::iterator tsFLOAT ;
typedef set<DOUBLE         >  stDOUBLE  ;   typedef stDOUBLE::iterator tsDOUBLE;
typedef set<UINT           >  stUINT    ;   typedef stUINT  ::iterator tsUINT  ;
typedef set<BYTE           >  stBYTE    ;   typedef stBYTE  ::iterator tsBYTE  ;
typedef set<SHORT          >  stSHORT   ;   typedef stSHORT ::iterator tsSHORT ;
typedef set<WORD           >  stWORD    ;   typedef stWORD  ::iterator tsWORD  ;
typedef set<DWORD          >  stDWORD   ;   typedef stDWORD ::iterator tsDWORD ;
typedef set<QWORD          >  stQWORD   ;   typedef stQWORD ::iterator tsQWORD ;

typedef set<LC_HANDLE      >  stHANDLE  ;   typedef stHANDLE::iterator tsHANDLE;
typedef set<PLC_OBJECT     >  stOBJECT  ;   typedef stOBJECT::iterator tsOBJECT;
typedef set<TLC_ARGS       >  stARGS    ;   typedef stARGS  ::iterator tsARGS  ;


// extended geometry structure

typedef vector<LCXVECTOR2  >  lsVECTOR2 ;   typedef lsVECTOR2::iterator	itVECTOR2;
typedef vector<LCXVECTOR3  >  lsVECTOR3 ;   typedef lsVECTOR3::iterator	itVECTOR3;
typedef vector<LCXVECTOR4  >  lsVECTOR4 ;   typedef lsVECTOR4::iterator	itVECTOR4;
typedef vector<LCXCOLORB   >  lsCOLORB  ;   typedef lsCOLORB ::iterator	itCOLORB ;
typedef vector<LCXCOLOR    >  lsCOLOR   ;   typedef lsCOLOR  ::iterator	itCOLOR  ;
typedef vector<LCXMATRIX   >  lsMATRIX  ;   typedef lsMATRIX ::iterator	itMATRIX ;

typedef vector<LCX_ABXPCK  >  lsABXPCK  ;   typedef lsABXPCK ::iterator	itABXPCK ;
typedef vector<LCX_PCK     >  lsLXPCK   ;   typedef lsLXPCK  ::iterator	itLXPCK  ;
typedef vector<TLC_IDX_POS >  lsIDXPOS  ;   typedef lsIDXPOS ::iterator	itIDXPOS ;
typedef vector<TLXX_WRKS*  >  lsLXWRKS  ;   typedef lsLXWRKS ::iterator	itLXWRKS ;




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// auxiliary functions for vector container

template <class T>
void lc_shrink_to_fit(vector<T>& v)
{
	vector<T> t(v); v.swap(t);
}

/*
template<class T1, class T2>
INT lc_find_object_index(T1& lst, T2 pObj)
{
	INT i = 0;
	for(T1::iterator it = lst.begin(); it != lst.end(); ++it, ++i)
	{
		if( T2(*it) == pObj)
			return i;
	}
	return LC_EFAIL;
}
*/


template<class T>
int lc_find_object_index(std::vector<T>& lst, T pObj)
{
	int iSize = (int)lst.size();
	for(int i=0; i<iSize; ++i)
	{
		if(lst[i] == pObj)
			return i;
	}

	return LC_EFAIL;
}


template<class T1, class T2>
INT lc_find_object_index(T1 F, T1 L, T2 pObj)
{
	for(INT i = 0; F != L; ++F, ++i)
	{
		if( T2(*F) == pObj)
			return i;
	}
	return LC_EFAIL;
}


template<class T> struct TCMP_LEN_GREATER										// For sort involved dist. descendent Sort
{
	INT operator()(const T& t1,const T& t2) const
	{
		return t1.dist > t2.dist;
	}
};


template<class T> struct TCMP_LEN_LESS											// For sort involved dist. ascendent Sort
{
	INT operator()(const T& t1,const T& t2) const
	{
		return t1.dist < t2.dist;
	}
};


template<class T> struct TCMP_Z_GREATER											// For sort involved z. descendent Sort
{
	INT operator()(const T& t1,const T& t2) const
	{
		return t1.z > t2.z;
	}
};


template<class T> struct TCMP_Z_LESS											// For sort involved z. ascendent Sort
{
	INT operator()(const T& t1,const T& t2) const
	{
		return t1.z < t2.z;
	}
};


template<class T> struct TCMP_DEPTH_GREATER										// For PLCX_MDL sort. descendent Sort
{
	INT operator()(const T& t1,const T& t2) const
	{
		FLOAT	f1 = t1->Zdepth();
		FLOAT	f2 = t2->Zdepth();
		//LOGI("TCMP_DEPTH_GREATER:: %f %f\n", f1, f2);

		return f1 > f2;
	}
};


template<class T> struct TCMP_DEPTH_LESS										// For PLCX_MDL sort... ascendent Sort
{
	INT operator()(const T& t1,const T& t2) const
	{
		FLOAT	f1 = t1->Zdepth();
		FLOAT	f2 = t2->Zdepth();
		//LOGI("TCMP_DEPTH_LESS:: %f %f\n", f1, f2);

		return f1 < f2;
	}
};


template<class T>
void lc_swap(T& a, T& b)
{
	//T t= static_cast<T&&>(a);
	//a  = static_cast<T&&>(b);
	//b  = static_cast<T&&>(t);
	std::swap(a,b);
}

template<class T>
void lc_swap_array(T& a, T& b, INT N)
{
	for(INT i=0;  i<N; ++i)
	{
		::lc_swap(a[i], b[i]);
	}
}

void   LcAxx_Swap          (LC_HANDLE a,   LC_HANDLE b,   INT size);			// swap a and b
INT    LcAxx_Serialize     (LC_HANDLE buf, LC_HANDLE src, INT size);			// same to memcpy
INT    LcAxx_MemCpy        (LC_HANDLE dst, LC_HANDLE src, INT size);			// same to memcpy


#endif

