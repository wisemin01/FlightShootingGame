#include "DXUT.h"
#include "cAnimationManager.h"

extern LPD3DXSPRITE m_sprite;

animation::animation(LPDIRECT3DTEXTURE9 texturePtr, D3DXIMAGE_INFO info, INT sceneNumber, DWORD changeTime, BOOL Loop)
	:texturePtr(texturePtr), info(info), sceneNumber(sceneNumber), changeTime(changeTime), Loop(Loop)
{
	NowTime = timeGetTime();
	prevTime = NowTime + changeTime;
	sceneSize.x = info.Width / sceneNumber;
	sceneSize.y = info.Height;
	CurrentNumber = 0;
}

BOOL animation::Render(float x, float y, float size, float rot, D3DCOLOR color)
{
	if (!GAMEPAUSE) {
		NowTime = timeGetTime();
		if (NowTime >= prevTime) {
			CurrentNumber++;
			if (CurrentNumber >= sceneNumber) {
				if (Loop == false) {
					return false;
				}
				CurrentNumber = 0;
			}
			prevTime = NowTime + changeTime;
		}
	}
	ANIMATIONMANAGER->Render(this, x, y, size, rot, color);
	return true;
}

BOOL animation::SceneRender(D3DXVECTOR2 pos, float size,float rot, D3DCOLOR color, int playScene)
{
	CurrentNumber = playScene;
	ANIMATIONMANAGER->Render(this, pos.x, pos.y, size, rot, color);
	return 0;
}

BOOL animation::SceneCenterRender(D3DXVECTOR2 pos, float size, D3DCOLOR color, int playScene)
{
	CurrentNumber = playScene;
	ANIMATIONMANAGER->CenterRender(this, pos.x, pos.y, size, 0, color);
	return 0;
}


void  animation::CenterRender(float x, float y, float size, float rot, D3DCOLOR color)
{
	ANIMATIONMANAGER->CenterRender(this, x, y, size, rot, color);
}

cAnimationManager::cAnimationManager()
{
}


cAnimationManager::~cAnimationManager()
{
	Release();
}

//불러올 이미지를 부를 이름과 경로
animation* cAnimationManager::AddAnimation(const string& key, const string& path, INT sceneNumber, DWORD changeTime, BOOL Loop)
{
	auto find = m_images.find(key);//이미 있는 이름을 다시 쓰려고 하는게 아닌지 확인해본다
	if (find == m_images.end())
	{
		LPDIRECT3DTEXTURE9 texturePtr;
		D3DXIMAGE_INFO info;

		if (D3DXCreateTextureFromFileExA(g_device, path.c_str(), D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 0, 0,
			D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, &info, nullptr, &texturePtr) == S_OK)
		{
			animation* ani = new animation(texturePtr, info, sceneNumber, changeTime, Loop);
			m_images.insert(make_pair(key, ani));
			return ani;
		}
#pragma region 로딩실패
		DEBUG_LOG("ERROR! 이미지 로딩에 실패했습니다. 파일경로를 다시 확인해주세요");
		DEBUG_LOG("\tkey :" << key.c_str() << "\t path : " << path.c_str());
#pragma endregion
		//이미지 로딩이 실패했을경우(없는 파일, cpu메모리 부족등등) 이곳으로 오게 된다
		return nullptr;
	}
	//이미 불러온 이미지를 다시 불러오려 했거나
	//다른 이미지를 같은 이름으로 쓰고 있을경우 이곳으로 오게 된다
	return find->second;
}

pieceAnimation * cAnimationManager::AddPieceAnimation(const string & key, INT sceneNumber, DWORD changeTime, BOOL Loop)
{
	pieceAnimation* newAnimation;
	map<int, texture*> Anilist;

	for (int i = 0; i < sceneNumber; i++) {

		string skey = key + std::to_string(i);
		texture* text = IMAGE(skey);
		Anilist.insert(make_pair(i, text));
	}

	newAnimation = new pieceAnimation(Anilist, Anilist.begin()->second->info, sceneNumber, changeTime, Loop);
	return newAnimation;
}

animation* cAnimationManager::FindAnimation(const string& key)
{
	auto find = m_images.find(key);//이름으로 이미지를 찾아본다
	if (find == m_images.end()) return nullptr;//없으면 nullptr을 뱉는다
	return find->second;//있으면 그걸 뱉는다
}

