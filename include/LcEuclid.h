//  For Mathematics for Euclid Field.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef _LcEuclid_H_
#define _LcEuclid_H_

#include <math.h>
#include "LcType.h"
#include "LcBase.h"
#include "LcMath.h"


typedef LCXVECTOR2		VEC2;
typedef LCXVECTOR3		VEC3;
typedef LCXVECTOR4		VEC4;
typedef LCXMATRIX		MAT4;


//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// for 2d...

// collision for RECT in 2d program
template<class T>
void LCXRect2Region(T* v)														// right, bottom to w and height
{
	v->w = v->right  - v->left;
	v->h = v->bottom - v->top;
}

template<class T>
void LCXRegion2Rect(T* v)														// width, height to right and bottom
{
	v->right = v->left + v->_w;
	v->bottom= v->top  + v->_h;
}

template<class T1, class T2>
INT LCXIsInRect(const T1& p, const T2& rc)
{
	if( rc.x > p.x || p.x > rc.x + rc.w ||
		rc.y > p.y || p.y > rc.y + rc.h )
		return LC_EFAIL;

	return LC_OK;
}

template<class T>
INT LCXIsInRect(const T& p, FLOAT x, FLOAT y, FLOAT w, FLOAT h)					// x: left, y: top, w: width, h: height
{
	if( x > p.x || p.x > x + w ||
		y > p.y || p.y > y + h )
		return LC_EFAIL;

	return LC_OK;
}

template<class T>
INT LCXIsInRect(T px, T py, FLOAT x, FLOAT y, FLOAT w, FLOAT h)					// x: left, y: top, w: width, h: height
{
	if( x > px || px > x + w ||
		y > py || py > y + h )
		return LC_EFAIL;

	return LC_OK;
}

template<class T>
INT LCXIsInRect(FLOAT x, FLOAT y, const T& rc)									//
{
	if( rc.x > x || x > rc.x + rc.w ||
		rc.y > y || y > rc.y + rc.h )
		return LC_EFAIL;

	return LC_OK;
}

template<class T>
INT LCXIsInMinMax(const T& p,FLOAT min_x,FLOAT min_y,FLOAT max_x,FLOAT max_y)	// check where the p is in min and max
{
	if( min_x > p.x || p.x > max_x ||
		min_y > p.y || p.y > max_y )
		return LC_EFAIL;

	return LC_OK;
}

template<class T>																// p0, p1, p2, p3 are in min, max
INT LCXIsInMinMax2(T& p0, T& p1, T& p2, T& p3,
				   FLOAT min_x,FLOAT min_y,FLOAT max_x,FLOAT max_y)
{
	if(LC_FAILED(LCXIsInMinMax(p0, min_x, min_y, max_x, max_y)))
		return LC_EFAIL;

	if(LC_FAILED(LCXIsInMinMax(p1, min_x, min_y, max_x, max_y)))
		return LC_EFAIL;

	if(LC_FAILED(LCXIsInMinMax(p2, min_x, min_y, max_x, max_y)))
		return LC_EFAIL;

	if(LC_FAILED(LCXIsInMinMax(p3, min_x, min_y, max_x, max_y)))
		return LC_EFAIL;

	return LC_OK;
}

template<class T>																// rect must be x, y, w, h
INT LCXCollisionRect2Rect(const T& v1, const T& v2)
{
	if(	v1.x        > v2.x + v2.w ||											// ! v1.left   <= v2.right
		v1.x + v1.w < v2.x        ||											// ! v1.right  >= v2.left
		v1.y        > v2.y + v2.h ||											// ! v1.top    <= v2.bottom
		v1.y + v1.h < v2.y		)												// ! v1.bottom >= v2.top
		return LC_EFAIL;

	return LC_OK;
}

