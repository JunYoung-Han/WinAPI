#pragma once

// Key MAnager 의 목적
// 같은 키보드를 눌렀는데 progress 처리중에
// 어떤함수는 입력처리, 어떤 함수는 미입력 처리로 처리가 될 확률이 있다. 따라서, 
// 1. Frame 동기화를 해준다.
// 동일 프레임 내에서 같은 키에 대해, 동일한 이벤트를 가져간다.
// 
// 2. 키 입력 이벤트 처리
// tap, hold, away
//

enum class KEY_STATE
{
	NONE, // 눌리지 않고, 이전에도 눌리지 않은 상태
	TAP, // 막 누른 시점
	HOLD, // 누르고 있는
	AWAY, // 막 뗀 시점
};

enum class KEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,

	Q,
	W,
	E,
	R,
	T,
	Y,
	U,
	I,
	O,
	P,
	A,
	S,
	D,
	F,
	G,
	H,
	J,
	K,
	L,
	Z,
	X,
	C,
	V,
	B,

	ALT,
	CTRL,
	LSHIFT,
	SPACE,
	ENTER,
	ESC,

	LAST,
};

struct tKeyInfo
{
	KEY_STATE	eState;	// 키의 상태값
	bool		bPrevPush;	// 이전 프레임에서 눌렸는지 여부
};

class CKeyMgr
{
	SINGLE(CKeyMgr);

private:
	vector<tKeyInfo> m_vecKey;

public:
	void init();
	void update();

public:
	KEY_STATE GetKeyState(KEY _eKey) { return m_vecKey[(int)_eKey].eState;	}
};