void cAnimationManager::Init()
{
	D3DXCreateSprite(g_device, &m_sprite);
}

void cAnimationManager::Release()
{
	for (auto iter : m_images)
	{
		iter.second->texturePtr->Release();
		SAFE_DELETE(iter.second);
	}
	m_images.clear();
}

void cAnimationManager::Begin()
{
	m_sprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void cAnimationManager::End()
{
	m_sprite->End();
}

void cAnimationManager::Render(animation* texturePtr, float x, float y, float size, float rot, D3DCOLOR color)
{
	if (texturePtr)
	{
		D3DXMATRIXA16 mat;
		RECT rc;
		D3DXVECTOR3 CenterPos = { (float)(texturePtr->sceneSize.x / 2),(float)(texturePtr->info.Height / 2),0.0f };

		rc.left = texturePtr->CurrentNumber*texturePtr->sceneSize.x;
		rc.top = 0;
		rc.right = rc.left + texturePtr->sceneSize.x;
		rc.bottom = texturePtr->sceneSize.y;

		D3DXMatrixAffineTransformation2D(&mat, size, nullptr, rot, &D3DXVECTOR2(x, y));
		m_sprite->SetTransform(&mat);
		m_sprite->Draw(texturePtr->texturePtr, &rc, &CenterPos, nullptr, color);
	}
}

void cAnimationManager::CenterRender(animation* texturePtr, float x, float y, float size, float rot, D3DCOLOR color)
{
	Render(texturePtr, x - texturePtr->info.Width / 2, y - texturePtr->info.Height / 2, size, rot, color);
}

void cAnimationManager::LostDevice()
{
	m_sprite->OnLostDevice();
}

void cAnimationManager::ResetDevice()
{
	m_sprite->OnResetDevice();
}

pieceAnimation::pieceAnimation(map<int, texture*> images, D3DXIMAGE_INFO info, INT sceneNumber, DWORD changeTime, BOOL loop)
	:m_images(images), info(info), sceneNumber(sceneNumber), changeTime(changeTime), Loop(loop)
{
	prevTime = nowTime + changeTime;
	CurrentNumber = 0;
}

pieceAnimation::~pieceAnimation()
{
	m_images.clear();
}

void pieceAnimation::Render(float x, float y, float size, float rot, D3DCOLOR color)
{
	if (!GAMEPAUSE) {
		if (nowTime >= prevTime) {
			CurrentNumber++;
			if (CurrentNumber >= sceneNumber) {
				if (Loop == false) {
					return;
				}
				else
					CurrentNumber = 0;
			}
			prevTime = nowTime + changeTime;
		}
	}
	auto find = m_images.find(CurrentNumber);
	IMAGEMANAGER->Render(find->second, x, y);
}

void pieceAnimation::CenterRender(float x, float y, float size, float rot, D3DCOLOR color)
{
	if (!GAMEPAUSE) {
		if (nowTime >= prevTime) {
			CurrentNumber++;
			if (CurrentNumber >= sceneNumber) {
				if (Loop == false) {
					return;
				}
				CurrentNumber = 0;
			}
			prevTime = nowTime + changeTime;
		}
	}
	auto find = m_images.find(CurrentNumber);
	IMAGEMANAGER->CenterRender(find->second, x, y,size,rot,color);
}

void pieceAnimation::sceneRender(float x, float y, float size, float rot, D3DCOLOR color, int playscene)
{
	CurrentNumber = playscene;
	IMAGEMANAGER->Render(m_images[playscene], x, y);
}
void pieceAnimation::sceneCenterRender(float x, float y, float size, float rot, D3DCOLOR color, int playscene)
{
	CurrentNumber = playscene;
	IMAGEMANAGER->CenterRender(m_images[playscene], x, y, size, rot, color);
}

void cAnimationManager::LoadPieceAnimation(const string &key, const string&path, const string& extension, int count) {
	for (int i = 0; i < count; i++) {
		string l_key = key + std::to_string(i);
		string l_path = path + std::to_string(i);
		l_path += extension;
		LOADIMAGE(l_key, l_path);
	}
}