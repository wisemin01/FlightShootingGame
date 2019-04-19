#pragma once
#include "singleton.h"

struct animation {

	LPDIRECT3DTEXTURE9 texturePtr;
	D3DXIMAGE_INFO info;

	INT sceneNumber;
	INT CurrentNumber;

	BOOL Loop;

	D3DXVECTOR2 sceneSize;
	DWORD changeTime;

	DWORD prevTime;
	DWORD NowTime;

	animation(LPDIRECT3DTEXTURE9 texturePtr, D3DXIMAGE_INFO info, INT sceneNumber, DWORD changeTime, BOOL Loop = true);

	BOOL Render(float x, float y, float size = 1.0f, float rot = 0.0f, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
	BOOL SceneRender(D3DXVECTOR2 pos, float size = 1.0f,float rot = 0, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255), int playScene = 0);
	BOOL SceneCenterRender(D3DXVECTOR2 pos, float size = 1.0f, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255), int playScene = 0);

	void CenterRender(float x, float y, float size, float rot, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
};

struct pieceAnimation {
	map<int, texture*> m_images;
	D3DXIMAGE_INFO info;

	INT sceneNumber;
	INT CurrentNumber;

	BOOL Loop;
	DWORD changeTime;
	DWORD prevTime;

	pieceAnimation(map<int, texture*> images, D3DXIMAGE_INFO info, INT sceneNumber, DWORD changeTime, BOOL loop = true);
	~pieceAnimation();

	void Render(float x, float y, float size = 1.0f, float rot = 0.0f, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
	void CenterRender(float x, float y, float size = 1.0f, float rot = 0.0f, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
	void sceneRender(float x, float y, float size = 1.0f, float rot = 0.0f, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255), int playscene = 0);
	void sceneCenterRender(float x, float y, float size = 1.0f, float rot = 0.0f, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255), int playscene = 0);
};

class cAnimationManager :
	public singleton<cAnimationManager>
{
private:
	map<string, animation*> m_images;
private:
	void Init();
	void Release();
public:
	cAnimationManager();
	~cAnimationManager();


	animation* AddAnimation(const string& key, const string& path, INT sceneNumber, DWORD changeTime, BOOL Loop = true);
	pieceAnimation* AddPieceAnimation(const string& key, INT sceneNumber, DWORD changeTime, BOOL Loop = true);
	void LoadPieceAnimation(const string& key, const string& path, const string& extension, int count);
	animation* FindAnimation(const string& key);

	void Begin();
	void End();

	void Render(animation* texturePtr, float x, float y, float size, float rot, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
	//좌상단을 기준으로 이미지 랜더링

	void CenterRender(animation* texturePtr, float x, float y, float size, float rot, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
	//가운데를 기준으로 이미지 랜더링

	void LostDevice();
	void ResetDevice();

};


#define ANIMATIONMANAGER cAnimationManager::GetInstance()