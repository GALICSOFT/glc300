// Interface for the 3D utilities classes.
//
////////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER)
  #pragma once
#endif

#ifndef _ILCX_Entity_H_
#define _ILCX_Entity_H_

#include <LcType.h>
#include <LcBase.h>


enum ELCX_ENTITY
{
	// Attribute set/get for transfrom
	LCX_TM_OBJ				= 0xA001,											// LCXTRANSFORM. get pointer
	LCX_TM_OBJ_PT			= 0xA002,											// LCXTRANSFORM. set/get
	LCX_TM_SCALING			= 0xA003,											// float3.   Set/Get Model scaling
	LCX_TM_ROTATION			= 0xA004,											// float4.   Set/Get Euler angle(x,y,z) and multiple order of rotation matrix x,y,z.
	LCX_TM_POSITION			= 0xA005,											// float3.   Set/Get Model position
	LCX_TM_WORLD			= 0xA006,											// float4x4. Set/Get: World Matrix
	LCX_TM_WORLD_PT			= 0xA007,											// float4x4. Get: World Matrix pointer
	LCX_TM_ZVALUE			= 0xA008,											// float.    Get: Z value for camera

	// attribute set/get time
	LCX_TIME_ADVANCE		= 0xA101,											// to advance the current time(DOUBLE)
	LCX_TIME_DELTA			= 0xA102,											// delta time(DOUBLE) for linear sequece or animation delta time
	LCX_TIME_CURRENT		= 0xA103,											// Current Time (DOUBLE)
	LCX_TIME_SPEED			= 0xA104,											// animation speed. curent_time += eplased_time * time_speed
};


//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Grid and XYZ Axis Line

DCL_INTERFACE ILCX_Entity : public ILC_Object
{
	DCL_CLASS_DESTROYER(	ILCX_Entity	);

	virtual INT		Query(char* sCmd, LC_HANDLE pData)=0;
	//virtual INT	Desc(LC_HANDLE) =0;											// It needs TLC_GEO*

	virtual INT		Scaling (const LCXVECTOR3*) =0;								// float3
	virtual INT		Rotation(const LCXVECTOR4*) =0;								// float4 euler angle of rotation x, y, z, and w = rotation order ROT_ZXY...
	virtual INT		Position(const LCXVECTOR3*) =0;								// float3

	virtual CONF(LCXVECTOR3*) Scaling () =0;
	virtual CONF(LCXVECTOR4*) Rotation() =0;
	virtual CONF(LCXVECTOR3*) Position() =0;

	virtual INT		FrameMove() =0;
	virtual void	Render   () =0;
};

typedef	ILCX_Entity*	PLCX_ENTITY;


// Create Entity Instance
#define LCXCMD_ENTITY_AXIS		(char*)"Entity Axis"
#define LCXCMD_ENTITY_AXGZ		(char*)"Entity AxGizmo"
#define LCXCMD_ENTITY_GRID		(char*)"Entity Grid"
#define LCXCMD_ENTITY_CUBE		(char*)"Entity Cube"
#define LCXCMD_ENTITY_SPHERE	(char*)"Entity Sphere"
#define LCXCMD_ENTITY_CYLINDER	(char*)"Entity Cylinder"
#define LCXCMD_ENTITY_ROADER	(char*)"Entity Roader"

// set/get attribute
#define LCXQRY_SET_DIFFUSE		(char*)"Set Diffuse Color"
#define LCXQRY_GET_DIFFUSE		(char*)"Get Diffuse Color"
#define LCXQRY_SET_CUBE			(char*)"Set Cube"
#define LCXQRY_GET_CUBE			(char*)"Get Cube"


// TLC_ARGS for Entity
// LCXCMD_ENTITY_AXIS: float x, y, z
// LCXCMD_ENTITY_AXGZ: float width
// LCXCMD_ENTITY_AXGZ: float width
// LCXCMD_ENTITY_GRID: no args
// LCXCMD_ENTITY_CUBE: float x, y, z
// LCXCMD_ENTITY_SPHERE: float radius, int segment
// LCXCMD_ENTITY_CYLINDER: float radius, float height, int segment, int start
// LCXCMD_ENTITY_ROADER: 5args. float cell width, vec3 line0 begin, end, line1 begin end

INT LcxEnt_CreateEntity(char* sCmd, PLCX_ENTITY* pOut, PLC_ARGS arg = NULL);




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Interface for the ILCX_Camera class.

enum ELCX_CAMERA
{
	LCX_CAM_NONE	=0,															//
	LCX_CAM_FIRST	,															// 1st Person
	LCX_CAM_THIRD	,															// 3rd Person
	LCX_CAM_2D		,															// 2d camera
	LCX_CAM_YAW		= 0x00101,													// Get the yaw angle for 3d person camera
	LCX_CAM_PITCH	= 0x00102,													// Get the pitch angle for 3d person camera
};

struct TXDSC_CAMERA
{
	INT			nType;															// ELCX_CAMERA
	FLOAT		fFov;															// Projection Matrix: Field of View. 2D is Otho view and this valus is zero
	FLOAT		fNear, fFar;													// Projection Matrix: Near, Far
	FLOAT		fScnW, fScnH;													// Projection Matrix: View Screen w, h

	LCXVECTOR3	vEye ;															// View Matrix: Camera Position X,Y  and 3D:Z.  2d  does not use the z-coordinate
	LCXVECTOR3	vLook;															// View Matrix: Camera Look At Position X,Y and 3D:Z
	LCXVECTOR3	vUp  ;															// View Matrix: Camera Up Vector X,Y  and 3D:Z
};


