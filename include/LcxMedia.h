//	Copyright(C) GaLic Soft. All rights reserved.
//	GaLic Game Library Collection
//
// Interface for the Media class.
//
////////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER)
  #pragma once
#endif

#ifndef _LcxMedia_H_
#define _LcxMedia_H_

#include <LcType.h>
#include <LcBase.h>


//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Interface for the ILCX_Input class.

DCL_INTERFACE ILCX_Input : public ILC_Object
{
	DCL_CLASS_DESTROYER(	ILCX_Input	);

	virtual INT			Update()=0;												// Input Update
	virtual void		Reset()=0;												// reset(clear) the input data
	virtual void		SetActive(INT bActive=LC_TRUE)=0;						// return input values only active state.
	virtual INT			GetActive()=0;


	virtual const BYTE* const KeyMap()const=0;									// Key+Button Map
	virtual const BYTE* const MtsMap()const=0;									// Multi-touch Screen Map

	virtual LC_STATE	KeyDown(INT nKey)=0;
	virtual LC_STATE	KeyUp(INT nKey)=0;
	virtual LC_STATE	KeyPress(INT nKey)=0;
	virtual LC_STATE	KeyState(INT nKey)=0;

	virtual LC_STATE	MtsDown(INT nMultiTouch=0)=0;							// Multi-touch Screen down
	virtual LC_STATE	MtsUp(INT nMultiTouch=0)=0;								// Multi-touch Screen up
	virtual LC_STATE	MtsPress(INT nMultiTouch=0)=0;							// Multi-touch Screen press
	virtual LC_STATE	MtsState(INT nMultiTouch=0)=0;							// Multi-touch Screen state

	virtual const FLOAT* const MtsPosition(int nMultiTouch=0)const=0;			// Multi-touch Screen Position Need FLOAT x 3
	virtual const FLOAT* const MtsDelta(int nMultiTouch=0)const=0;				// Gradient of Multi-touch Screen Need FLOAT x 3
	virtual LC_STATE	IsMtsMove()=0;

	virtual void		SetCurKey(BYTE* pKey, INT iLen = LC_MAX_KEY)=0;
	virtual void		SetCurTsb(BYTE* pTsb, INT iLen = LC_MAX_TSB)=0;
	virtual void		SetTsbPos(FLOAT* vcPos, int nMultiTouch=0)=0;

	virtual LC_STATE	IsInRect (FLOAT x,FLOAT y,FLOAT w,FLOAT h,INT touchIdx=0)=0;	// return  TRUE or FALSE.
	virtual LC_STATE	IsInRect2(FLOAT x,FLOAT y,FLOAT w,FLOAT h)=0;					// test collison rect x,y,w,h and 0, 1 touch region
};

typedef ILCX_Input*	PLCX_INPUT;

// For Keypad, Multi-touch Screen controller
// Create Input device. So, you have not to call LcStv_InputOpen..()
// Create Openoal/SL Sound
//  sCmd        - absolutely, you must set the value to Null.
// ILCX_Input use the saved window handle by LcVar_WriteP(LC_VAR_WIN_HANDLE, hWnd);

INT LcxEnt_CreateInput(char* sCmd, PLCX_INPUT* pOut, PLC_ARGS = NULL);




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Interface for the ILCX_Sound class.

enum ELCX_AV																	// audio, video enum
{
	LCX_AV_PCM				= LC_SND_PCM	,									// Format: pcm

	LCX_AV_STOP				= LC_LOOP_STOP	,									// Stop
	LCX_AV_RESET			= LC_LOOP_RESET	,									// Reset
	LCX_AV_PAUSE			= LC_LOOP_PAUSE	,									// Pause
	LCX_AV_PLAY				= LC_LOOP_PLAY	,									// Play
	LCX_AV_INFINITE			= LC_INFINITE	,									// loop infinite
};


