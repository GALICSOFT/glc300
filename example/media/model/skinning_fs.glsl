// Vertex blending - PIXEL SHADER: same to general pixel shader

varying	vec4	vr_dif;								//  1
varying	vec2	vr_tx0;								//  2
varying	vec2	vr_tx1;								//  3
varying	float	vr_fgw;								//  4
													//  5
uniform	vec4	un_fgc;								//  6
uniform	int		un_tx0;								//  7
uniform	int		un_tx1;								//  8
													//  9
uniform	int		un_s0;								// 10
uniform	int		un_s1;								//  1
uniform	int		un_s2;								//  2
uniform	int		un_s3;								//  3
													//  4
uniform	sampler2D us_t0;							//  5
uniform	sampler2D us_t1;							//  6
uniform	sampler2D us_t2;							//  7
uniform	sampler2D us_t3;							//  8
													//  9
void main() {										// 20
	vec4 ret = vr_dif;								//  1
	vec4 ct0 = vec4(0,0,0,1);						//  2
	vec4 ct1 = vec4(0,0,0,1);						//  3
	vec4 ct2 = vec4(0,0,0,1);						//  4
	vec4 ct3 = vec4(0,0,0,1);						//  5
													//  6
	if(0< un_tx0){									//  7
		if(0< un_s0)								//  8
			ct0 = texture2D(us_t0, vr_tx0);			//  9
													// 30
		if(0< un_s1 && 0 == un_tx1)					//  1
			ct1 = texture2D(us_t1, vr_tx0);			//  2
													//  3
		if(0< un_s2)								//  4
			ct2 = texture2D(us_t2, vr_tx0);			//  5
													//  6
		if(0< un_s3)								//  7
			ct3 = texture2D(us_t3, vr_tx0);			//  8
	}												//  9
	if(0< un_tx1)									// 40
			ct1 = texture2D(us_t1, vr_tx1);			//  1
													//  2
	if     (1 ==un_s0) ret *= ct0;					//  3
	else if(2 ==un_s0) ret += ct0;					//  4
	else if(3 ==un_s0) ret -= ct0;					//  5
	else if(4 ==un_s0) ret  = ret+ct0 - ret*ct0;	//  6
	else if(5 ==un_s0) ret  = ct0;					//  7
													//  8
	if     (1 ==un_s1) ret *= ct1;					//  9
	else if(2 ==un_s1) ret += ct1;					// 50
	else if(3 ==un_s1) ret -= ct1;					//  1
	else if(4 ==un_s1) ret  = ret+ct1 - ret*ct1;	//  2
	else if(5 ==un_s1) ret  = ct1;					//  3
													//  4
	if     (1 ==un_s2) ret *= ct2;					//  5
	else if(2 ==un_s2) ret += ct2;					//  6
	else if(3 ==un_s2) ret -= ct2;					//  7
	else if(4 ==un_s2) ret  = ret+ct2 - ret*ct2;	//  8
	else if(5 ==un_s2) ret  = ct2;					//  9
													// 60
	if     (1 ==un_s3) ret *= ct3;					//  1
	else if(2 ==un_s3) ret += ct3;					//  2
	else if(3 ==un_s3) ret -= ct3;					//  3
	else if(4 ==un_s3) ret  = ret+ct3 - ret*ct3;	//  4
	else if(5 ==un_s3) ret  = ct3;					//  5
													//  6
	if(0<un_fgc.a){									//  7
		ret.rgb = (1.0 - vr_fgw) * ret.rgb			//  8
				+ vr_fgw * un_fgc.rgb;				//  9
	}												// 70
	gl_FragColor = ret;								//  1
}													//  2