#pragma once
#include "CObject.h"
#include "AI.h"


struct tMonsterInfo
{
	float       fSpeed;         // 속도
	float       fHP;            // 체력
	float       fRecogRange;    // 인지 범위
	float       fAttRange;      // 공격 범위
	float       fAttackPower;      // 공격력
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

	// Set 함수 일일히 안만들어도 된다.
	friend class CMonsterFactory;
};