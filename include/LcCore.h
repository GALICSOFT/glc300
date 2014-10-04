//	Copyright(C) GaLic Soft. All rights reserved.
//
//	for Initialize system and 3D Rendering Pipe Line.
//
////////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER)
  #pragma once
#endif

#ifndef _LcCore_H_
#define _LcCore_H_

#include <LcType.h>
#include <LcBase.h>


//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// GLC System

//System Initialize and Close
INT  LcSys_Init(																// Initializes the system to execute a program. needs arg4(apk, cls, env, etc)
				PLC_ARGS = NULL													// apk(arg0:LC_HANDLE) - file name for android ex) "com.galic.Totem" in android system. occasionally windows systems use to current directory. other systems set to the null.
				);																// cls(arg1:LC_HANDLE) - class name for android. other systems are null. env(arg2:LC_HANDLE) - java env handle for android. other systems are null. etc(arg3:LC_HANDLE)

void LcSys_Close();																// Release the system  and return to main menu.
INT  LcSys_ReleaseFunctionAdd(LC_HANDLE v);										// add the release function dependent on system


// for Window( it's same to Microsoft windows system)
typedef LRESULT (LC_CALLBACK* PRC_MSG)(LC_HWND,UINT,WPARAM,LPARAM);				// for Window Message Procedure. only to use in Microsoft windows system.
typedef INT     (LC_CALLBACK* PRC_RUN)(LC_HANDLE);								// for Setting Main Run function

INT LcSys_CreateWindow( PRC_MSG													// Message Procedure function pointer
					  , char*     ClassName										// class Name
					  , INT       ScnW=0										// window(screen) width
					  , INT       ScnH=0										// window(screen) height
					  , INT       ScnX=-1										// window(screen) position X for PC. -1 is center
					  , INT       ScnY=-1										// window(screen) position Y for PC. -1 is center
					  , LC_HANDLE Etc=NULL										// Etc value. Form pointer in Bada system
					  );

INT LcSys_DestroyWindow        ();												// destroy window
INT LcSys_SetMainRunFunc       (PRC_RUN);										// Set Main Processing Run Function
INT LcSys_Run                  (LC_HANDLE pApp=NULL);							// Main Processing. only possible that the pApp inherited PLC_APPFRAME.
INT LcSys_ManagedObjectAdd     (PLC_OBJECT);									// Add to the managed object to list
INT LcSys_ManagedObjectRemove  (PLC_OBJECT);									// Remove the managed object list
INT LcSys_ManagedObjectInvalid ();												// Invalidate the managed object
INT LcSys_ManagedObjectRestore ();												// Restore the managed object




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// 3D Rendering Device

// defined in device
enum ELC_DEVICE_CONST
{
	LC_QUAD_NUM					= 16384,										// Maximum number of Quad Index
	LC_LIGHTING_NUM				=  8,  											// Default lighting number
	LC_LIGHTING_RGBA			=  4,  											// constant lighting number is 4(r,g,b,a)
	LC_SHADER_NUM				= 32,											// default shader count
	LC_SHADER_BEGIN				=  0,  											// shader begin index
	LC_SHADER_SPRITE			=  0,  											// shader index for sprite
	LC_SHADER_SPRITE_MONO		=  1,  											// shader index for mono sprite
	LC_SHADER_SPRITE_TM			=  2,  											// shader index for sprite has transform
	LC_SHADER_SPRITE_TM_MONO	=  3,  											// shader index for sprite has transform and mono output
	LC_SHADER_SIMPLE3D			=  4,  											// shader index for simple 3D model
	LC_SHADER_GENERAL3D			=  5,  											// shader index for general 3d(fog, lighting)
	LC_SHADER_VTXBLEND3D		=  6,  											// shader index for vertex blending, fog, lighting
	LC_SHADER_MDL				=  7,  											// for simple model xyz, tex0
	LC_SHADER_MDL_NOR			=  8,  											// for simple model xyz, nor, tex0
	LC_SHADER_MDL_OL			=  9,  											// for simple model xyz, outline
	LC_SHADER_MDL_VBLEND		= 10,  											// for skinning model xyz, tex0, vertex blending
	LC_SHADER_MDL_VBLEND_NOR	= 11,  											// for skinning model xyz, nor, tex0, vertex blending
	LC_SHADER_MDL_VBLEND_OL		= 12,  											// for skinning model outline
};

enum ELC_DEVICE_ST
{
	LC_CLEAR_COLOR_BUFFER		= 0x4000,										// GL_COLOR_BUFFER_BIT
	LC_CLEAR_DEPTH_BUFFER		= 0x0100,										// GL_DEPTH_BUFFER_BIT
	LC_CLEAR_STENCIL_BUFFER		= 0x0400,										// GL_STENCIL_BUFFER_BIT
};

// Vertex Format for Fixed Pipe Line
enum ELC_DEVICE_FORMAT
{
	LC_FVF_XYZ					= 0x0002,										// position float 2,3,4
	LC_FVF_NORMAL				= 0x0010,										// normal vector float3
	LC_FVF_DIFFUSE				= 0x0040,										// diffuse color float4
	LC_FVF_TEX0					= 0x0100,										// use texture coordinate 0 float2
	LC_FVF_TEX1					= 0x0200,										// use texture coordinate 1 float2
	LC_FVF_BLND					= 0x0400,										// vertex blending float4 - [x,y]: index of matrix0, weight, [z,w]: index of matrix1, weight

	LC_FMT_NONE					= 0x0000,										// Not defined
	LC_FMT_WORD					= 0x1403,										// GL_UNSIGNED_SHORT
	LC_FMT_DWORD				= 0x1405,										// GL_UNSIGNED_INT
	LC_FMT_FIXED				= 0x140C,										// GL_FIXED
	LC_FMT_UBYTE				= 0x1401,										// GL_UNSIGNED_BYTE
	LC_FMT_FLOAT				= 0x1406,										// GL_FLOAT

	LC_VA_POS					= 0x0000,										// position. Vertex attribute index for gl..VertexAttribArray in fixed function on glc
	LC_VA_NOR					= 0x0001,										// normal vector
	LC_VA_DIF					= 0x0002,										// diffuse
	LC_VA_TX0					= 0x0003,										// multi texture coordinate 0
	LC_VA_TX1					= 0x0004,										// multi texture coordinate 1
	LC_VA_BLND					= 0x0005,										// blending attribute index(x,y) and weight(z,w) for vertex animation or other texture splatting
	LC_VA_MAX					= 0x0008,										// max blending attribute index 
};

enum ELC_TRANSFORM
{
	LC_TM_WORLD					= 0x0001,										// world matrix
	LC_TM_VIEW					= 0x0002,										// viewing matrix
	LC_TM_PROJ					= 0x0003,										// projection matrix
	LC_TM_WORLD_IDENTITY		= 0x0011,										// Setup the world matrix to Identity
	LC_TM_VIEW_IDENTITY			= 0x0012,										// Setup the viewing matrix to Identity
	LC_TM_PROJ_IDENTITY			= 0x0013,										// Setup the projection matrix to Identity
	LC_TM_WORLD_EXT				= 0x0021,										// External world matrix
	LC_TM_VIEW_EXT				= 0x0022,										// External viewing matrix
	LC_TM_PROJ_EXT				= 0x0023,										// External projection matrix
	LC_TM_WORLD_PT				= 0x0031,										// world matrix pointer
	LC_TM_VIEW_PT				= 0x0032,										// viewing matrix pointer
	LC_TM_VIEW_INV_PT			= 0x0033,										// Inverse viewing matrix pointer
	LC_TM_BILLBOARD_PT			= 0x0034,										// Inverse viewing matrix(has _41=0, _42=0, _43=0) pointer
	LC_TM_PROJ_PT				= 0x0035,										// projection matrix pointer
	LC_TM_VIEWPORT_PT			= 0x0036,										// viewport matrix poiner. only use to GetTransform...
	LC_TM_WVP_PT				= 0x0037,										// world * view * proection matrix pointer
	LC_TM_VP_PT					= 0x0038,										// view * proection matrix pointer
	LC_TM_BLEND_PT				= 0x0039,										// vertex blending with transform cos, sin, axis, and translation. it uses the TLC_VBLEND structure.
	LC_TM_CAMERA_POS_PT			= 0x003A,										// camera position from view matrix
	LC_TM_CAMERA_XAXIS_PT		= 0x003B,										// camera X axis from view matrix
	LC_TM_CAMERA_YAXIS_PT		= 0x003C,										// camera Y axis from view matrix
	LC_TM_CAMERA_ZAXIS_PT		= 0x003D,										// camera Z axis from view matrix
	LC_TM_CAMERA_FRUSTUM		= 0x003E,										// camera viewing frustum. needs 6 LCXPLANE for Near, Far, Left, Right, Top, and Bottom
};

enum ELC_PRIMITIVETYPE
{
	LC_PT_POINT_LIST			= 0x0000,										// GL_POINTS
	LC_PT_LINE_LIST				= 0x0001,										// GL_LINES
	LC_PT_LINE_LOOP				= 0x0002,										// GL_LINE_LOOP
	LC_PT_LINE_STRIP			= 0x0003,										// GL_LINE_STRIP
	LC_PT_TRIANGLE_LIST			= 0x0004,										// GL_TRIANGLES
	LC_PT_TRIANGLE_STRIP		= 0x0005,										// GL_TRIANGLE_STRIP
	LC_PT_TRIANGLE_FAN			= 0x0006,										// GL_TRIANGLE_FAN
};

