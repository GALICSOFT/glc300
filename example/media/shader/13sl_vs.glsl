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
attribute	vec2	at_tex;

varying		vec2	vr_tex;

uniform		mat4	um_Wld;
uniform		mat4	um_Viw;
uniform		mat4	um_Prj;
uniform		float	uv_scl;

void main()
{
	vec4 pos = at_pos * uv_scl;
	pos.w = 1.0;
	pos = um_Wld * pos;
	pos = um_Viw * pos;
	pos = um_Prj * pos;
	gl_Position = pos;

	vr_tex = at_tex;
}

