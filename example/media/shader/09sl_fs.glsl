// fragment shader.
//
// Copyright (c) GALICSOFT Inc. All rights reserved.
// Author: Heesung Oh (afewhee@hotmail.com)
// Date: 2009-08-04
//
///////////////////////////////////////////////////////////////////////////////

#ifdef GL_ES
precision mediump float;
#endif

#define MUL		1
#define ADD		2
#define SUB		3
#define ADS		4

varying		vec4		vr_pos;
varying		vec3		vr_nor;
varying		vec4		vr_dif;
varying		vec2		vr_tx0;
varying		vec2		vr_tx1;

uniform		int			un_nor;
uniform		int			un_dif;	// blending operation 0-stage diffuse and t-factor color
uniform		int			un_tx0;
uniform		int			un_tx1;

uniform		int			un_sc;	// t-factor color operation with vr_dif on 0-state
uniform		int			un_s0;	// blending operation 0-stage
uniform		int			un_s1;	// blending operation 1-stage
uniform		int			un_s2;	// blending operation 2-stage
uniform		int			un_s3;	// blending operation 3-stage

uniform		vec4		us_tc;	// t-factor color
uniform		sampler2D	us_t0;	// texturing sampler 0
uniform		sampler2D	us_t1;	// texturing sampler 1
uniform		sampler2D	us_t2;	// texturing sampler 2
uniform		sampler2D	us_t3;	// texturing sampler 3

void main()
{
	vec4	ret = vr_dif;
	vec4	ct0 = vec4(0,0,0,1);
	vec4	ct1 = vec4(0,0,0,1);
	vec4	ct2 = vec4(0,0,0,1);
	vec4	ct3 = vec4(0,0,0,1);

	// sampling
	if(1 == un_tx0)
	{
		if(0 < un_s0)
			ct0 = texture2D(us_t0, vr_tx0);

		if(0 < un_s1 && 0 == un_tx1)
			ct1 = texture2D(us_t1, vr_tx0);

		if(0 < un_s2)
			ct2 = texture2D(us_t2, vr_tx0);

		if(0 < un_s3)
			ct3 = texture2D(us_t3, vr_tx0);
	}

	if(0 < un_tx1)
		ct1 = texture2D(us_t1, vr_tx1);

	// op with t-factor
	if     (MUL == un_sc) ret *= us_tc;
	else if(ADD == un_sc) ret += us_tc;
	else if(SUB == un_sc) ret  = us_tc - ret;
	else if(ADS == un_sc) ret  = ret + us_tc - ret*us_tc;

	// op with 0-stage texture
	if     (MUL == un_s0) ret *= ct0;
	else if(ADD == un_s0) ret += ct0;
	else if(SUB == un_s0) ret  = ct0 - ret;
	else if(ADS == un_s0) ret  = ret + ct0 - ret*ct0;

	// op with 1-stage texture
	if     (MUL == un_s1) ret *= ct1;
	else if(ADD == un_s1) ret += ct1;
	else if(SUB == un_s1) ret  = ct1 - ret;
	else if(ADS == un_s1) ret  = ret + ct1 - ret*ct1;

	// op with 2-stage texture
	if     (MUL == un_s2) ret *= ct2;
	else if(ADD == un_s2) ret += ct2;
	else if(SUB == un_s2) ret  = ct2 - ret;
	else if(ADS == un_s2) ret  = ret + ct2 - ret*ct2;

	// op with 3-stage texture
	if     (MUL == un_s3) ret *= ct3;
	else if(ADD == un_s3) ret += ct3;
	else if(SUB == un_s3) ret  = ct3 - ret;
	else if(ADS == un_s3) ret  = ret + ct3 - ret*ct3;

	gl_FragColor = ret;
}
