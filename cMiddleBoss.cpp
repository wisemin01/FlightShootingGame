#include "DXUT.h"
#include "cMiddleBoss.h"
#include "cMonsterBullet.h"
#include "cAccelBullet.h"
#include "cSplitBullet.h"

void cMiddleBoss::SetRect()
{
	m_monsterRect = {
		(LONG)(m_pos.x - 100),
		(LONG)(m_pos.y - 60),
		(LONG)(m_pos.x + 100),
		(LONG)(m_pos.y + 60),
	};
}

cMiddleBoss::cMiddleBoss(vector<cBullet*>& monsterBullet, D3DXVECTOR2 pos, float speed, int pattern, int way)
	:cMonster(monsterBullet, pos, 60, 1, pattern), m_way(way)
{
	m_speed = speed;
	if (pattern = 2)
		m_hp *= 2;
	Init();
}

cMiddleBoss::~cMiddleBoss()
{
	Release();
}

void cMiddleBoss::Init()
{
	m_monsterType = e_monsterType_middleBoss;
	m_shootTime = nowTime;
	m_monsterBulletAniIndex = 0;
	m_isdeathAnimationPlayTime = 0;


	m_middleBoss = ANIMATIONMANAGER->AddPieceAnimation("middleBoss", 20, 60);
	m_explode = ANIMATIONMANAGER->AddPieceAnimation("explodeEffect", 36, 40);

	m_state = move;
	m_downspeed = m_speed / 60;

	m_attackTime = nowTime;
	m_attackCount = 0;
}