// Rendering State Status(Value)
enum ELC_RENDERINGSTATE
{
	LC_RS_EAGL_RESIZE			= 0xA000,										// EAGL Resize Action
	LC_RS_CLEAR_COLOR			= 0xA001,										// glClearColor() Set
	LC_RS_CLEAR_DEPTH			= 0xA002,										// glClearDepthf() Set
	LC_RS_CLEAR_STENCIL			= 0xA003,										// glClearStencil() Set
	LC_RS_FUNC_ALPHA			= 0xA011,										// AlphaFunction and alpha test value. function is fixed GL_LEQUAL and default test value is 20(0.08)
	LC_RS_FUNC_DEPTH			= 0xA012,										// glClearDepthf() Set
	LC_RS_FUNC_STENCIL			= 0xA013,										// glStencilFunc() Set
	LC_RS_FILL_MODE				= 0xA014,										// glPolygoneMode() Set only for PC. LC_ST_FILL_{POINT|LINE|SOLID}
	LC_RS_ZBIAS					= 0xA021,										// Z-BIAS
	LC_RS_DISPLAY_MONO			= 0xA022,										// Mono display for 2D spriteTM
	LC_RS_LIGHT_LIST_DIRECTION	= 0xA031,										// get the directional light list
	LC_RS_LIGHT_LIST_DIFFUSE	= 0xA032,										// get the diffuse color list
	LC_RS_LIGHT_LIST_SPECULAR	= 0xA033,										// get the specular color list
	LC_RS_LIGHT_SUM_DIFFUSE		= 0xA034,										// get the sigma Colori * Directional Lighti. Get. need vec3*4 array
	LC_RS_NORMAL_EFFECT			= 0xA041,										// get the normal effect multiple coefficient for dot x,y,z. w is using inner process. 0.0 is nothing. set/getRs needs xyzw vector4.
	LC_RS_DEF_SHADER			= 0xA100,										// get the default shader instance [LC_SHADER_BEGIN~LC_SHADER_NUM]

	LC_RS_ALPHA_TEST        	= 0x0BC0,										// ALPHA_TEST. Enable(True)/Disable(False), over write threshold?(true/false), threshold value[0,255]
	LC_RS_DEPTH_TEST			= 0x0B71,										// GL_DEPTH_TEST. Enable(True), Disable(False)
	LC_RS_STENCIL_TEST			= 0x0B90,										// GL_STENCIL_TEST. Enable(True), Disable(False)
	LC_RS_SCISSOR_TEST			= 0x0C11,										// GL_SCISSOR_TEST. It needs TLC_SCISSOR
	LC_RS_DEPTH_WRITE			= 0x0B72,										// GL_DEPTH_WRITEMASK.
	LC_RS_CULL_FACE				= 0x0B44,										// GL_CULL_FACE, Enable(True), Disable(False), glCullFace()
	LC_RS_CULL_MODE				,												// glFrontFace(),
	LC_RS_DITHER				= 0x0BD0,										// GL_DITHER                         
	LC_RS_BLEND					= 0x0BE2,										// GL_BLEND: AlphaBlending Disable(LC_FALSE), Enable(LC_TRUE), Enable call glBlendFunc(SOURCE, DEST)
	LC_RS_FOG					= 0x0B60,										// glEnable(GL_FOG), glDisable(GL_FOG)
	LC_RS_FOG_DATA				,												// glFogf...(), GL_FOG_COLOR, GL_FOG_MODE, GL_FOG_START, GL_FOG_END  Set

	LC_RS_LIGHTING				= 0x0B50,										// glEnable(GL_LIGHTING), glDisable(GL_LIGHTING)
	LC_RS_LIGHT0				= 0x4000,										// GL_LIGHT0
	LC_RS_LIGHT1				= 0x4001,										// GL_LIGHT1
	LC_RS_LIGHT2				= 0x4002,										// GL_LIGHT2
	LC_RS_LIGHT3				= 0x4003,										// GL_LIGHT3
	LC_RS_LIGHT4				= 0x4004,										// GL_LIGHT4
	LC_RS_LIGHT5				= 0x4005,										// GL_LIGHT5
	LC_RS_LIGHT6				= 0x4006,										// GL_LIGHT6
	LC_RS_LIGHT7				= 0x4007,										// GL_LIGHT7
	LC_RS_LIGHT0_DATA			= 0x4008,										// GL_LIGHT7 +1, glLightfv(GL_LIGHT0, ...)
	LC_RS_LIGHT1_DATA			,												// glLightfv(GL_LIGHT1, ...)
	LC_RS_LIGHT2_DATA			,												// glLightfv(GL_LIGHT2, ...)
	LC_RS_LIGHT3_DATA			,												// glLightfv(GL_LIGHT3, ...)
	LC_RS_LIGHT4_DATA			,												// glLightfv(GL_LIGHT4, ...)
	LC_RS_LIGHT5_DATA			,												// glLightfv(GL_LIGHT5, ...)
	LC_RS_LIGHT6_DATA			,												// glLightfv(GL_LIGHT6, ...)
	LC_RS_LIGHT7_DATA			,												// glLightfv(GL_LIGHT7, ...)
	//LC_RS_MATERIAL_DATA		= 0x4010,										//

	LC_RS_LINE_WIDTH			= 0x0B21,										// GL_LINE_WIDTH
	LC_RS_VIEWPORT				= 0x0BA2,										// GL_VIEWPORT for glViewport(). needs TLC_VIEWPORT pointer
	LC_RS_AMBIENT				= 0x1200,										// GL_AMBIENT

	LC_RS_PICK_RAY				= 0xA110,										// picking lay position, direction from input
};

// Rendering Status(State Value)
enum ELC_RENDERINGSTATUS
{
	LC_ST_ENABLE				= 0x0001,										// True
	LC_ST_DISABLE				= 0x0000,										// False
	LC_ST_ZERO					= 0x0000,										// GL_ZERO
	LC_ST_ONE					= 0x0001,										// GL_ONE

	LC_ST_NEVER					= 0x0200,										// GL_NEVER
	LC_ST_LESS					= 0x0201,										// GL_LESS
	LC_ST_EQUAL					= 0x0202,										// GL_EQUAL
	LC_ST_LEQUAL				= 0x0203,										// GL_LEQUAL
	LC_ST_GREATER				= 0x0204,										// GL_GREATER
	LC_ST_NOTEQUAL				= 0x0205,										// GL_NOTEQUAL
	LC_ST_GEQUAL				= 0x0206,										// GL_GEQUAL
	LC_ST_ALWAYS				= 0x0207,										// GL_ALWAYS

	LC_ST_FLAT					= 0x1D00,										// GL_FLAT
	LC_ST_SMOOTH				= 0x1D01,										// GL_SMOOTH
	LC_ST_CW					= 0x0900,										// GL_CW
	LC_ST_CCW					= 0x0901,										// GL_CCW
	LC_ST_FRONT					= 0x0404,										// GL_FRONT
	LC_ST_BACK					= 0x0405,										// GL_BACK
	LC_ST_FRONT_AND_BACK		= 0x0408,										// GL_FRONT_AND_BACK
	LC_ST_CULL_FACE				= 0x0B44,										// GL_CULL_FACE
	LC_ST_POLYGON_OFFSET_FILL	= 0x8037,										// GL_POLYGON_OFFSET_FILL

	LC_ST_FILL_POINT			= 0x1B00,										// glPolygoneMode() Set value for PC. GL_POINT. Fill point
	LC_ST_FILL_LINE				= 0x1B01,										// glPolygoneMode() Set value for PC. GL_LINE. Fill wire
	LC_ST_FILL_SOLID			= 0x1B02,										// glPolygoneMode() Set value for PC. GL_FILL. Fill solid

	LC_ST_SRC_COLOR				= 0x0300,										// GL_SRC_COLOR
	LC_ST_SRC_INV_COLOR			= 0x0301,										// GL_ONE_MINUS_SRC_COLOR
	LC_ST_SRC_ALPHA				= 0x0302,										// GL_SRC_ALPHA
	LC_ST_SRC_INV_ALPHA			= 0x0303,										// GL_ONE_MINUS_SRC_ALPHA
	LC_ST_DST_ALPHA				= 0x0304,										// GL_DST_ALPHA
	LC_ST_DST_INV_ALPHA			= 0x0305,										// GL_ONE_MINUS_DST_ALPHA
	LC_ST_DST_COLOR				= 0x0306,										// GL_DST_COLOR
	LC_ST_DST_INV_COLOR			= 0x0307,										// GL_ONE_MINUS_DST_COLOR
	LC_ST_SRC_ALPHA_SATURATE	= 0x0308,										// GL_SRC_ALPHA_SATURATE

	LC_ST_FOG_LINEAR			= 0x2601,										// GL_LINEAR
	LC_ST_GL_EXP				= 0x0800,										// GL_EXP
	LC_ST_GL_EXP2				= 0x0801,										// GL_EXP2

	LC_ST_AMBIENT				= 0x1200,										// GL_AMBIENT
	LC_ST_DIFFUSE				= 0x1201,										// GL_DIFFUSE
	LC_ST_SPECULAR				= 0x1202,										// GL_SPECULAR
	LC_ST_POSITION				= 0x1203,										// GL_POSITION
	LC_ST_SPOT_DIRECTION		= 0x1204,										// GL_SPOT_DIRECTION
	LC_ST_SPOT_EXPONENT			= 0x1205,										// GL_SPOT_EXPONENT
	LC_ST_SPOT_CUTOFF			= 0x1206,										// GL_SPOT_CUTOFF
	LC_ST_CONSTANT_ATTENUATION	= 0x1207,										// GL_CONSTANT_ATTENUATION
	LC_ST_LINEAR_ATTENUATION	= 0x1208,										// GL_LINEAR_ATTENUATION
	LC_ST_QUADRATIC_ATTENUATION = 0x1209,										// GL_QUADRATIC_ATTENUATION
	LC_ST_EMISSION				= 0x1600,										// GL_EMISSION
	LC_ST_SHININESS				= 0x1601,										// GL_SHININESS

