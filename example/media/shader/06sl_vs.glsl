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

varying   vec4	vr_dif;

uniform   mat4	um_Wld;
uniform   mat4	um_Viw;
uniform   mat4	um_Prj;

void main()
{
	vec4 pos = um_Wld * at_pos;
	pos = um_Viw * pos;
	pos = um_Prj * pos;
	gl_Position = pos;

	vr_dif = at_dif;
}
