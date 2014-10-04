// GalicSoft Game Library Collection. Copyright(C) GALICSOFT. All rights reserved.
//
//	Math Library.
//
//	Operator Overriding
//	Dot Product: '*'
//	Cross Product: '^'
//
////////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER)
  #pragma once
#endif

#ifndef _LcMath_H_
#define _LcMath_H_

#include <math.h>
#include "LcType.h"
#include "LcBase.h"

#define LCX_FMAX		3.402823466e+36F
#define LCX_PI			3.1415926535897932384626433832795
#define LCX_PI2         1.5707963267948966192313216916398
#define LCX_PI23        4.7123889803846898576939650749193
#define LCX_ROOT05		0.7071067811865475244008443621049
#define LCX_ROOT2		1.4142135623730950488016887242097
#define LCX_ROOT3		1.7320508075688772935274463415059
#define ONE_RADtoDEG	57.295779513082320876798154814105
#define ONE_DEGtoRAD	.01745329251994329576923690768489
#define DEG90toRAD		1.5707963267948966192313216916398
#define LCXToRadian(d)	(float)((d) * LCX_PI / 180.0)
#define LCXToDegree(r)	(float)((r) * 180.0  / LCX_PI)
#define RADtoDEG(v)		(float)( (v)*ONE_RADtoDEG)
#define DEGtoRAD(v)		(float)( (v)*ONE_DEGtoRAD)
#define LCX_R_DELTA		0.00005
#define LCX_FIXF		65536.0F
#define LCX_DEPTH		4096.0F

template<class T> T lc_abs  (T v){ return (0.0 <= v)? v : -v; }
template<class T> T lc_mix  (T a, T b, T v){ return (v<a)? a:((v>b)? b:v);}		// restrict region in [a, b]
template<class T> T lc_clamp(T v, T a, T b){ return (v<a)? a:((v>b)? b:v);}		// restrict region in [a, b]


enum { LCX_ROT_ZXY = 0, LCX_ROT_YXZ, LCX_ROT_XYZ, LCX_ROT_XZY, LCX_ROT_YZX, LCX_ROT_ZYX, };	// ROTATION ORDER
enum { FIXED_PRECISION	=16, FIXED_ONE = (1<<FIXED_PRECISION), FIXED_ZERO = (0), };			// for fixed point number

LC_INLINE INT LCXIsEqual    (FLOAT a, FLOAT b, FLOAT e=LCX_R_DELTA){ return (lc_abs(1.0F-b/a) < e ? LC_TRUE:LC_FALSE); }	// a must be not zero
LC_INLINE INT LCXIsNotEqual (FLOAT a, FLOAT b, FLOAT e=LCX_R_DELTA){ return (lc_abs(1.0F-b/a) >=e ? LC_TRUE:LC_FALSE); }	// a must be not zero

LC_INLINE QWORD LCXMAKEQWORD(DWORD l,DWORD h){ return (QWORD)( ((QWORD)l) | ((QWORD)h) << 32); }
LC_INLINE DWORD LCXMAKEDWORD(WORD  l,WORD  h){ return (DWORD)( ((DWORD)l) | ((DWORD)h) << 16); }
LC_INLINE WORD  LCXMAKEWORD (BYTE  l,BYTE  h){ return (WORD )( ((WORD)l ) | ((WORD)h ) <<  8); }
LC_INLINE DWORD LCXHIDWORD  (QWORD t)        { return (DWORD)((t>>32)& 0xFFFFFFFF); }
LC_INLINE DWORD LCXLODWORD  (QWORD t)        { return (DWORD)( t )                ; }
LC_INLINE WORD  LCXHIWORD   (DWORD t)        { return (WORD )( (t>>16) & 0xFFFF)  ; }
LC_INLINE WORD  LCXLOWORD   (DWORD t)        { return (WORD )( t )                ; }
LC_INLINE BYTE  LCXHIBYTE   (WORD  t)        { return (BYTE )((t>>8) & 0xFF)      ; }
LC_INLINE BYTE  LCXLOBYTE   (WORD  t)        { return (BYTE )( t )                ; }

LC_INLINE INT LCXQuantum2Power(INT v)        { INT n=1; for(; n<v; n <<= 1); return n; }


// finite, NaN(Not a Number)

FLOAT  LCX_InfinityFloat  ()			;										// return Infinity value: 0x7F800000(FLT_MAX+1)
DOUBLE LCX_InfinityDouble ()			;										// return Infinity value: 0x7FF0000000000000(DBL_MAX+1)
FLOAT  LCX_NaNFloat       ()			;										// return Infinity max value: 0x7FFFFFFF
DOUBLE LCX_NaNDouble      ()			;										// return Infinity max value: 0x7FF0FFFFFFFFFFFF
INT    LCX_IsNaN          (FLOAT  v)	;										// return (0x7F7FFFFF < v || v < 0xFF7FFFFF)
INT    LCX_IsNaN          (DOUBLE v)	;										// return (0x7FEFFFFFFFFFFFFF < v || v < 0xFFEFFFFFFFFFFFFF)
INT    LCX_IsFinite       (FLOAT  v)	;										// return (0x7F7FFFFF >= t && t >= 0xFF7FFFFF)
INT    LCX_IsFinite       (DOUBLE v)	;										// return (0x7FEFFFFFFFFFFFFF >= v && v >= 0xFFEFFFFFFFFFFFFF)


// using math table functions.

FLOAT LCXMathCos      (FLOAT Radian)	;										// sin value from sine table
FLOAT LCXMathSin      (FLOAT Radian)	;										// cos value from cosine table
FLOAT LCXMathTan      (FLOAT Radian)	;										// tangent value value from LCX_Sin/LCX_Cos
FLOAT LCXMathAcos     (FLOAT v)			;										// acos value from arccosine table
FLOAT LCXMathAsin     (FLOAT v)			;										// asin value from arcsine table
FLOAT LCXMathAtan2    (FLOAT y, FLOAT x);										// it uses atan2 function.




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// 32-bit fixed point number

struct FIXED32
{
	INT _;

	FIXED32();
	FIXED32(const char  &);
	FIXED32(const SHORT &);
	FIXED32(const INT   &);
	FIXED32(const FLOAT &);
	FIXED32(const DOUBLE&);
	FIXED32(const LONG  &);
	FIXED32(const DINT  &);

	FIXED32 operator =(const char  &);
	FIXED32 operator =(const SHORT &);
	FIXED32 operator =(const INT   &);
	FIXED32 operator =(const FLOAT &);
	FIXED32 operator =(const DOUBLE&);
	FIXED32 operator =(const LONG  &);
	FIXED32 operator =(const DINT  &);

	operator char   () const;
	operator SHORT  () const;
	operator INT    () const;
	operator FLOAT  () const;
	operator DOUBLE () const;
	operator LONG   () const;
	operator DINT   () const;

	// unary operators
	FIXED32 operator +() const;
	FIXED32 operator -() const;

	// assignment operators
	FIXED32& operator+= (const FIXED32& v);
	FIXED32& operator-= (const FIXED32& v);
	FIXED32& operator*= (const FIXED32& v);
	FIXED32& operator/= (const FIXED32& v);

	// binary operators
	FIXED32 operator +(const FIXED32& v) const;
	FIXED32 operator -(const FIXED32& v) const;
	FIXED32 operator *(const FIXED32& v) const;
	FIXED32 operator /(const FIXED32& v) const;
	friend FIXED32 operator +(const FIXED32& v1, const FIXED32& v2);
	friend FIXED32 operator -(const FIXED32& v1, const FIXED32& v2);
	friend FIXED32 operator *(const FIXED32& v1, const FIXED32& v2);
	friend FIXED32 operator /(const FIXED32& v1, const FIXED32& v2);
	static FLOAT FloatCut(FLOAT v);												// cut off the below decimal point. return (FLOAT)(INT(v*65536.0F)>>FIXED_PRECISION);
};



//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Short Int type vector

// vector2 x=0, y=0
struct LCXVEC2s : public LC_SHORT2
{
	LCXVEC2s();
	LCXVEC2s(const LCXVEC2s&);
	LCXVEC2s(const SHORT*);
	LCXVEC2s(const LCXVEC2s*);
	LCXVEC2s(SHORT,SHORT);
	LCXVEC2s(const LC_SHORT2&);

	// casting
	operator SHORT*();
	operator const SHORT*() const;
	SHORT& operator[](int n);

	// assignment operators
	LCXVEC2s& operator +=(const LCXVEC2s&);
	LCXVEC2s& operator -=(const LCXVEC2s&);
	LCXVEC2s& operator *=(SHORT)	;
	LCXVEC2s& operator /=(SHORT)	;

	// unary operators
	LCXVEC2s operator +() const		;
	LCXVEC2s operator -() const		;

	// binary operators
	LCXVEC2s operator +(const LCXVEC2s&) const;
	LCXVEC2s operator -(const LCXVEC2s&) const;
	LCXVEC2s operator *(SHORT) const	;
	LCXVEC2s operator /(SHORT) const	;
	friend LCXVEC2s operator *(SHORT, const LCXVEC2s&);

	INT operator ==(const LCXVEC2s&) const;
	INT operator !=(const LCXVEC2s&) const;
};


// short3 x=0, y=0, z=0
// pack 2byte
#if defined(_MSC_VER)
  #pragma pack(push, 1)
#endif

struct LCXVEC3s : public LC_SHORT3
{
	LCXVEC3s();
	LCXVEC3s(const LCXVEC3s&);
	LCXVEC3s(const SHORT*);
	LCXVEC3s(const LCXVEC3s*);
	LCXVEC3s(SHORT,SHORT,SHORT);
	LCXVEC3s(const LC_SHORT3&);

	// casting
	operator SHORT*();
	operator const SHORT*() const;
	SHORT& operator[](int n);

	// assignment operators
	LCXVEC3s& operator +=(const LCXVEC3s&);
	LCXVEC3s& operator -=(const LCXVEC3s&);
	LCXVEC3s& operator *=(SHORT)	;
	LCXVEC3s& operator /=(SHORT)	;

	// unary operators
	LCXVEC3s operator +() const		;
	LCXVEC3s operator -() const		;

	// binary operators
	LCXVEC3s operator +(const LCXVEC3s&) const;
	LCXVEC3s operator -(const LCXVEC3s&) const;
	LCXVEC3s operator *(SHORT) const	;
	LCXVEC3s operator /(SHORT) const	;
	friend LCXVEC3s operator *(SHORT, const LCXVEC3s&);

	INT operator ==(const LCXVEC3s&) const;
	INT operator !=(const LCXVEC3s&) const;
}
#if defined(_MSC_VER)
  #pragma pack(pop)
#else
  __attribute__((packed))
#endif
;


struct LCXCOLOR;

struct LCXCOLORB : public LC_COLORB												// Colors Byte(RGBA). color range [0, 255]. default color r = 255, g = 255, b = 255, a = 255
{
	LCXCOLORB();
	LCXCOLORB(const LCXCOLORB&);
	LCXCOLORB(const BYTE*);
	LCXCOLORB(const FLOAT*);													// float array is rgba and range is [0,1]; r=v[0]*255, g=v[1]*255, b=v[2]*255, a=v[3]*255
	LCXCOLORB(const LCXCOLOR&);
	LCXCOLORB(BYTE R, BYTE G, BYTE B, BYTE A);
	LCXCOLORB(COLOR32 argb);													// Need ARGB 32 bit
	LCXCOLORB(const LC_COLORB&);
	LCXCOLORB(const LC_COLORF*);

