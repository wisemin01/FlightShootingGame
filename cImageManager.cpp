#include "DXUT.h"
#include "cImageManager.h"

LPD3DXSPRITE m_sprite;

void texture::Render(float x, float y, float size, float rot, D3DCOLOR color)
{
	IMAGEMANAGER->Render(this, x, y, size, rot, color);
}

void texture::Render(float x, float y, float rot)
{
	IMAGEMANAGER->Render(this, x, y, rot);
}

void texture::CenterRender(float x, float y, float size, float rot, D3DCOLOR color)
{
	IMAGEMANAGER->CenterRender(this, x, y, size, rot, color);
}

void texture::CenterRender(float x, float y, float rot)
{
	IMAGEMANAGER->CenterRender(this, x, y, rot);
}

cImageManager::cImageManager()
{
	m_sprite = nullptr;
	Init();
}


cImageManager::~cImageManager()
{
	Release();
}

//불러올 이미지를 부를 이름과 경로
texture* cImageManager::AddImage(const string& key, const string& path)
{
	auto find = m_images.find(key);//이미 있는 이름을 다시 쓰려고 하는게 아닌지 확인해본다
	if (find == m_images.end())
	{
		LPDIRECT3DTEXTURE9 texturePtr;
		D3DXIMAGE_INFO info;

		if (D3DXCreateTextureFromFileExA(g_device, path.c_str(), D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 0, 0,
			D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, &info, nullptr, &texturePtr) == S_OK)
		{
			texture* text = new texture(texturePtr, info);
			m_images.insert(make_pair(key, text));
			return text;
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

texture* cImageManager::FindImage(const string& key)
{
	auto find = m_images.find(key);//이름으로 이미지를 찾아본다
	if (find == m_images.end()) { 
		DEBUG_LOG(key.c_str() << "은(는) 존재하지 않습니다.");
		return nullptr; 
	}//없으면 nullptr을 뱉는다
	return find->second;//있으면 그걸 뱉는다
}

void cImageManager::Init()
{
	D3DXCreateSprite(g_device, &m_sprite);
}

void cImageManager::Release()
{
	for (auto iter : m_images)
	{
		iter.second->texturePtr->Release();
		SAFE_DELETE(iter.second);
	}
	m_images.clear();

	m_sprite->Release();
}

void cImageManager::Begin()
{
	m_sprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void cImageManager::End()
{
	m_sprite->End();
}

void cImageManager::Render(texture* texturePtr, float x, float y, float size, float rot, D3DCOLOR color)
{
	if (texturePtr)
	{
		D3DXMATRIXA16 mat;

		D3DXMatrixAffineTransformation2D(&mat, size, nullptr, rot, &D3DXVECTOR2(x, y));
		m_sprite->SetTransform(&mat);
		m_sprite->Draw(texturePtr->texturePtr, nullptr, nullptr, nullptr, color);
	}
}

void cImageManager::Render(texture* texturePtr, float x, float y, float rot)
{
	if (texturePtr)
	{
		D3DXMATRIXA16 mat;

		D3DXMatrixAffineTransformation2D(&mat, 1.f, nullptr, rot, &D3DXVECTOR2(x, y));
		m_sprite->SetTransform(&mat);
		m_sprite->Draw(texturePtr->texturePtr, nullptr, nullptr, nullptr, D3DCOLOR_XRGB(255, 255, 255));
	}
}

void cImageManager::CenterRender(texture* texturePtr, float x, float y, float size, float rot, D3DCOLOR color)
{
	Render(texturePtr, x - (texturePtr->info.Width / 2) * size, y - (texturePtr->info.Height / 2) * size, size, rot, color);
}

void cImageManager::CenterRender(texture* texturePtr, float x, float y, float rot)
{
	Render(texturePtr, x - texturePtr->info.Width / 2, y - texturePtr->info.Height / 2, rot);
}

void cImageManager::DeleteImage(const string & key)
{
	auto find = m_images.find(key);

	SAFE_RELEASE(find->second->texturePtr);
	SAFE_DELETE(find->second);

	m_images.erase(find);
}

void cImageManager::LostDevice()
{
	m_sprite->OnLostDevice();
}

void cImageManager::ResetDevice()
{
	m_sprite->OnResetDevice();
}
