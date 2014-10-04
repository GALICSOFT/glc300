//
//
//
////////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER) && _MSC_VER >= 1200
  #pragma warning( disable : 4786)
  #pragma warning( disable : 4996)
#endif


#if defined(_MSC_VER)
  #pragma comment(linker, "/subsystem:console")
  #pragma comment(lib, "lgpwn_a30_.lib")
  #pragma comment(lib, "lgpwn_b30_.lib")
  #pragma comment(lib, "lgpwn_c30_.lib")
  #pragma comment(lib, "lgpwn_d30_.lib")
  #pragma comment(lib, "lgpwn_i30_.lib")
  #pragma comment(lib, "lgpwn_n30_.lib")
  #pragma comment(lib, "lgpwn_e30_.lib")

  #pragma comment(lib, "OpenGL32.lib")
  #pragma comment(lib, "Imm32.lib")
  #pragma comment(lib, "winmm.lib")
  #pragma comment(lib, "dxguid.lib")
  #pragma comment(lib, "ws2_32.lib")
#endif


#include <vector>
using namespace std;


#include <stdio.h>

#include <LcType.h>
#include <LcBase.h>
#include <LcMath.h>
#include <LcEuclid.h>
#include <LcCore.h>
#include <LcAux.h>
#include <LcStdev.h>
#include <LcxEntity.h>
#include <LcxMedia.h>


PLC_DEVICE	m_pDev	= NULL;		// Device
PLC_SPRITE	m_pSpt	= NULL;		// 2D Sprite

PLCX_INPUT		m_pInput;		// Input



struct Obj2D
{
	FLOAT		x, y;	// center
	FLOAT		a;		// rotation angle(radian)
	float		w, h;	// width, height
};



Obj2D			m_obj1;
Obj2D			m_obj2;

LCXVECTOR3		g_rc1[4];
LCXVECTOR3		g_rc2[4];

INT				m_bCollision;


int Collision2DRect(FLOAT center1x, FLOAT center1y, FLOAT a1, FLOAT w1, FLOAT h1,
					FLOAT center2x, FLOAT center2y, FLOAT a2, FLOAT w2, FLOAT h2);


DOUBLE GetAppFrame();



void InitGame()
{
	if(LC_FAILED(LcxEnt_CreateInput(NULL, &m_pInput)))
		return;


	m_obj1.x = 214.0F;
	m_obj1.y = 100.0F;
	m_obj1.a = -0.12F;
	m_obj1.w = 200.0F;
	m_obj1.h = 100.0F;

	m_obj2.x = 452.0F;
	m_obj2.y = 230.0F;
	m_obj2.a =  0.88F;
	m_obj2.w = 350.0F;
	m_obj2.h = 80.00F;
}


// Main Loop
INT LC_CALLBACK Run(LC_HANDLE)
{
#if defined(_WIN32)
	LcAux_Sleep(10);
#endif

	static INT c=0;
	++c;

//	if(c>20*60*20)
	if(c>8*60*20)
	{
		printf("Game Process Terminated\n");
		return LC_EFAIL;
	}



	FLOAT fFrame = (FLOAT)GetAppFrame();


	// Input Update
	m_pInput->Update();

	const BYTE*	pKey = m_pInput->KeyMap();
	const BYTE*	pMts = m_pInput->MtsMap();

	if(pKey[LCIK_ESCAPE])
		return LC_EFAIL;


	// Move, Rotation Speed
	FLOAT speed = 2.0f;


	int i = 0;
	if(pKey[LCIK_A])
	{
		m_obj1.x -= speed;
	}

	if(pKey[LCIK_D])
	{
		m_obj1.x += speed;
	}

	if(pKey[LCIK_W])
	{
		m_obj1.y -= speed;
	}

	if(pKey[LCIK_Z])
	{
		m_obj1.y += speed;
	}

	if(pKey[LCIK_Q])
	{
		m_obj1.a += speed*0.01F;
	}

	if(pKey[LCIK_E])
	{
		m_obj1.a -= speed*0.01F;
	}



	if(pKey[LCIK_LEFT])
	{
		m_obj2.x -= speed;
	}

	if(pKey[LCIK_RIGHT])
	{
		m_obj2.x += speed;
	}

	if(pKey[LCIK_UP])
	{
		m_obj2.y -= speed;
	}

	if(pKey[LCIK_DOWN])
	{
		m_obj2.y += speed;
	}


	if(pKey[LCIK_HOME])
	{
		m_obj2.a += speed*0.01F;
	}

	if(pKey[LCIK_END])
	{
		m_obj2.a -= speed*0.01F;
	}



	// Prepare Rendering...
	m_pDev->BeginScene();

	// Clear Backbuffer
	m_pDev->Clear(LC_CLEAR_COLOR_BUFFER | LC_CLEAR_DEPTH_BUFFER);


	// Sprite Begin
	m_pSpt->Begin();


	m_bCollision =  Collision2DRect(  m_obj1.x, m_obj1.y, m_obj1.a, m_obj1.w, m_obj1.h
									, m_obj2.x, m_obj2.y, m_obj2.a, m_obj2.w, m_obj2.h
								);


	LCXCOLOR col(1,1,1,1);

	col = (m_bCollision)? LCXCOLOR(1,0,1,1) : LCXCOLOR(0.5F, 0, 0.5F, 1);

	m_pSpt->DrawLine(LC_PT_LINE_LOOP, g_rc1, 10.0F, &col, 4);

	col = (m_bCollision)? LCXCOLOR(0,1,1,1) : LCXCOLOR(0, 0.5F, 0.5F, 1);
	m_pSpt->DrawLine(LC_PT_LINE_LOOP, g_rc2, 10.0F, &col, 4);


	// Sprite End
	m_pSpt->End();


	// Post Rendering...
	m_pDev->EndScene();

	return LC_OK;
}



