#pragma once
class cMonster;
class cBullet;
class cMonsterAdmin
{
	enum e_monster_type {
		e_missile = 0,
		e_middleboss = 1,
		e_boss = 2,
		e_hideMonster = 3,
		e_stage1Boss = 4
	};
	enum e_monster_way {
		e_left,
		e_mid,
		e_right,
		e_random
	};
private:
	vector<cMonster*> m_monsters;
	vector<cBullet*>& m_monsterBullets;

	pieceAnimation* m_warring;

	DWORD patternTime;
	DWORD m_isWarring;
	DWORD m_warringTime;

	UINT m_currentProgress;

	BOOL m_MonsterStand[3];

	D3DXVECTOR2 m_WarningPos;
	INT m_warningSpeed;
private:
	void MonsterCollisionCheck();
	void MonsterDeathCheck();
public:
	cMonsterAdmin(vector<cBullet*>&bullet);
	~cMonsterAdmin();

	void Init();
	void Update();
	void Render();
	void Release();

	vector<cMonster*>& GetMonster() { return m_monsters; }
	cMonster* CreateMonster(D3DXVECTOR2 pos,float hp,float speed,float damage,int pattern,int type,int mway = 0);
public:
	//Monster Patterns
	void missileUnit(int flag);
	void updownmissile(int flag);
	void sideMissile(int flag);
	void middleBoss(int flag);
	void updownmiddleBoss(int flag);
	void sideMiddleBoss(int flag);
	void Boss(int flag);
	void HideMonster(int flag);
	void Stage1Boss();
	void Warring();
public:
	// pattern Update
	void PatternUpdate();
};

