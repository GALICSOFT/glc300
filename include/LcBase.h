// GalicSoft Game Library Collection. Copyright(C) GALICSOFT. All rights reserved.
//
// base types, values and architectures
//
////////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER)
  #pragma once
#endif

#ifndef _LcBase_H_
#define _LcBase_H_


struct TLC_ARGS;

#if defined(_MSC_VER)
  #pragma pack(push, 1)
#endif

struct QINT																		// for object id(128bit)::little endian
{
	union
	{
		struct{ INT  a, b, c, d;};
		struct{ INT _0,_1,_2,_3;};
		struct{ DINT p,q;       };
		INT i[4]; SHORT s[8]; char t[16];										// 32, 64, 16 bit id
	};

	QINT();
	QINT(const QINT&);
	QINT(const QINT*);
	QINT(INT  _a, INT  _b=0,INT _c=0,INT _d=0);
	QINT(DINT _p, DINT _q=0);
	QINT(TLC_ARGS&);

	// casting
	operator INT();																// return a
	operator const INT() const;

	operator DINT();															// return n[0]
	operator const DINT() const;

	// assignment
	QINT& operator=(const QINT& r);
	QINT& operator=(const INT r);

	// arithmetic
	//unary operators
	QINT operator +() const;
	QINT operator -() const;

	QINT operator ++(   );
	QINT operator ++(int);
	QINT operator --(   );
	QINT operator --(int);

	// binary operators
	QINT operator +(const QINT&) const;

	// compare
	INT  operator == (const QINT&) const;
	INT  operator != (const QINT&) const;
}
#if defined(_MSC_VER)
  #pragma pack(pop)
#else
  __attribute__((packed))
#endif
;


struct LC_QID : public QINT
{
	INT				Id(INT n=0);												// return the id
	CONF(INT*)		Ids() const;												// return the ids
	void			Ids(INT*, INT*, INT* =0, INT* =0);							// get the id

	void			Id(INT n, INT v);											// set the id
	void			Ids(const INT*);											// set the id int *4 array
	void			Ids(INT, INT =0, INT =0, INT =0);							// set the id

	SHORT			Wid(INT n=0);												// return the id
	CONF(SHORT*)	Wids() const;												// return the ids
	void			Wids(SHORT*   , SHORT*   , SHORT* =0, SHORT* =0
						,SHORT* =0, SHORT* =0, SHORT* =0, SHORT* =0);			// get the id

	void			Wid(INT n, SHORT v);										// set the id
	void			Wids(const SHORT*);											// set the id int *4 array
	void			Wids(SHORT   , SHORT =0, SHORT =0, SHORT =0
						,SHORT =0, SHORT =0, SHORT =0, SHORT =0);				// set the id
};



  
//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Hierarchy

// ILC_Base::Query command
//   set/get owner : simple pointer owner. if the object has owner, it' cannot be released.
//   set/get parent : for world transform or node linking
//   set/get sqc parent : timeline sequence parent for animation.
//     if the model has the timeline sequence parent, it will be skipped on update or frame move and it use the parent animation information in rendering.

#define LC_QUERY_SET_TS_PARENT	(char*)"Set TS Parent"
#define LC_QUERY_GET_PARENT		(char*)"Get Parent"
#define LC_QUERY_GET_TS_PARENT	(char*)"Get TS Parent"


// The GLC base objects
DCL_INTERFACE ILC_Base;
typedef       ILC_Base*		PLC_BASE;

DCL_INTERFACE ILC_Object;
typedef       ILC_Object*	PLC_OBJECT;


// Declaration the GLC base object which is the base of all instance.

DCL_INTERFACE ILC_Base
{
	// Release Object. It returns remained Reference Count.
	// If all objects are released perfectly, then the Release function returns zero. Failed <0
	// The Release function is same to call LcVar_DestroyObject() definded in LC_Base.h
	// the instance created without using LcVar_IncRefCountObject(), then bDecreaseRefCount mustbe false.
	virtual INT	Release(INT bDecreaseRefCount=LC_TRUE);

	// Read / Write the attribute, or execution of Object: success: >=0 failed: <0
	virtual INT Query(char* sCmd, LC_HANDLE pData) { return LC_EFAIL;  }

	// destroyer
	DCL_CLASS_DESTROYER( ILC_Base );
};




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Declaration the GLC game object which is the scene graph of all objects

DCL_INTERFACE ILC_Object : public ILC_Base
{
public:
	LC_QID				m_qid	;												// id

protected:
	LC_HANDLE			m_own	;												// Instance Onwer: if there the owner exist, this instance cannot be released.
	LC_HANDLE			m_usr	[4];											// extra instance created by user.

	// basic node																// all node related world transform.
	PLC_OBJECT			m_prn	;												// parent node.
	PLC_OBJECT			m_chd	;												// child node
	PLC_OBJECT			m_bfr	;												// previous node
	PLC_OBJECT			m_nxt	;												// next node

public:
	ILC_Object();
	virtual ~ILC_Object();

	// data format
	virtual UINT		StorageType  () ;										// source storage type: LC_SRC_T_{FILE | MEM | BUF, RSC}. default: return LC_SRC_T_NONE.
	virtual UINT		ObjType      () ;										// get the Object type: LC_OBJ_... default: return LC_OBJ_UNKNOWN.
	virtual UINT		RscType      () ;										// object source kind: image, texture->ELC_IMAGE: IMAGE TYPE, sound->LC_OBJ_{WAV|OGG}... default: return LC_OBJ_UNKNOWN.
	virtual UINT		Type         () ;										// more detailed type. defined each class for object. default: return LC_OBJ_UNKNOWN.
	virtual	INT			Desc         (LC_HANDLE) ;								// get the Object information. It needs pointer address. default usage: Tinf_pf* pDsc; instance->GetDesc(&pDsc); default: return LC_EFAIL.
	virtual	CONC		Name         () ;										// get the Object name from information. default: return NULL.

	// attribute, id, extera data
	virtual INT  		SetAttrib    (UINT dCmd, LC_HANDLE pData);				// Extended the Query. set the attribute value. default: return LC_EFAIL.
	virtual INT		 	GetAttrib    (UINT dCmd, LC_HANDLE pData);				// Extended the Query. get the attribute value. default: return LC_EFAIL.

	virtual LC_HANDLE	Owner        ()                  ;						// retrieve the owner
	virtual void		Owner        (LC_HANDLE v)       ;						// Setting Owner. if Owner Exist. belonged instance to owner cannot be destroyed.
	virtual LC_HANDLE	UsrData      (INT n)             ;						// sequence parent(Tsq)
	virtual void		UsrData      (INT n, LC_HANDLE v);						// setup the user data

	// Node Iteration
	virtual INT			HasParent    ()	;										// Has parent?
	virtual INT			HasNotParent ()	;										// Has no parent?
	virtual INT			HasChild     ()	;										// Has child?
	virtual INT			HasNotChild  ()	;										// Has no child?
	virtual INT			IsSiblingF   ()	;										// Am I first child?

	virtual INT			IsSiblingL   ()	;										// Am I last child?
	virtual INT			IsRoot       ()	;										// Am I root?
	virtual INT			IsChild      ()	;										// Am I Child?

	virtual PLC_OBJECT	Parent       ()	;										// parent
	virtual PLC_OBJECT	Child        ()	;										// child
	virtual PLC_OBJECT	Before       ()	;										// previous
	virtual PLC_OBJECT	Next         ()	;										// next

	virtual PLC_OBJECT	SiblingF     ()	;										// find first node from sibling list
	virtual PLC_OBJECT	SiblingL     ()	;										// find last node from sibling list
	virtual PLC_OBJECT	FindRoot     ()	;										// find root node

	virtual void		AttachTo     (PLC_OBJECT _parent);						// set the parent node. (I'm a child node)
	virtual void		Attach       (PLC_OBJECT _child );						// attach the child node. (I'm parent node)
	virtual void		Detach       ()                  ;						// detach
	virtual INT			CountNodes   ()                  ;						// count node
};




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// for event and message listener

DCL_INTERFACE ILC_MsgPrc : public ILC_Base
{
	virtual INT	Release(INT bDecreaseRefCount=LC_TRUE){ return LC_EFAIL; }
	virtual INT Query(char*, LC_HANDLE)               { return LC_EFAIL; }

	virtual INT	MsgPrc(LC_HANDLE =0,LC_HANDLE =0,LC_HANDLE =0,LC_HANDLE =0) =0;	// for event or mesage procedure function
};
typedef ILC_MsgPrc*	PLC_MSGPRC;




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// 2D, 3D basic structure

struct LC_INT2_  { union{ struct{ INT x, y;             }; INT m[2]; }; };
struct LC_INT3_  { union{ struct{ INT x, y, z;          }; INT m[3]; }; };
struct LC_INT4_  { union{ struct{ INT x, y, z, w;       }; INT m[4]; }; };
struct LC_INT6_  { union{ struct{ INT x, y, z, w, p, q; }; INT m[6]; }; };
struct LC_INT8_  { union{ struct{ INT _0,_1,_2,_3,_4,_5,_6,_7; }; INT m[8]; }; };

struct LC_FLOAT2_{ union{ struct{ FLOAT x, y;     }; INT m[2]; }; };
struct LC_FLOAT3_{ union{ struct{ FLOAT x, y, z;  }; INT m[3]; }; };
struct LC_FLOAT4_{ union{
		struct	{ FLOAT x, y, z, w; };
		struct	{ FLOAT a, b, c, d; };
		FLOAT m[4];
	};
};

struct LC_FLOAT6_ { union{ struct{ FLOAT x, y, z, w, p, q; }; FLOAT m[6]; }; };
struct LC_FLOAT8_ { union{ struct{ FLOAT _0,_1,_2,_3,_4,_5,_6,_7; }; FLOAT m[8]; }; };


