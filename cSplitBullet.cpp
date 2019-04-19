#include "DXUT.h"
#include "cSplitBullet.h"
#include "cMonsterBullet.h"
#include "cAccelBullet.h"

void cSplitBullet::SetRect()
{
	if (m_isexplode == true) {
		m_bulletRect = { 0,0,0,0 };
		return;
	}
	m_bulletRect = {
		(LONG)(m_pos.x - 10),
		(LONG)(m_pos.y - 10),
		(LONG)(m_pos.x + 10),
		(LONG)(m_pos.y + 10)
	};
}

cSplitBullet::cSplitBullet(D3DXVECTOR2 pos, float size, float speed, float damage, int splitCount,D3DXVECTOR2 dir ,vector<cBullet*>& bullets, float explodeTime)
	:cBullet(pos, size, speed, damage), m_fireBullet(bullets), m_explodeTime(explodeTime + nowTime),m_dir(dir),m_splitCount(splitCount)
{
	m_image = ANIMATIONMANAGER->FindAnimation("monsterBullet");
	m_isexplode = false;
}

cSplitBullet::~cSplitBullet()
{
}

void cSplitBullet::Update()
{
	m_pos += m_dir * (m_speed * DXUTGetElapsedTime());

	if (nowTime > m_explodeTime)
	{
		FLOAT rad_step;
		FLOAT rad;
		D3DXVECTOR2 dir;

		rad_step = M_PI / 180 * 10;

		rad = m_splitCount % 2 ? -m_splitCount / 2 * rad_step : (-m_splitCount / 2 + 0.5)*rad_step;

		dir = D3DXVECTOR2(0, 1);

		for (int i = 0; i < m_splitCount; i++, rad += rad_step) {

			float c = cos(rad), s = sin(rad);

			D3DXVECTOR2 dir02 = D3DXVECTOR2(dir.x * c - dir.y * s, dir.x*s + dir.y*c);

			D3DXVec2Normalize(&dir02, &dir02);
			m_fireBullet.push_back(new cAccelBullet(D3DXVECTOR2(m_pos.x, m_pos.y), 150, 1, 0, dir02));

		}

		m_explodeTime = nowTime + 10000;
		m_isexplode = true;
		m_isDeath = true;
	}

	SetRect();
}

void cSplitBullet::Render()
{
	if (!m_isexplode && m_image) {
		m_image->SceneRender(m_pos, 1.5, 0, OriginalColor, 0);
	}
}

