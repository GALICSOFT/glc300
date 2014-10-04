// Implementation of the CMain class.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


#define MEDIA_DIR	"../../media/"



INT MyEft2D1::Init(LC_HANDLE _init)
{
	TXDSC_EPS* init = (TXDSC_EPS*)_init;

	float	width = float( (50 + rand()%100) * 0.1);

	float	theta = float(-90 + -10 + rand()%21);
	float	Cos   = 0;
	float	Sin   = 0;

	float	Speed  = float( (50 + rand()%200) * 0.0125);

	pos   = init->tm_pos;
	pos.x+= rand()%20;

	theta = LCXToRadian(theta);
	Cos   = LCXMathCos(theta);
	Sin   = LCXMathSin(theta);


	float r = init->it_dif.r;
	float g = init->it_dif.g;
	float b = init->it_dif.b;

	if(r >g && r >b)
	{
		dif.r = (200 + rand()%56)/255.F	;
		dif.g = ( 50 + rand()%50)/255.F	;
		dif.b = 0;
	}
	else
	{
		dif.b = (200 + rand()%56)/255.F	;
		dif.g = ( 50 + rand()%50)/255.F	;
		dif.r = 0;
	}

	dif.a = (128 + rand()%128)/255.F	;

	vlc.x = Speed * Cos;
	vlc.y = Speed * Sin;

	//acc.y = 0.04F;

	clv.a= -float((100 + rand()%101) * 0.0001);

	mag   = LCXVECTOR2(width*init->it_mag.x, width*init->it_mag.y);
	life  = 1.0F;

	return 0;
}

INT MyEft2D1::Reset(LC_HANDLE _init)
{
	TXDSC_EPS* init = (TXDSC_EPS*)_init;

	float	width = float( (50 + rand()%100) * 0.1);

	float	theta = float(-90 + -10 + rand()%21);
	float	Cos   = 0;
	float	Sin   = 0;

	float	Speed  = float( (50 + rand()%200) * 0.0125);

	pos   = init->tm_pos;
	pos.x+= rand()%20;

	theta = LCXToRadian(theta);
	Cos   = LCXMathCos(theta);
	Sin   = LCXMathSin(theta);

	float r = init->it_dif.r;
	float g = init->it_dif.g;
	float b = init->it_dif.b;


	if(r >g && r >b)
	{
		dif.r = (200 + rand()%56)/255.F	;
		dif.g = ( 50 + rand()%50)/255.F	;
		dif.b = 0;
	}
	else
	{
		dif.b = (200 + rand()%56)/255.F	;
		dif.g = ( 50 + rand()%50)/255.F	;
		dif.r = 0;
	}

	dif.a = (128 + rand()%128)/255.F	;

	vlc.x = Speed * Cos;
	vlc.y = Speed * Sin;

	//acc.y = 0.04F;

	clv.a= -float((100 + rand()%101) * 0.0001);

	mag   = LCXVECTOR2(width*init->it_mag.x, width*init->it_mag.y);
	life  = 1.0F;

	return 0;
}


INT MyEft2D1::Update(LC_HANDLE _init)
{
	TXDSC_EPS* init = (TXDSC_EPS*)_init;
	DOUBLE elapsed = 0;

	LcVar_TimeElapsed(&elapsed);
	elapsed *= 0.05;

	vlc  += acc* FLOAT(elapsed);
	pos  += vlc* FLOAT(elapsed);
	dif  += clv* FLOAT(elapsed);

	// boundary
	LCXRECT* pRct = (LCXRECT*)&init->rc_bnd;

	if( LC_OK != pRct->IsInRect((FLOAT*)&pos) || 0.F >= dif.a)
	{
		life  = 0.0F;
		Reset(init);
	}

	return 0;
}


//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8

