#include "DXUT.h"
#include "cFirstStageScene.h"

#include "cScroolMap.h"
#include "cBulletAdmin.h"
#include "cPlayer.h"
#include "cMonsterAdmin.h"
#include "cCollisionAdmin.h"
#include "cButton.h"
#include "cNumber.h"

cFirstStageScene::cFirstStageScene()
{
}


cFirstStageScene::~cFirstStageScene()
{
}

void cFirstStageScene::Init()
{
	m_map		 = new cScroolMap	();
	m_cloud		 = new cScroolMap	(IMAGE("cloud"));
	m_number	 = new cNumber		(1.0);
	m_bullet	 = new cBulletAdmin	();
	m_player	 = new cPlayer		(m_bullet->GetPlayerBullet(), m_bullet); 
	m_monster	 = new cMonsterAdmin(m_bullet->GetMonsterBullet());
	m_collision	 = new cCollisionAdmin(m_bullet->GetPlayerBullet(),
									m_bullet->GetMonsterBullet(),
									m_monster->GetMonster(),m_player);
	m_quitButton = new cButton		(WINSIZEX / 2, WINSIZEY / 2 + 40);

	m_gameclear			  = IMAGE("stageclear");
	m_gamePauseImg		  = IMAGE("gamePause");
	m_grayImg			  = IMAGE("grayImg");
	m_gamePauseBackGround = IMAGE("gamePauseBackGround");
	m_scoreboard		  = IMAGE("scoreboard");

	m_gameoverAni		  = ANIMATIONMANAGER->AddPieceAnimation("gameover", 15, 100, 1);

	m_progressTime		  = nowTime;
	m_gameover			  = false;
	m_gameoverAniTime	  = 0;

	m_quitButton->SetButtonImg(IMAGE("quitButtonUp"), IMAGE("quitButtonDown"));

	GAMEMANAGER->SetGameProgress(0);
}

void cFirstStageScene::Release()
{
	SAFE_DELETE(m_map	);
	SAFE_DELETE(m_cloud );

	SAFE_DELETE(m_player );
	SAFE_DELETE(m_bullet );
	SAFE_DELETE(m_number );
	SAFE_DELETE(m_monster);

	SAFE_DELETE(m_collision	 );
	SAFE_DELETE(m_quitButton );
	SAFE_DELETE(m_gameoverAni);
}

void cFirstStageScene::Update()
{
	if (KEY_DOWN(VK_BACK)) {
		if (!m_gameover)
			GAMEPAUSE = !GAMEPAUSE;
	}

	if (GAMEPAUSE == false) {
		if (m_map) m_map->Update(150);
		if (m_cloud) m_cloud->Update(500);
		if (m_bullet) m_bullet->Update();
		if (m_player) m_player->Update();
		if (m_monster) m_monster->Update();
		if (m_collision) m_collision->Update();

		if (!m_gameover || GAMEMANAGER->g_stageClear)
			UpdateProgress();

		if (m_player) {
			if (!m_player->GetState()) {
				SAFE_DELETE(m_player);
				m_gameover = true;
				m_gameoverAniTime = nowTime + 1500;
			}
		}
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
	if (m_gameover) {
		m_quitButton->Update();
		if (m_quitButton->isDown()) {
			SCENEMANAGER->ChangeScene("ending");
			GAMEPAUSE = false;
		}
		if (KEY_RETAIN(VK_RETURN))
		{
			SCENEMANAGER->ChangeScene("ending");
			GAMEPAUSE = false;
		}
	}
	if (GAMEMANAGER->g_stageClear) {
		m_quitButton->Update();
		if (m_quitButton->isDown()) {
			SCENEMANAGER->ChangeScene("ending");
			GAMEMANAGER->g_stageClear = false;
			GAMEPAUSE = false;
		}
		if (KEY_RETAIN(VK_RETURN))
		{
			SCENEMANAGER->ChangeScene("ending");
			GAMEMANAGER->g_stageClear = false;
			GAMEPAUSE = false;
		} 
	}
}

void cFirstStageScene::Render()
{
	if (m_map)		m_map->Render();
	if (m_cloud)	m_cloud->Render();
	if (m_player)	m_player->Render();
	if (m_bullet)	m_bullet->Render();
	if (m_monster)	m_monster->Render();

	if (!m_gameover)
		if (m_number) m_number->Render(WINSIZEX / 2, 100, GAMESCORE);
	
	if (m_gameover) {
		if (m_gameoverAniTime > nowTime)
			m_gameoverAni->Render(0, 0);
		else {
			m_gamePauseBackGround->Render(0, 0);
			m_grayImg->CenterRender(WINSIZEX / 2, WINSIZEY / 2);
			m_quitButton->Render();
			m_number->Render(WINSIZEX / 2, WINSIZEY / 2 - 45, GAMESCORE);
		}
	}

	if (GAMEMANAGER->g_stageClear) {
		if (m_gamePauseBackGround)
			m_gamePauseBackGround->Render(0, 0);
		if (m_scoreboard)
			m_scoreboard->CenterRender(WINSIZEX / 2, WINSIZEY / 2 + 100);
		if (m_gameclear)
			m_gameclear->Render(0, 0);
		if (m_quitButton)
			m_quitButton->Render(WINSIZEX/2,WINSIZEY/2 + 300);
		m_number->Render(WINSIZEX / 2, WINSIZEY / 2 + 85, GAMESCORE);
	}
	if (GAMEPAUSE) {
		if (m_gamePauseBackGround)
			m_gamePauseBackGround->Render(0, 0);
		if (m_gamePauseImg)
			m_gamePauseImg->CenterRender(WINSIZEX / 2, WINSIZEY / 2);
		if (m_quitButton)
			m_quitButton->Render();
	}
}

void cFirstStageScene::UpdateProgress()
{
	if (nowTime >= m_progressTime) {
		GAMEMANAGER->SetGameProgress(GAMEMANAGER->GetGameProgress() + 1);
		m_progressTime = nowTime + 1000;
	}
}
