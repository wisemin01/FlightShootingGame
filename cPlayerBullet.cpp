#include "DXUT.h"
#include "cPlayerBullet.h"

void cPlayerBullet::SetRect()
{
	m_bulletRect = { (LONG)m_pos.x - 20,(LONG)m_pos.y - 20,(LONG)m_pos.x + 20,(LONG)m_pos.y + 20 };
}

cPlayerBullet::cPlayerBullet(const D3DXVECTOR2& pos, float speed, float damage, int aniIndex, D3DXVECTOR2 targetPos)
	:cBullet(pos, 20, speed, damage), m_aniIndex(aniIndex), m_dir(targetPos)
{
	m_image = ANIMATIONMANAGER->FindAnimation("playerBullet");
	m_iscanTurn = false;
}

cPlayerBullet::cPlayerBullet(animation * newImg, const D3DXVECTOR2 & pos, float speed, float damage, int aniIndex, D3DXVECTOR2 targetPos, int turn)
	: cBullet(pos, 20, speed, damage), m_aniIndex(aniIndex), m_dir(targetPos), m_image(newImg)
{
	m_rot = 0;
	m_iscanTurn = turn;

	if (m_image == NULL) {
		m_image = ANIMATIONMANAGER->FindAnimation("playerBullet");
	}

	if (m_iscanTurn == 2) {
		D3DXVECTOR2 dir = MOUSE_POS - m_pos;
		D3DXVECTOR2 normal(0, -1);

		if (MOUSE_POS.x < m_pos.x) {
			normal = { 0,1 };
		}

		D3DXVec2Normalize(&dir, &dir);
		D3DXVec2Normalize(&normal, &normal);

		float dot = D3DXVec2Dot(&dir, &normal);

		m_rot = (float)acos(dot);
	}
	else if(m_iscanTurn == 1){
		D3DXVECTOR2 dir = GAMEMANAGER->GetNearbyMonsterPos() - m_pos;
		D3DXVECTOR2 normal(0, -1);

		if (GAMEMANAGER->GetNearbyMonsterPos().x < m_pos.x) {
			normal = { 0,1 };
		}


		D3DXVec2Normalize(&dir, &dir);
		D3DXVec2Normalize(&normal, &normal);

		float dot = D3DXVec2Dot(&dir, &normal);

		m_rot = (float)acos(dot);
	}
}

cPlayerBullet::~cPlayerBullet()
{
}

void cPlayerBullet::Update()
{
	m_pos += m_dir * (m_speed * DXUTGetElapsedTime());

	SetRect();
}

void cPlayerBullet::Render()
{
	if (m_image)
		m_image->SceneRender(m_pos, 1.0, m_rot , 4294967295UL, m_aniIndex);
}
