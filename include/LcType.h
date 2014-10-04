// GalicSoft Game Library Collection. Copyright(C) GALICSOFT. All rights reserved.
//
// Type definition.
//
// platform identity directive
//   windows : _MSC_VER, _PC_WIN32_
//   linux   : _PC_LINUX_
//   iphone  : __IOS__
//   android : __ANDROID__
//   bada    : __TIZEN__
//
////////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER)
  #pragma once
#endif

#ifndef _LcType_H_
#define _LcType_H_

typedef	int                    INT      ;						// basic type
typedef	signed int             INT32    ;
typedef	unsigned int           UINT32   ;
typedef	signed char            INT8     ;
typedef	unsigned char          UINT8    ;
typedef	signed short int       INT16    ;
typedef	unsigned short int     UINT16   ;
typedef	short int              SHORT    ;
typedef	unsigned short int     USHORT   ;

#if defined(__IOS__)
  typedef int                  BOOL     ;
#endif

typedef	long int               LONG     ;
typedef	long int               HRESULT  ;
typedef float                  FLOAT    ;
typedef double                 DOUBLE   ;
typedef	unsigned char          BYTE     ;
typedef	signed char            SCHAR    ;
typedef	unsigned short         WORD     ;
typedef unsigned short         MCHAR    ;						// wide or Multi byte character
typedef	unsigned int           UINT     ;
typedef	unsigned long int      ULONG    ;
typedef unsigned int           SIZE_T_  ;						// size_t
typedef char*                  CSTR     ;						// for string

#if defined(_MSC_VER)											// double word
  typedef unsigned long        DWORD    ;
#else
  typedef unsigned int         DWORD    ;
#endif

#if defined(__GNUC__)											// 64bit int (double int)
  typedef long long            DINT     ;
  typedef unsigned long long   UDINT    ;
#else
  typedef __int64              DINT     ;
  typedef unsigned __int64     UDINT    ;
#endif

typedef DINT                   INT64    ;						// 64bit int
typedef UDINT                  UINT64   ;						// 64bit unsigned int
typedef DINT                   LLONG    ;						// 64bit long
typedef	UDINT                  QWORD    ;						// q-word
typedef LLONG                  L_PTR    ;						// 64bit long pointer
typedef LLONG*                 PL_PTR   ;
typedef void*                  LPVOID   ;						// void pointer

typedef BYTE                   COLOR8   ;						//  8bit color
typedef WORD                   COLOR16  ;						// 16bit color
typedef UINT                   COLOR32  ;						// 32bit argb 0xAARRGGBB color
typedef UDINT                  COLOR64  ;						// 64bit color

typedef	LPVOID                 LC_HANDLE;						// for mobile device
typedef UINT                   LC_SOCKET;						// socket descriptor
typedef	UINT                   LC_STATE ;						// device state.
typedef	INT                    LC_DEVICE;						// device handle
typedef UINT                   LC_VB    ;						// VBO(Vertex Buffer Object)
typedef UINT                   LC_IB    ;						// IBO(Index Buffer Object == VBO)

typedef UINT                   WPARAM   ;						// Portability of Microsoft Windows Application
typedef LONG                   LPARAM   ;
typedef LONG                   LRESULT  ;

typedef UINT                   GL_SHADER;						// OpenGL shader object
typedef UINT                   GL_PROGRAM;						// OpenGL shader Program

#if !defined(_MSC_VER)											// Handle for Microsoft windows and X-window system
  struct HWND__ { int unused; };
#endif

#if defined(_MSC_VER)
   typedef struct HWND__      *LC_HWND  ;

#elif defined(_PC_LINUX_)

  typedef struct tagHNWD
  {
	  LC_HANDLE w, d, n, t;										// window, display, info, temp
  } *LC_HWND;

#else
  typedef void* LC_HWND;

#endif

#if defined(_MSC_VER)											// define callback
  #ifndef LC_CALLBACK
    #define LC_CALLBACK        __stdcall
  #endif

  #ifndef LC_WINAPI
    #define LC_WINAPI          __stdcall
  #endif

#else
  #ifndef LC_CALLBACK
    #define LC_CALLBACK
  #endif

  #ifndef LC_WINAPI
    #define LC_WINAPI
  #endif

#endif


#ifndef CONST													// const and null
  #define CONST   const
#endif

#ifndef NULL
  #define NULL    0
#endif

#ifndef L_NULL
  #define L_NULL  0
#endif

#ifndef L_NIL
  #define L_NIL	(LC_HANDLE)0
#endif


