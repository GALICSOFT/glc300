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

void main()
{
	//float	r;
	//r = vr_dif.r * 0.299 + vr_dif.g * 0.587 + vr_dif.b * 0.114;
	// Inversion
	//gl_FragColor = vec4(1.0 - vr_dif.r, 1.0 - vr_dif.g, 1.0 - vr_dif.b, vr_dif.a);

	// pow(dif,2) *2;
	gl_FragColor = vec4(  vr_dif.r * vr_dif.r
						, vr_dif.g * vr_dif.g
						, vr_dif.b * vr_dif.b
						, vr_dif.a) * 2.;
}
