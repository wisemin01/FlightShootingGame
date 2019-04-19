#pragma once
#include "cMonster.h"
class cStage1Boss :
	public cMonster
{
private:
	pieceAnimation * m_stage1BossImg;
	pieceAnimation* m_explode;

	DWORD m_patternCountTime;
	UINT m_progress;
	UINT m_prevProgress;

	void SetRect();
	void UpdateProgress();
	void BossPattern();
public:
	cStage1Boss(vector<cBullet*>& monsterBullet, D3DXVECTOR2 pos, float speed = 100);
	~cStage1Boss();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