struct LC_POINT2
{
	INT x, y;

	LC_POINT2()										;
	LC_POINT2(INT X, INT Y)							;

	operator INT*()									;
	operator const INT*() const						;
	LC_POINT2& operator+=(const LC_POINT2&)			;
	LC_POINT2& operator-=(const LC_POINT2&)			;
	INT operator == (const LC_POINT2&) const		;
	INT operator != (const LC_POINT2&) const		;
};


struct LC_POINT3
{
	INT x, y, z;

	LC_POINT3()										;
	LC_POINT3(INT X, INT Y, INT Z)					;

	operator INT*()									;
	operator const INT*() const						;
	LC_POINT3& operator+=(const LC_POINT3&)			;
	LC_POINT3& operator-=(const LC_POINT3&)			;
	INT operator == (const LC_POINT3&) const		;
	INT operator != (const LC_POINT3&) const		;
};


struct LC_POINT4
{
	INT x, y, z, w;

	LC_POINT4()										;
	LC_POINT4(INT X, INT Y, INT Z, INT W)			;

	operator INT*()									;
	operator const INT*() const						;
	LC_POINT4& operator+=(const LC_POINT4&)			;
	LC_POINT4& operator-=(const LC_POINT4&)			;
	INT operator == (const LC_POINT4&) const		;
	INT operator != (const LC_POINT4&) const		;
};


struct LC_RECT
{
	union
	{
		struct{  INT x,   y,  w,    h;     }		;	// w ==> width, h==>height
		struct{  INT l,   t,  r,    b;     }		;
		struct{  INT x0,  y0, x1,   y1;    }		;
		struct{  INT left,top,right,bottom;}		;
		FLOAT m[4];
	};

	LC_RECT()										;
	LC_RECT(INT X, INT Y, INT W, INT H)				;

	operator INT*()									;
	operator const INT*() const						;
	INT operator == (const LC_RECT&) const			;
	INT operator != (const LC_RECT&) const			;
};


#if defined(_MSC_VER)
  #pragma pack(push, 1)
#endif
struct LC_SHORT2
{
	union{ struct{ SHORT x, y; }; SHORT m[2]; }		;

	LC_SHORT2()										;
	LC_SHORT2(SHORT X, SHORT Y)						;

	operator SHORT*()								;
	operator const SHORT*() const					;
	INT operator == (const LC_SHORT2&) const		;
	INT operator != (const LC_SHORT2&) const		;
}
#if defined(_MSC_VER)
  #pragma pack(pop)
#else
  __attribute__((packed))
#endif
;


#if defined(_MSC_VER)
  #pragma pack(push, 1)
#endif
struct LC_WORD2
{
	union{ struct{ WORD x,y;}; WORD m[2];}			;

	LC_WORD2()										;
	LC_WORD2(WORD X, WORD Y)						;

	operator WORD*()								;
	operator const WORD*() const					;
	INT operator == (const LC_WORD2&) const			;
	INT operator != (const LC_WORD2&) const			;
}
#if defined(_MSC_VER)
  #pragma pack(pop)
#else
  __attribute__((packed))
#endif
;


#if defined(_MSC_VER)
  #pragma pack(push, 1)
#endif
struct LC_SHORT3
{
	union{ struct{ SHORT x,y,z;}; SHORT m[3];}		;

	LC_SHORT3()										;
	LC_SHORT3(SHORT X, SHORT Y, SHORT Z)			;

	operator SHORT*()								;
	operator const SHORT*() const					;
	INT operator == (const LC_SHORT3&) const		;
	INT operator != (const LC_SHORT3&) const		;
}
#if defined(_MSC_VER)
  #pragma pack(pop)
#else
  __attribute__((packed))
#endif
;


#if defined(_MSC_VER)
  #pragma pack(push, 1)
#endif
struct LC_WORD3
{
	union{ struct{ WORD x, y, z;}; WORD m[3]; }		;

	LC_WORD3()										;
	LC_WORD3(WORD X, WORD Y, WORD Z)				;

	operator WORD*()								;
	operator const WORD*() const					;
	INT operator == (const LC_WORD3&) const			;
	INT operator != (const LC_WORD3&) const			;
}
#if defined(_MSC_VER)
  #pragma pack(pop)
#else
  __attribute__((packed))
#endif
;


struct LC_INT2
{
	union
	{
		struct { INT  a, b;};
		struct { INT  x, y;};
		struct { INT _0,_1;};
		INT m[2];
	};

	LC_INT2()										;
	LC_INT2(INT X, INT Y)							;

	operator INT*()									;
	operator const INT*() const						;
	LC_INT2& operator+=(const LC_INT2&)				;
	LC_INT2& operator-=(const LC_INT2&)				;
	INT operator == (const LC_INT2&) const			;
	INT operator != (const LC_INT2&) const			;
};


struct LC_INT3
{
	union
	{
		struct { INT  a, b, c;};
		struct { INT  x, y, z;};
		struct { INT _0,_1,_2;};
		INT m[3];
	};

	LC_INT3()										;
	LC_INT3(INT X, INT Y, INT Z)					;

	operator INT*()									;
	operator const INT*() const						;
	LC_INT3& operator+=(const LC_INT3&)				;
	LC_INT3& operator-=(const LC_INT3&)				;
	INT operator == (const LC_INT3&) const			;
	INT operator != (const LC_INT3&) const			;
};


struct LC_INT4
{
	union
	{
		struct { INT  a, b, c, d;};
		struct { INT  x, y, z, w;};
		struct { INT _0,_1,_2,_3;};
		INT m[4];
	};

	LC_INT4()										;
	LC_INT4(INT X, INT Y, INT Z, INT W)				;

	operator INT*()									;
	operator const INT*() const						;
	LC_INT4& operator+=(const LC_INT4&)				;
	LC_INT4& operator-=(const LC_INT4&)				;
	INT operator == (const LC_INT4&) const			;
	INT operator != (const LC_INT4&) const			;
};


struct LC_INT6
{
	union
	{
		struct { INT  a, b, c, d, e, f;};
		struct { INT  x, y, z, w, p, q;};
		struct { INT _0,_1,_2,_3,_4,_5;};
		INT m[6];
	};

	LC_INT6()										;
	LC_INT6(INT __0,INT __1,INT __2,
			INT __3,INT __4,INT __5)				;

	operator INT*()									;
	operator const INT*() const						;
	LC_INT6& operator+=(const LC_INT6&)				;
	LC_INT6& operator-=(const LC_INT6&)				;
	INT operator == (const LC_INT6&) const			;
	INT operator != (const LC_INT6&) const			;
};


struct LC_INT8
{
	union
	{
		struct { INT  a, b, c, d, e, f, g, h;};
		struct { INT  x, y, z, w, p, q, r, s;};
		struct { INT _0,_1,_2,_3,_4,_5,_6,_7;};
		INT m[8];
	};

	LC_INT8()										;
	LC_INT8(INT __0,INT __1,INT __2,INT __3,
			INT __4,INT __5,INT __6,INT __7)		;

	operator INT*()									;
	operator const INT*() const						;
	LC_INT8& operator+=(const LC_INT8&)				;
	LC_INT8& operator-=(const LC_INT8&)				;
	INT operator == (const LC_INT8&) const			;
	INT operator != (const LC_INT8&) const			;
};


struct LC_FLOAT2
{
	union
	{
		struct { FLOAT  x,  y; };
		struct { FLOAT  a,  b; };
		struct { FLOAT _0, _1; };
		FLOAT m[2];
	};

	LC_FLOAT2()										;
	LC_FLOAT2(FLOAT X, FLOAT Y)						;
	LC_FLOAT2(const FLOAT* v)						;

	operator FLOAT*()								;
	operator const FLOAT*() const					;
	FLOAT& operator[](int)							;
	LC_FLOAT2& operator +=(const LC_FLOAT2&)		;
	LC_FLOAT2& operator -=(const LC_FLOAT2&)		;
	LC_FLOAT2& operator *=(FLOAT)					;
	LC_FLOAT2& operator /=(FLOAT)					;
	LC_FLOAT2 operator +() const					;
	LC_FLOAT2 operator -() const					;
	LC_FLOAT2 operator+(const LC_FLOAT2&) const		;
	LC_FLOAT2 operator-(const LC_FLOAT2&) const		;
	LC_FLOAT2 operator*(FLOAT) const				;
	LC_FLOAT2 operator/(FLOAT) const				;
	INT operator == (const LC_FLOAT2&) const		;
	INT operator != (const LC_FLOAT2&) const		;
};


struct LC_FLOAT3
{
	union
	{
		struct { FLOAT  x,  y,  z; };
		struct { FLOAT  a,  b,  c; };
		struct { FLOAT _0, _1, _2; };
		FLOAT m[3];
	};

	LC_FLOAT3()										;
	LC_FLOAT3(FLOAT X,FLOAT Y,FLOAT Z)				;
	LC_FLOAT3(const FLOAT* v)						;

	// casting
	operator FLOAT*()								;
	operator const FLOAT*() const					;
	FLOAT& operator[](int)							;

	// assignment operators
	LC_FLOAT3& operator +=(const LC_FLOAT3&)		;
	LC_FLOAT3& operator -=(const LC_FLOAT3&)		;
	LC_FLOAT3& operator *=(FLOAT)					;
	LC_FLOAT3& operator /=(FLOAT)					;

	// unary operators
	LC_FLOAT3 operator +() const					;
	LC_FLOAT3 operator -() const					;

	// binary operators
	LC_FLOAT3 operator +(const LC_FLOAT3&) const	;
	LC_FLOAT3 operator -(const LC_FLOAT3&) const	;
	LC_FLOAT3 operator *(FLOAT) const				;
	LC_FLOAT3 operator /(FLOAT) const				;
	INT operator == (const LC_FLOAT3&) const		;
	INT operator != (const LC_FLOAT3&) const		;
};


