#pragma once
#include "CObject.h"

// 내가 만들어보는 미사일.

class CMissile2 :
    public CObject
{
private:
    Vec2    m_vCenterPos;
    float   m_fDirY;
    float   m_fDirX;
    float   m_fMaxDistanceX;
    float   m_fSpeed;
    
public:
    void SetDir(bool _bUp)
    {
        if (_bUp)
            m_fDirY = -1.f;
        else
            m_fDirY = 1.f;
    }


public:
    virtual void update();
    virtual void render(HDC _dc);
    void SetCenterPos(Vec2 _vPos) { m_vCenterPos = _vPos; }
    void SetSpeed(float _f) { m_fSpeed = _f; }

public:
    CMissile2();
    ~CMissile2();
};

