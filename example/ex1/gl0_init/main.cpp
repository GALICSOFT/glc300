//
//
//
////////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER) && _MSC_VER >= 1200
  #pragma warning( disable : 4786)
  #pragma warning( disable : 4996)
#endif


#if defined(_MSC_VER)
  #pragma comment(linker, "/subsystem:console")
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


#if defined(_MSC_VER)
  #define _CRTDBG_MAP_ALLOC
  #include <crtdbg.h>
#endif


#if defined(_WIN32)
	#include <windows.h>

#else

	#define CALLBACK
	typedef void*	HWND;
	typedef long (CALLBACK* WNDPROC)(HWND, unsigned int, unsigned int, long);

	#include <unistd.h>

#endif


#include <gles/egl2.h>
#include <gles/gl2.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// window handle, display, surface, and rendering context for OpenGL
NativeWindowType	pEgWnd = 0;	// window handle
EGLDisplay			pEgDsp = 0;	// EGL display
EGLSurface			pEgSrf = 0;	// EGL rendering surface
EGLContext			pEgCtx = 0;	// EGL rendering context

EGLConfig			pEgCfg[16]={0};



int	 Run();
long CALLBACK MyMsgPrc(HWND, unsigned int, unsigned int, long);



int OS_CreateWindow(NativeWindowType* pWnd, WNDPROC WndProc, char* ClassName, int ScreenW, int ScreenH)
{
	*pWnd = 0;

#if defined(_WIN32)

	// Register Window Procedure function and create Window Handle in Win32 System
	HWND		hWnd = NULL;
	HINSTANCE	hInst = (HINSTANCE)GetModuleHandle(NULL);

	WNDCLASS	wc=
	{
		CS_HREDRAW | CS_VREDRAW
		,	WndProc
		,	0L
		,	0L
		,	hInst
		,	LoadIcon(NULL, IDI_APPLICATION)
		,	LoadCursor(NULL, IDC_ARROW)
		,	(HBRUSH)GetStockObject(WHITE_BRUSH)
		,	NULL
		,	ClassName
	};

	if( 0==	RegisterClass(&wc))
		return -1;


	UINT dStyle=WS_VISIBLE | WS_CAPTION | WS_SYSMENU;
	RECT rc = {0,0, ScreenW, ScreenH};
	AdjustWindowRect(&rc, dStyle, 0);


	// Create Window Handle in Win32 System
	hWnd = ::CreateWindow(ClassName
						  , ClassName
						  , dStyle
						  , 1
						  , 1
						  , rc.right  - rc.left
						  , rc.bottom - rc.top
						  , NULL
						  , NULL
						  , hInst
						  , NULL);

	if( NULL == hWnd)
		return -1;

	EnableWindow( hWnd, 1);
	SetForegroundWindow(hWnd);
	ShowWindow(hWnd, SW_SHOWNORMAL);

	*pWnd = (NativeWindowType)hWnd;
#endif

	return 0;
}





