#pragma once
#include "singleton.h"
class cGameManager :
	public singleton<cGameManager>
{
private:
	UINT	g_score;
	UINT	g_gameProgress;

	map<UINT, string, greater<UINT>> g_scorelist;

	D3DXVECTOR2 m_playerPos;
	D3DXVECTOR2 m_NearbyMonsterPos;

private:
	void Init();
	void Release();
public:
	cGameManager();
	~cGameManager();

	UINT GetScore() { return g_score; }
	UINT GetGameProgress() { return g_gameProgress; }

	void SetScore(UINT n_score) { g_score = n_score; }
	void SetGameProgress(UINT n_progress) { g_gameProgress = n_progress; }
public:
	void LoadScore();
	void SaveScore();

public:
	void SetPlayerPos(D3DXVECTOR2 playerPos) { m_playerPos = playerPos; }
	D3DXVECTOR2 GetPlayerPos() { return m_playerPos; }
	void SetNearbyMonsterPos(D3DXVECTOR2 NearbyMonsterPos) { m_NearbyMonsterPos = NearbyMonsterPos; }
	D3DXVECTOR2 GetNearbyMonsterPos() { return m_NearbyMonsterPos; }

	map<UINT, string, greater<UINT>>& GetScoreList();

	BOOL	g_gamePause;
	BOOL	g_stageClear;

	string	g_name;

};

#define GAMEMANAGER cGameManager::GetInstance()
#define GAMEPAUSE	GAMEMANAGER->g_gamePause