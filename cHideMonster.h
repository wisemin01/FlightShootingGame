#pragma once
#include "cMonster.h"
class cHideMonster :
	public cMonster
{
	enum e_pos {
		left,
		mid,
		right
	};
private:
	pieceAnimation * m_hideMonster;
	pieceAnimation* m_explode;

	DWORD m_hideTime;
	BOOL m_isHide;
	UINT m_moveCount;
	UINT m_bulletCount;

	INT m_posType;

	INT m_monsterAlpha;
public:
	cHideMonster(vector<cBullet*>& monsterBullet, D3DXVECTOR2 pos, float speed = 100, int pattern = 0);
	~cHideMonster();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	void SetRect();
};

