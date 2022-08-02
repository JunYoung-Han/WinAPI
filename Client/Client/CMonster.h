#pragma once
#include "CObject.h"
#include "AI.h"


struct tMonsterInfo
{
	float       fSpeed;         // �ӵ�
	float       fHP;            // ü��
	float       fRecogRange;    // ���� ����
	float       fAttRange;      // ���� ����
	float       fAttackPower;      // ���ݷ�
};

class CMonster :
	public CObject
{
private:
	tMonsterInfo        m_tInfo;
	class AI* m_pAI;

public:
	float       GetSpeed() { return m_tInfo.fSpeed; }
	void        SetSpeed(float _f) { m_tInfo.fSpeed = _f; }
	void        SetAI(class AI* _pAI);
	const       tMonsterInfo& GetInfo() { return m_tInfo; }

private:
	void SetMonsterInfo(const tMonsterInfo& _info) { m_tInfo = _info; }


public:
	virtual void update();
	void CreateMissile();
	void CreateMissile2();

	virtual void OnCollisionEnter(CCollider* _pOther) 	 override;
	virtual void OnCollision(CCollider* _pOther) 		 override;
	virtual void OnCollisionExit(CCollider* _pOther) 	 override;

public:
	CMonster();
	~CMonster();

	// Set �Լ� ������ �ȸ��� �ȴ�.
	friend class CMonsterFactory;
};