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

varying	vec4	vr_dif;
varying	vec2	vr_tex;

uniform	int		un_tex;

uniform	sampler2D us_tex;

void main()
{
	vec4	col = vec4(1,1,1,1);

	if(0 <un_tex)
		col =texture2D(us_tex, vr_tex);

	gl_FragColor = col * vr_dif;
}
