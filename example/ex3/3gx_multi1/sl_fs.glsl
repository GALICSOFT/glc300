// fragment shader.
//
// Copyright (c) GALICSOFT Inc. All rights reserved.
// Author: Heesung Oh (afewhee@hotmail.com)
// Date: 2009-08-04
//
///////////////////////////////////////////////////////////////////////////////


#ifdef GL_ES
precision mediump	float;
#endif

varying   vec2      vr_tx0;

uniform   sampler2D us_t0;
uniform   sampler2D us_t1;

void main()
{
	vec4 ret = vec4(1.0, 1.0, 1.0, 1.0);
	vec4 ct0 =texture2D(us_t0, vr_tx0);
	vec4 ct1 =texture2D(us_t1, vr_tx0);

	ret.rgb = ct0.rgb * (1.0 - ct1.a) + ct1.rgb * ct1.a;
	ret.a = clamp( ct0.a + ct1.a, 0.0, 1.0);

	gl_FragColor = ret;
}

