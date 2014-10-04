//	Copyright(C) GaLic Soft. All rights reserved.
//
// Stdev is Standard (System) Device.
// the input(keypad, Multi-touch Screen), Sensor, haptic motor,
// sound and recording device are called the standard device.
//
////////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER)
  #pragma once
#endif

#ifndef _LcStdev_H_
#define _LcStdev_H_

#include <LcType.h>
#include <LcBase.h>


//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// GLC Input

enum ELC_INPUT
{
	LCIK_READ_WAIT		= 1,
	LCIK_READ_COMPLETE	= 0,

	// Type
	LCIK_NONE			= 0,

	// State
	LCIK_KEYNONE		= 0,
	LCIK_KEYDOWN		= 1,
	LCIK_KEYUP			= 2,
	LCIK_KEYPRESS		= 3,

	// Mouse for pc
	LCIK_LBUTTON		= 0,
	LCIK_RBUTTON		= 1,
	LCIK_MBUTTON		= 2,
};

enum EDInput
{
	DI_K_ESCAPE          = 0x01,
	DI_K_1               = 0x02,
	DI_K_2               = 0x03,
	DI_K_3               = 0x04,
	DI_K_4               = 0x05,
	DI_K_5               = 0x06,
	DI_K_6               = 0x07,
	DI_K_7               = 0x08,
	DI_K_8               = 0x09,
	DI_K_9               = 0x0A,
	DI_K_0               = 0x0B,
	DI_K_MINUS           = 0x0C,   /* - on main keyboard */
	DI_K_EQUALS          = 0x0D,
	DI_K_BACK            = 0x0E,   /* backspace */
	DI_K_TAB             = 0x0F,
	DI_K_Q               = 0x10,
	DI_K_W               = 0x11,
	DI_K_E               = 0x12,
	DI_K_R               = 0x13,
	DI_K_T               = 0x14,
	DI_K_Y               = 0x15,
	DI_K_U               = 0x16,
	DI_K_I               = 0x17,
	DI_K_O               = 0x18,
	DI_K_P               = 0x19,
	DI_K_LBRACKET        = 0x1A,
	DI_K_RBRACKET        = 0x1B,
	DI_K_RETURN          = 0x1C,    /* Enter on main keyboard */
	DI_K_LCONTROL        = 0x1D,
	DI_K_A               = 0x1E,
	DI_K_S               = 0x1F,
	DI_K_D               = 0x20,
	DI_K_F               = 0x21,
	DI_K_G               = 0x22,
	DI_K_H               = 0x23,
	DI_K_J               = 0x24,
	DI_K_K               = 0x25,
	DI_K_L               = 0x26,
	DI_K_SEMICOLON       = 0x27,
	DI_K_APOSTROPHE      = 0x28,
	DI_K_GRAVE           = 0x29,    /* accent grave */
	DI_K_LSHIFT          = 0x2A,
	DI_K_BACKSLASH       = 0x2B,
	DI_K_Z               = 0x2C,
	DI_K_X               = 0x2D,
	DI_K_C               = 0x2E,
	DI_K_V               = 0x2F,
	DI_K_B               = 0x30,
	DI_K_N               = 0x31,
	DI_K_M               = 0x32,
	DI_K_COMMA           = 0x33,
	DI_K_PERIOD          = 0x34,    /* . on main keyboard */
	DI_K_SLASH           = 0x35,    /* / on main keyboard */
	DI_K_RSHIFT          = 0x36,
	DI_K_MULTIPLY        = 0x37,    /* * on numeric keypad */
	DI_K_LMENU           = 0x38,    /* left Alt */
	DI_K_SPACE           = 0x39,
	DI_K_CAPITAL         = 0x3A,
	DI_K_F1              = 0x3B,
	DI_K_F2              = 0x3C,
	DI_K_F3              = 0x3D,
	DI_K_F4              = 0x3E,
	DI_K_F5              = 0x3F,
	DI_K_F6              = 0x40,
	DI_K_F7              = 0x41,
	DI_K_F8              = 0x42,
	DI_K_F9              = 0x43,
	DI_K_F10             = 0x44,
	DI_K_NUMLOCK         = 0x45,
	DI_K_SCROLL          = 0x46,    /* Scroll Lock */
	DI_K_NUMPAD7         = 0x47,
	DI_K_NUMPAD8         = 0x48,
	DI_K_NUMPAD9         = 0x49,
	DI_K_SUBTRACT        = 0x4A,    /* - on numeric keypad */
	DI_K_NUMPAD4         = 0x4B,
	DI_K_NUMPAD5         = 0x4C,
	DI_K_NUMPAD6         = 0x4D,
	DI_K_ADD             = 0x4E,    /* + on numeric keypad */
	DI_K_NUMPAD1         = 0x4F,
	DI_K_NUMPAD2         = 0x50,
	DI_K_NUMPAD3         = 0x51,
	DI_K_NUMPAD0         = 0x52,
	DI_K_DECIMAL         = 0x53,    /* . on numeric keypad */
	DI_K_OEM_102         = 0x56,    /* <> or \| on RT 102-key keyboard (Non-U.S.) */
	DI_K_F11             = 0x57,
	DI_K_F12             = 0x58,
	DI_K_F13             = 0x64,    /*                     (NEC PC98) */
	DI_K_F14             = 0x65,    /*                     (NEC PC98) */
	DI_K_F15             = 0x66,    /*                     (NEC PC98) */
	DI_K_KANA            = 0x70,    /* (Japanese keyboard)            */
	DI_K_ABNT_C1         = 0x73,    /* /? on Brazilian keyboard */
	DI_K_CONVERT         = 0x79,    /* (Japanese keyboard)            */
	DI_K_NOCONVERT       = 0x7B,    /* (Japanese keyboard)            */
	DI_K_YEN             = 0x7D,    /* (Japanese keyboard)            */
	DI_K_ABNT_C2         = 0x7E,    /* Numpad . on Brazilian keyboard */
	DI_K_NUMPADEQUALS    = 0x8D,    /* = on numeric keypad (NEC PC98) */
	DI_K_PREVTRACK       = 0x90,    /* Previous Track (DI_K_CIRCUMFLEX on Japanese keyboard) */
	DI_K_AT              = 0x91,    /*                     (NEC PC98) */
	DI_K_COLON           = 0x92,    /*                     (NEC PC98) */
	DI_K_UNDERLINE       = 0x93,    /*                     (NEC PC98) */
	DI_K_KANJI           = 0x94,    /* (Japanese keyboard)            */
	DI_K_STOP            = 0x95,    /*                     (NEC PC98) */
	DI_K_AX              = 0x96,    /*                     (Japan AX) */
	DI_K_UNLABELED       = 0x97,    /*                        (J3100) */
	DI_K_NEXTTRACK       = 0x99,    /* Next Track */
	DI_K_NUMPADENTER     = 0x9C,    /* Enter on numeric keypad */
	DI_K_RCONTROL        = 0x9D,
	DI_K_MUTE            = 0xA0,    /* Mute */
	DI_K_CALCULATOR      = 0xA1,    /* Calculator */
	DI_K_PLAYPAUSE       = 0xA2,    /* Play / Pause */
	DI_K_MEDIASTOP       = 0xA4,    /* Media Stop */
	DI_K_VOLUMEDOWN      = 0xAE,    /* Volume - */
	DI_K_VOLUMEUP        = 0xB0,    /* Volume + */
	DI_K_WEBHOME         = 0xB2,    /* Web home */
	DI_K_NUMPADCOMMA     = 0xB3,    /* , on numeric keypad (NEC PC98) */
	DI_K_DIVIDE          = 0xB5,    /* / on numeric keypad */
	DI_K_SYSRQ           = 0xB7,
	DI_K_RMENU           = 0xB8,    /* right Alt */
	DI_K_PAUSE           = 0xC5,    /* Pause */
	DI_K_HOME            = 0xC7,    /* Home on arrow keypad */
	DI_K_UP              = 0xC8,    /* UpArrow on arrow keypad */
	DI_K_PRIOR           = 0xC9,    /* PgUp on arrow keypad */
	DI_K_LEFT            = 0xCB,    /* LeftArrow on arrow keypad */
	DI_K_RIGHT           = 0xCD,    /* RightArrow on arrow keypad */
	DI_K_END             = 0xCF,    /* End on arrow keypad */
	DI_K_DOWN            = 0xD0,    /* DownArrow on arrow keypad */
	DI_K_NEXT            = 0xD1,    /* PgDn on arrow keypad */
	DI_K_INSERT          = 0xD2,    /* Insert on arrow keypad */
	DI_K_DELETE          = 0xD3,    /* Delete on arrow keypad */
	DI_K_LWIN            = 0xDB,    /* Left Windows key */
	DI_K_RWIN            = 0xDC,    /* Right Windows key */
	DI_K_APPS            = 0xDD,    /* AppMenu key */
	DI_K_POWER           = 0xDE,    /* System Power */
	DI_K_SLEEP           = 0xDF,    /* System Sleep */
	DI_K_WAKE            = 0xE3,    /* System Wake */
	DI_K_WEBSEARCH       = 0xE5,    /* Web Search */
	DI_K_WEBFAVORITES    = 0xE6,    /* Web Favorites */
	DI_K_WEBREFRESH      = 0xE7,    /* Web Refresh */
	DI_K_WEBSTOP         = 0xE8,    /* Web Stop */
	DI_K_WEBFORWARD      = 0xE9,    /* Web Forward */
	DI_K_WEBBACK         = 0xEA,    /* Web Back */
	DI_K_MYCOMPUTER      = 0xEB,    /* My Computer */
	DI_K_MAIL            = 0xEC,    /* Mail */
	DI_K_MEDIASELECT     = 0xED,    /* Media Select */
	