	// casting
	operator COLOR32 () const;
	operator BYTE* ();
	operator const BYTE* () const;
	operator LCXCOLOR () const;
	BYTE& operator[](int n);

	// assignment operators
	LCXCOLORB& operator +=(const LCXCOLORB&);
	LCXCOLORB& operator -=(const LCXCOLORB&);
	LCXCOLORB& operator *=(const LCXCOLORB&);
	LCXCOLORB& operator *=(BYTE)	;
	LCXCOLORB& operator /=(BYTE)	;

	// unary operators
	LCXCOLORB operator +() const	;											//
	LCXCOLORB operator -() const	;											//

	// binary operators
	LCXCOLORB operator+ (const LCXCOLORB&) const;
	LCXCOLORB operator- (const LCXCOLORB&) const;
	LCXCOLORB operator* (const LCXCOLORB&) const;
	LCXCOLORB operator* (BYTE) const			;
	LCXCOLORB operator/ (BYTE) const			;
	friend LCXCOLORB operator* (BYTE, const LCXCOLORB&);

	INT operator == (const LCXCOLORB&) const	;
	INT operator != (const LCXCOLORB&) const	;
};


#if defined(_MSC_VER)
  #pragma pack(push, 1)
#endif

struct LCXCOLORB3																// Colors Byte(RGB). color range [0, 255]. default color r = 255, g = 255, b = 255
{
	union{ struct{ BYTE r, g, b; };	BYTE m[3];	};								// caution the byte order

	LCXCOLORB3();
	LCXCOLORB3(BYTE R,BYTE G,BYTE B);

	LCXCOLORB3(const LCXCOLORB&);
	LCXCOLORB3(const BYTE*);
	LCXCOLORB3(const FLOAT*);													// float array is rgba and range is [0,1]; r=v[0]*255, g=v[1]*255, b=v[2]*255
	LCXCOLORB3(const LCXCOLOR&);
	LCXCOLORB3(COLOR32 argb);													// Need ARGB 32 bit( alpha will be ignored.)
	LCXCOLORB3(const LC_COLORB&);
	LCXCOLORB3(const LC_COLORF*);

	// casting
	operator COLOR32 () const;													// alpha will be 0xFF.
	operator BYTE* ();
	operator const BYTE* () const;
	operator LCXCOLORB () const;												// alpha will be 0xFF.
	operator LCXCOLOR () const;													// alpha will be 1.0F
	BYTE& operator[](int n);

	// assignment operators
	LCXCOLORB3& operator +=(const LCXCOLORB3&);
	LCXCOLORB3& operator -=(const LCXCOLORB3&);
	LCXCOLORB3& operator *=(const LCXCOLORB3&);
	LCXCOLORB3& operator *=(BYTE)	;
	LCXCOLORB3& operator /=(BYTE)	;

	// unary operators
	LCXCOLORB3 operator +() const	;
	LCXCOLORB3 operator -() const	;

	// binary operators
	LCXCOLORB3 operator+ (const LCXCOLORB3&) const;
	LCXCOLORB3 operator- (const LCXCOLORB3&) const;
	LCXCOLORB3 operator* (const LCXCOLORB3&) const;
	LCXCOLORB3 operator* (BYTE) const			;
	LCXCOLORB3 operator/ (BYTE) const			;
	friend LCXCOLORB3 operator* (BYTE, const LCXCOLORB3&);

	INT operator == (const LCXCOLORB3&) const	;
	INT operator != (const LCXCOLORB3&) const	;
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

// for UNSIGNED_SHORT_4_4_4_4(RGBA): R-0xF000 G-0x0F00 B-0x00F0 A-0x000F
struct LCXCOLORW4
{
	union { struct { BYTE a:4; BYTE b:4; BYTE g:4; BYTE r:4; }; COLOR16 d; };

	LCXCOLORW4();
	LCXCOLORW4(INT R, INT G, INT B, INT A);
	LCXCOLORW4(COLOR16 rgba);
	LCXCOLORW4(COLOR32 argb);
	LCXCOLORW4(const LCXCOLORB& v);

	// casting
	operator COLOR16  () const;
	operator COLOR32  () const;
	operator LCXCOLORB() const;
	operator LCXCOLOR () const;

	void R(INT _r);
	void G(INT _g);
	void B(INT _b);
	void A(INT _a);
	void ARGB(COLOR16 argb);													// setup from argb color
	void RGBA(COLOR16 rgba);													// setup from rgba color

	BYTE R();
	BYTE G();
	BYTE B();
	BYTE A();
}
#if defined(_MSC_VER)
  #pragma pack(pop)
#else
  __attribute__((packed))
#endif
;




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// INT type vector

// vector2 x=0, y=0
struct LCXVEC2i : public LC_INT2
{
	LCXVEC2i();
	LCXVEC2i(const LCXVEC2i&);
	LCXVEC2i(const INT*);
	LCXVEC2i(const LCXVEC2i*);
	LCXVEC2i(INT,INT);
	LCXVEC2i(FLOAT,FLOAT);
	LCXVEC2i(const FLOAT*);
	LCXVEC2i(const LC_INT2&);

	// casting
	operator INT*();
	operator const INT*() const;
	INT& operator[](int n);
	const LCXVEC2i& operator=(const LCXVEC2i&);

	// assignment operators
	LCXVEC2i& operator +=(const LCXVEC2i&);
	LCXVEC2i& operator -=(const LCXVEC2i&);
	LCXVEC2i& operator *=(INT)	;
	LCXVEC2i& operator /=(INT)	;

	// unary operators
	LCXVEC2i operator +() const	;
	LCXVEC2i operator -() const	;

	// binary operators
	LCXVEC2i operator +(const LCXVEC2i&) const;
	LCXVEC2i operator -(const LCXVEC2i&) const;
	LCXVEC2i operator *(INT) const;
	LCXVEC2i operator /(INT) const;
	friend LCXVEC2i operator* (INT, const LCXVEC2i&);

	INT operator ==(const LCXVEC2i&) const;
	INT operator !=(const LCXVEC2i&) const;
};

// vector3 x=0, y=0, z=0
struct LCXVEC3i : public LC_INT3
{
	LCXVEC3i();
	LCXVEC3i(const LCXVEC3i&);
	LCXVEC3i(const INT*);
	LCXVEC3i(const LCXVEC3i*);
	LCXVEC3i(INT,INT,INT);
	LCXVEC3i(FLOAT,FLOAT,FLOAT);
	LCXVEC3i(const FLOAT*);
	LCXVEC3i(const LC_INT3&);
	LCXVEC3i(const LCXVEC2i& v, INT _z);

	// casting
	operator INT*();
	operator const INT*() const;
	INT& operator[](int n);
	const LCXVEC3i& operator=(const LCXVEC3i&);

	// assignment operators
	LCXVEC3i& operator +=(const LCXVEC3i&);
	LCXVEC3i& operator -=(const LCXVEC3i&);
	LCXVEC3i& operator *=(INT)	;
	LCXVEC3i& operator /=(INT)	;

	// unary operators
	LCXVEC3i operator +() const	;
	LCXVEC3i operator -() const	;

	// binary operators
	LCXVEC3i operator +(const LCXVEC3i&) const;
	LCXVEC3i operator -(const LCXVEC3i&) const;
	LCXVEC3i operator *(INT) const		;
	LCXVEC3i operator /(INT) const		;
	friend LCXVEC3i operator*(INT, const LCXVEC3i&);

	INT operator==(const LCXVEC3i&) const;
	INT operator!=(const LCXVEC3i&) const;
};


// vector4 x=0, y=0, z=0, w=0
struct LCXVEC4i : public LC_INT4
{
	LCXVEC4i();
	LCXVEC4i(const LCXVEC4i& r);
	LCXVEC4i(const INT*);
	LCXVEC4i(const LCXVEC4i*);
	LCXVEC4i(INT,INT,INT,INT);
	LCXVEC4i(FLOAT,FLOAT,FLOAT,FLOAT);
	LCXVEC4i(const LC_INT4&);
	LCXVEC4i(const LCXVEC3i&, INT _w);

	// casting
	operator INT*();
	operator const INT*() const;
	INT& operator[](int n);
	const LCXVEC4i& operator=(const LCXVEC4i&);

	// assignment operators
	LCXVEC4i& operator +=(const LCXVEC4i&);
	LCXVEC4i& operator -=(const LCXVEC4i&);
	LCXVEC4i& operator *=(INT)	;
	LCXVEC4i& operator /=(INT)	;

	// unary operators
	LCXVEC4i operator +() const	;
	LCXVEC4i operator -() const	;

	// binary operators
	LCXVEC4i operator +(const LCXVEC4i&) const;
	LCXVEC4i operator -(const LCXVEC4i&) const;
	LCXVEC4i operator *(INT) const	;
	LCXVEC4i operator /(INT) const	;
	friend LCXVEC4i operator*(INT, const LCXVEC4i&);

	INT operator==(const LCXVEC4i& v) const;
	INT operator!=(const LCXVEC4i& v) const;
};




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// FLOAT type vector

struct LCXVECTOR2;
struct LCXVECTOR3;
struct LCXVECTOR4;
struct LCXMATRIX;
struct LCXMATRIX4X3;
struct LCXMATRIX3X3;
struct LCXMATRIX3X2;

// vector2 x=0, y=0
struct LCXVECTOR2 : public LC_FLOAT2
{
	LCXVECTOR2();
	LCXVECTOR2(const LCXVECTOR2&);
	LCXVECTOR2(const FLOAT*);
	LCXVECTOR2(const LCXVECTOR2*);
	LCXVECTOR2(FLOAT,FLOAT);
	LCXVECTOR2(const LC_FLOAT2&);

	// casting
	operator FLOAT*();
	operator const FLOAT*() const;
	FLOAT& operator[](int n);

	// assignment operators
	LCXVECTOR2& operator +=(const LCXVECTOR2&);
	LCXVECTOR2& operator -=(const LCXVECTOR2&);
	LCXVECTOR2& operator *=(FLOAT);
	LCXVECTOR2& operator /=(FLOAT);
	LCXVECTOR2& operator  =(const LCXVECTOR3& v);

	// unary operators
	LCXVECTOR2 operator +() const;
	LCXVECTOR2 operator -() const;

	// binary operators
	LCXVECTOR2 operator +(const LCXVECTOR2&) const;
	LCXVECTOR2 operator -(const LCXVECTOR2&) const;
	LCXVECTOR2 operator *(FLOAT) const;
	LCXVECTOR2 operator /(FLOAT) const;
	friend LCXVECTOR2 operator *(FLOAT, const LCXVECTOR2&);

	INT operator ==(const LCXVECTOR2&) const;
	INT operator !=(const LCXVECTOR2&) const;

	// Dot Product
	FLOAT operator *(const LCXVECTOR2&);
	friend FLOAT operator *(const LCXVECTOR2&, const LCXVECTOR2&);

	// Cross Product(Z-Value)
	FLOAT operator ^(const LCXVECTOR2&);
	friend FLOAT operator ^(const LCXVECTOR2&, const LCXVECTOR2&);

	// Transform: vector * Matrix3X3
	LCXVECTOR2 operator *(const LCXMATRIX3X3&);
	// Transform: Matrix3X3 * vector;
	friend LCXVECTOR2 operator *(const LCXMATRIX3X3&, const LCXVECTOR2&);

