#pragma once
#include "cBullet.h"
class cMonsterBullet :
	public cBullet
{
private:
	animation * m_image;
	INT m_aniIndex;
	D3DXVECTOR2 m_dir;

	void SetRect();
public:
	cMonsterBullet(D3DXVECTOR2 pos, float speed, float damage, int aniIndex = 0, D3DXVECTOR2 targetPos = D3DXVECTOR2(0, 1));
	virtual ~cMonsterBullet();

	virtual void Update() override;
	virtual void Render() override;
};

