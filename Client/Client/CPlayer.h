#pragma once
#include "CObject.h"

class CPlayer :
	public CObject
{
private:
	bool m_bMissileType;

public:
	virtual void update();

private:
	void CreateMissile();
	void CreateMissile2();
	void ChangeMissile() { m_bMissileType = !m_bMissileType; }

public:
	CPlayer()
		: m_bMissileType(true)
	{

	}
	~CPlayer()
	{}

};