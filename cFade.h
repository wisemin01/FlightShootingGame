#pragma once
#include "cUI.h"
class cFade :
	public cUI
{
public:
	enum e_fadeType {
		e_fadeIn,
		e_fadeOut
	};
private:
	int m_fadeAlpha;
	bool m_fadeType;

	texture* m_fade;
public:
	cFade();
	virtual ~cFade();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	void SetFadeType(int fadeType) { m_fadeType = fadeType; }
	bool GetFadeFinish() { if (m_fadeAlpha == 255 || m_fadeAlpha == 0) return true; else return false; }
};

