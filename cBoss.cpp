#include "DXUT.h"
#include "cBoss.h"
#include "cMonsterBullet.h"

void cBoss::SetRect()
{
	m_monsterRect = {
		(LONG)(m_pos.x - 108),
		(LONG)(m_pos.y - 80),
		(LONG)(m_pos.x + 108),
		(LONG)(m_pos.y + 80),
	};
}

void cBoss::n_wayBullet(int flag,int BulletCount)
{

	FLOAT rad_step;
	FLOAT rad;
	D3DXVECTOR2 dir;

	switch (flag) {
	case 1: // Â¦¼ö
	{
		rad_step = D3DX_PI / 180 * 10;
		rad = BulletCount % 2 ? -BulletCount / 2 * rad_step : (-BulletCount / 2 + 0.5)*rad_step;
		dir = D3DXVECTOR2(0,1);
		for (int i = 0; i < BulletCount; i++, rad += rad_step) {
			float c = cos(rad), s = sin(rad);
			D3DXVECTOR2 dir02 = D3DXVECTOR2(dir.x * c - dir.y * s, dir.x*s + dir.y*c);
			D3DXVec2Normalize(&dir02, &dir02);
			m_fireBullet.push_back(new cMonsterBullet(D3DXVECTOR2(m_pos.x, m_pos.y + 70), 300, 1, 0, dir02));
		}
		break;
	}
	case 2: // È¦¼ö
		break;
	default:
		break;
	}
}

cBoss::cBoss(vector<cBullet*>& monsterBullet, D3DXVECTOR2 pos, float speed, int pattern)
	:cMonster(monsterBullet, pos, 110, 4, pattern)
{
	m_speed = speed;
	Init();
}

cBoss::~cBoss()
{
	Release();
}

void cBoss::Init()
{
	m_monsterType = e_monsterType_Boss;
	m_shootTime = 0;
	m_monsterBulletAniIndex = 0;
	m_Boss = ANIMATIONMANAGER->AddPieceAnimation("Boss", 20, 60);
	m_explode = ANIMATIONMANAGER->AddPieceAnimation("explodeEffect", 36, 40);
}

void cBoss::Update()
{
	if (m_pos.y < 200) {
		m_pos.y += m_speed * DXUTGetElapsedTime();
	}
	else {
		switch (m_pattern) {
		case 1:
			if (nowTime > m_shootTime) {
				if (m_isdeathAnimationPlayTime == 0) {
					n_wayBullet(1, 15);
					m_shootTime = nowTime + 1500;
				}
			}
			break;
		default:
			break;
		}
	}
	SetRect();
	if (m_hp < 0) {
		if (m_isdeathAnimationPlayTime == 0) {
			n_wayBullet(1, 40);
			m_isdeathAnimationPlayTime = nowTime + 1000;
		}
	}
	if (m_isdeathAnimationPlayTime != 0) {
		if (m_isdeathAnimationPlayTime < nowTime) {
			cMonster::m_state = death;
		}
	}
	if (m_prevHp != m_hp) {
		m_hitTime = nowTime + 50;
	}
	m_prevHp = m_hp;
}

void cBoss::Render()
{
	if (m_isdeathAnimationPlayTime == 0)
	{
		if (m_hitTime > nowTime) {
			m_Boss->sceneCenterRender(m_pos.x, m_pos.y, 1.0, 0.0, D3DCOLOR_XRGB(255, 200, 200), 0);
		}
		else
			m_Boss->sceneCenterRender(m_pos.x, m_pos.y, 1.0, 0.0, OriginalColor, 0);
	}
	else
		m_explode->CenterRender(m_pos.x, m_pos.y, 2.0);
}

void cBoss::Release()
{
	SAFE_DELETE(m_Boss);
	SAFE_DELETE(m_explode);
}