	LC_ST_PXL_RED				= 0x0D52,										// pixel process for red. GL_RED_BITS
	LC_ST_PXL_GREEN				= 0x0D53,										// pixel process for green. GL_GREEN_BITS
	LC_ST_PXL_BLUE				= 0x0D54,										// pixel process for blue. GL_BLUE_BITS
	LC_ST_PXL_ALPHA				= 0x0D55,										// pixel process for alpha. GL_ALPHA_BITS
	LC_ST_PXL_DEPTH				= 0x0D56,										// pixel process for depth. GL_DEPTH_BITS
	LC_ST_PXL_STENCIL			= 0x0D57,										// pixel process for stencil. GL_STENCIL_BITS
};

// texture state
enum ELC_TEXTURE_STATE
{
	LC_TS_TEXTURE_ENV_MODE		= 0x2200,										// GL_TEXTURE_ENV_MODE
	LC_TS_TEXTURE_MAG_FILTER	= 0x2800,										// GL_TEXTURE_MAG_FILTER
	LC_TS_TEXTURE_MIN_FILTER	= 0x2801,										// GL_TEXTURE_MIN_FILTER
	LC_TS_TEXTURE_WRAP_S		= 0x2802,										// GL_TEXTURE_WRAP_S
	LC_TS_TEXTURE_WRAP_T		= 0x2803,										// GL_TEXTURE_WRAP_T
	LC_TS_TEXTURE_ENV_COLOR		= 0x2201,										// GL_TEXTURE_ENV_COLOR
	LC_TS_MODULATE				= 0x2100,										// GL_MODULATE
	LC_TS_DECAL					= 0x2101,										// GL_DECAL
	LC_TS_ADD					= 0x0104,										// GL_ADD
	LC_TS_ADD_SIGNED			= 0x8574,										// GL_ADD_SIGNED
	LC_TS_SUBTRACT				= 0x84E7,										// GL_SUBTRACT
	LC_TS_INTERPOLATE			= 0x8575,										// GL_INTERPOLATE
	LC_TS_NEAREST				= 0x2600,										// GL_NEAREST
	LC_TS_LINEAR				= 0x2601,										// GL_LINEAR
	LC_TS_NEAREST_MIPMAP_NEAREST= 0x2700,										// GL_NEAREST_MIPMAP_NEAREST
	LC_TS_LINEAR_MIPMAP_NEAREST	= 0x2701,										// GL_LINEAR_MIPMAP_NEAREST
	LC_TS_NEAREST_MIPMAP_LINEAR	= 0x2702,										// GL_NEAREST_MIPMAP_LINEAR
	LC_TS_LINEAR_MIPMAP_LINEAR	= 0x2703,										// GL_LINEAR_MIPMAP_LINEAR
	LC_TS_REPEAT				= 0x2901,										// GL_REPEAT
	LC_TS_CLAMP					= 0x812F,										// GL_CLAMP_TO_EDGE
	LC_TS_MIRROR				= 0x8370,										// GL_MIRRORED_REPEAT

	LC_TS_TOP_NONE				= 0x0000,										// multi-texturing operation
	LC_TS_TOP_MUL				= LC_TS_MODULATE,								// before-color * current color
	LC_TS_TOP_ADD				= LC_TS_ADD,									// before-color + current color
	LC_TS_TOP_SUB				= LC_TS_SUBTRACT,								// before-color - current color
	LC_TS_TOP_ADS				= LC_TS_ADD_SIGNED,								// before-color + current color - before-color * current color
	LC_TS_TOP_ONE				= LC_TS_DECAL,									// current-color
};


struct TLC_IMAGE_SUB
{
	INT x, y, w, h;
	BYTE* p;
};


struct TLC_SCISSOR
{
	INT			a;																// enable or disable
	FLOAT		x,y,w,h;														// x, y, width, height
};

struct TLC_VIEWPORT
{
	FLOAT		x,y,w,h;														// upper left, top, width, height
	FLOAT		n, z;															// clipping volume minimum(n), maximum(z) depth.
};


struct TLC_FOG
{
	LC_COLORF	Col;															// Fog colorFLOAT r,g,b,a
	union { struct{	FLOAT Bgn, Rng, Pow, Act; };								// Fog mode: it will be call start, range, pow(Mod), and activating
			struct{ FLOAT   x,   y,   z,   w; };};								// range = fog end - fog start
};


struct TLC_LIGHT																// GLC Lighting: system use only directional lighting and fixed 4-lightings.
{																				// Ambient ->SetRenderState(LC_ST_AMBIENT, UINT color);
	LC_COLORF	Dif;															// Diffuse Color(r, g, b)
	LC_COLORF	Spc;															// Specular Color(r, g, b) and alpha is shapness
	LC_FLOAT4	Dir;															// Direction
};


struct TLC_VBLEND																// Vertex blending info
{
	INT			n;																// array count
	FLOAT*		c;																// cosine list
	FLOAT*		s;																// sine list
	LC_FLOAT3*	a;																// Axis list
	LC_FLOAT3*	t;																// translation list
};


struct TLC_DISPLAY																// Display Info
{
	INT			r, g, b, a, d, s;												// red, green, blue, alpha, depth, stencil bit count
	INT			w, h;															// display with, and height
};


// Texture
DCL_INTERFACE	ILC_Texture;
typedef			ILC_Texture*	PLC_TEXTURE;

// Vertex Buffer
DCL_INTERFACE	ILC_VB;
typedef			ILC_VB*			PLC_VB;

// Index Buffer
DCL_INTERFACE	ILC_IB;
typedef			ILC_IB*			PLC_IB;

// shader object
DCL_INTERFACE	ILcEffect;
typedef			ILcEffect*		PLC_EFFECT;

// Frame buffer object
DCL_INTERFACE	ILC_FBO;
typedef			ILC_FBO*		PLC_FBO;




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// 3D rendering

// Device
DCL_INTERFACE ILC_Device : public ILC_Object
{
	DCL_CLASS_DESTROYER(	ILC_Device	);

	virtual INT		Query(char* sCmd, LC_HANDLE pData)=0;						// inherit from the ILC_Object

	virtual UINT	ObjType() { return LC_OBJ_DEVICE; }							// return the type of instance

	virtual	INT		SetTransform(INT nTransform, const LC_HANDLE v)=0;			// 3D PipeLine World, View, Projection Transform
	virtual	INT		GetTransform(INT nTransform, LC_HANDLE v)=0;

	virtual	INT		BeginScene()=0;												// Prepare Rendering it's going to call the glViewport. and SetContext in iPhone system
	virtual	INT		EndScene()=0;												// Post Rendering

	// Rendering State
	virtual	INT		SetRenderState(INT nState, INT, INT =0,INT =0,INT =0)=0;	// Redering Machine State
	virtual	INT		SetRenderState(INT nState,LC_HANDLE v)=0;					// Redering Machine State for Pointer
	virtual	INT		GetRenderState(INT nState,LC_HANDLE v)=0;					// Redering Machine State

	// Texture and Multi-texture...
	virtual INT		SetTextureAddressS (INT nStage, INT v)=0;
	virtual INT		SetTextureAddressT (INT nStage, INT v)=0;
	virtual INT		SetTextureFilterMin(INT nStage, INT v)=0;
	virtual INT		SetTextureFilterMag(INT nStage, INT v)=0;
	virtual INT		SetTextureStageOp  (INT nStage, INT v)=0;
	virtual INT		GetTextureAddressS (INT nStage, INT* v)=0;
	virtual INT		GetTextureAddressT (INT nStage, INT* v)=0;
	virtual INT		GetTextureFilterMin(INT nStage, INT* v)=0;
	virtual INT		GetTextureFilterMag(INT nStage, INT* v)=0;
	virtual INT		GetTextureStageOp  (INT nStage, INT* v)=0;

	virtual	INT		SetFVF(INT nFVF)=0;											// Vertex Format
	virtual INT		SetTexture(INT nStage, PLC_TEXTURE  pTex)=0;				// Set Texture
	virtual INT		GetTexture(INT nStage, PLC_TEXTURE* pTex)=0;				// Get Texture pointer

	virtual	INT		SetTcolor(LC_COLORF* v, INT  op=LC_TS_TOP_MUL)=0;			// T-factor color. op: default-mul, add, sub(tcolor-raster), one(use tcolor), zero(use rastercolor)
	virtual	INT		GetTcolor(LC_COLORF* v, INT* op=NULL) =0;					// get T-factor color.
	virtual INT		StreamActive( INT stream, INT bActive)=0;					// gl{Enable|Disable}VertexAttribArray(stream);

	virtual INT		SetStream(INT stream, void* buf, INT bType= LC_FMT_NONE		// Rendering Primitive for opengl stream stream buffer. it will calls the glEnableVertexAttribArray and glVertexAttribPointer
							, INT size=0,INT normalized=0, INT stride=0)=0;		// if bType == LC_FMT_UBYTE, you must setup the nomalized value to true(1)


	// Rendering Primitive for Vertex Buffer Object
	virtual INT		SetStreamSource(PLC_VB)=0;
	virtual INT		SetIndices(PLC_IB)=0;

	virtual INT		DrawPrimitive		( INT nMode, INT First, INT nVtx)=0;
	virtual INT		DrawIndexedPrimitive( INT nMode								// ELC_PRIMITIVETYPE
										, INT nIndexCount						// Index count
										, const void *pIdx=NULL					// Index buffer
										, INT idxType=LC_FMT_WORD)=0;			// Index type unsigned short:LC_FMT_WORD, unsigned int 32bit LC_FMT_DWORD


	// Rendering Primitive for User Memory Pointer
	// These mothods use the built in shading object.

	virtual INT		DrawPrimitiveUP			( INT nMode
											, INT First
											, INT nVertexCount
											, const void* pVertices
											, INT dStride)=0;

	virtual INT		DrawIndexedPrimitiveUP	( INT nMode
											, INT nIndexCount					// Index count
											, const void* pIdx=NULL				// Index buffer. if the idices is setting then pIdx must be NULL.
											, INT idxType=LC_FMT_WORD)=0;		// Index type unsigned short:LC_FMT_WORD, unsigned int 32bit LC_FMT_DWORD

	virtual INT		DrawIndexedPrimitiveUP	( INT nMode							// draw with user point memory
											, INT nIndexCount					// Index count
											, const void *pIdx					// Index buffer
											, INT idxType						// Index type unsigned short:LC_FMT_WORD, unsigned int 32bit LC_FMT_DWORD
											, const void* pVtx					// vertex buffer
											, INT dStride)=0;					// vertex struct size



	virtual INT		Clear(UINT dClearMode)=0;									// glClear()
	virtual INT		Present(LC_HANDLE =0, LC_HANDLE  =0
							, LC_HANDLE =0, LC_HANDLE =0)=0;					// glSwapBuffer() + glFlush()
};


