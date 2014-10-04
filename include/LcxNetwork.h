//	Copyright(C) GaLic Soft. All rights reserved.
//	GaLic Game Library Collection
//
// Interface for the ILCX_Network class.
//
////////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER)
  #pragma once
#endif

#ifndef _LcxNetwork_H_
#define _LcxNetwork_H_

#include <LcType.h>
#include <LcBase.h>


enum ELC_NETWORK
{
	// general return
	LCNET_TIMEOUT			= LC_OK,											// INVALID = LC_EFAIL

	// address family
	LCNET_AF_INET4			=      2,
	LCNET_AF_INET6			=     23,

	// protocol
	LCNET_TCP4				= 0x0006,											// AF_INET, IPPROTO_TCP
	LCNET_UDP4				= 0x0011,											// AF_INET, IPPROTO_UDP
	//LCNET_TCP6			= 0x1006,											// AF_INET6, IPPROTO_TCP
	//LCNET_UDP6			= 0x1011,											// AF_INET6, IPPROTO_UDP
	LCNET_BT				= 0X0003,											// BTHPROTO_RFCOMM(bluetooth)

	// io option
	LCNET_OPT_NONBLOCKING	= 126,												// FIONBIO
	LCNET_OPT_NAGLE_OFF		= 0x0001,											// TCP_NODELAY
	LCNET_OPT_REUSEADDR		= 0X0004,											// SO_REUSEADDR
	LCNET_OPT_LINGER		= 0x0080,											// SO_LINGER
	LCNET_OPT_DONTLINGER	= (UINT)(~LCNET_OPT_LINGER),
	LCNET_OPT_SNDTIMEO		= 0x1005,											// SO_SNDTIMEO
	LCNET_OPT_RCVTIMEO		= 0x1006,											// SO_RCVTIMEO
	LCNET_OPT_SNDBUF		= 0x1001,											// SO_SNDBUF
	LCNET_OPT_RCVBUF		= 0x1002,											// SO_RCVBUF

	// Host type
	LCNET_SERVER			= 0x0001,											// Server
	LCNET_CLIENT			= 0x0002,											// Clinet

	// io notify type
	LCNET_IO_NONE			= 0x0000,											// Non-blocking io
	LCNET_IO_SELECT			= 0x0001,											// select for linux and windows client or p2p
	LCNET_IO_ASYNC			= 0x0002,											// async select for windows client
	LCNET_IO_EVENT			= 0x0003,											// event select for windows client
	LCNET_IO_EPOLL			= 0x0005,											// epoll for linux server

	// for packet
	LCNET_PCK_VER_M			= 0x0012,
	LCNET_PCK_VER_N			= 0x0004,
	LCNET_PCK_MAX			= 0x0568,											// max segment size = 1384
	LCNET_PCK_HEAD			= 16,												// packet header size = 16
	LCNET_PCK_HEAD_WORD		= LCNET_PCK_HEAD/2,
	LCNET_PCK_SEND			= 2*(LCNET_PCK_MAX+LCNET_PCK_HEAD),					// max send buffer size
	LCNET_PCK_RECV			= 4*(LCNET_PCK_MAX+LCNET_PCK_HEAD),					// max send buffer size
	LCNET_PCK_NO_DATA		= 0,												// packet result for PopFront
	LCNET_PCK_BUFFERING		= 0,
	LCNET_PCK_OOM			= 0xFFFFFF01,										// Out of memory for PushBack
	LCNET_PCK_ERR_DATA		= 0xFFFFFF02,										// not define or read error

	// state and message.
	LCNET_ST_INVALID		= LC_EFAIL,
	LCNET_ST_CLOSE			= LC_FALSE,											// closed the socket
	LCNET_ST_ENABLE			= LC_TRUE,											// socket is enable
	LCNET_ST_LISTEN			= 0x0002,											// accept the new clent
	LCNET_ST_ACCEPT			= 0x0003,											// accept the new clent
	LCNET_ST_CONNECT		= 0x0004,											// connection to server
	LCNET_ST_SEND			= 0x0005,											// sending
	LCNET_ST_RECV			= 0x0006,											// receive
	LCNET_ST_USER			= 0x0040,											// user defined message


