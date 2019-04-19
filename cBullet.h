#pragma once
class cBullet abstract
{
protected:
	D3DXVECTOR2 m_pos;
	RECT		m_bulletRect;

	float		m_speed;
	float		m_damage;
	float		m_rotation;
	double		m_size;

	bool		m_isDeath;
public:
	cBullet(const D3DXVECTOR2& pos, double size,float speed,float damage);
	virtual ~cBullet();

	virtual void Update() PURE;
	virtual void Render() PURE;

	bool	IsOutMap();
	bool	IsDeathUnit() { return m_isDeath; }
	RECT	GetRect() { return m_bulletRect; }
	FLOAT	GetDamage() { return m_damage; }
};