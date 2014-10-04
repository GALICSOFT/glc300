// Start Program.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


CMain*	g_pApp = NULL;


int main(int argc, char* argv[])
{
	int		hr=0;

	CMain	mainApp;
	g_pApp = &mainApp;

	hr = mainApp.Create(NULL);
	if(LC_FAILED(hr))
		return LC_OK;

	hr = mainApp.Run(NULL);

	return hr;
}




