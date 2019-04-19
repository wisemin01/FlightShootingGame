#pragma once

#include <iostream>
#include <random>
#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <functional>

using namespace std;

#define g_device		DXUTGetD3D9Device()
#define nowTime			timeGetTime()
#define OriginalColor	D3DCOLOR_XRGB(255,255,255)
#define M_PI			3.14f

#define IMAGE			IMAGEMANAGER->FindImage
#define LOADIMAGE		IMAGEMANAGER->AddImage

#define ANIMATION		ANIMATIONMANAGER->FindAnimation
#define LOADANIMATION	ANIMATIONMANAGER->AddAnimation

#define GAMESCORE		GAMEMANAGER->GetScore()
#define SETSCORE(x)		GAMEMANAGER->SetScore(x)
#define SAVESCORE		GAMEMANAGER->SaveScore
#define LOADSCORE		GAMEMANAGER->LoadScore

//다이렉트X는 디바이스(device)라는 개념을 사용한다
//이 디바이스는 프로그래머가 그래픽카드를 제어할수 있는 방법을 주는 녀석이라 생각하면 된다

#ifdef _DEBUG
#define DEBUG_LOG(log) cout << log << endl;
#else
#define DEBUG_LOG(log)
#endif

const int WINSIZEX = 800;
const int WINSIZEY = 1000;

float FloatSquare(float f);
int	  randomNumber(int min, int max);

TCHAR* StringToTCHAR(string& s);

//매니저 추가
#include "cImageManager.h"
#include "cSceneManager.h"
#include "cGameManager.h"
#include "cAnimationManager.h"
#include "cTextManager.h"
#include "cInputManager.h"