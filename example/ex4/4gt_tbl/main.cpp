// Implementation of the CMain class.
//
////////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER) && _MSC_VER >= 1200
  #pragma warning( disable : 4996)

#endif


#if defined(_MSC_VER)
  #pragma comment(linker, "/subsystem:console")
  #pragma comment(linker, "/NODEFAULTLIB:library")

#if defined(_DEBUG)
  #pragma comment(lib, "lgpwn_a30_.lib")
  #pragma comment(lib, "lgpwn_b30_.lib")
  #pragma comment(lib, "lgpwn_c30_.lib")
  #pragma comment(lib, "lgpwn_d30_.lib")
  #pragma comment(lib, "lgpwn_i30_.lib")
  #pragma comment(lib, "lgpwn_n30_.lib")
  #pragma comment(lib, "lgpwn_e30_.lib")
#else

  #pragma comment(lib, "lgpwn_a30.lib")
  #pragma comment(lib, "lgpwn_b30.lib")
  #pragma comment(lib, "lgpwn_c30.lib")
  #pragma comment(lib, "lgpwn_d30.lib")
  #pragma comment(lib, "lgpwn_i30.lib")
  #pragma comment(lib, "lgpwn_n30.lib")
  #pragma comment(lib, "lgpwn_e30.lib")
#endif

  #pragma comment(lib, "OpenGL32.lib")
  #pragma comment(lib, "Imm32.lib")
  #pragma comment(lib, "winmm.lib")
  #pragma comment(lib, "dxguid.lib")
  #pragma comment(lib, "ws2_32.lib")
  #pragma comment(lib, "comctl32.lib")

  #pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' \
						 version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' \
                         language='*'\"")
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
#include <LcAxx.h>

#include <LcStdev.h>
#include <LcxEntity.h>
#include <LcxMedia.h>
#include <LctEntity.h>


PLC_OBJECT TblMdlCreate(char* path, char* name, PLC_ARGS pOpt)
{
	printf("%s%s", path, name);

	// test ..
	char* pObj = (char*)LcMem_Alloc(512);
	sprintf( pObj, "TblMdlCreate:: %s%s", path, name);
	
	return (PLC_OBJECT)pObj;
}


void TblMdlRelease(PLC_OBJECT* pRsc, PLC_ARGS pOpt)
{
	char**	pObj = (char**)pRsc;
	SAFE_FREE(*pObj);

	*pRsc = NULL;
}


INT TblMdlCmp(PLC_ARGS pArgs, LC_HANDLE _searchName)
{
	INT hr = 0;
	LC_HANDLE	p0		= pArgs->_0;
	LC_HANDLE	p1		= pArgs->_1;
	LC_HANDLE	p2		= pArgs->_2;
	LC_HANDLE	p3		= pArgs->_3;

	char*	tbM			= (char*)p0;
	char*	tbP			= (char*)p1;
	char*	tbS			= (char*)p2;
	char*	recName		= (char*)p3;
	char*	searchName	= (char*)_searchName;


	char sMedia[LC_MAX_PATH]={0};
	char sFile [LC_MAX_PATH]={0};

	sprintf(sFile, "%s%s", tbP, recName);
	LcStr_ReplacePath(sMedia, (const char*)sFile, NULL, NULL, NULL, "");

	hr = LcStr_Strcmp(sMedia, searchName);

	return hr;
}


//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8