	DI_K_BACKSPACE       = DI_K_BACK    ,    /* backspace */
	DI_K_NUMPADSTAR      = DI_K_MULTIPLY,    /* * on numeric keypad */
	DI_K_LALT            = DI_K_LMENU   ,    /* left Alt */
	DI_K_CAPSLOCK        = DI_K_CAPITAL ,    /* CapsLock */
	DI_K_NUMPADMINUS     = DI_K_SUBTRACT,    /* - on numeric keypad */
	DI_K_NUMPADPLUS      = DI_K_ADD     ,    /* + on numeric keypad */
	DI_K_NUMPADPERIOD    = DI_K_DECIMAL ,    /* . on numeric keypad */
	DI_K_NUMPADSLASH     = DI_K_DIVIDE  ,    /* / on numeric keypad */
	DI_K_RALT            = DI_K_RMENU   ,    /* right Alt */
	DI_K_UPARROW         = DI_K_UP      ,    /* UpArrow on arrow keypad */
	DI_K_PGUP            = DI_K_PRIOR   ,    /* PgUp on arrow keypad */
	DI_K_LEFTARROW       = DI_K_LEFT    ,    /* LeftArrow on arrow keypad */
	DI_K_RIGHTARROW      = DI_K_RIGHT   ,    /* RightArrow on arrow keypad */
	DI_K_DOWNARROW       = DI_K_DOWN    ,    /* DownArrow on arrow keypad */
	DI_K_PGDN            = DI_K_NEXT    ,    /* PgDn on arrow keypad */
};


