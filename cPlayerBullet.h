#pragma once
#include "cBullet.h"

class cPlayerBullet : public cBullet
{
private:
	animation * m_image;
	D3DXVECTOR2 m_dir;
	float m_rot;
	int m_aniIndex;
	int m_iscanTurn;

	void SetRect();
public:
	cPlayerBullet(const D3DXVECTOR2& pos,float speed,float damage,int aniIndex = 0, D3DXVECTOR2 targetPos = D3DXVECTOR2(0, 1));
	cPlayerBullet(animation* newImg,const D3DXVECTOR2& pos, float speed, float damage, int aniIndex = 0, D3DXVECTOR2 targetPos = D3DXVECTOR2(0, 1),int turn = 0);
	~cPlayerBullet();

	virtual void Update() override;
	virtual void Render() override;

	void SetTurnSetting(bool b) { m_iscanTurn = b; }
};

