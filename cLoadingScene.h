#pragma once
#include "cScene.h"
class cLoadingScene :
	public cScene
{
private:
	pieceAnimation * m_loadingImg;

	INT m_loadingIndex;

	void ImageLoading();
public:
	cLoadingScene();
	~cLoadingScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

