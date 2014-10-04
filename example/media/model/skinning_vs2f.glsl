attribute	vec3	at_pos;							//  1
attribute	vec3	at_nor;							//  2
attribute	vec4	at_dif;							//  3
attribute	vec2	at_tx0;							//  4
attribute	vec2	at_tx1;							//  5
attribute	vec4	at_igt;							//  6
													//  7
varying	vec4		vr_dif;							//  8
varying	vec2		vr_tx0;							//  9
varying	vec2		vr_tx1;							// 10
varying	float		vr_fgw;							//  1
													//  2
uniform	int			un_sc;							//  3
uniform	vec4		us_tc;							//  4
uniform	int			un_dif;							//  5
uniform	int			un_tx0;							//  6
uniform	int			un_tx1;							//  7
uniform	int			un_bln;							//  8
													//  9
uniform	mat4		um_Wld;							// 20
uniform	mat4		um_WVP;							//  1
uniform	mat4		um_Rot;							//  2
													//  3
uniform	int			un_lgt;							//  4
uniform	vec3		un_cap;							//  5
uniform	vec3		un_caz;							//  6
uniform	vec3		un_fgr;							//  7
													//  8
uniform	vec3		un_lam;							//  9
uniform	vec4		un_ldr[4];						// 30
uniform	vec3		un_ldf[4];						//  1
uniform	vec4		un_lsp[4];						//  2
													//  3
uniform float	uk_Cos[64];							//  4
uniform float	uk_Sin[64];							//  5
uniform vec3	uk_Axs[64];							//  6
uniform vec3	uk_Trn[64];							//  7
													//  8
void main() {										//  9
	vec3  pos  = vec3(0);							// 40
	vec3  pos2 = vec3(0);							//  1
	vec3  nor  = vec3(0);							//  2
	vec3  nor2 = vec3(0);							//  3
	vec3  axs  = vec3(0);							//  4
													//  5
	vec4  dif = vec4(1);							//  6
	vec3  eye = vec3(0);							//  7
	vec3  lam = vec3(0);							//  8
	vec3  Lam = vec3(0);							//  9
	vec3  Spc = vec3(0);							// 50
	vec3  hlf = vec3(0);							//  1
	vec3  lgt = vec3(0);							//  2
	float tmp = 0;									//  3
	int     n = 0;									//  4
															//  5
	if(0<un_bln) {											//  6
		n = int(at_igt.x);									//  7
		tmp = at_igt.z;										//  8
															//  9
		axs  = uk_Axs[n];									// 60
		pos  = uk_Cos[n]* at_pos;							//  1
		nor  = uk_Cos[n]* at_nor;							//  2
															//  3
		pos += uk_Sin[n]* cross(at_pos, axs);				//  4
		nor += uk_Sin[n]* cross(at_nor, axs);				//  5
															//  6
		pos += (1.0- uk_Cos[n])* dot(at_pos, axs)* axs;		//  7
		nor += (1.0- uk_Cos[n])* dot(at_nor, axs)* axs;		//  8
															//  9
		pos += uk_Trn[n];									//  0
		nor += uk_Trn[n];									// 71
															//  2
		pos *= tmp;											//  3
		nor *= tmp;											//  4
															//  5
		n = int(at_igt.y);									//  6
		tmp = 1.0 - tmp;									//  7
		if(0<= n && 0<tmp) {								//  8
			axs   = uk_Axs[n];								//  9
			pos2  = uk_Cos[n]* at_pos;						// 80
			nor2  = uk_Cos[n]* at_nor;						//  1
															//  2
			pos2 += uk_Sin[n]* cross(at_pos,axs);			//  3
			nor2 += uk_Sin[n]* cross(at_nor,axs);			//  4
															//  5
			pos2 += (1.0-uk_Cos[n])* dot(at_pos,axs)* axs;	//  6
			nor2 += (1.0-uk_Cos[n])* dot(at_nor,axs)* axs;	//  7
															//  8
			pos2 += uk_Trn[n];								//  9
			nor2 += uk_Trn[n];								// 90
															//  1
			pos2 *= tmp;									//  2
			nor2 *= tmp;									//  3
															//  4
			pos  += pos2;									//  5
			nor  += nor2;									//  6
		}													//  7
															//  8
		nor = normalize(nor);								//  9
		eye = un_cap - vec3(pos);							// 00
		gl_Position = um_WVP * vec4(pos,1);					//  1
	}														//  2
															//  3
	else {													//  4
		gl_Position = um_WVP * vec4(at_pos,1);				//  5
		pos = vec3(um_Wld * vec4(at_pos,1) );				//  6
															//  7
		nor = normalize(vec3(um_Rot* vec4(at_nor,1)));		//  8
		eye = un_cap - vec3(pos);							//  9
	}														// 10
															//  1
	tmp = dot(eye, un_caz);									//  2
															//  3
	vr_fgw = 0.0;											//  4
	if(0<un_fgr.z) {										//  5
	if(tmp<= un_fgr.x)	vr_fgw = 0.0;						//  6
	else if(tmp>= un_fgr.y) vr_fgw = 1.0;					//  7
	else vr_fgw = (tmp-un_fgr.x)/(un_fgr.y-un_fgr.x);		//  8
	vr_fgw = pow(vr_fgw, un_fgr.z);							//  9
	}														//  0
															// 21
	eye = normalize(eye);									//  2
															//  3
	vr_tx0 = vec2(0);										//  4
	vr_tx1 = vec2(0);										//  5
	if(0 < un_tx0)											//  6
	{														//  7
		vr_tx0 = at_tx0;									//  8
		vr_tx1 = at_tx0;									//  9
	}														//  0
	if(0 < un_tx1)											// 31
		vr_tx1 = at_tx1;									//  2
															//  3
	if     (0< un_dif) dif = at_dif;						//  4
	if     (1 ==un_sc) dif *= us_tc;						//  5
	else if(2 ==un_sc) dif += us_tc;						//  6
	else if(3 ==un_sc) dif = us_tc - dif;					//  7
	else if(4 ==un_sc) dif = dif+us_tc - dif*us_tc;			//  8
	else if(5 ==un_sc) dif = us_tc;							//  9
															//  0
	vr_dif = dif;											// 41
	if(0<un_lgt){											//  2
	for(n=0; n<4; ++n){										//  3
		if( 0.0 == un_ldr[n].w) continue;					//  4
		tmp  = dot(nor, -vec3(un_ldr[n]));					//  5
		tmp += 1.0;											//  6
		tmp *= 0.44;										//  7
		Lam +=  tmp*un_ldf[n];								//  8
															//  9
		hlf = normalize(eye - vec3(un_ldr[n]));				//  0
		tmp  = clamp(dot(hlf, nor), 0.0, 1.0);				// 51
		tmp  = pow(tmp, un_lsp[n].w*100.0);					//  2
		Spc += tmp*vec3(un_lsp[n]);							//  3
	}														//  4
															//  5
	lgt = un_lam + Spc;										//  6
	vr_dif = dif * vec4(Lam, 1) +vec4(lgt, 0);				//  7
	}														//  8
}															//  9
