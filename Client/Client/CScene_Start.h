#pragma once
#include "CScene.h"

class CScene_Start :
    public CScene   // ������Ʈ�� �����ϴ� ���� �θ�� ���.
{

public:
    // �������̵��� �����Լ�����, �Ϲ��Լ� ���� �����ϱ� ���� virtual�� ������ش�.   
    // �ڡڡڡ� virtual �Ⱥ����൵ �����Լ��� �νĵ�, Only ����� ȿ�� �ڡڡڡ�
    virtual void Enter();
    virtual void Exit();

public:
    CScene_Start();
    ~CScene_Start();


};

