#pragma once
#include "singleton.h"
class cInputManager :
	public singleton<cInputManager>
{
public:
	enum {
		KEY_RETAIN,
		KEY_DOWN,
		KEY_UP,
		KEY_NONE
	};

	BYTE m_keyMap[256];
	BYTE m_CurKeyState[256];
	BYTE m_OldKeyState[256];

	D3DXVECTOR2 m_mousePos;
	bool m_CursorState;
public:
	cInputManager();
	virtual ~cInputManager();

	void Update();

	INT GetKeyRetain(INT key_number);
	INT GetKeyDown(INT key_number);
	INT GetKeyUp(INT key_number);

	void ShowCursor(bool flag);

	BOOL GetCursorState() { return m_CursorState; }
	D3DXVECTOR2 GetMousePos();
};

#define INPUTMANAGER	cInputManager::GetInstance()

#define MOUSE_POS		INPUTMANAGER->GetMousePos()

#define KEY_RETAIN(vk)	INPUTMANAGER->GetKeyRetain(vk)
#define KEY_DOWN(vk)	INPUTMANAGER->GetKeyDown(vk)
#define KEY_UP(vk)		INPUTMANAGER->GetKeyUp(vk)