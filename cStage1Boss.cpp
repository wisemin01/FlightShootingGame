#include "DXUT.h"
#include "cStage1Boss.h"

#include "cMonsterBullet.h"
#include "cAccelBullet.h"
#include "cSplitBullet.h"

void cStage1Boss::SetRect()
{
	m_monsterRect = {
		(LONG)(m_pos.x - 130),
		(LONG)(m_pos.y - 70),
		(LONG)(m_pos.x + 130),
		(LONG)(m_pos.y + 70)
	};
}

void cStage1Boss::UpdateProgress()
{
	if (nowTime > m_patternCountTime) {
		m_progress ++;
		m_patternCountTime = nowTime + 500;
	}
}

cStage1Boss::cStage1Boss(vector<cBullet*>& monsterBullet, D3DXVECTOR2 pos, float speed)
	: cMonster(monsterBullet, pos, 200, 1)
{
	Init();
}

cStage1Boss::~cStage1Boss()
{
	Release();
}

void cStage1Boss::Init()
{
	m_stage1BossImg = ANIMATIONMANAGER->AddPieceAnimation("stage1Boss", 21, 50);
	m_explode = ANIMATIONMANAGER->AddPieceAnimation("explodeEffect", 36, 40);
	m_progress = 0;
	m_patternCountTime = 0;
	m_hp = 500;
	m_isdeathAnimationPlayTime = 0;
	m_state = idle;
	m_speed = 100;
	m_monsterType = e_monsterType_stage1Boss;
}

void cStage1Boss::Update()
{
	if (m_pos.y < 200) {
		m_pos.y += m_speed * DXUTGetElapsedTime();
	}
	else {
		if (m_state == idle) {
			if (m_isdeathAnimationPlayTime == 0) {
				UpdateProgress();
				BossPattern();
				SetRect();
			}
		}
		if (m_hp < 0) {
			if (m_isdeathAnimationPlayTime == 0)
				m_isdeathAnimationPlayTime = nowTime + 1000;
		}
		if (m_isdeathAnimationPlayTime != 0) {
			if (m_isdeathAnimationPlayTime < nowTime)
				cMonster::m_state = death;
			GAMEMANAGER->g_stageClear = true;
		}
	}
	if (m_prevHp != m_hp) {
		m_hitTime = nowTime + 50;
	}
	m_prevHp = m_hp;
}

void cStage1Boss::Render()
{
	if (m_isdeathAnimationPlayTime > 0)
		m_explode->CenterRender(m_pos.x, m_pos.y, 1.2, 0);
	else {
		if(m_pos.y < 200)
		m_stage1BossImg->CenterRender(m_pos.x, m_pos.y);
		else {
			if (m_hitTime > nowTime) {
				m_stage1BossImg->sceneCenterRender(m_pos.x, m_pos.y, 1.0, 0.0, D3DCOLOR_XRGB(255, 200, 200), 0);
			}
			else
			m_stage1BossImg->sceneCenterRender(m_pos.x, m_pos.y, 1.0, 0.0, OriginalColor, 0);
		}
	}
}

void cStage1Boss::Release()
{
	SAFE_DELETE(m_explode);
	SAFE_DELETE(m_stage1BossImg);
}