INT MyEft2D2::Init(LC_HANDLE _init)
{
	TXDSC_EPS* init = (TXDSC_EPS*)_init;

	float	width = float( (50 + rand()%100) * 0.05);

	float	theta = float(-90 + -30 + rand()%61);
	float	Cos   = 0;
	float	Sin   = 0;

	float	Speed  = float( (50 + rand()%200) * 0.05);

	pos   = init->tm_pos;
	pos.x+= rand()%20;

	theta = LCXToRadian(theta);
	Cos   = LCXMathCos(theta);
	Sin   = LCXMathSin(theta);

	dif.r = (100 + rand()%56 )/255.F	;
	dif.g = (200 + rand()%56 )/255.F	;
	dif.b = (200 + rand()%56 )/255.F	;
	dif.a = (128 + rand()%128)/255.F	;

	vlc.x = Speed * Cos;
	vlc.y = Speed * Sin;

	acc.y = 0.1F;

	clv.a= -float((100 + rand()%101) * 0.0001);

	mag   = LCXVECTOR2(width*init->it_mag.x, width*init->it_mag.y);
	life  = 1.0F;

	return 0;
}


INT MyEft2D2::Reset(LC_HANDLE _init)
{
	TXDSC_EPS* init = (TXDSC_EPS*)_init;

	float	width = float( (50 + rand()%100) * 0.05);

	float	theta = float(-90 + -30 + rand()%61);
	float	Cos   = 0;
	float	Sin   = 0;

	float	Speed  = float( (50 + rand()%200) * 0.05);

	pos   = init->tm_pos;
	pos.x+= rand()%20;

	theta = LCXToRadian(theta);
	Cos   = LCXMathCos(theta);
	Sin   = LCXMathSin(theta);

	dif.r = (100 + rand()%56 )/255.F	;
	dif.g = (200 + rand()%56 )/255.F	;
	dif.b = (200 + rand()%56 )/255.F	;
	dif.a = (128 + rand()%128)/255.F	;

	vlc.x = Speed * Cos;
	vlc.y = Speed * Sin;

	acc.y = 0.1F;

	clv.a= -float((100 + rand()%101) * 0.0001);

	mag   = LCXVECTOR2(width*init->it_mag.x, width*init->it_mag.y);
	life  = 1.0F;

	return 0;
}


INT MyEft2D2::Update(LC_HANDLE _init)
{
	TXDSC_EPS* init = (TXDSC_EPS*)_init;
	DOUBLE elapsed = 0;

	LcVar_TimeElapsed(&elapsed);
	elapsed *= 0.05;

	vlc  += acc* FLOAT(elapsed);
	pos  += vlc* FLOAT(elapsed);
	dif  += clv* FLOAT(elapsed);

	// boundary
	LCXRECT* pRct = (LCXRECT*)&init->rc_bnd;

	if( LC_OK != pRct->IsInRect((FLOAT*)&pos) || 0.F >= dif.a)
	{
		life  = 0.0F;
		Reset(init);
	}

	return 0;
}


//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8

INT MyEft2D3::Init(LC_HANDLE _init)
{
	TXDSC_EPS* init = (TXDSC_EPS*)_init;

	// boundary
	LCXRECT* pRct = (LCXRECT*)&init->rc_bnd;

	int		PtcN = init->prt_num;
	float	width = (200 + rand()%(PtcN+1)) * 0.02F;
	float	scnW = pRct->w;

	pos.x = (rand()%(PtcN+1)) * scnW/PtcN;
	pos.y = -300.F + rand()%(301);

	dif.r = 1.F	;
	dif.g = 1.F	;
	dif.b = 1.F	;
	dif.a = (128 + rand()%128)/255.F	;

	vlc.x = 0;
	vlc.y = (100 + rand()%(PtcN+1)) * 0.01F;
	clv  = LCXCOLOR(0,0,0,-0.004F);

	mag   = LCXVECTOR2(width*init->it_mag.x, width*init->it_mag.y);

	return 0;
}


INT MyEft2D3::Reset(LC_HANDLE _init)
{
	TXDSC_EPS* init = (TXDSC_EPS*)_init;

	pos.y = -300.F + rand()%(301);
	dif.a = (128 + rand()%128)/255.F	;

	life  = 1.0F;

	return 0;
}


