#include "DXUT.h"
#include "cMissileMonster.h"
#include "cMonsterBullet.h"
#include "cAccelBullet.h"

void cMissileMonster::SetRect()
{
	m_monsterRect = { (LONG)m_pos.x - 50,
		(LONG)m_pos.y - 50,
		(LONG)m_pos.x + 50,
		(LONG)m_pos.y + 50 };
}

cMissileMonster::cMissileMonster(vector<cBullet*>& monsterBullet, D3DXVECTOR2 pos, float speed, int pattern, int way)
	:cMonster(monsterBullet, pos, 2, 1, pattern), m_way(way)
{
	m_missileMonster = ANIMATIONMANAGER->AddPieceAnimation("missileMonster", 20, 40);
	m_explode = ANIMATIONMANAGER->AddPieceAnimation("explodeEffect", 36, 30);
	m_OriginalSpeed = speed;
	m_speed = speed + 200;
	m_downspeed = speed / 60;
	if (pattern == 3) m_hp = 2;
	Init();
}

cMissileMonster::~cMissileMonster()
{
	Release();
}

void cMissileMonster::Init()
{
	m_monsterType	= e_monsterType_missile;
	m_shootTime		= nowTime;
}

void cMissileMonster::Update()
{
	if (m_isdeathAnimationPlayTime == 0) {
		switch (m_pattern) {
		case 1:
			m_pos.y += m_speed * DXUTGetElapsedTime();
			if (m_speed > m_OriginalSpeed) {
				m_speed -= m_OriginalSpeed/10;
			}
			if (nowTime > m_shootTime)
			{
				D3DXVECTOR2 m_dic(GAMEMANAGER->GetPlayerPos() - m_pos);
				D3DXVec2Normalize(&m_dic, &m_dic);
				m_fireBullet.push_back(new cAccelBullet(D3DXVECTOR2(m_pos.x, m_pos.y - 100), 100, 1, 0, m_dic));
				m_shootTime = nowTime + 600;
			}
			break;
		case 2:
			if (!m_way) {
				if (m_pos.x < WINSIZEX / 2) {
					m_pos.y -= 120 * DXUTGetElapsedTime();
				}
				else {
					m_pos.y += 120 * DXUTGetElapsedTime();
				}
				m_pos.x += m_speed/2 * DXUTGetElapsedTime();
				if (nowTime > m_shootTime)
				{
					D3DXVECTOR2 m_dic(GAMEMANAGER->GetPlayerPos() - m_pos);
					D3DXVec2Normalize(&m_dic, &m_dic);
					m_fireBullet.push_back(new cAccelBullet(D3DXVECTOR2(m_pos.x, m_pos.y + 100), 100, 1, 0, m_dic));
					m_shootTime = nowTime + 700;
				}
			}
			else if (m_way) {
				if (m_pos.x > WINSIZEX / 2) {
					m_pos.y -= 120 * DXUTGetElapsedTime();
				}
				else {
					m_pos.y += 120 * DXUTGetElapsedTime();
				}
				m_pos.x -= m_speed/2 * DXUTGetElapsedTime();
				if (nowTime > m_shootTime)
				{
					D3DXVECTOR2 m_dic(GAMEMANAGER->GetPlayerPos() - m_pos);
					D3DXVec2Normalize(&m_dic, &m_dic);
					m_fireBullet.push_back(new cAccelBullet(D3DXVECTOR2(m_pos.x, m_pos.y + 100), 100, 1, 0, m_dic));
					m_shootTime = nowTime + 700;
				}
			}
			break;
		case 3:
			m_pos.y += m_speed * DXUTGetElapsedTime();
			m_speed -= m_downspeed;

			if (nowTime > m_shootTime)
			{
				D3DXVECTOR2 m_dic(GAMEMANAGER->GetPlayerPos() - m_pos);
				D3DXVec2Normalize(&m_dic, &m_dic);
				m_fireBullet.push_back(new cAccelBullet(D3DXVECTOR2(m_pos.x, m_pos.y + 100), 250, 1, 0, m_dic));
				m_shootTime = nowTime + 700;
			}

			break;
		default:
			DEBUG_LOG("missileMonster" << " : 존재하지 않는 패턴");
			break;
		}
	}
	SetRect();
	if (m_hp <= 0) {
		if (!m_isdeathAnimationPlayTime)
			m_isdeathAnimationPlayTime = nowTime + 1000;
	}
	if (m_isdeathAnimationPlayTime != 0) {
		if (nowTime >= m_isdeathAnimationPlayTime) {
			m_state = death;
		}
	}
}

void cMissileMonster::Render()
{
	if (m_isdeathAnimationPlayTime > 0)
		m_explode->CenterRender(m_pos.x, m_pos.y, 0.7, 0);
	else
		m_missileMonster->CenterRender(m_pos.x, m_pos.y, 0.5, 0, 4294967295UL);
}

void cMissileMonster::Release()
{
	SAFE_DELETE(m_missileMonster);
	SAFE_DELETE(m_explode);
}
