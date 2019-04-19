#include "DXUT.h"
#include "cPlayer.h"

#include "cPlayerBullet.h"
#include "cBulletAdmin.h"

cPlayer::cPlayer(vector<cBullet*>& playerBullet, cBulletAdmin* admin)
	:m_pos(WINSIZEX / 2, 450), m_fireBullet(playerBullet), admin(admin)
{
	m_playerAni = ANIMATIONMANAGER->AddPieceAnimation("player", 7, 50);
	m_explode = ANIMATIONMANAGER->AddPieceAnimation("explodeEffect", 36, 60);

	shootTime = nowTime;
	sideShootTime = shootTime;

	m_playerAniIndex = 0;
	m_changeIndexTime = 0;
	m_playerBulletAniIndex = 0;
	ShootCount = 0;
	m_speed = 480;
	m_state = true;

	m_hp = 5;
	DeathAniTime = 0;
}

cPlayer::~cPlayer()
{
	SAFE_DELETE(m_playerAni);
	SAFE_DELETE(m_explode);
}

void cPlayer::Update()
{
	GAMEMANAGER->SetPlayerPos(m_pos);

	m_playerKeystate = mid;

	if (DeathAniTime == 0) {
		PlayerMove();
		PlayerShootUpdate();
	}

	SetAniIndex();
	SetRect();
	PlayerStateUpdate();
}

void cPlayer::Render()
{
	if (DeathAniTime == 0)
		m_playerAni->sceneCenterRender(m_pos.x, m_pos.y, 1.0, 0, OriginalColor, m_playerAniIndex);
	else
		m_explode->CenterRender(m_pos.x, m_pos.y, 1.0, 0, OriginalColor);
}

void cPlayer::SetAniIndex()
{
	if (m_changeIndexTime <= nowTime) {
		switch (m_playerKeystate) {
		case left:
			if (m_playerAniIndex > 0)
				m_playerAniIndex--;
			break;
		case mid:
			if (m_playerAniIndex != 3) {
				if (m_playerAniIndex < 3)
					m_playerAniIndex++;
				if (m_playerAniIndex > 3)
					m_playerAniIndex--;
			}
			break;
		case right:
			if (m_playerAniIndex < 6)
				m_playerAniIndex++;
			break;
		default:
			break;
		}
		if (m_playerAniIndex > 20)
			m_playerAniIndex = 0;
		if (m_playerAniIndex < 0)
			m_playerAniIndex = 20;
		m_changeIndexTime = nowTime + 50;
	}
}

void cPlayer::PlayerMove()
{
	if (KEY_RETAIN(VK_LEFT)) {
		if (m_pos.x > 0) {
			m_pos.x -= m_speed * DXUTGetElapsedTime();
		}
		m_playerKeystate = left;
	}
	if (KEY_RETAIN(VK_RIGHT)) {
		if (m_pos.x < WINSIZEX) {
			m_pos.x += m_speed * DXUTGetElapsedTime();
		}
		m_playerKeystate = right;
	}
	if (KEY_RETAIN(VK_UP)) {
		if (m_pos.y > 0) {
			m_pos.y -= m_speed * DXUTGetElapsedTime();
		}
	}
	if (KEY_RETAIN(VK_DOWN)) {
		if (m_pos.y < WINSIZEY) {
			m_pos.y += m_speed * DXUTGetElapsedTime();
		}
	}
	if (KEY_RETAIN(VK_SPACE))
	{
		ShootCount = 3;
		if (nowTime > sideShootTime)
		{
			D3DXVECTOR2 dirc1 = GAMEMANAGER->GetNearbyMonsterPos() - D3DXVECTOR2(m_pos.x - 30, m_pos.y - 30);
			D3DXVECTOR2 dirc2 = GAMEMANAGER->GetNearbyMonsterPos() - D3DXVECTOR2(m_pos.x + 30, m_pos.y - 30);

			D3DXVec2Normalize(&dirc1, &dirc1);
			D3DXVec2Normalize(&dirc2, &dirc2);

			m_fireBullet.push_back(new cPlayerBullet(ANIMATIONMANAGER->FindAnimation("playerSideBullet"), D3DXVECTOR2(m_pos.x - 30, m_pos.y - 30), 700, 1, 0, dirc1, 1));
			m_fireBullet.push_back(new cPlayerBullet(ANIMATIONMANAGER->FindAnimation("playerSideBullet"), D3DXVECTOR2(m_pos.x + 30, m_pos.y - 30), 700, 1, 0, dirc2, 1));
			sideShootTime = nowTime + 200;
		}
	}
}

void cPlayer::PlayerStateUpdate()
{
	if (m_hp < 0)
	{
		if (DeathAniTime == 0)
			DeathAniTime = nowTime + 1500;
	}
	if (DeathAniTime != 0) {
		if (DeathAniTime < nowTime)
			m_state = false;
	}
	if (GAMEMANAGER->g_stageClear)
		m_pos.y -= m_speed * DXUTGetElapsedTime();
}

void cPlayer::PlayerShootUpdate()
{

	if (ShootCount > 0) {
		if (nowTime > shootTime) {
			m_fireBullet.push_back(new cPlayerBullet(
				D3DXVECTOR2(m_pos.x, m_pos.y - 60), 1500, 2, m_playerBulletAniIndex++, D3DXVECTOR2(0, -1)));
			if (m_playerBulletAniIndex >= 4)
				m_playerBulletAniIndex = 0;

			shootTime = nowTime + 50;
			ShootCount--;
		}
	}
}

void cPlayer::SetRect()
{
	m_playerRect = {
		(LONG)(m_pos.x - 10),
		(LONG)(m_pos.y - 10),
		(LONG)(m_pos.x + 10),
		(LONG)(m_pos.y + 10),
	};
}