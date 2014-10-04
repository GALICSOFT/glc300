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
ILCX_Net*	g_pSvr = NULL;



int main(int argc, char** argv)
{
	if(LC_FAILED(LcNet_Open()))
		return 0;


	//char*	ipLst=NULL;
	//int w   = LC_RSC_NAME;
	//int nIp = LcNet_LocalIpAddress(&ipLst, w);

	//for(int n=0; n<nIp; ++n)
	//{
	//	char* sIp = ipLst +w*n;
	//	printf("Ip Addrs: %s\n", sIp);
	//}



	INT hr = 0;
	INT cnt_msg =0;
	INT cnt_rcv =0;

	TLC_SOCKET tsc={0};

	tsc.sck_ap = LCNET_TCP4;
	tsc.sck_ht = LCNET_SERVER;
	tsc.sck_nt = LCNET_IO_EVENT;
	tsc.sck_pt = uPt;

	TLC_ARGS	args;
	MAKE_ARG1(args, (LC_HANDLE)&tsc);
	hr = LcxEnt_CreateNet(NULL, &g_pSvr, &args);
	if(LC_FAILED(hr))
		return 0;

	hr=g_pSvr->Query(LCX_QUERY_NET_START, &tsc);





	while(1)
	{
		hr=g_pSvr->Query(LCX_QUERY_NET_UPDATE, NULL);
		if(LC_EFAIL == hr)
			break;

		cnt_msg = g_pSvr->GetAttrib(LCNET_CMD_MSG, NULL);
		if(0>= cnt_msg)
			continue;

		for(int n=0; n<cnt_msg; ++n)
		{
			TLC_NETMSG	msg;
			hr = g_pSvr->GetAttrib(LCNET_CMD_MSG, &msg);
			if(0 >= hr)
				break;


			switch(msg.nsm_cm)
			{
				case LCNET_ST_ACCEPT :
				{
					LOGI("New accept %d\n", msg.nsm_ac);
					break;
				}
				case LCNET_ST_CONNECT :
				{
					LOGI("New connect %d\n", msg.nsm_ac);
					break;
				}
				case LCNET_ST_CLOSE :
				{
					LOGI("Client close %d\n", msg.nsm_ac);
					break;
				}
				case LCNET_ST_SEND :
				{
					LOGI("send to client %d\n", msg.nsm_ac);
					break;
				}
				case LCNET_ST_RECV :
				{
					cnt_rcv = g_pSvr->Recv(&msg.nsm_ac, NULL);

					for(int k=0; k<cnt_rcv; ++k)
					{
						TLC_PACKET	pck_rcv;
						char*		sbuf;
						hr			= g_pSvr->Recv(&msg.nsm_ac, &pck_rcv);
						if(LC_FAILED(hr))
							break;

						sbuf = pck_rcv.GetData();



						// data receiving
						char		s_rcv[LCNET_PCK_MAX]={0};		// CP949 buffer
						char*		p_rcv= sbuf;

						LcStr_StringUtf8ToCp949(s_rcv, p_rcv);
						p_rcv = s_rcv;
						LOGI("Receive::%s\n", p_rcv);



						LOGI("Receive [0x%08X]: %d\n", msg.nsm_ac, hr);

						INT		iLen=0;
						char	sTmp[256]={0};		// Temp 버퍼
						static	int sqc = 0;
						++sqc;

						sprintf(sTmp, "Server Echo[0x%08X]:%s", msg.nsm_ac, sbuf);


						// 데이터 송신
						TLC_PACKET	pck_snd;

						iLen = strlen(sTmp);
						iLen = (iLen >>1 ) <<1;	iLen += 2;

						pck_snd.WriteBegin(0, sqc);
							pck_snd.AddData(sTmp, iLen);
						pck_snd.WriteEnd();

						int nClient = g_pSvr->GetAttrib(LCNET_CMD_RMH_COUNT, NULL);

						for(int idx=1; idx<=nClient; ++idx)
						{
							TLCX_RMH* pH = NULL;
							TLC_ARGS  args;

							MAKE_ARG1(args, idx);

							hr = g_pSvr->GetAttrib(LCNET_CMD_RMH_LST, &args);
							if(LC_FAILED(hr))
								continue;

							pH = (TLCX_RMH*)( (LC_HANDLE)args._1 );
							g_pSvr->Send(pH->rm_a, &pck_snd);
						}
					}

					break;
				}
				default :
				{
					break;
				}
			}

		}


		LcAux_Sleep(1);
	}


	delete g_pSvr;

	LcNet_Close();
	return 0;
}