template<class T>																// Collision: lt: (left, top), rb: (right,bottom)
INT LCXCollisionRect2Rect( const T& v1_lt
						  , const T& v1_rb
						  , const T& v2_lt
						  , const T& v2_rb)
{
	if( v1_lt.x > v2_rb.x ||													// ! v1.left   <= v2.right
		v1_rb.x < v2_lt.x ||													// ! v1.right  >= v2.left
		v1_lt.y > v2_rb.y ||													// ! v1.top    <= v2.bottom
		v1_rb.y < v2_lt.y  )													// ! v1.bottom >= v2.top
		return LC_EFAIL;

	return LC_OK;
}

template<class T>																// Collision :  (left, top, width, height)
INT LCXCollisionRect2RectLTWH(T x1, T y1, T w1, T h1, T x2, T y2, T w2, T h2)
{
	if( x1      > x2 + w2 ||													// ! left1   <= right2
		x1 + w1 < x2      ||													// ! right1  >= left2
		y1      > y2 + h2 ||													// ! top1    <= bottom2
		y1 + h1 < y2       )													// ! bottom1 >= top2
		return LC_EFAIL;

	return LC_OK;
}

template<class T>																// Collision:  (left, top, right ,bottom)
INT LCXCollisionRect2RectLTRB(T l1, T r1, T t1, T b1
						, T l2, T r2, T t2, T b2)
{
	if( l1 > r2 ||																// ! left1   <= right2
		r1 < l2 ||																// ! right1  >= left2
		t1 > b2 ||																// ! top1    <= bottom2
		b1 < t2  )																// ! bottom1 >= top2
		return LC_EFAIL;

	return LC_OK;
}


template<class T>
INT LCXLine2Line(const T& l0, const T& l1, const T& s0, const T& s1)
{
	return LC_OK;
}


template<class T>
INT LCXCollisionCircle2Circle(const T& c1, const T& c2, FLOAT r1, FLOAT r2)		// center 1, center2, radius 1, radius 2
{
	if( (c1.x - c2.x) * (c1.x - c2.x) +
		(c1.y - c2.y) * (c1.y - c2.y) - (r1 + r2) * (r1 + r2)  > 0
		)
		return LC_EFAIL;

	return LC_OK;
}

INT LCXCollisionOBB2D(LCXVECTOR2* p1, INT stride1, int count1					// p and v must be a clock-wise or ccw direction and convex polygon.
					, LCXVECTOR2* p2, INT stride2, int count2
					, INT bCCW = LC_FALSE);

INT LCXCollisionOBBRECT(LCXVECTOR2* p1
					  , LCXVECTOR2* p2, INT bCCW = LC_FALSE);					// p and v have 4-convex points.




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Simple Triangle

struct LCX_TRI
{
	VEC3		p[3];

	LCX_TRI();
	LCX_TRI(const LCX_TRI&);
	LCX_TRI(const VEC3*);
	LCX_TRI(const VEC3& _0, const VEC3& _1, const VEC3& _2);
	LCX_TRI(const VEC3* _0, const VEC3* _1, const VEC3* _2);
	LCX_TRI(const FLOAT*);
	LCX_TRI(FLOAT _0x, FLOAT _0y, FLOAT _0z
		  , FLOAT _1x, FLOAT _1y, FLOAT _1z
		  , FLOAT _2x, FLOAT _2y, FLOAT _2z);

	// casting
	operator FLOAT*();
	operator const FLOAT*() const;

	const LCX_TRI& operator=(const LCX_TRI&);
	INT operator == (const LCX_TRI&) const;
	INT operator != (const LCX_TRI&) const;
};




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Picking Trangle

struct LCX_PCK
{
	VEC3		pck;															// Picking Position or Bound Center
	FLOAT	 	dist;															// Distance from view matrix eye for Sorting or Bound Radius
	LCX_TRI		tri;															// triangle
	LC_INT3		idx;															// Triangle Index for tri[0], tri[1], and tri[2]
	LC_INT4		xtr;															// extera data

	LCX_PCK	();
	LCX_PCK	( VEC3* _pck, FLOAT _dist);
	LCX_PCK	( VEC3* _pck, FLOAT _dist
			, VEC3* _tri0, VEC3* _tri1, VEC3* _tri2
			, INT* _id, INT* _extra);

