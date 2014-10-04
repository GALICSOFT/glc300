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

#include <WinSock2.h>
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


BYTE		g_sIp[LC_IP_LEN] = {0x00, 0x19, 0x0E, 0x11, 0x56, 0xD4, 0};
//BYTE		g_sIp[LC_IP_LEN] = {0x18, 0xE2, 0xC2, 0x0E, 0x53, 0x24, 0};
//BYTE		g_sIp[LC_IP_LEN] = {0x88, 0x53, 0x2E, 0xBC, 0xCA, 0xC2, 0};

char		g_uuid[ ] = "990CAFFE-8C4F-4522-8F59-5F87EF4340C3";
ILCX_Net*	g_pCln = NULL;


DWORD LC_WINAPI ThreadRecv(void* pParam);


int main(int argc, char** argv)
{
	if(LC_FAILED(LcNet_Open()))
		return 0;

	INT hr = 0;
	TLC_SOCKET tsc={0};

	tsc.sck_ap   = LCNET_BT;
	tsc.sck_ht   = LCNET_CLIENT;
	tsc.sck_tx[0]= g_uuid;

	TLC_ARGS	args;
	MAKE_ARG1(args, (LC_HANDLE)&tsc);
	hr = LcxEnt_CreateNet(NULL, &g_pCln, &args);
	if(LC_FAILED(hr))
		return 0;

	LC_HANDLE hTh = LcNet_ThreadCreate((void*)ThreadRecv);
	LcNet_CloseHandle(&hTh);

	memcpy(tsc.sck_pi, g_sIp, LC_IP_LEN);
	tsc.sck_tx[0]= g_uuid;
	g_pCln->Query(LCX_QUERY_NET_CONNECT, &tsc);



	// 채팅...
	while(1)
	{
		hr= g_pCln->GetAttrib(LCNET_CMD_STATE, NULL);
		if(LC_FAILED(hr))
			break;

		static int sqc = 0;
		++sqc;

		LcAux_Sleep(300);

		INT			iLen=0;
		char	data[128]={0};		// Temp 버퍼
		sprintf(data, "안녕하세요 Sending...... %4d", sqc);
		iLen = strlen(data);

		if(1 >iLen)
			continue;


		if('\n' == data[iLen-1])
		{
			data[iLen-1] =0;
			--iLen;
		}

		if(0 == g_pCln)
			break;


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
			break;
	}

	delete g_pCln;

	LcNet_Close();
	return 0;
}



DWORD LC_WINAPI ThreadRecv(void* pParam)
{
	INT	hr = 0;
	INT cnt_msg = 0;
	INT cnt_rcv = 0;


	while(1)
	{
		LcNet_Sleep(1);

		if(NULL == g_pCln)
			break;

		hr      = g_pCln->GetAttrib(LCNET_CMD_STATE, NULL);
		cnt_msg = g_pCln->GetAttrib(LCNET_CMD_MSG, NULL);

		if(LC_FAILED(hr))
			goto END;


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

	LcNet_ThreadEnd();
	return 0;
}

