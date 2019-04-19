#pragma once
#include "cUI.h"
class cCursorPointer :
	public cUI
{
private:
	texture * m_mousePointer;
public:
	cCursorPointer(D3DXVECTOR2 pos);
	~cCursorPointer();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