	FLOAT	 	Length();														// Length
	FLOAT		LengthSq();														// Length Square
	LCXVECTOR2	Normalize();													// Magnitude = 1
	LCXVECTOR2	Normalize(const LCXVECTOR2*);									// Copy and Normalize
	FLOAT		Cross(const LCXVECTOR2*, const LCXVECTOR2*);					// this = (A x B).z
	LCXVECTOR2& Negative();														// x= -x, y= -y
	LCXVECTOR2& Lerp(const LCXVECTOR2* v1, const LCXVECTOR2* v2, FLOAT t);		// this = (1-t)*v1 + t* v2
	LCXVECTOR2&	Multiple(const LCXVECTOR2& v);									// x*=r.x, y*=r.y, return *this;

	LCXVECTOR2& Zero ();
	LCXVECTOR2& One  ();
	LCXVECTOR2& AxisX();
	LCXVECTOR2& AxisY();
};


// vector3 x=0, y=0, z=0
struct LCXVECTOR3 : public LC_FLOAT3
{
	LCXVECTOR3();
	LCXVECTOR3(const LCXVECTOR3&);
	LCXVECTOR3(const FLOAT*);
	LCXVECTOR3(const LCXVECTOR3*);
	LCXVECTOR3(FLOAT,FLOAT,FLOAT);
	LCXVECTOR3(const LC_FLOAT3&);
	LCXVECTOR3(const LCXVECTOR2&, FLOAT _z);

	// casting
	operator FLOAT*();
	operator const FLOAT*() const;
	FLOAT& operator[](int n);

	// assignment operators
	LCXVECTOR3& operator +=(const LCXVECTOR3&);
	LCXVECTOR3& operator -=(const LCXVECTOR3&);
	LCXVECTOR3& operator *=(FLOAT);
	LCXVECTOR3& operator /=(FLOAT);

	LCXVECTOR3& operator +=(const LCXVECTOR4&);									// vec3 += vec3 + vec4.xyz
	LCXVECTOR3& operator -=(const LCXVECTOR4&);									// vec3 += vec3 + vec4.xyz

	// unary operators
	LCXVECTOR3 operator +() const;
	LCXVECTOR3 operator -() const;

	// binary operators
	LCXVECTOR3 operator +(const LCXVECTOR3&) const;
	LCXVECTOR3 operator -(const LCXVECTOR3&) const;
	LCXVECTOR3 operator *(FLOAT) const;
	LCXVECTOR3 operator /(FLOAT) const;
	friend LCXVECTOR3 operator *(FLOAT, const LCXVECTOR3&);

	INT operator ==(const LCXVECTOR3&) const;
	INT operator !=(const LCXVECTOR3&) const;

	// Dot Product
	FLOAT operator *(const LCXVECTOR3&);
	friend FLOAT operator *(const LCXVECTOR3&, const LCXVECTOR3&);

	// Cross Product
	LCXVECTOR3 operator ^(const LCXVECTOR3&);
	friend LCXVECTOR3 operator ^(const LCXVECTOR3&, const LCXVECTOR3&);

	// Transform: vector * Matrix4x4
	LCXVECTOR3 operator *(const LCXMATRIX&);

	// Transform: Matrix4x4 * vector;
	friend LCXVECTOR3 operator *(const LCXMATRIX&, const LCXVECTOR3&);

	FLOAT       Length();														// Length
	FLOAT       LengthSq();														// Length Square
	LCXVECTOR3	Normalize();													// Magnitude = 1
	LCXVECTOR3	Normalize(const LCXVECTOR3*);									// Copy and Normalize
	LCXVECTOR3	Cross(const LCXVECTOR3*, const LCXVECTOR3*);					// this = A x B
	LCXVECTOR3& Negative();														// x= -x, y= -y, z= -z
	LCXVECTOR3& Lerp(const LCXVECTOR3* v1, const LCXVECTOR3* v2, FLOAT t);		// this = (1-t)*v1 + t* v2
	LCXVECTOR3&	Multiple(const LCXVECTOR3& v);									// x*=r.x, y*=r.y, z*=r.z, return *this;

	LCXVECTOR3& Zero ();
	LCXVECTOR3& One  ();
	LCXVECTOR3& AxisX();
	LCXVECTOR3& AxisY();
	LCXVECTOR3& AxisZ();
};


// vector4 x=0, y=0, z=0, w=0
struct LCXVECTOR4 : public LC_FLOAT4
{
	LCXVECTOR4();
	LCXVECTOR4(const LCXVECTOR4&);
	LCXVECTOR4(const FLOAT*);
	LCXVECTOR4(const LCXVECTOR4*);
	LCXVECTOR4(FLOAT,FLOAT,FLOAT,FLOAT);
	LCXVECTOR4(const LC_FLOAT4& v);
	LCXVECTOR4(const LCXVECTOR3&, FLOAT _w);

	// casting
	operator FLOAT*();
	operator const FLOAT*() const;
	FLOAT& operator[](int n);

	// assignment operators
	LCXVECTOR4& operator +=(const LCXVECTOR4&);
	LCXVECTOR4& operator -=(const LCXVECTOR4&);
	LCXVECTOR4& operator *=(FLOAT v);
	LCXVECTOR4& operator /=(FLOAT v);

	// unary operators
	LCXVECTOR4 operator +() const;
	LCXVECTOR4 operator -() const;

	// binary operators
	LCXVECTOR4 operator +(const LCXVECTOR4&) const;
	LCXVECTOR4 operator -(const LCXVECTOR4&) const;
	LCXVECTOR4 operator *(FLOAT) const;
	LCXVECTOR4 operator /(FLOAT) const;
	friend LCXVECTOR4 operator *(FLOAT, const LCXVECTOR4&);

	INT operator ==(const LCXVECTOR4&) const;
	INT operator !=(const LCXVECTOR4&) const;

	// Dot Product
	FLOAT operator *(const LCXVECTOR4&);
	friend FLOAT operator *(const LCXVECTOR4&, const LCXVECTOR4&);

	// Transform: vector * Matrix4x4
	LCXVECTOR4 operator *(const LCXMATRIX&);

	// Transform: Matrix4x4 * vector;
	friend LCXVECTOR4 operator *(const LCXMATRIX&, const LCXVECTOR4&);

	FLOAT       Length();														// Length
	FLOAT       LengthSq();														// Length Square
	LCXVECTOR4	Normalize();													// Magnitude = 1
	LCXVECTOR4	Normalize(const LCXVECTOR4*);									// Copy and Normalize
	LCXVECTOR4& Negative();														// x= -x, y = -y, z = -z, w = -w
	LCXVECTOR4& Lerp(const LCXVECTOR4* v1, const LCXVECTOR4* v2, FLOAT t);		// this = (1-t)*v1 + t* v2
	LCXVECTOR4&	Multiple(const LCXVECTOR4& v);									// x*=r.x, y*=r.y, z*=r.z, w*=r.w, return *this;

	LCXVECTOR4& Zero();
	LCXVECTOR4& One ();
};




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Matrix4x4 ==> Identity Matrix

struct LCXMATRIX : public LC_MATRIX
{
	LCXMATRIX();
	LCXMATRIX(const LCXMATRIX&);
	LCXMATRIX(const FLOAT*);
	LCXMATRIX(const LCXMATRIX*);
	LCXMATRIX(	FLOAT _11,FLOAT _12,FLOAT _13,FLOAT _14,
				FLOAT _21,FLOAT _22,FLOAT _23,FLOAT _24,
				FLOAT _31,FLOAT _32,FLOAT _33,FLOAT _34,
				FLOAT _41,FLOAT _42,FLOAT _43,FLOAT _44 );

	LCXMATRIX(const LC_MATRIX&);

	// access grants
	FLOAT& operator () ( int iRow, int iCol );
	FLOAT  operator () ( int iRow, int iCol ) const;

	// casting operators
	operator FLOAT* ();
	operator const FLOAT* () const;
	FLOAT& operator[](int n);

	// assignment operators
	LCXMATRIX& operator *=(const LCXMATRIX&);
	LCXMATRIX& operator +=(const LCXMATRIX&);
	LCXMATRIX& operator -=(const LCXMATRIX&);
	LCXMATRIX& operator *=(FLOAT);
	LCXMATRIX& operator /=(FLOAT);

	// unary operators
	LCXMATRIX operator +() const;
	LCXMATRIX operator -() const;

	LCXMATRIX operator *(const LCXMATRIX&) const;
	LCXMATRIX operator +(const LCXMATRIX&) const;
	LCXMATRIX operator -(const LCXMATRIX&) const;
	LCXMATRIX operator *(FLOAT) const;
	LCXMATRIX operator /(FLOAT) const;

	// const * Matrix
	friend LCXMATRIX  operator *(FLOAT, const LCXMATRIX&);						// number * matrix
	friend LCXMATRIX  operator *(const LCXMATRIX&, FLOAT);						// matrix * number
	friend LCXVECTOR4 operator *(LCXVECTOR4&, const LCXMATRIX&);				// vector4 * matrix
	friend LCXVECTOR4 operator *(const LCXMATRIX&, LCXVECTOR4&);				// matrix * vector4
	friend LCXVECTOR3 operator *(LCXVECTOR3&, const LCXMATRIX&);				// vector3 * matrix. return vector is x, y, z, w => x/w, y/w, z/w
	friend LCXVECTOR3 operator *(const LCXMATRIX&, LCXVECTOR3&);				// matrix * vector3

	INT operator ==(const LCXMATRIX&) const;
	INT operator !=(const LCXMATRIX&) const;

	// basic operation
	LCXMATRIX&	Identity();														// Identity (1,0,0,0,  0,1,0,0,  0,0,1,0,  0,0,0,1)
	LCXMATRIX&	Zero();															// Identity (0,0,0,0,  0,0,0,0,  0,0,0,0,  0,0,0,1)
	LCXMATRIX&	Transpose();													// Transpose: M[i,j] -> M[j,i]
	LCXMATRIX&	Transpose(const LCXMATRIX*);
	LCXMATRIX&	Inverse(FLOAT* det, INT bQuick=LC_TRUE);						// if the 'bQuick' is not false then this function will be calculating the inverse matrix  except _14=0, _24=0, _34=0, _44=1
	LCXMATRIX&	Inverse(FLOAT* det, const LCXMATRIX* In, INT bQuick=LC_TRUE);	//
	FLOAT       Determinant() const;											//

	// scaling Matrix
	LCXMATRIX&	Scaling(FLOAT X, FLOAT Y, FLOAT Z);
	LCXMATRIX&	Scaling(const LCXVECTOR3* vScl);

	// Viewing Matrix
	LCXMATRIX&	ViewD3dLH(const LCXVECTOR3* Eye, const LCXVECTOR3* LookAt, const LCXVECTOR3* Up);	// D3D LH
	LCXMATRIX&	ViewD3dRH(const LCXVECTOR3* Eye, const LCXVECTOR3* LookAt, const LCXVECTOR3* Up);	// D3D RH
	LCXMATRIX&	ViewGl   (const LCXVECTOR3* Eye, const LCXVECTOR3* LookAt, const LCXVECTOR3* Up);	// OpenGL RH it's same to ViewD3dRH.  It likes 3D Max system. If you use this function, you have to change x and z and upvector will be (0,0,1). see ex1 projection sample.	// If you want to use this function like a 3DMAX, you have to change x and z and upvector will be (0,0,1). see ex1 projection sample.

