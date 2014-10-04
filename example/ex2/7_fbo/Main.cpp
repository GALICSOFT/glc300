// Implementation of the CMain class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


static char g_CurrentDir[260]={0};


#define MEDIA_DIR	"../../media/"



CMain::CMain()
{
	m_pEft		= NULL;
	m_pTex		= NULL;

	m_pFbo		= NULL;

	LcAux_GetCurrentDir( g_CurrentDir, 260);
}


INT	CMain::Init()
{
	INT			hr =0;
	TLC_ARGS	args;

	LcAux_SetCurrentDir( g_CurrentDir);


	char* attlist[] = {"at_pos", NULL};
	MAKE_ARG3(args, (char*)MEDIA_DIR"shader/27sl_vs.glsl", (char*)MEDIA_DIR"shader/27sl_fs.glsl", (char**)attlist);
	hr = LcDev_CreateEffectFromTxtFile(NULL, &m_pEft, m_pDev, &args);
	if(LC_FAILED(hr))
		return LC_EFAIL;




	MAKE_ARG4(args, (char*)MEDIA_DIR"tex/bg512x256.tga", (UINT)0, (UINT)0, (UINT)1);
	hr = LcDev_CreateTextureFromFile(NULL, &m_pTex, &args);
	if(LC_FAILED(hr))
		return LC_EFAIL;


	int scn = FBO_SCN_W;

	MAKE_ARG2(args, (int)scn, int(scn));

	hr = LcDev_CreateFBO(NULL, &m_pFbo, &args);
	if(LC_FAILED(hr))
		return LC_EFAIL;

	return LC_OK;
}

INT	CMain::Destroy()
{
	SAFE_RELEASE(	m_pTex	);
	SAFE_RELEASE(	m_pEft	);

	SAFE_RELEASE(	m_pFbo	);

	return LC_OK;
}



// Vertex Stream data
// position buffer
GLfloat vertexArray[8] =
{
	-0.97F, -0.95F,
	 0.97F, -0.95F,
	 0.97F,  0.95F,
	-0.97F,  0.95F,
};

// texture coordinate buffer
GLfloat texCoordArray[8] =
{
	0.0F,          1.0F - 240.0F/256.0F,
	320.0F/512.0F, 1.0F - 240.0F/256.0F,
	320.0F/512.0F, 1.0F,
	0.0F,          1.0F
};


LCXCOLOR color(2.0F, 2.0F, 2.0F, 1.0F);



INT	CMain::FrameMove()
{
	INT hr = 0;


#if defined(_WIN32)
	LcAux_Sleep(10);
#endif


	static INT c=0;
	++c;

	//	if(c>20*60*20)
	if(c>8*60*20)
	{
		printf("Game Process Terminated\n");
		return LC_EFAIL;
	}

	static INT n = 0;
	++n;

	float fps = (float)this->GetFPS();

	if(n>5)
	{
		printf("FPS: %3.f\n", fps);
		n = 0;
	}



	m_pFbo->Begin();
	{
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_pEft->Begin();


		UINT nTex = m_pTex->Oid();

		hr = m_pEft->Int	("un_tex", nTex);
		hr = m_pEft->Color  ("uv_Dif", &color);
		hr = m_pEft->Texture("us_tex", 0, nTex);

		glEnableVertexAttribArray(0);	glVertexAttribPointer(0, 2, GL_FLOAT, 0, 0, vertexArray);
		glEnableVertexAttribArray(1);	glVertexAttribPointer(1, 2, GL_FLOAT, 0, 0, texCoordArray);

		// Binding Texture
		glActiveTexture(GL_TEXTURE0);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, nTex);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glDrawArrays(GL_TRIANGLE_FAN, 0,4);

		// Unbinding texture...
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_TEXTURE_2D);


		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		m_pEft->End();
	}

	m_pFbo->End();

	return LC_OK;
}


INT	CMain::Render()
{
	INT hr = 0;

	LCXVECTOR3	scl(0.25F, 0.25F, 1.0F);

	glDisable( GL_DEPTH_TEST);		// disable depth test
	glDisable( GL_CULL_FACE );		// disalbe culling face

	glClearColor(0.9f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	PLC_TEXTURE	pTex = m_pFbo->ColorBuffer();

	m_pSpt->Begin();
	m_pSpt->Draw(pTex, NULL, NULL, &scl, NULL);

	m_pSpt->End();

	return LC_OK;
}