typedef	ILC_Device*	PLC_DEVICE;


#define LC_QUERY_GET_SCREEN_WIDTH_HEIGHT (char*)"Get Screen Width and Height"
#define LC_QUERY_INVALID                 (char*)"Invalid"
#define LC_QUERY_RESTORE                 (char*)"Restore"
#define LC_QUERY_COPY                    (char*)"Copy"
#define LC_QUERY_REPLACE                 (char*)"Replace"
#define LC_QUERY_REPLACE_SRC             (char*)"Replace source"

INT         LcDev_CreateDevice(char* sCmd, PLC_DEVICE* pOut, PLC_ARGS = NULL);	// Create Device

BYTE*       LcDev_DefaultWhiteDiffuse();										// default white diffuse buffer(2048*2048 *2bytes)
PLC_TEXTURE	LcDev_DefaultWhiteTexture();										// default white texture 2048*2048 565
PLC_TEXTURE	LcDev_DefaultBlackTexture();										// default blac texture 4*4 8888
INT         LcDev_EffectSetupWithType(PLC_DEVICE, PLC_EFFECT, UINT type);		// setup envirionment for shader type: [LC_SHADER_SPRITE, LC_SHADER_MDL_VBLEND_NOR]
INT         LcDev_ReleaseFunctionAdd(LC_HANDLE v);								// add the release function dependent on device. v must be INT (void) function pointer;
INT         LcDev_ReleaseFunctionRelease();										// release the "relese functions" dependent on device.



//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Sprite Layer. Mixing and Rendering
// ILC_SpriteS draw is immediately mode. but ILC_Sprite draw mode is delayed draw.
// when you call Draw with different old texture, this instance is going to draw vertex list.
// End() function will be drawing remain vertex list.

DCL_INTERFACE ILC_Sprite : public ILC_Object
{
	DCL_CLASS_DESTROYER(	ILC_Sprite	);

	virtual UINT	ObjType() { return LC_OBJ_SPRITE; }							// return the type of instance
	//virtual UINT	Type() =0;													// return the sprite mode GUI or Model

	virtual INT		Begin(UINT dMode=LC_OBJ_SPRITE)=0;							// Save 3d environment before the execution of Sprite.
	virtual INT		End(UINT dForce=LC_FALSE)=0;								// Draw, Clear and Reload saved 3d environment.

	virtual	INT		SetTransform(INT nTransform, const LC_HANDLE v)=0;			// 3D PipeLine World, View, Projection Transform. LC_TM_WORLD~
	virtual	INT		GetTransform(INT nTransform, LC_HANDLE v)=0;

	virtual	INT		SetRenderState(INT nState
									, INT=0, INT =0,INT =0,INT =0)=0;			// Redering Machine State

	virtual	INT		SetTcolor(LC_COLORF* c)=0;									// set the t-color. 2d sprite t-color is independent 3device. c is null then color will be set to 0xFFFFFFFF
	virtual	INT		GetTcolor(LC_COLORF* c)=0;									// get the saved t-color float(r,g,b,a)
	

	// Draw(), DrawEx() Functions redefined to assemble and construct the vertex list in spritemx.
	virtual INT		Draw( PLC_TEXTURE		pTexture							// LC_Texture Pointer
						, const LC_RECTF*	pImgRc								// Image rect
						, const LC_FLOAT3*	vcTrn								// Position
						, const LC_FLOAT3*	vcScl=NULL							// Scaling
						, const LC_COLORF*	color=NULL							// color
						) =0;

	virtual INT		DrawEx(PLC_TEXTURE		pTexture							// LC_Texture Pointer
						, const LC_RECTF*	pImgRc								// Image rect
						, const LC_FLOAT3*	vcTrn								// Position
						, const LC_FLOAT3*	vcScl								// Scaling
						, const LC_FLOAT3*	vcRot								// Rotation Center
						, FLOAT				fRot								// Angle(Radian)
						, const LC_COLORF*	color=NULL							// color
						) =0;

	// Draw the vertex list
	virtual INT		DrawFlush()=0;												// it is going to render the assembled vertex list. if the current teuxture and new texture is not equal then absolutely draw assembled vertex list and assemble vertex for new texture.


	// other operation needs sprite.
	virtual INT		DrawArray(PLC_TEXTURE		pTexture						// the sprite draws array buffer.
							, const LC_FLOAT3*	vPos							// Position buffer. simply, immediately draw the vertex array
							, const LC_COLORB*	vColor							// rgba color buffer. be careful it use a,r,g,b byte[0,256] color. if NULL then it will use (255,255,255,255)
							, const LC_FLOAT2*	vTxCoord						// Texture coordinate buffer.
							, INT				nCount =1						// RECT count
							) =0;


	virtual INT		DrawLine( UINT				dLineType						// line primitive type LC_PT_LINE_{LIST|STRIP|LOOP}, zero is Line List type.
							, const LC_FLOAT3*	vPos							// Position buffer(points).
							, FLOAT				fWidth = 1.0F					// line width
							, const LC_COLORF*	pColor = NULL					// rgba color value.
							, INT				nCount = 1						// points count
							) =0;

	virtual INT		DrawRect( const LC_FLOAT3*	pPos							// rect start Position
							, FLOAT				rcW								// rect width
							, FLOAT				rcH								// rect height
							, FLOAT				fWidth = 1.0F					// line width
							, const LC_COLORF*	pColor = NULL					// Draw Rect: rc Must be LCXRECT(x,y,w,h);
							) =0;

	virtual INT		DrawEllipsoid(LC_FLOAT3*		center						// Draw Ellipsoid: center(x,y)
								, FLOAT				radiusX						// radius for x-axis.
								, FLOAT				radiusY						// radius for y-axis.
								, FLOAT				fWidth = 1.0F				// line width
								, const LC_COLORF*	pColor = NULL				// color
								) =0;

	virtual INT		DrawBuffer(PLC_TEXTURE		pTexture						// the sprite draws buffer.
							, const LC_FLOAT3*	pPos							// Position buffer.
							, const LC_COLORB*	pColor							// color buffer.
							, const LC_FLOAT2*	pTxCoord						// Texture coordinate buffer.
							, const WORD*		pIdx							// Index buffer.
							, INT				vertexCount						// Vertex Count
							, INT				indexcount						// Index Count
							, INT				prmtv = LC_PT_TRIANGLE_LIST		// primitive type
							) =0;

};

typedef	ILC_Sprite*	PLC_SPRITE;

// Create Sprite...
//  sCmd        - absolutely, you must set the value to Null.
//  TLC_ARGS
//    arg0:UINT      - type: LC_OBJ_GUI( 0,0 is left top), LC_OBJ_SPRITE( 0,0 is screen center)
INT LcDev_CreateSprite(char* sCmd, PLC_SPRITE* pOut, PLC_ARGS arg);




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Sprite Collector
// Assembling the rectangles and draw.

DCL_INTERFACE ILC_SpriteC : public ILC_Object
{
	DCL_CLASS_DESTROYER(	ILC_SpriteC	);

	virtual UINT	ObjType() { return LC_OBJ_SPRITE_C; }						// return the type of instance

	virtual INT		AddRect(const LC_RECTF*	pImgRc								// Image rect
						, const LC_FLOAT3*	vcTrn								// Position
						, const LC_FLOAT3*	vcScl								// Scaling
						, const LC_FLOAT3*	vcRot								// Rotation Center
						, FLOAT				fRot								// Angle(Radian)
						, const LC_COLORF*	color=NULL							// color
						) =0;

	virtual INT		Draw() =0;													// Draw the vertex list
	virtual void	SetTexture(PLC_TEXTURE v) =0;								// Set Texture
};

