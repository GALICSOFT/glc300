// GalicSoft Game Library Collection. Copyright(C) GALICSOFT. All rights reserved.
//
// GLC SDK Auxiliary Program
//
////////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER)
  #pragma once
#endif

#ifndef _LcAux_H_
#define _LcAux_H_

#include <LcType.h>
#include <LcBase.h>


// Utilty Macro

#ifndef SAFE_FREE
#define SAFE_FREE(p)					\
{ if(p) {								\
		free(p); (p) = NULL;			\
} }
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)					\
{ if(p) {								\
		delete (p);	(p) = NULL;			\
} }
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p)			\
{ if(p) {								\
		delete [] (p); (p) = NULL;		\
} }
#endif

#ifndef SAFE_DEL_ARR
#define SAFE_DEL_ARR(p)					\
{ if(p) {								\
		delete [] (p); (p) = NULL;		\
} }
#endif

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)					\
{ if(p) {								\
		(p)->Release();	(p) = NULL;		\
} }
#endif

#ifndef SAFE_FCLOSE
#define SAFE_FCLOSE(p)					\
{ if(p) {								\
		fclose(p);	(p) = NULL;			\
} }
#endif

#ifndef SAFE_NEWCREATE1
#define SAFE_NEWCREATE1(p, CLASSTYPE, P1)						\
{ if(!(p)) {													\
		p = new CLASSTYPE;										\
		if(!(p)) {	return -1;	}								\
																\
		if(LC_FAILED(((CLASSTYPE *)p)->Create(P1)))	{			\
			delete p; p=(NULL); return -1;						\
		}														\
} }
#endif

#ifndef SAFE_NEWCREATE2
#define SAFE_NEWCREATE2(p, CLASSTYPE, P1, P2)					\
{ if(!(p)) {													\
		p = new CLASSTYPE;										\
		if(!(p)) {	return -1;	}								\
																\
		if(LC_FAILED(((CLASSTYPE *)p)->Create(P1, P2)))	{		\
			delete p; p=(NULL); return -1;						\
		}														\
} }
#endif

#ifndef SAFE_NEWCREATE3
#define SAFE_NEWCREATE3(p, CLASSTYPE, P1, P2, P3)				\
{ if(!(p)) {													\
		p = new CLASSTYPE;										\
		if(!(p)) {	return -1;	}								\
																\
		if(LC_FAILED(((CLASSTYPE *)p)->Create(P1, P2, P3))) {	\
			delete p; p=(NULL); return -1;						\
		}														\
} }
#endif

#ifndef SAFE_NEWCREATE4
#define SAFE_NEWCREATE4(p, CLASSTYPE, P1, P2, P3, P4)			\
{ if(!(p)) {													\
		p = new CLASSTYPE;										\
		if(!(p)) {	return -1;	}								\
																\
		if(LC_FAILED(((CLASSTYPE *)p)->Create(P1,P2,P3,P4))) {	\
			delete p; p=(NULL); return -1;						\
		}														\
} }
#endif


