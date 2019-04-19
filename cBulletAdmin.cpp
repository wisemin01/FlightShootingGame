#include "DXUT.h"
#include "cBulletAdmin.h"

#include "cBullet.h"

cBulletAdmin::cBulletAdmin()
{
	Reset();
}


cBulletAdmin::~cBulletAdmin()
{
	Reset();
}

void cBulletAdmin::Reset()
{
	for (auto iter : m_playerBullet)
		SAFE_DELETE(iter);

	for (auto iter : m_monsterBullet)
		SAFE_DELETE(iter);

	m_playerBullet.clear();
	m_monsterBullet.clear();
}

void cBulletAdmin::Update()
{
	for (auto iter : m_playerBullet) {
		iter->Update();
	}

	for (auto iter : m_monsterBullet) {
		iter->Update();
	}

	CheckCollision();
}

void cBulletAdmin::Render()
{
	for (auto iter : m_playerBullet)
		iter->Render();
	for (auto iter : m_monsterBullet)
		iter->Render();
}

void cBulletAdmin::CheckCollision()
{
	size_t size = m_playerBullet.size();

	for (size_t i = 0; i < size; i++)
	{
		auto& iter = m_playerBullet[i];
		if (iter->IsOutMap())
		{
			SAFE_DELETE(iter);
			m_playerBullet.erase(m_playerBullet.begin() + i);
			i--, size--;
		}
	}

	size = m_monsterBullet.size();

	for (size_t i = 0; i < size; i++)
	{
		auto& iter = m_monsterBullet[i];
		if (iter->IsOutMap())
		{
			SAFE_DELETE(iter);
			m_monsterBullet.erase(m_monsterBullet.begin() + i);
			i--, size--;
		}
	}
}