// Single Camera
DCL_INTERFACE ILCX_Camera : public ILC_Object
{
	DCL_CLASS_DESTROYER(	ILCX_Camera	);

	virtual INT		Query(char* sCmd, LC_HANDLE pData)=0;
	virtual UINT	Type()=0;
	virtual INT		Desc(LC_HANDLE) =0;											// It needs TXDSC_CAMERA*	pointer address!!!

	virtual INT  	SetAttrib(UINT dCmd, LC_HANDLE pData)=0;					// Extended the Query. set the attribute value
	virtual INT  	GetAttrib(UINT dCmd, LC_HANDLE pData)=0;					// Extended the Query. get the attribute value

	virtual INT		Update()=0;													// Setup View and Projection Matrix of Camera
																				// Set Parameter
	virtual INT		Param    (const TXDSC_CAMERA*)=0;							// setup the camera
	virtual INT		MatrixViw(const LCXMATRIX*  )=0;							// set with the view matrix.
	virtual INT		MatrixPrj(const LCXMATRIX*  )=0;							// set with the projection matrix.

	virtual INT		Eye      (const LCXVECTOR3*, INT=0)=0;						// set the eye vector parameter. 2nd parameter is for 3rd person camera
	virtual INT		Look     (const LCXVECTOR3*, INT=0)=0;						// set the look at vector parameter. 2nd parameter is for 3rd person camera
	virtual INT		Up       (const LCXVECTOR3* )=0;							// set the up vector parameter.
																				// Get value
	virtual CONF(TXDSC_CAMERA*) Param		 ()  =0;							// get the releated view, projection matrix parameter.
	virtual CONF(LCXMATRIX*	 ) MatrixViw	 ()  =0;							// get the view matrix.
	virtual CONF(LCXMATRIX*	 ) MatrixViwI	 ()  =0;							// get the inverse view matrix.
	virtual CONF(LCXMATRIX*  ) MatrixPrj	 ()  =0;							// get the projection matrix.
	virtual CONF(LCXVECTOR3* ) Eye			 ()  =0;							// get the eye vector.
	virtual CONF(LCXVECTOR3* ) Look			 ()  =0;							// get the look at vector.
	virtual CONF(LCXVECTOR3* ) Up			 ()  =0;							// get the up vector.

	virtual CONF(LCXVECTOR3* ) AxisX		 ()  =0;
	virtual CONF(LCXVECTOR3* ) AxisY		 ()  =0;
	virtual CONF(LCXVECTOR3* ) AxisZ		 ()  =0;

	virtual CONF(LCXPLANE*   ) FrustumPlanes ()  =0;
	virtual CONF(LCXVECTOR3* ) FrustumPoints ()  =0;
	virtual INT		IsInFrustum(  LCXVECTOR3* pos
								, FLOAT eps
								, INT bTestNear=LC_FALSE
								, INT bTestFar =LC_FALSE)=0;					// it is test where the position is in camera view frustum(LC_OK), out out frustum(0>)

	// Action
	virtual INT		MoveSideward(FLOAT fSpeed)=0;								// 1st: move sideward. 3rd person: rotation + increase/decreate for x direction
	virtual INT		MoveForward	(FLOAT fSpeed,FLOAT fY=1)=0;					// 1st: move forward. 3rd person: zoom in/out
	virtual INT		MoveUpward  (FLOAT fSpeed)=0;								// 1st: move upward. 3rd person: rotation + increase/decrease the height

	virtual INT		RotateYaw	(FLOAT fDelta, FLOAT fSpeed)=0;
	virtual INT		RotatePitch	(FLOAT fDelta, FLOAT fSpeed)=0;
	virtual INT		RotateRoll	(FLOAT fDelta, FLOAT fSpeed)=0;					// for 2d Camera and few 3D application


	// write the view/projection matrix to rendering pipe line. just only 3d camera
	virtual INT		TransformViw() =0;											// setup the viewing matrix in rendering pipe line
	virtual INT		TransformPrj() =0;											// setup the projection matrix in rendering pipe line
};

typedef ILCX_Camera*	PLCX_CAMERA;

// Create Camera
//  sCmd        - absolutely, you must set the value to Null.
//  TLC_ARGS
//    arg0:LC_HANDLE - TXDSC_CAMERA pointer. NULL is default camera for 3d.
INT LcxEnt_CreateCamera(char* sCmd, PLCX_CAMERA* pOut, PLC_ARGS arg);




#if !defined(_LC_ORG_SRC_)
//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Game Model Interface

enum ELCX_MDL
{
	LCXM_FRAME_INTERVAL		= 40,												// Default Animation Time Interval(40ms==>25Frame)

	// state
	LCXM_ST_ACTIVE			= 0x0000,											// Query active state
	LCXM_ST_UPDATE			= 0x0001,											// Enable update state
	LCXM_ST_RENDER			= 0x0002,											// Enable rendering state

	// Resource Type: RscType()
	LCXM_SRC_ID				= 0x0003,											// Source file id(name). it has not file extension

	// Attributes...
	LCXM_CURRENT_FRAME		= 0x0103,											// Current Frame(FLOAT)
	LCXM_REPEAT_COUNT		= 0x0104,											// repeat count (INT). NULL is infinite
	LCXM_ANIMATION			= 0x0105,											// Set Current Animation by name. Get current animation info
	LCXM_ANIMATION_ABS		= 0x0106,											// Set/Get Change the Current Animation Immediately. you use the LC_ARG4 {name, (LC_HANDLE)index}
	LCXM_ANIMATION_COUNT	= 0x0107,											// Get animation count for tdm and mds
	LCXM_ANIMATION_INDEX	= 0x0108,											// Get animation info by index for tdm and mds
	LCXM_ANIMATION_NAME		= 0x0109,											// Get animation info by name for tdm and mds
								
	LCXM_LAYER_MATRIX		= 0x0112,											// Updated Layer Matrix
	LCXM_LAYER_MATRIX_PT	= 0x0113,											// Updated Layer Matrix Address
	LCXM_GEOMETRY_MATRIX	= 0x0115,											// Updated Geometry Matrix
	LCXM_GEOMETRY_MATRIX_PT	= 0x0116,											// Updated Geometry Matrix Address
								
	LCXM_LOOP_SECTION		= 0x0121,											// Animation Loop Section
	LCXM_FRAME_INDEX		= 0x0122,
	LCXM_FRAME_INDEX_ABSOLUTE=0x0123,
	LCXM_MAX_ANI_BLENDING	= 0x0124,											// Skinning Animation Matrix Blending Number
	LCXM_FRAME_SPEED		= 0x0125,											// Animation Frame Speed (FLOAT)
	LCXM_REPEATE_COUNT		= 0x0126,											// Repeate Count(INT)
	LCXM_END_FREEZE_FRAME	= 0x0127,											// End Freeze Frame
								
