// vertex shader.
//
// Copyright (c) GALICSOFT Inc. All rights reserved.
// Author: Heesung Oh (afewhee@hotmail.com)
// Date: 2009-08-04
//
///////////////////////////////////////////////////////////////////////////////

#ifdef GL_ES
precision mediump float;
#endif

attribute	vec4	at_pos;
attribute	vec3	at_nor;
attribute	vec4	at_dif;
attribute	vec2	at_tx0;
attribute	vec2	at_tx1;

varying		vec3	vr_nor;
varying		vec4	vr_dif;
varying		vec2	vr_tx0;
varying		vec2	vr_tx1;

void main()
{
	gl_Position = at_pos;

	vr_tx0 = at_tx0;
	vr_tx1 = 2*at_tx0;
}
