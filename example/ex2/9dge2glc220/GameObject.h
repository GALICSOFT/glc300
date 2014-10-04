// GLC 2.0 Tutorial Example
//
// Interface for Main GameObject Class.
//
//
// Copyright(C) GPH(Gamepark Holdings). All rights reserved.
// Dogma-G Game Studios In-House Library DGE
//
////////////////////////////////////////////////////////////////////////////////


#ifndef _GameObject_H_
#define _GameObject_H_



struct GameObject
{
	INT			m_nTex;		// 텍스처 번호
	LCXVECTOR3	m_pos;		// 출력 위치
	LCXVECTOR3	m_vlc;		// 이동 속도
	LCXVECTOR3	m_dir;		// 이동 방향
	FLOAT		m_rot;		// 회전
	INT			nAlive;		// 생존 여부

	GameObject();
	// 화면 출력
	void Draw(PLC_SPRITE pSpt, PLC_TEXTURE* pTex);
};



#endif