	LCX_PCK	( VEC3* _pck, FLOAT _dist
			, VEC3* _tri0, VEC3* _tri1, VEC3* _tri2
			, INT _t0, INT _t1, INT _t2											// triangle index for tri. idx.x<- _t0, idx.y<- _t1, idx.z<- _t2
			, INT _e0, INT _e1, INT _e2 =0xFFFFFFFF, INT _e3 =0xFFFFFFFF		// xtr.x <- _e0, xtr.y <- _e1, xtr.z <- _e2, xtr.w <- _e3
			);

	const LCX_PCK& operator=(const LCX_PCK&);
	INT			operator == (const LCX_PCK&) const;
	INT			operator != (const LCX_PCK&) const;

	FLOAT		BoundRadius();
	VEC3		BoundCenter();
	void		Invalid();															// set the data to >0
};




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
//
// edge point index for cuboid(Hexahedron), ABB(Axis Aligned Bounding Box),
// OBB(object oriented bounding box)
//
//                           (Max)
//           6-----------------7
//          /|                /|
//         / |               / |
//        /  |   +z         /  |
//       /   |    |   +y   /   |
//      /    |    |  /    /    |
//     /     |    | /    /     |
//    4-----------------5      |
//    |  -x --- center -|-- +x |
//    |      2-- /|-----|------3
//    |     /   / |     |     /
//    |    /   /  |     |    /
//    |   /  -y   |     |   /
//    |  /        -z    |  /
//    | /               | /
//    |/                |/
//    0-----------------1
//    (Min)



// cube has edge, dimensioin, and color

struct LCX_CUBOID
{
	VEC3		edg[8];															// edge point
	VEC3		dim;
	COLOR32		col;

	LCX_CUBOID	();
	LCX_CUBOID	(const LCX_CUBOID&);
	LCX_CUBOID	(FLOAT x, FLOAT y, FLOAT z);									// like to AABB
	LCX_CUBOID	(FLOAT x, FLOAT y, FLOAT z										// like to OBB
				, const VEC3* X, const VEC3* Y, const VEC3* Z);					// axis X, Y, Z

	void		Dimension(FLOAT x, FLOAT y, FLOAT z);							// setup with AABB box dimension
	void		Dimension(FLOAT x, FLOAT y, FLOAT z								// setup with OOBB box dimention and axis
						 , const VEC3* X, const VEC3* Y, const VEC3* Z);		// axis X, Y, Z

	void		MinMax	(const VEC3* v_min, const VEC3* v_max);					// setup with min, max position
	void		Position(const VEC3* pos);										// translation

	operator	FLOAT*();
	operator	const FLOAT*() const;

	INT   		operator ==(const LCX_CUBOID&) const;
	INT   		operator !=(const LCX_CUBOID&) const;
	void  		operator = (const LCX_CUBOID&);

	static 		WORD idxLine[12][2];											// { {0,1},  {1,3},  {3,2}, {1,5},  {5,7},  {7,3}, {5,4},  {4,6},  {6,7}, {4,0},  {0,2},  {2,6}, };
	static 		WORD idxTri1[ 6][3];											// { {0,1,4}, {1,3,5},  {3,2,7},  {2,0,6},  {4,5,6},  {0,2,1},};
	static 		WORD idxTri2[12][3];											// { {0,1,4}, {5,4,1}, {1,3,5}, {7,5,3},  {3,2,7}, {6,7,2},  {2,0,6}, {4,6,0},  {4,5,6}, {7,6,5}, {0,2,1}, {3,1,2}, };
};




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// center + half dimension

struct LCX_AABC
{
	VEC3		vcO;															// aabb center
	VEC3		vcL;															// half length for x,y and z axis

	LCX_AABC();
	LCX_AABC(const VEC3& _min, const VEC3& _max);

	VEC3		Extent() const;
	void		Edge(VEC3* pvcEdge);											// needs VEC3 * 8 array
	void		Line(VEC3* pvcLine);											// needs VEC3 * 2 array

