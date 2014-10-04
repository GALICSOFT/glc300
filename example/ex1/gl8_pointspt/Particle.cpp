// Implementation of the CParticle class.
//
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <gles/gl2.h>

#include <LcType.h>
#include <LcBase.h>
#include <LcMath.h>
#include <LcEuclid.h>
#include <LcCore.h>
#include <LcAux.h>

#include "Particle.h"

//#define USE_OPENGL_ARG	1



CParticle::CParticle()
{
	m_pTex	= 0;

	m_PtcN	= 0;
	m_Ptc	= NULL;

	m_vtx	= NULL;

	memset(m_pEft, 0, sizeof(m_pEft));

	m_bHardware	= 0;
}


CParticle::~CParticle()
{
	Destroy();
}


void CParticle::Destroy()
{
	SAFE_DELETE_ARRAY(	m_Ptc	);

	SAFE_DELETE_ARRAY(	m_vtx	);

	SAFE_RELEASE(	m_pTex	);
}


int CParticle::Create(char* sTexture, int ParticleNumber)
{
	int	hr = 0;


	TLC_ARGS args;

	MAKE_ARG4(args, (char*)sTexture, 0, 0, (INT)1);
	hr = LcDev_CreateTextureFromFile(NULL, &m_pTex, &args);
	if(0>hr)
		return LC_EFAIL;
	



	m_PtcN = ParticleNumber;

	m_Ptc = new CParticle::Tptc[m_PtcN];
	m_vtx = new CParticle::VtxDUV[m_PtcN*3];


	for(int n=0; n<m_PtcN; ++n)
		InitPtc(n);

#if USE_OPENGL_ARG

	char* arb = "GL_ARB_point_sprite";
	char* ext = (char*)glGetString(GL_EXTENSIONS);
	char* dst = strstr(ext, "GL_ARB_point_sprite");

	if(dst)
	{
		printf("---------------\n ARB spec::device can be able to use the %s .\n\n", arb);
		m_bHardware = 1;
	}
	else
		printf("---------------\n ARB spec::device can't be able to use the %s .\n\n", arb);

#endif
	
	return LC_OK;
}


int CParticle::FrameMove()
{
	LCXMATRIX	mtPrj;
	FLOAT		pnt_size = 16;
	float		temp[16]={0};
	float		w, h;
	float		x, y;
	float		fsize;
	float		a;

	glGetFloatv(GL_VIEWPORT, temp);		// get viewport to set the screen width and height.
	w = temp[2];
	h = temp[3];



	for(int n=0; n<m_PtcN; ++n)
	{
		fsize = m_Ptc[n].size;

		x = m_Ptc[n].pos1.x;
		y = m_Ptc[n].pos1.y;

		x += m_Ptc[n].vec.x;
		y += m_Ptc[n].vec.y;


		a = m_Ptc[n].col.a;

		a -= 0.002F;


		m_Ptc[n].pos1.x = x;
		m_Ptc[n].pos1.y = y;
		m_Ptc[n].col.a  = a;


		m_vtx[n*3 + 0].p.x = x  -1.0F * fsize;
		m_vtx[n*3 + 0].p.y = y  -0.5F * fsize;
		m_vtx[n*3 + 1].p.x = x  +1.0F * fsize;
		m_vtx[n*3 + 1].p.y = y  -0.5F * fsize;
		m_vtx[n*3 + 2].p.x = x  -0.0F * fsize;
		m_vtx[n*3 + 2].p.y = y  +1.5F * fsize;

		m_vtx[n*3 + 0].d = m_Ptc[n].col;
		m_vtx[n*3 + 1].d = m_Ptc[n].col;
		m_vtx[n*3 + 2].d = m_Ptc[n].col;
		
		if(-h/2 >= m_Ptc[n].pos1.y || 0.F >= m_Ptc[n].col.a)
			InitPtc(n);
	}

	return LC_OK;
}

#define GL_POINT_SPRITE              0x8861
#define GL_VERTEX_PROGRAM_POINT_SIZE 0x8642 


