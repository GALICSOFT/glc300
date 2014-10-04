

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

#include <string>
using namespace std;


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>

#include <gles/gl2.h>

#include <LcType.h>
#include <LcBase.h>
#include <LcMath.h>
#include <LcEuclid.h>
#include <LcCore.h>
#include <LcAux.h>


LC_HWND			m_hWnd	= NULL;		// Window Handle
PLC_DEVICE		m_pDev = NULL;		// Device pointer


INT LC_CALLBACK Run(LC_HANDLE);



static const float g_pos[] =
{
   -0.97f, -0.95f,
    0.97f, -0.95f,
    0.97f,  0.95f,
   -0.97f,  0.95f,
};

static const float g_dif[] =
{
   1.0f, 0.0f, 0.0f, 1.0f,
   0.0f, 1.0f, 0.0f, 1.0f,
   0.0f, 0.0f, 1.0f, 1.0f,
   1.0f, 0.0f, 1.0f, 1.0f,
};



static const unsigned short g_idx[] =
{
	0, 1, 2,
	0, 2, 3,
};



static char g_vs[] = 
"#ifdef GL_ES									\n"
"precision mediump float;						\n"
"#endif											\n"

"attribute vec4 at_pos;							\n"
"attribute vec4 at_dif;							\n"

"varying   vec4 vr_dif;							\n"

"void main()									\n"
"{												\n"
"	vr_dif   = at_dif;							\n"
"	gl_Position = at_pos;						\n"
"}												\n"
;


static char g_fs[] = 
"#ifdef GL_ES									\n"
"precision mediump float;						\n"
"#endif											\n"

"varying   vec4	vr_dif;							\n"

"void main()									\n"
"{												\n"
"	float	r;									\n"
"	r = vr_dif.r * 0.299 + vr_dif.g * 0.587;	\n"
"	r+= vr_dif.b * 0.114;						\n"
//"	gl_FragColor = vec4(r,r,r, vr_dif.a);		\n"
"	gl_FragColor = vr_dif;						\n"
"}												\n"
;


GLuint g_shVtx;
GLuint g_shFrag;
GLuint g_shProg;


int SetupShader()
{
	int hr =0;
	GLint bLinked;

	TLC_ARGS	args;

	MAKE_ARG2(args, (UINT)GL_VERTEX_SHADER, (char*)g_vs);

	hr = LcDev_CreateShaderFromTxtBuffer(&g_shVtx, &args);
	if(0>hr)
	{
		hr = LcDev_CreateShaderFromTxtBuffer(&g_shVtx, &args);
		if(0>hr)
			return -1;
	}


	MAKE_ARG2(args, (UINT)GL_FRAGMENT_SHADER, (char*)g_fs);

	hr = LcDev_CreateShaderFromTxtBuffer(&g_shFrag, &args);
	if(0>hr)
	{
		hr = LcDev_CreateShaderFromTxtBuffer(&g_shFrag, &args);
		if(0>hr)
			return -1;
	}


	g_shProg = glCreateProgram();

	glAttachShader(g_shProg, g_shVtx);
	glAttachShader(g_shProg, g_shFrag);

	glBindAttribLocation(g_shProg, 0, "at_pos");
	glBindAttribLocation(g_shProg, 1, "at_dif");

	glLinkProgram(g_shProg);

	glGetProgramiv(g_shProg, GL_LINK_STATUS, &bLinked);
	if (!bLinked)
	{
		int i32InfoLogLength;
		int i32CharsWritten;
		glGetProgramiv(g_shProg, GL_INFO_LOG_LENGTH, &i32InfoLogLength);
		char* pszInfoLog = new char[i32InfoLogLength];
		glGetProgramInfoLog(g_shProg, i32InfoLogLength, &i32CharsWritten, pszInfoLog);

		LOGE("Shader Link Err: %s\n", i32InfoLogLength ? pszInfoLog : "");
		delete[] pszInfoLog;
		return -1;
	}

	return 0;
}


INT InitDevice()
{
	INT hr = LC_OK;

	// Init GLC Library
	LcSys_Init();

	printf("LcSys_Init\n");

	// Set Main procedure Function Pointer
	LcSys_SetMainRunFunc(Run);

	// Create Window
	hr = LcSys_CreateWindow(NULL, (char*)"LC_Tutorial", 800, 480);
	if(LC_FAILED(hr))
	{
		printf("LcSys_CreateWindow Failed\n");
		return LC_EFAIL;
	}

	// Create GLC Rendering Device
	if(LC_FAILED(LcDev_CreateDevice(NULL, &m_pDev)))
	{
		printf("LcDev_CreateDevice Failed\n");
		return LC_EFAIL;
	}

	return LC_OK;
}




// rendering 3d Model
void Render()
{
	glUseProgram(g_shProg);


	glDisable( GL_DEPTH_TEST);		// disable depth test
	glDisable( GL_CULL_FACE );		// disalbe culling face

	glClearColor(0.9f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 2, GL_FLOAT, 0, 0, g_pos);
	glVertexAttribPointer(1, 4, GL_FLOAT, 0, 0, g_dif);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, g_idx);

	// disable client-side capability
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

}



// Main Program
int main(int argc, char* argv[])
{
	char sdir[260]={0};
	_getcwd( sdir, 260);

	if(LC_FAILED(InitDevice()))
		goto End;

	_chdir(sdir);
	_getcwd( sdir, 260);

	SetupShader();
	

	// Run Program
	while(1)
	{
		if(LC_FAILED(LcSys_Run()))
			break;

		// Flipping
		m_pDev->Present(0,0,0,0);
	}


End:
	m_pDev->Release();		// Release Device

	// Release Window
	LcSys_DestroyWindow();

	// Release GLC
	LcSys_Close();

	return LC_OK;
}



INT LC_CALLBACK Run(LC_HANDLE)
{
#if defined(_WIN32)
	LcAux_Sleep(1);
#endif

	static int frames = 11500;

	if(0 == --frames)
		return LC_EFAIL;


	Render();

	return LC_OK;
}