	INT			operator==(const LCX_AABC& v) const;
	INT			operator!=(const LCX_AABC& v) const;
};




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// center + obb axis
struct LCX_OBBC
{
	VEC3		vcO;															// obb center
	VEC3		vcA[3];															// axis left, top, and depth. they have length.(is not normalized).
};




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// cubue has only min, and max position

struct LCX_AABB
{
	VEC3		vMin;
	VEC3		vMax;

	LCX_AABB	();
	LCX_AABB	(const LCX_AABB&);
	LCX_AABB	(const VEC3*);
	LCX_AABB	(const VEC3& _min, const VEC3& _max);
	LCX_AABB	(const VEC3&);
	LCX_AABB	(FLOAT*);
	LCX_AABB	(FLOAT x0, FLOAT y0, FLOAT z0, FLOAT x1, FLOAT y1, FLOAT z1);	// min , max

	void		AddPoint(const VEC3* pV);
	void		AddPoint(FLOAT x, FLOAT y, FLOAT z);

	VEC3		Extent() const;
	void		Edge(VEC3* pvcEdge);											// needs VEC3 * 8 array
	void		Line(VEC3* pvcLine);											// needs VEC3 * 2 array
	VEC3		Center() const;

	INT			IsInside(const VEC3* pV);
	void		Repair();

	INT   		operator==(const LCX_AABB& v) const;
	INT   		operator!=(const LCX_AABB& v) const;
};




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// axis aligned bound box has cube, center position, radius, and its ownwer.

struct LCX_ABX
{
	LCX_CUBOID	c;
	VEC3		p;			// center position
	FLOAT 	r;			// radius
	LC_HANDLE	o;			// Owner of Bound Box

	LCX_ABX	();
	LCX_ABX	(const VEC3* Min, const VEC3* Max, LC_HANDLE _pOwn=NULL);
	
	void		Set(const VEC3* Min, const VEC3* Max);
	void		Set(const VEC3* Min, const VEC3* Max, LC_HANDLE _pOwn);

	void		Owner(LC_HANDLE _pOwn);
	LC_HANDLE	Owner();
	void		Color(COLOR32 dColor);
	COLOR32		Color();

	VEC3*		Min() const;
	VEC3*		Max() const;
	VEC3*		Center() const;
	VEC3*		Demension() const;
	FLOAT		Radius();
};



//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
//

struct LCX_ABXPCK																//  Picking Aligned Axis bound box
{
	VEC3		pck;															// Get Position
	LCX_ABX*	pbb;															// Bound Box Pointer
	FLOAT		dist;															// Distance From Camera

	LCX_ABXPCK	();
	LCX_ABXPCK	(const VEC3& vcP, LCX_ABX* _pBnd, FLOAT _fD);
};




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// index + position

struct TLC_IDX_POS																// index + position
{
	LCXVEC3i	idx;															// indecies x, y, z= other index in block
	LCXVECTOR3	pos;															// position

	TLC_IDX_POS();
	TLC_IDX_POS(INT X, INT Y, INT Z, const LCXVECTOR3& P);
};




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// 2D RECT info

struct TLCX_RECT2D
{
	LCXRECT		r;																// rect
	LCXVECTOR2	s;																// scaling
	LCXVECTOR2	p;																// position

	TLCX_RECT2D();
	TLCX_RECT2D(const TLCX_RECT2D& v);
	TLCX_RECT2D(const LCXRECT&);
	TLCX_RECT2D(const LCXRECT& rct
			  , const LCXVECTOR2& scl
			  , const LCXVECTOR2& pos);
};




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8


INT   LcMath_TriUV             ( FLOAT* fu, FLOAT* fv, const VEC3* p					// uv value from triangle p = p0 + fu*(p1-p0) + fv*(p2-p0)
							  , const VEC3* p0, const VEC3* p1, const VEC3* p2);

void  LcMath_TriTranslate      (LCX_TRI* Out, const VEC3*, const LCX_TRI*);				// translation Triangle
void  LcMath_TriTransform      (LCX_TRI* Out, const MAT4*, const LCX_TRI*);				// transform Triangle

