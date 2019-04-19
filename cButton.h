#pragma once
#include "cUI.h"
class cButton :
	public cUI
{
	enum e_buttonState {
		e_up = 0,
		e_down = 1
	};

private:
	texture* m_buttonImg[2];
	BOOL m_state;
	BOOL m_isdown;
	BOOL m_isMouseOn;
	POINT m_mousepos;

public:
	cButton(float x, float y);
	virtual ~cButton();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	void Render(float x, float y);

public:
	bool isDown() { return m_isdown; }
	bool isMouseOn() { return m_isMouseOn; }
	void SetButtonImg(texture* up, texture* down) { m_buttonImg[0] = up; m_buttonImg[1] = down; }
};

