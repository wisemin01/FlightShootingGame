#include "DXUT.h"
#include "cShipPlayer.h"
#include "cBullet.h"
#include "cPlayerBullet.h"


cShipPlayer::cShipPlayer(vector<cBullet*>& playerBullet)
	:m_fireBullet(playerBullet)
{
	Init();
}

cShipPlayer::~cShipPlayer()
{
	Release();
}

void cShipPlayer::Init()
{
	m_pos = { WINSIZEX / 2,WINSIZEY / 2 };

	m_playerAni = IMAGE("ShipPlayer");
	m_explode = ANIMATIONMANAGER->AddPieceAnimation("explodeEffect", 36, 60);

	m_speed = 500;
	m_bullet_delay = nowTime;
	m_bullet_count = 0;
	m_hp = 100;
	SetRect();
}

void cShipPlayer::Update()
{
	if (KEY_RETAIN('W'))
		m_pos.y -= m_speed * DXUTGetElapsedTime();

	if (KEY_RETAIN('S'))
		m_pos.y += m_speed * DXUTGetElapsedTime();

	if (KEY_RETAIN('A'))
		m_pos.x -= m_speed * DXUTGetElapsedTime();

	if (KEY_RETAIN('D'))
		m_pos.x += m_speed * DXUTGetElapsedTime();

	if (KEY_RETAIN(VK_LBUTTON)) {
		m_bullet_count = 3;
	}

	if (m_bullet_count > 0 && m_bullet_delay < nowTime) {
		D3DXVECTOR2 dir = MOUSE_POS - D3DXVECTOR2(m_pos.x, m_pos.y - 110);
		D3DXVec2Normalize(&dir, &dir);

		m_fireBullet.push_back(new cPlayerBullet(ANIMATIONMANAGER->FindAnimation("playerSideBullet"), D3DXVECTOR2(m_pos.x, m_pos.y - 110), 1000, 2, 0, dir, 2));
		m_bullet_delay = nowTime + 100;
		m_bullet_count--;
	}
	SetRect();
}
void cShipPlayer::Render()
{
	m_playerAni->CenterRender(m_pos.x, m_pos.y, 1.0, 0, OriginalColor);
}

void cShipPlayer::Release()
{
	SAFE_DELETE(m_explode);
}

void cShipPlayer::SetRect()
{
	m_playerRect = {
		(LONG)(m_pos.x - 10),
		(LONG)(m_pos.y - 10),
		(LONG)(m_pos.x + 10),
		(LONG)(m_pos.y + 10),
	};
	GAMEMANAGER->SetPlayerPos(m_pos);
}

RECT cShipPlayer::GetRect()
{
	return m_playerRect;
}