#if defined(_MSC_VER)
  #pragma pack(push, 1)
#endif

typedef struct _LCUUID											// 128 uuid number
{
	ULONG	d1;
    USHORT	d2;
    USHORT	d3;
    BYTE	d4[8];
}
#if defined(_MSC_VER)
  #pragma pack(pop)
#else
  __attribute__((packed))
#endif
LCUUID;


enum ELC_CONSTANT												// GLC basic constant
{
	LC_SDK_VER               =  0x00030112,						// VERSION: GLC Library Version: 03.01.10
	LC_SDK_DATE              =  0x20141131,						// VERSION: Last Build Date 2014-11-31

	LC_DEADBEEF              =  0xDeadBeef,						// COMMON: crash or deadlock
	LC_BAADFOOD              =  0xBaadF00d,						// COMMON: indicate uninitialised allocated with LocalAlloc(LMEM_FIXED) on microsoft system
	LC_TRUE                  =  1         ,						// COMMON: TRUE
	LC_FALSE                 =  0         ,						// COMMON: FALSE

	LC_FTYPE_FOLDER          =  0x00000010,						// FILE TYPE: folder
	LC_FTYPE_FILE            =  0x00000020,						// FILE TYPE: file
	LC_FTYPE_SYS             =  0x00000004,						// FILE TYPE: system
	LC_FILE_BEGIN            =  0x00000000,						// FILE POINER OFFSET: SEEK_SET,
	LC_FILE_CURRENT          =  0x00000001,						// FILE POINER OFFSET: SEEK_CUR,
	LC_FILE_END              =  0x00000002,						// FILE POINER OFFSET: SEEK_END,

	LC_FILE_ALREADY_OPEN     =  0x000000F1,						// FILE RETURN: the file is already opend
	LC_FILE_CANNT_ACCESS     =  0xFFFFFFF1,						// FILE RETURN: access failed
	LC_FILE_NOT_OPENED       =  0xFFFFFFF2,						// FILE RETURN: file not opened
	LC_FILE_GET_LENGTH_ERR   =  0xFFFFFFF3,						// FILE RETURN: error the file length

	LC_UNKNOWN               =  0x00000000,						// IUPUT/OUTPUT: unknown or not defined
	LC_DEFAULT               =  ((UINT)-1),						// IUPUT/OUTPUT: default value less then zero to failed process
	LC_FINISH                =  0x7FFFFFFF,						// IUPUT/OUTPUT: finish or end state.
	LC_INFINITE              =  LC_DEFAULT,						// IUPUT/OUTPUT: finite max bit(all bits 1)
	LC_DEFAULT_NAME          =  160       ,						// IUPUT/OUTPUT: Max Name Length

	LC_OK                    =  0x00000000,						// PROCESSING RESULT: Succeeded default value
	LC_EFAIL                 = -1         ,						// PROCESSING RESULT: Failed default value
	LC_INVALID_CALL          =  0xFFFF0001,						// PROCESSING RESULT: Invalid funtion or device called
	LC_CANNT_ALLOC           =  0xFFFF0002,						// PROCESSING RESULT: resource alloc failed
	LC_CANNT_FIND_RESOURCE   =  0xFFFF0003,						// PROCESSING RESULT: resource find failed
	LC_NOT_IMPLEMENTED       =  0xFFFF0004,						// PROCESSING RESULT: funtion or module is not implemented
	LC_CANNT_ACQUIRE_DEVICE  =  0xFFFF0005,						// PROCESSING RESULT: device/driver acquire failed
	LC_INVALID_RESOURCE      =  0xFFFF0006,						// PROCESSING RESULT: resource spoied or not matched
	LC_DEPRECATED            =  0xFFFF0010,						// PROCESSING RESULT: deprecated
	LC_INVALID_DEVICE        = -1         ,						// PROCESSING RESULT: default device error

	LC_MAX_PATH              =  260       ,						// DICTORY/FILE: short length for relative path
	LC_MAX_PATH2             =  360       ,						// DICTORY/FILE: long length for absolute path
	LC_MAX_DRIVE             =   16       ,						// DICTORY/FILE: drive name
	LC_MAX_DIR               =  240       ,						// DICTORY/FILE: directory name
	LC_MAX_FNAME             =  240       ,						// DICTORY/FILE: file name
	LC_MAX_EXT               =   16       ,						// DICTORY/FILE: file extention

