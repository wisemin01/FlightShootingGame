#include "DXUT.h"
#include "cScroolMap.h"


cScroolMap::cScroolMap()
	:m_scrool(0)
{
	m_backGround = IMAGE("mapBackGround");
}

cScroolMap::cScroolMap(texture * backGround)
	: m_scrool(0)
{
	m_backGround = backGround;
}

cScroolMap::~cScroolMap()
{
}

void cScroolMap::Update(float speed)
{
	m_scrool += speed * DXUTGetElapsedTime();
}

void cScroolMap::Render()
{
	float renderPos = (int)m_scrool % m_backGround->info.Height;
	m_backGround->Render(0, renderPos - m_backGround->info.Height);
	m_backGround->Render(0, renderPos);
}