#if defined(USE_DIRECT_INPUT)

	#define LCIK_ESCAPE			DI_K_ESCAPE
	#define LCIK_1				DI_K_1
	#define LCIK_2				DI_K_2
	#define LCIK_3				DI_K_3
	#define LCIK_4				DI_K_4
	#define LCIK_5				DI_K_5
	#define LCIK_6				DI_K_6
	#define LCIK_7				DI_K_7
	#define LCIK_8				DI_K_8
	#define LCIK_9				DI_K_9
	#define LCIK_0				DI_K_0
	#define LCIK_MINUS			DI_K_MINUS
	#define LCIK_EQUALS			DI_K_EQUALS
	#define LCIK_BACK			DI_K_BACK
	#define LCIK_TAB			DI_K_TAB
	#define LCIK_Q				DI_K_Q
	#define LCIK_W				DI_K_W
	#define LCIK_E				DI_K_E
	#define LCIK_R				DI_K_R
	#define LCIK_T				DI_K_T
	#define LCIK_Y				DI_K_Y
	#define LCIK_U				DI_K_U
	#define LCIK_I				DI_K_I
	#define LCIK_O				DI_K_O
	#define LCIK_P				DI_K_P
	#define LCIK_LBRACKET		DI_K_LBRACKET
	#define LCIK_RBRACKET		DI_K_RBRACKET
	#define LCIK_RETURN			DI_K_RETURN
	#define LCIK_LCONTROL		DI_K_LCONTROL
	#define LCIK_A				DI_K_A
	#define LCIK_S				DI_K_S
	#define LCIK_D				DI_K_D
	#define LCIK_F				DI_K_F
	#define LCIK_G				DI_K_G
	#define LCIK_H				DI_K_H
	#define LCIK_J				DI_K_J
	#define LCIK_K				DI_K_K
	#define LCIK_L				DI_K_L
	#define LCIK_SEMICOLON		DI_K_SEMICOLON
	#define LCIK_APOSTROPHE		DI_K_APOSTROPHE
	#define LCIK_GRAVE			DI_K_GRAVE
	#define LCIK_LSHIFT			DI_K_LSHIFT
	#define LCIK_BACKSLASH		DI_K_BACKSLASH
	#define LCIK_Z				DI_K_Z
	#define LCIK_X				DI_K_X
	#define LCIK_C				DI_K_C
	#define LCIK_V				DI_K_V
	#define LCIK_B				DI_K_B
	#define LCIK_N				DI_K_N
	#define LCIK_M				DI_K_M
	#define LCIK_COMMA			DI_K_COMMA
	#define LCIK_PERIOD			DI_K_PERIOD
	#define LCIK_SLASH			DI_K_SLASH
	#define LCIK_RSHIFT			DI_K_RSHIFT
	#define LCIK_MULTIPLY		DI_K_MULTIPLY
	#define LCIK_LMENU			DI_K_LMENU
	#define LCIK_SPACE			DI_K_SPACE
	#define LCIK_CAPITAL		DI_K_CAPITAL
	#define LCIK_F1				DI_K_F1
	#define LCIK_F2				DI_K_F2
	#define LCIK_F3				DI_K_F3
	#define LCIK_F4				DI_K_F4
	#define LCIK_F5				DI_K_F5
	#define LCIK_F6				DI_K_F6
	#define LCIK_F7				DI_K_F7
	#define LCIK_F8				DI_K_F8
	#define LCIK_F9				DI_K_F9
	#define LCIK_F10			DI_K_F10
	#define LCIK_NUMLOCK		DI_K_NUMLOCK
	#define LCIK_SCROLL			DI_K_SCROLL
	#define LCIK_NUMPAD7		DI_K_NUMPAD7
	#define LCIK_NUMPAD8		DI_K_NUMPAD8
	#define LCIK_NUMPAD9		DI_K_NUMPAD9
	#define LCIK_SUBTRACT		DI_K_SUBTRACT
	#define LCIK_NUMPAD4		DI_K_NUMPAD4
	#define LCIK_NUMPAD5		DI_K_NUMPAD5
	#define LCIK_NUMPAD6		DI_K_NUMPAD6
	#define LCIK_ADD			DI_K_ADD
	#define LCIK_NUMPAD1		DI_K_NUMPAD1
	#define LCIK_NUMPAD2		DI_K_NUMPAD2
	#define LCIK_NUMPAD3		DI_K_NUMPAD3
	#define LCIK_NUMPAD0		DI_K_NUMPAD0
	#define LCIK_DECIMAL		DI_K_DECIMAL
	#define LCIK_OEM_102		DI_K_OEM_102
	#define LCIK_F11			DI_K_F11
	#define LCIK_F12			DI_K_F12
	#define LCIK_F13			DI_K_F13
	#define LCIK_F14			DI_K_F14
	#define LCIK_F15			DI_K_F15
	#define LCIK_KANA			DI_K_KANA
	#define LCIK_ABNT_C1		DI_K_ABNT_C1
	#define LCIK_CONVERT		DI_K_CONVERT
	#define LCIK_NOCONVERT		DI_K_NOCONVERT
	#define LCIK_YEN			DI_K_YEN
	#define LCIK_ABNT_C2		DI_K_ABNT_C2
	#define LCIK_NUMPADEQUALS	DI_K_NUMPADEQUALS
	#define LCIK_PREVTRACK		DI_K_PREVTRACK
	#define LCIK_AT				DI_K_AT
	#define LCIK_COLON			DI_K_COLON
	#define LCIK_UNDERLINE		DI_K_UNDERLINE
	#define LCIK_KANJI			DI_K_KANJI
	#define LCIK_STOP			DI_K_STOP
	#define LCIK_AX				DI_K_AX
	#define LCIK_UNLABELED		DI_K_UNLABELED
	#define LCIK_NEXTTRACK		DI_K_NEXTTRACK
	#define LCIK_NUMPADENTER	DI_K_NUMPADENTER
	#define LCIK_RCONTROL		DI_K_RCONTROL
	#define LCIK_MUTE			DI_K_MUTE
	#define LCIK_CALCULATOR		DI_K_CALCULATOR
	#define LCIK_PLAYPAUSE		DI_K_PLAYPAUSE
	#define LCIK_MEDIASTOP		DI_K_MEDIASTOP
	#define LCIK_VOLUMEDOWN		DI_K_VOLUMEDOWN
	#define LCIK_VOLUMEUP		DI_K_VOLUMEUP
	#define LCIK_WEBHOME		DI_K_WEBHOME
	#define LCIK_NUMPADCOMMA	DI_K_NUMPADCOMMA
	#define LCIK_DIVIDE			DI_K_DIVIDE
	#define LCIK_SYSRQ			DI_K_SYSRQ
	#define LCIK_RMENU			DI_K_RMENU
	#define LCIK_PAUSE			DI_K_PAUSE
	#define LCIK_HOME			DI_K_HOME
	#define LCIK_UP				DI_K_UP
	#define LCIK_PRIOR			DI_K_PRIOR
	#define LCIK_LEFT			DI_K_LEFT
	#define LCIK_RIGHT			DI_K_RIGHT
	#define LCIK_END			DI_K_END
	#define LCIK_DOWN			DI_K_DOWN
	#define LCIK_NEXT			DI_K_NEXT
	#define LCIK_INSERT			DI_K_INSERT
	#define LCIK_DELETE			DI_K_DELETE
	#define LCIK_LWIN			DI_K_LWIN
	#define LCIK_RWIN			DI_K_RWIN
	#define LCIK_APPS			DI_K_APPS
	#define LCIK_POWER			DI_K_POWER
	#define LCIK_SLEEP			DI_K_SLEEP
	#define LCIK_WAKE			DI_K_WAKE
	#define LCIK_WEBSEARCH		DI_K_WEBSEARCH
	#define LCIK_WEBFAVORITES	DI_K_WEBFAVORITES
	#define LCIK_WEBREFRESH		DI_K_WEBREFRESH
	#define LCIK_WEBSTOP		DI_K_WEBSTOP
	#define LCIK_WEBFORWARD		DI_K_WEBFORWARD
	#define LCIK_WEBBACK		DI_K_WEBBACK
	#define LCIK_MYCOMPUTER		DI_K_MYCOMPUTER
	#define LCIK_MAIL			DI_K_MAIL
	#define LCIK_MEDIASELECT	DI_K_MEDIASELECT

	#define LCIK_BACKSPACE		DI_K_BACKSPACE
	#define LCIK_NUMPADSTAR		DI_K_NUMPADSTAR
	#define LCIK_LALT			DI_K_LALT
	#define LCIK_CAPSLOCK		DI_K_CAPSLOCK
	#define LCIK_NUMPADMINUS	DI_K_NUMPADMINUS
	#define LCIK_NUMPADPLUS		DI_K_NUMPADPLUS
	#define LCIK_NUMPADPERIOD	DI_K_NUMPADPERIOD
	#define LCIK_NUMPADSLASH	DI_K_NUMPADSLASH
	#define LCIK_RALT			DI_K_RALT
	#define LCIK_UPARROW		DI_K_UPARROW
	#define LCIK_PGUP			DI_K_PGUP
	#define LCIK_LEFTARROW		DI_K_LEFTARROW
	#define LCIK_RIGHTARROW		DI_K_RIGHTARROW
	#define LCIK_DOWNARROW		DI_K_DOWNARROW
	#define LCIK_PGDN			DI_K_PGDN
	#define LCIK_CIRCUMFLEX		DI_K_CIRCUMFLEX

