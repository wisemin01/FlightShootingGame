#include "DXUT.h"
#include "cEndingScene.h"
#include "cScroolMap.h"
#include "cNumber.h"

cEndingScene::cEndingScene()
{
	m_nowTime = 0;
}


cEndingScene::~cEndingScene()
{
}

void cEndingScene::Init()
{
	m_scrool = new cScroolMap();
	m_number = new cNumber(1.0);
	m_back = IMAGE("scoreboard");
	m_name = IMAGE("name");
}

void cEndingScene::Update()
{
	m_scrool->Update(100);

	for (int i = 65; i < 91; i++) {
		if (KEY_DOWN(i)) {
			if (GAMEMANAGER->g_name.size() <= 3) {
				GAMEMANAGER->g_name += (char)i;
			}
		}
	}
	if (m_nowTime < nowTime)
	{
		if (KEY_DOWN(VK_BACK)) {
			m_nowTime = nowTime + 100;
			GAMEMANAGER->g_name = GAMEMANAGER->g_name.substr(0, GAMEMANAGER->g_name.size() - 1);
		}
	}

	if (KEY_DOWN(VK_RETURN)) {
		if (GAMEMANAGER->g_name.size() >= 2) {
			SAVESCORE();
			SETSCORE(0);
			SCENEMANAGER->ChangeScene("title");
			GAMEMANAGER->g_name = "";
		}
	}
}

void cEndingScene::Render()
{
	m_scrool->Render();
	m_back->CenterRender(WINSIZEX / 2, WINSIZEY / 2);
	m_number->Render(WINSIZEX / 2 + 18, WINSIZEY / 2 - 20, GAMESCORE);
	m_name->CenterRender(WINSIZEX / 2 - 100, WINSIZEY / 2 + 50);
	TEXTMANAGER->drawText(GAMEMANAGER->g_name, D3DXVECTOR2(WINSIZEX / 2 + 65 - GAMEMANAGER->g_name.size() * 17.5, WINSIZEY / 2 + 20));
}

void cEndingScene::Release()
{
	SAFE_DELETE(m_scrool);
	SAFE_DELETE(m_number);
}

