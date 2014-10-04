// Start Program.
//
////////////////////////////////////////////////////////////////////////////////


#if defined(_MSC_VER)
  #define _CRTDBG_MAP_ALLOC
  #include <crtdbg.h>
#endif

#include "_StdAfx.h"


CMain*	g_pApp = NULL;


int main(int argc, char* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(269);


	int		hr=0;

	CMain	mainApp;
	g_pApp = &mainApp;

	hr = mainApp.Create();
	if(LC_FAILED(hr))
		return LC_OK;

	hr = mainApp.Run(NULL);

	_CrtDumpMemoryLeaks();
	return hr;
}

