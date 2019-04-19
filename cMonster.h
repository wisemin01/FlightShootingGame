#pragma once
class cBullet;
class cMonster abstract
{
public:
	enum e_state {
		death,
		idle
	};
	enum e_monsterType {
		e_monsterType_missile = 0,
		e_monsterType_middleBoss = 1,
		e_monsterType_Boss = 2,
		e_monsterType_hideMonster = 3,
		e_monsterType_stage1Boss = 4
	};
protected:
	vector<cBullet*>& m_fireBullet;

	D3DXVECTOR2 m_pos;
	FLOAT		m_hp;
	FLOAT		m_speed;
	FLOAT		m_damage;
	animation*	m_img;

	INT			m_pattern;
	RECT		m_monsterRect;

	INT			m_state;
	INT			m_monsterType;
	DWORD		m_isdeathAnimationPlayTime;

	DWORD		m_prevHp;
	DWORD		m_hitTime;
public:
	cMonster(vector<cBullet*>& fireBullet,D3DXVECTOR2 pos, float hp = 3, float damage = 1.0f, int pattern = 1);
	virtual ~cMonster();

	virtual void Init	()	PURE;
	virtual void Update	()	PURE;
	virtual void Render ()		;
	virtual void Release()	PURE;

	bool	isOutMap();
public:
	RECT	GetRect	() { return m_monsterRect; }
	FLOAT		GetHp	() { return m_hp; }
	INT		GetState() { return m_state; }
	INT		GetAniPlayTime() { if (!m_isdeathAnimationPlayTime) return false; else return true; }
	INT		GetMonsterType() { return m_monsterType; }

	D3DXVECTOR2 GetMonsterPos() { return m_pos; }

	void	SetHp(float nhp) { m_hp = nhp; }
};

