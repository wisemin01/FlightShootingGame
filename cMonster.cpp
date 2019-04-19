#include "DXUT.h"
#include "cMonster.h"
#include "cBullet.h"

cMonster::cMonster(vector<cBullet*>& fireBullet, D3DXVECTOR2 pos, float hp, float damage,int pattern)
	:m_pos(pos), m_hp(hp), m_damage(damage),m_pattern(pattern),m_fireBullet(fireBullet)
{
	m_isdeathAnimationPlayTime = 0;
	m_state = idle;
	m_prevHp = hp;
}


cMonster::~cMonster()
{
}

void cMonster::Render()
{
	m_img->Render(m_pos.x, m_pos.y);
}

bool cMonster::isOutMap()
{
	return (m_pos.x < -500		||
			m_pos.x	> WINSIZEX  + 500	||
			m_pos.y	< -500		||
			m_pos.y	> WINSIZEY  + 500	);
}