// for the using opengl in embedded systems, u need display, surface, and rendering context.
// but window handle, device context(DC), and rendering context in windows system of PC
int InitGL(NativeWindowType hWnd)
{
	struct _Tcfg_val { int k; int v;	};
	const _Tcfg_val cfg_att[] =
	{
		{	EGL_RED_SIZE		, 8						},
		{	EGL_GREEN_SIZE		, 8						},
		{	EGL_BLUE_SIZE		, 8						},
		{	EGL_ALPHA_SIZE		, 8						},
		{	EGL_DEPTH_SIZE		, 24					},
		{	EGL_STENCIL_SIZE	,  8					},
		{	EGL_SURFACE_TYPE	, EGL_WINDOW_BIT		},
		{	EGL_RENDERABLE_TYPE	, EGL_OPENGL_ES2_BIT	},
		{	EGL_NONE			, EGL_NONE				},
	};

	const _Tcfg_val cfg_ctx[] =
	{
		{	EGL_CONTEXT_CLIENT_VERSION, 2			},
		{	EGL_NONE,					EGL_NONE	},
	};

	INT		match = 0;
	int		ver_maj=0;
	int		ver_min=0;

	eglBindAPI(EGL_OPENGL_ES_API);


	// get an display connection for the native display.
	// almost embedded systems use the EGL_DEFAULT_DISPLAY(zero) value.
	pEgDsp = eglGetDisplay((EGLNativeDisplayType)hWnd);
	if(NULL == pEgDsp)
	{
		printf("eglGetDisplay() Failed\n");
		return -1;
	}

	if( 0 == eglInitialize(pEgDsp, &ver_maj, &ver_min) )
	{
		printf("eglInitialize() Failed\n");
		return -1;
	}

	if( 0 == eglChooseConfig(pEgDsp, (const EGLint*)&cfg_att[0], &pEgCfg[0], 16, &match) )
	{
		printf("eglChooseConfig() Failed\n");
		return -1;
	}

	if(1>match)	// No Match
	{
		printf("There is no match\n");
		return -1;
	}


	pEgSrf = eglCreateWindowSurface(pEgDsp, pEgCfg[0], hWnd, 0);
	if(NULL == pEgSrf)
	{
		printf("eglCreateWindowSurface() Failed\n");
		return -1;
	}

	// create rendering context(RC)
	pEgCtx = eglCreateContext(pEgDsp, pEgCfg[0], 0, (const EGLint*)&cfg_ctx[0]);
	if(NULL == pEgCtx)
	{
		printf("eglCreateContext() Failed\n");
		return -1;
	}


	// connect activate the context for rendering to the surface
	if( !eglMakeCurrent(pEgDsp, pEgSrf, pEgSrf, pEgCtx) )
	{
		printf("eglMakeCurrent() Failed\n");
		return -1;
	}

	// Set the swap interval of display to immediately mode.
	// it means that buffer swaps are not synchronized to a video frame,
	// and the swap happens as soon as the render is complete.
	//if( !eglSwapInterval(pEgDsp, 0))
	//{
	//	printf("eglSwapInterval() Failed\n");
	//	return -1;
	//}



	printf("GLSL ability: ------------------------------\n");

	float size = 0;
	size = 0; glGetFloatv(GL_MAX_VERTEX_ATTRIBS              , &size);	printf("GL_MAX_VERTEX_ATTRIBS: %.f\n", size);
	size = 0; glGetFloatv(GL_MAX_VERTEX_UNIFORM_VECTORS      , &size);	printf("GL_MAX_VERTEX_UNIFORM_VECTORS: %.f\n", size);
	size = 0; glGetFloatv(GL_MAX_VARYING_VECTORS             , &size);	printf("GL_MAX_VARYING_VECTORS: %.f\n", size);
	size = 0; glGetFloatv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &size);	printf("GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS: %.f\n", size);
	size = 0; glGetFloatv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS  , &size);	printf("GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS: %.f\n", size);
	size = 0; glGetFloatv(GL_MAX_TEXTURE_IMAGE_UNITS         , &size);	printf("GL_MAX_TEXTURE_IMAGE_UNITS: %.f\n", size);
	size = 0; glGetFloatv(GL_MAX_FRAGMENT_UNIFORM_VECTORS    , &size);	printf("GL_MAX_FRAGMENT_UNIFORM_VECTORS: %.f\n", size);


	printf("it was perfectly finished that the initialization for rendering.\n");

	return 0;
}






// OpenGL Rendering
void Render()
{
	// specify clear values(red, green, blue, alpha) for the color buffer
	glClearColor(0.0f, 0.4f, 0.6f, 1.0f);

	// Clear Color buffer and Depth Buffer.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


	// Setting Rendering pipeline
	glDisable( GL_DEPTH_TEST);		// disable depth test
	glDisable( GL_CULL_FACE );		// disalbe culling face


	// force execution of GL commands in finite time
	// It does not wait until the execution of all previously
	// issued GL commands is complete.
	//glFlush();

	// post EGL surface color buffer to a native window
	eglSwapBuffers(pEgDsp, pEgSrf);
}

void Clean()
{
	if(NULL == pEgDsp)
		return;

	eglMakeCurrent		(pEgDsp, 0, 0, 0);	// Make current to null
	eglDestroyContext	(pEgDsp, pEgCtx);	// release context, surface, and display
	eglDestroySurface	(pEgDsp, pEgSrf);
	eglTerminate		(pEgDsp);

	pEgSrf	= NULL;
	pEgCtx	= NULL;
	pEgDsp	= NULL;
	pEgWnd	= NULL;
}





int main(int argc, char** argv)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	int hr = 0;

	// Create native window.
	hr = OS_CreateWindow(&pEgWnd, MyMsgPrc, (char*)"Welcome to Galic SDK", 800, 480);
	if(0 > hr)
		return 0;


	 // OpenGL ES Initialization
	if( 0 >InitGL(pEgWnd))
		return 0;


	// Main Loop
	while(1)
	{
		if(0>Run())
			break;
	}


	//Clean up all
	Clean();

	_CrtDumpMemoryLeaks();
	return 0;
}




int Run()
{
#if defined(_WIN32)
	static MSG msg ={0};

	if(msg.message==WM_QUIT)
		return -1;

	// check message in queue
	if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
	{
		::TranslateMessage( &msg );
		::DispatchMessage( &msg );
	}

	Sleep(1);

#endif

	static int frames = 1000;

	if(0 == --frames)
		return -1;


	// Rendering
	Render();

	return 0;
}



long CALLBACK MyMsgPrc(HWND hWnd, unsigned int uMsg, unsigned int wParam, long lParam)
{
	long hr = 0;

#if defined(_WIN32)
	switch (uMsg)
	{
		case WM_KEYDOWN:
		{
			if(VK_ESCAPE == wParam)
			{
				SendMessage(hWnd, WM_CLOSE, 0, 0);
				return 0;
			}
			break;
		}

		case WM_CLOSE:
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	}

	hr = DefWindowProc(hWnd, uMsg, wParam, lParam);
#endif

	return hr;
}




