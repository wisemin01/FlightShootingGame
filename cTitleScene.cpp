#include "DXUT.h"
#include "cTitleScene.h"
#include "cButton.h"
#include "cScroolMap.h"
#include "cFade.h"

cTitleScene::cTitleScene()
{
}


cTitleScene::~cTitleScene()
{
}

void cTitleScene::Init()
{
	m_backGround	= new cScroolMap();

	m_startGame		= IMAGE("startButton");
	m_ranking		= IMAGE("rankingButton");
	m_quit			= IMAGE("quitButton");
	m_titleLogo		= IMAGE("titleLogo");
	m_SelectArrow	= IMAGE("buttonArrow");

	m_SeleteIndex	= 0;

	menuSelect[0]	= new cButton(WINSIZEX / 2, WINSIZEY / 2 + 50);
	menuSelect[1]	= new cButton(WINSIZEX / 2, WINSIZEY / 2 + 150);
	menuSelect[2]	= new cButton(WINSIZEX / 2, WINSIZEY / 2 + 250);
	menuSelect[3]	= new cButton(WINSIZEX / 2, WINSIZEY / 2 + 350);

	Sleep(100);
}

void cTitleScene::Update()
{
	for (int i = 0; i < 3; i++) {
		menuSelect[i]->Update();
	}

	for (int i = 0; i < 3; i++) {
		if (menuSelect[i]->isDown()) {
			switch (i) {
			case 0:
				SCENEMANAGER->ChangeScene("firstStage");
				break;
			case 1:
				SCENEMANAGER->ChangeScene("secondStage");
				break;
			case 2:
				SCENEMANAGER->ChangeScene("ranking");
				break;
			case 3:
				PostQuitMessage(1);
				break;
			}
		}
		if (menuSelect[i]->isMouseOn()) {
			switch (i) {
			case 0:
				m_SeleteIndex = 0;
				m_ArrowPos = D3DXVECTOR2(WINSIZEX / 2 - 160, WINSIZEY / 2 + 50);
				break;
			case 1:
				m_SeleteIndex = 1;
				m_ArrowPos = D3DXVECTOR2(WINSIZEX / 2 - 160, WINSIZEY / 2 + 150);
				break;
			case 2:
				m_SeleteIndex = 2;
				m_ArrowPos = D3DXVECTOR2(WINSIZEX / 2 - 160, WINSIZEY / 2 + 250);
				break;
			case 3:
				m_SeleteIndex = 3;
				m_ArrowPos = D3DXVECTOR2(WINSIZEX / 2 - 160, WINSIZEY / 2 + 350);
				break;
			default:
				break;
			}
		}
	}

	m_backGround->Update(100);

	if (KEY_DOWN(VK_UP)) {
		if (m_SeleteIndex > 0)
			m_SeleteIndex--;
	}
	if (KEY_DOWN(VK_DOWN)) {
		if (m_SeleteIndex < 4)
			m_SeleteIndex++;
	}

	switch (m_SeleteIndex) {
	case 0:
		m_ArrowPos = D3DXVECTOR2(WINSIZEX / 2 - 160, WINSIZEY / 2 + 50);
		break;
	case 1:
		m_ArrowPos = D3DXVECTOR2(WINSIZEX / 2 - 160, WINSIZEY / 2 + 150);
		break;
	case 2:
		m_ArrowPos = D3DXVECTOR2(WINSIZEX / 2 - 160, WINSIZEY / 2 + 250);
		break;
	case 3:
		m_ArrowPos = D3DXVECTOR2(WINSIZEX / 2 - 160, WINSIZEY / 2 + 350);
		break;
	default:

		break;
	}

	if (KEY_DOWN(VK_RETURN)) {
		switch (m_SeleteIndex) {
		case 0:
			SCENEMANAGER->ChangeScene("firstStage");
			break;
		case 1:
			SCENEMANAGER->ChangeScene("secondStage");
			break;
		case 2:
			SCENEMANAGER->ChangeScene("ranking");
			break;
		case 3:
			PostQuitMessage(1);
			break;
		}
	}
}

void cTitleScene::Render()
{
	m_backGround->	Render();

	m_titleLogo->	CenterRender(WINSIZEX / 2, WINSIZEY / 2 - 200);
	m_startGame->	CenterRender(WINSIZEX / 2, WINSIZEY / 2 + 50);
	m_startGame->	CenterRender(WINSIZEX / 2, WINSIZEY / 2 + 150);
	m_ranking->		CenterRender(WINSIZEX / 2, WINSIZEY / 2 + 250);
	m_quit->		CenterRender(WINSIZEX / 2, WINSIZEY / 2 + 350);

	m_SelectArrow->	CenterRender(m_ArrowPos.x, m_ArrowPos.y);
}

void cTitleScene::Release()
{
	SAFE_DELETE(m_backGround);

	for (int i = 0; i < 4; i++)
		SAFE_DELETE(menuSelect[i]);
}
