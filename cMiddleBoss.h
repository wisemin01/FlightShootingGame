#pragma once
#include "cMonster.h"
class cMiddleBoss :
	public cMonster
{
private:
	enum state {
		move,
		stop
	};
	DWORD m_shootTime;
	DWORD m_attackTime;
	INT m_attackCount;
	INT	  m_monsterBulletAniIndex;

	pieceAnimation* m_middleBoss;
	pieceAnimation* m_explode;

	INT			m_state;
	FLOAT		m_downspeed;
	int m_way;
private:
	void SetRect();
public:
	cMiddleBoss(vector<cBullet*>& monsterBullet,D3DXVECTOR2 pos, float speed = 100, int pattern = 0, int way = 0);
	~cMiddleBoss();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};