#else

// - on main keyboard
	#define WNVK_MINUS		0xBD
	#define WNVK_EQUALS		0xBB
	#define WNVK_BACKSLASH	0xDC

	#define WNVK_LBRACKET	0xDB
	#define WNVK_RBRACKET	0xDD

	#define WNVK_SEMICOLON	0xBA
	#define WNVK_APOSTROPHE	0xDE

	#define WNVK_COMMA		0xBC

	// . on main keyboard
	#define WNVK_PERIOD		0xBE
	#define WNVK_SLASH		0xBF

	#define WNVK_0			0x30
	#define WNVK_1			0x31
	#define WNVK_2			0x32
	#define WNVK_3			0x33
	#define WNVK_4			0x34
	#define WNVK_5			0x35
	#define WNVK_6			0x36
	#define WNVK_7			0x37
	#define WNVK_8			0x38
	#define WNVK_9			0x39
	#define WNVK_A			0x41
	#define WNVK_B			0x42
	#define WNVK_C			0x43
	#define WNVK_D			0x44
	#define WNVK_E			0x45
	#define WNVK_F			0x46
	#define WNVK_G			0x47
	#define WNVK_H			0x48
	#define WNVK_I			0x49
	#define WNVK_J			0x4A
	#define WNVK_K			0x4B
	#define WNVK_L			0x4C
	#define WNVK_M			0x4D
	#define WNVK_N			0x4E
	#define WNVK_O			0x4F
	#define WNVK_P			0x50
	#define WNVK_Q			0x51
	#define WNVK_R			0x52
	#define WNVK_S			0x53
	#define WNVK_T			0x54
	#define WNVK_U			0x55
	#define WNVK_V			0x56
	#define WNVK_W			0x57
	#define WNVK_X			0x58
	#define WNVK_Y			0x59
	#define WNVK_Z			0x5A

	#define WNVK_LBUTTON	0x01
	#define WNVK_RBUTTON	0x02
	#define WNVK_CANCEL		0x03
	#define WNVK_MBUTTON	0x04
	#define WNVK_BACK		0x08
	#define WNVK_TAB		0x09
	#define WNVK_CLEAR		0x0C
	#define WNVK_RETURN		0x0D
	#define WNVK_SHIFT		0x10
	#define WNVK_CONTROL	0x11
	#define WNVK_MENU		0x12
	#define WNVK_PAUSE		0x13
	#define WNVK_CAPITAL	0x14
	#define WNVK_ESCAPE		0x1B
	#define WNVK_SPACE		0x20
	#define WNVK_PRIOR		0x21
	#define WNVK_NEXT		0x22
	#define WNVK_END		0x23
	#define WNVK_HOME		0x24
	#define WNVK_LEFT		0x25
	#define WNVK_UP			0x26
	#define WNVK_RIGHT		0x27
	#define WNVK_DOWN		0x28
	#define WNVK_SELECT		0x29
	#define WNVK_EXECUTE	0x2B
	#define WNVK_SNAPSHOT	0x2C
	#define WNVK_INSERT		0x2D
	#define WNVK_DELETE		0x2E
	#define WNVK_HELP		0x2F
	#define WNVK_LWIN		0x5B
	#define WNVK_RWIN		0x5C
	#define WNVK_APPS		0x5D
	#define WNVK_NUMPAD0	0x60
	#define WNVK_NUMPAD1	0x61
	#define WNVK_NUMPAD2	0x62
	#define WNVK_NUMPAD3	0x63
	#define WNVK_NUMPAD4	0x64
	#define WNVK_NUMPAD5	0x65
	#define WNVK_NUMPAD6	0x66
	#define WNVK_NUMPAD7	0x67
	#define WNVK_NUMPAD8	0x68
	#define WNVK_NUMPAD9	0x69
	#define WNVK_MULTIPLY	0x6A
	#define WNVK_ADD		0x6B
	#define WNVK_SEPARATOR	0x6C
	#define WNVK_SUBTRACT	0x6D
	#define WNVK_DECIMAL	0x6E
	#define WNVK_DIVIDE		0x6F
	#define WNVK_F1			0x70
	#define WNVK_F2			0x71
	#define WNVK_F3			0x72
	#define WNVK_F4			0x73
	#define WNVK_F5			0x74
	#define WNVK_F6			0x75
	#define WNVK_F7			0x76
	#define WNVK_F8			0x77
	#define WNVK_F9			0x78
	#define WNVK_F10		0x79
	#define WNVK_F11		0x7A
	#define WNVK_F12		0x7B
	#define WNVK_F13		0x7C
	#define WNVK_F14		0x7D
	#define WNVK_F15		0x7E
	#define WNVK_F16		0x7F
	#define WNVK_F17		0x80
	#define WNVK_F18		0x81
	#define WNVK_F19		0x82
	#define WNVK_F20		0x83
	#define WNVK_F21		0x84
	#define WNVK_F22		0x85
	#define WNVK_F23		0x86
	#define WNVK_F24		0x87
	#define WNVK_NUMLOCK	0x90
	#define WNVK_SCROLL		0x91
	#define WNVK_LSHIFT		0xA0
	#define WNVK_RSHIFT		0xA1
	#define WNVK_LCONTROL	0xA2
	#define WNVK_RCONTROL	0xA3
	#define WNVK_LMENU		0xA4
	#define WNVK_RMENU		0xA5
	#define WNVK_PACKET		0xE7
	#define WNVK_ATTN		0xF6
	#define WNVK_CRSEL		0xF7
	#define WNVK_EXSEL		0xF8
	#define WNVK_EREOF		0xF9
	#define WNVK_PLAY		0xFA
	#define WNVK_ZOOM		0xFB
	#define WNVK_NONAME		0xFC
	#define WNVK_PA1		0xFD
	#define WNVK_OEM_CLEAR	0xFE

	#define WNVK_KANA		0x15
	#define WNVK_HANGEUL	0x15
	#define WNVK_HANGUL		0x15
	#define WNVK_JUNJA		0x17
	#define WNVK_FINAL		0x18
	#define WNVK_HANJA		0x19
	#define WNVK_KANJI		0x19

	#define WNVK_CONVERT	0x1C
	#define WNVK_NONCONVERT	0x1D
	#define WNVK_ACCEPT		0x1E
	#define WNVK_MODECHANGE	0x1F

	#define WNVK_SELECT		0x29
	#define WNVK_PRINT		0x2A
	#define WNVK_EXECUTE	0x2B
	#define WNVK_SNAPSHOT	0x2C
	#define WNVK_INSERT		0x2D
	#define WNVK_DELETE		0x2E
	#define WNVK_HELP		0x2F
	#define WNVK_PROCESSKEY	0xE5


	#define LCIK_LBUTTON		WNVK_LBUTTON
	#define LCIK_RBUTTON		WNVK_RBUTTON
	#define LCIK_CANCEL			WNVK_CANCEL
	#define LCIK_MBUTTON		WNVK_MBUTTON

	#define LCIK_BACK			WNVK_BACK
	#define LCIK_TAB			WNVK_TAB

	#define LCIK_CLEAR			WNVK_CLEAR
	#define LCIK_RETURN			WNVK_RETURN

	#define LCIK_SHIFT			WNVK_SHIFT
	#define LCIK_CONTROL		WNVK_CONTROL
	#define LCIK_MENU			WNVK_MENU
	#define LCIK_PAUSE			WNVK_PAUSE
	#define LCIK_CAPITAL		WNVK_CAPITAL

	#define LCIK_KANA			WNVK_KANA
	#define LCIK_HANGEUL		WNVK_HANGEUL
	#define LCIK_HANGUL			WNVK_HANGUL
	#define LCIK_JUNJA			WNVK_JUNJA
	#define LCIK_FINAL			WNVK_FINAL
	#define LCIK_HANJA			WNVK_HANJA
	#define LCIK_KANJI			WNVK_KANJI

	#define LCIK_ESCAPE			WNVK_ESCAPE

	#define LCIK_CONVERT		WNVK_CONVERT
	#define LCIK_NONCONVERT		WNVK_NONCONVERT
	#define LCIK_ACCEPT			WNVK_ACCEPT
	#define LCIK_MODECHANGE		WNVK_MODECHANGE

	#define LCIK_SPACE			WNVK_SPACE
	#define LCIK_PRIOR			WNVK_PRIOR
	#define LCIK_NEXT			WNVK_NEXT

	#define LCIK_PAGEUP			WNVK_PRIOR
	#define LCIK_PAGEDOWN		WNVK_NEXT
	#define LCIK_VOL_UP			WNVK_PRIOR
	#define LCIK_VOL_DOWN		WNVK_NEXT

	#define LCIK_END			WNVK_END
	#define LCIK_HOME			WNVK_HOME
	#define LCIK_LEFT			WNVK_LEFT
	#define LCIK_UP				WNVK_UP
	#define LCIK_RIGHT			WNVK_RIGHT
	#define LCIK_DOWN			WNVK_DOWN
	#define LCIK_SELECT			WNVK_SELECT
	#define LCIK_PRINT			WNVK_PRINT
	#define LCIK_EXECUTE		WNVK_EXECUTE
	#define LCIK_SNAPSHOT		WNVK_SNAPSHOT
	#define LCIK_INSERT			WNVK_INSERT
	#define LCIK_DELETE			WNVK_DELETE
	#define LCIK_HELP			WNVK_HELP

	#define LCIK_LWIN			WNVK_LWIN
	#define LCIK_RWIN			WNVK_RWIN
	#define LCIK_APPS			WNVK_APPS

	#define LCIK_NUMPAD0		WNVK_NUMPAD0
	#define LCIK_NUMPAD1		WNVK_NUMPAD1
	#define LCIK_NUMPAD2		WNVK_NUMPAD2
	#define LCIK_NUMPAD3		WNVK_NUMPAD3
	#define LCIK_NUMPAD4		WNVK_NUMPAD4
	#define LCIK_NUMPAD5		WNVK_NUMPAD5
	#define LCIK_NUMPAD6		WNVK_NUMPAD6
	#define LCIK_NUMPAD7		WNVK_NUMPAD7
	#define LCIK_NUMPAD8		WNVK_NUMPAD8
	#define LCIK_NUMPAD9		WNVK_NUMPAD9
	#define LCIK_MULTIPLY		WNVK_MULTIPLY
	#define LCIK_ADD			WNVK_ADD
	#define LCIK_SEPARATOR		WNVK_SEPARATOR
	#define LCIK_SUBTRACT		WNVK_SUBTRACT
	#define LCIK_DECIMAL		WNVK_DECIMAL
	#define LCIK_DIVIDE			WNVK_DIVIDE
	#define LCIK_F1				WNVK_F1
	#define LCIK_F2				WNVK_F2
	#define LCIK_F3				WNVK_F3
	#define LCIK_F4				WNVK_F4
	#define LCIK_F5				WNVK_F5
	#define LCIK_F6				WNVK_F6
	#define LCIK_F7				WNVK_F7
	#define LCIK_F8				WNVK_F8
	#define LCIK_F9				WNVK_F9
	#define LCIK_F10			WNVK_F10
	#define LCIK_F11			WNVK_F11
	#define LCIK_F12			WNVK_F12
	#define LCIK_F13			WNVK_F13
	#define LCIK_F14			WNVK_F14
	#define LCIK_F15			WNVK_F15
	#define LCIK_F16			WNVK_F16
	#define LCIK_F17			WNVK_F17
	#define LCIK_F18			WNVK_F18
	#define LCIK_F19			WNVK_F19
	#define LCIK_F20			WNVK_F20
	#define LCIK_F21			WNVK_F21
	#define LCIK_F22			WNVK_F22
	#define LCIK_F23			WNVK_F23
	#define LCIK_F24			WNVK_F24

	#define LCIK_NUMLOCK		WNVK_NUMLOCK
	#define LCIK_SCROLL			WNVK_SCROLL

	#define LCIK_LSHIFT			WNVK_LSHIFT
	#define LCIK_RSHIFT			WNVK_RSHIFT
	#define LCIK_LCONTROL		WNVK_LCONTROL
	#define LCIK_RCONTROL		WNVK_RCONTROL
	#define LCIK_LMENU			WNVK_LMENU
	#define LCIK_RMENU			WNVK_RMENU
	#define LCIK_LALT			WNVK_LMENU
	#define LCIK_RALT			WNVK_RMENU

	#define LCIK_PROCESSKEY		WNVK_PROCESSKEY

	#define LCIK_ATTN			WNVK_ATTN
	#define LCIK_CRSEL			WNVK_CRSEL
	#define LCIK_EXSEL			WNVK_EXSEL
	#define LCIK_EREOF			WNVK_EREOF
	#define LCIK_PLAY			WNVK_PLAY
	#define LCIK_ZOOM			WNVK_ZOOM
	#define LCIK_NONAME			WNVK_NONAME
	#define LCIK_PA1			WNVK_PA1
	#define LCIK_OEM_CLEAR		WNVK_OEM_CLEAR

	#define LCIK_MINUS			WNVK_MINUS
	#define LCIK_EQUALS			WNVK_EQUALS
	#define LCIK_BACKSLASH		WNVK_BACKSLASH
	#define LCIK_LBRACKET		WNVK_LBRACKET
	#define LCIK_RBRACKET		WNVK_RBRACKET
	#define LCIK_SEMICOLON		WNVK_SEMICOLON
	#define LCIK_APOSTROPHE		WNVK_APOSTROPHE
	#define LCIK_COMMA			WNVK_COMMA
	#define LCIK_PERIOD			WNVK_PERIOD
	#define LCIK_SLASH			WNVK_SLASH
	#define LCIK_SYSRQ			WNVK_SNAPSHOT
	#define LCIK_GRAVE			WNVK_SELECT

	#define LCIK_0				WNVK_0
	#define LCIK_1				WNVK_1
	#define LCIK_2				WNVK_2
	#define LCIK_3				WNVK_3
	#define LCIK_4				WNVK_4
	#define LCIK_5				WNVK_5
	#define LCIK_6				WNVK_6
	#define LCIK_7				WNVK_7
	#define LCIK_8				WNVK_8
	#define LCIK_9				WNVK_9

	#define LCIK_A				WNVK_A
	#define LCIK_B				WNVK_B
	#define LCIK_C				WNVK_C
	#define LCIK_D				WNVK_D
	#define LCIK_E				WNVK_E
	#define LCIK_F				WNVK_F
	#define LCIK_G				WNVK_G
	#define LCIK_H				WNVK_H
	#define LCIK_I				WNVK_I
	#define LCIK_J				WNVK_J
	#define LCIK_K				WNVK_K
	#define LCIK_L				WNVK_L
	#define LCIK_M				WNVK_M
	#define LCIK_N				WNVK_N
	#define LCIK_O				WNVK_O
	#define LCIK_P				WNVK_P
	#define LCIK_Q				WNVK_Q
	#define LCIK_R				WNVK_R
	#define LCIK_S				WNVK_S
	#define LCIK_T				WNVK_T
	#define LCIK_U				WNVK_U
	#define LCIK_V				WNVK_V
	#define LCIK_W				WNVK_W
	#define LCIK_X				WNVK_X
	#define LCIK_Y				WNVK_Y
	#define LCIK_Z				WNVK_Z

