#pragma once
#include "cUI.h"
class cNumber :
	public cUI
{
private:
	D3DXVECTOR2 m_pos;
	pieceAnimation* m_NumberImage;
	FLOAT m_size;
public:
	cNumber(float size);
	~cNumber();

	void Render(float x, float y, int number);

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

