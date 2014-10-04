// Implementation of the CMain class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


#define MEDIA_DIR	"../../media/"


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
   0, 1, 2, 2, 3, 0,
};


int CMain::SetupShader()
{
	int hr =0;
	GLint bLinked;

	TLC_ARGS args;

	MAKE_ARG2(args, (UINT)GL_VERTEX_SHADER, (char*)MEDIA_DIR"shader/01sl_vs.glsl");
	hr = LcDev_CreateShaderFromTxtFile(&m_VsShader, &args);
	if(0>hr)
		return -1;

	MAKE_ARG2(args, (UINT)GL_FRAGMENT_SHADER, (char*)MEDIA_DIR"shader/01sl_fs.glsl");
	hr = LcDev_CreateShaderFromTxtFile(&m_FgShader, &args);
	if(0>hr)
		return -1;

	m_program = glCreateProgram();

    glAttachShader(m_program, m_FgShader);
    glAttachShader(m_program, m_VsShader);

    glBindAttribLocation(m_program, 0, "at_pos");
	//glBindAttribLocation(m_program, 1, "at_dif");

    glLinkProgram(m_program);

	glGetProgramiv(m_program, GL_LINK_STATUS, &bLinked);
	if (!bLinked)
	{
		int i32InfoLogLength;
		int i32CharsWritten;
		glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &i32InfoLogLength);
		char* pszInfoLog = new char[i32InfoLogLength];
		glGetProgramInfoLog(m_program, i32InfoLogLength, &i32CharsWritten, pszInfoLog);

		LOGE("Shader Link Err: %s\n", i32InfoLogLength ? pszInfoLog : "");
		delete[] pszInfoLog;
		return -1;
	}

	return 0;
}



static char g_CurrentDir[260]={0};


CMain::CMain()
{
	LcAux_GetCurrentDir(g_CurrentDir, 260);
}



int	CMain::Init()
{
	LcAux_SetCurrentDir(g_CurrentDir);

	SetupShader();

	return LC_OK;
}

int	CMain::Destroy()
{
	return LC_OK;
}


int	CMain::FrameMove()
{
#if defined(_WIN32)
	LcAux_Sleep(10);
#endif

	static int c=0;
	++c;

	//	if(c>20*60*20)
	if(c>8*60*2)
	{
		printf("Game Process Terminated\n");
		return LC_EFAIL;
	}

	static int n = 0;
	++n;


	float fps = (float)this->GetFPS();

	if(n>5)
	{
		printf("FPS: %3.f\n", fps);
		n = 0;
	}


	return LC_OK;
}



int	CMain::Render()
{
	glUseProgram(m_program);


	glDisable( GL_DEPTH_TEST);		// disable depth test
	glDisable( GL_CULL_FACE );		// disalbe culling face

	glClearColor(0.9f, 1.0f, 1.0f, 1.0f);


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 2, GL_FLOAT, 0, 0, g_pos);
	glVertexAttribPointer(1, 4, GL_FLOAT, 0, 0, g_dif);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, g_idx);
	//glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	// disable client-side capability
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	return LC_OK;
}



