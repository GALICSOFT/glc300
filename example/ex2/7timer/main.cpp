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


#include <stdio.h>

#include <LcType.h>
#include <LcBase.h>
#include <LcMath.h>
#include <LcEuclid.h>
#include <LcCore.h>
#include <LcAux.h>


struct TimeEvent : public ILC_MsgPrc
{
	virtual INT MsgPrc(LC_HANDLE p1=0, LC_HANDLE =0, LC_HANDLE =0, LC_HANDLE =0)
	{
		PLC_TIMER pTimer = (PLC_TIMER)p1;

		UINT nCnt	= pTimer->Count();
		UINT nRemain= pTimer->RemainCount();
		char* sMsg	= (char*)pTimer->UserData();

		char sbuf[128]={0};
		int r = 0;

		r = sprintf(&sbuf[r], "key: 0x%p", p1);

		if(sMsg )
			r += sprintf(&sbuf[r], " Msg: %s", sMsg);

		r += sprintf(&sbuf[r], " count:%3d   remain:%3d", nCnt, nRemain);

		if(0 == nRemain)
			r += sprintf(&sbuf[r], "   --- stop");
		
		r += sprintf(&sbuf[r], "\n");

		printf(sbuf);

		return 0;
	}
};


int main(int arg, char *argv[])
{
	INT hr;
	PLC_TIMER	m_pTimer1 = 0;
	PLC_TIMER	m_pTimer2 = 0;
	PLC_TIMER	m_pTimer3 = 0;

	char msg1[] = "message1";
	char msg2[] = "message2";
	char msg3[] = "message3";




	// set 1 sec interval timer.
	hr = LcAux_TimerCreate(NULL, &m_pTimer1, 0, 700, 40, new TimeEvent, msg1);

	if(LC_FAILED(hr))
	{
		printf("LcTimer_Set() fail\n");
		return -1;
	}

	// set 2 sec interval timer.
	hr = LcAux_TimerCreate(NULL, &m_pTimer2, 0, 800, 50, new TimeEvent, msg2);

	if(LC_FAILED(hr))
	{
		printf("LcTimer_Set() fail\n");
		return -1;
	}

	// set 3 sec interval timer.
	hr = LcAux_TimerCreate(NULL, &m_pTimer3, 0, 900, 60, new TimeEvent, msg3);

	if(LC_FAILED(hr))
	{
		printf("LcTimer_Set() fail\n");
		return -1;
	}

	m_pTimer1->Start();
	m_pTimer2->Start();
	m_pTimer3->Start();

	int key = 0;
	char cmd[32] = {0,};

	while(1)
	{
		LcAux_Sleep(1000);

		if(	0 == m_pTimer1->RemainCount() &&
			0 == m_pTimer2->RemainCount() &&
			0 == m_pTimer3->RemainCount() )
			break;
	}

	m_pTimer1->Release();
	m_pTimer2->Release();
	m_pTimer3->Release();

	return 0;
}