	// Projection Matrix
	LCXMATRIX&	PerspectiveD3dLH(FLOAT FOV, FLOAT Aspect, FLOAT fNear, FLOAT fFar);					// Direct3D Perspective Left Handle Rule Matrix x and y: [-1, 1], z: [0, 1]
	LCXMATRIX&	PerspectiveD3dRH(FLOAT FOV, FLOAT Aspect, FLOAT fNear, FLOAT fFar);					// Direct3D Perspective Light Handle Rule Matrix
	LCXMATRIX&	PerspectiveGl   (FLOAT FOV, FLOAT Aspect, FLOAT fNear, FLOAT fFar);					// OpenGL Perspective Matrix. It's same to glFrustum
	LCXMATRIX&	OrthoGl(FLOAT Left, FLOAT Right, FLOAT Bottom, FLOAT Top, FLOAT fNear, FLOAT fFar);	// OpenGL Orthogonal Matrix.  It's same to glOrtho and LCXMatrixOrthoOffCenterRH

	// Rotation Matrix
	LCXMATRIX&	RotationX(FLOAT fRad);
	LCXMATRIX&	RotationY(FLOAT fRad);
	LCXMATRIX&	RotationZ(FLOAT fRad);
	LCXMATRIX&	RotationZXY(FLOAT r_x, FLOAT r_y, FLOAT r_z);					// rotation matrix = rot_matrixZ(r_z) * rot_matrixX(r_x) * rot_matrixY(r_y)
	LCXMATRIX&	RotationYXZ(FLOAT r_x, FLOAT r_y, FLOAT r_z);					// rotation matrix = rot_matrixZ(r_y) * rot_matrixX(r_x) * rot_matrixY(r_z)

	LCXMATRIX&	RotationXYZ(FLOAT r_x, FLOAT r_y, FLOAT r_z);					// matrix = rot(x) * rot(y) * rot(z)
	LCXMATRIX&	RotationXZY(FLOAT r_x, FLOAT r_y, FLOAT r_z);					// matrix = rot(x) * rot(z) * rot(y)
	LCXMATRIX&	RotationYZX(FLOAT r_x, FLOAT r_y, FLOAT r_z);					// matrix = rot(y) * rot(z) * rot(x)
	LCXMATRIX&	RotationZYX(FLOAT r_x, FLOAT r_y, FLOAT r_z);					// matrix = rot(z) * rot(y) * rot(x)
	LCXMATRIX&	RotationYawPitchRoll(FLOAT r_y, FLOAT r_x, FLOAT r_z);			// matrix = rot(y) * rot(z) * rot(x)

	LCXMATRIX&	RotationAxis(FLOAT x, FLOAT y, FLOAT z, FLOAT fRad);			// x, y, z is axis
	LCXMATRIX&	RotationAxis(const LCXVECTOR3* vAxis, FLOAT fRad);
	LCXMATRIX&	RotationAxis(const LCXVECTOR4* vAxis);							// vAxis.w is radian
	LCXMATRIX&	Translation(FLOAT x,FLOAT y,FLOAT z,INT bIdentity=LC_TRUE);
	LCXMATRIX&	Translation(const LCXVECTOR3* vTrs, INT bIdentity=LC_TRUE);

	// setup from 4x3, 3x3, 3x2 matrix
	LCXMATRIX&	From4X3(const LCXMATRIX4X3* tm);								// 4x3 matrix must be transform matrix. => _14=_24=_34=0, _44=1
	LCXMATRIX&	From3X3(const LCXMATRIX3X3* tm);								// 3x3 matrix must be transform matrix. => _31=_32=_34=_43=0,         _33= 1, _41=tm->_31. _42=tm->_32, _44=tm->_33
	LCXMATRIX&	From3X2(const LCXMATRIX3X2* tm);								// 3x2 matrix must be transform matrix. => _14=_24=_31=_32=_34=_43=0, _33= 1, _41=tm->_31. _42=tm->_32, _44=1


	// calculating the transform of vector by this matrix.
	void        TransformCoord(LCXVECTOR3* Out, const LCXVECTOR3* In);			// Out = In * M with translation
	void        TransformNormal(LCXVECTOR3* Out, const LCXVECTOR3* In);			// Out = In * M with no translation

	LCXMATRIX&  Negative();														// Mij = - Mij

	// Kinear interpolation between m1 and m2 with weight.
	LCXMATRIX&  Lerp(const LCXMATRIX* m1, const LCXMATRIX* m2, FLOAT t);		// this = (1-t)*v1 + t* v2
	LCXMATRIX&  Lerp(const LCXMATRIX4X3* m1, const LCXMATRIX4X3* m2, FLOAT t);	// this = (1-t)*v1 + t* v2
};

typedef LCXMATRIX LCXMAT4X4;




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Quaternion: x=0, y=0, z=0, w=1
struct LCXQUATERNION : public LC_FLOAT4
{
	LCXQUATERNION();
	LCXQUATERNION(const LCXQUATERNION&);
	LCXQUATERNION(const FLOAT*);
	LCXQUATERNION(const LCXQUATERNION*);
	LCXQUATERNION(FLOAT x,FLOAT y,FLOAT z,FLOAT w);
	LCXQUATERNION(const LC_FLOAT4&);

	// casting
	operator FLOAT* ();
	operator const FLOAT* () const;
	FLOAT& operator[](int n);

	// assignment operators
	LCXQUATERNION& operator +=(const LCXQUATERNION&);
	LCXQUATERNION& operator -=(const LCXQUATERNION&);
	LCXQUATERNION& operator *=(const LCXQUATERNION&);
	LCXQUATERNION& operator *=(FLOAT);
	LCXQUATERNION& operator /=(FLOAT);

	// unary operators
	LCXQUATERNION  operator +() const;
	LCXQUATERNION  operator -() const;

	// binary operators
	LCXQUATERNION operator +(const LCXQUATERNION&) const;
	LCXQUATERNION operator -(const LCXQUATERNION&) const;
	LCXQUATERNION operator *(const LCXQUATERNION&) const;
	LCXQUATERNION operator *(FLOAT) const;
	LCXQUATERNION operator /(FLOAT) const;
	friend LCXQUATERNION operator *(FLOAT,const LCXQUATERNION&);

	INT operator ==(const LCXQUATERNION&) const;
	INT operator !=(const LCXQUATERNION&) const;

	LCXQUATERNION&	Identity();
	LCXQUATERNION&	Conjugate();
	LCXQUATERNION&	Negative();													// x=-x, y=-y, z=-z, w=-w

	void SLerp(const LCXQUATERNION* q1, const LCXQUATERNION* q2, FLOAT t);		//Q = (1/sinθ)[  sin (θ*(1-t)) * Q1 + sin (θ*t) * Q2]
	void RotationMatrix(LCXMATRIX* Out, INT bLHR = LC_TRUE);					// LHR = Left Hand Rule. ex)Direct3D
};




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Colors r=1.0F, g=1.0F, b=1.0F, a=1.0F
struct LCXCOLOR : LC_COLORF
{
	LCXCOLOR();
	LCXCOLOR(const LCXCOLOR&);
	LCXCOLOR(const FLOAT *);
	LCXCOLOR(const LCXCOLOR*);
	LCXCOLOR(COLOR32 argb);
	LCXCOLOR(const BYTE* rgba/*r[0],g[1],b[2],a[3]*/);
	LCXCOLOR(FLOAT r,FLOAT g,FLOAT b,FLOAT a);
	LCXCOLOR(const LC_COLORF&);

	// casting
	operator COLOR32 () const;
	operator FLOAT* ();
	operator const FLOAT* () const;
	FLOAT& operator[](int n);

	// assignment operators
	LCXCOLOR& operator +=(const LCXCOLOR&);
	LCXCOLOR& operator -=(const LCXCOLOR&);
	LCXCOLOR& operator *=(const LCXCOLOR&);										// r *= rhs.r, g *= rhs.g, b *= rhs.b, a *= rhs.a
	LCXCOLOR& operator *=(FLOAT);
	LCXCOLOR& operator /=(FLOAT);

	// unary operators
	LCXCOLOR operator +() const;
	LCXCOLOR operator -() const;												// Negative: return LCXCOLOR(1.F-r, 1.F-g, 1.F-b, a)

	// binary operators
	LCXCOLOR operator +(const LCXCOLOR&) const;									// Add
	LCXCOLOR operator -(const LCXCOLOR&) const;									// Substract
	LCXCOLOR operator *(const LCXCOLOR&) const;									// Modulate: LCXCOLOR(r+rhs.r, g+rhs.g, b+rhs.b, a+rhs.a)
	LCXCOLOR operator *(FLOAT) const;											// Modulate
	LCXCOLOR operator /(FLOAT) const;											// Devide
	friend LCXCOLOR operator *(FLOAT,const LCXCOLOR&);							// Scaling

	INT operator == (const LCXCOLOR&) const;
	INT operator != (const LCXCOLOR&) const;

	LCXCOLOR& Negative();														// r= 1.F-r, g = 1.F-g, b=1.F-b, a=a
	LCXCOLOR& Lerp(const LCXCOLOR* v1, const LCXCOLOR* v2, FLOAT t);			// this = (1-t)*v1 + t* v2
};




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Plane (3D)
struct LCXPLANE : public LC_FLOAT4
{
	LCXPLANE();
	LCXPLANE(const LCXPLANE&);
	LCXPLANE(const LCXVECTOR3&, const LCXVECTOR3&, const LCXVECTOR3&);			// Like setup from points
	LCXPLANE(const FLOAT*);
	LCXPLANE(FLOAT a,FLOAT b,FLOAT c,FLOAT d);

	// casting
	operator FLOAT* ();
	operator const FLOAT* () const;
	FLOAT& operator[](int n);

	// unary operators
	LCXPLANE operator + () const;
	LCXPLANE operator - () const;

	// binary operators
	INT operator == ( const LCXPLANE& ) const;
	INT operator != ( const LCXPLANE& ) const;

	void FromPointNormal(const LCXVECTOR3* point, const LCXVECTOR3* normal);
	void FromPoints(const LCXVECTOR3* p0, const LCXVECTOR3* p1, const LCXVECTOR3* p2);
};

// Plane 2D(z=0)
struct LCXPLANE2
{
	union {	struct { FLOAT a; FLOAT b; FLOAT d; }; FLOAT m[3]; };

	LCXPLANE2();
	LCXPLANE2(const LCXPLANE2&);
	LCXPLANE2(const LCXVECTOR2&, const LCXVECTOR2&);
	LCXPLANE2(const FLOAT*);
	LCXPLANE2(FLOAT a,FLOAT b,FLOAT d);

	// casting
	operator FLOAT* ();
	operator const FLOAT* () const;
	FLOAT& operator[](int n);

	// unary operators
	LCXPLANE2 operator + () const;
	LCXPLANE2 operator - () const;

	// binary operators
	INT operator == ( const LCXPLANE2& ) const;
	INT operator != ( const LCXPLANE2& ) const;

	void PointNormal(const LCXVECTOR2* p, const LCXVECTOR2* n);					// setup from point and normal vector. z value of all vectors is 0
	void Points(const LCXVECTOR2* p0, const LCXVECTOR2* p1);					// setup from 3 points. N = (p1-p0) X Z(0,0,1)
};




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// 4X3 Matrix

struct LCXMATRIX4X3 : public LC_MATRIX4X3
{
	LCXMATRIX4X3();
	LCXMATRIX4X3(const LCXMATRIX4X3&);
	LCXMATRIX4X3(const FLOAT*);
	LCXMATRIX4X3(const LCXMATRIX4X3*);
	LCXMATRIX4X3(const LCXVECTOR3*);
	LCXMATRIX4X3(const LCXMATRIX&);
	LCXMATRIX4X3(const LCXMATRIX*);

	LCXMATRIX4X3(
				FLOAT _11,FLOAT _12,FLOAT _13,
				FLOAT _21,FLOAT _22,FLOAT _23,
				FLOAT _31,FLOAT _32,FLOAT _33,
				FLOAT _41,FLOAT _42,FLOAT _43 );

