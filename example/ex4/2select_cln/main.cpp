//
//
////////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER) && _MSC_VER >= 1200
  #pragma warning( disable : 4786)
  #pragma warning( disable : 4996)
#endif


#if defined(_MSC_VER)
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
#include <stdlib.h>
#include <string.h>

#include <LcType.h>
#include <LcBase.h>
#include <LcMath.h>
#include <LcEuclid.h>
#include <LcCore.h>
#include <LcAux.h>
#include <LcxNetwork.h>


USHORT		uPt	= 20000;
//BYTE		uIp[LC_IP_LEN]	= {127,0,0,1,0};
BYTE		uIp[LC_IP_LEN]	= {192,168,0,7,0};
ILCX_Net*	g_pCln = NULL;


INT TestSendData();


int main(int argc, char** argv)
{
	INT	hr = 0;
	INT cnt_msg = 0;
	INT cnt_rcv = 0;

	TLC_SOCKET tsc={0};

	tsc.sck_ap  = LCNET_TCP4;
	tsc.sck_ht  = LCNET_CLIENT;
	tsc.sck_nt = LCNET_IO_SELECT;

	TLC_ARGS	args;
	MAKE_ARG1(args, (LC_HANDLE)&tsc);
	hr = LcxEnt_CreateNet(NULL, &g_pCln, &args);
	if(LC_FAILED(hr))
		return 0;


	tsc.sck_pt   = uPt;
	memcpy(tsc.sck_pi, uIp, 4);
	g_pCln->Query(LCX_QUERY_NET_CONNECT, &tsc);


	while(g_pCln)
	{
		TestSendData();
		hr=g_pCln->Query(LCX_QUERY_NET_UPDATE, NULL);

		if(0>hr)
			break;



		hr      = g_pCln->GetAttrib(LCNET_CMD_STATE, NULL);
		cnt_msg = g_pCln->GetAttrib(LCNET_CMD_MSG, NULL);


		if(LC_FAILED(hr))
			break;

		if(0>= cnt_msg)
			continue;


		for(int n=0; n<cnt_msg; ++n)
		{
			TLC_NETMSG	msg;
			hr = g_pCln->GetAttrib(LCNET_CMD_MSG, &msg);
			if(LC_FAILED(hr) )
				break;


			switch(msg.nsm_cm)
			{
				case LCNET_ST_CONNECT :
				{
					LOGI("Connection success\n");
					break;
				}
				case LCNET_ST_CLOSE :
				{
					if(LCNET_ST_INVALID == msg.nsm_ac)
						LOGI("Server is not valid. Connection Error\n");

					else
						LOGI("Disconnect\n");

					goto END;
				}
				case LCNET_ST_SEND :
				{
					LOGI("Sending message\n");
					break;
				}
				case LCNET_ST_RECV :
				{
					cnt_rcv = g_pCln->Recv(0, NULL);

					for(int k=0; k<cnt_rcv; ++k)
					{
						TLC_PACKET	pck_rcv;
						char*		sbuf;

						if(LC_FAILED(g_pCln->Recv(0, &pck_rcv)))
							break;

						sbuf = pck_rcv.GetData();



						// data receiving
						char		s_rcv[LCNET_PCK_MAX]={0};		// CP949 buffer
						char*		p_rcv= sbuf;

						LcStr_StringUtf8ToCp949(s_rcv, p_rcv);
						p_rcv = s_rcv;
						LOGI("Receive::%s\n", p_rcv);
					}

					break;
				}
				default :
				{
					break;
				}
			}

		}

		//Sleep(100);
	
	}


END:
	delete g_pCln;

	LcNet_Close();
	return 0;
}



INT TestSendData()
{
	if(NULL == g_pCln)
		return 0;

	INT bConnected = g_pCln->GetAttrib(LCNET_CMD_STATE, &bConnected);

	if(LCNET_ST_CONNECT != bConnected)
		return bConnected;


	int		hr;
	static int c=0;
	++c;

	static int sqc=0;

	if(c<80000)
		return 0;


	c=0;
	++sqc;



	INT			iLen=0;
	char	data[128]={0};		// Temp 버퍼
	sprintf(data, "안녕하세요 Sending...... %4d", sqc);
	iLen = strlen(data);


	// data sending
	char		s_snd[128]={0};		// UTF8 buffer
	char*		p_snd = NULL;
	TLC_PACKET	pck;

	p_snd = data;
	LcStr_StringCp949ToUtf8(s_snd, data);
	p_snd = s_snd;

	iLen = strlen(p_snd);
	iLen = (iLen >>1 ) <<1;	iLen += 2;

	pck.WriteBegin(0, sqc);
		pck.AddData(p_snd, iLen);
	pck.WriteEnd();

	hr = g_pCln->Send(0, &pck);
	if(LC_FAILED(hr))
		return -1;

	return 0;
}


