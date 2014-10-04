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

attribute vec4      at_pos;
attribute vec2      at_tx0;

varying   vec2      vr_tx0;

void main()
{
	gl_Position = at_pos;
	vr_tx0 = at_tx0;
}
