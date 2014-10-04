


#if defined(_MSC_VER)
  #pragma comment(linker, "/subsystem:console")
  #pragma comment(lib, "lgpwn_a30_.lib")
  #pragma comment(lib, "lgpwn_b30_.lib")
#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <LcType.h>
#include <LcBase.h>
#include <LcMath.h>
#include <LcEuclid.h>
#include <LcAux.h>


#define MEDIA_DIR	"../../media/"


int main(int argc, char** argv)
{
	INT hr = 0;

	char	sFile[] = MEDIA_DIR"data/test_comp.json";
	char*	buf    = NULL;
	int		length = 0;
	

	PLC_FILE	fp = NULL;
	if(LC_FAILED(LcFile_Open(NULL, &fp, sFile, (char*)"rt")))
	{
		printf("XML::Err fopen:%s\n", sFile);
		return LC_CANNT_FIND_RESOURCE;
	}


	// read all data of file
	fp->ReadBytes( (BYTE**)&buf, &length);

	printf("length: %d \n", length);
	printf(buf);


	printf("--------------------------------------------------------------\n");
	printf("--------------------------------------------------------------\n");
	printf("--------------------------------------------------------------\n");
	printf("--------------------------------------------------------------\n");

	fp->Seek(0, SEEK_SET);

	while(1)
	{
		char sline[256+4]={0};
		int r = fp->ReadLine(sline, 256);

		if( 0> r)
			break;

		printf("%s\n", sline);
	}


	SAFE_RELEASE(fp);
	SAFE_FREE(buf);

	return 0;
}
