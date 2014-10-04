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

varying   vec3		vr_nor;
varying   vec3		vr_hlf;

uniform   vec3		uf_dir;
uniform   vec4		uf_amb;
uniform   vec4		uf_dif;

void main()
{
	float	sharp = 30;

	vec4	col   = uf_dif;

	vec3	nor = normalize(vr_nor);
	vec3	hlf = normalize(vr_hlf);
	float	lam	= dot(uf_dir, nor) *0.5 + 0.52;
	float	spc = pow( (dot(nor, hlf) +1.0) * 0.49, sharp);

	col  *= lam;
	col  += (uf_amb + spc);

	gl_FragColor = col;
}

