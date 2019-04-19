#pragma once
class cBullet;
class cMonster;
class cPlayer;
class cShipPlayer;
class cCollisionAdmin
{
private:
	vector<cBullet*> &	m_playerBullet;
	vector<cBullet*> &	m_monsterBullet;
	vector<cMonster*>&	m_monster;
	cPlayer*			m_player;
	cShipPlayer*		m_shipPlayer;
public:
	cCollisionAdmin(vector<cBullet*>&playerBullet, vector<cBullet*>&monsterBullet,
		vector<cMonster*>&monster, cPlayer *player);
	cCollisionAdmin(vector<cBullet*>&playerBullet, vector<cBullet*>&monsterBullet,
		vector<cMonster*>&monster, cShipPlayer *shipplayer);
	virtual ~cCollisionAdmin();

	void Init();
	void Update();
	void Render();
	void Release();
};