void  LcMath_CuboidTranslate   (LCX_CUBOID* Out, const VEC3*, const LCX_CUBOID*);		// translation edge
void  LcMath_CuboidTransform   (LCX_CUBOID* Out, const MAT4*, const LCX_CUBOID*);		// transform edge
void  LcMath_CuboidLineList    (LC_HANDLE Out, INT nChunk, const LCX_CUBOID*);			// Get Box Line

void  LcMath_CuboidABTranslate (LCX_AABB* Out,const VEC3*, const LCX_AABB*);			// translation aabb
void  LcMath_CuboidABTransform (LCX_AABB* Out,const MAT4*, const LCX_AABB*);			// transform aabb

INT   LcMath_CuboidToLine      (VEC3* Out, FLOAT* fDist, const VEC3* rayPos				// intersection diectional line(ray) to cuboid.
								, const VEC3* rayDir, const VEC3* edge);				// it return the collision position, and distance.

INT   LcMath_CuboidABCToLine   (LCX_AABC* Abc, const VEC3* rayPos, const VEC3* rayDir);	// intersection diectional line(ray) to LCX_AABC
INT   LcMath_CuboidOBCToLine   (LCX_OBBC* Obc, const VEC3* rayPos, const VEC3* rayDir);	// intersection diectional line(ray) to LCX_AABC




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8


INT   LcMath_LineCross2D       ( LCXVECTOR2* Out, const LCXVECTOR2* p);			// collision between p[0,1] and p[2,3]
INT   LcMath_LineCross2D       ( LCXVECTOR2* Out
								, const LCXVECTOR2* p0							// collision between p0,p1 and p2,p3
								, const LCXVECTOR2* p1
								, const LCXVECTOR2* p2
								, const LCXVECTOR2* p3);

INT   LcMath_Point3DtoScreen  ( VEC3* Out										// Output: 3차원 점을 카메라의 Near 평면에 투영 하기
								, const VEC3* vcIn								// Input
								, const VEC3* vcCam								// Camera pos
								, const VEC3* vcZ								// Camera Z vector
								, const MAT4*  mtVP								// View matrix * Projection Matrix
								, FLOAT fScnW									// Screen Width
								, FLOAT fScnH );								// Screen Height


INT   LcMath_MousePositionTo3D   (  VEC3* vcOut
								 , MAT4 matView
								 , MAT4 matProj
								 , FLOAT fScnW
								 , FLOAT fScnH
								 , LC_POINT2 ptMouse);

FLOAT LcMath_PointToPlaneDistance(LCXPLANE* pPn, VEC3* p1);						// the shortest distance between point and plane

FLOAT LcMath_LineToPointDistance (const LCXLINE* pL, const VEC3* pP);			// the shortest distance between point and line

INT   LcMath_LineToSphere        (VEC3* Out										// output the position
								, FLOAT* fDst									// output the shortest distance between point infinite line
								, const LCXLINE* pLine
								, const VEC3* pC								// point or center of sphere
								, const FLOAT fR);								// radius sphere

FLOAT LcMath_LineToLineDistance(												// 직선과 직선 사이의 최단 거리
									FLOAT* pSinTheta							// 직선과 직선 사이의 각도
								,	VEC3* Out									// 직선과 직선사이의 노말벡터
								,	const LCXLINE* pV1							// 직선 1
								,	const LCXLINE* pV2							// 직선 2
								);


INT   LcMath_LineToLineIntersection(											// 직선과 직선 사이의 관계 구하기: RETURN VALUE:겹처 있다면 -1, 평행 하면 -2 교차하면 1, 교차하지 않으면 최단거리의 점들을 돌려줌
										FLOAT* pSinTheta						// 직선과 직선 사이의 각도
									,	FLOAT* pDst								// 직선가 직선 사이의 최단 거리
									,	VEC3* Out								// 최단 거리의 점들
									,	const LCXLINE* pV1						// 직선 1
									,	const LCXLINE* pV2						// 직선 2
									);