	LCXM_BOUNDING_RECT		= 0x0141,											// Bounding rect. only 2d model. it needs LCXRECT
	LCXM_BOUNDING_BOX		= 0x0142,											// Bounding box
	LCXM_BOUNDING_SPHERE	= 0x0143,											// Bounding sphere
	LCXM_DIFFUSE_COLOR		= 0x0146,											// Diffuse Color. It needs FLOAT4 RGBA color.

	// Command Execution: Set/GetAttrib()
	LCXM_EXEC_TEXTURE_LOAD	= 0x0151,											// Texture Loading Command.
	LCXM_TEXTURE_LIST_NUMBER= 0x0152,											// Texture List Number
	LCXM_TEXTURE_LIST_NAME	= 0x0153,											// Texture Name List
	LCXM_TEXTURE_LIST_POINTER=0x0154,											// Texture Pointer List
	LCXM_SPRITE_LAYER		= 0x0155,											// Set/Get Sprite Layer
	LCXM_CREAE_COLONE		= 0x0156,											// Create instance(clone) from original instance for TDM. GetAttrib
	LCXM_EFFECT_POINTER     = 0x0157,											// set/get PLC_EFFECT
};




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Three-dimensional Game Model Interface

struct TXDSC_MDL																// Model info
{
	char*		src_n	;														// Resource Name for Search. Model name
	INT			mdl_t	;														// LC_OBJ_{MODEL3D|SLD|RGD|SKN}
	INT			mdl_m	;														// Number of Material
	INT			mdl_g	;														// Number of Geometry
	LCXVECTOR3	mdl_s	[2];													// dimension min, max vertex position
	INT			frm_b	;														// Begin Frame
	INT			frm_e	;														// End Frame
	INT			frm_s	;														// Frames per one scecond
	INT			frm_t	;														// Tick per one Frame
};

struct TLCXM_TRC																// Animation track
{
	INT			nF		;														// Frame
	LCXMAT4X3	tm		;														// ANIMATION MATRIX

	TLCXM_TRC();
	TLCXM_TRC(INT F, const LCXMAT4X3* _tm);
};

struct TLCXM_ATM																// Local and world transform animation matrix
{
	INT			nAtm	;														// Count of Animation track matrix
	TLCXM_TRC*	vAtm	;														// list of Animation track matrix

	TLCXM_ATM();
	~TLCXM_ATM();
};


DCL_INTERFACE ILCX_Mdl : public ILC_Object
{
	DCL_CLASS_DESTROYER(	ILCX_Mdl	);

	virtual INT		Query(char* sCmd, LC_HANDLE pData)=0;
	virtual UINT	RscType() =0;
	virtual INT		Desc(LC_HANDLE) =0;											// It needs TXDSC_MDL*	pointer address!!!
	virtual CONC	Name() =0;

	virtual INT		SetAttrib(UINT dCmd, LC_HANDLE pData) =0;
	virtual INT		GetAttrib(UINT dCmd, LC_HANDLE pData) =0;

	virtual	INT		FrameMove() =0;
	virtual void	Render() =0;
																				// Position, rotation, scaling for world transform matrix. same to Set/GetAttrib( LCXM_{POSITION|LCX_TM_ROTATION|LCX_TM_ROTATION}
	virtual INT		Scaling (const LCXVECTOR3*) =0;								// set the scaling float3
	virtual INT		Rotation(const LCXVECTOR4*) =0;								// set the rotation info. float4 euler angle of rotation x, y, z, and w = rotation order ROT_ZXY...
	virtual INT		Position(const LCXVECTOR3*) =0;								// set the position. float3
	virtual INT		Epsilon (const LCXVECTOR4*) =0;								// set the epsilon. float4

	virtual CONF(LCXVECTOR3*) Scaling  () =0;									// get the scaling
	virtual CONF(LCXVECTOR4*) Rotation () =0;									// get the rotation
	virtual CONF(LCXVECTOR3*) Position () =0;									// get the position
	virtual CONF(LCXVECTOR4*) Epsilon  () =0;									// get the epsilon
	virtual FLOAT             Zdepth   () =0;									// get the rendering z-value( dot(eye - position, camera z)
	virtual CONF(LCXVECTOR3*) Dimension() =0;									// get the dimension min, max of object
};

typedef	ILCX_Mdl*	PLCX_MDL;

// Create 3D Model
//  sCmd        - absolutely, you must set the value to Null.
//  TLC_ARGS
//    arg0:char*    file name       identity name

INT LcxEnt_CreateMdl(char* sCmd, PLCX_MDL* pOut, PLC_ARGS arg);




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Game Animation 3D Models Interface

#if !defined(_LC_MDS_SRC_)

DCL_INTERFACE	ILcx_Mds;
typedef			ILcx_Mds*		PLCX_MDS;


struct TLCXM_DISC
{
	char			dsk_name[LC_RSC_NAME];										// disc name
	INT				dsk_bgn	;													// Begin Frame
	INT				dsk_end	;													// End Frame
	INT				dsk_spd	;													// Frames per one scecond
	INT				dsk_tck	;													// Tick per one Frame

	TLCXM_ATM*		atm_lst	;													// Local and world transform animation matrix
	LCXVECTOR3**	vtx_pos	;
	LCXVECTOR3**	vtx_nor	;

	void			Destroy(INT nGeo);

	TLCXM_DISC();
	~TLCXM_DISC();
};


struct TLCXM_ANI
{
	char			ani_name[LC_RSC_SID];										// animation name
	char			ani_dsc[LC_RSC_NAME];										// disc name
	INT				ani_bgn	;													// Begin Frame
	INT				ani_end	;													// End Frame
	TLCXM_ANI();
	TLCXM_ANI(const TLCXM_ANI&);
	TLCXM_ANI& operator=(const TLCXM_ANI& r);
};


struct TLCXM_LNK
{
	char			lnk_name[LC_RSC_SID];										// link name
	INT				lnk_bone;													// link to bone(geo) index
	LCXQUATERNION	lnk_rot	;													// Count of Animation record
	LCXVECTOR3		lnk_trn	;

	TLCXM_LNK();
};

struct TLCXM_EVN
{
	char			evn_name[LC_RSC_SID];										// event name
	char			evn_ani	[LC_RSC_SID];										// animation name
	char			evn_dsc [LC_RSC_NAME];										// event description
	INT				evn_frm	;													// event frame
	LC_HANDLE		evn_lsn	;													// event lister handle

	TLCXM_EVN();
};

