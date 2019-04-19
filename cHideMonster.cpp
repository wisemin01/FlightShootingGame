#include "DXUT.h"
#include "cHideMonster.h"
#include "cMonsterBullet.h"
#include "cBullet.h"

cHideMonster::cHideMonster(vector<cBullet*>& monsterBullet, D3DXVECTOR2 pos, float speed, int pattern)
	:cMonster(monsterBullet, pos, 17, 2, pattern)
{
	m_speed = speed;
	Init();
}

cHideMonster::~cHideMonster()
{
	Release();
}

void cHideMonster::Init()
{
	m_hideTime = 0;
	m_bulletCount = 0;
	m_moveCount = 0;
	m_isdeathAnimationPlayTime = 0;
	m_isHide = false;
	m_monsterAlpha = 255;
	m_monsterType = e_monsterType_hideMonster;
	m_hideMonster = ANIMATIONMANAGER->AddPieceAnimation("hideMonster", 1, 30);
	m_explode = ANIMATIONMANAGER->AddPieceAnimation("explodeEffect", 36, 30);

	if (m_pos.x < WINSIZEX / 3) {
		m_posType = left;
	}
	else if (m_pos.x < (WINSIZEX / 3) * 2) {
		m_posType = mid;
	}
	else m_posType = right;
}

void cHideMonster::Update()
{
	if (m_isdeathAnimationPlayTime == 0) {
		if (m_hideTime < nowTime) {
			m_isHide = !m_isHide;
			m_hideTime = nowTime + 1200;
			m_bulletCount = 3;
			m_moveCount = 1;
		}
		if (!m_isHide) {
			if (m_monsterAlpha < 255)
				m_monsterAlpha += 5;
			if (m_bulletCount > 0) {
				D3DXVECTOR2 dirc = GAMEMANAGER->GetPlayerPos() - m_pos;
				D3DXVec2Normalize(&dirc, &dirc);
				m_fireBullet.push_back(new cMonsterBullet(D3DXVECTOR2(m_pos.x, m_pos.y), 100, 2, 0, dirc));
				m_bulletCount--;
			}
		}
		if (m_isHide) {
			if (m_monsterAlpha > 0)
				m_monsterAlpha -= 5;
			if (m_moveCount) {
				switch (m_posType) {
				case left:
					m_pos = D3DXVECTOR2(rand() % (WINSIZEX / 3), rand() % (WINSIZEY / 2));
					break;
				case mid:
					m_pos = D3DXVECTOR2(rand() % (WINSIZEX / 3) + (WINSIZEX / 3), rand() % (WINSIZEY / 2));
					break;
				case right:
					m_pos = D3DXVECTOR2(rand() % (WINSIZEX / 3) + 2 * (WINSIZEX / 3), rand() % (WINSIZEY / 2));
					break;
				}
				m_moveCount--;
			}
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

void cHideMonster::Render()
{
	if (m_isdeathAnimationPlayTime > 0) {
			m_explode->CenterRender(m_pos.x, m_pos.y);
	}
	else {
	if (!m_isHide)
		m_hideMonster->CenterRender(m_pos.x, m_pos.y, 1.0, 0.0, D3DCOLOR_ARGB(m_monsterAlpha, 255, 255, 255));
	}
}

void cHideMonster::Release()
{
	SAFE_DELETE(m_hideMonster);
	SAFE_DELETE(m_explode);
}

void cHideMonster::SetRect()
{
	m_monsterRect = {
		(LONG)m_pos.x - 30,
		(LONG)m_pos.y - 30,
		(LONG)m_pos.x + 30,
		(LONG)m_pos.y + 30 };
}
