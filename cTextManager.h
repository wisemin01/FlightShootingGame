#pragma once
#include "singleton.h"

class cTextManager :
	public singleton<cTextManager>
{
private:
	LPD3DXFONT m_font;
public:
	cTextManager();
	~cTextManager();

	void Init();
	void drawText(string string, D3DXVECTOR2 pos, D3DXCOLOR color = D3DCOLOR_XRGB(255,255,255));
};

#define TEXTMANAGER cTextManager::GetInstance()