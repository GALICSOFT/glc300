//	Copyright(C) GaLic Soft. All rights reserved.
//	GaLic Game Library Collection
//
// Interface for the DGT Entities.
//
////////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER)
  #pragma once
#endif

#ifndef _LctEntity_H_
#define _LctEntity_H_

//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// for android method

LC_HANDLE LctJni_FindMethod(const char* name);									// Find method for JNI application
INT       LctJni_ExecMethod(LC_HANDLE, PLC_ARGS);								// execution method with finding method




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// for simple xml

DCL_INTERFACE ILCT_Xml : public ILC_Object
{
	DCL_CLASS_DESTROYER(	ILCT_Xml	);

	virtual INT	Release(INT bDecreaseRefCount=LC_TRUE)=0;
	virtual INT	Query(char* sCmd, LC_HANDLE pData)=0;

	virtual LC_HANDLE	ElmList(const char* sElm, LC_HANDLE pNodeParent)=0;
	virtual LC_HANDLE	ElmNode(LC_HANDLE pNode, INT nIdx)=0;
	virtual INT			ElmSize(LC_HANDLE pNode)=0;
	virtual INT			ElmText(char* sOutput, LC_HANDLE pNode)=0;
	virtual INT			ElmAttrb(char* sOutput, int sOutputSize, LC_HANDLE pNode, const char* sAttName)=0;
};

typedef	ILCT_Xml*	PLCT_XML;

INT LctXml_Create(char* sCmd
					, PLCT_XML* pData
					, LC_HANDLE p1			// XML File
					, LC_HANDLE p2 = NULL	// No Use
					, LC_HANDLE p3 = NULL	// No Use
					, LC_HANDLE p4 = NULL	// No Use
				 );




#if !defined(_LC_ORG_SRC_)

//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// for csv file

enum ELctDBcsv
{
	LCTDB_MAX_FIELD		= 128,
	LCTDB_MAX_NAME		= 64,
	LCTDB_MAX_TEXT		= 512,

	// for Get Attribute
	LCTDB_RECORD_NUM	= 0x1001,			// Get the record number
	LCTDB_FIELD_NUM		= 0x1002,			// Get the field number

	LCTDB_FIELD_INDEX	= 0x1003,			// Get the field index. it needs string
	LCTDB_FIELD_NAME	= 0x1004,			// Get the field name. return the field name
	LCTDB_FIELD_TYPE	= 0x1005,			// Get the field type.
};

// Query Command
#define LCTDB_QUERY_COPY_TO		(char*)"Copy to"
#define LCTDB_QUERY_SAVE_AS		(char*)"Save As"


DCL_INTERFACE ILCT_DBcsv : public ILC_Object
{
	struct TCSV_CELL
	{
		INT			t;					// cell type
		union							// value
		{
			char	b;					// for Boolean
			INT		n;					// for Small
			FLOAT	f;					// for Float
			DOUBLE	d;					// for Big
			char*	s;					// string
		};

		TCSV_CELL() : t(0), n(-1){}
	};

	struct TCSV_REC
	{
		INT			cnt;
		TCSV_CELL	rec[LCTDB_MAX_FIELD];
	};


	DCL_CLASS_DESTROYER(	ILCT_DBcsv	);

	virtual INT	Query(char* sCmd, LC_HANDLE pData)=0;

	virtual INT	Select(TCSV_CELL* pOut, INT row, INT col)=0;
	virtual INT	Select(TCSV_CELL* pOut, INT row, char* FieldName)=0;
	virtual INT	Select(TCSV_REC * pOut, INT row)=0;

	virtual INT	Insert(TCSV_REC * pIn)=0;

	virtual INT	Update(TCSV_CELL* pIn, INT row, INT col)=0;
	virtual INT	Update(TCSV_CELL* pIn, INT row, char* FieldName)=0;

	virtual INT	Delete(INT row)=0;
};

typedef	ILCT_DBcsv*		PLCT_DBCSV;

// Create DB from CSV
INT LctDB_CreateCsv(char* sCmd
				   , PLCT_DBCSV* pOut		// Output instance
				   , LC_HANDLE p1			// CSV File Name or Memory Address
				   , LC_HANDLE p2 = NULL	// Memory Size Address(int*). if it will be used from file then it must be null or zero
				   , LC_HANDLE p3 = NULL	// Delimiter. ',' is default if change this value int dlm =',' and set the argument to &dlm
				   , LC_HANDLE p4 = NULL	// No Use
					 );




//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
// Simple searcher with two index keys

enum
{
	LCXT_ITK_VERSION	,														// ITK VERSION
	LCXT_ITK_MST_SIZE	,														// Maser(primary) key count
	LCXT_ITK_SUB_SIZE	,														// sub(secondary) key count
	LCXT_ITK_REC_SIZE	,														// Record count of sub

	LCXT_ITK_TBL_NAME	,														// Table instance name
	LCXT_ITK_MST_NAME	,														// master name
	LCXT_ITK_SUB_NAME	,														// sub master name
	LCXT_ITK_REC_NAME	,														// resource name
	LCXT_ITK_REC_VAL	,														// resource option
	LCXT_ITK_REC_PAIR	,														// resource name and option
	LCXT_ITK_SUB_PATH	,														// resource group path
};

DCL_INTERFACE ILCX_ITK : public ILC_Object
{
	DCL_CLASS_DESTROYER(	ILCX_ITK	);

	virtual INT				Release(INT bDecreaseRefCount=LC_TRUE)=0;
	virtual INT				Query(char* sCmd, LC_HANDLE pData)=0;

	virtual INT				SetAttrib(UINT dCmd, LC_HANDLE pData) =0;			// VERSION(INT), MST_SIZE(INT)
	virtual INT				GetAttrib(UINT dCmd, LC_HANDLE pData) =0;

	virtual	INT				Select(INT* nMst, char* sMst) =0;												// find the master index
	virtual	INT				Select(INT* nMst/*Out*/, INT* nSub/*Out*/, char* sSub) =0;						// select the master and sub index by sub name: return -1: failed.
	virtual	LC_HANDLE		Select(INT* nMst/*Out*/, INT* nSub/*Out*/, INT* nRec/*Out*/, char* rsc) =0;		// select the master, sub, and record index byt resource name
	virtual	LC_HANDLE		Select(INT  nMst, INT nSub, INT nRec) =0;										// select the resource
	virtual	CONF(TLC_ARGS*)	SelectOpt (INT nMst, INT nSub, INT nRec) =0;									// select the resource option
};

typedef ILCX_ITK*	PLCX_TBL;


INT LcxEnt_CreateTable(char* sCmd, PLCX_TBL* pOut, PLC_ARGS arg);


typedef INT        (*PTBL_LOAD   )(PLC_ARGS);									// table load function
typedef PLC_OBJECT (*PTBL_CREATE )(char* path, char* name, PLC_ARGS option);	// create the resource instance with path, filename, and option
typedef void       (*PTBL_RELEASE)(LC_HANDLE* intance, PLC_ARGS option);		// release the resource instance and value ...

																				// record search
typedef INT        (*PTBL_RECCMP )(PLC_ARGS, LC_HANDLE searchName);				// record search Mster name, Sub path, sub name, recored name, search name

#endif //#if !defined(_LC_ORG_SRC_)




#endif