#endif


// Keypad Mapping
typedef BYTE*	PKEYMAP;

// Multi-touch Screen
struct TLC_INPUT_TS
{
	INT	x,y;		// Multi-touch Screen x, y
	INT	t;			// Multi-touch state
};


INT  LcStv_InputOpen();															// Input device open.
INT  LcStv_InputClose();														// Input device release.

INT  LcStv_InputReadKey(PKEYMAP pkey);											// gain Keypad data(needs over 32 unsigned char: minimum 32byte)
INT  LcStv_InputWriteKey(INT key, INT v);										// write the keypad data. key is LCIK_ key..

INT  LcStv_InputReadMts(INT idx, TLC_INPUT_TS* ts);								// gain Multi-touch Screen coordinate and state. ex) TLC_INPUT_TS t; LcStv_InputReadMts([0,16], &t);
INT  LcStv_InputWriteMts(INT idx, TLC_INPUT_TS* ts=NULL);						// write the ts data. NULL sets to default. ex) TLC_INPUT_TS t...; LcStv_InputWriteMts([0,16], &t);
INT  LcStv_InputCountMts();														// read the active touch pointers




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// GLC Ime

enum
{
	LCIME_ENG = 0	,															// Ime state
	LCIME_KOR		,															// Korean
	LCIME_JPN		,															// Japanese.	It's not Implemental
	LCIME_CHR		,															// Chinese.		It's not Implemental
	LCIME_MAX = 520	,															// Ime Max buffer length
};

