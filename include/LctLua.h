//	Copyright(C) GaLic Soft. All rights reserved.
//	GaLic Game Library Collection
//
// Interface for the Lua App
//
////////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER)
  #pragma once
#endif

#ifndef _LctLua_H_
#define _LctLua_H_


struct LscH								// Lua Handle
{
	UINT		id;
	LC_HANDLE	pi;						// Instance
	char		sn[LC_MAX_PATH];		// Name

	LscH();
};


// Lua Library inter face
LC_HANDLE Lua_Open						();										// Lua Open
INT       Lua_Load						(LC_HANDLE pL,LC_HANDLE n,INT l=0);		// File: name and size =0, Buffer: name is buffer, and size is not zero
INT       Lua_OpenLibs					(LC_HANDLE pL);							// Open the Lua Library
void      Lua_Close						(LC_HANDLE* pL);						// Lua Close
char*     Lua_GetString					(LC_HANDLE pL, INT idx);				// Get String

// Lua Api interface
INT       LscLua_Create   				(LC_HANDLE pL);							// Call Lua_Create
INT       LscLua_Init     				(LC_HANDLE pL);							// Call Lua_Init
INT       LscLua_Destroy  				(LC_HANDLE pL);							// Call Lua_Destroy
INT       LscLua_FrameMove				(LC_HANDLE pL);							// Call Lua_FrameMove
INT       LscLua_Render   				(LC_HANDLE pL);							// Call Lua_Render




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Interface for the LscSys class.

struct LscSys
{
	static INT	Create					(LC_HANDLE v);		// MainApp pointer
	static INT	Destroy					();
	static INT	OpenLib					(LC_HANDLE pL);

	static INT	Lsc_Platform			(LC_HANDLE pL);		// get the application platform
	static INT	Lsc_CreateWindow		(LC_HANDLE pL);		// Window Create
	static INT	Lsc_ScriptFile			(LC_HANDLE pL);		// Script File Load
	static INT	Lsc_Release				(LC_HANDLE pL);		// Window Release
	static INT	Lsc_Query				(LC_HANDLE pL);		// Command

	static INT	Lsc_ConsoleAlloc		(LC_HANDLE pL);
	static INT	Lsc_ConsoleSet			(LC_HANDLE pL);		// Use console
	static INT	Lsc_ConsoleSend			(LC_HANDLE pL);		// Send String to colsole

	static INT	Lsc_Sleep				(LC_HANDLE pL);		// Sleep
	static INT	Lsc_TimeGetTime			(LC_HANDLE pL);		// TimeGetTime
	static INT	Lsc_DateTime			(LC_HANDLE pL);		// System Date and Time

	static INT	Lsc_ShowCursor			(LC_HANDLE pL);		// Show Cursor
	static INT	Lsc_ShowState			(LC_HANDLE pL);		// State 보이기
	static INT	Lsc_ChangeMode			(LC_HANDLE pL);		// Full <--> Window
	static INT	Lsc_SetClearColor		(LC_HANDLE pL);		// 배경화면 클리어 색상설정
	static INT	Lsc_GetClearColor		(LC_HANDLE pL);		// 배령화면 클리어 색상 가져오기

	static INT	Lsc_WindowSize			(LC_HANDLE pL);		// Get Window Size
	static INT	Lsc_WindowTitle			(LC_HANDLE pL);		// Set Window Title
	static INT	Lsc_LogO				(LC_HANDLE pL);		// log out Option
	static INT	Lsc_LogI				(LC_HANDLE pL);		// log out Information
	static INT	Lsc_LogW				(LC_HANDLE pL);		// log out Warning
	static INT	Lsc_LogE				(LC_HANDLE pL);		// log out Error
	static INT	Lsc_LogOut				(INT,LC_HANDLE);	// log out
	static INT	Lsc_ModulePath			(LC_HANDLE pL);		// Get Module Path

	static INT	Lsc_DoFile				(LC_HANDLE pL);		// Do File
	static INT	Lsc_OpenFile			(LC_HANDLE pL);		// Open File
	static INT	Lsc_MessageBox			(LC_HANDLE pL);		// Window Box

	static INT	Lsc_RegOpen				(LC_HANDLE pL);		// Register Open
	static INT	Lsc_RegClose			(LC_HANDLE pL);		// Register Close
	static INT	Lsc_RegDelete			(LC_HANDLE pL);		// Register Clear
	static INT	Lsc_RegRead				(LC_HANDLE pL);		// Register Read
	static INT	Lsc_RegWrite			(LC_HANDLE pL);		// Register Write