// Vector delete all in list
#define SAFE_DEL_LST(p)											\
{																\
	if( !p.empty() ) {											\
		int __nLst##p = p.size();								\
		for(int __n##p=0; __n##p < __nLst##p ; ++__n##p ) {		\
			if( p[ __n##p ]	)									\
				delete p[ __n##p ];								\
																\
			p[ __n##p ] = NULL;									\
		}														\
		p.clear();												\
	}															\
}

// element of vector release all in list
#define SAFE_RELEASE_LST(p)										\
{																\
	if( !p.empty() ) {											\
		int __nLst##p = p.size();								\
		for(int __n##p=0; __n##p < __nLst##p ; ++__n##p ) {		\
			if( p[ __n##p ]	)									\
				p[ __n##p ]->Release();							\
																\
			p[ __n##p ] = NULL;									\
		}														\
		p.clear();												\
	}															\
}

#ifndef SAFE_FRAMEMOVE
#define SAFE_FRAMEMOVE(p){ if(p) (p)->FrameMove(); }
#endif
#ifndef SAFE_UPDATE
#define SAFE_UPDATE(p)   { if(p) (p)->Update();	   }
#endif
#ifndef SAFE_RENDER
#define SAFE_RENDER(p)   { if(p) (p)->Render();    }
#endif




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// LC Time and Etc...

INT   LcAux_tzset();
INT   LcAux_InitTime();															// set up the start time
DINT  LcAux_TimeGetTime(INT bAbsolute = LC_FALSE);								// middle resolution(1ms) or hi resolution(1/1000ms) timer.
DINT  LcAux_SystemDateTime(char* str_date=NULL, char* str_time=NULL
						,  int* _year=NULL, int* _mon=NULL, int* _day=NULL
						,  int* _hh  =NULL, int* _mm =NULL, int* _ss=NULL);		// System Absolute time, string date, and time. string must be greater then 32bytes




DCL_INTERFACE ILC_Timer : public ILC_Base
{
	virtual INT			Set         (UINT beginTime								// begin time (1/1000s)
									,UINT interval								// timer interval
									,UINT totalCount) =0;						// total count

	virtual INT			Start       () =0;										// timer start
	virtual INT			Stop        () =0;										// timer stop. if the timer count is over the total count then it will be stop automatically.
	virtual INT			Reset       () =0;										// timer reset
	virtual UINT		Count       () =0;										// get the current count
	virtual UINT		RemainCount () =0;										// get the remained count
	virtual LC_HANDLE	UserData    () =0;										// get the user data
};


typedef ILC_Timer*	PLC_TIMER;


INT LcAux_TimerCreate(char*			sCmd
					, PLC_TIMER*	pOut										// instance.
					, UINT			beginTime									// first time event.
					, UINT			interval									// timer interval.
					, UINT			count										// timer count. 0xFFFFFFFF : infinite
					, PLC_MSGPRC	pPrc										// timer message listener. it must be exist.
					, LC_HANDLE		pUsrData = NULL								// user defind data pointer.
					);




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// LC Etc...

INT	   LcAux_Sleep          ( UINT Milliseconds);								// Sleep
INT    LcAux_RandSeedSet    ( DINT dSeed);										// srand( time() ) ==> LcAux_RandSeedSet(0);
INT    LcAux_Rand           ( INT _min, INT _max);								// call _min + rand() %(_max-_min +1)

INT    LcAux_ResourcePath   ( char* Out,const char* sPathIn);					// make up the resource path from dest device for iphone, android, and bada. Output needs 260bytes.
INT    LcAux_ResourceFind   ( char* dstPath, const char* srcPath				// replace and find resource. same to LcStr_ReplacePath+ LcAux_ResourcePath. drive, dir, fname, or ext from source path.
							, const char* drive, const char* dir				// if arguments drive~fname are NULL then it does not change.
							, const char* fname, const char* ext);				// if you want get rid of dir ~ext then you have to use [""] string.

const char* LcAux_TempFolder();													// Iphone: Get Temporary folder. it needs 260bytes
const char* LcAux_AppFolder(char* apkName=NULL);								// to be able to read and write. Iphone: return the Document folder. Android: the get method App Foler when the apk Name is NULL.

const char* LcAux_IphoneRscPath();												// get the iphone resource path
const char* LcAux_AndroidApkFile(char* apkName=NULL);							// set/get android apk file. the get method Apk File when the apk Name is NULL

INT  LcAux_GetCurrentDir(char* dir, INT MaxLength);								// getcwd()
INT  LcAux_SetCurrentDir(char* dir);											// chdir()
INT  LcAux_SetCurrentDirWithCommandLine();										// Set Current directory with command line in Microsoft Windows




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// LC Memory

LC_HANDLE LcMem_Alloc    (INT size, INT initVal=0x00, INT byteS= 1);			// malloc, memset(initVal), byte segment multiple 1, 2, 4, 8
LC_HANDLE LcMem_Realloc  (LC_HANDLE org, INT size_dst							// realloc(org,size_dst) + memset(dst+size_org, initVal, size_dst-size_org)
						, INT size_org, INT initVal=0x00);
LC_HANDLE LcMem_AllocCopy(LC_HANDLE src, INT size
						, INT initVal=0x00, INT byteS=1);						// LcMem_Alloc + copy
void      LcMem_Free     (LC_HANDLE* v);										// free(*v) + *v = NULL;




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// LC String

LC_INLINE INT LcStr_tolower(INT c);												// Redefine tolower()
LC_INLINE INT LcStr_toupper(INT c);												// Redefine toupper()

void  LcStr_toLower(char* str);													// string to lower()
void  LcStr_toUpper(char* str);													// string to upper()

// little endian string, code conversion
// conversion string. len is source code counter.
INT   LcStr_StringCp949ToUni (MCHAR* sDst, const char*  sSrc, INT len=-1
							, const char* nl=(char*)"\r\n");					// string cp949     -> unicode 2, null characters

INT   LcStr_StringUniToCp949 (char*  sDst, const MCHAR* sSrc, INT len=-1);		// string unicode 2 -> cp949
INT   LcStr_StringUtf8ToUni  (MCHAR* sDst, const char*  sSrc, INT len=-1);		// string utf8      -> unicode 2
INT   LcStr_StringUniToUtf8  (char*  sDst, const MCHAR* sSrc, INT len=-1);		// string unicode 2 -> utf8
INT   LcStr_StringCp949ToUtf8(char*  sDst, const char*  sSrc, INT len=-1
							, const char* nl=(char*)"\r\n");					// string cp949     -> utf8

INT   LcStr_StringUtf8ToCp949(char*  sDst, const char*  sSrc, INT len=-1);		// string utf8      -> cp949

// one character conversion
INT   LcStr_CodeCp949ToUni   (MCHAR* sDst, const char*  sSrc);				// code cp949     -> unicode 2
INT   LcStr_CodeUniToCp949   (char*  sDst, const MCHAR* sSrc);				// code unicode 2 -> cp949
INT   LcStr_CodeUtf8ToUni    (MCHAR* sDst, const char*  sSrc);				// code utf8      -> unicode 2
INT   LcStr_CodeUniToUtf8    (char*  sDst, const MCHAR* sSrc);				// code unicode 2 -> utf8
INT   LcStr_CodeCp949ToUtf8  (char*  sDst, const char*  sSrc);				// code cp949     -> utf8
INT   LcStr_CodeUtf8ToCp949  (char*  sDst, const char*  sSrc);				// code utf8      -> cp949

INT   LcStr_AnsiLen (const char* str);											// get the word(2byte) length on multibyte string.
INT   LcStr_WCSLen  (const MCHAR* wstr);										// wcslen() is not appropriate. and windows system and linux so, we define new function
INT   LcStr_Strcpy  (char* dest, const char* src, INT opt=0);					// string copy. opt<0: to lower character, opt>0: to upper character. opt=0: strcpy()
INT   LcStr_Strcpy_s(char* dest, int dest_size, const char* src, INT opt=0);	// string copy with limited destination buffer size. opt<0: to lower character, opt>0: to upper character. opt=0: strcpy_s()
INT   LcStr_Format  (char* dest, const char* format,...);						// setup the string with the format
INT   LcStr_Strcmp	(const char* s1,const char* s2);							// Redefine strcmp()
INT   LcStr_Strncmp	(const char* s1,const char* s2, INT size);					// Redefine strncmp()
INT   LcStr_Stricmp (const char* s1,const char* s2);							// Redefine _stricmp() or strcasecmp()
INT   LcStr_Strnicmp(const char* s1,const char* s2, INT size);					// Redefine _strnicmp() or strncasecmp()
INT   LcStr_Replace (char* dst, const char* src
					, const char* s_tgt, const char* rep);						// string copy with s_tgt to rep.
void  LcStr_Replace (char* str, int dst_chr, char* target);						// it replaces the characters(target) to destination character(dst_chr) in given string(str).
INT   LcStr_Strtok  (char** dst, int block										// same to strtok. return count of tokens. but not recomended. to use the TLC_STRTOK.
					, int nList, char* src, const char* sep);					// dst must be char[nList][block].
char* LcStr_AnsiSubString(const char* src, INT _begin=0, INT _end=-1);			// get the substring [_begin,_end]with index of 2byte ansi string. this function uses the shard memory,so you have to lock in multi threading.

void  LcStr_SplitPath(															// Redefine _splitpath()
					  const char *path											// Input Path
					,	char *drive												// split drive Need 260 bytes
					,	char *dir												// split directory
					,	char *fname												// split file name
					,	char *ext												// split extension
					);

INT LcStr_MakePath(char* dstPath, char* drive, char* dir						// same to make path
					, char* fname, char* ext);
INT LcStr_ReplacePath(char* dstPath, const char* srcPath						// replace drive, dir, fname, or ext from source path.
					, const char* drive, const char* dir						// if arguments drive~fname are NULL then it does not change.
					, const char* fname, const char* ext);						// if you want get rid of dir ~ext then you have to use [""] string.

void  LcStr_Trim     (char* s,const char* w=(char*)" \t\r\n");					// Left + Right Trim
void  LcStr_TrimLeft (char* s,const char* w=(char*)" \t\r\n");					// Left Trim
void  LcStr_TrimRight(char* s,const char* w=(char*)" \t\r\n");					// Right Trim
INT   LcStr_Quot     (char* Dst,const char* Src);								// retrn string list and number with "{ }" block
INT   LcStr_StringToUuid(LC_HANDLE pDst, const char* strUuid);					// get the guid number from string


struct TLC_STRING
{
	void		Release();														// free the buffer.

	INT			Len();															// get the stored string. length: -1 is no stored string
	const char*	Str() const;													// get the stored string. NULLis no stored string
	INT			CopyFrom(const char* source);									// copy the string to object
	INT			CopyTo(char* dest, INT size);									// copy the stored string to dest buffer with given length
	INT			Replace(INT target, INT dest, INT idx=-1);						// replace the target character to dest. -1 is all characters in string. if idx(index) is not -1 then target argument will not be used.
	INT			Replace(const char* target, const char* dest);
	INT			Mid(char* dest, INT nFirst, INT nCount);
	INT			Tokenize(const char* src, const char * delim);
	void		ToUpper();
	void		ToLower();
	INT			Reverse();
	INT			Insert(INT n, char* s);
	INT			Remove(const char* s);
	INT			Format(const char* format, ...);
	INT			Compare(const char* s, INT bCapitcal= LC_FALSE) const;
	void		Add(const char*);

	TLC_STRING&	Trim (const char *whiteSpace=(char*)" \t\r\n");
	TLC_STRING&	TrimL(const char *whiteSpace=(char*)" \t\r\n");
	TLC_STRING&	TrimR(const char *whiteSpace=(char*)" \t\r\n");

	INT operator[](int n);
	operator char* ();
	operator const char* () const;

	TLC_STRING& operator=(char* s);
	TLC_STRING& operator=(const char* s);
	TLC_STRING& operator+=(const char* s);

	bool operator==(const TLC_STRING& r);
	bool operator!=(const TLC_STRING& r);
	bool operator< (const TLC_STRING& r);
	bool operator> (const TLC_STRING& r);
	bool operator<=(const TLC_STRING& r);
	bool operator>=(const TLC_STRING& r);

	bool operator==(const char* s);
	bool operator!=(const char* s);
	bool operator< (const char* s);
	bool operator> (const char* s);
	bool operator<=(const char* s);
	bool operator>=(const char* s);

	friend bool operator==(const char* s, const TLC_STRING& r);
	friend bool operator!=(const char* s, const TLC_STRING& r);
	friend bool operator< (const char* s, const TLC_STRING& r);
	friend bool operator> (const char* s, const TLC_STRING& r);
	friend bool operator<=(const char* s, const TLC_STRING& r);
	friend bool operator>=(const char* s, const TLC_STRING& r);

	TLC_STRING();
	TLC_STRING(const char* s);
	TLC_STRING(const TLC_STRING& r);

	INT	m_ls;	INT	m_lb;		char*	m_sb;									// length of the string, length of the buffer, string buffer
};


struct TLC_STRTOK																// tokenize the string. it does not use static memory
{
	void		Release();														// free the buffer

	INT			Len();															// get the strin block with index
	const char*	GetStr(INT idx) const;											// get the stored string. NULLis no stored string
	INT			Tokenize(const char* src, const char* sep);

	TLC_STRTOK();
	TLC_STRTOK(const TLC_STRTOK& r);
	~TLC_STRTOK();

	INT	m_cnt;		char**	m_sb;												// string buffer count, string buffers
};




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// LC File

struct TLC_FINDDATA
{
    UINT	attrib;
    LONG	time_create;														// -1 for FAT file systems
    LONG	time_access;														// -1 for FAT file systems
    LONG	time_write;
    ULONG	size;
    char	name[LC_MAX_PATH2];
};


struct TLC_FINF
{
	INT		nType;																// Folder: 0x10, File: 0x20
	LONG	lDate;																// Make Date
	LONG	lBuf;																// Length of File Buffer
	LONG	lBufB;																// Start Buffer in Merge File
	LONG	lt1;																// temp1
	LONG	lt2;																// temp2
	LONG	lt3;																// temp3
	LONG	lt4;																// temp4
	LONG	iname;																// Length of File Name
	char*	name;																// File Name

	TLC_FINF*	pNext;
};


INT   LcFile_Exist(char* file);													// Is File Exist? LC_OK, LC_EFAIL.

int   LcFile_Info(  const char *sFile											// file name
				  , unsigned long* size											// file size
				  , unsigned long* time_m										// modified time
				  , unsigned long* time_c);										// created time.  fi call failed -1.

UINT  LcFile_Attribute(const char* sPath);										// get the file attributes
L_PTR LcFile_FindFirst(TLC_FINDDATA* pFindData, const char* sSearPath);			// Redefine _findfirst()
INT   LcFile_FindNext(L_PTR handle, TLC_FINDDATA* pFindData);					// Redefine _findnext()
INT   LcFile_FindClose(L_PTR handle);											// Redefine _findClose()

void  LcFile_GatherAllFiles(TLC_FINF** pOut, const char* sStartRoot);
void  LcFile_GatherFree(TLC_FINF** pIn);

INT   LcFile_mkdir(const char* sFolder, UINT mod= 0777);						// Redefine mkdir()
INT   LcFile_rmdir(const char* sFolder);										// Redefine rmdir()

void  LcFile_SimpleStrDateTime(char* pOut, char* sYear, char* sMon, char* sDay
								, char* sTime, DINT lTime);
INT   LcFile_Finds(TLC_FINF** pOut, const char* sPath, const char* sFile);		// Find File List
INT   LcFile_FindSameExt(TLC_FINF** pOut, const char* sPath, const char* sExt);	// Find Same Extension File List
INT   LcFile_XcopyFileToFile(char* destfile, char* srcfile);					// File Copy src to dest. return the copyed bytes. failed -1
INT   LcFile_XcopyBufferToFile(char* destfile, BYTE* buf, INT size);			// Buffer Copy to dest file. return the copyed bytes. failed -1


DCL_INTERFACE ILC_File : public ILC_Base
{
	DCL_CLASS_DESTROYER(	ILC_File	);

	virtual INT		ReadByte (void*  buf, INT  size, INT count) =0;				// fread. if eof then return LC_EFAIL
	virtual INT		ReadBytes(BYTE** buf, INT* size) =0;						// read file data.
	virtual INT		WriteByte(void*  buf, INT  size, INT count) =0;				// fwrite
	virtual INT		ReadLine (void*  buf, INT  size) =0;						// fgets
	virtual INT		Seek     (INT offset, INT  origin) =0;						// fseek

	virtual INT		Size() =0;													// return the size of buffer or file
	virtual INT		Mode() =0;													// return the mode. read: 0x1, write: 0x2, rw: 0x3
	virtual INT		Tell() =0;													// return the current file pointer position
	virtual INT		Eof () =0;													// is End of File?
};

typedef ILC_File*	PLC_FILE;

INT LcFile_CreateFile(char*     sCmd											// Command. Low level file open
                    , PLC_FILE* pOut											// Output instance
                    , LC_HANDLE sFile											// file name or buffer address
                    , INT       size  = 0										// if it'll be used to file size must be zero. buffer then size is greather than zero
                    , char*     mode  ="r"										// read write mode. w, r, w+, r+ rt, wt, rb, wb. not support the append 'a' or 'a+'
                    );

INT LcFile_Open		(  char*       sCmd											// Command. Simple file open. this function will read the data from file on windows, ios systems or buffer(apk), folder on android
					 , PLC_FILE*   pOut											// Output instance. if the file name has "save" then the file will be copied to saved data folder on android system.
					 , const char* sFile										// file name
					 , char*       sMode);										// r/w mode.




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// registry or ini file for save the game data.


INT LcFile_RegOpen(UDINT* hKey, char* file, LONG key = 0x80000001);				// registry key open
INT LcFile_RegClose(UDINT hKey);												// registry close
INT LcFile_RegDelete(char* file, LONG key = 0x80000001);						// registry delete
INT LcFile_RegRead(UDINT hKey, char* name, INT* type, void* data);				// read the data from register
INT LcFile_RegWrite(UDINT hKey, char* name, INT type, void* data, INT size);	// write the data from register




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// zlib 1.2.5 and minizip Zip Api Interface

enum
{
	LZIP_NO_COMPRESS      =    0,
	LZIP_BEST_SPEED       =    1,
	LZIP_BEST_COMPRESS    =    9,
	LZIP_DEFAULT_COMPRESS = (-1),

	LZIP_OK               =    0,
	LZIP_STREAM_END       =    1,
	LZIP_NEED_DICT        =    2,
	LZIP_ERRNO            = (-1),
	LZIP_STREAM_ERROR     = (-2),
	LZIP_DATA_ERROR       = (-3),
	LZIP_MEM_ERROR        = (-4),
	LZIP_BUF_ERROR        = (-5),
	LZIP_VERSION_ERROR    = (-6),
};


// compressed buffer =
//    total size(unsigned long: zipped size + unsigned long*2 )
//    + orginal size(unsigned long) + zip data(unsigned byte*)


INT Lzip_CompressBufferToBuffer(BYTE**       OutZip								// output zip data with source size and zip size
							  , const BYTE*  Src								// input src data
							  , const ULONG  SrcSize							// input src size
							  , INT level = LZIP_BEST_SPEED						// zip level
							  );


INT Lzip_CompressToBufferFromFile(BYTE**     OutZip								// output zip data
							   , const char* sOrg								// source file name
							   , INT level=LZIP_BEST_SPEED						// zip level
							   );


INT Lzip_CompressFileToFile(char* sZip											// Output Compress File Name
						  , char* sOrg											// Source File Name
							);


INT Lzip_DeCompressBufferToBuffer(BYTE** OutUnzip								// output unzip data with output size
								, BYTE* InputZiped								// Input zipped data
								);

INT Lzip_DeCompressBufferToBuffer(BYTE**  OutUnzip								// output unzip data with no output size
								, ULONG* OutSize								// input src size
								, BYTE*  InputZiped								// Input zipped data
								);


INT Lzip_DeCompressToBufferFromFile(  BYTE**      OutUnZip						// output unzip data
									, ULONG*      OutSize						// input src size
									, char*       sOrgFile						// original file name
									, const char* sZip							// zipped file name
									);

INT Lzip_DeCompressFileToFile ( char* sOrg										// Output DeCompress File Name
							  , const char* sZip								// zipped File Name
							  );

int Lzip_SimpleUnZip		(  BYTE**      bufOut								// DeCompress Data
							 , ULONG*      lsize								// DeCompress Data Size
							 , const char* ZipFile								// Compressed zip file
							 , const char* searchName							// to finding file Name
							 );

INT Lzip_AssetBuffer		(													// unzip from zip file by finding name. you need to call the free()...
							   BYTE** bufOut									// DeCompress Data
							 , ULONG* lsize										// DeCompress Data Size
							 , const char* ZipFile								// Compressed zip file
							 , const char* FindingName							// to finding file Name
							 , INT bIgnorePath = 0								// Ignore the path in zip file
							 );




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// GLC Log for Debugging

void  LcLog_Out(INT nOp, const char* fmt,...);									// print the log
void  LcLog_OutI(const char* fmt, ...);											// This and LcLog_Out(LC_LOG_INFO) are the same function.
void  LcLog_OutW(const char* fmt, ...);											// This and LcLog_Out(LC_LOG_WARNING) are the same function.
void  LcLog_OutE(const char* fmt, ...);											// This and LcLog_Out(LC_LOG_ERROR) are the same function.

// setup the log environment
void  LcLog_SetOp(INT v);														// setup the ouput meethod type of Log message
void  LcLog_SetSate(INT v);														// Activity: LC_LOG_ENABLE(LC_TRUE), LC_LOG_DISABLE(LC_FALSE)
INT   LcLog_GetState();															// Log activity state
INT   LcLog_ErrCount();															// get the error(LC_LOG_ERROR) log count
INT   LcLog_CloseFile();														// close log file.

#define LOGI	LcLog_OutI
#define LOGW	LcLog_OutW
#define LOGE	LcLog_OutE




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// LC Random
class TLC_RAND
{
public:
	TLC_RAND();																	// Sets the random starting point with current time.
	TLC_RAND(DINT v);															// Sets the random starting point with the argument value.

	DOUBLE	NextDouble();														// random double number in [0, 1.0 ]
	INT		Next();																// random int number in [0, 32767( RAND_MAX ) ]
	INT		Next(INT   _max);													// random int number in [0, _max]
	INT		Next(INT   _min, INT   _max);										// random int number in [_min,_max]
};




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// for event structure

struct TLC_EVENT
{
	LC_HANDLE	e_o;															// event object
	UINT		e_c;															// clazz
	UINT		e_m;															// message
	TLC_VAR		e_v;															// event value:

	TLC_EVENT 	(LC_HANDLE owner=0, INT clzz=0, INT msg=0);
	TLC_EVENT 	(const TLC_EVENT& v);
	TLC_EVENT&	operator= (const TLC_EVENT& v);

	void	Set     (LC_HANDLE owner, INT clzz, INT msg);						// owner, clzz, message
	void	Owner   (LC_HANDLE owner);
	void	Type    (UINT c);
	void	Message (UINT m);
	void	Value   (const TLC_VAR& v);
	void	Value   (const TLC_VAR* v);
	void	Clear	();
};
typedef TLC_EVENT*	PLC_EVENT;




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// LC Tree(Node) Structure.
//
//	parent
//	ก่ก้         ก่             ก่             ก่
//	chld <--> sibling1 <--> sibling2 <--> sibling3

template<class T>
class TLC_NODE
{
protected:
	TLC_NODE<T>* P;																// parent
	TLC_NODE<T>* C;																// child
	TLC_NODE<T>* B;																// previous
	TLC_NODE<T>* N;																// next

	T*           A;																// attribute

public:
	TLC_NODE();
	TLC_NODE(TLC_NODE<T>*);
	virtual ~TLC_NODE();


	T*	 GetAttrib()		{	return A;	}
	void SetAttrib(const T& a){	A = (T*)&a;	}
	void SetAttrib(T* a)	{	A = (T*)a;	}
	void SetAttrib(INT a)	{	A = (T*)a;	}


	////////////////////////////////////////////////////////////////////////////
	// Node Iteration

	INT HasParent()		;														// Has parent?
	INT HasNotParent()	;														// Has no parent?
	INT HasChild()		;														// Has child?
	INT HasNotChild()	;														// Has no child?
	INT IsSiblingF()	;														// Am I first child?

	INT IsSiblingL()	;														// Am I last child?
	INT IsRoot()		;														// Am I root?
	INT IsChild()		;														// Am I Child?

	TLC_NODE<T>* GetSiblingF();													// find first node from sibling list
	TLC_NODE<T>* GetSiblingL();													// find last node from sibling list
	TLC_NODE<T>* FindRoot()   ;													// find root node

	void AttachTo(TLC_NODE<T>* Parent);											// set the parent node. (I'm a child node)
	void Attach(TLC_NODE<T>* Child);											// attach the child node. (I'm parent node)
	void Detach();																// detach
	INT CountNodes();															// count node
};

typedef TLC_NODE<PLC_OBJECT >	VLC_OBJECT;




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
//Implementation of TLC_NODE

template<class T> TLC_NODE<T>::TLC_NODE() : P(0), C(0), B(0), N(0){}


template<class T> TLC_NODE<T>::~TLC_NODE()
{
	Detach();																	// detach from parent node
	if(0 == C)
		return;

	while(C)
		C->Detach();															// if has child
}


template<class T> INT TLC_NODE<T>::HasParent()	 {	return (0 != P);	}		// Has parent?
template<class T> INT TLC_NODE<T>::HasNotParent(){	return (0 == P);	}		// Has no parent?
template<class T> INT TLC_NODE<T>::HasChild()	 {	return (0 != C);	}		// Has child?
template<class T> INT TLC_NODE<T>::HasNotChild(){	return (0 == C);	}		// Has no child?
template<class T> INT TLC_NODE<T>::IsSiblingF() {	return (P&&P->C==this);}	// Am I first child?

template<class T> INT TLC_NODE<T>::IsSiblingL() {	return (P && 0 == N);	}	// Am I last child?
template<class T> INT TLC_NODE<T>::IsRoot()		{	return (0 == P);		}	// Am I root?
template<class T> INT TLC_NODE<T>::IsChild()	{	return (0 != P);		}	// Am I Child?

template<class T> TLC_NODE<T>* TLC_NODE<T>::GetSiblingF(){return (B)? B->GetSiblingF():this;}	// find first node from sibling list
template<class T> TLC_NODE<T>* TLC_NODE<T>::GetSiblingL(){return (N)? N->GetSiblingL():this;}	// find last node from sibling list
template<class T> TLC_NODE<T>* TLC_NODE<T>::FindRoot()   {return (P)? P->FindRoot()   :this;}	// find root node

template<class T> void TLC_NODE<T>::AttachTo(TLC_NODE<T>* Parent)				 // set the parent node. (I'm a child node)
{
	TLC_NODE<T>* pParentChild = NULL;
	TLC_NODE<T>* pSiblingLast = NULL;

	if(P)
		Detach();

	P = Parent;																	// set the parent node
	pParentChild =	P->C;

	if(!P->C)
	{
		P->C = this;
	}
	else
	{
		pSiblingLast = pParentChild->GetSiblingL();
		B = pSiblingLast;
		pSiblingLast->N = this;
	}
}

template<class T> void TLC_NODE<T>::Attach(TLC_NODE<T>* Child)					// attach the child node. (I'm parent node)
{
	TLC_NODE<T>* pSiblingLast = NULL;

	if(Child->HasParent())
		Child->Detach();

	Child->P = this;
	if(C)
	{
		pSiblingLast = C->GetSiblingL();
		pSiblingLast->N = Child;
		Child->B = pSiblingLast;
	}
	else
	{
		C = Child;
	}
}

template<class T> void TLC_NODE<T>::Detach()
{
	if(P && P->C == this)
	{
		if(N)
		{
			P->C = N;
			P->C->B = 0;
		}
		else
			P->C = 0;
	}

	if(B) B->N = N;
	if(N) N->B = B;

	P = 0; B = 0; N = 0;
}

template<class T> INT TLC_NODE<T>::CountNodes()
{
	if(C)
		return C->CountNodes() + 1;

	return 1;
}


//Other auxiliary functions
LC_INLINE INT lc_multi4(INT v){ return (4 * int((v+7)/4) ); }

#endif

