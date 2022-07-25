#pragma once

class CMonster;

// 몬스터 타입
enum class MONSTER_TYPE
{
	NORMAL,
	RANGE,
	END
};

class CMonsterFactory
{
public:
	static CMonster* CreateMonster(MONSTER_TYPE _eType, Vec2 _vPos);

private:
	CMonsterFactory() {};
	~CMonsterFactory() {};

};