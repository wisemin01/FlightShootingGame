#pragma once
#include "cScene.h"

class cScroolMap;
class cShipPlayer;
class cBulletAdmin;
class cCursorPointer;
class cButton;
class cMonsterAdmin;
class cCollisionAdmin;

class cSecondStageScene :
	public cScene
{
private:
	cScroolMap * m_scrool;
	cShipPlayer* m_player;
	cBulletAdmin* m_bullet;
	cCursorPointer* m_pointer;
	cMonsterAdmin* m_monster;
	cCollisionAdmin* m_collision;

	texture* m_gamePauseImg;
	texture* m_grayImg;
	texture* m_gamePauseBackGround;

	cButton* m_quitButton;

	DWORD m_progressTime;
public:
	cSecondStageScene();
	~cSecondStageScene();

	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;

	void UpdateProgress();
};

