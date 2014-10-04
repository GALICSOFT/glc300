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
attribute vec4	at_dif;
attribute vec2	at_tex;

varying   vec4	vr_dif;
varying   vec2	vr_tex;

uniform   mat4	uf_Prj;

void main()
{
	vec4 pos = uf_Prj * at_pos;
	gl_Position = pos;

	vr_dif = at_dif;
	vr_tex = at_tex;
}