	LC_RSC_GPACK             =  0x4B435047,						// RESOURCE: G-pack Resource ID = "KCPG" <-GPCK: Little endian
	LC_RSC_GPACK_            =  0x4750434B,						// RESOURCE: G-pack Resource ID = "GPCK"
	LC_RSC_VER               =  0x20100000,						// RESOURCE: version
	LC_RSC_FNAME             = 128,								// RESOURCE: file name in resource
	LC_RSC_HEADER            = 128,								// RESOURCE: file header offset
	LC_RSC_NAME              =  64,								// RESOURCE: resource name or id max length
	LC_RSC_SID               =  40,								// RESOURCE: short id max length for animation or hierarchy..

	LC_SRC_T_NONE            =  0x00000000,						// SOURCE: from none
	LC_SRC_T_FILE            =  0x00000001,						// SOURCE: from file
	LC_SRC_T_MEM             =  0x00000002,						// SOURCE: from memory buffer with information
	LC_SRC_T_BUF             =  0x00000003,						// SOURCE: from simple buffer
	LC_SRC_T_RSC             =  0x00000004,						// SOURCE: from resource on windows system

	LC_OBJ_UNKNOWN           =  LC_UNKNOWN,						// RESOURCE OBJECT: UnKnown or undefined Object
	LC_OBJ_DEVICE            =  0x00002001,						// RESOURCE OBJECT: 3d opengl or direct3d Device
	LC_OBJ_SPRITE            =  0x00002002,						// RESOURCE OBJECT: 2d Sprite
	LC_OBJ_SPRITE_C          =  0x00002011,						// RESOURCE OBJECT: 2d Sprite Collector
	LC_OBJ_SPRITE_L          =  0x00002012,						// RESOURCE OBJECT: 2d Sprite Layer
	LC_OBJ_BUF               =  0x00002021,						// RESOURCE OBJECT: simple buffer
	LC_OBJ_FONT              =  0x00002022,						// RESOURCE OBJECT: FONT face
	LC_OBJ_FONT_BUF          =  0x00002023,						// RESOURCE OBJECT: FONT buffer
	LC_OBJ_IMAGE             =  0x00002101,						// RESOURCE OBJECT: image
	LC_OBJ_TEXTURE           =  LC_OBJ_IMAGE,					// RESOURCE OBJECT: texture
	LC_OBJ_GUI               =  LC_OBJ_SPRITE,					// RESOURCE OBJECT: Gui
	LC_OBJ_MODEL2D           =  0x00002111,						// RESOURCE OBJECT: 2D Model
	LC_OBJ_TDA               =  0x00002112,						// RESOURCE OBJECT: Tda File
	LC_OBJ_TDM               =  0x00002113,						// RESOURCE OBJECT: Tdm File
	LC_OBJ_TDS               =  0x00002114,						// RESOURCE OBJECT: Tds File
	LC_OBJ_MODEL3D           =  0x00002121,						// RESOURCE OBJECT: Simple, billboard, or unknown 3D model.
	LC_OBJ_SLD               =  0x00002122,						// RESOURCE OBJECT: 3D Solid model
	LC_OBJ_RGD               =  0x00002123,						// RESOURCE OBJECT: 3D Rigid body model
	LC_OBJ_SKN               =  0x00002124,						// RESOURCE OBJECT: 3D Skinning animation model
	LC_OBJ_MDS               =  0x00002125,						// RESOURCE OBJECT: 3D animation assemble model
	LC_OBJ_FBX               =  0x00002126,						// RESOURCE OBJECT: 3D Max FBX File
	LC_OBJ_IMG               =  0x00002200,						// RESOURCE OBJECT: image
	LC_OBJ_BMP               =  0x00002201,						// RESOURCE OBJECT: image bmp
	LC_OBJ_TGA               =  0x00002202,						// RESOURCE OBJECT: image tga
	LC_OBJ_PNG               =  0x00002203,						// RESOURCE OBJECT: image png
	LC_OBJ_JPG               =  0x00002204,						// RESOURCE OBJECT: image jpg
	LC_OBJ_GPT               =  0x00002205,						// RESOURCE OBJECT: image gptf
	LC_OBJ_RNT               =  0x00002206,						// RESOURCE OBJECT: render target
	LC_OBJ_MEDIA             =  0x00002300,						// RESOURCE OBJECT: MEDIA
	LC_OBJ_AUDIO             =  0x00002311,						// RESOURCE OBJECT: sound
	LC_OBJ_VIDEO             =  0x00002312,						// RESOURCE OBJECT: video
	LC_OBJ_WAV               =  0x00002321,						// RESOURCE OBJECT: wave
	LC_OBJ_MIDI              =  0x00002322,						// RESOURCE OBJECT: midi
	LC_OBJ_OGG               =  0x00002323,						// RESOURCE OBJECT: ogg
	LC_OBJ_MP3               =  0x00002324,						// RESOURCE OBJECT: mp3
	LC_OBJ_GPS               =  0x00002325,						// RESOURCE OBJECT: gpsf
	LC_OBJ_NSD               =  0x00002330,						// RESOURCE OBJECT: Non-standard data or native.
	LC_OBJ_CSV               =  0x00002331,						// RESOURCE OBJECT: csv
	LC_OBJ_XML               =  0x00002332,						// RESOURCE OBJECT: XML
	LC_OBJ_INPUT             =  0x00002300,						// RESOURCE OBJECT: Input
	LC_OBJ_SCRIPT            =  0x00002501,						// RESOURCE OBJECT: Script file
	LC_SND_PCM               =  0x00001001,						// Sound Format: pcm
	LC_MAX_BONE              = 1024       ,						// Maximum skinning bone number for weighting and indexing
	LC_MAX_BBONE             =   46       ,						// Maximum blending bone number in hardware acceleration.
	LC_MAX_PARSE_LINE        =  512       ,						// Maximum parsing line for text data.
	LC_MAX_EGL_CONFIG        =   16       ,						// SYSTEM: Max EGL Configuration
	LC_MAX_KEY               =  256       ,						// SYSTEM: Keypad or keyboard
	LC_MAX_TSB               =   16       ,						// SYSTEM: touch screen
	LC_MAX_SENSOR            =   32       ,						// SYSTEM: sensor
	LC_IP_LEN                =   20       ,						// SYSTEM: ip address lentgh
	LC_LOOP_DONE             =  LC_FINISH ,						// Loop state: data loop done state
	LC_LOOP_STOP             =  0x00000000,						// Loop state: data loop stop state
	LC_LOOP_RESET            =  0x00000001,						// Loop state: data loop reset state
	LC_LOOP_SET              =  0x00000002,						// Loop state: data loop set state
	LC_LOOP_PAUSE            =  0x00000003,						// Loop state: data loop pause state
	LC_LOOP_PLAY             =  0x00000004,						// Loop state: data loop playing state
};