INT TblMdlLoad(PLC_ARGS pArg)
{
	INT			hr		= 0;
	TLC_ARGS	args	;

	LC_HANDLE	p0		= pArg->_0;
	LC_HANDLE	p1		= pArg->_1;

	PLCX_TBL	pTbl	= (PLCX_TBL)p0;
	char*		sFile	= (char*   )p1;

	INT			nMst	= -1, nSub = -1, nRec = -1;

	TLC_SKEY sParse[] =
	{
		{	"Version"	,	strlen("Version"	)	},		//0
		{	"Rec*"		,	strlen("Rec*"		)	},		//1
		{	"NumMst"	,	strlen("NumMst"		)	},		//2
		{	"TbMst"		,	strlen("TbMst"		)	},		//3
		{	"MstName"	,	strlen("MstName"	)	},		//4

		{	"NumSub"	,	strlen("NumSub"		)	},		//5
		{	"TbSub"		,	strlen("TbSub"		)	},		//6
		{	"NumRec"	,	strlen("NumRec"		)	},		//7
		{	"SubName"	,	strlen("SubName"	)	},		//8
		{	"SubPath"	,	strlen("SubPath"	)	},		//9
	};

	enum
	{
		LOAD_TBL_VER	= 0,
		LOAD_TBL_REC	,
		LOAD_TBL_MNUM	,
		LOAD_TBL_MST	,
		LOAD_TBL_MNAME	,

		LOAD_TBL_SNUM	,
		LOAD_TBL_SUB	,
		LOAD_TBL_RNUM	,
		LOAD_TBL_SNAME	,
		LOAD_TBL_SPATH	,
	};


	char	sLine[LC_MAX_PARSE_LINE+4]={0};

	PLC_FILE	fp = NULL;
	hr = LcFile_Open(NULL, &fp, sFile, "r");
	if(NULL == fp)
		return LC_CANNT_FIND_RESOURCE;



	pTbl->SetAttrib(LCXT_ITK_TBL_NAME, sFile);

	
#define	READ_TEXT_LINE(index)	\
	if( 0 == LcStr_Strnicmp(sLine, sParse[index].sKey, sParse[index].iKey) )
	
	while( !fp->Eof() )
	{
		fp->ReadLine(sLine, LC_MAX_PARSE_LINE);
		LcStr_Trim(sLine);

		READ_TEXT_LINE(LOAD_TBL_VER)
		{
			INT		ver0 = 0;
			INT		ver1 = 0;
			INT		ver2 = 0;
			INT		ver  = 0;

			sscanf(sLine, "%*s %d.%d.%d", &ver0, &ver1, &ver2);
			ver = ver0 <<24 | ver1 <<16 | ver2 <<8;
			pTbl->SetAttrib(LCXT_ITK_VERSION, &ver);
		}

		READ_TEXT_LINE(LOAD_TBL_MST)
		{
			{
				char*	src = sLine + sParse[LOAD_TBL_MST].iKey;
				char	idx[LC_DEFAULT_NAME]={0};

				strcpy(idx, src);
				LcStr_Trim(idx);

				if(0 < strlen(idx))
					nMst = atoi(idx);
				else
					++nMst;

				MAKE_ARG1(args, (INT)(nMst+1));
				pTbl->SetAttrib(LCXT_ITK_MST_SIZE, &args);

				nSub = -1;
				nRec = -1;
			}


			while( !fp->Eof() )
			{
				fp->ReadLine(sLine, LC_MAX_PARSE_LINE);
				LcStr_Trim(sLine);

				if('}' == sLine[0])
					break;


				READ_TEXT_LINE(LOAD_TBL_MNAME)
				{
					char*	src = sLine + sParse[LOAD_TBL_MNAME].iKey;
					char	name[LC_DEFAULT_NAME]={0};

					strcpy(name, src);
					LcStr_Trim(name);
					MAKE_ARG2(args, nMst, name);

					pTbl->SetAttrib(LCXT_ITK_MST_NAME, &args);
				}

				READ_TEXT_LINE(LOAD_TBL_SNUM)
				{
					INT	iS=0;
					sscanf(sLine,"%*s %d", &iS);

					MAKE_ARG2(args, nMst, iS);
					pTbl->SetAttrib(LCXT_ITK_SUB_SIZE, &args);
				}


				READ_TEXT_LINE(LOAD_TBL_SUB)
				{
					{
						char*	src = sLine + sParse[LOAD_TBL_SUB].iKey;
						char	idx[LC_DEFAULT_NAME]={0};

						strcpy(idx, src);
						LcStr_Trim(idx);

						if(0 < strlen(idx))
							nSub = atoi(idx);
						else
							++nSub;

						MAKE_ARG2(args, nMst, (INT)(nSub+1));
						pTbl->SetAttrib(LCXT_ITK_SUB_SIZE, &args);

						nRec = -1;
					}


					while( !fp->Eof() )
					{
						fp->ReadLine(sLine, LC_MAX_PARSE_LINE);
						LcStr_Trim(sLine);

						if('}' == sLine[0])
							break;

						READ_TEXT_LINE(LOAD_TBL_SNAME)
						{
							char*	src = sLine + sParse[LOAD_TBL_MNAME].iKey;
							char	name[LC_DEFAULT_NAME]={0};

							strcpy(name, src);
							LcStr_Trim(name);
							MAKE_ARG3(args, nMst, nSub, name);

							pTbl->SetAttrib(LCXT_ITK_SUB_NAME, &args);
						}

						READ_TEXT_LINE(LOAD_TBL_SPATH)
						{
							char*	src = sLine + sParse[LOAD_TBL_MNAME].iKey;
							char	path[LC_DEFAULT_NAME]={0};
							INT		len = 0;

							strcpy(path, src);
							LcStr_Trim(path);
							len = strlen(path);

							if('/' != path[len-1] )
							{
								path[len] ='/';
								path[len+1] ='\0';
							}

							MAKE_ARG3(args, nMst, nSub, path);
							pTbl->SetAttrib(LCXT_ITK_SUB_PATH, &args);
						}


						READ_TEXT_LINE(LOAD_TBL_RNUM)
						{
							INT iR=0;

							sscanf(sLine, "%*s %d", &iR);

							MAKE_ARG3(args, nMst, nSub, iR);
							pTbl->SetAttrib(LCXT_ITK_REC_SIZE, &args);
						}


						READ_TEXT_LINE(LOAD_TBL_REC)
						{
							INT iR = 0;
							char sName[LC_MAX_PATH2]={0};

							sscanf(sLine, "%*s %s", sName);

							++nRec;
							iR = nRec +1;

							MAKE_ARG3(args, nMst, nSub, iR);
							pTbl->SetAttrib(LCXT_ITK_REC_SIZE, &args);

							MAKE_ARG4(args, nMst, nSub, nRec, sName);
							pTbl->SetAttrib(LCXT_ITK_REC_NAME, &args);
						}// if
					}//while
				}// if
			}// while
		}// if

#undef	READ_TEXT_LINE
	}// while

	SAFE_RELEASE( fp );


//#if !defined(LCX_HF_LIB)
	return LC_OK;
//#endif
	

	FILE*	fpo   = NULL;
	char*	src_n = NULL;
	char	sTmp[LC_MAX_PATH2]={0};

	pTbl->GetAttrib(LCXT_ITK_TBL_NAME, &src_n);
	LcStr_ReplacePath(sTmp, src_n, NULL, NULL, NULL, (const char*)"");
	strcat(sTmp, "_cnf.txt");

	fpo = fopen(sTmp, "wt");
	if(NULL == fpo)
		return LC_CANNT_FIND_RESOURCE;


	INT tblVer = 0;
	INT numMst = 0;
	INT numSub = 0;
	INT numRec = 0;

	fprintf(fpo, "////////////////////////////////////////////////////\n//\n\n");
	fprintf(fpo, "TableName	%s\n", src_n);

	pTbl->GetAttrib(LCXT_ITK_VERSION, &tblVer);
	fprintf(fpo, "%s\t\t0x%08X\n",	sParse[LOAD_TBL_VER].sKey, tblVer);
	
	pTbl->GetAttrib(LCXT_ITK_MST_SIZE, &numMst);
	fprintf(fpo, "%s\t\t%d\n"	,	sParse[LOAD_TBL_MNUM].sKey, numMst);


	for(INT m=0; m<numMst; ++m)
	{
		char*	mstName = NULL;
		
		MAKE_ARG1(args, m);
		pTbl->GetAttrib(LCXT_ITK_MST_NAME, &args);
		mstName = args._1;

		MAKE_ARG1(args, m);
		pTbl->GetAttrib(LCXT_ITK_SUB_SIZE, &args);
		numSub = args._1;


		fprintf(fpo, "\n%s\t%d\n{\n",	sParse[LOAD_TBL_MST  ].sKey, m);
		fprintf(fpo, "\t%s\t%s\n"	,	sParse[LOAD_TBL_MNAME].sKey, mstName);
		fprintf(fpo, "\t%s\t%d\n"	,	sParse[LOAD_TBL_SNUM ].sKey, numSub);

		for(INT s=0; s<numSub; ++s)
		{
			char*	subName = NULL;
			char*	subPath = NULL;

			MAKE_ARG2(args, m, s);
			pTbl->GetAttrib(LCXT_ITK_SUB_NAME, &args);
			subName = args._2;

			MAKE_ARG2(args, m, s);
			pTbl->GetAttrib(LCXT_ITK_SUB_PATH, &args);
			subPath = args._2;

			MAKE_ARG2(args, m, s);
			pTbl->GetAttrib(LCXT_ITK_REC_SIZE, &args);
			numRec = args._2;


			fprintf(fpo, "\n\t%s\t%d\n\t{\n",	sParse[LOAD_TBL_SUB  ].sKey, s);
			fprintf(fpo, "\t\t%s\t%s\n"		,	sParse[LOAD_TBL_SNAME].sKey, subName);
			fprintf(fpo, "\t\t%s\t%s\n"		,	sParse[LOAD_TBL_SPATH].sKey, subPath);
			fprintf(fpo, "\t\t%s\t%d\n\n"	,	sParse[LOAD_TBL_RNUM ].sKey, numRec);

			for(INT r=0; r<numRec; ++r)
			{
				char*	recName = NULL;

				MAKE_ARG3(args, m, s, r);
				pTbl->GetAttrib(LCXT_ITK_REC_NAME, &args);
				recName = args._3;

				fprintf(fpo, "\t\t%s\t%s\n"	,	sParse[LOAD_TBL_REC].sKey, recName);
			}

			fprintf(fpo, "\t}\n");
		}

		fprintf(fpo, "}\n");
	}

	fclose(fpo);

	return LC_OK;
}


#define MEDIA_DIR	"../../media/"


int main(int argc, char* argv[])
{
	TLC_ARGS	args;
	INT			hr = 0;

	char		tblFile[] = MEDIA_DIR"data/tbl_model.dat";
	PLCX_TBL	tbl_mdl	= NULL;


	MAKE_ARG6(args, (UINT)LC_SRC_T_FILE, tblFile, (LC_HANDLE)TblMdlLoad, (LC_HANDLE)TblMdlCreate, (LC_HANDLE)TblMdlRelease, (LC_HANDLE)TblMdlCmp);
	hr = LcxEnt_CreateTable(NULL, &tbl_mdl, &args);
	if(LC_FAILED(hr))
		return LC_EFAIL;


	PLCX_TBL	pTbMdl = tbl_mdl;


	int nM, nS, nR;
	char* obj = (char*)pTbMdl->Select(&nM, &nS, &nR, "model/3d/tree02");

	printf("receive : %s\n", obj);
	SAFE_RELEASE(	tbl_mdl	);
	return 0;
}