struct LC_FLOAT4
{
	union
	{
		struct { FLOAT  x,  y,  z,  w; };
		struct { FLOAT  a,  b,  c,  d; };
		struct { FLOAT _0, _1, _2, _3; };
		FLOAT m[4];
	};

	LC_FLOAT4()										;
	LC_FLOAT4(FLOAT X,FLOAT Y,FLOAT Z, FLOAT W)		;
	LC_FLOAT4(const FLOAT* v)						;

	operator FLOAT*()								;
	operator const FLOAT*() const					;
	FLOAT& operator[](int)							;

	LC_FLOAT4& operator +=(const LC_FLOAT4&)		;
	LC_FLOAT4& operator -=(const LC_FLOAT4&)		;
	LC_FLOAT4& operator *=(FLOAT)					;
	LC_FLOAT4& operator /=(FLOAT)					;
	LC_FLOAT4 operator +() const					;
	LC_FLOAT4 operator -() const					;
	LC_FLOAT4 operator +(const LC_FLOAT4&) const	;
	LC_FLOAT4 operator -(const LC_FLOAT4&) const	;
	LC_FLOAT4 operator *(FLOAT) const				;
	LC_FLOAT4 operator /(FLOAT) const				;
	INT operator == (const LC_FLOAT4&) const		;
	INT operator != (const LC_FLOAT4&) const		;
};


struct LC_FLOAT6
{
	union
	{
		struct { FLOAT  a, b, c, d, e, f;};
		struct { FLOAT  x, y, z, w, p, q;};
		struct { FLOAT _0,_1,_2,_3,_4,_5;};
		FLOAT m[6];
	};

	LC_FLOAT6()										;
	LC_FLOAT6(FLOAT __0,FLOAT __1,FLOAT __2,
			  FLOAT __3,FLOAT __4,FLOAT __5)		;
	LC_FLOAT6(const FLOAT* v)						;

	operator FLOAT*()								;
	operator const FLOAT*() const					;
	FLOAT& operator[](int)							;

	LC_FLOAT6& operator +=(const LC_FLOAT6&)		;
	LC_FLOAT6& operator -=(const LC_FLOAT6&)		;
	LC_FLOAT6& operator *=(FLOAT)					;
	LC_FLOAT6& operator /=(FLOAT)					;
	LC_FLOAT6 operator +() const					;
	LC_FLOAT6 operator -() const					;
	LC_FLOAT6 operator +(const LC_FLOAT6&) const	;
	LC_FLOAT6 operator -(const LC_FLOAT6&) const	;
	LC_FLOAT6 operator *(FLOAT) const				;
	LC_FLOAT6 operator /(FLOAT) const				;
	INT operator == (const LC_FLOAT6&) const		;
	INT operator != (const LC_FLOAT6&) const		;
};


struct LC_FLOAT8
{
	union
	{
		struct { FLOAT  a, b, c, d, e, f, g, h;};
		struct { FLOAT  x, y, z, w, p, q, r, s;};
		struct { FLOAT _0,_1,_2,_3,_4,_5,_6,_7;};
		FLOAT m[8];
	};

	LC_FLOAT8()										;
	LC_FLOAT8(FLOAT __0     , FLOAT __1=0.0F, FLOAT __2=0.0F, FLOAT __3=0.0F,
			  FLOAT __4=0.0F, FLOAT __5=0.0F, FLOAT __6=0.0F, FLOAT __7=0.0F);
	LC_FLOAT8(const FLOAT* v)						;

	operator FLOAT*()								;
	operator const FLOAT*() const					;
	FLOAT& operator[](int)							;

	LC_FLOAT8& operator +=(const LC_FLOAT8&)		;
	LC_FLOAT8& operator -=(const LC_FLOAT8&)		;
	LC_FLOAT8& operator *=(FLOAT)					;
	LC_FLOAT8& operator /=(FLOAT)					;
	LC_FLOAT8 operator +() const					;
	LC_FLOAT8 operator -() const					;
	LC_FLOAT8 operator +(const LC_FLOAT8&) const	;
	LC_FLOAT8 operator -(const LC_FLOAT8&) const	;
	LC_FLOAT8 operator *(FLOAT) const				;
	LC_FLOAT8 operator /(FLOAT) const				;
	INT operator == (const LC_FLOAT8&) const		;
	INT operator != (const LC_FLOAT8&) const		;
};



struct LC_COLORF
{
	union{ struct{ FLOAT r,g,b,a; }; FLOAT m[4]; }	;

	LC_COLORF()										;
	LC_COLORF(FLOAT R,FLOAT G,FLOAT B,FLOAT A)		;
	LC_COLORF(COLOR32 D)							;

	operator COLOR32 () const						;
	operator FLOAT *()								;
	operator const FLOAT *() const					;
	FLOAT& operator[](int)							;

	LC_COLORF& operator +=(const LC_COLORF&)		;
	LC_COLORF& operator -=(const LC_COLORF&)		;
	LC_COLORF& operator *=(FLOAT)					;
	LC_COLORF& operator /=(FLOAT)					;
	LC_COLORF operator +() const					;
	LC_COLORF operator -() const					;	// Negative
	LC_COLORF operator +(const LC_COLORF& v) const	;
	LC_COLORF operator -(const LC_COLORF& v) const	;
	LC_COLORF operator *(FLOAT) const				;
	LC_COLORF operator /(FLOAT) const				;
	INT operator == (const LC_COLORF&) const		;
	INT operator != (const LC_COLORF&) const		;
};


struct LC_COLORB
{
	union{ struct{ BYTE r,g,b,a;}; BYTE m[4]; }		;	// Notice!! the byte order

	LC_COLORB()										;
	LC_COLORB(BYTE R, BYTE G, BYTE B, BYTE A)		;
	LC_COLORB(const LC_COLORF& v)					;
	LC_COLORB(COLOR32 v)							;	// argument must be a argb(0xAARRGGBB)
	LC_COLORB(const LC_COLORB& v)					;

	operator COLOR32 () const						;
	operator BYTE* ()								;
	operator const BYTE* () const					;
	INT operator == (const LC_COLORB&) const		;
	INT operator != (const LC_COLORB&) const		;
};


struct LC_RECTF
{
	union
	{
		struct{  FLOAT x,   y,  w,    h;    }		;
		struct{  FLOAT l,   t,  r,    b;    }		;
		struct{  FLOAT left,top,right,bottom;}		;
		FLOAT	m[4];
	};

	LC_RECTF()										;
	LC_RECTF(FLOAT X, FLOAT Y, FLOAT W,FLOAT H)		;

	operator FLOAT*()								;
	operator const FLOAT*() const					;
	INT operator == (const LC_RECTF&) const			;
	INT operator != (const LC_RECTF&) const			;
};


struct LC_MATRIX3X2
{
	union { struct {
			FLOAT _11, _12;
			FLOAT _21, _22;
			FLOAT _31, _32; };
            FLOAT m[3][2]; };

	LC_MATRIX3X2()									;
	LC_MATRIX3X2( FLOAT t11, FLOAT t12
				, FLOAT t21, FLOAT t22
				, FLOAT t31, FLOAT t32)				;

	operator FLOAT*()								;
	operator const FLOAT*() const					;
	INT operator == (const LC_MATRIX3X2&) const		;
	INT operator != (const LC_MATRIX3X2&) const		;
};


struct LC_MATRIX3X3
{
	union { struct {
			FLOAT _11, _12, _13;
			FLOAT _21, _22, _23;
			FLOAT _31, _32, _33; };
            FLOAT m[3][3]; };

	LC_MATRIX3X3()									;
	LC_MATRIX3X3( FLOAT t11, FLOAT t12, FLOAT t13
				, FLOAT t21, FLOAT t22, FLOAT t23
				, FLOAT t31, FLOAT t32, FLOAT t33)	;

	operator FLOAT*()								;
	operator const FLOAT*() const					;
	INT operator == (const LC_MATRIX3X3&) const		;
	INT operator != (const LC_MATRIX3X3&) const		;
};


struct LC_MATRIX4X3
{
	union { struct {
			FLOAT _11, _12, _13;
			FLOAT _21, _22, _23;
			FLOAT _31, _32, _33;
			FLOAT _41, _42, _43; };
            FLOAT m[4][3]; };

	LC_MATRIX4X3()									;
	LC_MATRIX4X3(
			   FLOAT t11, FLOAT t12, FLOAT t13
			,  FLOAT t21, FLOAT t22, FLOAT t23
			,  FLOAT t31, FLOAT t32, FLOAT t33
			,  FLOAT t41, FLOAT t42, FLOAT t43)		;

	operator FLOAT*()								;
	operator const FLOAT*() const					;
	INT operator == (const LC_MATRIX4X3&) const		;
	INT operator != (const LC_MATRIX4X3&) const		;
};


struct LC_MATRIX
{
	union { struct {
			FLOAT _11, _12, _13, _14;
			FLOAT _21, _22, _23, _24;
			FLOAT _31, _32, _33, _34;
			FLOAT _41, _42, _43, _44; };
            FLOAT m[4][4]; };

	LC_MATRIX()										;
	LC_MATRIX(FLOAT t11, FLOAT t12, FLOAT t13, FLOAT t14
			, FLOAT t21, FLOAT t22, FLOAT t23, FLOAT t24
			, FLOAT t31, FLOAT t32, FLOAT t33, FLOAT t34
			, FLOAT t41, FLOAT t42, FLOAT t43, FLOAT t44);

	operator FLOAT*()								;
	operator const FLOAT*() const					;
	INT operator == (const LC_MATRIX&) const		;
	INT operator != (const LC_MATRIX&) const		;
};




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// glc argument interface

