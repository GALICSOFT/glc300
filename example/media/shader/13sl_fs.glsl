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

varying	vec2		vr_tex;

uniform	sampler2D	uf_tex;
uniform	vec4		uf_dif;

void main()
{
	vec4	ctx =texture2D(uf_tex, vr_tex);

	ctx *= uf_dif;

	if(0.15 > ctx.a)
		discard;

	gl_FragColor = ctx;
}

