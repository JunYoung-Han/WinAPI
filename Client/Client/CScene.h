#pragma once
// 한 씬의 오브젝트들을 관리
// 씬 안에 디폴트 그룹, 몬스터, 플레이어 등등 있는거.

// 전방선언 이유 : 헤더끼리 서로를 참조하는 걸 방지하고자.
class CObject;	// 컴파일속도에 영향을 주지 않기 위해.
// 헤더를 참조하면, 오브젝트 코드가 변경될 때 마다 씬도 매번 컴파일 확인 됨.
// 그러나 씬은 오브젝트를 알지 못하고 그냥 이런 얘가 있다는 식으로 넘어왔기 때문에
// 오브젝트가 변경되더라도 씬쪽은 컴파일러가 재확인하지 않는다.


class CScene
{
	//protected:	// 부모 멤버 변수는 protected 로 하면 디버깅 힘들어짐. 여러개의 자식들이 다 접근 할 수 있자너.
					// --> 될 수 있으면 protected 함수로 접근하게 만들기.
private:
	// CObject a; // 전방선언 -> 클래스 타입 자체는 쓸 수 없다.
	// 무슨타입인지 구체적인 정보가 없어서. // 나중에 링크로 넘김
	// --> 포인터 타입만 사용가능

	// Cobject는 앞으로 파생될 오브젝트 클래스들의 가장 부모 타입
	// 자식 포인터 타입을 이걸로 다 받을 수 있다.
	vector<CObject*>	m_arrObj[(UINT)GROUP_TYPE::END]; // 오브젝트를 저장 및 관리할 벡터를 그룹 개수만큼 선언
	wstring				m_strName; // Scene 이름

// protected:
public:
	// 헤더에 함수 구현하여 inline화
	void AddObject(CObject* _Obj, GROUP_TYPE _eType)
	{
		m_arrObj[(UINT)_eType].push_back(_Obj);
	}
	// 원본을 줄려고 참조로 준다.
	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eType) { return m_arrObj[(UINT)_eType]; }


public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	void update();
	// 작업을 마무리. -ex) 충돌체가 플레이어를 따라가게 하는 일.
	void finalupdate();
	void render(HDC _dc);


	// 해당 Scene 진입시 호출
	virtual void Enter() = 0; // 순수 가상 함수
	// --> 순수 가상 함수를 가지고 있는 클래스는 추상 클래스가 된다.
	// ==> 직접 객체 생성이 불가능 해진다.
	// ==> 구현해야 될 함수(Enter()는 반드시 구현해라!)를 알리는 목적.

	// 해당 Scene 벗어날 때 호출
	virtual void Exit() = 0;

public:
	CScene();
	virtual ~CScene();	// 자식쪽의 소멸자를 호출하기 위해 부모인 CScene은 가상함수로 선언.
						// 부모 객체의 포인터로 자식을 접근하기 때문에 자식의 소멸자에 접근하려면 부모소멸자를 가상함수로 선언.
};

