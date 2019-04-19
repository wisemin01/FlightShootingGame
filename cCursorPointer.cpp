#include "DXUT.h"
#include "cCursorPointer.h"


cCursorPointer::cCursorPointer(D3DXVECTOR2 pos)
	:cUI(pos)
{
	Init();
}

cCursorPointer::~cCursorPointer()
{
	Release();
}

void cCursorPointer::Init()
{
	m_mousePointer = IMAGE("mousePointer");
}

void cCursorPointer::Update()
{
	m_pos = MOUSE_POS;
}

void cCursorPointer::Render()
{
	m_mousePointer->CenterRender(m_pos.x, m_pos.y, 1.0, 0.0, D3DCOLOR_ARGB(200, 255, 255, 255));
}

void cCursorPointer::Release()
{
}