typedef	ILC_SpriteC*	PLC_SPRITE_C;

// Create Sprite collector
//  sCmd        - absolutely, you must set the value to Null.
//  TLC_ARGS
//    arg0:LC_HANDLE - texture pointer
//    arg1:UINT      - type: LC_OBJ_GUI or zero( 0,0 is left top), LC_OBJ_MODEL2D( 0,0 is screen center)

INT LcDev_CreateSpriteC(char* sCmd, PLC_SPRITE_C* pOut, PLC_ARGS arg);




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Image

enum ELC_IMAGE
{
	// IMAGE_TYPE
	LC_IMG_WORD			= LC_FMT_WORD	,										// GL_UNSIGNED_SHORT
	LC_IMG_DWORD		= LC_FMT_DWORD	,										// GL_UNSIGNED_INT
	LC_IMG_UBYTE		= LC_FMT_UBYTE	,										// GL_UNSIGNED_BYTE
	LC_IMG_FLOAT		= LC_FMT_FLOAT	,										// GL_FLOAT

	// PIXEL_FORMAT
	LC_FMT_ALPHA		= 0x1906,												// GL_ALPHA
	LC_FMT_RGB			= 0x1907,												// GL_RGB
	LC_FMT_RGBA			= 0x1908,												// GL_RGBA
	LC_FMT_L8			= 0x1909,												// GL_LUMINANCE
	LC_FMT_LALPHA		= 0x190A,												// GL_LUMINANCE_ALPHA
	LC_FMT_W565			= 0x8363,												// GL_UNSIGNED_SHORT_5_6_5
	LC_FMT_W5551		= 0x8034,												// GL_UNSIGNED_SHORT_5_5_5_1
	LC_FMT_W4444		= 0x8033,												// GL_UNSIGNED_SHORT_4_4_4_4

	// etc..
	LC_IMG_MAX_WIDTH	= 2048	,												// Image max width
	LC_IMG_MAX_HEIGHT	= 2048	,												// Image max Height
};

struct TDSC_IMAGE
{
	UINT	img_s;																// Image source storage type: LC_SRC_T_{FILE | MEM | BUF, RSC}
	UINT	img_k;																// Resource Type. [LC_OBJ_BMP, LC_OBJ_RNT].
	UINT	img_t;																// byte type:  LC_FMT_UBYTE, LC_FMT_WORD, or LC_FMT_DWORD
	UINT	img_f;																// ELC_IMAGE: PIXEL_FORMAT
	INT		img_w;																// Width
	INT		img_h;																// Height
	INT		img_d;																// Depth(Channel). 1,2,3, and 4 (byte)
	UINT	img_c;																// Color Key
	BYTE*	img_p;																// pixels
};

DCL_INTERFACE ILC_Image : public ILC_Object
{
	DCL_CLASS_DESTROYER(	ILC_Image	);

	virtual UINT		RscType	() =0;											// source type: LC_OBJ_IMG
	virtual UINT		Type	() =0;											// pixel type:  IMAGE_TYPE
	virtual INT			Desc	(LC_HANDLE) =0;									// It needs TDSC_IMAGE* address

	virtual UINT		Format	() =0;											// pixel format ELC_IMAGE: PIXEL_FORMAT
	virtual INT			ImgW	() =0;											// Width
	virtual INT			ImgH	() =0;											// Height
	virtual INT			ImgD	() =0;											// Depth(Channel). 1,2,3, and 4 (byte)
	virtual UINT		ImgC	() =0;											// Color Key
	virtual CONF(BYTE*)	Pixel	() =0;											// pixels
};

typedef	ILC_Image*	PLC_IMAGE;


// Create Image from File
//  sCmd        - absolutely, you must set the value to Null.
//  TLC_ARGS
//    arg0: char* - file name
//    arg1: UINT  - Target pixel format 0(no convert), LC_FMT_W{565|55514444}
//    arg2: UINT  - Color Key

INT LcDev_CreateImageFromFile  ( char* sCmd, PLC_IMAGE* pOut, PLC_ARGS args);

// Create Image from buffer
//  sCmd        - absolutely, you must set the value to Null.
//  TLC_ARGS
//    arg0:UINT      - Target pixel format 0(no convert), LC_FMT_W{565|55514444}
//    arg1:UINT      - Color Key
//    arg2:INT       - Image Width.
//    arg3:INT       - Image Height.
//    arg4:LC_HANDLE - buffer address. source pixel. default is NULL
//    arg5:INT       - buffer size


INT LcDev_CreateImageFromBuffer( char* sCmd, PLC_IMAGE* pOut, PLC_ARGS args);


// Create Image for render target
//  sCmd        - absolutely, you must set the value to Null.
//  TLC_ARGS
//    arg0:UINT - Target pixel format 0(no convert), LC_FMT_W{565|55514444}
//    arg1:INT  - Image Width.
//    arg2:INT  - Image Height.

INT LcDev_CreateImageForRenderTarget( char* sCmd, PLC_IMAGE* pOut, PLC_ARGS args);


// simple Image Info: 
INT LcDev_ImageInfo(  INT* imgFormat, INT* imgWidth, INT* imgHeight
					, INT* imgDepth, INT* imgColorKey, const char* sFile);


// Convert pixel bit 32 or 24 bit pixel to 16 bit down grade.
INT	LcDev_Convert32to16Color(WORD*       oPxl
						   , UINT*       oType									// It must be LC_IMG_UBYTE
						   , const BYTE* iPxl									// Source Pixel buffer
						   , UINT        iFMT									// LC_IMG_WORD_{565|5551|4444}
						   , INT         iImgW									// Image Width
						   , INT         iImgH									// Image Height
						   , INT         iImgD									// Image Depth(byte)
						   , UINT        iImgC									// Color Key
						   );

// save the pixel data for debug
INT LcDev_SaveImageto16BitText(  TDSC_IMAGE* Out								// pixel info
							   , const char* sourceFile							// source file name
							   , UINT destColorkey=0x0							// color key
							   , UINT destFormat=LC_FMT_W5551);					// dest 16bit image format




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Texture

struct TDSC_TEXTURE																// For Load Texture Option
{
	char*		src_n;															// Resource Name for Search
	UINT		img_t;															// byte type:  LC_FMT_UBYTE, LC_FMT_WORD, or LC_FMT_DWORD
	UINT		img_f;															// ELC_IMAGE: PIXEL_FORMAT
	INT			img_w;															// Width
	INT			img_h;															// Height
	INT			img_d;															// Depth(Channel). 1,2,3, and 4 (byte)
	UINT		img_c;															// Color Key

	UINT		tex_i;															// Id
	INT			tex_m;															// Mipmap Level
	INT			tex_w;															// Width
	INT			tex_h;															// Height

	LC_HANDLE	mem_a;															// Memory address
	UINT		mem_s;															// Memory Size
	UINT		mem_p;															// Memory Pool. Save Original Memory? LC_OK, LC_EFAIL
};

DCL_INTERFACE ILC_Texture : public ILC_Object
{
	DCL_CLASS_DESTROYER(	ILC_Texture	);

	virtual INT			Release(INT bDecreaseRefCount=LC_TRUE)=0;
	virtual INT			Query(char* sCmd, LC_HANDLE pData)=0;
	virtual UINT		Type	() =0;											// pixel type:  IMAGE_TYPE
	virtual INT			Desc	(LC_HANDLE) =0;									// It needs TDSC_TEXTURE* address
	virtual CONC		Name    () =0;

	virtual CONF(char*)	Name	()const=0;										// Resource Name
	virtual UINT		Oid		() =0;											// OpenGL ID

	virtual UINT		Format	() =0;											// pixel format ELC_IMAGE: PIXEL_FORMAT
	virtual INT			ImgW	() =0;											// Width
	virtual INT			ImgH	() =0;											// Height
	virtual INT			ImgD	() =0;											// Depth(Channel). 1,2,3, and 4 (byte)
	virtual UINT		ImgC	() =0;											// Color Key
	virtual UINT		TexW	() =0;											// Texture Width
	virtual UINT		TexH	() =0;											// Texture Height

	virtual	INT		BindTexture(INT stage=0										// multi texturing stage
							  , INT modulate=0									// Binding Texture: If moduate =0  then Release Binding
							  , INT filter_min=LC_TS_LINEAR						// Minification Filter. GL_LINEAR: 0x2601
							  , INT filter_mag=LC_TS_LINEAR						// Magnification Filter
							  , INT smp_addrS=LC_TS_REPEAT						// Texture Address mode for the S coordinate. GL_REPEAT: 0x2901
							  , INT smp_addrT=LC_TS_REPEAT						// Texture Address mode for the T coordinate
							  )=0;

	virtual	INT		CopyTexImage2D(INT leftTop =LC_FALSE						// the standard base.. default is left bottom for right-hand coordinate.
								 , INT x = 0, INT y = 0							// region start
								 , INT w =-1, INT h =-1							// glCopyImage2D: Copy to Texture from Frame Buffer. when the value of w,h is -1, it use the width and height created values.
								 )=0;

	//virtual		INT		CopyTexImage2D(INT w =-1, INT h =-1)=0;				// glCopyImage2D: Copy to Texture from Frame Buffer. when the value of w,h is -1, it use the width and height created values.
};


#define LC_QUERY_TEXTURE_SETUP_MIPMAP    (char*)"Setup Mipmap"
#define LC_QUERY_TEXTURE_SAVE_TO_BUFFER  (char*)"Save to self buffer"
#define LC_QUERY_TEXTURE_SET             (char*)"Set texture"
#define LC_QUERY_TEXTURE_GET             (char*)"Get texture"