INT  LcStv_ImeOpen(UINT bsKeyId);												// reset and enable
INT  LcStv_ImeClose();															// reset and disable
INT  LcStv_ImeString(char* sOut, int ch=0);										// get the composed string. on windows system, ch='|' it returns with '|' character
void LcStv_ImeClear();															// clear the string buffer.
INT  LcStv_ImeState();															// get active(true)/inactive(false) for windows system
INT  LcStv_ImeEvent(INT bRemove=LC_FALSE);										// get the Ime complete event(LC_TRUE, LC_FALSE)
INT  LcStv_ImeCallback(LC_HANDLE h, LC_HANDLE m, LC_HANDLE w, LC_HANDLE l);		// while Ime processing on windows system.  return LC_OK, else return LC_TRUE




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// GLC Sensor

enum LC_SENSOR_TYPE
{
	LC_GSN_NONE					= 0 ,
	LC_GSN_ACCELEROMETER		= 1 ,
	LC_GSN_MAGNETIC_FIELD		= 2 ,
	LC_GSN_ORIENTATION			= 3 ,
	LC_GSN_GYROSCOPE			= 4 ,
	LC_GSN_LIGHT				= 5 ,
	LC_GSN_PRESSURE				= 6 ,
	LC_GSN_TEMPERATURE			= 7 ,
	LC_GSN_PROXIMITY			= 8 ,
	LC_GSN_GRAVITY				= 9 ,
	LC_GSN_LINEAR_ACCELERATION	= 10,
	LC_GSN_ROTATION_VECTOR		= 11,
};

