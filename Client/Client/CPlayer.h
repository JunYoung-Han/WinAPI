#pragma once
#include "CObject.h"

class CTexture;

class CPlayer :
	public CObject
{
private:
	bool m_bMissileType;
	CTexture* m_pTex;

public:
	virtual void update();
	virtual void render(HDC _dc);

private:
	void CreateMissile();
	void CreateMissile2();
	void ChangeMissile() { m_bMissileType = !m_bMissileType; }

public:
	CPlayer();
	~CPlayer();

};