struct TXDSC_MDS
{
	char*			src_n	;													// Resource Name for Search. Model name
	INT				mdl_t	;													// LC_OBJ_{MODEL3D|SLD|RGD|SKN}
	INT				mdl_m	;													// Number of Material
	INT				mdl_g	;													// Number of Geometry
	LCXVECTOR3		mdl_s	[2];												// dimension min, max vertex position

	INT				num_dsc	;													// animation disc count
	INT				num_ani	;													// animation count
	INT				num_lnk	;													// linkage number
	INT				num_mpp	;													// mapping texture number
	INT				num_evn	;													// event listener count

	TXDSC_MDS();
};


DCL_INTERFACE ILcx_Mds : public ILC_Object
{
	DCL_CLASS_DESTROYER(	ILcx_Mds	);
	
	virtual INT		Query(char* sCmd, LC_HANDLE pData)=0;
	virtual UINT	RscType() =0;
	virtual INT		Desc(LC_HANDLE) =0;											// It needs TXDSC_MDS*	pointer address!!!
	virtual CONC	Name() =0;

	virtual INT		SetAttrib(UINT dCmd, LC_HANDLE pData) =0;
	virtual INT		GetAttrib(UINT dCmd, LC_HANDLE pData) =0;

	virtual	INT		FrameMove() =0;
	virtual void	Render() =0;
																				// Position, rotation, scaling for world transform matrix. same to Set/GetAttrib( LCXM_{POSITION|LCX_TM_ROTATION|LCX_TM_ROTATION}
	virtual INT		Scaling (const LCXVECTOR3*) =0;								// set the scaling float3
	virtual INT		Rotation(const LCXVECTOR4*) =0;								// set the rotation info. float4 euler angle of rotation x, y, z, and w = rotation order ROT_ZXY...
	virtual INT		Position(const LCXVECTOR3*) =0;								// set the position. float3

	virtual CONF(LCXVECTOR3*) Scaling  () =0;									// get the scaling
	virtual CONF(LCXVECTOR4*) Rotation () =0;									// get the rotation
	virtual CONF(LCXVECTOR3*) Position () =0;									// get the position
	virtual FLOAT             Zdepth   () =0;									// get the rendering z-value( dot(eye - position, camera z)
	virtual CONF(LCXVECTOR3*) Dimension() =0;									// get the dimension min, max of object
};

// Create MDS
//  sCmd        - absolutely, you must set the value to Null.

INT LcxEnt_CreateMds(char* sCmd, PLCX_MDS* pOut, char* fileName);


#endif




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// 2d Texture Animation Sequence List Interface

struct TLC_TDAREC
{
	char		name	[LC_RSC_SID];											// Sequence Name
	LCXVECTOR3	pos		[4];													// position of vertices. primitive type is triangle fan
	LCXVECTOR2	tex		[4];													// texture coordinate uv of vertices. primitive type is triangle fan

	TLC_TDAREC();
	LCXVECTOR2	GetWH();														// get the width and height
	LCXVECTOR2	GetXY();														// get the position
};


struct TXDSC_TDA
{
	char		tda_s[LC_RSC_NAME];												// name
	INT			tda_l;															// list count
	INT			tda_w;															// image width
	INT			tda_h;															// image height
	char		tda_t[8];														// texture file extension
};

DCL_INTERFACE ILCX_Tda : public ILC_Object
{
	DCL_CLASS_DESTROYER( ILCX_Tda );

	virtual INT		Release(INT bDecreaseRefCount=LC_TRUE)=0;
	virtual INT		Query(char* sCmd, LC_HANDLE pData)=0;
	virtual UINT	RscType(){	return LC_OBJ_TDA; }
	virtual INT		Desc	(LC_HANDLE) =0;										// It needs TXDSC_TDA* address
	virtual CONC	Name	() =0;												// return the name. same to tda_s

	virtual INT		GetRecIdx(char* recName)=0;									// get the record index. if NULL == recName then return the count of Records
	virtual TLC_TDAREC* GetRec(char* recName)=0;								// get the record pointer with name
	virtual TLC_TDAREC* GetRec(INT recIdx)=0;									// get the record pointer with index

	virtual PLC_TEXTURE Texture()=0;											// get the texture
};


typedef	ILCX_Tda*	PLCX_TDA;

// Create TDA
//  sCmd        - absolutely, you must set the value to Null.

INT LcxEnt_CreateTda(char* sCmd, PLCX_TDA* pOut, char* fileName);




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Two-dimensional Game Model Interface

struct TLCX_ANI_TIME2D															// 2D sprite animation time squence
{
	INT			nAniC	;														// Current Animation
	INT			nAniS	;														// Current Sequence for current Animation
	DOUBLE		time_b	;														// Begin Time
	DOUBLE		time_c	;														// Current Time

	TLCX_ANI_TIME2D() : nAniC(0), nAniS(0), time_b(0), time_c(0){}
};


// Game Model Interface
DCL_INTERFACE ILCX_Tdm : public ILC_Object
{
	DCL_CLASS_DESTROYER( ILCX_Tdm );

	virtual INT		Query(char* sCmd, LC_HANDLE pData)=0;
	virtual UINT	RscType(){	return LC_OBJ_TDM; }

	virtual	INT		FrameMove()=0;
	virtual void	Render()=0;

	// Rendering Position
	virtual INT		Position(const LCXVECTOR2*)=0;							// position: float2
	virtual INT		Rotation(const LCXVECTOR3*)=0;							// rotation: float3 rotation center(x,y) + rotation angle(z: radian)
	virtual INT		Scaling (const LCXVECTOR2*)=0;							// scaling : float2
};

typedef	ILCX_Tdm*	PLCX_TDM;

// Create TDM
//
//  sCmd        - absolutely, you must set the value to Null.
//  TLC_ARGS
//    arg0:UINT - Resource Type: LC_SRC_T_{FILE | MEM | BUF, RSC}
//
//                             File                 Memory
//    arg1:char*,LC_HANDLE  file name            identity name
//    arg2:LC_HANDLE        Layer pointer        Layer pointer
//    arg3:INT              TDSC_TEXTURE pointer  TDSC_TEXTURE pointer
//    arg4:INT                                   Memory address
//    arg5:INT                                   Memory size
//
//    Layer pointer. Layer pointer(2D sprite pointer) can be setup to SetAttrib(LCXM_SPRITE_LAYER)

