#include "DXUT.h"
#include "cMonsterBullet.h"
#include "cBullet.h"

void cMonsterBullet::SetRect()
{
	m_bulletRect = {
	(LONG)m_pos.x - 5,
	(LONG)m_pos.y - 5,
	(LONG)m_pos.x + 5,
	(LONG)m_pos.y + 5
	};
}

cMonsterBullet::cMonsterBullet(D3DXVECTOR2 pos, float speed, float damage, int aniIndex, D3DXVECTOR2 targetPos)
	:cBullet(pos, 1.0, speed, damage), m_aniIndex(aniIndex), m_dir(targetPos)
{
	m_image = ANIMATIONMANAGER->FindAnimation("monsterBullet");
}

cMonsterBullet::~cMonsterBullet()
{
}

void cMonsterBullet::Update()
{
	SetRect();
	m_pos += m_dir * (m_speed * DXUTGetElapsedTime());
}



void cMonsterBullet::Render()
{
	if (m_image)
		m_image->SceneRender(m_pos, 1.0, D3DXToRadian(m_rotation++), OriginalColor, m_aniIndex);
}
