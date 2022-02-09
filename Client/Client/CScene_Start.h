#pragma once
#include "CScene.h"

class CScene_Start :
    public CScene   // 오브젝트를 관리하는 씬을 부모로 상속.
{

public:
    // 오버라이딩한 가상함수인지, 일반함수 인지 구분하기 위해 virtual을 명시해준다.   
    // ★★★★ virtual 안붙혀줘도 가상함수로 인식됨, Only 명시적 효과 ★★★★
    virtual void Enter();
    virtual void Exit();

public:
    CScene_Start();
    ~CScene_Start();


};

