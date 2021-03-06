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

varying vec4		vr_dif;

uniform sampler2D	uf_tex;	// sampler

void main()
{
	vec4 ctx =texture2D(uf_tex, gl_PointCoord);

	gl_FragColor = ctx * vr_dif;
}