// glc argument structure
struct TLC_ARG
{
    union {  LC_HANDLE p; DOUBLE d; DINT n; UDINT u; };

    operator INT           (){ return (INT  )n;        }
    operator UINT          (){ return (UINT )n;        }
    operator SHORT         (){ return (SHORT)n;        }
    operator LONG          (){ return (LONG )n;        }
    operator ULONG         (){ return (ULONG)n;        }
    operator WORD          (){ return (WORD )n;        }
    operator QWORD         (){ return (QWORD)n;        }
	operator DINT          (){ return (DINT )n;        }

    operator FLOAT         (){ return (FLOAT)d;        }
    operator DOUBLE        (){ return        d;        }

    operator LC_HANDLE     (){ return                p; }
    operator char*         (){ return (char*        )p; }
    operator const char*   (){ return (const char*  )p; }
	operator char**        (){ return (char**       )p; }
    operator const char**  (){ return (const char** )p; }
    operator BYTE*         (){ return (BYTE*        )p; }
    operator const BYTE*   (){ return (const BYTE*  )p; }
	operator BYTE**        (){ return (BYTE**       )p; }
    operator const BYTE**  (){ return (const BYTE** )p; }

	operator INT*          (){ return (INT*         )p; }
    operator const INT*    (){ return (const INT*   )p; }
	operator UINT*         (){ return (UINT*        )p; }
    operator const UINT*   (){ return (const UINT*  )p; }
	operator SHORT*        (){ return (SHORT*       )p; }
    operator const SHORT*  (){ return (const SHORT* )p; }
	operator LONG*         (){ return (LONG*        )p; }
    operator const LONG*   (){ return (const LONG*  )p; }

	operator ULONG*        (){ return (ULONG*       )p; }
    operator const ULONG*  (){ return (const ULONG* )p; }
	operator WORD*         (){ return (WORD*        )p; }
    operator const WORD*   (){ return (const WORD*  )p; }
	operator QWORD*        (){ return (QWORD*       )p; }
    operator const QWORD*  (){ return (const QWORD* )p; }
	operator DINT*         (){ return (DINT*        )p; }
    operator const DINT*   (){ return (const DINT*  )p; }

	operator FLOAT*        (){ return (FLOAT*       )p; }
    operator const FLOAT*  (){ return (const FLOAT* )p; }
	operator DOUBLE*       (){ return (DOUBLE*      )p; }
    operator const DOUBLE* (){ return (const DOUBLE*)p; }

    INT       operator =(const INT       &v){ n=v; return (INT   )n; }
    UINT      operator =(const UINT      &v){ n=v; return (UINT  )n; }
    SHORT     operator =(const SHORT     &v){ n=v; return (SHORT )n; }
    USHORT    operator =(const USHORT    &v){ n=v; return (USHORT)n; }
    LONG      operator =(const LONG      &v){ n=v; return (LONG  )n; }
    ULONG     operator =(const ULONG     &v){ n=v; return (ULONG )n; }
    QWORD     operator =(const QWORD     &v){ n=v; return (QWORD )n; }
    DINT      operator =(const DINT      &v){ n=v; return (DINT  )n; }

    DOUBLE    operator =(const DOUBLE    &v){ d=v; return (DOUBLE)d; }
    FLOAT     operator =(const FLOAT     &v){ d=v; return (FLOAT )d; }

    LC_HANDLE operator =(const LC_HANDLE &v){ p=(LC_HANDLE)v; return (LC_HANDLE)p;}
    char*     operator =(const char*     &v){ p=(LC_HANDLE)v; return (char* )p;   }
    BYTE*     operator =(const BYTE*     &v){ p=(LC_HANDLE)v; return (BYTE* )p;   }
	char**    operator =(const char**    &v){ p=(LC_HANDLE)v; return (char**)p;   }
    BYTE**    operator =(const BYTE**    &v){ p=(LC_HANDLE)v; return (BYTE**)p;   }
};


// glc argument list
struct TLC_ARGS
{
	union
	{
		struct { TLC_ARG _0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,_d,_e,_f,_g,_h,_i,_j; };
		struct { TLC_ARG p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,pa,pb,pc,pd,pe,pf,pg,ph,pi,pj; };
		TLC_ARG m[20];
	};
};
typedef TLC_ARGS* PLC_ARGS;


#define  _MAKE_ARG1(v,v0)\
	TLC_ARGS v={0}; (v)._0=(v0);

#define  _MAKE_ARG2(v,v0,v1)\
	TLC_ARGS v={0}; (v)._0=(v0);(v)._1=(v1);

#define  _MAKE_ARG3(v,v0,v1,v2)\
	TLC_ARGS v={0}; (v)._0=(v0);(v)._1=(v1);(v)._2=(v2);

#define  _MAKE_ARG4(v,v0,v1,v2,v3)\
	TLC_ARGS v={0}; (v)._0=(v0);(v)._1=(v1);(v)._2=(v2);(v)._3=(v3);

#define  _MAKE_ARG5(v,v0,v1,v2,v3,v4)\
	TLC_ARGS v={0}; (v)._0=(v0);(v)._1=(v1);(v)._2=(v2);(v)._3=(v3);(v)._4=(v4);

#define  _MAKE_ARG6(v,v0,v1,v2,v3,v4,v5)\
	TLC_ARGS v={0}; (v)._0=(v0);(v)._1=(v1);(v)._2=(v2);(v)._3=(v3);(v)._4=(v4);(v)._5=(v5);

#define  _MAKE_ARG7(v,v0,v1,v2,v3,v4,v5,v6)\
	TLC_ARGS v={0}; (v)._0=(v0);(v)._1=(v1);(v)._2=(v2);(v)._3=(v3);(v)._4=(v4);(v)._5=(v5);(v)._6=(v6);

#define  _MAKE_ARG8(v,v0,v1,v2,v3,v4,v5,v6,v7)\
	TLC_ARGS v={0}; (v)._0=(v0);(v)._1=(v1);(v)._2=(v2);(v)._3=(v3);(v)._4=(v4);(v)._5=(v5);(v)._6=(v6);(v)._7=(v7);

#define  _MAKE_ARG9(v,v0,v1,v2,v3,v4,v5,v6,v7,v8)\
	TLC_ARGS v={0}; (v)._0=(v0);(v)._1=(v1);(v)._2=(v2);(v)._3=(v3);(v)._4=(v4);(v)._5=(v5);(v)._6=(v6);(v)._7=(v7);\
	(v)._8=(v8);

#define _MAKE_ARG10(v,v0,v1,v2,v3,v4,v5,v6,v7,v8,v9)\
	TLC_ARGS v={0}; (v)._0=(v0);(v)._1=(v1);(v)._2=(v2);(v)._3=(v3);(v)._4=(v4);(v)._5=(v5);(v)._6=(v6);(v)._7=(v7);\
	(v)._8=(v8);(v)._9=(v9);

#define _MAKE_ARG11(v,v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,va)\
	TLC_ARGS v={0}; (v)._0=(v0);(v)._1=(v1);(v)._2=(v2);(v)._3=(v3);(v)._4=(v4);(v)._5=(v5);(v)._6=(v6);(v)._7=(v7);\
	(v)._8=(v8);(v)._9=(v9);(v)._a=(va);

#define _MAKE_ARG12(v,v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,va,vb)\
	TLC_ARGS v={0}; (v)._0=(v0);(v)._1=(v1);(v)._2=(v2);(v)._3=(v3);(v)._4=(v4);(v)._5=(v5);(v)._6=(v6);(v)._7=(v7);\
	(v)._8=(v8);(v)._9=(v9);(v)._a=(va);(v)._b=(vb);

#define _MAKE_ARG13(v,v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,va,vb,vc)\
	TLC_ARGS v={0}; (v)._0=(v0);(v)._1=(v1);(v)._2=(v2);(v)._3=(v3);(v)._4=(v4);(v)._5=(v5);(v)._6=(v6);(v)._7=(v7);\
	(v)._8=(v8);(v)._9=(v9);(v)._a=(va);(v)._b=(vb);(v)._c=(vc);

#define _MAKE_ARG14(v,v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,va,vb,vc,vd)\
	TLC_ARGS v={0}; (v)._0=(v0);(v)._1=(v1);(v)._2=(v2);(v)._3=(v3);(v)._4=(v4);(v)._5=(v5);(v)._6=(v6);(v)._7=(v7);\
	(v)._8=(v8);(v)._9=(v9);(v)._a=(va);(v)._b=(vb);(v)._c=(vc);(v)._d=(vd);

#define _MAKE_ARG15(v,v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,va,vb,vc,vd,ve)\
	TLC_ARGS v={0}; (v)._0=(v0);(v)._1=(v1);(v)._2=(v2);(v)._3=(v3);(v)._4=(v4);(v)._5=(v5);(v)._6=(v6);(v)._7=(v7);\
	(v)._8=(v8);(v)._9=(v9);(v)._a=(va);(v)._b=(vb);(v)._c=(vc);(v)._d=(vd);(v)._e=(ve);

#define _MAKE_ARG16(v,v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,va,vb,vc,vd,ve,vf)\
	TLC_ARGS v={0}; (v)._0=(v0);(v)._1=(v1);(v)._2=(v2);(v)._3=(v3);(v)._4=(v4);(v)._5=(v5);(v)._6=(v6);(v)._7=(v7);\
	(v)._8=(v8);(v)._9=(v9);(v)._a=(va);(v)._b=(vb);(v)._c=(vc);(v)._d=(vd);(v)._e=(ve);(v)._f=(vf);

