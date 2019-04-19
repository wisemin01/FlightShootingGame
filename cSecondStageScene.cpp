#include "DXUT.h"
#include "cSecondStageScene.h"

#include "cShipPlayer.h"
#include "cScroolMap.h"
#include "cBulletAdmin.h"
#include "cBullet.h"
#include "cCursorPointer.h"
#include "cMonsterAdmin.h"
#include "cCollisionAdmin.h"
#include "cButton.h"

cSecondStageScene::cSecondStageScene()
{
}


cSecondStageScene::~cSecondStageScene()
{
}

void cSecondStageScene::Init()
{
	m_bullet = new cBulletAdmin();
	m_scrool = new cScroolMap(IMAGE("mapBackGround"));
	m_player = new cShipPlayer(m_bullet->GetPlayerBullet());
	m_pointer = new cCursorPointer(MOUSE_POS);
	m_monster = new cMonsterAdmin(m_bullet->GetMonsterBullet());
	m_collision = new cCollisionAdmin(m_bullet->GetPlayerBullet(), m_bullet->GetMonsterBullet(), m_monster->GetMonster(), m_player);

	m_gamePauseImg = IMAGE("gamePause");
	m_grayImg = IMAGE("grayImg");
	m_gamePauseBackGround = IMAGE("gamePauseBackGround");

	m_quitButton = new cButton(WINSIZEX / 2, WINSIZEY / 2 + 40);

	INPUTMANAGER->ShowCursor(false);
	GAMEMANAGER->SetGameProgress(0);
	m_progressTime = 0;
}

void cSecondStageScene::Update()
{
	if (KEY_DOWN(VK_BACK)) {
		GAMEPAUSE = !GAMEPAUSE;
	}
	if (GAMEPAUSE == false) {
		m_scrool->Update(30);
		m_player->Update();
		m_bullet->Update();
		m_monster->Update();
		m_collision->Update();

		UpdateProgress();
	}
	else {
		m_quitButton->Update();
		if (m_quitButton->isDown()) {
			SCENEMANAGER->ChangeScene("title");
			SAVESCORE();
			GAMEMANAGER->SetScore(0);
			GAMEPAUSE = false;
			Sleep(100);
		}
		if (KEY_DOWN(VK_RETURN))
		{
			SCENEMANAGER->ChangeScene("title");
			SAVESCORE();
			GAMEMANAGER->SetScore(0);
			GAMEPAUSE = false;
			Sleep(100);
		}
	}
	if (!INPUTMANAGER->GetCursorState())
		m_pointer->Update();
}

void cSecondStageScene::Render()
{
	m_scrool->Render();
	m_player->Render();
	m_bullet->Render();
	m_monster->Render();

	if (GAMEPAUSE) {
		if (m_gamePauseBackGround)
			m_gamePauseBackGround->Render(0, 0);
		if (m_gamePauseImg)
			m_gamePauseImg->CenterRender(WINSIZEX / 2, WINSIZEY / 2);
		if (m_quitButton)
			m_quitButton->Render();
	}

	if (!INPUTMANAGER->GetCursorState())
		m_pointer->Render();
}

void cSecondStageScene::Release()
{
	SAFE_DELETE(m_scrool);
	SAFE_DELETE(m_player);
	SAFE_DELETE(m_bullet);
	SAFE_DELETE(m_pointer);
	SAFE_DELETE(m_quitButton);
	SAFE_DELETE(m_monster);

	INPUTMANAGER->ShowCursor(true);
}


void cSecondStageScene::UpdateProgress()
{
	if (nowTime >= m_progressTime) {
		GAMEMANAGER->SetGameProgress(GAMEMANAGER->GetGameProgress() + 1);
		m_progressTime = nowTime + 1000;
	}
}
