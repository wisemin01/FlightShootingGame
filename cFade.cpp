#include "DXUT.h"
#include "cFade.h"


cFade::cFade()
	:cUI(D3DXVECTOR2(0, 0))
{
	m_fadeAlpha = 250;
	m_fadeType = e_fadeIn;
	Init();
}


cFade::~cFade()
{
	Release();
}

void cFade::Init()
{
	m_fade = IMAGE("fade");
}

void cFade::Update()
{
	if (m_fadeType == e_fadeIn)
		m_fadeAlpha--;
	else if (m_fadeType == e_fadeOut)
		m_fadeAlpha++;

	if (m_fadeAlpha > 255)
		m_fadeAlpha = 255;
	if (m_fadeAlpha < 0)
		m_fadeAlpha = 0;
}

void cFade::Render()
{
	m_fade->Render(m_pos.x, m_pos.y, 1.0, 0, D3DCOLOR_ARGB(m_fadeAlpha, 255, 255, 255));
}

void cFade::Release()
{
}
