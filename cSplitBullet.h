#pragma once
#include "cBullet.h"
class cSplitBullet :
	public cBullet
{
private:
	vector<cBullet*>& m_fireBullet;
	FLOAT			m_explodeTime;
	BOOL m_isexplode;
	D3DXVECTOR2 m_dir;
	INT m_splitCount;

	animation * m_image;

	void SetRect();
public:
	cSplitBullet(D3DXVECTOR2 pos,float size,float speed,float damage,int splitCount,D3DXVECTOR2 dir,vector<cBullet*>& bullets,float explodeTime);
	~cSplitBullet();

	virtual void Update() override;
	virtual void Render() override;
};