// Rendering Copy Texture
//  sCmd       - absolutely, you must set the value to Null.
//  TLC_ARGS
//    arg0:INT - Image Width.
//    arg1:INT - Image Height.
//    if args is NULL then dest texture width/height will be setup to screen width/height;
INT LcDev_CreateTextureTarget(char* sCmd, PLC_TEXTURE* pOut, PLC_ARGS =NULL);


// Create Texture from merged file
//  sCmd        - absolutely, you must set the value to Null.
//  TLC_ARGS
//    arg0:char*- "File Name"
//    arg1:UINT - Color Key
//    arg2:UINT - Pixel format 0(no convert), LC_FMT_W{565|55514444}
//    arg3:INT  - Mip Level
//    arg4:INT  - memory managing LC_FAIL: not, 0<= Duplicate(Default)
INT LcDev_CreateTextureFromFile(char* sCmd, PLC_TEXTURE* pOut, PLC_ARGS arg);


// Create Texture from specified TDSC_IMAGE struct values
//  sCmd           - absolutely, you must set the value to Null.
//  TLC_ARGS
//    arg0:char*     - "Name" for identifier
//    arg1:LC_HANDLE - TDSC_IMAGE pointer
//    arg2:INT       - Mip Level
//    arg3:INT       - memory managing LC_FAIL: not, 0<= Duplicate(Default)
INT LcDev_CreateTextureFromBuffer(char* sCmd, PLC_TEXTURE* pOut, PLC_ARGS arg);




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Vertex Buffer and Index Buffer Data

struct TLC_GEO
{
	UINT			fmt;			// fvf formad
	INT				strd;			// vertex buffer stride
	INT				num;			// number of vertex/index count
	LC_HANDLE		buf;			// buffer
	INT				len;			// buffer size
};


DCL_INTERFACE ILC_VB : public ILC_Object
{
	DCL_CLASS_DESTROYER(	ILC_VB	);

	virtual INT		Release(INT bDecreaseRefCount=LC_TRUE)=0;
	virtual INT		Query(char* sCmd, LC_HANDLE pData)=0;

	virtual UINT	Fmt() =0;													// Get the FVF
	virtual INT		Stride() =0;												// Get the stride
	virtual INT		Offset(UINT fvf) =0;										// Get the offset for LC_FVF_XYZ ~ LC_FVF_BLND. -1 is failed.
	virtual INT		Fill(LC_HANDLE Buf,INT BufSize,INT bReCreate=LC_FALSE)=0;	// Fill Buffer
	virtual INT		Bind(INT bBind=LC_TRUE)=0;									// Bind Buffer
};


// Create Vertex Buffer Instance
//  sCmd        - absolutely, you must set the value to Null.
//  TLC_ARGS
//    arg0:UINT     - FVF of vertex buffer.
//    arg1:LC_HANDLE- Input Buffer pointer.
//    arg2:INT      - Input Buffer Size
INT LcDev_CreateVB(char* sCmd, PLC_VB* pOut, PLC_ARGS pArg);




DCL_INTERFACE ILC_IB : public ILC_Object
{
	DCL_CLASS_DESTROYER(	ILC_IB	);

	virtual INT		Release(INT bDecreaseRefCount=LC_TRUE)=0;
	virtual INT		Query(char* sCmd, LC_HANDLE pData)=0;

	virtual UINT	Fmt()=0;													// Get the FVF
	virtual INT		Fill(LC_HANDLE Buf,INT BufSize,INT ReCreate=LC_FALSE)=0;	// Fill Buffer
	virtual INT		Bind(INT bBind=LC_TRUE)=0;									// Bind Buffer
};


// Create Vertex Buffer Instance
//  sCmd        - absolutely, you must set the value to Null.
//  TLC_ARGS
//    arg0:UINT     - FVF of index buffer(only use the LC_FMT_WORD).
//    arg1:LC_HANDLE- Input Buffer pointer.
//    arg2:INT      - Input Buffer Size
INT LcDev_CreateIB(char* sCmd, PLC_IB* pOut, PLC_ARGS pArg);




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Shader

// for OpenGL shader
struct TLC_GLSHADER
{
	GL_SHADER		v;															// vertex shader
	GL_SHADER		f;															// fragment shader
	GL_PROGRAM		p;															// program
};

DCL_INTERFACE ILcEffect : public ILC_Object
{
	DCL_CLASS_DESTROYER(	ILcEffect	);

	virtual INT		Release(INT bDecreaseRefCount=LC_TRUE)=0;
	virtual INT		Query(char* sCmd, LC_HANDLE pData)=0;


	virtual INT		Begin(INT nCmd=0x0) =0;
	virtual INT		End() =0;

	// Setup Attrribute Index
	virtual	INT		AttribIndex(char* attName, INT nIndex) =0;

	// Setup Uniform value
	virtual	INT		Int     (const char* name, INT v) =0;
	virtual	INT		Intv    (const char* name, LC_HANDLE v, INT nCount) =0;
	virtual	INT		Float   (const char* name, FLOAT v) =0;
	virtual	INT		Float2  (const char* name, FLOAT x,FLOAT y) =0;
	virtual	INT		Float3  (const char* name, FLOAT x,FLOAT y,FLOAT z) =0;
	virtual	INT		Float4  (const char* name, FLOAT x,FLOAT y,FLOAT z,FLOAT w) =0;
	virtual	INT		Floatv  (const char* name, LC_HANDLE v, INT nCount) =0;

	virtual	INT		Vector2 (const char* name, LC_HANDLE v) =0;
	virtual	INT		Vector3 (const char* name, LC_HANDLE v) =0;
	virtual	INT		Vector4 (const char* name, LC_HANDLE v) =0;
	virtual	INT		Matrix2 (const char* name, LC_HANDLE v) =0;
	virtual	INT		Matrix3 (const char* name, LC_HANDLE v) =0;
	virtual	INT		Matrix4 (const char* name, LC_HANDLE v) =0;
	virtual	INT		Color   (const char* name, LC_HANDLE v) =0;

	virtual	INT		Vec2v   (const char* name, LC_HANDLE v, INT nCount=1) =0;
	virtual	INT		Vec3v   (const char* name, LC_HANDLE v, INT nCount=1) =0;
	virtual	INT		Vec4v   (const char* name, LC_HANDLE v, INT nCount=1) =0;
	virtual	INT		Mat2v   (const char* name, LC_HANDLE v, INT nCount=1) =0;
	virtual	INT		Mat3v   (const char* name, LC_HANDLE v, INT nCount=1) =0;
	virtual	INT		Mat4v   (const char* name, LC_HANDLE v, INT nCount=1) =0;
	virtual	INT		Colorv  (const char* name, LC_HANDLE v, INT nCount=1) =0;

	virtual	INT		Texture (const char* name, INT nStage, INT nTexID) =0;
	virtual	INT		Texture (const char* name, INT nStage, ILC_Texture* pTex) =0;
};


// Create Shader from Text file.
//  sCmd        - absolutely, you must set the value to Null.
//  TLC_ARGS
//    arg0:UINT - type: GL_FRAGMENT_SHADER, GL_VERTEX_SHADER
//    arg1:char*- "file name"
INT LcDev_CreateShaderFromTxtFile  (GL_SHADER* s, PLC_ARGS arg);


// Create Shader from Text buffer.
//  sCmd        - absolutely, you must set the value to Null.
//  TLC_ARGS
//    arg0:UINT - type: GL_FRAGMENT_SHADER, GL_VERTEX_SHADER
//    arg1:char*- buffer
//    arg2:INT  - length(option)
INT LcDev_CreateShaderFromTxtBuffer(GL_SHADER* s, PLC_ARGS arg);


// Create Shader from compiled file.
//  sCmd        - absolutely, you must set the value to Null.
//  TLC_ARGS
//    arg0:UINT - type: GL_FRAGMENT_SHADER, GL_VERTEX_SHADER
//    arg1:char*- "file name"
INT LcDev_CreateShaderFromBinFile  (GL_SHADER* s, PLC_ARGS arg);


// Create Shader from compiled buffer.
//  sCmd        - absolutely, you must set the value to Null.
//  TLC_ARGS
//    arg0:UINT - type: GL_FRAGMENT_SHADER, GL_VERTEX_SHADER
//    arg1:char*- buffer
//    arg2:INT  - length
INT LcDev_CreateShaderFromBinBuffer(GL_SHADER* s, PLC_ARGS arg);


// Simple Create glProgram with vertex and fragment shader
INT LcDev_CreateGlProgram(  GL_SHADER* pProg
						  , GL_SHADER* pShdVtx
						  , GL_SHADER* pShdFrg
						  , const char* s_vtx, const char* s_frg);


// Create Effect from text file
//  sCmd         - absolutely, you must set the value to Null.
//  pDev         - for call pDev->SetTexture(stage...). if you do not use the pDev then you need to call te pDev->SetTexture(....) with using tetxure.
//  TLC_ARGS
//    arg0:char* - "vertex shader file name"
//    arg1:char* - "fragment shader file name"
//    arg2:char**- Attribute list	ex) char* attlist[] ={ "vs_pos", "vs_dif", NULL};
INT LcDev_CreateEffectFromTxtFile  (char* sCmd,PLC_EFFECT* pOut, PLC_DEVICE pDev, PLC_ARGS arg);


