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
	INT			m_nTex;		// �ؽ�ó ��ȣ
	LCXVECTOR3	m_pos;		// ��� ��ġ
	LCXVECTOR3	m_vlc;		// �̵� �ӵ�
	LCXVECTOR3	m_dir;		// �̵� ����
	FLOAT		m_rot;		// ȸ��
	INT			nAlive;		// ���� ����

	GameObject();
	// ȭ�� ���
	void Draw(PLC_SPRITE pSpt, PLC_TEXTURE* pTex);
};



#endif