	LCXMATRIX4X3(const LC_MATRIX&);

	// access grants
	FLOAT& operator () ( int iRow, int iCol );
	FLOAT  operator () ( int iRow, int iCol ) const;

	// casting operators
	operator FLOAT* ();
	operator const FLOAT* () const;
	FLOAT& operator[](int n);

	// assignment operators
	LCXMATRIX4X3& operator +=(const LCXMATRIX4X3&);
	LCXMATRIX4X3& operator -=(const LCXMATRIX4X3&);
	LCXMATRIX4X3& operator *=(FLOAT);
	LCXMATRIX4X3& operator /=(FLOAT);

	// unary operators
	LCXMATRIX4X3 operator +() const;
	LCXMATRIX4X3 operator -() const;

	// binary operators
	LCXMATRIX4X3 operator +(const LCXMATRIX4X3&) const;
	LCXMATRIX4X3 operator -(const LCXMATRIX4X3&) const;
	LCXMATRIX4X3 operator *(FLOAT) const;
	LCXMATRIX4X3 operator /(FLOAT) const;

	// const * Matrix
	friend LCXMATRIX4X3 operator *(FLOAT, const LCXMATRIX4X3&);
	friend LCXMATRIX4X3 operator *(const LCXMATRIX4X3&, FLOAT);

	// const * Matrix
	friend LCXMATRIX  operator *(FLOAT, const LCXMATRIX&);						// number * matrix
	friend LCXMATRIX  operator *(const LCXMATRIX&, FLOAT);						// matrix * number
	friend LCXVECTOR4 operator *(LCXVECTOR4&, const LCXMATRIX&);				// vector4 * matrix
	friend LCXVECTOR4 operator *(const LCXMATRIX&, LCXVECTOR4&);				// matrix * vector4
	friend LCXVECTOR3 operator *(LCXVECTOR3&, const LCXMATRIX&);				// vector3 * matrix. return vector is x, y, z, w => x/w, y/w, z/w
	friend LCXVECTOR3 operator *(const LCXMATRIX&, LCXVECTOR3&);				// matrix * vector3


	INT operator ==(const LCXMATRIX4X3&) const;
	INT operator !=(const LCXMATRIX4X3&) const;

	LCXMATRIX4X3& Identity();
	LCXMATRIX4X3& Matrix4x4(const LCXMATRIX*);
	void          TransformCoord(LCXVECTOR3* Out, const LCXVECTOR3* In);
	void          TransformNormal(LCXVECTOR3* Out, const LCXVECTOR3* In);		// Out = In * M with no translation

	LCXMATRIX4X3& Negative();													// Mij = - Mij
	LCXMATRIX4X3& Lerp(const LCXMATRIX4X3* v1,const LCXMATRIX4X3* v2, FLOAT t);	// this = (1-t)*v1 + t* v2
};

typedef LCXMATRIX4X3 LCXMAT4X3;




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// 3X3 Matrix

struct LCXMATRIX3X3 : public LC_MATRIX3X3
{
	LCXMATRIX3X3();
	LCXMATRIX3X3(const LCXMATRIX3X3&);
	LCXMATRIX3X3(const FLOAT*);
	LCXMATRIX3X3(const LCXMATRIX3X3*);
	LCXMATRIX3X3(
				FLOAT _11,FLOAT _12,FLOAT _13,
				FLOAT _21,FLOAT _22,FLOAT _23,
				FLOAT _31,FLOAT _32,FLOAT _33  );

	LCXMATRIX3X3(const LCXMATRIX&);

	// access grants
	FLOAT& operator () ( int iRow, int iCol );
	FLOAT  operator () ( int iRow, int iCol ) const;

	// casting operators
	operator FLOAT* ();
	operator const FLOAT* () const;
	FLOAT& operator[](int n);

	// assignment operators
	LCXMATRIX3X3& operator *=(const LCXMATRIX3X3&);
	LCXMATRIX3X3& operator +=(const LCXMATRIX3X3&);
	LCXMATRIX3X3& operator -=(const LCXMATRIX3X3&);
	LCXMATRIX3X3& operator *=(FLOAT);
	LCXMATRIX3X3& operator /=(FLOAT);

	// unary operators
	LCXMATRIX3X3 operator +() const;
	LCXMATRIX3X3 operator -() const;

	LCXMATRIX3X3 operator *(const LCXMATRIX3X3&) const;
	LCXMATRIX3X3 operator +(const LCXMATRIX3X3&) const;
	LCXMATRIX3X3 operator -(const LCXMATRIX3X3&) const;
	LCXMATRIX3X3 operator *(FLOAT) const;
	LCXMATRIX3X3 operator /(FLOAT) const;

	// const * Matrix
	friend LCXMATRIX3X3 operator *(FLOAT, const LCXMATRIX3X3&);
	friend LCXMATRIX3X3 operator *(const LCXMATRIX3X3&, FLOAT);
	friend LCXVECTOR3   operator *(LCXVECTOR3&, const LCXMATRIX3X3&);			// vector3 * matrix
	friend LCXVECTOR3   operator *(const LCXMATRIX3X3&, LCXVECTOR3&);			// matrix * vector3
	friend LCXVECTOR2   operator *(LCXVECTOR2&, const LCXMATRIX3X3&);			// vector2 * matrix. return vector is x, y, z => x/z, y/z
	friend LCXVECTOR2   operator *(const LCXMATRIX3X3&, LCXVECTOR2&);			// matrix * vector2

	INT operator ==(const LCXMATRIX3X3&) const;
	INT operator !=(const LCXMATRIX3X3&) const;

	LCXMATRIX3X3& Identity();
	LCXMATRIX3X3& Transpose();
	LCXMATRIX3X3& Transpose(const LCXMATRIX3X3*);
	LCXMATRIX3X3& Inverse(FLOAT* det);
	LCXMATRIX3X3& Inverse(FLOAT* det, const LCXMATRIX3X3* In);
	FLOAT         Determinant();

	LCXMATRIX3X3& Scaling(FLOAT X, FLOAT Y);
	LCXMATRIX3X3& Scaling(const LCXVECTOR2* vScl);
	LCXMATRIX3X3& Rotation(FLOAT fRad);
	LCXMATRIX3X3& Translation(FLOAT x, FLOAT y, INT bIdentity=LC_TRUE);
	LCXMATRIX3X3& Translation(const LCXVECTOR2* vTrs, INT bIdentity=LC_TRUE);

	void          TransformCoord(LCXVECTOR2* Out, const LCXVECTOR2* In);
	void          TransformNormal(LCXVECTOR2* Out, const LCXVECTOR2* In);		// Out = In * M with no translation

	LCXMATRIX3X3& Negative();													// Mij = - Mij
	LCXMATRIX3X3& Lerp(const LCXMATRIX3X3* v1,const LCXMATRIX3X3* v2, FLOAT t);	// this = (1-t)*v1 + t* v2
};

typedef LCXMATRIX3X3 LCXMAT3X3;




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// 3X2 Matrix
// LCXMATRIX3X2 matrix is the specialized LCXMATRIX3X3(_11, _12, 0,  _21, _22, 0,   _31, _32, 1);
struct LCXMATRIX3X2 : public LC_MATRIX3X2
{
	LCXMATRIX3X2();
	LCXMATRIX3X2(const LCXMATRIX3X2&);
	LCXMATRIX3X2(const FLOAT*);
	LCXMATRIX3X2(const LCXMATRIX3X2*);
	LCXMATRIX3X2(
				FLOAT _11,FLOAT _12,
				FLOAT _21,FLOAT _22,
				FLOAT _31,FLOAT _32  );

	LCXMATRIX3X2(const LCXMATRIX3X3&);

	// access grants
	FLOAT& operator () ( int iRow, int iCol );
	FLOAT  operator () ( int iRow, int iCol ) const;

	// casting operators
	operator FLOAT* ();
	operator const FLOAT* () const;
	FLOAT& operator[](int n);

	// assignment operators
	LCXMATRIX3X2& operator *=(const LCXMATRIX3X2&);								//M[3,2] * M[3,2] is not allowed in matrix but it will be run same to [3,3(0,0,1)] * [3,3(0,0,1)]
	LCXMATRIX3X2& operator +=(const LCXMATRIX3X2&);
	LCXMATRIX3X2& operator -=(const LCXMATRIX3X2&);
	LCXMATRIX3X2& operator *=(FLOAT);
	LCXMATRIX3X2& operator /=(FLOAT);

	// unary operators
	LCXMATRIX3X2 operator +() const;
	LCXMATRIX3X2 operator -() const;

	LCXMATRIX3X2 operator *(const LCXMATRIX3X2&) const;
	LCXMATRIX3X2 operator +(const LCXMATRIX3X2&) const;
	LCXMATRIX3X2 operator -(const LCXMATRIX3X2&) const;
	LCXMATRIX3X2 operator *(FLOAT) const;
	LCXMATRIX3X2 operator /(FLOAT) const;

	// const * Matrix
	friend LCXMATRIX3X2 operator *(FLOAT, const LCXMATRIX3X2&);
	friend LCXMATRIX3X2 operator *(const LCXMATRIX3X2&, FLOAT);

	friend LCXVECTOR2 operator *(LCXVECTOR2&, const LCXMATRIX3X2&);				// vector2 * matrix. return vector is x, y, z => x/z, y/z
	//friend LCXVECTOR2 operator *(const LCXMATRIX3X2&, LCXVECTOR2&);			// matrix * vector2 is not allowed

	INT operator ==(const LCXMATRIX3X2&) const;
	INT operator !=(const LCXMATRIX3X2&) const;

	LCXMATRIX3X2& Identity();
	LCXMATRIX3X2& Inverse(FLOAT* det);
	LCXMATRIX3X2& Inverse(FLOAT* det, const LCXMATRIX3X2* In);
	FLOAT         Determinant();

	LCXMATRIX3X2& Scaling(FLOAT X, FLOAT Y);
	LCXMATRIX3X2& Scaling(const LCXVECTOR2* vScl);
	LCXMATRIX3X2& Rotation(FLOAT fRad);
	LCXMATRIX3X2& Translation(FLOAT x, FLOAT y, INT bIdentity=LC_TRUE);
	LCXMATRIX3X2& Translation(const LCXVECTOR2* vTrs, INT bIdentity=LC_TRUE);

	void          TransformCoord(LCXVECTOR2* Out, const LCXVECTOR2* In);
	void          TransformNormal(LCXVECTOR2* Out, const LCXVECTOR2* In);		// Out = In * M with no translation

	LCXMATRIX3X2& Negative();													// Mij = - Mij
	LCXMATRIX3X2& Lerp(const LCXMATRIX3X2* v1,const LCXMATRIX3X2* v2, FLOAT t);	// this = (1-t)*v1 + t* v2
};

typedef LCXMATRIX3X2 LCXMAT3X2;




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// LCXRECT using x, y, w, h. default:x=0, y=0, w=0, h=0
struct LCXRECT : public LC_RECTF
{
	LCXRECT();
	LCXRECT(const LCXRECT&);
	LCXRECT(const FLOAT*);
	LCXRECT(const LCXRECT*);
	LCXRECT(FLOAT,FLOAT,FLOAT,FLOAT);
	LCXRECT(const LC_RECTF& v);
	LCXRECT(const LC_RECT& v);

	// casting
	operator FLOAT*();
	operator const FLOAT*() const;
	FLOAT& operator[](int n);