// Create Effect from Text buffer.
//  sCmd         - absolutely, you must set the value to Null.
//  pDev         - for call pDev->SetTexture(stage...). if you do not use the pDev then you need to call te pDev->SetTexture(....) with using tetxure.
//  TLC_ARGS
//    arg0:char* - vertex shader buffer address
//    arg1:char* - fragment shader buffer address
//    arg2:char**- Attribute list	ex) char* attlist[] ={ "vs_pos", "vs_dif", NULL};
INT LcDev_CreateEffectFromTxtBuffer(char* sCmd,PLC_EFFECT* pOut, PLC_DEVICE pDev, PLC_ARGS arg);

// get the default effect defined in system.
// idx: [LC_SHADER_BEGIN, LC_SHADER_NUM]
PLC_EFFECT LcDev_DefaultEffect(INT idx);




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Multiple Rendering Context with device.

DCL_INTERFACE ILC_MRC : public ILC_Object
{
	DCL_CLASS_DESTROYER(	ILC_MRC	);

	virtual INT		Query(char* sCmd, LC_HANDLE pData)=0;						// LC_QUERY_GET_SCREEN_WIDTH_HEIGHT...

	virtual	INT		Begin()=0;													// Begine the Multiple Rendering
	virtual	INT		End()=0;													// End the other target Rendering
};

typedef	ILC_MRC*	PLC_MRC;


// Create Font from File
//  sCmd             - absolutely, you must set the value to Null.
//  TLC_ARGS
//    arg0:LC_HANDLE - Window Handle(HWND)
//    arg1:INT      - Red bit
//    arg2:INT      - Green bit
//    arg3:INT      - Blue bit
//    arg4:INT      - Alpha bit
//    arg5:INT      - Depth bit
//    arg6:INT      - Stencil bit
//    if( arg1 ~arg7 are zero then it will be created same format of the main device context.

INT LcDev_CreateMRC(char* sCmd, PLC_MRC* pOut, PLC_ARGS arg);




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Frame buffer object for off screen rendering

DCL_INTERFACE ILC_FBO : public ILC_Object
{
	DCL_CLASS_DESTROYER( ILC_FBO );

	virtual INT			Release(INT bDecreaseRefCount=LC_TRUE)=0;
	virtual INT			Query(char* sCmd, LC_HANDLE pData)=0;

	virtual INT			Begin()=0;
	virtual INT			End()=0;

	virtual PLC_TEXTURE	ColorBuffer()=0;										// Get the color buffer of frame buffer
	virtual PLC_TEXTURE	DepthBuffer()=0;										// Get the depth buffer of frame buffer
};

// for Query
#define LC_QUERY_EXTERN_COLOR_BUF        (char*)"External color frame buffer"
#define LC_QUERY_EXTERN_DEPTH_BUF        (char*)"External depth frame buffer"


// Create FBO Instance
//  sCmd         - absolutely, you must set the value to Null.
//  TLC_ARGS
//    arg0:INT   - buffer Width.           default : 512
//    arg1:INT   - buffer Height.          default : 512
//    arg2:INT   - color buffer format.    default : LC_FMT_RGBA
//    arg3:INT   - color buffer mip level. default : 0
INT LcDev_CreateFBO( char* sCmd, PLC_FBO* pOut, PLC_ARGS =NULL);




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Application Frame Work

DCL_INTERFACE ILC_AppFrame : public ILC_Object
{
	DCL_CLASS_DESTROYER(	ILC_AppFrame	);

	virtual INT		Release   (INT bDecreaseRefCount=LC_TRUE){return LC_OK;   }
	virtual INT		Query     (char*, LC_HANDLE){return LC_EFAIL;}

	virtual INT		Create    (PLC_ARGS  =NULL)	{return LC_OK;   }				// call when the instance create time.
	virtual INT		Cleanup   ()                {return LC_OK;   }				// cleanup the initial values and condition
	virtual INT		Run       (LC_HANDLE =NULL)	{return LC_OK;   }				// include while loop
	virtual INT		Proc      (LC_HANDLE =NULL)	{return LC_OK;   }				// include one execution
	virtual INT		Init      ()                {return LC_OK;   }				// application init
	virtual INT		Destroy   ()                {return LC_OK;   }				// destroy the rendering data
	virtual INT		FrameMove ()                {return LC_OK;   }				// update the rendering data
	virtual INT		Render    ()                {return LC_OK;   }				// Rendering
};

typedef	ILC_AppFrame*	PLC_APPFRAME;

// user defininig functions.
extern PLC_APPFRAME LcSys_GetMainApp();											// Get    the main application instance. It must be implemented in code.
extern INT          LcSys_CreateAppFrame(char* sCmd								// Create the main application instance. It must be implemented in program start.
										, PLC_APPFRAME* pOut
										, PLC_ARGS =NULL);

extern INT          LcSys_DestroyAppFrame();									// Release the main application instance. It must be implemented in program end.
extern INT          LcSys_ProcAppFrame(LC_HANDLE);								// Run the main application instance.
extern INT          LcSys_ExecAppFrame(char* sCmd, LC_HANDLE pData);			// Execute by Command




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// 3D Application Auxiliary

// GLC 3D Index, Vertex Format
namespace LC3D
{
	// 16-bit Triangle Index
	#if defined(_MSC_VER)
	  #pragma pack(push, 1)
	#endif

	struct VtxFce16
	{
		union
		{
			struct{ WORD  a; WORD  b; WORD  c;};
			struct{ WORD _0; WORD _1; WORD _2;};
			WORD m[3];
		};

		VtxFce16() : a(0), b(0), c(0){}
		VtxFce16(WORD A,WORD B,WORD C) : a(A), b(B), c(C){}
		VtxFce16(const WORD* v)	{ a = v[0]; b = v[1]; c = v[2];	}

		operator WORD*()			{	return (WORD*)&a;		}
		operator const WORD*() const{	return (const WORD*)&a;	}

		enum { FVF = (LC_FMT_WORD), };
	}
	#if defined(_MSC_VER)
	  #pragma pack(pop)
	#else
	  __attribute__((packed))
	#endif
	;


	// 16-bit Quad Index
	#if defined(_MSC_VER)
	  #pragma pack(push, 1)
	#endif

	struct VtxQuad16
	{
		union
		{
			struct{ WORD  a; WORD  b; WORD  c; WORD  d; WORD  e; WORD  f;};
			struct{ WORD _0; WORD _1; WORD _2; WORD _3; WORD _4; WORD _5;};
			WORD m[6];
		};

		VtxQuad16()
			: a(0), b(0), c(0), d(0), e(0), f(0){}

		VtxQuad16(WORD A, WORD B, WORD C, WORD D, WORD E, WORD F)
			: a(A), b(B), c(C), d(D), e(E), f(F){}

		VtxQuad16(const WORD* v)
		{
			a=v[0]; b=v[1]; c=v[2]; d=v[3]; b=v[4]; c=v[5];
		}

		operator WORD*()			{	return (WORD*)&a;		}
		operator const WORD*() const{	return (const WORD*)&a;	}

		enum { FVF = (LC_FMT_WORD), };
	}
	#if defined(_MSC_VER)
	  #pragma pack(pop)
	#else
	  __attribute__((packed))
	#endif
	;


	// 32-bit Triangle Index
	#if defined(_MSC_VER)
	  #pragma pack(push, 1)
	#endif

	struct VtxFce32
	{
		union
		{
			struct{ UINT  a; UINT  b; UINT  c;};
			struct{ UINT _0; UINT _1; UINT _2;};
			UINT m[3];
		};

		VtxFce32(): a(0), b(0), c(0){}
		VtxFce32(UINT A, UINT B, UINT C): a(A), b(B), c(C){}
		VtxFce32(const UINT* v){ a=v[0]; b=v[1]; c=v[2]; }

		operator UINT*()			{	return (UINT*)&a;		}
		operator const UINT*() const{	return (const UINT*)&a;	}

		enum { FVF = (LC_FMT_DWORD), };
	}
	#if defined(_MSC_VER)
	  #pragma pack(pop)
	#else
	  __attribute__((packed))
	#endif
	;

	// 32-bit Quadrangle Index
	#if defined(_MSC_VER)
	  #pragma pack(push, 1)
	#endif

	struct VtxQuad32
	{
		union
		{
			struct{ UINT  a; UINT  b; UINT  c; UINT  d; UINT  e; UINT  f;};
			struct{ UINT _0; UINT _1; UINT _2; UINT _3; UINT _4; UINT _5;};
			WORD m[6];
		};

		VtxQuad32()
			: a(0), b(0), c(0), d(0), e(0), f(0){}

		VtxQuad32(UINT A, UINT B, UINT C, UINT D, UINT E, UINT F)
			: a(A), b(B), c(C), d(D), e(E), f(F){}

		VtxQuad32(const UINT* v)
		{
			a=v[0]; b=v[1]; c=v[2]; d=v[3]; b=v[4]; c=v[5];
		}

		operator UINT*()			{	return (UINT*)&a;		}
		operator const UINT*() const{	return (const UINT*)&a;	}

		enum { FVF = (LC_FMT_DWORD), };
	}
	#if defined(_MSC_VER)
	  #pragma pack(pop)
	#else
	  __attribute__((packed))
	#endif
	;

	////////////////////////////////////////////////////////////////////////////
	// Float type

	struct Vtx
	{
		LC_FLOAT3	p;															// Position Vector
		enum { FVF = (LC_FVF_XYZ), };
	};

	struct VtxD
	{
		LC_FLOAT3	p;															// Position Vector
		LC_COLORB	d;															// Diffuse
		enum { FVF = (LC_FVF_XYZ|LC_FVF_DIFFUSE), };
	};