// sensor data
struct TLC_SENSOR
{
	FLOAT x, y, z;			// value
	INT   t;				// type
};


INT  LcStv_SensorOpen();							// Init Device
INT  LcStv_SensorClose();							// Release Device
INT  LcStv_SensorWrite(INT n, TLC_SENSOR* v);		// Write data
INT  LcStv_SensorRead(INT n, TLC_SENSOR* v);			// Read data




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// GLC Haptic motor

INT  LcStv_HapticOpen();										// Init Vibration Motor Device
INT  LcStv_HapticClose();										// Release Device
INT  LcStv_HapticEnable();										// Motor Is Enable=LC_OK, Disable = LC_EFAIL
INT  LcStv_HapticPlay(INT millisec);							// One-Action Motor Play
INT  LcStv_HapticPattern(INT p[], INT n, INT r=LC_INFINITE);	// Motor Play pattern	n is {delay-play} count, r is repeat -1 infinite else once
INT  LcStv_HapticStop();										// Motor Stop




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Mixer

enum ELC_MIXER_CHANNEL
{
	LC_MIXER_VOLUME		= 0x0,	// Speaker
	LC_MIXER_HEADPHONE	= 0x0,	// Speaker
	LC_MIXER_BASS		= 0x1,	// Bass
	LC_MIXER_TREBLE		= 0x2,	// Treble
	LC_MIXER_PCM		= 0x4,	// PCM
	LC_MIXER_LINE		= 0x6,	// Line
	LC_MIXER_MIC		= 0x7,	// Microphone
};


INT LcStv_MixerOpen();											// Mixer Device Init
INT LcStv_MixerClose();											// Mixer Device Release
INT	LcStv_MixerReadVolumeRange(INT* pMaxMin);					// need 8byte INT. Get Mixer Device Volume Range. Max, Min value range is [0 ,127]
INT	LcStv_MixerReadVolume (INT channel, INT* left, INT* right);	// Get the Mixer Device Volume
INT	LcStv_MixerWriteVolume(INT channel, INT  left, INT  right);	// Set the Mixer Device Volume


enum ELC_BATTERY
{
	// Battery state
	LC_BATTERY_HIGH = 1,
	LC_BATTERY_MID,
	LC_BATTERY_LOW,
	LC_BATTERY_EMPTY,
};

INT LcStv_BatteryRead();				// return the Battery Remain

INT LcStv_RecordingSound(char* pBuf);	// Recording: need minimum 1024 byte. return Recorded size


#endif //_LC_Stdev_H_

