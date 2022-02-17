#pragma once

class CScene;

// ��� ������ �����Ѵ�.
class CSceneMgr
{
	SINGLE(CSceneMgr);
private:
	CScene* m_arrScene[(UINT)SCENE_TYPE::END];		// ��� �� ���
	CScene* m_pCurScene;			// ���� ��



public:
	void init();
	// Object ���� �Լ�.
	void update();
	void render(HDC _pMemDC);

public:
	CScene* GetCurScene() { return m_pCurScene; }
};

