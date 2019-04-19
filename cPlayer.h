#pragma once

class cBullet;
class cBulletAdmin;
class cPlayer
{
private:
	enum keystate {
		left,mid,right
	};
	pieceAnimation * m_playerAni;
	pieceAnimation* m_explode;

	D3DXVECTOR2 m_pos;

	vector<cBullet*>& m_fireBullet;

	DWORD	shootTime;
	DWORD	DeathAniTime;
	DWORD	sideShootTime;

	INT		ShootCount;	
	INT		m_hp;
	INT		m_state;

	FLOAT	m_speed;

	RECT	m_playerRect;

	void SetRect();
	void PlayerMove();
	void PlayerStateUpdate();
	void PlayerShootUpdate();
public:
	cBulletAdmin * admin;
private:

	INT m_playerAniIndex;
	INT m_playerBulletAniIndex;
	INT m_playerKeystate;

	DWORD m_changeIndexTime;


	void SetAniIndex();
public:
	cPlayer(vector<cBullet*>& playerBullet,cBulletAdmin* admin);
	~cPlayer();

	void Update();
	void Render();

	void SetHp(int nhp) { m_hp = nhp; }

	D3DXVECTOR2 GetPos() { return m_pos; }
	RECT GetRect() { return m_playerRect; }
	INT	 GetHp() { return m_hp; }

	INT	GetState() { return m_state; }
};

