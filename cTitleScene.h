#pragma once
#include "cScene.h"
class cButton;
class cScroolMap;
class cFade;

class cTitleScene :
	public cScene
{
private:
	cScroolMap* m_backGround;

	texture* m_startGame;
	texture* m_ranking;
	texture* m_quit;
	texture* m_titleLogo;
	texture* m_SelectArrow;

	INT m_SeleteIndex;

	D3DXVECTOR2 m_ArrowPos;

	cButton* menuSelect[4];
public:
	cTitleScene();
	~cTitleScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