#define _MAKE_ARG17(v,v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,va,vb,vc,vd,ve,vf,vg)\
	TLC_ARGS v={0}; (v)._0=(v0);(v)._1=(v1);(v)._2=(v2);(v)._3=(v3);(v)._4=(v4);(v)._5=(v5);(v)._6=(v6);(v)._7=(v7);\
	(v)._8=(v8);(v)._9=(v9);(v)._a=(va);(v)._b=(vb);(v)._c=(vc);(v)._d=(vd);(v)._e=(ve);(v)._f=(vf);\
	(v)._g=(vg);

#define _MAKE_ARG18(v,v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,va,vb,vc,vd,ve,vf,vg,vh)\
	TLC_ARGS v={0}; (v)._0=(v0);(v)._1=(v1);(v)._2=(v2);(v)._3=(v3);(v)._4=(v4);(v)._5=(v5);(v)._6=(v6);(v)._7=(v7);\
	(v)._8=(v8);(v)._9=(v9);(v)._a=(va);(v)._b=(vb);(v)._c=(vc);(v)._d=(vd);(v)._e=(ve);(v)._f=(vf);\
	(v)._g=(vg);(v)._h=(vh);

#define _MAKE_ARG19(v,v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,va,vb,vc,vd,ve,vf,vg,vh,vi)\
	TLC_ARGS v={0}; (v)._0=(v0);(v)._1=(v1);(v)._2=(v2);(v)._3=(v3);(v)._4=(v4);(v)._5=(v5);(v)._6=(v6);(v)._7=(v7);\
	(v)._8=(v8);(v)._9=(v9);(v)._a=(va);(v)._b=(vb);(v)._c=(vc);(v)._d=(vd);(v)._e=(ve);(v)._f=(vf);\
	(v)._g=(vg);(v)._h=(vh);(v)._i=(vi);

#define _MAKE_ARG20(v,v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,va,vb,vc,vd,ve,vf,vg,vh,vi,vj)\
	TLC_ARGS v={0}; (v)._0=(v0);(v)._1=(v1);(v)._2=(v2);(v)._3=(v3);(v)._4=(v4);(v)._5=(v5);(v)._6=(v6);(v)._7=(v7);\
	(v)._8=(v8);(v)._9=(v9);(v)._a=(va);(v)._b=(vb);(v)._c=(vc);(v)._d=(vd);(v)._e=(ve);(v)._f=(vf);\
	(v)._g=(vg);(v)._h=(vh);(v)._i=(vi);(v)._j=(vj);


#define  MAKE_ARG1(v,v0)\
	(v)._0=(v0); (v)._1=L_NIL;(v)._2=L_NIL;(v)._3=L_NIL;(v)._4=L_NIL;(v)._5=L_NIL;(v)._6=L_NIL;(v)._7=L_NIL;\
	(v)._8=L_NIL;(v)._9=L_NIL;(v)._a=L_NIL;(v)._b=L_NIL;(v)._c=L_NIL;(v)._d=L_NIL;(v)._e=L_NIL;(v)._f=L_NIL;\
	(v)._g=L_NIL;(v)._h=L_NIL;(v)._i=L_NIL;(v)._j=L_NIL;

#define  MAKE_ARG2(v,v0,v1)\
	(v)._0=(v0); (v)._1=(v1); (v)._2=L_NIL;(v)._3=L_NIL;(v)._4=L_NIL;(v)._5=L_NIL;(v)._6=L_NIL;(v)._7=L_NIL;\
	(v)._8=L_NIL;(v)._9=L_NIL;(v)._a=L_NIL;(v)._b=L_NIL;(v)._c=L_NIL;(v)._d=L_NIL;(v)._e=L_NIL;(v)._f=L_NIL;\
	(v)._g=L_NIL;(v)._h=L_NIL;(v)._i=L_NIL;(v)._j=L_NIL;

#define  MAKE_ARG3(v,v0,v1,v2)\
	(v)._0=(v0); (v)._1=(v1); (v)._2=(v2); (v)._3=L_NIL;(v)._4=L_NIL;(v)._5=L_NIL;(v)._6=L_NIL;(v)._7=L_NIL;\
	(v)._8=L_NIL;(v)._9=L_NIL;(v)._a=L_NIL;(v)._b=L_NIL;(v)._c=L_NIL;(v)._d=L_NIL;(v)._e=L_NIL;(v)._f=L_NIL;\
	(v)._g=L_NIL;(v)._h=L_NIL;(v)._i=L_NIL;(v)._j=L_NIL;

#define  MAKE_ARG4(v,v0,v1,v2,v3)\
	(v)._0=(v0); (v)._1=(v1); (v)._2=(v2); (v)._3=(v3); (v)._4=L_NIL;(v)._5=L_NIL;(v)._6=L_NIL;(v)._7=L_NIL;\
	(v)._8=L_NIL;(v)._9=L_NIL;(v)._a=L_NIL;(v)._b=L_NIL;(v)._c=L_NIL;(v)._d=L_NIL;(v)._e=L_NIL;(v)._f=L_NIL;\
	(v)._g=L_NIL;(v)._h=L_NIL;(v)._i=L_NIL;(v)._j=L_NIL;

#define  MAKE_ARG5(v,v0,v1,v2,v3,v4)\
	(v)._0=(v0); (v)._1=(v1); (v)._2=(v2); (v)._3=(v3); (v)._4=(v4); (v)._5=L_NIL;(v)._6=L_NIL;(v)._7=L_NIL;\
	(v)._8=L_NIL;(v)._9=L_NIL;(v)._a=L_NIL;(v)._b=L_NIL;(v)._c=L_NIL;(v)._d=L_NIL;(v)._e=L_NIL;(v)._f=L_NIL;\
	(v)._g=L_NIL;(v)._h=L_NIL;(v)._i=L_NIL;(v)._j=L_NIL;

#define  MAKE_ARG6(v,v0,v1,v2,v3,v4,v5)\
	(v)._0=(v0); (v)._1=(v1); (v)._2=(v2); (v)._3=(v3); (v)._4=(v4); (v)._5=(v5); (v)._6=L_NIL;(v)._7=L_NIL;\
	(v)._8=L_NIL;(v)._9=L_NIL;(v)._a=L_NIL;(v)._b=L_NIL;(v)._c=L_NIL;(v)._d=L_NIL;(v)._e=L_NIL;(v)._f=L_NIL;\
	(v)._g=L_NIL;(v)._h=L_NIL;(v)._i=L_NIL;(v)._j=L_NIL;

#define  MAKE_ARG7(v,v0,v1,v2,v3,v4,v5,v6)\
	(v)._0=(v0); (v)._1=(v1); (v)._2=(v2); (v)._3=(v3); (v)._4=(v4); (v)._5=(v5); (v)._6=(v6);(v)._7=L_NIL;\
	(v)._8=L_NIL;(v)._9=L_NIL;(v)._a=L_NIL;(v)._b=L_NIL;(v)._c=L_NIL;(v)._d=L_NIL;(v)._e=L_NIL;(v)._f=L_NIL;\
	(v)._g=L_NIL;(v)._h=L_NIL;(v)._i=L_NIL;(v)._j=L_NIL;

#define  MAKE_ARG8(v,v0,v1,v2,v3,v4,v5,v6,v7)\
	(v)._0=(v0); (v)._1=(v1); (v)._2=(v2); (v)._3=(v3); (v)._4=(v4); (v)._5=(v5); (v)._6=(v6); (v)._7=(v7);\
	(v)._8=L_NIL;(v)._9=L_NIL;(v)._a=L_NIL;(v)._b=L_NIL;(v)._c=L_NIL;(v)._d=L_NIL;(v)._e=L_NIL;(v)._f=L_NIL;\
	(v)._g=L_NIL;(v)._h=L_NIL;(v)._i=L_NIL;(v)._j=L_NIL;

#define  MAKE_ARG9(v,v0,v1,v2,v3,v4,v5,v6,v7,v8)\
	(v)._0=(v0); (v)._1=(v1); (v)._2=(v2); (v)._3=(v3); (v)._4=(v4); (v)._5=(v5); (v)._6=(v6); (v)._7=(v7);\
	(v)._8=(v8);(v)._9=L_NIL;(v)._a=L_NIL;(v)._b=L_NIL;(v)._c=L_NIL;(v)._d=L_NIL;(v)._e=L_NIL;(v)._f=L_NIL;\
	(v)._g=L_NIL;(v)._h=L_NIL;(v)._i=L_NIL;(v)._j=L_NIL;

#define MAKE_ARG10(v,v0,v1,v2,v3,v4,v5,v6,v7,v8,v9)\
	(v)._0=(v0);(v)._1=(v1);(v)._2=(v2); (v)._3=(v3); (v)._4=(v4); (v)._5=(v5); (v)._6=(v6); (v)._7=(v7);\
	(v)._8=(v8);(v)._9=(v9);(v)._a=L_NIL;(v)._b=L_NIL;(v)._c=L_NIL;(v)._d=L_NIL;(v)._e=L_NIL;(v)._f=L_NIL;\
	(v)._g=L_NIL;(v)._h=L_NIL;(v)._i=L_NIL;(v)._j=L_NIL;

#define MAKE_ARG11(v,v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,va)\
	(v)._0=(v0);(v)._1=(v1);(v)._2=(v2);(v)._3=(v3); (v)._4=(v4); (v)._5=(v5); (v)._6=(v6); (v)._7=(v7);\
	(v)._8=(v8);(v)._9=(v9);(v)._a=(va);(v)._b=L_NIL;(v)._c=L_NIL;(v)._d=L_NIL;(v)._e=L_NIL;(v)._f=L_NIL;\
	(v)._g=L_NIL;(v)._h=L_NIL;(v)._i=L_NIL;(v)._j=L_NIL;

