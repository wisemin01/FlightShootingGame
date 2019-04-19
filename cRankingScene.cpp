#include "DXUT.h"
#include "cRankingScene.h"
#include "cScroolMap.h"
#include "cNumber.h"

cRankingScene::cRankingScene()
{
}


cRankingScene::~cRankingScene()
{
}

void cRankingScene::Init()
{
	m_rankingBoard = IMAGE("rankingBoard");
	m_rankingBlocks = IMAGE("rankingBlocks");
	m_backGround = new cScroolMap();
	m_number = new cNumber(1.0);
}

void cRankingScene::Release()
{
	SAFE_DELETE(m_backGround);
	SAFE_DELETE(m_number);
}

void cRankingScene::Update()
{
	m_backGround->Update(120);
	if (KEY_RETAIN(VK_BACK)) {
		SCENEMANAGER->ChangeScene("title");
	}
}

void cRankingScene::Render()
{
	int i = 0;

	m_backGround->Render();

	m_rankingBoard->CenterRender(WINSIZEX / 2, WINSIZEY / 2);
	m_rankingBlocks->CenterRender(WINSIZEX / 2, WINSIZEY / 2);

	for (auto iter : GAMEMANAGER->GetScoreList()) {
		m_number->Render(WINSIZEX / 2, WINSIZEY / 2 - 200 + 100 * i, iter.first);
		TEXTMANAGER->drawText(iter.second, D3DXVECTOR2(WINSIZEX / 2 - 200, WINSIZEY / 2 - 230 + 100 * i));
		i++;
	}
}

//IMAGEMANAGER->GetFont()->DrawTextW(IMAGEMANAGER->GetSprite(),
//(*iter)->m_Name, lstrlen((*iter)->m_Name), &rcFont, DT_NOCLIP | DT_CENTER, D3DCOLOR_ARGB(255, 255, 255, 255));