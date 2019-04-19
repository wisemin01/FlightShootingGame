#pragma once
#include "cBullet.h"
class cAccelBullet :
	public cBullet
{
private:
	animation * m_image;
	INT m_aniIndex;
	D3DXVECTOR2 m_dir;

	float m_accelSpeed;

	void SetRect();
public:
	cAccelBullet(D3DXVECTOR2 pos, float speed, float damage, int aniIndex = 0, D3DXVECTOR2 targetPos = D3DXVECTOR2(0, 1));
	cAccelBullet(D3DXVECTOR2 pos, float speed, float damage, int aniIndex = 0,float accelspeed = 0, D3DXVECTOR2 targetPos = D3DXVECTOR2(0, 1));
	virtual ~cAccelBullet();

	virtual void Update() override;
	virtual void Render() override;
};