#define MAKE_ARG12(v,v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,va,vb)\
	(v)._0=(v0);(v)._1=(v1);(v)._2=(v2);(v)._3=(v3);(v)._4=(v4); (v)._5=(v5); (v)._6=(v6); (v)._7=(v7);\
	(v)._8=(v8);(v)._9=(v9);(v)._a=(va);(v)._b=(vb);(v)._c=L_NIL;(v)._d=L_NIL;(v)._e=L_NIL;(v)._f=L_NIL;\
	(v)._g=L_NIL;(v)._h=L_NIL;(v)._i=L_NIL;(v)._j=L_NIL;

#define MAKE_ARG13(v,v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,va,vb,vc)\
	(v)._0=(v0);(v)._1=(v1);(v)._2=(v2);(v)._3=(v3);(v)._4=(v4);(v)._5=(v5); (v)._6=(v6); (v)._7=(v7);\
	(v)._8=(v8);(v)._9=(v9);(v)._a=(va);(v)._b=(vb);(v)._c=(vc);(v)._d=L_NIL;(v)._e=L_NIL;(v)._f=L_NIL;\
	(v)._g=L_NIL;(v)._h=L_NIL;(v)._i=L_NIL;(v)._j=L_NIL;

#define MAKE_ARG14(v,v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,va,vb,vc,vd)\
	(v)._0=(v0);(v)._1=(v1);(v)._2=(v2);(v)._3=(v3);(v)._4=(v4);(v)._5=(v5);(v)._6=(v6); (v)._7=(v7);\
	(v)._8=(v8);(v)._9=(v9);(v)._a=(va);(v)._b=(vb);(v)._c=(vc);(v)._d=(vd);(v)._e=L_NIL;(v)._f=L_NIL;\
	(v)._g=L_NIL;(v)._h=L_NIL;(v)._i=L_NIL;(v)._j=L_NIL;

#define MAKE_ARG15(v,v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,va,vb,vc,vd,ve)\
	(v)._0=(v0);(v)._1=(v1);(v)._2=(v2);(v)._3=(v3);(v)._4=(v4);(v)._5=(v5);(v)._6=(v6);(v)._7=(v7);\
	(v)._8=(v8);(v)._9=(v9);(v)._a=(va);(v)._b=(vb);(v)._c=(vc);(v)._d=(vd);(v)._e=(ve);(v)._f=L_NIL;\
	(v)._g=L_NIL;(v)._h=L_NIL;(v)._i=L_NIL;(v)._j=L_NIL;

#define MAKE_ARG16(v,v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,va,vb,vc,vd,ve,vf)\
	(v)._0=(v0);(v)._1=(v1);(v)._2=(v2);(v)._3=(v3);(v)._4=(v4);(v)._5=(v5);(v)._6=(v6);(v)._7=(v7);\
	(v)._8=(v8);(v)._9=(v9);(v)._a=(va);(v)._b=(vb);(v)._c=(vc);(v)._d=(vd);(v)._e=(ve);(v)._f=(vf);\
	(v)._g=L_NIL;(v)._h=L_NIL;(v)._i=L_NIL;(v)._j=L_NIL;

#define MAKE_ARG17(v,v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,va,vb,vc,vd,ve,vf,vg)\
	(v)._0=(v0);(v)._1=(v1);(v)._2=(v2);(v)._3=(v3);(v)._4=(v4);(v)._5=(v5);(v)._6=(v6);(v)._7=(v7);\
	(v)._8=(v8);(v)._9=(v9);(v)._a=(va);(v)._b=(vb);(v)._c=(vc);(v)._d=(vd);(v)._e=(ve);(v)._f=(vf);\
	(v)._g=(vg);(v)._h=L_NIL;(v)._i=L_NIL;(v)._j=L_NIL;

#define MAKE_ARG18(v,v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,va,vb,vc,vd,ve,vf,vg,vh)\
	(v)._0=(v0);(v)._1=(v1);(v)._2=(v2);(v)._3=(v3);(v)._4=(v4);(v)._5=(v5);(v)._6=(v6);(v)._7=(v7);\
	(v)._8=(v8);(v)._9=(v9);(v)._a=(va);(v)._b=(vb);(v)._c=(vc);(v)._d=(vd);(v)._e=(ve);(v)._f=(vf);\
	(v)._g=(vg);(v)._h=(vh);(v)._i=L_NIL;(v)._j=L_NIL;

#define MAKE_ARG19(v,v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,va,vb,vc,vd,ve,vf,vg,vh,vi)\
	(v)._0=(v0);(v)._1=(v1);(v)._2=(v2);(v)._3=(v3);(v)._4=(v4);(v)._5=(v5);(v)._6=(v6);(v)._7=(v7);\
	(v)._8=(v8);(v)._9=(v9);(v)._a=(va);(v)._b=(vb);(v)._c=(vc);(v)._d=(vd);(v)._e=(ve);(v)._f=(vf);\
	(v)._g=(vg);(v)._h=(vh);(v)._i=(vi);(v)._j=L_NIL;

#define MAKE_ARG20(v,v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,va,vb,vc,vd,ve,vf,vg,vh,vi,vj)\
	(v)._0=(v0);(v)._1=(v1);(v)._2=(v2);(v)._3=(v3);(v)._4=(v4);(v)._5=(v5);(v)._6=(v6);(v)._7=(v7);\
	(v)._8=(v8);(v)._9=(v9);(v)._a=(va);(v)._b=(vb);(v)._c=(vc);(v)._d=(vd);(v)._e=(ve);(v)._f=(vf);\
	(v)._g=(vg);(v)._h=(vh);(v)._i=(vi);(v)._j=(vj);


void      LcArgs_Reset    (PLC_ARGS _dst);												// reset the args to zero
void      LcArgs_FromInt  (PLC_ARGS _dst, const INT*     _src, INT cnt);				// copy from int array[max 8]
void      LcArgs_ToInt    (INT*     _src, const PLC_ARGS _dst, INT cnt);				// copy to int array[max 8]
void      LcArgs_FromFloat(PLC_ARGS _dst, const FLOAT*   _src, INT cnt);				// copy from float array[max 8]
void      LcArgs_ToFloat  (FLOAT*   _src, const PLC_ARGS _dst, INT cnt);				// copy to float array[max 8]
LC_HANDLE LcArgs_ToHandle (LC_HANDLE p);												// static casting from args element
LC_HANDLE LcArgs_ToHandle (const PLC_ARGS _src, INT index);								// static casting from args index



//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// to save the GLOBAL VARIABLEs chunk for system and application


struct TLC_VAR
{
	union {
		struct{ INT       _i0, _i1, _i2, _i3, _i4, _i5, _i6, _i7, _i8, _i9, _ia, _ib, _ic, _id, _ie, _if; };
		struct{ FLOAT     _f0, _f1, _f2, _f3, _f4, _f5, _f6, _f7, _f8, _f9, _fa, _fb, _fc, _fd, _fe, _ff; };
		struct{ LC_HANDLE _p0, _p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9, _pa, _pb, _pc, _pd, _pe, _pf; };
		struct{ DOUBLE    _d0, _d1, _d2, _d3, _d4, _d5, _d6, _d7; };
		struct{ DINT      _n0, _n1, _n2, _n3, _n4, _n5, _n6, _n7; };
		struct{ UDINT     _u0, _u1, _u2, _u3, _u4, _u5, _u6, _u7; };
		struct{ SHORT     _s0, _s1, _s2, _s3, _s4, _s5, _s6, _s7, _s8, _s9, _sa, _sb, _sc, _sd, _se, _sf; };
		struct{ INT       _ix, _iy, _iw, _ih; };
		struct{ INT       _cr, _cg, _cb, _ca, _cd, _cs, _cw, _ch; };
		struct{ FLOAT     _x,   _y,  _z,  _w; };
		struct{ FLOAT     _11, _12, _13, _14, _21, _22, _23, _24, _31, _32, _33, _34, _41, _42, _43, _44; };
		INT8   v_b[64];    INT16  v_s[32];    INT32  v_i[16];    INT64  v_n[ 8];
		FLOAT  v_f[16];    DOUBLE v_d[ 8];    LPVOID v_p[16];
	};

	TLC_VAR();
	TLC_VAR(  INT _0  , INT _1=0, INT _2=0, INT _3=0
			, INT _4=0, INT _5=0, INT _6=0, INT _7=0
			, INT _8=0, INT _9=0, INT _a=0, INT _b=0
			, INT _c=0, INT _d=0, INT _e=0, INT _f=0);

	TLC_VAR(  DINT _0  , DINT _1=0, DINT _2=0, DINT _3=0
			, DINT _4=0, DINT _5=0, DINT _6=0, DINT _7=0);

	TLC_VAR(  FLOAT  _0     , FLOAT _1=0.0F, FLOAT _2=0.0F, FLOAT _3=0.0F
			, FLOAT  _4=0.0F, FLOAT _5=0.0F, FLOAT _6=0.0F, FLOAT _7=0.0F
			, FLOAT  _8=0.0F, FLOAT _9=0.0F, FLOAT _a=0.0F, FLOAT _b=0.0F
			, FLOAT  _c=0.0F, FLOAT _d=0.0F, FLOAT _e=0.0F, FLOAT _f=0.0F);

	TLC_VAR(  DOUBLE  _0    , DOUBLE _1=0.0, DOUBLE _2=0.0, DOUBLE _3=0.0
			, DOUBLE  _4=0.0, DOUBLE _5=0.0, DOUBLE _6=0.0, DOUBLE _7=0.0);

	TLC_VAR(  LC_HANDLE _0     , LC_HANDLE _1=NULL, LC_HANDLE _2=NULL, LC_HANDLE _3=NULL
			, LC_HANDLE _4=NULL, LC_HANDLE _5=NULL, LC_HANDLE _6=NULL, LC_HANDLE _7=NULL
			, LC_HANDLE _8=NULL, LC_HANDLE _9=NULL, LC_HANDLE _a=NULL, LC_HANDLE _b=NULL
			, LC_HANDLE _c=NULL, LC_HANDLE _d=NULL, LC_HANDLE _e=NULL, LC_HANDLE _f=NULL);