INT MyEft2D3::Update(LC_HANDLE _init)
{
	TXDSC_EPS* init = (TXDSC_EPS*)_init;
	DOUBLE elapsed = 0;

	LcVar_TimeElapsed(&elapsed);
	elapsed *= 0.05;

	pos  += vlc* FLOAT(elapsed);
	dif  += clv* FLOAT(elapsed);

	// boundary
	if(800 < pos.y || 0.F >= dif.a)
	{
		life  = 0.0F;
		Reset(init);
	}

	return 0;
}


//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8
//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8

INT MyEft3D1::Init(LC_HANDLE _init)
{
	TXDSC_EPS* init = (TXDSC_EPS*)_init;

	float	width = float( (50 + rand()%51) * 0.01);

	float	theta = (-10 + rand()%21) * 2.0F;
	float	Cos   = 0;
	float	Sin   = 0;

	float	Speed  = float( (50 + rand()%200) * 0.001);

	pos   = LCXVECTOR3(0,0,0);
	pos.x+= (rand()%20) * 0.05F;

	theta = LCXToRadian(theta);
	Cos   = LCXMathCos(theta);
	Sin   = LCXMathSin(theta);


	float r = init->it_dif.r;
	float g = init->it_dif.g;
	float b = init->it_dif.b;

	if(r >g && r >b)
	{
		dif.r = (200 + rand()%56)/255.F	;
		dif.g = ( 50 + rand()%50)/255.F	;
		dif.b = 0;
	}
	else
	{
		dif.b = (200 + rand()%56)/255.F	;
		dif.g = ( 50 + rand()%50)/255.F	;
		dif.r = 0;
	}

	dif.a = (128 + rand()%128)/255.F	;

	vlc.x = Speed * Sin;
	vlc.z = Speed * Cos;

	//acc.z = -0.01F;

	clv.a= -float((100 + rand()%101) * 0.0001);

	mag   = LCXVECTOR2(width*init->it_mag.x, width*init->it_mag.y);
	life  = 1.0F;

	return 0;
}

INT MyEft3D1::Reset(LC_HANDLE _init)
{
	TXDSC_EPS* init = (TXDSC_EPS*)_init;

	float	width = float( (50 + rand()%51) * 0.01);

	float	theta = (-10 + rand()%21) * 2.0F;
	float	Cos   = 0;
	float	Sin   = 0;

	float	Speed  = float( (50 + rand()%200) * 0.001);

	pos   = LCXVECTOR3(0,0,0);
	pos.x+= (rand()%20) * 0.05F;

	theta = LCXToRadian(theta);
	Cos   = LCXMathCos(theta);
	Sin   = LCXMathSin(theta);

	float r = init->it_dif.r;
	float g = init->it_dif.g;
	float b = init->it_dif.b;


	if(r >g && r >b)
	{
		dif.r = (200 + rand()%56)/255.F	;
		dif.g = ( 50 + rand()%50)/255.F	;
		dif.b = 0;
	}
	else
	{
		dif.b = (200 + rand()%56)/255.F	;
		dif.g = ( 50 + rand()%50)/255.F	;
		dif.r = 0;
	}

	dif.a = (128 + rand()%128)/255.F	;

	vlc.x = Speed * Sin;
	vlc.z = Speed * Cos;

	//acc.z = -0.01F;

	clv.a= -float((100 + rand()%101) * 0.0001);

	mag   = LCXVECTOR2(width*init->it_mag.x, width*init->it_mag.y);
	life  = 1.0F;

	return 0;
}


INT MyEft3D1::Update(LC_HANDLE _init)
{
	TXDSC_EPS* init = (TXDSC_EPS*)_init;
	DOUBLE elapsed = 0;

	LcVar_TimeElapsed(&elapsed);
	elapsed *= 0.05;

	vlc  += acc* FLOAT(elapsed);
	pos  += vlc* FLOAT(elapsed);
	dif  += clv* FLOAT(elapsed);

	// boundary
	LCXRECT* pRct = (LCXRECT*)&init->rc_bnd;

	if( 0.F >= dif.a)
	{
		life  = 0.0F;
		Reset(init);
	}

	return 0;
}


