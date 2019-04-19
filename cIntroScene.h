#pragma once
#include "cScene.h"
class cIntroScene :
	public cScene
{
private:
	texture* m_introImg;
	texture* m_introImg2;

	int m_renderState;
public:
	cIntroScene();
	~cIntroScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