	static int	SendToGameCenter		(LC_HANDLE pL);		// SNS: Send game score to game center
	static int	ShowLeaderBoard			(LC_HANDLE pL);		// SNS: Open the score board
};




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Interface for the LscAux class.

struct LscAux
{
	//Lsc API.
	static INT	Lsc_Mod					(LC_HANDLE pL);		// Modulate
	static INT	Lsc_Rand				(LC_HANDLE pL);		// Random

	static INT	Lsc_CastInt				(LC_HANDLE pL);		// Casting Integer
	static INT	Lsc_GetWords			(LC_HANDLE pL);		// Get Word from Strings
	static INT	Lsc_GetWordLen			(LC_HANDLE pL);		// Get Word Length from Strings
	static INT	Lsc_StrLen				(LC_HANDLE pL);		// Get String Length

	// string Module
	static INT	Lsc_StrCmp				(LC_HANDLE pL);		// String Compare
	static INT	Lsc_StrToInt			(LC_HANDLE pL);		// String To Int
	static INT	Lsc_StrToDouble			(LC_HANDLE pL);		// String To Double
	static INT	Lsc_ToHexa				(LC_HANDLE pL);		// To Hexa string
	static INT	Lsc_ToHexaByte			(LC_HANDLE pL);		// To Hexa byte string
};




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Interface for the LscInput class.

struct LscInput
{
	static INT	Create					(LC_HANDLE v);		// v needs Input pointer
	static INT	Destroy					();
	static INT	OpenLib					(LC_HANDLE pL);

	//Lsc API.
	static INT	Lsc_KeyboardAll			(LC_HANDLE pL);		// keyboard All Key
	static INT	Lsc_KeyboardOne			(LC_HANDLE pL);		// keyboard One Key
	static INT	Lsc_MousePos			(LC_HANDLE pL);		// Mouse Pos
	static INT	Lsc_MouseDelta			(LC_HANDLE pL);
	static INT	Lsc_MouseEvnt			(LC_HANDLE pL);		// Mouse Event
	static INT	Lsc_MouseCount			(LC_HANDLE pL);		// Mouse Count
	static INT	Lsc_MouseInRect			(LC_HANDLE pL);		// Mouse point in Rect
	static INT	Lsc_ImeOn				(LC_HANDLE pL);		// Ime on
	static INT	Lsc_ImeOff				(LC_HANDLE pL);		// Ime off
	static INT	Lsc_ImeString			(LC_HANDLE pL);		// get the string to ime
	static INT	Lsc_ImeState			(LC_HANDLE pL);		// get the ime state
	static INT	Lsc_ImeClear			(LC_HANDLE pL);		// clear the string buffer
	static INT	Lsc_ImeEvent			(LC_HANDLE pL);		// get the ime complete event
};




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Interface for the LscTex class.

#define MAX_TEX		8192

struct LscTex
{
	struct ILhLst
	{
		ILhLst();
		~ILhLst();

		LscH*	vLst[MAX_TEX];

		INT		Alloc(char* sFile, UINT b16 = 0, UINT dColorKey=0x00FFFFFF, UINT dFilter=0x00);
		INT		ReAlloc(INT nKey, char* sFile, UINT b16 = 0, UINT dColorKey=0x00FFFFFF, UINT dFilter=0x00);
		INT		Release(INT nKey);
		LscH*	Find(INT nKey);
		LscH*	Find(INT* nKey, char* sFile);
		INT		FindEmpty();
	};


	static INT	Create					(LC_HANDLE v);		// v needs PLC_SPRITE
	static INT	Destroy					();
	static INT	OpenLib					(LC_HANDLE pL);

	static INT	Lsc_Alloc				(LC_HANDLE pL);		// 이미지 file loading
	static INT	Lsc_ReAlloc				(LC_HANDLE pL);		// 이미지 file 다시 loading
	static INT	Lsc_Release				(LC_HANDLE pL);		// 이미지 file release
	static INT	Lsc_Width				(LC_HANDLE pL);		// 이미지 file 너비
	static INT	Lsc_Height				(LC_HANDLE pL);		// 이미지 file 높이
	static INT	Lsc_Pointer				(LC_HANDLE pL);		// Get texture Point
	static INT	Lsc_Draw				(LC_HANDLE pL);		// 이미지 그리기
	static INT	Lsc_DrawOne				(LC_HANDLE pL);		// 이미지 그리기
	static INT	Lsc_DrawEx				(LC_HANDLE pL);		// 이미지 그리기 Ex
	static INT	Lsc_SetTexture			(LC_HANDLE pL);		// Device->SetTexture
	static INT	Lsc_Blending			(LC_HANDLE pL);		// Sprite->SetBlending
	static INT	Lsc_ZBias				(LC_HANDLE pL);		// Sprite->SetRenderState(LC_RS_ZBIAS)
};




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Interface for the sprite and sprite collector class.