	// query and command for {Set|Get}Attrib
	LCNET_CMD_STATE			= 0x2021,											// Command: getting the state. It needs INT
	LCNET_CMD_MSG			= 0x2023,											// Command: get the number receive messages count(server) or saved packet size(client). get the message. it needs TLC_NETMSG
	LCNET_CMD_PAIR			= 0x2024,											// pair socket and user data for server. TLC_ARGS(socket, user pointer)
	LCNET_CMD_RMH_COUNT		= 0x2025,											// Remote host list count for server
	LCNET_CMD_RMH_LST		= 0x2026,											// get the Remote host with index.  TLC_ARGS(index, received TLCX_RMH* or TLCX_RMCP*)
	LCNET_CMD_RMH_SOCKET	= 0x2027,											// get the Remote host with socket.
	LCNET_EVENT_MSG			= 0x0400,
#if defined(_MSC_VER)
	LCNET_EVENT_MAX			= 64,
#else
	LCNET_EVENT_MAX			= 1024,
#endif
};

// Query function command for nonstandard operation
// common
#define LCX_QUERY_NET_CALLBACK		(char*)"Msg Callback"
#define LCX_QUERY_NET_UPDATE		(char*)"Update"

// for server
#define LCX_QUERY_NET_START			(char*)"Start"
#define LCX_QUERY_NET_STOP			(char*)"Stop"

// for client
#define LCX_QUERY_NET_CONNECT		(char*)"Connect"
#define LCX_QUERY_NET_DISCONNECT	(char*)"Disconnect"




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// network functions

INT  LcNet_Open();																// Network Device Open
INT  LcNet_Close();																// Network Device Close

INT  LcNet_BluetoothOpen	();													// Bluetooth adapter open
INT  LcNet_BluetoothClose	();													// Bluetooth adapter close
INT  LcNet_BluetoothPairList(char** addr, char** name, int lstIdx);				// retrive the Bluetooth pairing address, name. if address and name ar null, this function returns count of list. mininum size of address and name must be LC_IP_LEN, LC_RSC_NAME

INT  LcNet_SocketCreate		(LC_SOCKET* pScH, INT type);						// Create Socket. nagle off, linger(1,0), don't linger, reuseaddr
INT  LcNet_SocketClose		(LC_SOCKET* scH);									// Socket Close

INT  LcNet_SocketConnect	(LC_SOCKET scH, USHORT* uPort, BYTE* uIp
							 , INT protocol=LCNET_TCP4);						// Connection. uPort is uuid address for bluetooth
INT  LcNet_SocketBind		(LC_SOCKET scH, USHORT* uPort, BYTE* uIp=NULL
							 , INT protocol=LCNET_TCP4);						// Socket Binding.  uPort is uuid address for bluetooth. etc is extra output data like a mac address in bluetooth
INT  LcNet_SocketListen		(LC_SOCKET scH);									// Socket Listen
INT  LcNet_SocketAccept		(LC_SOCKET* pScH, LC_HANDLE addr
							 , INT* addLen, LC_SOCKET scListen);				// Accept

INT  LcNet_SocketSend		(LC_SOCKET scH, const char* Buf,INT len);			// Data(Buffer) Send (Write)
INT  LcNet_SocketRecv		(LC_SOCKET scH, char* Buf,INT len);					// Data(Buffer) Receive (Read)
INT  LcNet_SocketOptionSet	(LC_SOCKET scH, INT opt, INT v);					// set the socket option
INT  LcNet_SocketOptionDefault(LC_SOCKET scH);									// set the socket option to REUSEADDR, DONTLINGER, LINGER to be enable

INT  LcNet_HostName			(char* sHost, INT bufLen);							// get the host name.
INT  LcNet_IpAddress		(char* sIp, LC_SOCKET scH, INT bLocal=LC_FALSE);	// get the ip address from socket. if server bLocal = LC_TRUE
INT  LcNet_IpAddressFromAddr(char* sIp, LC_HANDLE sdH, INT addrLen);			// get the ip address from adddress_in
INT  LcNet_LocalIpAddress	(char** sIpList, INT w, INT af=0);					// Get Local Ip Addresses. w must be greater then 44 for IPv6. it reads w bytes each ip address. if failed return -1 else return the number of ip address
void LcNet_InetAddr32		(BYTE* uIp, char* sIp);								// 32-bit ip

