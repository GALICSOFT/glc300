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

varying   vec4	vr_dif;

uniform   mat4	um_Wld;
uniform   mat4	um_Viw;
uniform   mat4	um_Prj;

uniform   vec4	uf_FogCol;		// Fog 색상
uniform   vec2	uf_FogRng;      // 시작: FogRng.x, 끝: Fog.y

void main()
{
	float f;

	vec4 pos = um_Wld * at_pos;
	pos = um_Viw * pos;

	f = -pos.z/(uf_FogRng.y - uf_FogRng.x);

	vr_dif = uf_FogCol * f;


	pos = um_Prj * pos;
	gl_Position = pos;
}