//++5++++1+++++++++2+++++++++3+++++++++4+++++++++5+++++++++6+++++++++7+++++++++8

INT MyEft3D2::Init(LC_HANDLE _init)
{
	TXDSC_EPS* init = (TXDSC_EPS*)_init;

	float	width = float( (50 + rand()%51) * 0.01);

	float	theta = float(-30 + rand()%61);
	float	CosT   = 0;
	float	SinT   = 0;

	float	phi    = float(rand()%360);
	float	CosP   = 0;
	float	SinP   = 0;


	float	Speed  = (50 + rand()%200) * 0.005F;

	pos   = LCXVECTOR3(0,0,0);
	pos.x+= (rand()%20) * 0.01F;

	theta = LCXToRadian(theta);
	CosT  = LCXMathCos(theta);
	SinT  = LCXMathSin(theta);

	phi   = LCXToRadian(phi);
	CosP  = LCXMathCos(phi);
	SinP  = LCXMathSin(phi);



	dif.r = (100 + rand()%56 )/255.F	;
	dif.g = (200 + rand()%56 )/255.F	;
	dif.b = (200 + rand()%56 )/255.F	;
	dif.a = (128 + rand()%128)/255.F	;

	vlc.x = Speed * SinT * CosP;
	vlc.y = Speed * SinT * SinP;
	vlc.z = Speed * CosT;

	acc.z = -0.01F;

	clv.a= -float((100 + rand()%101) * 0.0001);

	mag   = LCXVECTOR2(width*init->it_mag.x, width*init->it_mag.y);
	life  = 1.0F;

	return 0;
}


INT MyEft3D2::Reset(LC_HANDLE _init)
{
	TXDSC_EPS* init = (TXDSC_EPS*)_init;

	float	width = float( (50 + rand()%51) * 0.01);

	float	theta = float(-30 + rand()%61);
	float	CosT   = 0;
	float	SinT   = 0;

	float	phi    = float(rand()%360);
	float	CosP   = 0;
	float	SinP   = 0;

	float	Speed  = (50 + rand()%200) * 0.005F;

	pos   = LCXVECTOR3(0,0,0);
	pos.x+= (rand()%20) * 0.01F;

	theta = LCXToRadian(theta);
	CosT  = LCXMathCos(theta);
	SinT  = LCXMathSin(theta);

	phi   = LCXToRadian(phi);
	CosP  = LCXMathCos(phi);
	SinP  = LCXMathSin(phi);

	dif.r = (100 + rand()%56 )/255.F	;
	dif.g = (200 + rand()%56 )/255.F	;
	dif.b = (200 + rand()%56 )/255.F	;
	dif.a = (128 + rand()%128)/255.F	;

	vlc.x = Speed * SinT * CosP;
	vlc.y = Speed * SinT * SinP;
	vlc.z = Speed * CosT;

	acc.z = -0.01F;

	clv.a= -float((100 + rand()%101) * 0.0001);

	mag   = LCXVECTOR2(width*init->it_mag.x, width*init->it_mag.y);
	life  = 1.0F;

	return 0;
}


INT MyEft3D2::Update(LC_HANDLE _init)
{
	TXDSC_EPS* init = (TXDSC_EPS*)_init;
	DOUBLE elapsed = 0;

	LcVar_TimeElapsed(&elapsed);
	elapsed *= 0.05;


	vlc  += acc* FLOAT(elapsed);
	pos  += vlc* FLOAT(elapsed);
	dif  += clv* FLOAT(elapsed);

	// boundary
	LCXRECT* pRct = (LCXRECT*)&init->rc_bnd;

	if( 0 > pos.z || 0.F >= dif.a)
	{
		life  = 0.0F;
		Reset(init);
	}

	return 0;
}

