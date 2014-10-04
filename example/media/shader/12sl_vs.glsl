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
//attribute vec4	at_nor;
attribute vec3	at_nor;

varying   vec3	vr_nor;
varying   vec3	vr_hlf;

uniform   mat4	um_Wld;
uniform   mat4	um_Viw;
uniform   mat4	um_Prj;
uniform   mat4	um_Rot;

uniform   vec3	uf_cam;
uniform   vec3	uf_dir;

void main()
{
	vec4 pos = um_Wld * at_pos;
	//vec3 nor = vec3(um_Rot * at_nor);
	vec3 nor = vec3(um_Wld * vec4(at_nor,0.0));

	vec3 eye = vec3(pos);

	pos = um_Viw * pos;
	pos = um_Prj * pos;
	gl_Position = pos;

	nor = normalize(nor);

	vr_nor = nor;
	vr_hlf = normalize( normalize(uf_cam - eye) + uf_dir );
}

