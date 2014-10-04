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

varying vec2		vr_tx0;
varying vec2		vr_tx1;

uniform sampler2D	uf_tex0;
uniform sampler2D	uf_tex1;

uniform vec4		uv_Dif;		// glcolor4f
uniform float		uf_mode;	// blending mode

void main()
{
	vec4	col = vec4(1,1,1,1);
	vec4	ctx0 =texture2D(uf_tex0, vr_tx0);
	vec4	ctx1 =texture2D(uf_tex1, vr_tx1);

	if     (1.0 == uf_mode)
		col = (ctx1 * ctx0);				// modulate

	else if(2.0 == uf_mode)
		col = (ctx1 + ctx0);				// add

	else if(3.0 == uf_mode)
		col = (ctx1 - ctx0);				// sub

	else if(4.0 == uf_mode)
		col = (ctx1 + ctx0 - ctx1 * ctx0);	// add signed


	col *= uv_Dif;		// modulate
	col.a = 1.0;

	gl_FragColor = col;
}