FLOAT LcMath_LineToPlaneKValue(  const LCXPLANE* p1
								 , const VEC3* p2
								 , const VEC3* p3);								// K 값 구하기.


INT   LcMath_LineToTri		(	VEC3* Out										// collision position. this function returns -1(failed)/success(0)
							,	FLOAT* fDist									// Distance from pRayPos to Out
							,	VEC3* pRayPos									// Starting Ray Position
							,	VEC3* pRayDir									// Ray Direction(It must be Normalization.)
							,	VEC3* pTri
							,	INT bUseCull=LC_TRUE);


INT   LcMath_LineToTri		(	VEC3* Out										// collision position. this function returns -1(failed)/success(0)
							,	FLOAT* fDist									// Distance from pRayPos to Out
							,	const VEC3* pRayPos								// Starting Ray Position
							,	const VEC3* pRayDir								// Starting Ray Position
							,	const VEC3* p0									// Triangle 0
							,	const VEC3* p1									// Triangle 1
							,	const VEC3* p2									// Triangle 2
							,	INT bUseCull=LC_TRUE);


INT   LcMath_LineToTri		(	VEC3* Out										// collision position. this function returns -1(failed)/success(0)
							,	const	VEC3* pTri								// 삼각형
							,	const	LCXLINE* pLine							// 직선
							,	INT bRectangle=LC_FALSE							// 충돌영역을 삼각형의 확장  평행사변형으로 쓸것인지..
							,	INT positiveDir=LC_FALSE						// 직선의 방향으로만 충돌점을 구하기
							,	const VEC3* pBoundLine = NULL					// 유한 직선인 경우 양 끝 지점
							,	const VEC3* pTriNormal= NULL					// 삼각형의 Normal Vector
							);


INT   LcMath_LineToTri		(  VEC3* Out										// collision position. this function returns -1(failed)/success(0)
							, const VEC3* V0									// triangle v0. this function tests the triangle to ccw
							, const VEC3* V1									// triangle v1
							, const VEC3* V2									// triangle v2
							, const VEC3* L0									// start position of line
							, const VEC3* L										// line direction vector
							, FLOAT* pU = NULL									// Barycentric Hit Coordinates
							, FLOAT* pV = NULL									// Barycentric Hit Coordinates
							, FLOAT* pW = NULL);								// ratio with Lay Direction. if the direction vector is normalize then this value equals to distance from line start to collision position



INT   LcMath_TriangleToTriangle(VEC3* Out, VEC3* pV1, VEC3* pV2);				//삼각형 VS 삼각형 충돌
FLOAT LcMath_CircumcircleCorrect(VEC3* Out,const VEC3* pTri);					// 정확한 삼각형의 외접원
FLOAT LcMath_TriangleBoundSphere(VEC3* Out,const VEC3* pTri);					// 부정확한 삼각형의 외접원


INT   LcMath_PlaneToLine		(VEC3* Out, const LCXPLANE*,const VEC3*,const VEC3*);			// 직선과 평면과의 충돌점
INT   LcMath_PlaneToLimitedLine	(VEC3* Out, const LCXPLANE*,const VEC3*,const VEC3*);			// 2점사이의 평면

FLOAT LcMath_DistancePlane2Plane		(const LCXPLANE*, const LCXPLANE*);						// 평행한 평면사이의 최단거리
INT   LcMath_PlaneToPointRelation       (const LCXPLANE*, const VEC3*);							// 임의의 점이 평면의 위(뒤)에 있는 가 아래(앞)에 있는가?
INT   LcMath_PlaneToPointIsFront        (const LCXPLANE*, const VEC3*, FLOAT epsilon=0.0F);		// 점(구)이 평면의 앞에 있는가?

INT   LcMath_PlaneToPlaneInterSect		(const LCXPLANE*, const LCXPLANE*);						//평행하면 Dot product는 failed: -1, success: 1
INT   LcMath_PlaneToPlaneIntersectLine  (LCXLINE* Out, const LCXPLANE*, const LCXPLANE*);		// 두 평면이 교차하는 직선의 방정식 구하기. 직선 시작, 방향
FLOAT LcMath_PlaneToPointMinDistance    (const LCXPLANE*, const FLOAT*);						// 평면과 점사이의 최단 거리

