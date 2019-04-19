#include "DXUT.h"
#include "cNumber.h"


cNumber::cNumber(float size) 
	:cUI(D3DXVECTOR2(0,0)),m_size(size)
{
	m_NumberImage = ANIMATIONMANAGER->AddPieceAnimation("number", 10, 50);
}

cNumber::~cNumber()
{
	Release();
}

void cNumber::Render(float x, float y, int number)
{
	string strNum = std::to_string(number);
	float temp = 0;

	for (int i = 0; i < strNum.size(); i++) {
		char str = strNum[i];
		int numberBuffer = str - 48;
		m_NumberImage->sceneCenterRender(x - 30 + temp * m_size * 0.8, y, m_size, 0, OriginalColor, numberBuffer);
		temp += 30;
	}
}

void cNumber::Init()
{

}

void cNumber::Update()
{

}

void cNumber::Render()
{

}

void cNumber::Release()
{
	SAFE_DELETE(m_NumberImage);
}
