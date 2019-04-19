#include "DXUT.h"
#include "cLoadingScene.h"

void cLoadingScene::ImageLoading()
{
#pragma region image load

	switch (m_loadingIndex) {
	case 0:
		LOADIMAGE("introImg", "./image/intro/backGround.png");
		LOADIMAGE("introImg2", "./image/intro/backGround2.png");
		ANIMATIONMANAGER->LoadPieceAnimation("warring", "./image/ingame/backGround/warning", ".png", 1);
		ANIMATIONMANAGER->LoadPieceAnimation("number", "./image/any/score/", ".png", 10);
		break;
	case 1:
		LOADIMAGE("startButton", "./image/title/01.png");
		LOADIMAGE("rankingButton", "./image/title/02.png");
		LOADIMAGE("fade", "./image/any/fade.png");
		ANIMATIONMANAGER->LoadPieceAnimation("stage1Boss", "./image/ingame/monsterAnimation/stage1Boss/0000", ".png", 21);
		break;
	case 2:
		LOADIMAGE("quitButton", "./image/title/03.png");
		LOADIMAGE("quitButtonUp", "./image/ingame/pause/QuitbuttonUp.png");
		LOADIMAGE("quitButtonDown", "./image/ingame/pause/QuitbuttonDown.png");
		LOADIMAGE("stageclear", "./image/ingame/pause/stageclear.png");
		LOADIMAGE("scoreboard", "./image/ingame/pause/scoreboard.png");
		break;
	case 3:
		LOADIMAGE("buttonArrow", "./image/title/Arrow.png");
		LOADIMAGE("titleLogo", "./image/title/T.png");
		LOADIMAGE("gamePause", "./image/ingame/pause/gamePause.png");
		ANIMATIONMANAGER->LoadPieceAnimation("gameover", "./image/ingame/pause/0", ".png", 15);
		break;
	case 4:
		LOADIMAGE("mapBackGround", "./image/ingame/backGround/mapBackGround.png");
		LOADIMAGE("gamePauseBackGround", "./image/ingame/pause/gray.png");
		LOADIMAGE("name", "./image/ending/name.png");
		LOADIMAGE("rankingBoard", "./image/ranking/1.png");
		break;
	case 5:
		LOADIMAGE("cloud", "./image/ingame/backGround/cloudBackGround.png");
		ANIMATIONMANAGER->LoadPieceAnimation("player", "./image/ingame/playerAnimation/idle/D000", ".png", 7);
		break;
	case 6:
		ANIMATIONMANAGER->LoadPieceAnimation("missileMonster", "./image/ingame/monsterAnimation/A1100", ".png", 20);
		LOADIMAGE("grayImg", "./image/ingame/pause/1.png");
		LOADIMAGE("mousePointer", "./image/ingame/bullets/monsterBulletAni.png");
		break;
	case 7:
		ANIMATIONMANAGER->LoadPieceAnimation("middleBoss", "./image/ingame/monsterAnimation/A1100", ".png", 20);
		ANIMATIONMANAGER->LoadPieceAnimation("Boss", "./image/ingame/monsterAnimation/A1100", ".png", 20);
		break;
	case 8:
		ANIMATIONMANAGER->LoadPieceAnimation("hideMonster", "image/ingame/monsterAnimation/hideMonster/hideMonster", ".png", 1);
		LOADIMAGE("rankingBlocks", "./image/ranking/3.png");
		LOADIMAGE("ShipPlayer", "./image/ingame/playerAnimation/2/D3.png");
		break;
	case 9:
		ANIMATIONMANAGER->LoadPieceAnimation("explodeEffect", "./image/ingame/effect/A00", ".png", 36);
		ANIMATIONMANAGER->AddAnimation("playerBullet", "./image/ingame/bullets/playerBulletAni.png", 4, 30);
		break;
	case 10:
		ANIMATIONMANAGER->AddAnimation("monsterBullet", "./image/ingame/bullets/monsterBulletAni.png", 1, 30);
		ANIMATIONMANAGER->AddAnimation("playerSideBullet", "./image/ingame/bullets/playerSideBulletAni.png", 1, 30);
		break;
		//ending
	}
#pragma endregion
	m_loadingIndex++;
}

cLoadingScene::cLoadingScene()
{
}

cLoadingScene::~cLoadingScene()
{
}

void cLoadingScene::Init()
{
	ANIMATIONMANAGER->LoadPieceAnimation("loadingImg", "./image/loading/", ".png", 11);
	m_loadingIndex = 0;
	m_loadingImg = ANIMATIONMANAGER->AddPieceAnimation("loadingImg",11,60);
}

void cLoadingScene::Update()
{
	ImageLoading();
	if (m_loadingIndex == 11)
		SCENEMANAGER->ChangeScene("intro");
}

void cLoadingScene::Render()
{
	m_loadingImg->sceneRender(0, 0, 1.0, 0, OriginalColor, m_loadingIndex);
}

void cLoadingScene::Release()
{
	SAFE_DELETE(m_loadingImg);
}