	// unary operators
	LCXRECT operator +() const;
	LCXRECT operator -() const;

	INT operator ==(const LCXRECT&) const;
	INT operator !=(const LCXRECT&) const;


	// assignment operators
	LCXRECT& operator+=(const LCXVECTOR2&)	;									// translation. x += rhs.x, y += rhs.y
	LCXRECT& operator-=(const LCXVECTOR2&)	;									// translation. x -= rhs.x, y -= rhs.y
	LCXRECT& operator*=(FLOAT v)			;									// scaling. x *=v, y *=v, w *=v, h *=v
	LCXRECT& operator/=(FLOAT v)			;									// scaling. x /=v, y /=v, w /=v, h /=v


	void ToRegion();															// right, bottom to w and height
	void ToRegion(LCXRECT* v);
	void ToRegion(FLOAT tLeft, FLOAT tTop, FLOAT tRight, FLOAT tBottom);

	void ToRect();																// width, height to right and bottom
	void ToRect(LCXRECT* v);

	INT IsInRect(const FLOAT* v);												// is a vector2 in rect?
	INT IsInRect(const LCXVECTOR2* v);
	INT IsInRect(const LCXRECT* v);

	INT Collision(const FLOAT* v);
	INT Collision(const LCXRECT* v);

	LCXVECTOR2 Get00()	 ;														// return x  , y
	LCXVECTOR2 Get10()	 ;														// return x+w, y
	LCXVECTOR2 Get01()	 ;														// return x  , y+h
	LCXVECTOR2 Get11()	 ;														// return x+w, y+h
	LCXVECTOR2 GetCenter();														// return x+w/2, y+h/2
	LC_RECT    GetRECT() ;														// return x, y, x+w, y+h. for window RECT
	LCXRECT&   Zero   () ;
	LCXRECT&   One    () ;
};




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Line

struct LCXLINE
{
	LCXVECTOR3	p;		// Start Pointer
	LCXVECTOR3	t;		// Tranverse Vector

	LCXLINE();
	LCXLINE(const FLOAT*)	;
	LCXLINE(const LCXLINE&)	;

	LCXLINE(FLOAT Px,FLOAT Py,FLOAT Pz,FLOAT Tx,FLOAT Ty,FLOAT Tz);
	LCXLINE(const LCXVECTOR3& P, const LCXVECTOR3& T);

	// casting
	operator FLOAT*()						;
	operator const FLOAT*() const			;

	// unary operators
	LCXLINE operator+() const				;
	LCXLINE operator-() const				;

	bool operator==(const LCXLINE& v) const	;
	bool operator!=(const LCXLINE& v) const	;
};




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Sphere

struct LCXSPHERE
{
	LCXVECTOR3	p;		// sphere center
	FLOAT 	r;		// sphere radius

	LCXSPHERE();
	LCXSPHERE(const FLOAT*)			;
	LCXSPHERE(const LCXSPHERE&)		;
	LCXSPHERE(FLOAT X,FLOAT Y,FLOAT Z,FLOAT R);

	// casting
	operator FLOAT*()						;
	operator const FLOAT*() const			;

	// unary operators
	LCXSPHERE operator+() const				;
	LCXSPHERE operator-() const				;

	bool operator==(const LCXSPHERE& v) const;
	bool operator!=(const LCXSPHERE& v) const;
};




struct LCXELLIPSOID
{
	FLOAT       a;																// radius along the x
	FLOAT       b;																// radius along the y
	LCXVECTOR2	c;																// center

	INT Collision(const LCXVECTOR2* p);											// return LC_EFAIL when it is not collison
};




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Cylinder

struct LCXCYLINDER
{
	LCXVECTOR3	p;		// cylinder start position. like to line
	LCXVECTOR3	t;		// cylinder traverse vector
	FLOAT 	r;		// radius
	FLOAT 	h;		// height

	LCXCYLINDER();
	LCXCYLINDER(const FLOAT*v);
	LCXCYLINDER(const LCXCYLINDER& v);
	LCXCYLINDER(FLOAT Px,FLOAT Py,FLOAT Pz,FLOAT Tx,FLOAT Ty,FLOAT Tz, FLOAT R, FLOAT H);
	LCXCYLINDER(const LCXVECTOR3& P, const LCXVECTOR3& T, FLOAT R, FLOAT H);

	// casting
	operator FLOAT*();
	operator const FLOAT*() const;

	// unary operators
	bool operator==(const LCXCYLINDER& v) const;
	bool operator!=(const LCXCYLINDER& v) const;

	// 임의의 두점과 반경과 높이
	void Set(const LCXVECTOR3& p0, const LCXVECTOR3& p1, FLOAT R, FLOAT H);
};




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// transform object

struct LCXTRANSFORM																// world transform
{
	LCXTRANSFORM();

	void Clear();																//
	void Scaling     (const LCXVECTOR3*      );									// setup the scaling
	void Scaling     (FLOAT,FLOAT,FLOAT      );									//
	void Rotation    (const LCXVECTOR4*      );									// setup the rotation. xyz: axis, w(radian angle). is not quaternion
	void Rotation    (FLOAT,FLOAT,FLOAT,FLOAT);
	void Translation (const LCXVECTOR3*      );									// setup the position
	void Translation (FLOAT,FLOAT,FLOAT      );
	void Epsilon     (const LCXVECTOR3*      );									// set epsilon: position
	void Epsilon     (const LCXVECTOR4*      );									// set epsilon position: xyz  and rotation: w
	void Epsilon     (FLOAT                  );									// set epsilon: rotation radian
	void TM          (LCXMATRIX*             );									// caution. set the matrix without change scaling, rotation, and position

	const LCXMATRIX*  const TM         () const;								// get transform matrix
	const LCXVECTOR3* const Scaling    () const;								// get scaling
	const LCXVECTOR4* const Rotation   () const;								// get rotation
	const LCXVECTOR3* const Translation() const;								// get position
	const LCXVECTOR4* const Epsilon    () const;								// get epsilon

protected:
	LCXMATRIX	m;																// final result transform matrix(world matrix)
	LCXVECTOR3	s;																// original scaling
	LCXVECTOR3	t;																// original position
	LCXVECTOR4	r;																// original rotation axis and angle(radian)
	LCXVECTOR4	e;																// epsilon position:xyz, rotation radian: w
	void Setup();
};




// transform for 2D
struct LCXTRANSFORM2D
{
	LCXTRANSFORM2D();

	void Clear       ();														//
	void Scaling     (const LCXVECTOR2*);										// scaling : float2
	void Scaling     (FLOAT,FLOAT      );										//
	void Rotation    (const LCXVECTOR3*);										// rotation: float3 rotation center(x,y) + rotation angle(z: radian)
	void Rotation    (FLOAT,FLOAT,FLOAT);
	void Translation (const LCXVECTOR2*);										// position: float2
	void Translation (FLOAT,FLOAT      );
	void Zvalue      (const FLOAT      );										// setup the z value
	void Epsilon     (const LCXVECTOR3*);										// set epsilon: position
	void Epsilon     (FLOAT            );										// set epsilon: rotation radian
	void Epsilon     (const LCXVECTOR4*);										// set epsilon position: xyz  and rotation: w
	void TM          (LCXMATRIX*       );										// caution. set the matrix without change scaling, rotation, and position