struct LscSpc
{
	struct ILhLst
	{
		ILhLst();
		~ILhLst();

		LscH*	vLst[MAX_TEX];

		INT		Alloc(INT textureId);					// texture id from lua
		INT		Release(INT nKey);
		LscH*	Find(INT nKey);
		INT		FindEmpty();
	};


	static INT	Create					(LC_HANDLE v);		// v needs PLC_SPRITE
	static INT	Destroy					();
	static INT	OpenLib					(LC_HANDLE pL);

	static INT	Lsc_Alloc				(LC_HANDLE pL);		// 이미지 file loading
	static INT	Lsc_Release				(LC_HANDLE pL);		// 이미지 file release
	static INT	Lsc_AddRect				(LC_HANDLE pL);		// gather rect
	static INT	Lsc_DrawFlush			(LC_HANDLE pL);		// draw the 2d buffer. and flush
	static INT	Lsc_Draw				(LC_HANDLE pL);		// draw the rect list
	static INT	Lsc_DrawLine			(LC_HANDLE pL);		// draw the lines
	static INT	Lsc_DrawRect			(LC_HANDLE pL);		// draw rect line
	static INT	Lsc_DrawEllipsoid		(LC_HANDLE pL);		// draw the ellipsoid
	static INT	Lsc_DrawPolygon			(LC_HANDLE pL);		// draw the polygon
	static INT	Lsc_Blending			(LC_HANDLE pL);		// Sprite->SetBlending
	static INT	Lsc_ZBias				(LC_HANDLE pL);		// Sprite->SetRenderState(LC_RS_ZBIAS)
	static INT	Lsc_Mono				(LC_HANDLE pL);		// Sprite->SetRenderState(LC_RS_DISPLAY_MONO)
};




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Interface for the LscFont cLscss.

#define MAX_FONT	8192

struct LscFont
{
	struct ILhLst
	{
		ILhLst();
		~ILhLst();

		LscH*	vLst[MAX_FONT];

		INT		Alloc(LC_HANDLE* pOut, char* sName,	INT	analyzer=1, INT lHeight=12, INT anti_a=LC_TRUE);
		INT		Release(INT nKey);
		LscH*	Find(INT nKey);
		INT		FindEmpty();
	};

	static INT	Create					(LC_HANDLE v);		// v needs PLC_SPRITE
	static INT	Destroy					();
	static INT	OpenLib					(LC_HANDLE pL);

	static INT	Lsc_Alloc				(LC_HANDLE pL);		// font loading
	static INT	Lsc_Release				(LC_HANDLE pL);		// font release
	static INT	Lsc_FontDraw			(LC_HANDLE pL);		// font Draw
	static INT	Lsc_FontSetup			(LC_HANDLE pL);		// font String Setup
	static INT	Lsc_FontString			(LC_HANDLE pL);		// font String
	static INT	Lsc_FontPos				(LC_HANDLE pL);		// font Position
	static INT	Lsc_FontColor			(LC_HANDLE pL);		// font Color
	static INT	Lsc_FontScale			(LC_HANDLE pL);		// font Scaling
	static INT	Lsc_FontAlign			(LC_HANDLE pL);		// font Alignment
	static INT	Lsc_FontCount			(LC_HANDLE pL);		// font Character Count
	static INT	Lsc_FontRect			(LC_HANDLE pL);		// font Character Rect
};




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Interface for the LscSnd class.

#define MAX_SMD		1024

struct LscSmd
{
	struct ILhLst
	{
		ILhLst();
		~ILhLst();

		LscH*	vLst[MAX_SMD];

		INT		Alloc(LC_HANDLE* pOut,char* sFile);		// create sound
		INT		Release(INT nKey);						// release sound
		LscH*	Find(INT nKey);							// search...
		INT		FindEmpty();
	};


	static INT	Create					(LC_HANDLE v);
	static INT	Destroy					();
	static INT	OpenLib					(LC_HANDLE pL);

