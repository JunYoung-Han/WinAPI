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