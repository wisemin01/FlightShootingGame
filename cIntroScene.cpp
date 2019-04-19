#include "DXUT.h"
#include "cIntroScene.h"


cIntroScene::cIntroScene()
{
}


cIntroScene::~cIntroScene()
{
}

void cIntroScene::Init()
{
	m_introImg = IMAGE("introImg");
	m_introImg2 = IMAGE("introImg2");
	m_renderState = 0;
	Sleep(100);
}

void cIntroScene::Update()
{
	if (KEY_DOWN(VK_RETURN) || KEY_DOWN(VK_LBUTTON)) {
		if (m_renderState == 0) {
			m_renderState++;
			Sleep(100);
		}
		else if (m_renderState == 1)
			SCENEMANAGER->ChangeScene("title");
	}
}

void cIntroScene::Render()
{	
	if (m_renderState == 0)
		m_introImg->Render(0, 0);
	else if (m_renderState == 1)
		m_introImg2->Render(0, 0);
}

void cIntroScene::Release()
{
	IMAGEMANAGER->DeleteImage("introImg");
	IMAGEMANAGER->DeleteImage("introImg2");
}
