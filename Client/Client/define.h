#pragma once

// 매크로 키워드
#define Add(a,b) a+b
// ==> 함수와 다른점: 컴파일 타이밍에 코드를 치환해서 실행된다.
// => 따라서 연산자 우선순위에 의해 값이 다르게 나올 수 있다.

// => 자주 쓰니 매크로 함수로 만들자!
//static CCore* GetInst()
//{
//	// static --> data 메모리 영역 사용.
//	static CCore core;
//
//	return &core;
//}

// Singleton 매크로
#define SINGLE(type) public:\
						static type* GetInst()\
						{\
							static type mgr;\
								return &mgr;\
						}\
					private:\
						type();\
						~type();

#define fDT CTimeMgr::GetInst()->GetfDt()
#define DT CTimeMgr::GetInst()->GetDt()

#define KEY_CHECK(key, state)	CKeyMgr::GetInst()->GetKeyState(key) == state
#define KEY_HOLD(key)	KEY_CHECK(key, KEY_STATE::HOLD)
#define KEY_TAP(key)	KEY_CHECK(key, KEY_STATE::TAP)
#define KEY_AWAY(key)	KEY_CHECK(key, KEY_STATE::AWAY)
#define KEY_NONE(key)	KEY_CHECK(key, KEY_STATE::NONE)
#define MOUSE_POS CKeyMgr::GetInst()->GetMousePos()


#define PI	3.141592

// UINT m_arrCheck[행] 의 자료형이 UINT (4 byte == 32bit)라서 32개
enum class GROUP_TYPE
{
	DEFAULT,
	PLAYER,
	MONSTER,
	PROJ_PLAYER,
	PROJ_MONSTER,

	END, //32
};

// 씬 구성.
enum class SCENE_TYPE
{
	TOOL,
	START,
	STAGE_01,
	STAGE_02,

	END,
};

enum class BRUSH_TYPE
{
	BLACK,
	HOLLOW,
	END,
};

enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,
	END,
};

enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,
	CHANGE_AI_STATE,
	END
};

enum class MON_STATE
{
	IDLE,
	PATROL,
	TRACE,
	ATTACK,
	RUN,
	DEAD, // 죽는 상태일때 다른 행동을 할 수 도 있음. (복제만든다 던지)
	END
};

