#pragma once
#include "CObject.h"

class CMonster :
    public CObject
{
private:
    float   m_fAcc;
    bool    m_bMissileType;
    Vec2    m_vCenterPos;
    float   m_fSpeed;
    float   m_fMaxDistance;
    int     m_iDir; // 1, -1

public:
    float GetSpeed() { return m_fSpeed; }
    void SetSpeed(float _f) { m_fSpeed = _f; }
    float GetMaxDistance() { return m_fMaxDistance; }
    void SetMaxDistance(float _f) { m_fMaxDistance = _f; }
    void SetCenterPos(Vec2 _vPos) { m_vCenterPos = _vPos; }

public:
    virtual void update();
    void CreateMissile();
    void CreateMissile2();


public:
    CMonster();
    ~CMonster();
};

