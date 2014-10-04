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

uniform		int		un_nor;
uniform		int		un_dif;
uniform		int		un_tx0;
uniform		int		un_tx1;

void main()
{
	gl_Position = at_pos;

	vr_dif = vec4(1, 1, 1, 1);
	vr_nor = vec3(0,0,1);

	vr_tx0 = vec2(0,0);
	vr_tx1 = vec2(0,0);

	if(0 < un_dif)
		vr_dif = at_dif;

	if(0 < un_tx0)
	{
		vr_tx0 = at_tx0;
		vr_tx1 = at_tx0;
	}

	if(0 < un_tx1)
		vr_tx1 = at_tx1;
}

