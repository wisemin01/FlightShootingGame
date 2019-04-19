#pragma once
#include "cScene.h"

class cScroolMap;
class cPlayer;
class cBulletAdmin;
class cMonsterAdmin;
class cCollisionAdmin;
class cButton;
class cNumber;
class cFirstStageScene : public cScene
{
private:
	cScroolMap* m_map;
	cScroolMap* m_cloud;

	cPlayer* m_player;
	cNumber* m_number;

	cBulletAdmin* m_bullet;
	cMonsterAdmin* m_monster;

	cCollisionAdmin* m_collision;
	pieceAnimation* m_gameoverAni;

	DWORD m_progressTime;
	DWORD m_gameoverAniTime;

	BOOL m_gameover;
private:
	//game pause
	texture* m_gamePauseImg;
	texture* m_grayImg;
	texture* m_gamePauseBackGround;
	texture* m_gameclear;
	texture* m_scoreboard;

	cButton* m_quitButton;
public:
	cFirstStageScene();
	~cFirstStageScene();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;
private:
	void UpdateProgress();
};