	static INT	Lsc_Alloc				(LC_HANDLE pL);		// sound loading
	static INT	Lsc_Release				(LC_HANDLE pL);		// sound release
	static INT	Lsc_SndPlay				(LC_HANDLE pL);		// sound play
	static INT	Lsc_SndStop				(LC_HANDLE pL);		// sound Stop
	static INT	Lsc_SndPause			(LC_HANDLE pL);		// sound Pause
	static INT	Lsc_SndReset			(LC_HANDLE pL);		// sound Reset
	static INT	Lsc_SndVolume			(LC_HANDLE pL);		// sound Volume
	static INT	Lsc_SetRepeat			(LC_HANDLE pL);		// sound Repeat
	static INT	Lsc_GetState			(LC_HANDLE pL);		// sound State
};




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Interface for the LscShw class.

#define MAX_SHW		256

struct LscShw
{
	struct ILhLst
	{
		ILhLst();
		~ILhLst();

		LscH*	vLst[MAX_SHW];

		INT		Alloc(LC_HANDLE* pOut,char* sFile);		// create show
		INT		Release(INT nKey);						// release show
		LscH*	Find(INT nKey);							// search...
		INT		FindEmpty();
	};


	static INT	Create(LC_HANDLE v);
	static INT	Destroy();
	static INT	OpenLib(LC_HANDLE pL);

	static INT	Lsc_Alloc				(LC_HANDLE pL);		// show loading
	static INT	Lsc_Release				(LC_HANDLE pL);		// show release
	static INT	Lsc_Play				(LC_HANDLE pL);		// show play
	static INT	Lsc_Stop				(LC_HANDLE pL);		// show Stop
	static INT	Lsc_Pause				(LC_HANDLE pL);		// show Pause
	static INT	Lsc_Reset				(LC_HANDLE pL);		// show Reset
	static INT	Lsc_Repeat				(LC_HANDLE pL);		// show Set/Get Repeat
	static INT	Lsc_State				(LC_HANDLE pL);		// show Get State
	static INT	Lsc_Width				(LC_HANDLE pL);		// show Width
	static INT	Lsc_Height				(LC_HANDLE pL);		// show Height
	static INT	Lsc_FrameMove			(LC_HANDLE pL);		// show FrameMove
	static INT	Lsc_Draw				(LC_HANDLE pL);		// show Draw
};




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Interface for the LscFile class.

#define MAX_FILE	1024

struct LscFile
{
	struct ILhLst
	{
		ILhLst();
		~ILhLst();

		LscH*	vLst[MAX_FILE];

		INT		Alloc(char* sFile, char* sMode);
		INT		Release(INT nKey);
		LscH*	Find(INT nKey);
		LscH*	Find(INT* nKey, char* sFile);
		INT		FindEmpty();
	};

	static INT	Create					(LC_HANDLE v);
	static INT	Destroy					();
	static INT	OpenLib					(LC_HANDLE pL);

	static INT	Lsc_FileOpen			(LC_HANDLE pL);		// file Open
	static INT	Lsc_FileClose			(LC_HANDLE pL);		// file Close
	static INT	Lsc_FileRead			(LC_HANDLE pL);		// file Read
	static INT	Lsc_FileReadLine		(LC_HANDLE pL);		// file Read Line
	static INT	Lsc_FileWrite			(LC_HANDLE pL);		// file Write
};




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Interface for the LsxTda class.

#define MAX_TSA		520
#define MAX_TSA_ORG	64

struct LsxTda
{
	struct ILhLst
	{
		ILhLst();
		~ILhLst();

		LscH*	vLst[MAX_TSA];								// Tda Instance
		LscH*	vLstO[MAX_TSA_ORG];							// Original List

		INT		Alloc(char* sFile);
		INT		Release(INT nKey);
		LscH*	Find(INT nKey);
		LscH*	Find(INT* nKey, char* sFile);
		INT		FindEmpty();

		LscH*	FindOrg(char* sFile);
	};

	static INT	Create					(LC_HANDLE v);		// v needs PLC_SPRITE
	static INT	Destroy					();
	static INT	OpenLib					(LC_HANDLE pL);

