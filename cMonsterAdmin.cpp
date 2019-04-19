#include "DXUT.h"
#include "cMonsterAdmin.h"
#include "cMonster.h"
#include "cBullet.h"

#include "cMiddleBoss.h"
#include "cMissileMonster.h"
#include "cBoss.h"
#include "cHideMonster.h"
#include "cStage1Boss.h"

// Constructor, Destructor

cMonsterAdmin::cMonsterAdmin(vector<cBullet*>&bullet)
	:m_monsterBullets(bullet)
{
	Init();
}

cMonsterAdmin::~cMonsterAdmin()
{
	Release();
}

// Init, Update, Render, Release

void cMonsterAdmin::Init()
{
	for (auto iter : m_monsters)
		SAFE_DELETE(iter);
	m_monsters.clear();

	patternTime = 0;
	m_currentProgress = GAMEMANAGER->GetGameProgress();
	m_warring = ANIMATIONMANAGER->AddPieceAnimation("warring", 1, 50);
	m_isWarring = false;
	m_WarningPos = D3DXVECTOR2(-800, 0);
	m_warningSpeed = 800;
}

void cMonsterAdmin::Update()
{
	PatternUpdate();
	for (auto iter : m_monsters)
		iter->Update();

	MonsterDeathCheck();
	MonsterCollisionCheck();

	if (m_isWarring) {
		m_WarningPos.x += m_warningSpeed * DXUTGetElapsedTime();
		if (m_WarningPos.x < 0) {
			if (m_warningSpeed > 100)
				m_warningSpeed -= 5;
		}
		else {
			m_warningSpeed += 30;
		}
		if (nowTime > m_warringTime)
			m_isWarring = false;
	}
}

void cMonsterAdmin::Render()
{
	for (auto iter : m_monsters) iter->Render();
	if (m_isWarring) m_warring->Render(m_WarningPos.x, m_WarningPos.y, 1.0, 0, D3DCOLOR_ARGB(55, 255, 255, 255));
}

void cMonsterAdmin::Release()
{
	for (auto iter : m_monsters) {
		SAFE_DELETE(iter);
	}
	m_monsters.clear();
	SAFE_DELETE(m_warring);
}

// Monster Creator

cMonster * cMonsterAdmin::CreateMonster(D3DXVECTOR2 pos, float hp, float speed, float damage,int pattern,int type,int mway)
{
	cMonster* newMonster = nullptr;
	try {
		switch (type) {
		case e_missile:
			newMonster = new cMissileMonster(m_monsterBullets, pos, speed, pattern, mway);
			break;
		case e_middleboss:
			newMonster = new cMiddleBoss(m_monsterBullets, pos, speed, pattern, mway);
			break;
		case e_boss:
			newMonster = new cBoss(m_monsterBullets, pos, speed, pattern);
			break;
		case e_hideMonster:
			newMonster = new cHideMonster(m_monsterBullets, pos, speed, pattern);
			break;
		case e_stage1Boss:
			newMonster = new cStage1Boss(m_monsterBullets, pos);
			break;
		default:
			DEBUG_LOG("monster create failed");
			throw false;
		}
	}
	catch (bool b) {
		return nullptr;
	}
	m_monsters.push_back(newMonster);
	return newMonster;
}
void cMonsterAdmin::MonsterDeathCheck() {
	size_t size = m_monsters.size();

	for (size_t i = 0; i < size; i++) {
		auto iter = m_monsters[i];
		if (iter->GetState() == false) {
			if (!GAMEMANAGER->g_stageClear) {
				switch (iter->GetMonsterType()) {
				case cMonster::e_monsterType_missile:
					SETSCORE(GAMESCORE + 10);
					break;

				case cMonster::e_monsterType_middleBoss:
					SETSCORE(GAMESCORE + 30);
					break;

				case cMonster::e_monsterType_Boss:
					SETSCORE(GAMESCORE + 50);
					break;

				case cMonster::e_monsterType_hideMonster:
					SETSCORE(GAMESCORE + 30);

					break;
				case cMonster::e_monsterType_stage1Boss:
					SETSCORE(GAMESCORE + 100);
					break;
				}
				SAFE_DELETE(iter);
				m_monsters.erase(m_monsters.begin() + i);
				i--; size--;
			}
		}
	}
}
void cMonsterAdmin::MonsterCollisionCheck()
{
	size_t size = m_monsters.size();

	GAMEMANAGER->SetNearbyMonsterPos(D3DXVECTOR2(WINSIZEX/2,0));

	if (size == 0)
		GAMEMANAGER->SetNearbyMonsterPos(D3DXVECTOR2(GAMEMANAGER->GetPlayerPos().x, GAMEMANAGER->GetPlayerPos().y - 1000));

	D3DXVECTOR2 pos = GAMEMANAGER->GetNearbyMonsterPos();

	for (size_t i = 0; i < size; i++) {

		auto iter = m_monsters[i];

		if (FloatSquare(GAMEMANAGER->GetPlayerPos().x - pos.x) + FloatSquare(GAMEMANAGER->GetPlayerPos().y - pos.y) >
			FloatSquare(GAMEMANAGER->GetPlayerPos().x - iter->GetMonsterPos().x) + FloatSquare(GAMEMANAGER->GetPlayerPos().y - iter->GetMonsterPos().y)) {
			if (iter->GetMonsterType() != cMonster::e_monsterType_hideMonster)
				pos = iter->GetMonsterPos();
		}

		if (iter->isOutMap()) {
			iter->Release();
			SAFE_DELETE(iter);
			m_monsters.erase(m_monsters.begin() + i);
			size--; i--;
		}
	}
	GAMEMANAGER->SetNearbyMonsterPos(pos);
}