INT LcxEnt_CreateTdm(char* sCmd, PLCX_TDM* pOut, PLC_ARGS arg);




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// 2d model sequnce

DCL_INTERFACE ILCX_Tds : public ILC_Object
{
	DCL_CLASS_DESTROYER( ILCX_Tds );

	virtual UINT	RscType(){	return LC_OBJ_TDS; }

	virtual	INT		FrameMove()=0;
	virtual void	Render()=0;

	// Rendering Position
	virtual INT		Position(const LCXVECTOR2*)=0;							// position: float2
	virtual INT		Rotation(const LCXVECTOR3*)=0;							// rotation: float3 rotation center(x,y) + rotation angle(z: radian)
	virtual INT		Scaling (const LCXVECTOR2*)=0;							// scaling : float2
};

typedef	ILCX_Tds*	PLCX_TDS;

// Create TDS Instance
//
//  sCmd        - absolutely, you must set the value to Null.
//  TLC_ARGS
//    arg0:char*,LC_HANDLE  file name            identity name
//    arg1:LC_HANDLE        Layer pointer        Layer pointer
//    arg2:INT              TDSC_TEXTURE pointer  TDSC_TEXTURE pointer
//
//    Layer pointer. Layer pointer(2D sprite pointer) can be setup to SetAttrib(LCXM_SPRITE_LAYER)

INT LcxEnt_CreateTds(char* sCmd, PLCX_TDS* pOut, PLC_ARGS arg);




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Graphic user interface.
// Gui Type: Dialog, Button, List, Combo box, Static, Edit Box, Check Box, Radio button, slide bar
// Dialog: Only Popup window
// Data structure: Tree Structure

enum ELX_UI
{
	LXUI_MAX_NAME		= LC_DEFAULT_NAME,										// Max Name Length
	LXUI_MAX_EVENT		= 1024  ,												// UI max event

	// GUI type
	LXUI_TYPE			= 0x3100,												// GuiDefault Type
	LXUI_DIALOG			= 0x3101,												// Dialog
	LXUI_SBUTTON		= 0x3102,												// System Button
	LXUI_BUTTON			= 0x3103,												// Button
	LXUI_EDIT			= 0x3104,												// Edit
	LXUI_LIST			= 0x3105,												// List
	LXUI_VSCROLL		= 0x3106,												// vertical scroll button.
	LXUI_HSCROLL		= 0x3107,												// horizon scroll button.
	LXUI_CBUTTON		= 0x3108,												// cool down timer button
	LXUI_MARKER			= 0x3109,												// Market. No event
	LXUI_STICKER		= 0x310A,												// Sticker, string or image. No event
	LXUI_ANIICON		= 0x310B,												// Animation icon. animation gui
	LXUI_SPRGRSS		= 0x310C,												// Scaling prograsss bar.

	// GUI State
	LXUI_DISABLE		= 0x3000,												// Action and Event Disable
	LXUI_ENABLE			= 0x3001,												// Actin and Event Enable
	LXUI_HIDE			= 0x3010,												// Hide
	LXUI_SHOW			= 0x3011,												// Show
	LXUI_ACTIVE			= 0x3012,												// Show and Active
	LXUI_INACTIVE		= 0x3013,												// Inactive
	LXUI_DRAG			= 0x3014,												// Drag

	// Event Message or Status Value
	LXUI_EVNT_NONE		= 0x0000,												// None event
	LXUI_EVNT_DOWN		= 0x0001,												// Mouse(touch) down
	LXUI_EVNT_UP		= 0x0002,												// Mouse(touch) up
	LXUI_EVNT_PRESS		= 0x0003,												// Mouse(touch) pressed
	LXUI_EVNT_MOVE		= 0x0010,												// Move(drag)
	LXUI_EVNT_OVER		= 0x0020,												// Mouse(touch) over
	LXUI_EVNT_CLOSE		= 0x0080,												// Close Event

	// Member Value
	LXUI_INFO			= 0x3301,												// Gui Info
	LXUI_ID				= 0x3302,												// id. it needs unsigned int
	LXUI_NAME			= 0x3303,												// Name
	LXUI_POSITION		= 0x3304,												// Read/Write Gui Position
	LXUI_EXTEND			= 0x3305,												// setup the vertex with extend value
	LXUI_TEXTURE		= 0x3307,												// setup the texture
	LXUI_FONT			= 0x3308,												// setup the Font. it needs TLC_FONT
	LXUI_TEXT			= 0x3309,												// get the Font string. it must be need font. if there is not exist the font, then the return value is null.
	LXUI_CHILD			= 0x330A,												// get the child GUI in dialog. it needs int ID value and pointer. ex) PLCX_UI pChild = (PLCX_UI)0x001; pDialog->GetAttrib(LXUI_CHILD, &pChild);// 0x001 is exam id.
	LXUI_COOLTIME		= 0x3311,												// Cool down time millisecond
};


DCL_INTERFACE		ILCX_Ui;
typedef ILCX_Ui*	PLCX_UI;


struct TXDSC_UI																	// Gui infomation of instance
{
	LC_QID		qid			;													// qid
	char		name		[LXUI_MAX_NAME];									// Name
	UINT		clzz		;													// class: LXUI_{DIALOG|SYSBUTTON|BUTTON|EDIT|LIST|STATIC}
	PLCX_UI		parent		;													// Parent Gui Window
	LCXRECT		rc_area		;													// Full Region area or event Rect(left, top, width, height)
	LCXRECT		rc_aux0		;													// auxiliary 1 area. tbar bar Rect or mouse normal image rect or etc1..
	LCXRECT		rc_aux1		;													// auxiliary 2 area. mouse over image rect or etc2..
	LCXRECT		rc_aux2		;													// auxiliary 3 area. mouse press image rect or etc3..
	INT			st_cur		;													// current state
	INT			st_act		;													// activate
	FLOAT		t_alpha		;													// current alpha

	TXDSC_UI();
	TXDSC_UI(const TXDSC_UI&);
	TXDSC_UI& operator = (const TXDSC_UI&);
};

