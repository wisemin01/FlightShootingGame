#include "DXUT.h"
#include "cTextManager.h"
#include "cImageManager.h"


extern LPD3DXSPRITE m_sprite;

cTextManager::cTextManager()
{
	Init();
}


cTextManager::~cTextManager()
{
	m_font->Release();
}

void cTextManager::Init()
{
	D3DXFONT_DESC dese = {
		50, 0
		, FW_BOLD, 1, TRUE
		, HANGUL_CHARSET
		, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE
		, TEXT("ÇÑÃÊ·Òµ¸¿ò")
	};

	D3DXCreateFontIndirect(g_device, &dese, &m_font);
}

void cTextManager::drawText(string string, D3DXVECTOR2 pos, D3DXCOLOR color)
{
	TCHAR* txt = StringToTCHAR(string);
	RECT rcFont = { 0 };

	D3DXMATRIX matTrans;
	D3DXMatrixTranslation(&matTrans,
		pos.x,
		pos.y,
		0);

	m_sprite->SetTransform(&matTrans);
	m_font->DrawTextW(m_sprite, txt, lstrlen(txt), &rcFont, DT_NOCLIP, color);
	SAFE_DELETE(txt);
}