// ============================================================================================================================ //
// *= Monster Patterns

void cMonsterAdmin::missileUnit(int flag)
{
	if (m_MonsterStand[flag]) {
		return;
	}
	else m_MonsterStand[flag] = true;
	switch (flag) {
	case e_left:
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 2; j++) {
				CreateMonster(D3DXVECTOR2(100 + j * 50, -400 + i * 60), 1, 300 + i * 15, 1, 1, e_missile);
			}
		}
		break;
	case e_mid:
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 2; j++) {
				CreateMonster(D3DXVECTOR2(WINSIZEX / 2 - 10 + j * 50, -400 + i * 60), 1, 300 + i * 15, 1, 1, e_missile);
			}
		}
		break;
	case e_right:
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 2; j++) {
				CreateMonster(D3DXVECTOR2(WINSIZEX - 100 - j * 50, -400 + i * 60), 1, 300 + i * 15, 1, 1, e_missile);
			}
		}
		break;
	default:
		DEBUG_LOG("[missileUnit] 패턴 flag 값이 잘못되었습니다.");
	}
}
void cMonsterAdmin::updownmissile(int flag)
{
	switch (flag) {
	case e_left:
		for (int i = 0; i < 4; i++) {
			CreateMonster(D3DXVECTOR2(150 + i * 40, -100 + 30 * i), 1, 250 + 50 * i, 1, 3, e_missile, 0);
		}
		break;
	case e_mid:
		for (int i = 0; i < 3; i++) {
			CreateMonster(D3DXVECTOR2(WINSIZEX / 2 + i * 40, -100 + 30 * i + (i == 2) ? -60 : 0), 1, 250 + 50 * i, 1, 3, e_missile, 0);
		}
		break;
	case e_right:
		for (int i = 0; i < 4; i++) {
			CreateMonster(D3DXVECTOR2(WINSIZEX - 150 - i * 40, -100 + 30 * i), 1, 250 + 50 * i, 1, 3, e_missile, 0);
		}
		break;
	case e_random:
		for (int i = 0; i < 3; i++) {
			CreateMonster(D3DXVECTOR2(rand() % (WINSIZEX - 50), -100 + 30 * i), 1, 200 + 50 * i, 1, 3, e_missile, 0);
		}
		break;
	}
}
void cMonsterAdmin::sideMissile(int flag)
{
	if (m_MonsterStand[flag]) {
		return;
	}
	else m_MonsterStand[flag] = true;
	switch (flag) {
	case e_left:
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 2; j++) {
				CreateMonster(D3DXVECTOR2(j * 50, WINSIZEY / 2 + i * 60), 1, 300, 1, 2, e_missile, 0);
			}
		}
		break;
	case e_right:
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 2; j++) {
				CreateMonster(D3DXVECTOR2(WINSIZEX - j * 50, WINSIZEY / 2 + i * 60), 1, 300, 1, 2, e_missile, 1);
			}
		}
		break;
	default:
		DEBUG_LOG("[sideMissile] 패턴 flag 값이 잘못되었습니다.");
		break;
	}
}
void cMonsterAdmin::middleBoss(int flag)
{
	if (m_MonsterStand[flag]) {
		return;
	}
	else m_MonsterStand[flag] = true;
	switch (flag) {
	case e_left:
		CreateMonster(D3DXVECTOR2(100, -200), 5, 150, 2, 1, e_middleboss, 0);
		break;
	case e_mid:
		CreateMonster(D3DXVECTOR2(WINSIZEX / 2, -200), 5, 150, 2, 1, e_middleboss, 0);
		break;
	case e_right:
		CreateMonster(D3DXVECTOR2(WINSIZEX - 100, -200), 5, 150, 2, 1, e_middleboss, 0);
		break;
	default:
		DEBUG_LOG("[middleBoss] 패턴 flag 값이 잘못되었습니다.");
		break;
	}
}
void cMonsterAdmin::updownmiddleBoss(int flag)
{
	switch (flag) {
	case e_right:
		CreateMonster(D3DXVECTOR2(150, -100), 5, 300, 2, 3, e_middleboss, 0);
		break;
	case e_mid:
		CreateMonster(D3DXVECTOR2(WINSIZEX / 2, -100), 5, 300, 2, 3, e_middleboss, 0);
		break;
	case e_left:
		CreateMonster(D3DXVECTOR2(WINSIZEX - 150, -100), 5, 300, 2, 3, e_middleboss, 0);
		break;
	default:
		break;
	}
}
void cMonsterAdmin::sideMiddleBoss(int flag)
{
	switch (flag) {
	case e_left:
		CreateMonster(D3DXVECTOR2(-100, WINSIZEY / 2 - 200), 5, 100, 2, 2, e_middleboss, 0);
		break;
	case e_right:
		CreateMonster(D3DXVECTOR2(WINSIZEX + 100, WINSIZEY / 2 - 200), 5, 100, 2, 2, e_middleboss, 1);
		break;
	default:
		DEBUG_LOG("[sideMiddleBoss] 패턴 flag 값이 잘못되었습니다.");
		break;
	}
}
void cMonsterAdmin::Boss(int flag)
{
	if (m_MonsterStand[flag]) {
		return;
	}
	else m_MonsterStand[flag] = true;
	switch (flag) {
	case e_left:
		CreateMonster(D3DXVECTOR2(100, 0), 40, 200, 4, 1, e_boss);
		break;
	case e_mid:
		CreateMonster(D3DXVECTOR2(WINSIZEX / 2, 0), 40, 200, 4, 1, e_boss);
		break;
	case e_right:
		CreateMonster(D3DXVECTOR2(WINSIZEX - 100, 0), 40, 200, 4, 1, e_boss);
		break;
	default:
		DEBUG_LOG("[boss] 패턴 flag 값이 잘못되었습니다.");
		break;
	}
}
void cMonsterAdmin::HideMonster(int flag)
{
	switch (flag) {
	case e_left:
		CreateMonster(D3DXVECTOR2(rand() % (WINSIZEX / 3), rand() % (WINSIZEY / 2)), 10, 100, 2, 1, e_hideMonster);
		break;
	case e_mid:
		CreateMonster(D3DXVECTOR2(rand() % (WINSIZEX / 3) + WINSIZEX/3, rand() % (WINSIZEY / 2)), 10, 100, 2, 1, e_hideMonster);
		break;
	case e_right:
		CreateMonster(D3DXVECTOR2(rand() % (WINSIZEX / 3) + (WINSIZEX / 3) * 2, rand() % (WINSIZEY / 2)), 10, 100, 2, 1, e_hideMonster);
		break;
	case e_random:
		CreateMonster(D3DXVECTOR2(rand() % WINSIZEX, rand() % (WINSIZEY / 2)), 10, 100, 2, 1, e_hideMonster);
		break;
	default:
		break;
	}
}
void cMonsterAdmin::Stage1Boss()
{
	CreateMonster(D3DXVECTOR2(WINSIZEX / 2, -100), 200, 100, 3, 1, e_stage1Boss);
}
void cMonsterAdmin::Warring()
{
	m_isWarring = true;
	m_warringTime = nowTime + 3000;
}