	TLC_VAR& operator =  (const TLC_VAR&);
	TLC_VAR& operator =  (const TLC_VAR*);
	INT      operator == (const TLC_VAR&) const	;
	INT      operator != (const TLC_VAR&) const	;

	void     Clear();

	void     Int8  (int index, INT8      val);
	void     Int16 (int index, INT16     val);
	void     Int32 (int index, INT32     val);
	void     Int64 (int index, INT64     val);
	void     Float (int index, FLOAT     val);
	void     Double(int index, DOUBLE    val);
	void     Handle(int index, LC_HANDLE val);

	void     ArrayInt8  (INT8     * val, int count);							// maximum 64
	void     ArrayInt16 (INT16    * val, int count);							// maximum 32
	void     ArrayInt32 (INT32    * val, int count);							// maximum 16
	void     ArrayInt64 (INT64    * val, int count);							// maximum  8
	void     ArrayFloat (FLOAT    * val, int count);							// maximum 16
	void     ArrayDouble(DOUBLE   * val, int count);							// maximum  8
	void     ArrayHandle(LC_HANDLE* val, int count);							// maximum 16
	void     String     (char     * val, int count);							// maximum 60

	INT8      Int8  (int index);
	INT16     Int16 (int index);
	INT32     Int32 (int index);
	INT64     Int64 (int index);
	FLOAT     Float (int index);
	DOUBLE    Double(int index);
	LC_HANDLE Handle(int index);

	INT8*      ArrayInt8  ();
	INT16*     ArrayInt16 ();
	INT32*     ArrayInt32 ();
	DINT*      ArrayInt64 ();
	FLOAT*     ArrayFloat ();
	DOUBLE*    ArrayDouble();
	LC_HANDLE* ArrayHandle();
	char*      String     ();
};
typedef TLC_VAR* PLC_VAR;



//++5++++1+++++++++2+++++++++3+++++++++4
// read/write the global variables

const TLC_VAR*  LcVar_Read (UINT  _lcVar);										// read the data from global, if _lcVar == LC_VAR_TOTAL then get the all chunk
const LC_HANDLE LcVar_ReadP(UINT  _lcVar, INT idx=0);							// get the pointer from global. idx=0,1,2,3
void  LcVar_Write (UINT _lcVar, TLC_VAR* pChunk=0);								// write the data to global. if(LC_VAR_WINDOW <= _lcVar && _lcVar <= LC_VAR_APP_NET) then directly access
void  LcVar_WriteP(UINT _lcVar, LC_HANDLE p, INT idx=0);						// write the data to global for pointer.
void  LcVar_WritePzero(UINT _lcVar);											// write null the data to global for pointer.

UINT  LcVar_Platform();															// SDK Version: Version(Major(Hi-word), Minor(Low-word), Build-date
INT   LcVar_Version(UINT* dVer, UINT* dDate);									// SDK Version: Version(Major(Hi-word), Minor(Low-word), Build-date
INT   LcVar_Log(INT*enable,INT*method,INT*count,LC_HANDLE*file,INT bWrite=0);	// log write enable, method(serial/file/mix), error count, file handle.
INT   LcVar_LogIncErrCount();													// Increase the error count.

INT   LcVar_WindowSize(INT* Width, INT* Height, INT bWrite=0);					// application screen width, screen height, bWrite = 0 ==> get the screen width and height. else ==> set the screen size
INT   LcVar_DisplayFormat(TLC_VAR* v, INT bWrite=0);							// device screen channel r, g, b, a, depth, stencil bit, display width, and height. it needs int * 8 array
INT   LcVar_DisplaySize(INT* Width, INT* Height);								// device screen  width, screen height
INT   LcVar_ClientRect(FLOAT* x, FLOAT* y, FLOAT* w, FLOAT* h, FLOAT* r=0);		// window rect on device. r = dstW/srcW

INT   LcVar_RefCountObject();													// Get the Remained GLC Object Reference Count.
INT   LcVar_IncRefCountObject();												// Increase the Reference Count. when the object is created, this function must be called.
INT   LcVar_DecRefCountObject();												// Decrease the Reference Count. when the object is destroy, this function must be called.
INT   LcVar_DestroyObject(PLC_OBJECT*);											// Release the GLC Object. Same as the ILC_Object::Release().
INT   LcVar_CheckSignature(void*);												// Check the file type in memory. LC_RSC_GPACK, LC_OBJ_WAV, LC_OBJ_OGG, etc. failed return  ==0

WORD* LcVar_QuadIndex();														// OpenGL Quad Index.

INT   LcVar_TimeElapsed (DOUBLE* Elapsed, INT bWrite=0);						// Set/Get the elapsed millisecond time per on frame.
INT   LcVar_TimeStored (DINT* Stored, INT bWrite=0);							// Set/Get the Stored Time.
INT   LcVar_TimeFrameRate (DOUBLE* Frames, INT bWrite=0);						// Set/Get the Frames per one second.




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// for image

typedef	int					lsc_int;
typedef	unsigned int		lsc_uint;
typedef	long				lsc_long;
typedef	unsigned long		lsc_dword;
typedef	unsigned char		lsc_byte;
typedef	unsigned short int	lsc_word;
typedef char*				lsc_buf;


#define _GL_T_UBYTE			0x1401
#define _GL_F_RGB			0x1907
#define _GL_F_RGBA			0x1908
#define _GL_GEN_MIPMAP		0x8191


#if defined(_MSC_VER)
  #pragma pack(push, 1)
#endif

typedef struct tag_Tinf_src
{
	lsc_dword	fs;									// file size
	lsc_dword	ts[2];								// creation time
}
#if defined(_MSC_VER)
  #pragma pack(pop)
#else
  __attribute__((packed))
#endif
Tinf_src;


#if defined(_MSC_VER)
  #pragma pack(push, 1)
#endif

typedef struct tag_Tinf_pf
{
	lsc_buf		src_n;								// File Name
	lsc_int		atts [8];							// Attribute
}
#if defined(_MSC_VER)
  #pragma pack(pop)
#else
  __attribute__((packed))
#endif
Tinf_pf;


#if defined(_MSC_VER)
  #pragma pack(push, 1)
#endif

typedef struct tag_Tinf_lf
{
	lsc_uint	fv[2];								// File Version
	lsc_dword	ts[2];								// modification:0 and creation time:1 of original file. it needs ULONG * 2
}
#if defined(_MSC_VER)
  #pragma pack(pop)
#else
  __attribute__((packed))
#endif
Tinf_lf;


int Gp_FileInfo		(Tinf_lf* pInf, lsc_uint* ver0, lsc_uint* ver1, lsc_dword* t0, lsc_dword* t1, const char* sFile);
int Gp_MemInfo 		(Tinf_lf* pInf, lsc_uint* ver0, lsc_uint* ver1, lsc_dword* t0, lsc_dword* t1, const void* memAddr);

#if defined(_MSC_VER)
  #pragma pack(push, 1)
#endif

typedef struct tag_Tinf_gpt
{
	Tinf_lf		inf_l;
	lsc_int		img_t;								// Pixel Type	GL_UNSIGNED_SHORT...
	lsc_int		img_f;								// Pixel Format	GL_RGB, RGBA, ....
	lsc_int		img_w;								// Image Width
	lsc_int		img_h;								// Image Height
	lsc_int		img_d;								// Image Depth	1(byte), 2(byte), 3(byte), 4(byte)
	lsc_uint	img_c;								// Image Color Key
}
#if defined(_MSC_VER)
  #pragma pack(pop)
#else
  __attribute__((packed))
#endif
Tinf_gpt;


int Gpt_FileInfo		(Tinf_gpt* pInf, char* sFile);
int Gpt_MemInfo 		(Tinf_gpt* pInf, const void* memAddr);
int Gpt_Info			(  lsc_int*  img_t
						 , lsc_int*  img_f
						 , lsc_int*  img_w
						 , lsc_int*  img_h
						 , lsc_int*  img_d
						 , lsc_uint* img_c
						 , const char* sFile);


int Gpt_FileRead		( lsc_byte**    poPxl		// Output Pixel
						, lsc_uint*     poImgT		// Output Image Pixel Type
						, lsc_uint*     poImgF		// Output Image Pixel Format
						, lsc_int*      poImgW		// Output Image Width
						, lsc_int*      poImgH		// Output Image Height
						, lsc_int*      poImgD		// Output Image Depth
						, lsc_uint*     poImgC		// Output Image Color Key
						, lsc_dword*    poTime		// modification:0 and creation time:1 of original file. it needs ULONG * 2
						, char*         sFile		// Source File
						);


int Gpt_MemRead			( lsc_byte**    poPxl		// Output Pixel
						, lsc_uint*     poImgT		// Output Image Pixel Type
						, lsc_uint*     poImgF		// Output Image Pixel Format
						, lsc_int*      poImgW		// Output Image Width
						, lsc_int*      poImgH		// Output Image Height
						, lsc_int*      poImgD		// Output Image Depth
						, lsc_uint*     poImgC		// Output Image Color Key
						, lsc_dword*    poTime		// modification:0 and creation time:1 of original file. it needs ULONG * 2
						, const void*   memAddr		// Memory buffer address
						, lsc_int       memSize		// Memory Size
						);


int Gpt_Read			( lsc_byte**    poPxl		// Output Pixel
						, lsc_uint*     poImgT		// Output Image Pixel Type
						, lsc_uint*     poImgF		// Output Image Pixel Format
						, lsc_int*      poImgW		// Output Image Width
						, lsc_int*      poImgH		// Output Image Height
						, lsc_int*      poImgD		// Output Image Depth
						, lsc_uint*     poImgC		// Output Image Color Key
						, lsc_dword*    poTime		// modification:0 and creation time:1 of original file. it needs ULONG * 2
						, char*         sFile		// Source File
						);



