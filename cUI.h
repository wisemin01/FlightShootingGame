#pragma once
class cUI abstract
{
protected:
	D3DXVECTOR2 m_pos;
public:
	cUI(D3DXVECTOR2 pos);
	virtual ~cUI();

	virtual void Init() PURE;
	virtual void Update() PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;
};