//
// ============================================================================================================================= //

// Pattern Update

void cMonsterAdmin::PatternUpdate()
{
	if (m_currentProgress != GAMEMANAGER->GetGameProgress()) {
		switch (GAMEMANAGER->GetGameProgress()) {
		case 1:
			updownmissile(e_left);
			break;
		case 3:
			updownmissile(e_right);
			break;
		case 5:
			updownmissile(e_mid);
			break;
		case 7:
			updownmissile(e_random);
			break;
		case 8:
			updownmissile(e_random);
			break;
		case 9:
			updownmissile(e_random);
			break;
		case 12:
			sideMiddleBoss(e_left);
			break;
		case 13:
			sideMiddleBoss(e_right);
			break;
		case 22:
			updownmiddleBoss(e_left);
			break;
		case 23:
			updownmiddleBoss(e_mid);
			break;
		case 24:
			updownmiddleBoss(e_right);
			break;
		case 30:
			sideMissile(e_right);
			break;
		case 33:
			missileUnit(e_left);
			break;
		case 34:
			missileUnit(e_right);
			break;
		case 35:
			missileUnit(e_mid);
			break;
		case 39:
			Boss(e_mid);
			break;
		case 40:
			HideMonster(e_left);
			break;
		case 41:
			HideMonster(e_right);
			break;
		case 42:
			HideMonster(e_mid);
			break;
		case 43:
			HideMonster(e_random);
			break;
		case 45:
			sideMiddleBoss(e_left);
			sideMiddleBoss(e_right);
			Boss(e_mid);
			break;
		case 50:
			sideMiddleBoss(e_left);
			break;
		case 52:
			sideMiddleBoss(e_right);
			break;
		case 58:
			Warring();
			break;
		case 61:
			Stage1Boss();
			break;
		case 76:
			missileUnit(e_left);
			break;
		case 78:
			missileUnit(e_right);
			break;
		}
		m_currentProgress = GAMEMANAGER->GetGameProgress();
		for (int i = 0; i < 3; i++) {
			m_MonsterStand[i] = false;
		}
	}
}