	const LCXMATRIX*  const TM         () const;								// get transform matrix
	const LCXVECTOR3* const Scaling    () const;								// get scaling
	const LCXVECTOR4* const Rotation   () const;								// get rotation
	const LCXVECTOR3* const Translation() const;								// get position
	FLOAT                   Zvalue     () const;								// get the z value
	const LCXVECTOR4* const Epsilon    () const;								// get epsilon

protected:
	LCXMATRIX	m;																// Output World Matrix
	LCXVECTOR2	s;																// Scaling
	LCXVECTOR3	r;																// Rotation
	LCXVECTOR3	t;																// Translation
	LCXVECTOR4	e;																// Epsilon. position: xyz, rotation radian: w
	void Setup();
};




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Vector2

FLOAT LCXVec2Dot        (const LCXVECTOR2* v1, const LCXVECTOR2* v2);							// dot2 product
FLOAT LCXVec2Length     (const LCXVECTOR2* v);													// vector2 Length
FLOAT LCXVec2LengthSq   (const LCXVECTOR2* v);													// vector2 Square Length
FLOAT LCXVec2Distance   (const LCXVECTOR2* v1, const LCXVECTOR2* v2);							// distance Square vector1, vector2
FLOAT LCXVec2DistanceSq (const LCXVECTOR2* v1, const LCXVECTOR2* v2);							// distance Square vector1, vector2
FLOAT LCXVec2Normalize  (LCXVECTOR2* v);														// normalize return length
FLOAT LCXVec2Normalize  (LCXVECTOR2* Out, const LCXVECTOR2* In);								// normalize return length
FLOAT LCXVec2Cross      (const LCXVECTOR2* v1, const LCXVECTOR2* v2);							// return the z value
void  LCXVec2Lerp       (LCXVECTOR2* Out
					   , const LCXVECTOR2* v1, const LCXVECTOR2* v2, FLOAT t);					// Out = (1-t)*v1 + t* v2

void LCXVec2MakeBoundingBox(LCXVECTOR2* vcMin, LCXVECTOR2* vcMax								// make out min, max of the bounding box from the List
						  , const LC_HANDLE pList, INT ListCount, INT stride);




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Vector3

FLOAT LCXVec3Dot          (const LCXVECTOR3* v1, const LCXVECTOR3* v2);							// dot3 product
FLOAT LCXVec3Length       (const LCXVECTOR3* v);												// vector3 Length
FLOAT LCXVec3LengthSq     (const LCXVECTOR3* v);												// vector3 Square Length
FLOAT LCXVec3DistanceSq   (const LCXVECTOR3* v1, const LCXVECTOR3* v2);							// distance Square vector1, vector2
FLOAT LCXVec3Normalize    (LCXVECTOR3* v);														// normalize return length
FLOAT LCXVec3Normalize    (LCXVECTOR3* Out, const LCXVECTOR3* In);								// normalize return length
void  LCXVec3Cross        (LCXVECTOR3* Out, const LCXVECTOR3* v);								// Out = cross(Out, v);
void  LCXVec3Cross        (LCXVECTOR3* Out
						 , const LCXVECTOR3* v1, const LCXVECTOR3* v2);							// Out = cross(v1, v2);

void  LCXVec3NormalVector (LCXVECTOR3* Out
						 , const LCXVECTOR3* v1, const LCXVECTOR3* v2, const LCXVECTOR3* v3);	// Out = normal(cross(v2-v1, v3, v1))

void  LCXVec3Minimize     (LCXVECTOR3* Out, const LCXVECTOR3* v1, const LCXVECTOR3* v2);		// min(v1.xyz, v2.xyz)
void  LCXVec3Maximize     (LCXVECTOR3* Out, const LCXVECTOR3* v1, const LCXVECTOR3* v2);		// max(v1.xyz, v2.xyz)
void  LCXVec3Lerp         (LCXVECTOR3* Out
							, const LCXVECTOR3* v1, const LCXVECTOR3* v2, FLOAT t);				// Out = (1-t)*v1 + t* v2

void  LCXVec3FromScreen   (LCXVECTOR3* pOut, FLOAT scn_x, FLOAT scn_y							// transform position on screen to 3d world position
							, const LCXMATRIX* vpt												// viewport matrix
							, const LCXMATRIX* prj												// projection matrix
							, const LCXMATRIX* viw);											// view matrix

void  LCXVec3DirectionFromScreen( LCXVECTOR3* pOut, FLOAT scn_x, FLOAT scn_y					// position on viewport
								, const LCXMATRIX* vpt
								, const LCXMATRIX* prj
								, const LCXMATRIX* viw);										// 3d direction mouse to near plane

void  LCXVec3DirectionFromScreen( LCXVECTOR3* pOut												// 3d direction from screen position
								, FLOAT scn_x, FLOAT scn_y										// position on viewport
								, FLOAT vpW, FLOAT vpH											// viewport width and height
								, const LCXMATRIX* invView										// inverse view matrix
								, const LCXMATRIX* Project  );									// projection matrix

void  LCXVec3MakeBoundingBox (LCXVECTOR3* pMin, LCXVECTOR3* pMax								// make out min, max of the bounding box from the List
							, const LC_HANDLE pList, INT ListCount, INT stride);

void  LCXVec3MinMaxFromQuad  (LCXVECTOR3* pMin, LCXVECTOR3* pMax								// make out min, max from 2~4 positions
							, const LCXVECTOR3* p0     , const LCXVECTOR3* p1=NULL
							, const LCXVECTOR3* p2=NULL, const LCXVECTOR3* p3=NULL);

void  LCXVec3CenterFromQuad  (LCXVECTOR3* Out													// make out the center 2~4 positions
							, const LCXVECTOR3* p0     , const LCXVECTOR3* p1=NULL
							, const LCXVECTOR3* p2=NULL, const LCXVECTOR3* p3=NULL);






//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Vector4

FLOAT LCXVec4Dot            (const LCXVECTOR4* v1, const LCXVECTOR4* v2);						// dot4 product
FLOAT LCXVec4Length         (const LCXVECTOR4* v);												// vector4 Length
FLOAT LCXVec4LengthSq       (const LCXVECTOR4* v);												// vector4 Square Length
FLOAT LCXVec4Normalize      (LCXVECTOR4* v);													// normalize return length
FLOAT LCXVec4Normalize      (LCXVECTOR4* Out, const LCXVECTOR4* In);							// normalize return length
void  LCXVec4Lerp           (LCXVECTOR4* Out
						   , const LCXVECTOR4* v1, const LCXVECTOR4* v2, FLOAT t);				// Out = (1-t)*v1 + t* v2




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Transform

// vector2: z = 1
void  LCXVec2TransformCoord   (LCXVECTOR2* Out, const LCXVECTOR2* In, const LCXMAT3X3* tm);		// transform of vector by 3x3 matrix. z = 1

// vector2: nun devided by z
void  LCXVec2TransformNormal  (LCXVECTOR2* Out, const LCXVECTOR2* In, const LCXMAT3X3* tm);		// transform of vector by 3x3 matrix. z = 0


// vector3: w = 1
void  LCXVec3TransformCoord   (LCXVECTOR3* Out, const LCXVECTOR3* In, const LCXMATRIX* tm);		// transform of vector by 4x4 matrix
void  LCXVec3TransformCoord   (LCXVECTOR3* Out, const LCXVECTOR3* In, const LCXMAT4X3* tm);		// transform of vector by 4x3 matrix

// vector3: w = 0
void  LCXVec3TransformNormal  (LCXVECTOR3* Out, const LCXVECTOR3* In, const LCXMATRIX* tm);		// transform of vector by 4x4 matrix
void  LCXVec3TransformNormal  (LCXVECTOR3* Out, const LCXVECTOR3* In, const LCXMAT4X3* tm);		// transform of vector by 4x3 matrix

// vector4
void  LCXVec4TransformCoord   (LCXVECTOR4* Out, const LCXVECTOR4* In, const LCXMATRIX* tm);

// vector3
void  LCXVec3Translate        (LCXVECTOR3* Out, const LCXMATRIX* tm, const LCXVECTOR3* In);		// out = In + vec3(tm._41, tm.42, tm.43)
void  LCXVec3InverseTranslate (LCXVECTOR3* Out, const LCXMATRIX* tm, const LCXVECTOR3* In);		// out = In - vec3(tm._41, tm.42, tm.43)
void  LCXVec3Rotate           (LCXVECTOR3* Out, const LCXMATRIX* pR, const LCXVECTOR3* In);
void  LCXVec3InverseRotate    (LCXVECTOR3* Out, const LCXMATRIX* pR, const LCXVECTOR3* In);




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Plane

FLOAT LCXPlaneDot                (const LCXPLANE* Out, const LCXVECTOR4* v);					// same to a*x + b*y + c*z + d*w
FLOAT LCXPlaneDotCoord           (const LCXPLANE* Out, const LCXVECTOR3* v);					// same to a*x + b*y + c*z + d*1
FLOAT LCXPlane2DotCoord          (const LCXPLANE2* Out, const LCXVECTOR2* v);					// same to a*x + b*y + d*1
FLOAT LCXPlaneDotNormal          (const LCXPLANE *p, const LCXVECTOR3 *v);						// same to a*x + b*y + c*z
void  LCXPlaneFromNormalDistance (LCXPLANE* Out, const LCXVECTOR3* n, FLOAT d);					// constructs a plane by normal and minimum distance from starting point(world zero vector)
void  LCXPlaneFromPointNormal    (LCXPLANE* Out
								, const LCXVECTOR3* p, const LCXVECTOR3* normal);				// constructs a plane by normal and point in plane
void  LCXPlaneFromPoints         (LCXPLANE* Out
								, const LCXVECTOR3*,const LCXVECTOR3*,const LCXVECTOR3*);		// constructs a plane by 3 points
void  LCXPlaneDvalue             (LCXPLANE* p, const LCXVECTOR3* v);							// set the plane d with position(v)
void  LCXPlaneTransform          (LCXPLANE* Out, const LCXPLANE* In, const LCXMATRIX* tm);		// It's similar to the D3DXPlaneTransform which needs inverse transpose of tm. but it does not need inverse transpose.
INT   LCXVec3From3Planes         (LCXVECTOR3*Out
								, const LCXPLANE* a,const LCXPLANE*b,const LCXPLANE*c);			// the overlap point of 3plane a, b, and c




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Quaternion

void  LCXQuaternionIdentity   (LCXQUATERNION* q);
FLOAT LCXQuaternionLength     (const LCXQUATERNION* q);
FLOAT LCXQuaternionLengthSq   (const LCXQUATERNION* q);
FLOAT LCXQuaternionDot        (const LCXQUATERNION* q1, const LCXQUATERNION* q2);
INT   LCXQuaternionIsIdentity (const LCXQUATERNION* q);
void  LCXQuaternionConjugate  (LCXQUATERNION* Out, const LCXQUATERNION* q);
void  LCXQuaternionSLerp      (LCXQUATERNION* Out												// qOut = (1/sin T)[ sin ( T *(1-t) ) * q1 + sin ( T * t ) * q2]
							 , const LCXQUATERNION* q1
							 , const LCXQUATERNION* q2
							 , FLOAT t);

void  LCXQuaternionToAxisRadian(LCXVECTOR3* pAxis, FLOAT* rad, const LCXQUATERNION* q);			// get the axis and radian from quaternion

void  LCXQuaternionToAxisCosSin(LCXVECTOR3* pAxis,FLOAT* fcos,FLOAT* fsin
							  , const LCXQUATERNION*);											// get the axis, cos, and sin value from from quaternion

void  LCXQuaternionFromMatrix  (LCXQUATERNION* Out, const LCXMATRIX* tm, INT bLHR = LC_TRUE);	// LHR = Left Hand Rule. ex)Direct3D
void  LCXQuaternionFromMatrix  (LCXQUATERNION* Out, const LCXMAT4X3* tm, INT bLHR = LC_TRUE);	// LHR = Left Hand Rule. ex)Direct3D




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Matrix.

void  LCXMatrixIdentity        (LCXMATRIX* m);
void  LCXMatrixAdd             (LCXMATRIX* m, const LCXMATRIX* a, const LCXMATRIX* b);			// m= a+b
void  LCXMatrixSub             (LCXMATRIX* m, const LCXMATRIX* a, const LCXMATRIX* b);			// m= a-b
void  LCXMatrixMul             (LCXMATRIX* m, const LCXMATRIX* a, const LCXMATRIX* b);			// m = a*b

void  LCXMatrixTranspose       (LCXMATRIX* Out, const LCXMATRIX *v);							// transpose.
FLOAT LCXMatrixInverse         (LCXMATRIX* m, INT bQuick=LC_TRUE);								// if the 'bQuick' is not false then this function will be calculating the inverse matrix  except _14=0, _24=0, _34=0, _44=1
INT   LCXMatrixInverse         (LCXMATRIX* Out, FLOAT* determinant, const LCXMATRIX* tm);		// the the inverse matrix
FLOAT LCXMatrixDeterminant     (const LCXMATRIX* m);
void  LCXMatrixScaling         (LCXMATRIX* m, const LCXVECTOR3* scl);
void  LCXMatrixScaling         (LCXMATRIX* m, FLOAT x, FLOAT y, FLOAT z);
void  LCXMatrixRotationX       (LCXMATRIX* m, FLOAT rad);
void  LCXMatrixRotationY       (LCXMATRIX* m, FLOAT rad);
void  LCXMatrixRotationZ       (LCXMATRIX* m, FLOAT rad);
void  LCXMatrixRotationAxis    (LCXMATRIX* m, const LCXVECTOR3* axs, FLOAT rad);

void  LCXMatrixLerp            (LCXMATRIX* m, const LCXMATRIX* m1								// m = (1-t)*m1 + t* m2
							  , const LCXMATRIX* m2, FLOAT t);

INT   LCXMatrixAxisCosSinRadian(LCXVECTOR3 *pAxs, FLOAT* pCos, FLOAT* pSin, FLOAT* pRad			// get the axis, cosine, sine, radian. if failed, return -1. if the radian is null, then the operation is more fast.
							   , const LCXMATRIX *tm, INT bLHR = LC_TRUE);						// LHR = Left Hand Rule. ex)Direct3D

INT   LCXMatrixAxisCosSinRadian(LCXVECTOR3 *pAxs, FLOAT* pCos, FLOAT* pSin, FLOAT* pRad			// get the axis, cosine, sine, radian. if failed, return -1. if the radian is null, then the operation is more fast.
							  , const LCXMAT4X3 *tm, INT bLHR = LC_TRUE);						// LHR = Left Hand Rule. ex)Direct3D

void  LCXMatrixFromQuat        (LCXMATRIX* Out, const LCXQUATERNION* q, INT bLHR=LC_TRUE);		// LHR = Left Hand Rule. ex)Direct3D
void  LCXMatrixFromQuat        (LCXMAT4X3* Out, const LCXQUATERNION* q, INT bLHR=LC_TRUE);		// LHR = Left Hand Rule. ex)Direct3D
void  LCXMatrix4X4From4X3      (LCXMATRIX* Out, const LCXMAT4X3* tm);
void  LCXMatrix4X4From3X3Tm    (LCXMATRIX* Out, const LCXMAT3X3* tm);							// It's same to LCXMATRIX::From3X3Tm
void  LCXMatrix4X3From4X4      (LCXMAT4X3* Out, const LCXMATRIX* tm);
void  LCXMatrixViewport        (LCXMATRIX* pOut, const FLOAT* viewport);						// 4x4 viewportmatrix. viewport needs FLOAT x,y,w,h, clipping volume minimum(n), maximum(z) depth.
void  LCXMatrixScreenOrient    (LC_HANDLE pOut, INT nModelType);								// Get the system window direction matrix. needs FLOAT*16. ModelType:: LC_OBJ_SPRITE, LC_OBJ_GUI, LC_RSC_MODEL2D




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// etc...

INT   LCXVec3Greater                  (const LCXVECTOR3* p1, const LCXVECTOR3* p2);
INT   LCXVec3Less                     (const LCXVECTOR3* p1, const LCXVECTOR3* p2);
INT   LCXVec3Equal                    (const LCXVECTOR3* p1, const LCXVECTOR3* p2
									 , FLOAT epsilon=LCX_R_DELTA);

void  LCXVec3RotationDegrees          (LCXVECTOR3* Out, const LCXMATRIX* In);
void  LCXMatrixRotationRadians        (LCXMATRIX* Out, const LCXVECTOR3* pRot);
void  LCXMatrixRotationDegrees        (LCXMATRIX* Out, const LCXVECTOR3* pRot);
void  LCXMatrixInverseRotationRadians (LCXMATRIX* Out, const LCXVECTOR3* pRot);
void  LCXMatrixInverseRotationDegrees (LCXMATRIX* Out, const LCXVECTOR3* pRot);

void  LCXLerpFloat2                   (FLOAT* Out, const FLOAT* v1, const FLOAT* v2, FLOAT g);	// Interpolation out = (1-g)*v1 + g*v2;
void  LCXLerpFloat3                   (FLOAT* Out, const FLOAT* v1, const FLOAT* v2, FLOAT g);
void  LCXLerpFloat4                   (FLOAT* Out, const FLOAT* v1, const FLOAT* v2, FLOAT g);
void  LCXLerpFloat                    (FLOAT* Out, const FLOAT* v1, const FLOAT* v2
									 , FLOAT g, INT count);

INT   LCXEllipseToPointCollision      (LCXELLIPSOID* e, const LCXVECTOR2* p);					// collision edllipse to point




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Color
// bit order Blue, Green, Red, Alpha(ARGB: DirectX System)

LC_INLINE COLOR8  LCXColAlphaFrom32ARGB  (COLOR32 c){ return COLOR8( (c>>24) & 0xFF);	}
LC_INLINE COLOR8  LCXColRedFrom32ARGB    (COLOR32 c){ return COLOR8( (c>>16) & 0xFF);	}
LC_INLINE COLOR8  LCXColGreenFrom32ARGB  (COLOR32 c){ return COLOR8( (c>> 8) & 0xFF);	}
LC_INLINE COLOR8  LCXColBlueFrom32ARGB   (COLOR32 c){ return COLOR8( (c>> 0) & 0xFF);	}

LC_INLINE COLOR8  LCXColAlphaFrom24ARGB  (COLOR32 c){ return                   0xFF ;	}
LC_INLINE COLOR8  LCXColRedFrom24ARGB    (COLOR32 c){ return COLOR8( (c>>16) & 0xFF);	}
LC_INLINE COLOR8  LCXColGreenFrom24ARGB  (COLOR32 c){ return COLOR8( (c>> 8) & 0xFF);	}
LC_INLINE COLOR8  LCXColBlueFrom24ARGB   (COLOR32 c){ return COLOR8( (c>> 0) & 0xFF);	}

LC_INLINE void    LCXColAlphaTo32ARGB    (COLOR32& c, COLOR32 a){ c = (a<<24) | (c & 0x00FFFFFF); }
LC_INLINE void    LCXColRedTo32ARGB      (COLOR32& c, COLOR32 r){ c = (r<<16) | (c & 0xFF00FFFF); }
LC_INLINE void    LCXColGreenTo32ARGB    (COLOR32& c, COLOR32 g){ c = (g<< 8) | (c & 0xFFFF00FF); }
LC_INLINE void    LCXColBlueTo32ARGB     (COLOR32& c, COLOR32 b){ c = (b<< 0) | (c & 0xFFFFFF00); }

LC_INLINE COLOR16 LCXColR5G6B5           (INT r,INT g,INT b)      { return (r<<8 & 0xF800) | (g<<3 & 0x7E0) | (b>>3 & 0x1F);                   }
LC_INLINE COLOR16 LCXColX1R5G5B5         (INT r,INT g,INT b)      { return (r>>7 & 0x7C00) | (g<<2 & 0x3E0) | (b>>3 & 0x1F) | (0x8000);        }
LC_INLINE COLOR16 LCXColA1R5G5B5         (INT r,INT g,INT b,INT a){ return (r>>7 & 0x7C00) | (g<<2 & 0x3E0) | (b>>3 & 0x1F) | (a<<8 & 0x8000); }

LC_INLINE COLOR16 LCXColR5G6B5FromARGB   (COLOR32 c){ return (COLOR16)( (c>>8 & 0xF800) | (c>>5 & 0x7E0) | (c>>3 & 0x1F)                    ); }
LC_INLINE COLOR16 LCXColX1R5G5B5FromARGB (COLOR32 c){ return (COLOR16)( (c>>9 & 0x7C00) | (c<<6 & 0x3E0) | (c>>3 & 0x1F) | (0x8000)         ); }
LC_INLINE COLOR16 LCXColA1R5G5B5FromARGB (COLOR32 c){ return (COLOR16)( (c>>9 & 0x7C00) | (c<<6 & 0x3E0) | (c>>3 & 0x1F) | (c>>16 & 0x8000) ); }

// Returns value from A1R5G5B5 color
LC_INLINE COLOR8  LCXColAlphaFrom1555    (COLOR16 c){ return (COLOR8 )(c>>15 & 0x01); }
LC_INLINE COLOR8  LCXColRedFrom1555      (COLOR16 c){ return (COLOR8 )(c>>10 & 0x1F); }
LC_INLINE COLOR8  LCXColGreenFrom1555    (COLOR16 c){ return (COLOR8 )(c>> 5 & 0x1F); }
LC_INLINE COLOR8  LCXColBlueFrom1555     (COLOR16 c){ return (COLOR8 )(c>> 0 & 0x1F); }

LC_INLINE COLOR8  LCXColRedFrom565       (COLOR16 c){ return (COLOR8 )(c>>11 & 0x1F); }
LC_INLINE COLOR8  LCXColGreenFrom565     (COLOR16 c){ return (COLOR8 )(c>> 5 & 0x3F); }
LC_INLINE COLOR8  LCXColBlueFrom565      (COLOR16 c){ return (COLOR8 )(c>> 0 & 0x1F); }

LC_INLINE COLOR16 LCXColLuminanceFrom1555(COLOR16 c){ return  ( (c>>15 & 0x01) + (c>>10 & 0x1F) + (c>> 5 & 0x1F) + (c>> 0 & 0x1F) ) << 3 / 3; }

// 16 -> 32 ARGB
LC_INLINE COLOR32 LCXColA8R8G8B8From1555 (COLOR16 c){ return (c&0x8000)<<16 | (c&0x7C00)<<9 | (c&0x3E0)<<6 | (c&0x1F)<<3;	}
LC_INLINE COLOR32 LCXColR8G8B8From565    (COLOR16 c){ return	 0xFF000000 | (c&0xF800)<<8 | (c&0x7E0)<<5 | (c&0x1F)<<3;	}




// bit order Red, Green, Blue, Alpha (ABGR or RGBA: OpenGL System)
LC_INLINE COLOR8  LCXColAlphaFrom32RGBA  (COLOR32 c){ return COLOR8( (c>>24) & 0xFF);	}
LC_INLINE COLOR8  LCXColBlueFrom32RGBA   (COLOR32 c){ return COLOR8( (c>>16) & 0xFF);	}
LC_INLINE COLOR8  LCXColGreenFrom32RGBA  (COLOR32 c){ return COLOR8( (c>> 8) & 0xFF);	}
LC_INLINE COLOR8  LCXColRedFrom32RGBA    (COLOR32 c){ return COLOR8( (c>> 0) & 0xFF);	}

LC_INLINE void    LCXColAlphaTo32RGBA    (COLOR32& c, COLOR32 a){ c = (a<<24) | (c & 0x00FFFFFF); }
LC_INLINE void    LCXColBlueTo32RGBA     (COLOR32& c, COLOR32 b){ c = (b<<16) | (c & 0xFF00FFFF); }
LC_INLINE void    LCXColGreenTo32RGBA    (COLOR32& c, COLOR32 g){ c = (g<< 8) | (c & 0xFFFF00FF); }
LC_INLINE void    LCXColRedTo32RGBA      (COLOR32& c, COLOR32 r){ c = (r<< 0) | (c & 0xFFFFFF00); }

LC_INLINE COLOR16 LCXColR5G5B5X1         (INT r,INT g,INT b)      { return (r<<8 & 0xF800) | (g<<3 & 0x7C0) | (b>>2 & 0x3E) | (0x1);  }
LC_INLINE COLOR16 LCXColR5G5B5A1         (INT r,INT g,INT b,INT a){ return (r<<8 & 0xF800) | (g<<3 & 0x7C0) | (b>>2 & 0x3E) | (a>>7 & 0x1); }

LC_INLINE COLOR16 LCXColR5G6B5FromABGR   (COLOR32 c){ return (COLOR16)( (c<<8 & 0xF800) | (c>>5 & 0x7E0) | (c>>19& 0x1F)                 ); }
LC_INLINE COLOR16 LCXColR5G5B5X1FromABGR (COLOR32 c){ return (COLOR16)( (c<<8 & 0xF800) | (c>>5 & 0x7C0) | (c>>18& 0x1F) | (0x8000)      ); }
LC_INLINE COLOR16 LCXColR5G5B5A1FromABGR (COLOR32 c){ return (COLOR16)( (c<<8 & 0xF800) | (c>>5 & 0x7C0) | (c>>18& 0x1F) | (c>>31 & 0x1) ); }

// Returns value from R5G5B5A1 color
LC_INLINE COLOR8  LCXColAlphaFrom5551    (COLOR16 c){ return (COLOR8 )(c>> 0 & 0x01); }
LC_INLINE COLOR8  LCXColRedFrom5551      (COLOR16 c){ return (COLOR8 )(c>>11 & 0x1F); }
LC_INLINE COLOR8  LCXColGreenFrom5551    (COLOR16 c){ return (COLOR8 )(c>> 6 & 0x1F); }
LC_INLINE COLOR8  LCXColBlueFrom5551     (COLOR16 c){ return (COLOR8 )(c>> 1 & 0x1F); }

LC_INLINE COLOR16 LCXColLuminanceFrom5551(COLOR16 c){ return  ( (c>>0 & 0x01) + (c>>11 & 0x1F) + (c>>6 & 0x1F) + (c>>1 & 0x1F) ) << 3 / 3; }

// 16 -> 32 RGBA
LC_INLINE COLOR32 LCXColA8B8G8R8From5551 (COLOR16 c){ return (c&0x1)<<31| (c&0x3E)<<18 | (c&0x7C0)<<5 | (c&0xF800)>>8; }
LC_INLINE COLOR32 LCXColB8G8R8From565    (COLOR16 c){ return 0xFF000000 | (c&0x1F)<<19 | (c&0x7E0)<<5 | (c&0xF800)>>8; }

// ARGB <--> BGR
LC_INLINE void    LCXColByteFromARGB     (BYTE* o, COLOR32 c){ BYTE* s=(BYTE*)&c; o[0] = s[3]; o[1] = s[2]; o[2] = s[1]; o[3] = s[0]; }
LC_INLINE void    LCXColByteFromBGR      (BYTE* o, COLOR32 c){ BYTE* s=(BYTE*)&c; o[0] = 0x00; o[1] = s[0]; o[2] = s[1]; o[3] = s[2]; }

#endif	//_LC_Math_H_
