#pragma once
#include "singleton.h"

//C++������ ����ü�� Ŭ������ ���̰� ���� ����
//struct�� �⺻�� public
//class�� �⺻�� private�� �Ǿ�������
//���� ������ ���� ���� �ȿ� �Լ��� ������ �ִ�.
struct texture
{
	LPDIRECT3DTEXTURE9 texturePtr;
	D3DXIMAGE_INFO info;

	texture(LPDIRECT3DTEXTURE9 texturePtr, D3DXIMAGE_INFO info)
		:texturePtr(texturePtr), info(info)
	{
	}

	void Render(float x, float y, float size, float rot, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
	void Render(float x, float y, float rot = 0);

	void CenterRender(float x, float y, float size, float rot, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
	void CenterRender(float x, float y, float rot = 0);
};

//singleton�� ��ӹ޾Ҵ�. ��𼭵� ������ ��������
class cImageManager : public singleton<cImageManager>
{
	friend class cAnimationManager;
private:
	map<string, texture*> m_images;

	//stl���� map�̶�� �ڷ����� �ִµ�
	//�̸����� ���� ã����, ���� ���� ȿ���� �����ش�
private:
	void Init();
	void Release();
public:
	cImageManager();
	~cImageManager();

	texture* AddImage(const string& key, const string& path);
	texture* FindImage(const string& key);

	void Begin();
	void End();

	void Render(texture* texturePtr, float x, float y, float size, float rot, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
	void Render(texture* texturePtr, float x, float y, float rot = 0);
	//�»���� �������� �̹��� ������

	void CenterRender(texture* texturePtr, float x, float y, float size, float rot, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
	void CenterRender(texture* texturePtr, float x, float y, float rot = 0);
	//����� �������� �̹��� ������

	void DeleteImage(const string& key);
	//�̹��� ����

	void LostDevice();
	void ResetDevice();
	//�Լ��� ���ڴ� �⺻������ 4������ ����ϴ°��� ����.(4���� �Ѿ�� �ް��� ��������)
	//�ڼ��� ������ ���߿� �������Ϳ� �ý��� ĳ�ø� �����Ҷ� �˾ƺ��� ����
};

#define IMAGEMANAGER cImageManager::GetInstance()
//�Ź� �Լ����� �������� cImageManager::GetInstance()->AddImage();���ִ°��� ����� ���ŷο���
//���� ���� �ٿ��� ����Ѵ