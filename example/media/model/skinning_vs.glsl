// skinning - VERTEX SHADER

attribute	vec3	at_pos;
attribute	vec4	at_nor;
attribute	vec4	at_dif;
attribute	vec2	at_tx0;
attribute	vec2	at_tx1;
attribute	vec4	at_mti;
attribute	vec4	at_mtg;

varying	vec4	vr_dif;
varying	vec2	vr_tx0;
varying	vec2	vr_tx1;
varying	float	vr_fgw;

uniform	int		un_sc;
uniform	vec4	us_tc;
uniform	int		un_dif;
uniform	int		un_tx0;
uniform	int		un_tx1;

uniform	mat4	um_VP;

uniform	mat4	um_Bld[64];

void main()
{
	mat4	mtWld = mat4(1,0,0,0,  0,1,0,0,  0,0,1,0,  0,0,0,1);
	int		n = 0;

	vec4  pos = vec4(1);
	vec4  dif = vec4(1);
	vr_tx0 = vec2(0);
	vr_tx1 = vec2(0);


	if(0 <at_mtg.x){	n = int(at_mti.x);	mtWld  = um_Bld[n] * at_mtg.x; };
	if(0 <at_mtg.y){	n = int(at_mti.y);	mtWld += um_Bld[n] * at_mtg.y; };
	if(0 <at_mtg.z){	n = int(at_mti.z);	mtWld += um_Bld[n] * at_mtg.z; };
	if(0 <at_mtg.w){	n = int(at_mti.w);	mtWld += um_Bld[n] * at_mtg.w; };


	mtWld[3][3] = 1.0;

	pos = mtWld * vec4(at_pos, 1);

	pos.xyz *= 100.0;
	pos = um_VP * pos;

	gl_Position = pos;




	if(0< un_dif)
		dif = at_dif;

	if(0< un_tx0)
	{
		vr_tx0 = at_tx0;
		vr_tx1 = at_tx0;
	}

	if(0< un_tx1)
		vr_tx1 = at_tx1;

	if     (1 ==un_sc) dif *= us_tc;
	else if(2 ==un_sc) dif += us_tc;
	else if(3 ==un_sc) dif= us_tc - dif;
	else if(4 ==un_sc) dif= dif+us_tc-dif*us_tc;
	else if(5 ==un_sc) dif= us_tc;
	vr_dif = dif;
}

