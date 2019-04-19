#pragma once
#include "cScene.h"
class cScroolMap;
class cNumber;
class cRankingScene :
	public cScene
{
private:
	cScroolMap * m_backGround;
	texture* m_rankingBoard;
	texture* m_rankingBlocks;
	cNumber* m_number;
public:
	cRankingScene();
	~cRankingScene();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;
};