enum LC_VAR														// GLC Engine stored global variable type. set/get use the LcVar_{} functions
{
	LC_VAR_TYPE_ENGINE       =  0,								// GLOBAL VARIABLE: GLC Engine type of mobile or pc Platform LC_VAR_SYS_{WIN32|LINUX|ANDROID|IOS|BADA}
	LC_VAR_VERSION           ,									// GLOBAL VARIABLE: GLC Version(_n0) and date(_n1)
	LC_VAR_LOG               ,									// GLOBAL VARIABLE: Log Options
	LC_VAR_TIME              ,									// GLOBAL VARIABLE: Application time, frame rate
	LC_VAR_GRAPHICS          ,									// GLOBAL VARIABLE: Graphic type _n0(LC_VAR_GRAPHICS_NONE|GL|DX) _n1:Major _n2:Minor1 _n3:minor2 _n3:Minor3 _n4:minor4
	LC_VAR_REF_COUNT         ,									// GLOBAL VARIABLE: created instance count
	LC_VAR_SCREEN            ,									// GLOBAL VARIABLE: application screen position(i[0], i[1]), screen width and height(i[2], i[3])
	
	LC_VAR_DISPLAY           ,									// GLOBAL VARIABLE: device display r, g, b, a, depth, stencil bit, width and height.
	LC_VAR_WIN_HANDLE        ,									// GLOBAL VARIABLE: window hadle(_p0) for default 3d device and application etc...
	LC_VAR_GLDEV			 ,									// GLOBAL VARIABLE: opengl device device(_p0), Egl Display hadle(_p1), Egl Surface hadle(_p2), Egl Context hadle(_p3), and GL_MAX_TEXTURE_IMAGE_UNITS number
	LC_VAR_GUI               ,									// GLOBAL VARIABLE: just for gui layer object.
	LC_VAR_SPRITE            ,									// GLOBAL VARIABLE: just for sprite object.
	LC_VAR_APP_MAIN          ,									// GLOBAL VARIABLE: Application main intance pointer
	LC_VAR_APP_INPUT         ,									// GLOBAL VARIABLE: Application input intance pointer
	LC_VAR_APP_NET           ,									// GLOBAL VARIABLE: Application network instance pointer
	LC_VAR_APP_CAMERA        ,									// GLOBAL VARIABLE: Application camera instance pointer

