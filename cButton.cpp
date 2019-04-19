#include "DXUT.h"
#include "cButton.h"


cButton::cButton(float x, float y)
	: cUI(D3DXVECTOR2(x, y))
{
	Init();
}


cButton::~cButton()
{
}

void cButton::Init()
{
	m_state = e_up;
	m_isdown = false;
	m_isMouseOn = false;
	m_buttonImg[true] = IMAGE("quitButtonUp");
	m_buttonImg[false] = IMAGE("quitButtonUp");
}


void cButton::Update()
{
	
	GetCursorPos(&m_mousepos);
	ScreenToClient(DXUTGetHWND(), &m_mousepos);

	if (m_pos.x - m_buttonImg[m_state]->info.Width / 2 <= m_mousepos.x &&
		m_pos.x + m_buttonImg[m_state]->info.Width / 2 >= m_mousepos.x &&
		m_pos.y - m_buttonImg[m_state]->info.Height / 2 <= m_mousepos.y &&
		m_pos.y + m_buttonImg[m_state]->info.Height / 2 >= m_mousepos.y)
	{
		m_state = e_down;
	}
	else m_state = e_up;
	if (m_state == e_down) {
		if (KEY_DOWN(VK_LBUTTON)) {

			m_isdown = true;
		}
	}
	if (m_state == e_down)
		m_isMouseOn = true;
	else if (m_state == e_up)
		m_isMouseOn = false;
}

void cButton::Render()
{
	m_buttonImg[m_state]->CenterRender(m_pos.x, m_pos.y);
}

void cButton::Release()
{
}

void cButton::Render(float x, float y)
{
	m_pos.x = x;
	m_pos.y = y;
	m_buttonImg[m_state]->CenterRender(x, y);
}