struct TLCXUI_EXT																// Extend Gui for setup TXDSC_UI field
{
	INT			img_w		;													// source image Width
	INT			img_h		;													// source image Height
	LC_HANDLE	ext 		;													// Full Region area or event Rect(left, top, width, height). exceptionally cooltimer,..
	LC_HANDLE	aux0		;													// auxiliary 0 area. tbar bar Rect or mouse normal image rect or etc1... exceptionally cooltimer,..
	LC_HANDLE	aux1		;													// auxiliary 1 area. mouse over image rect or etc2... exceptionally cooltimer,..
	LC_HANDLE	aux2		;													// auxiliary 2 area. mouse press image rect or etc3... exceptionally cooltimer,..

	TLCXUI_EXT();
};


DCL_INTERFACE ILCX_Ui : public ILC_Object
{
	DCL_CLASS_DESTROYER( ILCX_Ui );

	virtual INT		Release     (INT bDecreaseRefCount=LC_TRUE) =0;
	virtual UINT	RscType     () =0;											// Resource type: LXUI_DIALOG, ...
	virtual INT		Desc        (LC_HANDLE)=0;									// It needs TXDSC_UI* address

	virtual INT		Position    (const LCXVECTOR2*) =0;							// position float2
	virtual CONF(LCXVECTOR2*)   Position () =0;									// get the relative position with parent
	virtual LCXVECTOR2          PositionAbs() =0;								// get the absolute position

	virtual INT     AttachChild (PLCX_UI pChild) =0;							// Node process: Attatch child Gui
	virtual INT     DetachChild (PLCX_UI pChild) =0;							// Detatch child Gui
	virtual PLCX_UI UiParent    () =0;											// return Parent Gui
	virtual PLCX_UI UiRoot      () =0;											// return Root Gui

	virtual INT     State       () =0;											// read the gui state
	virtual void    State       (INT v) =0;										// write the gui state
	virtual INT     Text        (const char*,COLOR32 =0xFF000000) =0;			// Write the string in gui and text.
	virtual CONC    Text()      const =0;

	virtual INT		FrameMove   () =0;
	virtual void	Render      () =0;
};


// Create Dialog Instance
//     sCmd - absolutely, you must set the value to Null.
//     arg0:LC_HANDLE - TLCX_GUI* pointer. it must have GUI Type: LXUI_{DIALOG|SYSBUTTON...
//     arg1:LC_HANDLE - Extend data

INT    LcxUi_Create             ( char* sCmd, PLCX_UI* pOut, PLC_ARGS arg);
INT    LcxUi_CreateDialogFromGUT( char*	      cmd								// No Use: just null
								, PLCX_UI*    pOut								// Output dialog.
								, const char* name								// dialog name(identity)
								, const char* gutFile);							// dialog group file name(.gut)
INT    LcxUi_CreateDialogFromXML( char*	     sCmd								// No Use: just null
								, PLCX_UI*    pOut								// Output dialog.
								, const char* name								// name(identity)
								, const char* groupFile							// group file name(.grp)
								, const char* atlasFile  = NULL);				// atlas file name

INT    LcxUi_CreateIconFromXML  ( char*	      sCmd								// No Use: just null
								, PLCX_UI*    pOut								// Output animation icon ui.
								, const char* name								// name(identity)
								, const char* groupFile							// group file name(.grp)
								, const char* atlasFile  = NULL);				// atlas file name

PLC_TEXTURE LcxUi_FindTexture(const char* sName);								// find the created the texture.

INT  LcxUi_ProcSet      (PLC_ARGS _pArg);										// same to input device cannt use PLCX_INPUT. args: keyState[ubyte-256], touch0 pos(float3), touch1 pos(float3), touchdelta0(float3), touchdelta1(float3), touchstate0(int), touchstate1(int).
																				// MAKE_ARG7(args, keyState, mtsPos0, mtsPos1, mtsGrd0, mtsGrd1, mtsSt0, mtsSt1);  hr = LcxUi_ProcSet(&args);
INT  LcxUi_ProcSet      (PLC_OBJECT _pInput);									// PLCX_INPUT input device needs for messaging
INT  LcxUi_Proc         ();														// Update Gui and return the gui count which event occurred.
INT  LcxUi_Events       (PLC_EVENT* ppEvent);									// get the event list. PLC_EVENT address needs.
INT  LcxUi_DrawBegin    ();														// Rendering preprocessing for Gui
void LcxUi_Draw         ();														// Rendering All Gui
INT  LcxUi_DrawEnd      ();														// Rendering post for Gui

INT  LcxUi_Release      ();														// Release all dialog list
void LcxUi_Active       (PLCX_UI pDlg);											// Set active dialog. NULL is all dialogs are non-active
PLCX_UI LcxUi_Active    ();														// get active dialog.


//typedef vector<PLCX_UI > lsPLCXUI;
INT       LcxUi_DialogChildNumber    (PLCX_UI _pDlg);							// get the child list number.
LC_HANDLE LcxUi_DialogChildList      (INT* count, PLCX_UI _pDlg, INT clzz);		// get the child list pointer. NULL is zero size. use lsPLCXUI pointer. clzz: LXUI_TYPE, returns all attached children, but [LXUI_SBUTTON, LXUI_CBUTTON] returns children just belong to the dialog.




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Effect interface.

enum ELCX_EFFECT
{
	// Effect  type
	LCXE_PARTICLE_2D	= 0x0001,												// 2D Particle
	LCXE_PARTICLE_3D	= 0x0002,												// 3D Particle
	LCXE_TEXTURE_ANI	= 0x0004,												// Texture Animation
	LCXE_TEXTURE_BLEND	= 0x0005,												// Texture Animation blending

	// point sprite type
	LCXE_REN_POINT		= 0x0000,												// point sprite. (not supported)
	LCXE_REN_TIANGLE	= 0x0001,												// triangle type. for reduce the polygon
	LCXE_REN_QUAD		= 0x0002,												// quad type

	// member value
	LCXE_INFO			= 0x0001,												// Effect Info
};


//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// particle ...

struct TLCX_EPS_ELM																// effect particle syste element
{
	INT				idx		;													// Particle Index
	LCXCOLOR		dif		;													// diffuse Color
	LCXVECTOR2		mag		;													// Width(x) and height(y)
	FLOAT			life	;													// it_life time

	LCXVECTOR3		pos		;													// Position
	LCXVECTOR3		vlc		;													// Velocity
	LCXVECTOR3		acc		;													// Accelerator
	LCXCOLOR		clv		;													// Color Velocity

