#pragma once

class CScene;

// 모든 씬들을 관리한다.
class CSceneMgr
{
	SINGLE(CSceneMgr);
private:
	CScene* m_arrScene[(UINT)SCENE_TYPE::END];		// 모든 씬 목록
	CScene* m_pCurScene;			// 현재 씬



public:
	void init();
	// Object 조작 함수.
	void update();
	void render(HDC _pMemDC);

public:
	CScene* GetCurScene() { return m_pCurScene; }
};