void cStage1Boss::BossPattern()
{

	D3DXVECTOR2 dirc = GAMEMANAGER->GetPlayerPos() - m_pos;
	D3DXVec2Normalize(&dirc, &dirc);
	FLOAT rad_step;
	FLOAT rad;
	D3DXVECTOR2 dir;


	if (m_prevProgress != m_progress) {
		switch (m_progress) {
		case 1:
			for (int i = 0; i < 10; i++) {
				m_fireBullet.push_back(new cMonsterBullet(D3DXVECTOR2(m_pos.x, m_pos.y + 130), 400 + 50 * i, 1, 0, dirc));
			}
			break;
		case 2:
			for (int i = 0; i < 10; i++) {
				m_fireBullet.push_back(new cMonsterBullet(D3DXVECTOR2(m_pos.x, m_pos.y + 130), 400 + 50 * i, 1, 0, dirc));
			}
			break;

		case 3:
			for (int i = 0; i < 10; i++) {
				m_fireBullet.push_back(new cMonsterBullet(D3DXVECTOR2(m_pos.x, m_pos.y + 130), 400 + 50 * i, 1, 0, dirc));
			}
			break;
		case 4:
			for (int i = 0; i < 10; i++) {
				m_fireBullet.push_back(new cMonsterBullet(D3DXVECTOR2(m_pos.x, m_pos.y + 130), 400 + 50 * i, 1, 0, dirc));
			}
			break;
		case 5:
			for (int i = 0; i < 10; i++) {
				m_fireBullet.push_back(new cMonsterBullet(D3DXVECTOR2(m_pos.x, m_pos.y + 130), 400 + 50 * i, 1, 0, dirc));
			}
			break;
		case 10:
			m_fireBullet.push_back(new cSplitBullet(D3DXVECTOR2(m_pos.x, m_pos.y + 130), 1.0, 100, 3, 40, D3DXVECTOR2(0, 1), m_fireBullet, 3000));
			m_fireBullet.push_back(new cSplitBullet(D3DXVECTOR2(m_pos.x, m_pos.y + 130), 1.0, 50, 3, 15, D3DXVECTOR2(0.3, 1), m_fireBullet, 3500));
			m_fireBullet.push_back(new cSplitBullet(D3DXVECTOR2(m_pos.x, m_pos.y + 130), 1.0, 50, 3, 15, D3DXVECTOR2(-0.3, 1), m_fireBullet, 3500));
			break;
		case 15:
			rad_step = M_PI / 180 * 10;
			rad = 20 % 2 ? -20 / 2 * rad_step : (-20 / 2 + 0.5)*rad_step;
			dir = D3DXVECTOR2(0, 1);
			for (int i = 0; i < 20; i++, rad += rad_step) {
				float c = cos(rad), s = sin(rad);
				D3DXVECTOR2 dir02 = D3DXVECTOR2(dir.x * c - dir.y * s, dir.x*s + dir.y*c);
				D3DXVec2Normalize(&dir02, &dir02);
				m_fireBullet.push_back(new cMonsterBullet(D3DXVECTOR2(m_pos.x, m_pos.y + 130), 300, 1, 0, dir02));
			}
			break;
		case 17:
			rad_step = M_PI / 180 * 8;
			rad = 25 % 2 ? -25 / 2 * rad_step : (-25 / 2 + 0.5)*rad_step;
			dir = D3DXVECTOR2(0, 1);
			for (int i = 0; i < 25; i++, rad += rad_step) {
				float c = cos(rad), s = sin(rad);
				D3DXVECTOR2 dir02 = D3DXVECTOR2(dir.x * c - dir.y * s, dir.x*s + dir.y*c);
				D3DXVec2Normalize(&dir02, &dir02);
				m_fireBullet.push_back(new cMonsterBullet(D3DXVECTOR2(m_pos.x, m_pos.y + 130), 300, 1, 0, dir02));
			}
			break;
		case 25:
			m_fireBullet.push_back(new cAccelBullet(D3DXVECTOR2(m_pos.x, m_pos.y + 130), 400, 2, 0, dirc));
			break;
		case 26:
			m_fireBullet.push_back(new cAccelBullet(D3DXVECTOR2(m_pos.x, m_pos.y + 130), 400, 2, 0, dirc));
			break;
		case 27:
			m_fireBullet.push_back(new cAccelBullet(D3DXVECTOR2(m_pos.x, m_pos.y + 130), 400, 2, 0, dirc));
			break;
		case 28:
			m_fireBullet.push_back(new cAccelBullet(D3DXVECTOR2(m_pos.x, m_pos.y + 130), 400, 2, 0, dirc));
			break;
		case 29:
			m_fireBullet.push_back(new cAccelBullet(D3DXVECTOR2(m_pos.x, m_pos.y + 130), 400, 2, 0, dirc));
			break;
		case 30:
			m_fireBullet.push_back(new cAccelBullet(D3DXVECTOR2(m_pos.x, m_pos.y + 130), 400, 2, 0, dirc));
			break;
		case 31:
			m_progress = 0;
			break;
		}
		m_prevProgress = m_progress;
	}
}
// ºÐ¿­Åº ÄÚµå
// m_fireBullet.push_back(new cSplitBullet(m_pos, 1.0, 100, 3, 40, D3DXVECTOR2(0, 1), m_fireBullet,3000));

// n - way Åº ÄÚµå
//rad_step = M_PI / 180 * 10;
//rad = BulletCount % 2 ? -BulletCount / 2 * rad_step : (-BulletCount / 2 + 0.5)*rad_step;
//dir = D3DXVECTOR2(0, 1);
//for (int i = 0; i < BulletCount; i++, rad += rad_step) {
//	float c = cos(rad), s = sin(rad);
//	D3DXVECTOR2 dir02 = D3DXVECTOR2(dir.x * c - dir.y * s, dir.x*s + dir.y*c);
//	D3DXVec2Normalize(&dir02, &dir02);
//	m_fireBullet.push_back(new cMonsterBullet(D3DXVECTOR2(m_pos.x, m_pos.y + 70), 300, 1, 0, dir02));
//}

// ÀÏÀÚ·Î ³ª°¡´Â ÅºÈ¯
//D3DXVECTOR2 dirc = GAMEMANAGER->GetPlayerPos() - m_pos;
//D3DXVec2Normalize(&dirc, &dirc);
//for (int i = 0; i < 10; i++) {
//	m_fireBullet.push_back(new cMonsterBullet(D3DXVECTOR2(m_pos.x, m_pos.y + 130), 400 + 50 * i, 2, 0, dirc));
//}

// °¡¼ÓÅº ÄÚµå
// m_fireBullet.push_back(new cAccelBullet(D3DXVECTOR2(m_pos.x,m_pos.y + 100),400,2,0,dirc));