void CParticle::Render()
{
	int hr = 0;


	//glDisable(GL_DEPTH_TEST);
	//glDepthMask(0);

	glEnable(GL_BLEND);
	glDisable(GL_CULL_FACE);

	// sum graphic card does not work on gl_PointCoord 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE);



	LCXMATRIX	mtPrj;
	FLOAT		pnt_size = 16;
	float		temp[16]={0};
	float		w, h;
	glGetFloatv(GL_VIEWPORT, temp);		// get viewport to set the screen width and height.
	w = temp[2];
	h = temp[3];

	mtPrj.OrthoGl(   -w/2, w/2
						, -h/2, h/2
						, -1.F, 1.F);



	if(m_bHardware)
	{
		glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);

		// sume device needs this...
		glEnable( GL_POINT_SPRITE );


		m_pEft[0]->Begin();

		m_pEft[0]->Matrix4("uf_Prj", &mtPrj);
		m_pEft[0]->Texture("uf_tex", 0, m_pTex);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(CParticle::Tptc), &(m_Ptc[0].pos1 ) );
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(CParticle::Tptc), &(m_Ptc[0].col  ) );
		glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(CParticle::Tptc), &(m_Ptc[0].size ) );


		m_pTex->BindTexture(0, LC_TRUE);

		glDrawArrays(GL_POINTS, 0, m_PtcN);


		m_pTex->BindTexture(0, LC_FALSE);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		m_pEft[0]->End();

		glDisable( GL_POINT_SPRITE );
		glDisable(GL_VERTEX_PROGRAM_POINT_SIZE);
	}

	else
	{
		m_pEft[1]->Begin();

		m_pEft[1]->Matrix4("uf_Prj", &mtPrj);
		m_pEft[1]->Texture("uf_tex", 0, m_pTex);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		glVertexAttribPointer(0, 2, GL_FLOAT        , GL_FALSE, sizeof(CParticle::VtxDUV), &(m_vtx[0].p));
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE , sizeof(CParticle::VtxDUV), &(m_vtx[0].d));
		glVertexAttribPointer(2, 2, GL_FLOAT        , GL_FALSE, sizeof(CParticle::VtxDUV), &(m_vtx[0].t));


		m_pTex->BindTexture(0, LC_TRUE, LC_TS_LINEAR, LC_TS_LINEAR, LC_TS_CLAMP, LC_TS_CLAMP);

		glDrawArrays(GL_TRIANGLES, 0, m_PtcN*3);


		m_pTex->BindTexture(0, LC_FALSE);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		m_pEft[1]->End();

	}

	glDepthMask(1);
	glEnable(GL_DEPTH_TEST);
}


void CParticle::InitPtc(int n)
{
	float   fsize = 0;
	float	temp[16]={0};
	float	w, h;
	float   x, y;

	glGetFloatv(GL_VIEWPORT, temp);
	w = temp[2];
	h = temp[3];


	fsize  = 8.0F + 0.4F * ( rand()%(m_PtcN+1) );
	fsize *= 2.0F;

	x = -w/2.0F + (rand()%(m_PtcN+1)) * w/m_PtcN;
	y = +h/2.0F + 0.1f*( rand()%(301) -100);

	m_Ptc[n].pos1.x = x;
	m_Ptc[n].pos1.y = y;

	m_Ptc[n].vec.x = 0;
	m_Ptc[n].vec.y = -(100 + rand()%(m_PtcN+1)) * 0.01F;

	m_Ptc[n].col.r = (128 + rand()%128)/255.F	;
	m_Ptc[n].col.g = (128 + rand()%128)/255.F	;
	m_Ptc[n].col.b = (128 + rand()%128)/255.F	;
	m_Ptc[n].col.a = (128 + rand()%128)/255.F	;

	m_Ptc[n].size  = fsize;


	m_vtx[n*3 + 0].p.x = x  -1.0F * fsize;
	m_vtx[n*3 + 0].p.y = y  -0.5F * fsize;
	m_vtx[n*3 + 1].p.x = x  +1.0F * fsize;
	m_vtx[n*3 + 1].p.y = y  -0.5F * fsize;
	m_vtx[n*3 + 2].p.x = x  -0.0F * fsize;
	m_vtx[n*3 + 2].p.y = y  +1.5F * fsize;

	m_vtx[n*3 + 0].d =  m_Ptc[n].col;
	m_vtx[n*3 + 1].d =  m_Ptc[n].col;
	m_vtx[n*3 + 2].d =  m_Ptc[n].col;

	m_vtx[n*3 + 0].t.x = -0.5F;
	m_vtx[n*3 + 0].t.y =  0.0F;
	m_vtx[n*3 + 1].t.x =  1.5F;
	m_vtx[n*3 + 1].t.y =  0.0F;
	m_vtx[n*3 + 2].t.x =  0.5F;
	m_vtx[n*3 + 2].t.y =  2.0F;

}


