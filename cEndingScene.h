#pragma once
#include "cScene.h"

class cScroolMap;
class cNumber;

class cEndingScene :
	public cScene
{
private:
	char m_CurKeyState[256];
	char m_OldKeyState[256];

	cScroolMap* m_scrool;
	texture * m_back;
	texture* m_name;
	cNumber* m_number;

	DWORD	 m_nowTime;
public:
	cEndingScene();
	~cEndingScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