INT   LcMath_IsInFrustum ( const LCXPLANE* frustum								// frustum index must be 0: NEAR, 1: far, 2: left, 3: right, 4: top, 5: bottom
						 , const VEC3* pos										// this function returns LC_OK(Success), or 0>(Failed)
						 , FLOAT eps
						 , INT bTestNear=LC_FALSE
						 , INT bTestFar=LC_FALSE);								// it is test where the position is in camera view frustum(LC_OK), out out frustum(0>)


INT LcMath_SphereToTri(		VEC3* Out											// the position of the shortest distance between sphere and triangle
						,	FLOAT* fDist										// the shortest distance between sphere and triangle
						,	const VEC3* pSphereCenter							// sphere center
						,	const FLOAT* pSphereRadius							// sphere radius
						,	const VEC3* pTri									// triangle 3 points
						,	VEC3* pTriCenter	= NULL							// bound center of triangle
						,	FLOAT* pTriRadius	= NULL							// radius of triangle bound
						,	VEC3* pTriNormal	= NULL							// normal vector of triangle
						);


INT LcMath_SphereToSphere(	const VEC3* pSphereCenter1							// center of sphere 1
						,	const FLOAT* pSphereRadius1							// radius of sphere 1
						,	const VEC3* pSphereCenter2							// center of sphere 2
						,	const FLOAT* pSphereRadius2							// radius of sphere 2
						);





//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Simple Triangle, Cuboid transform

INT   LcMath_CuboidAABBToLine	( VEC3* vcOut, const VEC3* pMin, const VEC3* pMax
								, LCXLINE* pLine, INT positiveDir=LC_TRUE);		// Line의 진행 방항으로 충돌할 것인가?
INT   LcMath_CuboidAABBToLine	( VEC3* vcOut, const LCX_AABB* cube, const LCXLINE* line
								, INT positiveDir=LC_TRUE);
void  LcMath_CuboidAABBLineList	( LC_HANDLE Out,INT nChunk,const LCX_AABB* In);	// Get Hexagon Line
INT   LcMath_CuboidToSphere		( const LCX_CUBOID* pHexa
								, const VEC3* pPoint							// sphere center
								, FLOAT fRadius=0.f);							// sphere radius
INT   LcMath_CuboidToTri		( const LCX_CUBOID* c, const LCX_TRI* pTri);	// Collision Hexa to Tri
INT   LcMath_CuboidToH			( const LCX_CUBOID* c1, const LCX_CUBOID* c2);	// Collision Hexagon to Hexagon

INT   LcMath_CylinderToLine		( VEC3* Out										// 원통과 직선의 충돌: Intersection point
								, const LCXCYLINDER* pV1						// Input Cylinder
								, const LCXLINE* pV2							// Input Line
								, const VEC3* pV3 = NULL);						// Input Line Boundary
INT   LcMath_CylinderToTri		( VEC3* Out										// 원통과 삼각형의 충돌
								, const LCXCYLINDER* pV1						// Input Cylinder
								, const VEC3* pV2);								// Input Triangle
INT   LcMath_CylinderToTri		( VEC3* Out										// 원통과 삼각형의 충돌 원통의 중심선이 삼각형과 충돌안하면 return (nCnt+1)<<2;을 함으로 주의!!!
								, const LCXCYLINDER* pV1						// Input Cylinder
								, const LCX_PCK* pV2							// Input Bound Triangle
								, INT bRectangle=LC_FALSE						// 충돌영역을 삼각형의 확장 평행사변형으로 쓸것인지..
								, INT positiveDir=LC_FALSE						// 직선의 방향으로만 충돌점을 구하기
								, const VEC3* pBoundLine = NULL					// 유한 직선인 경우 양 끝 지점
								, const VEC3* pTriNormal= NULL);				// 삼각형의 Normal Vector


#endif