	static INT	Lsc_Alloc				(LC_HANDLE pL);		// Tda file loading
	static INT	Lsc_Release				(LC_HANDLE pL);		// Tda file release
	static INT	Lsc_DrawOneFrame		(LC_HANDLE pL);		// Tda Select
	static INT	Lsc_SetAnimation		(LC_HANDLE pL);		// Animation Set
	static INT	Lsc_FrameMove			(LC_HANDLE pL);		// FrameMove
	static INT	Lsc_Render				(LC_HANDLE pL);		// Render
};



//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Interface for the LstDB class.

#define MAX_DB	512

struct LstDB
{
	struct ILhLst
	{
		ILhLst();
		~ILhLst();

		LscH*	vLst[MAX_DB];

		INT		Alloc(char* sFile, INT dlm);
		INT		Release(INT nKey);
		LscH*	Find(INT nKey);
		LscH*	Find(INT* nKey, char* sFile);
		INT		FindEmpty();
	};

	static INT	Create					(LC_HANDLE v);
	static INT	Destroy					();
	static INT	OpenLib					(LC_HANDLE pL);

	static INT	Lsc_Alloc				(LC_HANDLE pL);		// DB file loading
	static INT	Lsc_Release				(LC_HANDLE pL);		// DB file release
	static INT	Lsc_Select				(LC_HANDLE pL);		// DB Select
	static INT	Lsc_Insert				(LC_HANDLE pL);		// DB Insert
	static INT	Lsc_Update				(LC_HANDLE pL);		// DB Update
	static INT	Lsc_Delete				(LC_HANDLE pL);		// DB Delete
	static INT	Lsc_FieldCount			(LC_HANDLE pL);		// Query: Field Count
	static INT	Lsc_RecordCount			(LC_HANDLE pL);		// Query: Record Count
	static INT	Lsc_Save				(LC_HANDLE pL);
};




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Interface for the LscHw class.

struct LscHw
{
	static INT	Create					(LC_HANDLE v);
	static INT	Destroy					();
	static INT	OpenLib					(LC_HANDLE pL);

	static INT	Lsc_HapticPlay			(LC_HANDLE pL);		// Vibration play
	static INT	Lsc_HapticPattern		(LC_HANDLE pL);		// Vibration play pattern
	static INT	Lsc_HapticStop			(LC_HANDLE pL);		// Vibration stop

	static INT	Lsc_Sensor				(LC_HANDLE pL);		// Read the Sensor

	static INT	Lsc_MasterVolumeUp		(LC_HANDLE pL);		// Setup the master volume up
	static INT	Lsc_MasterVolumeDown	(LC_HANDLE pL);		// Setup the master volume down
	static INT	Lsc_MasterVolumeMute	(LC_HANDLE pL);		// Setup the master volume mute
};




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Interface for the LscNet class.

#define MAX_NET		64

struct LscNet
{
	struct ILhLst										// ContFont
	{
		ILhLst();
		~ILhLst();

		LscH*	vLst[MAX_NET];

		INT		Alloc(LC_HANDLE inf);					// create network
		INT		Release(INT nKey);						// rlease network
		LscH*	Find(INT nKey);							// find
		INT		FindEmpty();
	};

	static INT	Create					(LC_HANDLE v);
	static INT	Destroy					();
	static INT	OpenLib					(LC_HANDLE pL);

	static INT	Lsc_Alloc				(LC_HANDLE pL);		// create network
	static INT	Lsc_Release				(LC_HANDLE pL);		// release network
	static INT	Lsc_BtOpen				(LC_HANDLE pL);		// bluetooth open
	static INT	Lsc_BtClose				(LC_HANDLE pL);		// bluetooth close
	static INT	Lsc_BtPairing			(LC_HANDLE pL);		// bluetooth pairing
	static INT	Lsc_Start				(LC_HANDLE pL);		// server start
	static INT	Lsc_Stop				(LC_HANDLE pL);		// server stop
	static INT	Lsc_Connect				(LC_HANDLE pL);		// connect to server
	static INT	Lsc_Disconnect			(LC_HANDLE pL);		// Disconnect
	static INT	Lsc_Update				(LC_HANDLE pL);		// Network update
	static INT	Lsc_Send				(LC_HANDLE pL);		// data send
	static INT	Lsc_Recv				(LC_HANDLE pL);		// data recv
	static INT	Lsc_State				(LC_HANDLE pL);		// state
	static INT	Lsc_Message				(LC_HANDLE pL);		// I/O message
	static INT	Lsc_SockDesc			(LC_HANDLE pL);		// Socket decription
	static INT	Lsc_HostDesc			(LC_HANDLE pL);		// Host socket decription on sever system
};


#endif

