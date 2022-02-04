#pragma once

// ��ũ�� Ű����
#define Add(a,b) a+b
// ==> �Լ��� �ٸ���: ������ Ÿ�ֿ̹� �ڵ带 ġȯ�ؼ� ����ȴ�.
// => ���� ������ �켱������ ���� ���� �ٸ��� ���� �� �ִ�.

// => ���� ���� ��ũ�� �Լ��� ������!
//static CCore* GetInst()
//{
//	// static --> data �޸� ���� ���.
//	static CCore core;
//
//	return &core;
//}

// Singleton ��ũ��
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