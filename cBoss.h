#pragma once
#include "cMonster.h"
class cBoss :
	public cMonster
{
private:
	enum state {
		move,
		stop
	};
	DWORD m_shootTime;
	INT	  m_monsterBulletAniIndex;

	pieceAnimation* m_Boss;
	pieceAnimation* m_explode;

	INT			m_state;
private:
	void SetRect();
	void n_wayBullet(int flag,int BulletCount);
public:
	cBoss(vector<cBullet*>& monsterBullet, D3DXVECTOR2 pos, float speed = 100, int pattern = 0);
	~cBoss();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

};

