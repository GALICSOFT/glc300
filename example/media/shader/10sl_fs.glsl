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

varying   vec2		vr_tex0;
varying   vec2		vr_tex1;

uniform sampler2D	uf_tex0;
uniform sampler2D	uf_tex1;

void main()
{
	vec4	ctx0 =texture2D(uf_tex0, vr_tex0);
	vec4	ctx1 =texture2D(uf_tex1, vr_tex1);

	gl_FragColor = (ctx0 + ctx1);
}

