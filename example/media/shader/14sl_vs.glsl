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

varying   vec2	vr_tex;

uniform   mat4	uf_Wld;
uniform   mat4	uf_Prj;

void main()
{
	vec4 pos = uf_Wld * at_pos;
	pos = uf_Prj * pos;
	gl_Position = pos;

	vr_tex = at_tex;
}

