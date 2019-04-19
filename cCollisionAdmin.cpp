#include "DXUT.h"
#include "cCollisionAdmin.h"
#include "cMonster.h"
#include "cPlayer.h"
#include "cShipPlayer.h"
#include "cBullet.h"

cCollisionAdmin::cCollisionAdmin(vector<cBullet*>& playerBullet, vector<cBullet*>& monsterBullet, vector<cMonster*>& monster, cPlayer *player)
	:m_playerBullet(playerBullet),m_monsterBullet(monsterBullet),m_monster(monster),m_player(player)
{
	m_shipPlayer = NULL;
}

cCollisionAdmin::cCollisionAdmin(vector<cBullet*>& playerBullet, vector<cBullet*>& monsterBullet, vector<cMonster*>& monster, cShipPlayer * shipplayer)
	: m_playerBullet(playerBullet), m_monsterBullet(monsterBullet), m_monster(monster), m_shipPlayer(shipplayer)
{
	m_player = NULL;
}

cCollisionAdmin::~cCollisionAdmin()
{
}

void cCollisionAdmin::Init()
{
}

void cCollisionAdmin::Update()
{
	RECT rc;

	size_t size = m_monsterBullet.size();
	for (size_t i = 0; i < size; i++) {
		auto iter = m_monsterBullet[i];

		auto player_rc = m_player ? m_player->GetRect() : m_shipPlayer->GetRect();

		if (IntersectRect(&rc, &iter->GetRect(), &player_rc)) {
			if (m_player)
				m_player->SetHp(m_player->GetHp() - iter->GetDamage());
			if (m_shipPlayer)
				m_shipPlayer->SetHp(m_shipPlayer->GetHp() - iter->GetDamage());
			SAFE_DELETE(iter);
			m_monsterBullet.erase(m_monsterBullet.begin() + i);
			size--; i--;
			break;
		}
	}
	size = m_playerBullet.size();
	for (size_t i = 0; i < size; i++) {
		auto iter = m_playerBullet[i]; 
		for (auto iter2 : m_monster) {
			if (IntersectRect(&rc, &iter->GetRect(), &iter2->GetRect())) {
				if (iter2->GetAniPlayTime() == true)
				{
					;
				}
				else {
					iter2->SetHp(iter2->GetHp() - iter->GetDamage());
					SAFE_DELETE(iter);
					m_playerBullet.erase(m_playerBullet.begin() + i);
					size--; i--;
					break;
				}
			}
		}
	}

	size = m_monsterBullet.size();

	for (size_t i = 0; i < size; i++) {
		auto iter = m_monsterBullet[i];
		if (iter->IsDeathUnit()) {
			SAFE_DELETE(iter);
			m_playerBullet.erase(m_playerBullet.begin() + i);
			size--; i--;
			break;
		}
	}
}

void cCollisionAdmin::Render()
{
}

void cCollisionAdmin::Release()
{
}
