

#if defined(_MSC_VER)
  #pragma comment(linker, "/subsystem:console")
  #pragma comment(lib, "lgpwn_a30_.lib")
  #pragma comment(lib, "lgpwn_b30_.lib")
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ac/zlib.h>

#include <LcType.h>
#include <LcBase.h>
#include <LcAux.h>

#define MEDIA_DIR	"../../media/"



int main(int argc, char* argv[])
{
	BYTE*      bufOut = NULL;
	ULONG      lsize  = 0;
	INT			hr =0;

	char*		src = "assets\\login2\\login.gptf";
	char		dst[260]={0};

	printf("---------------------------------------------------------------\n");
	printf("apk asset folder test ...\n");


	LcStr_Replace(dst, src, "\\", "/");
	hr = Lzip_AssetBuffer(&bufOut, &lsize, (char*)MEDIA_DIR"nffui.apk", "login2\\login.gptf", 0);

	SAFE_FREE(bufOut);


	printf("\n---------------------------------------------------------------");
	printf("\n---------------------------------------------------------------\n");
	printf("zip test ...\n");

	hr = Lzip_SimpleUnZip(&bufOut, &lsize, (char*)MEDIA_DIR"data.zip", "test_comp.json");

	// just for printf.. it does not need in application
	bufOut = (BYTE*)realloc(bufOut, lsize+4);
	bufOut[lsize]=0;
	printf("%s\n", (char*)bufOut);

	SAFE_FREE(bufOut);


	printf("\n---------------------------------------------------------------");
	printf("\n---------------------------------------------------------------\n");
	printf("gz test ...\n");


	gzFile fp = gzopen((char*)MEDIA_DIR"abc.gz", "rt");

	char sline[520];

	while(!gzeof(fp))
	{
		memset(sline, 0, sizeof(sline));
		gzgets(fp, sline, 512);
		printf("%s", sline);
	}


	gzclose(fp);
	return LC_OK;
}