	struct VtxDUV1
	{
		LC_FLOAT3	p;															// Position Vector
		LC_COLORB	d;															// Diffuse
		LC_FLOAT2	t;															// Texture Coord
		enum { FVF = (LC_FVF_XYZ|LC_FVF_DIFFUSE|LC_FVF_TEX0), };
	};

	struct VtxN
	{
		LC_FLOAT3	p;															// Position Vector
		LC_FLOAT3	n;															// Normal Vector
		enum { FVF = (LC_FVF_XYZ|LC_FVF_NORMAL), };
	};

	struct VtxUV1
	{
		LC_FLOAT3	p;															// Position Vector
		LC_FLOAT2	t;															// Texture Coord
		enum { FVF = (LC_FVF_XYZ|LC_FVF_TEX0), };
	};

	struct VtxNUV1
	{
		LC_FLOAT3	p;															// Position Vector
		LC_FLOAT3	n;															// Normal Vector
		LC_FLOAT2	t;															// Texture Coord
		enum { FVF = (LC_FVF_XYZ|LC_FVF_NORMAL|LC_FVF_TEX0), };
	};

	struct VtxNDUV1
	{
		LC_FLOAT3	p;															// Position Vector
		LC_FLOAT3	n;															// Normal Vector
		LC_COLORB	d;															// Diffuse
		LC_FLOAT2	t;															// Texture Coord
		enum { FVF = (LC_FVF_XYZ|LC_FVF_NORMAL|LC_FVF_DIFFUSE|LC_FVF_TEX0), };
	};

	struct VtxNDUV1B
	{
		LC_FLOAT3	p;															// Position Vector
		LC_FLOAT3	n;															// Normal Vector
		LC_COLORB	d;															// Diffuse
		LC_FLOAT2	t;															// Texture Coord
		LC_FLOAT4	b;															// vertex blending index: x,y weight z
		enum { FVF = (LC_FVF_XYZ    |LC_FVF_NORMAL|\
					  LC_FVF_DIFFUSE|LC_FVF_TEX0  |LC_FVF_BLND), };
	};
};




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
//	LC_Font Interface for printing string to 3d device.

enum ELC_FONT
{
	LC_FONT_AN_FTF = 0x0	,													// font analyzer. analyzed by freetype font
	LC_FONT_AN_INTERNAL		,													// analyzed by internal system

	LC_FONT_ALIGN_LT = 0x0	,													// alignment left top
	LC_FONT_ALIGN_RT		,													// alignment right top
	LC_FONT_ALIGN_CT		,													// alignment center top
	LC_FONT_ALIGN_LM		,													// alignment left middle
	LC_FONT_ALIGN_RM		,													// alignment right middle
	LC_FONT_ALIGN_CM		,													// alignment center middle
	LC_FONT_ALIGN_LB		,													// alignment left bottom
	LC_FONT_ALIGN_RB		,													// alignment right bottom
	LC_FONT_ALIGN_CB		,													// alignment center bottom

	// for {Set|Get}Attrib
	LC_FONT_ALIGN	 =0x1001,													// alignment
	LC_FONT_COLOR			,													// color. it needs LC_COLORF address
	LC_FONT_POSITION		,													// position. it needs LC_FLOAT3 address
	LC_FONT_SCALING			,													// scaling. it needs LC_FLOAT3 address
	LC_FONT_SCALEUP			,													// font resolution scaling up. Mininum is 1 and Maximum is 4
	LC_FONT_CHAR_COUNT		,													// Character Number(count)
	LC_FONT_RECT			,													// Character Rectangle. needs LC_RECTF. if you use this data to position you needs scale up value by LC_FONT_SCALEUP
	LC_FONT_RECT_SCALEUP	,													// Character Rectangle with scale up value.
};

struct TLC_FONT
{
	char*	src_n	;															// Resource Name for Search. LCCMD_DEFAULT is embedded font.
	INT		fnt_a	;															// Font type: freetype, internal
	INT		fnt_h	;															// Height
	INT		fnt_f	;															// Filtering for anti-aliasing
	BYTE**	fnt_p	;															// Buffer address
	INT		fnt_l	;															// Buffer Length

	INT		fnt_rH	;															// resolution of horizental
	INT		fnt_rV	;															// resolution of vertical

	TLC_FONT()	: src_n(NULL), fnt_a(1), fnt_h(0), fnt_f(1)
				, fnt_p(NULL), fnt_l(0)
				, fnt_rH(0), fnt_rV(0){}

	TLC_FONT(char*	s,	INT a =1, INT h=12, INT anti_alias=1)
				: src_n(s   ), fnt_a(a), fnt_h(h), fnt_f(anti_alias)
				, fnt_p(NULL), fnt_l(0)
				, fnt_rH(  0), fnt_rV(0){}

	TLC_FONT(char* s, BYTE** b, INT l
				, INT a=1, INT h=12, INT anti_alias=1
				, INT rH =0, INT rV=0)
				: src_n(s), fnt_a(a), fnt_h(h), fnt_f(anti_alias)
				, fnt_p(b), fnt_l(l)
				, fnt_rH(rH), fnt_rV(rV){}
};

DCL_INTERFACE ILC_Font : public ILC_Object
{
	DCL_CLASS_DESTROYER(	ILC_Font	);


	virtual INT		Release(INT bDecreaseRefCount=LC_TRUE)=0;
	virtual INT		Query(char* sCmd, LC_HANDLE pData)=0;

	virtual INT		DrawTxt ( PLC_SPRITE       pSprite= NULL					// Rendering with sprite pointer
							, INT              Begin  = 0						// Begin String Index	start is 0
							, INT              End    =-1						// End must be greater then Begin value except for the -1. "End index is -1" means to draw all string from begin
							, const LC_FLOAT3* vcTrn  = NULL					// Position
							, const LC_COLORF* color  = NULL					// Color
							)=0;

	virtual INT		String  (const char* sMsg)=0;								// Setting the string
	virtual	INT		Color   (const LC_COLORF*)=0;								// String color
	virtual INT		Position(const LC_FLOAT3*)=0;								// String Position
	virtual INT		Scaling (const LC_FLOAT3*)=0;								// scaling: float3

	virtual const char * const String  () const =0;								// return saved string in font instance
	virtual const FLOAT* const Color   () const =0;								// Get color
	virtual const FLOAT* const Position() const =0;								// Get position
	virtual PLC_TEXTURE        Texture () const =0;								// Get Texture

	virtual INT	Rect(LC_RECTF* pRc, INT Idx= LC_DEFAULT) =0;					// Get Rect with index. return rc value is left, top, width, height. if index = LC_DEFAULT then return the all region(left, top, width, height)
	virtual INT VtxLst(LC_FLOAT3* OutPos, LC_FLOAT2* OutTex)=0;					// Setup the Vertex List. OutPos and OutTex need 4 array of LCXVECTOR2.
};

typedef	ILC_Font*	PLC_FONT;


#define LCCMD_DEFAULT	(char*)"GLC_DEFAULT"

// Create Font from File
//  sCmd             - absolutely, you must set the value to Null.
//  TLC_ARGS
//    arg0:UINT      - Resource Type: LC_SRC_T_{NONE| FILE | MEM}. None is system font.
//    arg1:LC_HANDLE - TLC_Font*
//    arg2:LC_HANDLE - PLC_SPRITE
INT LcDev_CreateFont(char* sCmd, PLC_FONT* pOut, PLC_ARGS arg);




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// for android

#ifndef   INTERFACE_JNICB_BASE
  #define INTERFACE_JNICB_BASE	(char*)"gpack/JniCbBase"
#endif

#ifndef   INTERFACE_JNICB_SMD
  #define INTERFACE_JNICB_SMD	(char*)"gpack/JniCbSmd"
#endif

#ifndef   INTERFACE_JNICB_NET
  #define INTERFACE_JNICB_NET	(char*)"gpack/JniCbNet"
#endif

INT LcSys_SetupJvmEnv(LC_HANDLE* ppEnv, LC_HANDLE* ppClzz, const char* s_clss);	// JVM AttachCurrentThread and Find default class.
INT LcSys_ReleaseJvmEnv();														// JVM DetachhCurrentThread.
INT LcSys_JvmStaticMethod(LC_HANDLE* ppEnv,LC_HANDLE* pClzz,LC_HANDLE* pMethod	// LcSys_SetupJvmEnv + GetStaticMethodID
						,const char* clss,const char* method,const char* sign);	// class name, method name, method signature


LC_HANDLE LcAsset_Open   (char* fileName, const char* clss, const char* fnc);	// for android file open(read only) in asset folder
void      LcAsset_Close  (LC_HANDLE fp);										// for android file open(read only) in asset folder
INT       LcAsset_Read   (LC_HANDLE fp, void* buf, INT count);					// similar fread for asset file
INT       LcAsset_Seek   (LC_HANDLE fp, INT offset, INT whence);				// similar fseek for asset file
INT       LcAsset_Size   (LC_HANDLE fp);										// similar for file size.
LC_HANDLE LcAsset_Buffer (LC_HANDLE fp);										// get the entire buffer.


#if defined(__ANDROID__) || defined(ANDROID)
#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

// the below functions were redefined if jni.h and they were implemented in glc system.
// jint JNI_OnLoad(JavaVM* vm, void* reserved);
// void JNI_OnUnload(JavaVM* vm, void* reserved);

// additional functions for android system.
JavaVM* JNI_OnGetJavaVM();

#ifdef __cplusplus
}
#endif

#endif // __ANDROID__

#endif //_LcCore_H_