	LC_VAR_SYS_NONE          =  0x00000000,						// GLOBAL VARIABLE: PLATFORM: for LcVar_Platform()
	LC_VAR_SYS_WIN32         =  0x00000001,						// GLOBAL VARIABLE: PLATFORM: Windows32
	LC_VAR_SYS_LINUX         =  0x00000002,						// GLOBAL VARIABLE: PLATFORM: linux pc
	LC_VAR_SYS_ANDROID       =  0x00000003,						// GLOBAL VARIABLE: PLATFORM: android
	LC_VAR_SYS_IOS           =  0x00000004,						// GLOBAL VARIABLE: PLATFORM: ios
	LC_VAR_SYS_TIZEN         =  0x00000005,						// GLOBAL VARIABLE: PLATFORM: tizen = old bada.

	LC_VAR_GRAPHICS_NONE     =  0x00000000,						// GLOBAL VARIABLE: GRAPHICS:
	LC_VAR_GRAPHICS_GL       =  0x00000010,						// GLOBAL VARIABLE: GRAPHICS: OpenGL
	LC_VAR_GRAPHICS_DX       =  0x00000020,						// GLOBAL VARIABLE: GRAPHICS: Direct3D

	LC_VAR_USER_DATA         =  32        ,						// GLOBAL VARIABLE: user defined data starting index
	LC_VAR_TOTAL             =  64        ,
};

enum LC_VAR_SYS
{
	LC_LOG_SERIAL            =  0x00000000,						// LOG: default value. printf or LogCat
	LC_LOG_FILE              =  0x00000001,						// LOG: It will make a glc_log.txt with 'wb' option.
	LC_LOG_MIX               =  0x00000002,						// LOG: log to serial and file.
	LC_LOG_INFO              =  0x00000049,						// LOG: Information	'I'
	LC_LOG_WARNING           =  0x00000057,						// LOG: Warnning  'W'
	LC_LOG_ERROR             =  0x00000045,						// LOG: Error     'E'
	LC_LOG_GLC               =  0x00000047,						// LOG: General   'G'

	LC_TIME_ELAPSED          =  0x0000B013,						// TIME: DOUBLE, elapsed millisecond time per on frame. same to LcVar_TimeElapsed
	LC_TIME_STORED           =  0x0000B014,						// TIME: DINT, Stored Time. same to LcVar_TimeStored
	LC_TIME_FRAME            =  0x0000B015,						// TIME: double, Frames per one second. same to LcVar_TimeFrameRate
};

enum LC_STYPE													// Enum simple data type for data base and register
{
	LC_ST_DOUBLE             =  0x00000001,						// SIMPLE TYPE: double (8byte) for big number
	LC_ST_STRING             =  0x00000002,						// SIMPLE TYPE: string(null terminated)
	LC_ST_BOOL               =  0x00000003,						// SIMPLE TYPE: boolean (1byte)
	LC_ST_WORD               =  0x00000004,						// SIMPLE TYPE: short int (2byte)
	LC_ST_DWORD              =  0x00000005,						// SIMPLE TYPE: int (4byte). for small number
	LC_ST_QWORD              =  0x00000006,						// SIMPLE TYPE: double int (8byte)
	LC_ST_FLOAT              =  0x00000007,						// SIMPLE TYPE: float (4byte)
	LC_ST_VARIANT            =  0x00000008,						// SIMPLE TYPE: not defined byte data
};

#ifndef LC_SUCCEEDED											// succeeded/failed macro
  #define LC_SUCCEEDED(hr) ((HRESULT)(hr) >= 0)
  #define LC_FAILED(hr)    ((HRESULT)(hr) <  0)
#endif

#define lc_max(a,b)  (((a) > (b)) ? (a) : (b))					// Minimum and maximum macros
#define lc_min(a,b)  (((a) < (b)) ? (a) : (b))

#ifndef LC_INLINE												// inline
  #if defined(_MSC_VER)
    #define LC_INLINE __inline
  #else
    #define LC_INLINE inline __attribute__ ((always_inline))
  #endif
#endif


#ifndef DCL_INTERFACE											// Declare the Interface
  #define DCL_INTERFACE struct
#endif

#ifndef DCL_CLASS_DESTROYER
  #define DCL_CLASS_DESTROYER( CLASS_NAME ) \
  virtual ~CLASS_NAME(){}
#endif


#ifndef CONF													// const return function
  #define CONF(P) const P const
#endif

#ifndef CCSTR
  #define CCSTR	const char* const
#endif

#ifndef CONC
  #define CONC const char*
#endif

#endif	//_LcType_H_