struct TXDSC_SOUND																// Sound Information
{
	char*		src_n;															// Resource Name for Search
	UINT		snd_s;															// Sound source storage type: LC_SRC_T_{FILE | MEM | BUF, RSC}
	UINT		snd_k;															// Sound source kind: LC_OBJ_{WAV|OGG}
	UINT		snd_f;															// Audio Format. It must be LCX_AV_PCM. This sdk only supports PCM
	UINT		snd_b;															// Audio Bit Rate: => 8 or 16. This sdk only supports 16bit sound
	UINT		snd_c;															// Channels: Mono =>1, stereo =>2
	UINT		snd_z;															// Sampling Rate: ex) 8000 kHz => 8, 22050 kHz => 22050
	UINT		snd_l;															// Buffer Size
	INT			snd_r;															// Reference count
	BYTE*		snd_a;															// Audio Buffer pointer
};


DCL_INTERFACE ILCX_Sound : public ILC_Object
{
	DCL_CLASS_DESTROYER(	ILCX_Sound	);

	virtual INT		Release(INT bDecreaseRefCount=LC_TRUE)=0;
	virtual INT		Query(char* sCmd, LC_HANDLE pData)=0;
	virtual UINT	RscType	() =0;												// Sound source kind
	virtual INT		Desc	(LC_HANDLE) =0;										// It needs TXDSC_SOUND* address
	virtual CONC	Name    () =0;

	virtual UINT	Format		() =0;											// Audio Format

	virtual INT		Play		() =0;
	virtual INT		Stop		() =0;
	virtual INT		Pause		() =0;
	virtual INT		Reset		() =0;
	virtual void	SetVolume	( FLOAT Vol)=0;
	virtual FLOAT	GetVolume	() =0;
	virtual INT		SetRepeat	(INT repeat=LCX_AV_INFINITE)=0;
	virtual INT		GetRepeat	() =0;
	virtual INT		Status		() =0;
};


typedef ILCX_Sound*	PLCX_SOUND;

// for openal device or opensl sound engine
INT LcxSmd_SoundDeviceOpen();													// Open  the Openoal/SL sound device/engine.
INT	LcxSmd_SoundDeviceClose();													// close the Openoal/SL sound device/engine.


// Create Openoal/SL Sound
//  sCmd        - absolutely, you must set the value to Null.
//  TLC_ARGS
//    arg0:UINT - Resource Type: LC_SRC_T_{FILE | MEM | BUF, RSC}
//
//                             File       Buffer              Memory
//    arg1:char*,LC_HANDLE  file name  identity name       identity name
//    arg2:INT                         TXDSC_SOUND pointer Memory address
//    arg3:INT                                             Memory size

INT LcxSmd_CreateSound(char* sCmd, PLCX_SOUND* pOut, PLC_ARGS arg);




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Interface for the ILCX_Show class.

struct TLCX_SHOW																// Show Information
{
	char*		src_n;															// Resource Name for Search
	INT			shw_w;															// video width
	INT			shw_h;															// video height
	INT			shw_d;															// video depth. 3: rgb, 4: rgba.
	UINT		shw_l;															// Buffer Size
	BYTE*		shw_a;															// Video Buffer pointer
};


DCL_INTERFACE ILCX_Show : public ILC_Object
{
	DCL_CLASS_DESTROYER(	ILCX_Show	);

	virtual INT			Release(INT bDecreaseRefCount=LC_TRUE)=0;
	virtual INT			Query(char* sCmd, LC_HANDLE pData)=0;
	//virtual INT		Desc(LC_HANDLE) =0;										// It needs TLCX_SHOW* address
	//virtual CONC		Name() =0;

	virtual INT			FrameMove	() =0;										// Update the video streamming texture
	virtual INT			Play		() =0;
	virtual INT			Stop		() =0;
	virtual INT			Pause		() =0;
	virtual INT			Reset		() =0;
	virtual INT			SetRepeat	(INT repeat=LCX_AV_INFINITE)=0;
	virtual INT			GetRepeat	() =0;
	virtual INT			Status		() =0;
	virtual PLC_TEXTURE	Texture		() =0;
};


typedef ILCX_Show*	PLCX_SHOW;

// for Direct Show or OpenMAX engine
INT LcxSmd_ShowDeviceOpen();													// Open  the Direct Show/OpenMax engine.
INT	LcxSmd_ShowDeviceClose();													// close the Direct Show/OpenMax engine.

INT LcxSmd_CreateShow(char* sCmd, PLCX_SHOW* pOut, PLC_ARGS arg);

#endif

