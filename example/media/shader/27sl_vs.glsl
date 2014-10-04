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

varying   vec4	vr_dif;
varying   vec2	vr_tex;

uniform   vec4	uv_Dif;

void main()
{
	vec4 pos = at_pos;
	gl_Position = pos;

	vr_dif = uv_Dif;
	vr_tex = at_tex;
}