INT  LcNet_LastGetErr		();
void LcNet_ErrFormat		(char* s, int size, INT er);						// FormatMessage or strerror
INT  LcNet_IsNotErr			(INT er);

INT  LcNet_ProcessorCount	();

INT  LcNet_Select			(INT nFdCnt, LC_HANDLE R, LC_HANDLE W, LC_HANDLE E
								, INT wait=LC_INFINITE);						// select read. wait time = millisecond

LC_HANDLE LcNet_ThreadCreate(LC_HANDLE pFunc, LC_HANDLE pParam = NULL
							, INT bSuspend = LC_FALSE, LC_HANDLE pId=NULL);
void LcNet_ThreadEnd		(UINT =0);
INT  LcNet_ThreadClose		(LC_HANDLE* v);

void LcNet_CloseHandle		(LC_HANDLE* v);
void LcNet_Sleep			(INT millisecond);


//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
//
struct TLC_SOCKET
{
	LC_SOCKET	sck_ac;															// socket
	INT			sck_ap;															// protocol: LCNET_TCP4, LCNET_UDP4,...
	INT			sck_ht;															// host type: LCNET_SERVER, LCNET_CLIENT
	INT			sck_nt;															// notify io type: LCNET_IO_SELECT, LCNET_IO_ASYNC, LCNET_IO_EVENT, LCNET_IO_IOCP, LCNET_EPOLL
	USHORT		sck_pt;															// port
	BYTE		sck_pi[LC_IP_LEN];												// ip address it must be big endian and number.
	LC_HANDLE	sck_tx[4];														// extended data
};


#if defined(_MSC_VER)
#pragma pack(push, 1)
#endif


struct TLC_NETMSG																// network sokcet message
{
	LC_SOCKET	nsm_ac;															// socket
	INT			nsm_cm;															// message type
	LC_HANDLE	nsm_np;															// Network id
	LC_HANDLE	nsm_xt;															// extended data

	TLC_NETMSG() : nsm_ac(0), nsm_cm(0), nsm_np(0), nsm_xt(0){}
	TLC_NETMSG(LC_SOCKET _a, INT _m, LC_HANDLE _n=0, LC_HANDLE _tx=0)
				  : nsm_ac(_a), nsm_cm(_m), nsm_np(_n), nsm_xt(_tx){}
};


//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
//
struct TLC_PACKET
{
	union { struct{
		WORD	bsp;															// bitseperator 0xcccc
		BYTE	pvj;															// packet major version
		BYTE	pvn;															// packet minor version
		WORD	crp;															// crypto level or type 0,1,2,4 etc
		WORD	len;															// packet length
		UINT	pro;															// packet type
		UINT	sqc;															// packet sequence
		char	sgm[LCNET_PCK_MAX];	};											// segment data 1384
		char	pck[LCNET_PCK_MAX+LCNET_PCK_HEAD];								// 1400
	};

	TLC_PACKET();
	TLC_PACKET(const char* src);
	void  		Reset();

	UINT  		Type();
	INT   		GetLength();
	INT   		GetLengthData();
	char* 		GetPack();
	char* 		GetData();

	void  		WriteBegin (INT type, INT sqc);									// init packet and write the packet sequence and type
	void  		WriteEnd   (INT crypto = 0);									// write the end mark
	void  		AddData    (LC_HANDLE data, INT len);							// add buffer to segment
	void  		CopySgm    (LC_HANDLE dst);										// copy data segment
	INT   		ReadData   (LC_HANDLE dst, INT offset, INT size);				// read from segment with offset
}

#if !defined(_MSC_VER)
	__attribute__((packed))
#endif
;

#if defined(_MSC_VER)
#pragma pack(pop)
#endif


//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
//
struct TLC_RING_BUF
{
	TLC_RING_BUF();
	~TLC_RING_BUF();

	void		Clear()		;
	INT			End()		;
	INT			Front()		;
	INT			GetStore()	;													// get stored byte
	INT			GetCount()	;													// get the packet count
	INT			PushBack(LC_HANDLE pSrc);										// add the complete packet
	INT			PopFront(LC_HANDLE pDst);										// get the packet
	INT			AddtoTail(INT iSize, LC_HANDLE buf);							// add the buffer to tail
protected:
	INT			F,L,W,S,N;														// Header(begin), Rear(Last), Width, Stored byte, stored packet count
	WORD		B[LCNET_PCK_RECV];
};


