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

//�ҷ��� �̹����� �θ� �̸��� ���
texture* cImageManager::AddImage(const string& key, const string& path)
{
	auto find = m_images.find(key);//�̹� �ִ� �̸��� �ٽ� ������ �ϴ°� �ƴ��� Ȯ���غ���
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
		#pragma region �ε�����
		DEBUG_LOG("ERROR! �̹��� �ε��� �����߽��ϴ�. ���ϰ�θ� �ٽ� Ȯ�����ּ���");
		DEBUG_LOG("\tkey :" << key.c_str() << "\t path : " << path.c_str());
#pragma endregion
		//�̹��� �ε��� �����������(���� ����, cpu�޸� �������) �̰����� ���� �ȴ�
		return nullptr;
	}
	//�̹� �ҷ��� �̹����� �ٽ� �ҷ����� �߰ų�
	//�ٸ� �̹����� ���� �̸����� ���� ������� �̰����� ���� �ȴ�
	return find->second;
}

texture* cImageManager::FindImage(const string& key)
{
	auto find = m_images.find(key);//�̸����� �̹����� ã�ƺ���
	if (find == m_images.end()) { 
		DEBUG_LOG(key.c_str() << "��(��) �������� �ʽ��ϴ�.");
		return nullptr; 
	}//������ nullptr�� ��´�
	return find->second;//������ �װ� ��´�
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