int Gpt_FileWrite		( void*         pInPxl		// Input Pixel
						, lsc_uint      nImgT		// Output Image Pixel Type
						, lsc_uint      nImgF		// Output Image Pixel Format
						, lsc_int       nImgW		// Output Image Width
						, lsc_int       nImgH		// Output Image Height
						, lsc_int       nImgD		// Output Image Depth
						, lsc_uint      nImgC		// Output Image Color Key
						, lsc_dword*    uTime		// modification:0 and creation time:1 of original file. it needs ULONG * 2
						, char*         sFile		// Dest File
						);




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8


int	Bmp_FileRead		( lsc_byte**    poPxl		// Output Pixel
						, lsc_uint*     poImgT		// Output Image Pixel Type: it must be GL_UNSIGNED_BYTE
						, lsc_uint*     poImgF		// Output Image Pixel Format
						, lsc_int*      poImgW		// Output Image Width
						, lsc_int*      poImgH		// Output Image Height
						, lsc_int*      poImgD		// Output Image Channel(byte)
						, lsc_uint*     poImgC		// Output Image Color Key. it must be 0x0
						, lsc_dword*    poTime		// modification:0 and creation time:1 of original file. it needs ULONG * 2
						, char*         sFile		// Source File
						);


int	Bmp_MemRead			( lsc_byte**    poPxl		// Output Pixel
						, lsc_uint*     poImgT		// Output Image Pixel Type: it must be GL_UNSIGNED_BYTE
						, lsc_uint*     poImgF		// Output Image Pixel Format
						, lsc_int*      poImgW		// Output Image Width
						, lsc_int*      poImgH		// Output Image Height
						, lsc_int*      poImgD		// Output Image Channel(byte)
						, lsc_uint*     poImgC		// Output Image Color Key. it must be 0x0
						, const void*   memAddr		// Memory buffer address
						, lsc_int       memSize		// Memory Size
						);




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8


int Png_CheckSignature	(lsc_byte* sig);	// call the png_sig_cmp() functions return FALSE(0) or etc.


int Png_FileRead		( lsc_byte**    poPxl		// Output Pixel
						, lsc_uint*     poImgT		// Output Image Pixel Type
						, lsc_uint*     poImgF		// Output Image Pixel Format
						, lsc_int*      poImgW		// Output Image Width
						, lsc_int*      poImgH		// Output Image Height
						, lsc_int*      poImgD		// Output Image Depth
						, lsc_uint*     poImgC		// Output Image Color Key
						, lsc_dword*    poTime		// modification:0 and creation time:1 of original file. it needs ULONG * 2
						, char*         sFile		// Source File
						);


int Png_MemRead			( lsc_byte**    poPxl		// Output Pixel
						, lsc_uint*     poImgT		// Output Image Pixel Type
						, lsc_uint*     poImgF		// Output Image Pixel Format
						, lsc_int*      poImgW		// Output Image Width
						, lsc_int*      poImgH		// Output Image Height
						, lsc_int*      poImgD		// Output Image Depth
						, lsc_uint*     poImgC		// Output Image Color Key
						, const void*   memAddr		// Memory buffer address
						, lsc_int       memSize		// Memory Size
						);




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8


int Tga_FileRead		( lsc_byte**    poPxl		// Output Pixel
						, lsc_uint*     poImgT		// Output Image Pixel Type
						, lsc_uint*     poImgF		// Output Image Pixel Format
						, lsc_int*      poImgW		// Output Image Width
						, lsc_int*      poImgH		// Output Image Height
						, lsc_int*      poImgD		// Output Image Depth
						, lsc_uint*     poImgC		// Output Image Color Key
						, lsc_dword*    poTime		// modification:0 and creation time:1 of original file. it needs ULONG * 2
						, char*         sFile		// Source File
						);


int Tga_FileWrite		( lsc_byte*     piPxl		// Source Pixel
						, lsc_word		nImgW		// Source Image Width
						, lsc_word		nImgH		// Source Image Height
						, lsc_word		nImgD		// Source Image Depth
						, char*         sFile		// Dest File
						);


int Tga_MemRead			( lsc_byte**    poPxl		// Output Pixel
						, lsc_uint*     poImgT		// Output Image Pixel Type
						, lsc_uint*     poImgF		// Output Image Pixel Format
						, lsc_int*      poImgW		// Output Image Width
						, lsc_int*      poImgH		// Output Image Height
						, lsc_int*      poImgD		// Output Image Depth
						, lsc_uint*     poImgC		// Output Image Color Key
						, const void*   memAddr		// Memory buffer address
						, lsc_int       memSize		// Memory Size
						);




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8


int Jpg_FileRead		( lsc_byte**    poPxl		// Output Pixel
						, lsc_uint*     poImgT		// Output Image Pixel Type
						, lsc_uint*     poImgF		// Output Image Pixel Format
						, lsc_int*      poImgW		// Output Image Width
						, lsc_int*      poImgH		// Output Image Height
						, lsc_int*      poImgD		// Output Image Depth
						, lsc_uint*     poImgC		// Output Image Color Key
						, lsc_dword*    poTime		// modification:0 and creation time:1 of original file. it needs ULONG * 2
						, char*         sFile		// Source File
						);


int Jpg_MemRead			( lsc_byte**    poPxl		// Output Pixel
						, lsc_uint*     poImgT		// Output Image Pixel Type
						, lsc_uint*     poImgF		// Output Image Pixel Format
						, lsc_int*      poImgW		// Output Image Width
						, lsc_int*      poImgH		// Output Image Height
						, lsc_int*      poImgD		// Output Image Depth
						, lsc_uint*     poImgC		// Output Image Color Key
						, const void*   memAddr		// Memory buffer address
						, lsc_int       memSize		// Memory Size
						);




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// for sound

#if defined(_MSC_VER)
  #pragma pack(push, 1)
#endif

typedef struct tag_Tinf_gps
{
	Tinf_lf		inf_l;
	lsc_uint	snd_f;								// Audio Format. It's not use. This sdk only supports PCM
	lsc_uint	snd_b;								// Audio Bit Rate: => 8 or 16. This sdk only supports 16bit sound
	lsc_uint	snd_c;								// Channels: Mono =>1, stereo =>2
	lsc_uint	snd_z;								// Sampling Rate: ex) 8000 kHz => 8, 22050 kHz => 22050
	lsc_uint	snd_l;								// Buffer Size
}
#if defined(_MSC_VER)
  #pragma pack(pop)
#else
  __attribute__((packed))
#endif
Tinf_gps;


int Gps_FileInfo		(Tinf_gps* pInf, char* sFile);
int Gps_MemInfo			(Tinf_gps* pInf, const void* memAddr);

int Gps_FileRead		( lsc_byte** poSndA			// Output Audio buffer
						, Tinf_gps*  poInf			// Output Info
						, char*      sFile			// Source File
						);

int Gps_MemRead			( lsc_byte** poSndA			// Output Audio buffer
						, Tinf_gps*  poInf			// Output Info
						, void*      memAddr		// memory
						, lsc_uint   memSize		// memAddr Size
						);

int Gps_FileWrite		( void*      pSndA			// Input Audio buffer
						, Tinf_gps*  poInf			// Output Info
						, char*      sFile			// Dest File
						);

int Wav_FileRead		( lsc_byte** poSndA			// Output Audio buffer
						, Tinf_gps*  poInf			// Output Info
						, char*      sFile			// Source File
						);

int Wav_MemRead			( lsc_byte** poSndA			// Output Audio buffer
						, Tinf_gps*  poInf			// Output Info
						, void*      memAddr		// memory
						, lsc_uint   memSize		// memAddr Size
						);

int Ogg_FileRead		( lsc_byte** poSndA			// Output Audio buffer
						, Tinf_gps*  poInf			// Output Info
						, char*      sFile			// Input file name
						);

int Ogg_MemRead			( lsc_byte** poSndA			// Output Audio buffer
						, Tinf_gps*  poInf			// Output Info
						, void*      memAddr		// Input Audio buffer
						, lsc_uint   memSize		// Input Audio buffer size
						);

int Ogg_ReleaseBuf		( lsc_buf* oggBuf);			// release ogg buffer from Ogg_Create{} functions




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// for data sharing on system

struct TLC_SCDS										// sharing common data source
{
    char		name[LC_DEFAULT_NAME];				// name
	LC_HANDLE	ins;								// instance
	int			rfc;								// reference count
	int			len;								// length for instance

	LC_HANDLE	sbi[4];								// sub instance
	int			sbt[4];								// sub attribute

	TLC_SCDS();
	TLC_SCDS(const char* s, LC_HANDLE p, int _rfc=1, int _len=0);
};

struct TLC_SKEY										// Single simple key
{
	char	sKey	[LC_RSC_SID];					// String Keword
	INT		iKey	;								// etc
};


//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// for android

#if !defined(__ANDROID__)
  typedef BYTE          jboolean	;
  typedef INT8          jbyte		;
  typedef USHORT        jchar		;
  typedef SHORT         jshort		;
  typedef INT           jint		;
  typedef DINT          jlong		;
  typedef FLOAT         jfloat		;
  typedef DOUBLE        jdouble		;
  typedef LC_HANDLE		JavaVM		;
  typedef LC_HANDLE		JNIEnv		;
  typedef LC_HANDLE		jclass		;
  typedef LC_HANDLE		jfieldID	;
  typedef LC_HANDLE		jmethodID	;
  typedef LC_HANDLE		jobject		;
  typedef LC_HANDLE		jstring		;
  typedef LC_HANDLE		jbyteArray	;
  typedef LC_HANDLE		jintArray	;
  typedef LC_HANDLE		jfloatArray	;
#endif


#endif	//_LcBase_H_