// Main Program
int main(int argc, char* argv[])
{
	int		hr = 0;


	// Init GLC Library
	if(LC_FAILED(LcSys_Init()))
		return LC_OK;

	// Set Main procedure Function Pointer
	if(LC_FAILED(LcSys_SetMainRunFunc(Run)))
		goto End;


	// Create Window
	hr = LcSys_CreateWindow(NULL, (char*)"LC_Tutorial");
	if(0 > hr)
		goto End;

	// Create GLC Rendering Device
	if(LC_FAILED(LcDev_CreateDevice(NULL, &m_pDev)))
		goto End;

	// Set Clear Color
	m_pDev->SetRenderState(LC_RS_CLEAR_COLOR, (UINT)0xFF006699);



	// get the default Rendering 2D sprite
	m_pSpt = (PLC_SPRITE)LcVar_ReadP(LC_VAR_SPRITE);


	InitGame();


	// Run Program
	while(1)
	{
		if(LC_FAILED(LcSys_Run()))
			break;

		// Flipping
		m_pDev->Present(0,0,0,0);
	}


//	free(buf);

End:

	// Release Device
	SAFE_RELEASE( m_pDev );

	// Release Window
	LcSys_DestroyWindow();

	// Release GLC
	LcSys_Close();

	hr = LcVar_RefCountObject();
	if(0 == hr)
		printf(
				"Remain: %d\n"
				"release success.\n"
				, hr
				);
	else
		printf(
				"Remain: %d\n"
				"The non-zero reference count means that\n"
				"there is something object not cleaned up.\n"
				, hr
				);

	return LC_OK;

}


DOUBLE GetAppFrame()
{
#if defined(_WIN32)
	static INT		MaxCount = 10;
#else
	static INT		MaxCount = 10;
#endif

	static DOUBLE	fFps = 0.;
	static INT		iCnt = 0;
	static DINT		dBgn = ::LcAux_TimeGetTime();
	DINT			dCur = ::LcAux_TimeGetTime();

	++iCnt;

	if(iCnt>=MaxCount)
	{
		fFps = DOUBLE(dCur-dBgn);
		fFps = iCnt*1000./fFps;
		iCnt = 0;
		dBgn = dCur;
	}

	return fFps;
}



int Collision2DRect(FLOAT center1x, FLOAT center1y, FLOAT a1, FLOAT w1, FLOAT h1,
					FLOAT center2x, FLOAT center2y, FLOAT a2, FLOAT w2, FLOAT h2)
{
	LCXVECTOR3	rc1[4];
	LCXVECTOR3	rc2[4];

	LCXVECTOR2	D;
	LCXVECTOR2  K;

	int i=0, j=0;
	
	INT		det = 1;
	float	xx = 0;
	float	yy = 0;

	float	cosT1 = cos(a1);
	float	sinT1 = sin(a1);
	float	cosT2 = cos(a2);
	float	sinT2 = sin(a2);


	rc1[0].x = -w1/2.0F;	rc1[0].y = -h1/2.0F;
	rc1[1].x =  w1/2.0F;	rc1[1].y = -h1/2.0F;
	rc1[2].x =  w1/2.0F;	rc1[2].y =  h1/2.0F;
	rc1[3].x = -w1/2.0F;	rc1[3].y =  h1/2.0F;

	rc2[0].x = -w2/2.0F;	rc2[0].y = -h2/2.0F;
	rc2[1].x =  w2/2.0F;	rc2[1].y = -h2/2.0F;
	rc2[2].x =  w2/2.0F;	rc2[2].y =  h2/2.0F;
	rc2[3].x = -w2/2.0F;	rc2[3].y =  h2/2.0F;

	for(i=0; i<4; ++i)
	{
		xx = rc1[i].x;
		yy = rc1[i].y;

		rc1[i].x = cosT1 *xx - sinT1 *yy + center1x;
		rc1[i].y = sinT1 *xx + cosT1 *yy + center1y;

		xx = rc2[i].x;
		yy = rc2[i].y;

		rc2[i].x = cosT2 *xx - sinT2 *yy + center2x;
		rc2[i].y = sinT2 *xx + cosT2 *yy + center2y;
	}


	memcpy(g_rc1, rc1, sizeof(rc1) );
	memcpy(g_rc2, rc2, sizeof(rc2) );


	for(i=0; i<4; ++i)
	{
		D.y = -rc1[i].x + rc1[(i + 3)%4].x;
		D.x =  rc1[i].y - rc1[(i + 3)%4].y;

		det = 1;
		for(j=0; j<4; ++j)
		{
			K.x = rc2[j].x - rc1[i].x;
			K.y = rc2[j].y - rc1[i].y;

			if( 0 >= D.x * K.x + D.y * K.y)
			{
				det =0;
				break;
			}
		}

		if(det)
			return LC_FALSE;


		D.y = -rc2[i].x + rc2[(i + 3)%4].x;
		D.x =  rc2[i].y - rc2[(i + 3)%4].y;


		det = 1;
		for(j=0; j<4; ++j)
		{
			K.x = rc1[j].x - rc2[i].x;
			K.y = rc1[j].y - rc2[i].y;

			if( 0 >= D.x * K.x + D.y * K.y)
			{
				det =0;
				break;
			}
		}

		if(det)
			return LC_FALSE;
	}

	return LC_TRUE;
}