void cMiddleBoss::Update()
{
	FLOAT rad_step;
	FLOAT rad;
	D3DXVECTOR2 dir;
	INT BulletCount = 0;

	SetRect();
	switch (m_pattern) {

	case 1:
		if (m_pos.y < 150) {
			m_state = move;
			m_pos.y += m_speed * DXUTGetElapsedTime();
		}
		else {
			m_state = stop;
			if (m_shootTime < nowTime) {
				if (m_isdeathAnimationPlayTime == 0) {
					D3DXVECTOR2 playerPos = GAMEMANAGER->GetPlayerPos();
					if (rand() % 2)
						playerPos.x += 150;
					else playerPos.x -= 150;
					D3DXVECTOR2 dirc = playerPos - m_pos;
					D3DXVec2Normalize(&dirc, &dirc);
					for (int i = 0; i < 5; i++) {
						m_fireBullet.push_back(new cMonsterBullet(D3DXVECTOR2(m_pos.x, m_pos.y + 130 + i * 5), 150 + 40 * i, 1, 0, dirc));
					}
					m_shootTime = nowTime + 900;
				}
			}
			if (m_pos.x < WINSIZEX / 2)
				m_pos.x += 50 * DXUTGetElapsedTime();
			else if (m_pos.x > WINSIZEX / 2)
				m_pos.x -= 50 * DXUTGetElapsedTime();
			m_pos.y += m_speed / 4 * DXUTGetElapsedTime();
		}
		break;

	case 2:
		if (!m_way) { // ¿À¸¥ÂÊ
			if (m_pos.x < 200) {
				m_state = move;
				m_pos.x += m_speed * DXUTGetElapsedTime();
				m_pos.y -= (m_speed / 4) * DXUTGetElapsedTime();
			}
			else {
				m_state = stop;
				if (m_isdeathAnimationPlayTime == 0) {
					// bullet
					if (m_attackTime < nowTime)
					{
						if (m_attackCount < 4)
						{
							m_attackTime = timeGetTime() + 50;
							D3DXVECTOR2 firePos = D3DXVECTOR2(m_pos.x + 50, m_pos.y);
							D3DXVECTOR2 direction = GAMEMANAGER->GetPlayerPos() - firePos;
							D3DXVec2Normalize(&direction, &direction);

							if (m_attackCount % 2 == 0) {
								//
								rad_step = D3DX_PI / 180 * 8;
								rad = 1 % 2 ? -1 / 2 * rad_step : (-1 / 2 + 0.5)*rad_step;
								dir = direction;
								for (int i = 0; i < 1; i++, rad += rad_step) {
									float c = cos(rad), s = sin(rad);
									D3DXVECTOR2 dir02 = D3DXVECTOR2(dir.x * c - dir.y * s, dir.x*s + dir.y*c);
									D3DXVec2Normalize(&dir02, &dir02);
									m_fireBullet.push_back(new cAccelBullet(D3DXVECTOR2(m_pos.x, m_pos.y + 70), 0, 1, 0, 5, dir02));
								}
							}
							else {
								rad_step = D3DX_PI / 180 * 8;
								rad = 2 % 2 ? -2 / 2 * rad_step : (-2 / 2 + 0.5)*rad_step;
								dir = direction;
								for (int i = 0; i < 2; i++, rad += rad_step) {
									float c = cos(rad), s = sin(rad);
									D3DXVECTOR2 dir02 = D3DXVECTOR2(dir.x * c - dir.y * s, dir.x * s + dir.y * c);
									D3DXVec2Normalize(&dir02, &dir02);
									m_fireBullet.push_back(new cAccelBullet(D3DXVECTOR2(m_pos.x, m_pos.y + 70), 0, 1, 0, 5, dir02));
								}
								//
							}

							D3DXVECTOR2 firePos02 = D3DXVECTOR2(m_pos.x - 50, m_pos.y);
							D3DXVECTOR2 direction02 = GAMEMANAGER->GetPlayerPos() - firePos02;
							D3DXVec2Normalize(&direction02, &direction02);

							if (m_attackCount % 2 == 0) {
								//
								rad_step = D3DX_PI / 180 * 8;
								rad = 1 % 2 ? -1 / 2 * rad_step : (-1 / 2 + 0.5)*rad_step;
								dir = direction02;
								for (int i = 0; i < 1; i++, rad += rad_step) {
									float c = cos(rad), s = sin(rad);
									D3DXVECTOR2 dir02 = D3DXVECTOR2(dir.x * c - dir.y * s, dir.x * s + dir.y * c);
									D3DXVec2Normalize(&dir02, &dir02);
									m_fireBullet.push_back(new cAccelBullet(D3DXVECTOR2(m_pos.x, m_pos.y + 70), 0, 1, 0, 5, dir02));
								}
								//
							}
							else {
								//
								rad_step = D3DX_PI / 180 * 8;
								rad = 2 % 2 ? -2 / 2 * rad_step : (-2 / 2 + 0.5)*rad_step;
								dir = direction02;
								for (int i = 0; i < 2; i++, rad += rad_step) {
									float c = cos(rad), s = sin(rad);
									D3DXVECTOR2 dir02 = D3DXVECTOR2(dir.x * c - dir.y * s, dir.x * s + dir.y * c);
									D3DXVec2Normalize(&dir02, &dir02);
									m_fireBullet.push_back(new cAccelBullet(D3DXVECTOR2(m_pos.x, m_pos.y + 70), 0, 1, 0, 5, dir02));
								}
								//
							}
							m_attackCount++;
						}
						else {
							m_attackTime = nowTime + 4000;
							m_attackCount = 0;
						}
					}
					//end
					m_pos.x += (m_speed / 2) * DXUTGetElapsedTime();
					m_pos.y -= (m_speed / 8) * DXUTGetElapsedTime();
				}

			}
		}
		else { //¿ÞÂÊ
			if (m_pos.x > WINSIZEX - 200) {
				m_state = move;
				m_pos.x -= m_speed * DXUTGetElapsedTime();
				m_pos.y -= (m_speed / 4) * DXUTGetElapsedTime();
			}
			else {
				m_state = stop;
				if (m_isdeathAnimationPlayTime == 0) {
					// bullet

					if (m_attackTime < nowTime)
					{
						if (m_attackCount < 4)
						{
							m_attackTime = timeGetTime() + 50;
							D3DXVECTOR2 firePos = D3DXVECTOR2(m_pos.x + 50, m_pos.y);
							D3DXVECTOR2 direction = GAMEMANAGER->GetPlayerPos() - firePos;
							D3DXVec2Normalize(&direction, &direction);

							if (m_attackCount % 2 == 0) {
								//
								rad_step = D3DX_PI / 180 * 8;
								rad = 1 % 2 ? -1 / 2 * rad_step : (-1 / 2 + 0.5)*rad_step;
								dir = direction;
								for (int i = 0; i < 1; i++, rad += rad_step) {
									float c = cos(rad), s = sin(rad);
									D3DXVECTOR2 dir02 = D3DXVECTOR2(dir.x * c - dir.y * s, dir.x*s + dir.y*c);
									D3DXVec2Normalize(&dir02, &dir02);
									m_fireBullet.push_back(new cAccelBullet(D3DXVECTOR2(m_pos.x, m_pos.y + 70), 0, 1, 0, 5, dir02));
								}
								//
							}
							else {
								//
								rad_step = D3DX_PI / 180 * 8;
								rad = 2 % 2 ? -2 / 2 * rad_step : (-2 / 2 + 0.5)*rad_step;
								dir = direction;
								for (int i = 0; i < 2; i++, rad += rad_step) {
									float c = cos(rad), s = sin(rad);
									D3DXVECTOR2 dir02 = D3DXVECTOR2(dir.x * c - dir.y * s, dir.x * s + dir.y * c);
									D3DXVec2Normalize(&dir02, &dir02);
									m_fireBullet.push_back(new cAccelBullet(D3DXVECTOR2(m_pos.x, m_pos.y + 70), 0, 1, 0, 5, dir02));
								}
								//
							}

							D3DXVECTOR2 firePos02 = D3DXVECTOR2(m_pos.x - 50, m_pos.y);
							D3DXVECTOR2 direction02 = GAMEMANAGER->GetPlayerPos() - firePos02;
							D3DXVec2Normalize(&direction02, &direction02);

							if (m_attackCount % 2 == 0) {
								//
								rad_step = D3DX_PI / 180 * 8;
								rad = 1 % 2 ? -1 / 2 * rad_step : (-1 / 2 + 0.5)*rad_step;
								dir = direction02;
								for (int i = 0; i < 1; i++, rad += rad_step) {
									float c = cos(rad), s = sin(rad);
									D3DXVECTOR2 dir02 = D3DXVECTOR2(dir.x * c - dir.y * s, dir.x * s + dir.y * c);
									D3DXVec2Normalize(&dir02, &dir02);
									m_fireBullet.push_back(new cAccelBullet(D3DXVECTOR2(m_pos.x, m_pos.y + 70), 0, 1, 0, 5, dir02));
								}
								//
							}
							else {
								//
								rad_step = D3DX_PI / 180 * 8;
								rad = 2 % 2 ? -2 / 2 * rad_step : (-2 / 2 + 0.5)*rad_step;
								dir = direction02;
								for (int i = 0; i < 2; i++, rad += rad_step) {
									float c = cos(rad), s = sin(rad);
									D3DXVECTOR2 dir02 = D3DXVECTOR2(dir.x * c - dir.y * s, dir.x * s + dir.y * c);
									D3DXVec2Normalize(&dir02, &dir02);
									m_fireBullet.push_back(new cAccelBullet(D3DXVECTOR2(m_pos.x, m_pos.y + 70), 0, 1, 0, 5, dir02));
								}
								//
							}
							m_attackCount++;
						}
						else {
							m_attackTime = nowTime + 4000;
							m_attackCount = 0;
						}
					}
					//end
					m_pos.x -= (m_speed / 2) * DXUTGetElapsedTime();
					m_pos.y -= (m_speed / 8) * DXUTGetElapsedTime();
				}

			}
		}
		break;

	case 3:
		m_pos.y += m_speed * DXUTGetElapsedTime();
		m_speed -= m_downspeed;

		if (nowTime > m_shootTime && m_speed < 0)

		{
			D3DXVECTOR2 m_dic(GAMEMANAGER->GetPlayerPos() - m_pos);
			D3DXVec2Normalize(&m_dic, &m_dic);
			m_fireBullet.push_back(new cSplitBullet(D3DXVECTOR2(m_pos.x, m_pos.y + 130), 1.0, 100, 3, 40, D3DXVECTOR2(0, 1), m_fireBullet, 3000));
			m_shootTime = nowTime + 10000;
		}
		break;

	default:
		break;
	}
	if (m_hp < 0) {
		if (m_isdeathAnimationPlayTime == 0)
			m_isdeathAnimationPlayTime = nowTime + 1000;
	}
	if (m_isdeathAnimationPlayTime != 0) {
		if (m_isdeathAnimationPlayTime < nowTime)
			cMonster::m_state = death;
	}
	if (m_prevHp != m_hp) {
		m_hitTime = nowTime + 50;
	}
	m_prevHp = m_hp;
}

void cMiddleBoss::Render()
{
	if (m_isdeathAnimationPlayTime == 0) {
		if (m_state == move)
		{
			if (m_hitTime > nowTime) {
				m_middleBoss->sceneCenterRender(m_pos.x, m_pos.y, 1.0, 0.0, D3DCOLOR_XRGB(255, 200, 200), 0);
			}
			else
				m_middleBoss->sceneCenterRender(m_pos.x, m_pos.y, 1.0, 0.0, OriginalColor, 0);
		}
		else if (m_state == stop) {
			if (m_hitTime > nowTime) {
				m_middleBoss->sceneCenterRender(m_pos.x, m_pos.y, 1.0, 0.0, D3DCOLOR_XRGB(255, 200, 200), 0);
			}
			else
				m_middleBoss->sceneCenterRender(m_pos.x, m_pos.y, 1.0, 0.0, OriginalColor, 0);
		}
	}
	else m_explode->CenterRender(m_pos.x, m_pos.y);
}

void cMiddleBoss::Release()
{
	SAFE_DELETE(m_middleBoss);
	SAFE_DELETE(m_explode);
}
