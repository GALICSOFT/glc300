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

attribute vec4	at_pos;
attribute vec2	at_tex;

varying   vec2	vr_tex0;
varying   vec2	vr_tex1;

uniform   mat4	um_Wld;
uniform   mat4	um_Viw;
uniform   mat4	um_Prj;
uniform   mat4	um_Tex;

void main()
{
	vec4 pos = um_Wld * at_pos;
	pos = um_Viw * pos;
	pos = um_Prj * pos;

	gl_Position = pos;

	vec4 t_tex = vec4(at_tex, 0, 1);

	t_tex = um_Tex * t_tex;

	vr_tex0 = at_tex;
	vr_tex1.xy = t_tex.xy;
}

