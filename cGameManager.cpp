#include "DXUT.h"
#include "cGameManager.h"


void cGameManager::Init()
{
	g_score = 0;
	g_name = "";
	g_gamePause = false;
	g_stageClear = false;
}

void cGameManager::Release()
{
	g_scorelist.clear();
}

cGameManager::cGameManager()
{
	Init();
}

cGameManager::~cGameManager()
{
	Release();
}

void cGameManager::LoadScore()
{
	FILE* stream;
	stream = fopen("./data/data.txt","r+");
	if (stream == NULL)
		DEBUG_LOG("open error");
	for (int i = 0; i < 5; i++)
	{
		string tempstr = "";
		UINT   tempInt = 0;
		fscanf(stream, "%s %d", tempstr.c_str(), &tempInt);
		g_scorelist.insert(make_pair(tempInt, tempstr.c_str()));
	}
	fclose(stream);
}

void cGameManager::SaveScore()
{
	FILE* stream;
	stream = fopen("./data/data.txt", "w");

	g_scorelist.insert(make_pair(g_score, g_name.c_str()));
	if (g_scorelist.size() > 5) {
		auto find = --g_scorelist.end();
		g_scorelist.erase(find);
	}

	for (auto iter : g_scorelist)
	{
		fprintf(stream, "%s %d\n", iter.second.c_str(), iter.first);
	}
	fclose(stream);
}

map<UINT, string, greater<UINT>>& cGameManager::GetScoreList()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return g_scorelist;
}