	TLCX_EPS_ELM();

	virtual INT Init  (LC_HANDLE _pInit);										// _pInit must be TXDSC_EPS or TLCX_PRT_INIT3D pointer
	virtual INT Reset (LC_HANDLE _pInit);
	virtual INT Update(LC_HANDLE _pInit);
};


struct TXDSC_EPS																// effect particle system info
{
	// particle
	INT				prt_num  ;													// Particle Number
	INT				prt_clzz ;													// Particle clazz
	INT				prt_rtype;													// Rendering type: Point sprite=0, Triangle =1 , Quad=2
	INT				prt_strd ;													// Particle stride size
	PLC_TEXTURE		prt_tex  ;													// Texture Pointer
	TLCX_EPS_ELM*	prt_lst  ;													// Particle List

	// boundary and Initial value
	LC_FLOAT8		rc_bnd	;													// particle boundary. if 2d then rect, 3d then ... user defined
	LCXRECT			rc_tex	;													// texture rect. if(-1,-1,-1-1) then all 
	LCXVECTOR3		tm_pos	;													// Position
	LCXVECTOR3		tm_vcl	;													// Velocity
	LCXVECTOR3		tm_acc	;													// Acceleration
	LC_FLOAT2		tm_rot	;													// rotation Angle, velocity
	LCXVECTOR3		tm_scl	;													// scale
	LCXVECTOR3		tm_sclv	;													// Scale Velocity

	LCXCOLOR		it_dif	;													// diffuse Color
	LCXCOLOR		it_difv	;													// diffuse Color Velocity

	LC_FLOAT2		it_life	;													// it_life, fade speed
	LC_FLOAT2		it_mag	;													// magnitude width, height

	TXDSC_EPS();
};


DCL_INTERFACE ILCX_Eps : public ILC_Object										// effect particle system
{
	DCL_CLASS_DESTROYER( ILCX_Eps );

	virtual	INT		Desc(LC_HANDLE) =0;											// It needs TXDSC_EPS* address
	virtual UINT	RscType() =0;												// Resource type: LCXE_PARTICLE_2D, ...

	virtual	INT		FrameMove()=0;
	virtual void	Render()=0;
};

typedef ILCX_Eps*	PLCX_EPS;


// Create 2d particle
//  sCmd - absolutely, you must set the value to Null.
//  TLC_ARGS
//    arg0:LC_HANDLE - Particle Info: TXDSC_EPS pointer
//    arg1:LC_HANDLE - sprite object. if null then it will call the LcVar_ReadP(LC_VAR_SPRITE) on runtime

INT LcxEnt_CreateParticle(char* sCmd, PLCX_EPS* pOut, PLC_ARGS arg);




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// effect texture animation ...

struct TXDSC_ETA																// effect texture animation info
{
	INT				sqc_stt	;													// Sequence state
	INT				sqc_idx	;													// Current Sequence Index
	INT				sqc_tot	;													// Total Sequence
	DOUBLE			time_c	;													// Current Time(millisecond)
	DOUBLE			time_d	;													// Time delta(millisecond)

	TXDSC_ETA();
};


DCL_INTERFACE ILCX_Eta : public ILC_Object										// effect texture animation interface
{
	DCL_CLASS_DESTROYER( ILCX_Eta );

	virtual UINT	RscType() { return LCXE_TEXTURE_ANI; }

	virtual INT		Query(char* sCmd, LC_HANDLE pData) =0;
	virtual	INT		Desc(LC_HANDLE) =0;											// It needs TXDSC_ETA* address
	virtual CONC	Name() =0;													// get the src name

	virtual INT		SetAttrib(UINT dCmd, LC_HANDLE pData) =0;					// Write Attribute Value
	virtual INT		GetAttrib(UINT dCmd, LC_HANDLE pData) =0;					// Read Attribute Value

	virtual INT		Scaling (const LCXVECTOR3*) =0;								// float3
	virtual INT		Rotation(const LCXVECTOR4*) =0;								// float4 euler angle of rotation x, y, z, and w = rotation order ROT_ZXY...
	virtual INT		Position(const LCXVECTOR3*) =0;								// float3

	virtual CONF(LCXVECTOR3*) Scaling () =0;
	virtual CONF(LCXVECTOR4*) Rotation() =0;
	virtual CONF(LCXVECTOR3*) Position() =0;

	virtual INT     State() =0;													// read the gui state
	virtual void    State(INT v) =0;											// write the gui state

	virtual	INT		FrameMove()=0;
	virtual void	Render()=0;
};

typedef ILCX_Eta*	PLCX_ETA;


// Create texture animation effect
//  sCmd        - absolutely, you must set the value to Null.
//  TLC_ARGS
//    arg0:LC_HANDLE - Particle Info: TXDSC_EPS pointer
//    arg1:LC_HANDLE - sprite object. if null then it will call the LcVar_ReadP(LC_VAR_SPRITE) on runtime

INT LcxEnt_CreateEta(char* sCmd, PLCX_ETA* pOut, PLC_ARGS arg);


//++5++++1+++++++++2+++++++++3+++++++++

struct TXDSC_ETB																// effect texture animation blending info
{
	LC_HANDLE		org_ins		;												// original data instance
	DOUBLE			time_c		;												// Current Time(millisecond)
	DOUBLE			time_m		;												// Tortal max elapsed Time(millisecond)
	INT				sqc_stt		;												// Sequence state

	TXDSC_ETB();
};


DCL_INTERFACE ILCX_Etb : public ILC_Object										// effect texture animation blending interface
{
	DCL_CLASS_DESTROYER( ILCX_Etb );

	virtual UINT	RscType() { return LCXE_TEXTURE_BLEND; }

	virtual INT		Query(char* sCmd, LC_HANDLE pData) =0;
	virtual	INT		Desc(LC_HANDLE) =0;											// It needs TXDSC_ETB* address
	virtual CONC	Name() =0;													// get the src name

	virtual INT		SetAttrib(UINT dCmd, LC_HANDLE pData) =0;					// Write Attribute Value
	virtual INT		GetAttrib(UINT dCmd, LC_HANDLE pData) =0;					// Read Attribute Value

	virtual INT		Scaling (const LCXVECTOR3*) =0;								// float3
	virtual INT		Rotation(const LCXVECTOR4*) =0;								// float4 euler angle of rotation x, y, z, and w = rotation order ROT_ZXY...
	virtual INT		Position(const LCXVECTOR3*) =0;								// float3

	virtual CONF(LCXVECTOR3*) Scaling () =0;
	virtual CONF(LCXVECTOR4*) Rotation() =0;
	virtual CONF(LCXVECTOR3*) Position() =0;

	virtual INT     State() =0;													// read the gui state
	virtual void    State(INT v) =0;											// write the gui state

	virtual	INT		FrameMove()=0;
	virtual void	Render()=0;
};

