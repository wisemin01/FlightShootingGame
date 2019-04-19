#pragma once

class cBullet;

class cShipPlayer
{
	enum keystate {
		left, mid, right
	};

	texture * m_playerAni;
	pieceAnimation * m_explode;

	D3DXVECTOR2 m_pos;

	vector<cBullet*>& m_fireBullet;

	FLOAT m_speed;
	FLOAT m_hp;
	DWORD m_bullet_delay;
	INT m_bullet_count;

	RECT m_playerRect;

public:
	cShipPlayer(vector<cBullet*>& playerBullet);
	virtual ~cShipPlayer();

	void Init();
	void Update();
	void Render();
	void Release();

	INT GetHp() { return m_hp; }
	void SetHp(int n) { m_hp = n; }
	
	void SetRect();
	RECT GetRect();
};

