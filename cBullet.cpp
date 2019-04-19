#include "DXUT.h"
#include "cBullet.h"


cBullet::cBullet(const D3DXVECTOR2& pos, double size,float speed,float damage)
	:m_pos(pos), m_size(size),m_speed(speed),m_damage(damage)
{
	m_isDeath = false;
}


cBullet::~cBullet()
{
}


bool cBullet::IsOutMap()
{
	return (m_pos.x - m_size < 0
		|| m_pos.x + m_size > WINSIZEX
		|| m_pos.y - m_size < 0
		|| m_pos.y + m_size > WINSIZEY);
}