typedef ILCX_Etb*	PLCX_ETB;


// Create texture multi animation blending effect
//  sCmd        - absolutely, you must set the value to Null.
//  TLC_ARGS
//    arg0:LC_HANDLE - Particle Info: TXDSC_EPS pointer
//    arg1:LC_HANDLE - sprite object. if null then it will call the LcVar_ReadP(LC_VAR_SPRITE) on runtime

INT LcxEnt_CreateEtb(char* sCmd, PLCX_ETB* pOut, PLC_ARGS arg);




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Motion Sequence

enum ELCX_MSQC
{
	// Motion inv
	LCXMSQC_2D				= 0x0401,											// 2D Motion
	LCXMSQC_3D				= 0x0402,											// 3D Motion

	// Motion type
	LCXMSQC_CART_INTP		= 0x0410,											// Cartesian interpolation coordinate path
	LCXMSQC_BEZIER_INTP		= 0x0411,											// Bezier interpolation coordinate path
	LCXMSQC_HERMITE_INTP	= 0x0412,											// Hermite interpolation coordinate path

	// Member Value
	LCXMSQC_RESULT_SQC		= 0x0421,											// Sequence
	LCXMSQC_EVENT			= 0x0424,											// Event list number

	// Motion state(get) and Execution(set)
	LCXMSQC_DEFAULT			= LC_DEFAULT,										// default state. do not exeqution
	LCXMSQC_RESET			= LC_LOOP_RESET,									// start..
	LCXMSQC_PLAY			= LC_LOOP_PLAY,										// playing
	LCXMSQC_DONE			= LC_LOOP_DONE,										// end state
};


struct TXDSC_MSQC
{
	INT			sqc_clzz;														// LCXMSQC_2D , 3D
	INT			sqc_type;														// LCXMSQC_CARTESIAN, ...
	DOUBLE		time_c	;														// Current Time(millisecond)

	INT			sqc_stt	;														// Sequence state
	INT			sqc_idx	;														// Current Sequence Index
	LC_HANDLE	sqc_bgn	;														// Begin Pointer
	LC_HANDLE	sqc_end	;														// End Pointer

	TXDSC_MSQC();
};

	
// The motion sequence is action of translation, scaling,
// rotation and color variation for object with time line.
// initial conditions for motion
struct TLCX_MSQIC2D
{
	// basic sequence
	DOUBLE		time;															// time interval
	LCXVECTOR2	pos;															// position
	LCXVECTOR2	scl;															// scaling
	LCXVECTOR2	roc;															// rotation center offset =>  rot_center =  pos + ros
	FLOAT		ror;															// rotation angle(radian).
	LCXCOLOR	clr;															// color

	INT			nIdx;															// Index
	char		name[LC_RSC_SID];												// motion name or command
	INT			keys[LCXMSQC_EVENT];											// action key list or applied events

	// advanced opsition
	LCXVECTOR2	psa;															// acceleration => psa  = a(t)
	LCXVECTOR2	psv;															// velocity		=> psv += a * dt  => pos += v * dt
	LCXVECTOR2	scv;															// scaling speed  => scl += scv * dt
	FLOAT		rov;															// rotation speed.  ==>	ror += rov * dt
	LCXCOLOR	clv;															// color speed  ==> color += clv * dt

	TLCX_MSQIC2D();
	TLCX_MSQIC2D(const TLCX_MSQIC2D& v);
	TLCX_MSQIC2D(char* sName, int TimeOut=0, int* KeyList=NULL);
	TLCX_MSQIC2D& operator =(const TLCX_MSQIC2D& v);

	void Reset();
};


struct TLCX_MOSQ2D																// result Motion sequence
{
	DOUBLE		time;															// current time
	LCXVECTOR2	pos;															// position
	LCXVECTOR2	scl;															// scaling
	LCXVECTOR2	roc;															// rotation center
	FLOAT		ror;															// rotation angle(radian).
	LCXCOLOR	clr;															// color

	TLCX_MOSQ2D();
};


DCL_INTERFACE ILCX_Msqc : public ILC_Object
{
	DCL_CLASS_DESTROYER( ILCX_Msqc );

	virtual INT		Release(INT bDecreaseRefCount=LC_TRUE)=0;
	virtual INT		Query(char* sCmd, LC_HANDLE pData)=0;

	virtual	INT		Desc(LC_HANDLE) =0;											// It needs TXDSC_MSQC* address
	virtual UINT	RscType() =0;												// Resource type: LCXMSQC_2D, ...

	virtual	INT		FrameMove()=0;
};

typedef ILCX_Msqc*	PLCX_MOSQC;


// Create Motion Sequence
//  sCmd        - absolutely, you must set the value to Null.
//  TLC_ARGS
//    arg0:INT    - clzz LCXMSQC_SQC{2D|3D}
//    arg1:HANDLE - TLCX_MSQIC{2D|3D}
//    arg2:INT    - sequence size

INT LcxEnt_CreateMoSqc(char* sCmd, PLCX_MOSQC* pOut, PLC_ARGS arg);


#endif// _LC_ORG_SRC_



//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Two-dimensional Game Field Map
enum ELCX_TDF
{
	// Type
	LCXTDF_TOPVIEW			= 0x0011,											// rectangle tile of top view method field.
	LCXTDF_ISOMETRY			= 0x0012,											// Isometry tile.
};


DCL_INTERFACE ILCX_Tdf : public ILC_Object
{
	DCL_CLASS_DESTROYER(	ILCX_Tdf	);

	virtual INT		Release(INT bDecreaseRefCount=LC_TRUE)=0;
	virtual INT		Query(char* sCmd, LC_HANDLE pData)=0;

	virtual INT		FrameMove()=0;
	virtual void	Render()=0;
};

typedef ILCX_Tdf*	PLCX_TDF;


#endif

