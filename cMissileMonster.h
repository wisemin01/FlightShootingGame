#pragma once
#include "cMonster.h"
class cMissileMonster :
	public cMonster
{
private:
	void SetRect();
	pieceAnimation* m_missileMonster;
	pieceAnimation* m_explode;
	int m_way;
	float m_downspeed;
	float m_OriginalSpeed;
	DWORD m_shootTime;
protected:

public:
	cMissileMonster(vector<cBullet*>& monsterBullet,D3DXVECTOR2 pos, float speed = 100, int pattern = 0,int way = 0);
	virtual ~cMissileMonster();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

