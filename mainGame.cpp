#include "DXUT.h"
#include "mainGame.h"

#include "cFirstStageScene.h"
#include "cSecondStageScene.h"
#include "cIntroScene.h"
#include "cTitleScene.h"
#include "cEndingScene.h"
#include "cLoadingScene.h"
#include "cRankingScene.h"

#include <time.h>

mainGame::mainGame()
{
}

mainGame::~mainGame()
{
}

void mainGame::Init()
{
#pragma region AddScenes

	SCENEMANAGER->AddScene(	"firstStage"	,	new cFirstStageScene	);
	SCENEMANAGER->AddScene(	"secondStage"	,	new cSecondStageScene	);
	SCENEMANAGER->AddScene(	"title"			,	new cTitleScene			);
	SCENEMANAGER->AddScene(	"intro"			,	new cIntroScene			);
	SCENEMANAGER->AddScene(	"ending"		,	new cEndingScene		);
	SCENEMANAGER->AddScene(	"loading"		,	new	cLoadingScene		);
	SCENEMANAGER->AddScene( "ranking"		,	new cRankingScene		);

#pragma endregion

	SCENEMANAGER->ChangeScene("loading");

	LOADSCORE();

	srand((unsigned)time(NULL));
}

void mainGame::Release()
{
	cAnimationManager::ReleaseInstance();
	cImageManager::ReleaseInstance();
	cSceneManager::ReleaseInstance();
	cGameManager::ReleaseInstance();
	cTextManager::ReleaseInstance();
	cInputManager::ReleaseInstance();
}

void mainGame::Update()
{
	SCENEMANAGER->Update();
	INPUTMANAGER->Update();
}

void mainGame::Render()
{
	IMAGEMANAGER->Begin();
	SCENEMANAGER->Render();
	IMAGEMANAGER->End();
}

void mainGame::LostDevice()
{
}

void mainGame::ResetDevice()
{
}