//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
//
struct TLC_RING_MSG
{
	TLC_RING_MSG();
	~TLC_RING_MSG();

	void		Clear()		;
	INT			End()		;
	INT			Front()		;
	INT			GetCount()	;													// stored message count
	INT			AddMsg(LC_SOCKET _a, INT _m, LC_HANDLE _n=0, LC_HANDLE _x=0);	// add the message
	INT			PushBack(LC_HANDLE pSrc);										// add the message
	INT			PopFront(LC_HANDLE pDst, INT bRemove=LC_TRUE);					// get the packet
protected:
	INT			F,L,W,S;														// Header(begin), Rear(Last), Width, Stored(count)
	TLC_NETMSG	M[LCNET_EVENT_MSG*8];											// Message buffer
};


//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// for linux epolling system
struct TLC_EPOLL
{
	INT			eh;																// epoll handle
	LC_HANDLE	ev;																// epoll event
	INT			en;																// watch count

	TLC_EPOLL();
	~TLC_EPOLL();

	INT			Create(INT cnt);
	void		Close();
	INT			Ctrl(INT fd, INT opt, INT io_t);
	INT			Wait(DWORD waitTime = LC_INFINITE);
	INT			GetFd(INT n=0);													// get the fd to be binded event
};


//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Synchronization for CRITICAL SECTION
struct TLC_SYN_CS
{
	LC_HANDLE	syn_m;

	TLC_SYN_CS();
	~TLC_SYN_CS();

	INT			Init();
	INT			Close();
	INT			Lock();
	INT			Unlock();
};


//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// sync for mutex
struct TLC_SYN_MTX
{
	LC_HANDLE	syn_m;
	LC_HANDLE	syn_d;

	TLC_SYN_MTX();
	~TLC_SYN_MTX();

	INT			Init();
	INT			Close();
	INT			Begin(int wait=-1);												// begin wait
	INT			End();															// release mutex
	INT			SetSignal();
};


//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// remote host for i/o

struct TLCX_RMH
{
	LC_SOCKET		rm_a;														// socket
	LC_HANDLE		rm_e;														// Socket Event Handle
	INT				rm_u;														// Is Use: LC_TRUE(new client or after connection success), LC_FALSE(before connection), LC_EFAIL(after disconnect or before deleting)
	TLC_RING_BUF	rm_r;														// ring buffer for receiving(read)
	TLC_RING_BUF	rm_w;														// ring buffer for sending(write)
	LC_HANDLE		rm_p;														// etc_0 comrade
	BYTE			rm_x[LC_RSC_NAME];											// etc_1 for sdH or Mac-address of bluetooth
	char			rm_n[LC_RSC_NAME];											// etc_2 name

	TLCX_RMH();
	TLCX_RMH(LC_SOCKET a, INT nUse
				, LC_HANDLE ev =NULL, const char* ip=NULL, const char* name=NULL);
	~TLCX_RMH();

	void Close();
};


DCL_INTERFACE ILCX_Net : public ILC_Base
{
	DCL_CLASS_DESTROYER(	ILCX_Net	);

	virtual INT		Query		(char* sCmd, LC_HANDLE)=0;						// execution
	virtual INT		Desc		(LC_HANDLE pDsc)=0;								// retrive the Object info pointer. It needs TLC_SOCKET*	pointer address!!!
	virtual INT		SetAttrib	(UINT cmd,LC_HANDLE)=0;							// write attribute value
	virtual INT		GetAttrib	(UINT cmd,LC_HANDLE)=0;							// read attribute value

	virtual INT		Send		(LC_SOCKET , TLC_PACKET*)=0;					// add to sending ring buffer
	virtual INT		Recv		(LC_SOCKET*, TLC_PACKET*)=0;					// dequeue from receiving buffer. if TLC_PACKET* is null then it returns the count packet for socket.
};

typedef ILCX_Net*	PLCX_NET;

INT LcxEnt_CreateNet(char* sCmd, PLCX_NET* pOut, PLC_ARGS arg);					// Create the network instance.

#endif

