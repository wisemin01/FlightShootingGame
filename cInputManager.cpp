#include "DXUT.h"
#include "cInputManager.h"


cInputManager::cInputManager()
{	
	memset(m_keyMap, 0, sizeof(m_keyMap));
	m_CursorState = true;
}

cInputManager::~cInputManager()
{
}

void cInputManager::Update()
{
	memcpy(m_OldKeyState, m_CurKeyState, 256);
	memset(m_CurKeyState, KEY_NONE, sizeof(m_CurKeyState));

	GetKeyboardState(m_CurKeyState);

	for (int i = 0; i < 256; i++) {
		BYTE vkey = m_CurKeyState[i] & 0x80;
		m_CurKeyState[i] = (vkey) ? 1 : 0;

		INT nOld = m_OldKeyState[i];
		INT nCur = m_CurKeyState[i];

		if (nOld == 1 && nCur == 1) m_keyMap[i] = KEY_RETAIN;
		else if (nOld == 0 && nCur == 1) m_keyMap[i] = KEY_DOWN;
		else if (nOld == 1 && nCur == 0) m_keyMap[i] = KEY_UP;
		else m_keyMap[i] = KEY_NONE;
	}

	POINT pt;

	GetCursorPos(&pt);
	ScreenToClient(DXUTGetHWND(), &pt);
	
	m_mousePos = D3DXVECTOR2(pt.x, pt.y);
}

INT cInputManager::GetKeyRetain(INT key_number)
{
	return (m_keyMap[key_number] == KEY_RETAIN);
}

INT cInputManager::GetKeyDown(INT key_number)
{
	return (m_keyMap[key_number] == KEY_DOWN);
}

INT cInputManager::GetKeyUp(INT key_number)
{
	return m_keyMap[key_number] == KEY_UP;
}

void cInputManager::ShowCursor(bool flag)
{
	::ShowCursor(flag);
	m_CursorState = flag;
}

D3DXVECTOR2 cInputManager::GetMousePos()
{
	return m_mousePos;
}
