#pragma once
#include "singletonBase.h"
#include <string>
#include <map>

class gameNode;

class sceneManager : public singletonBase<sceneManager>
{
public:
	typedef map<string, gameNode*> mapSceneList;
	typedef map<string, gameNode*>::iterator mapSceneIter;
	// 맵에 키값이랑 씬이될 게임노드
private:
	static gameNode* _currentScene;

	mapSceneList _mSceneList;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	//씬추가 함수
	gameNode* addScene(string sceneName, gameNode* scene);

	//씬 변경 함수
	HRESULT changeScene(string sceneName);

	sceneManager() {};
	~sceneManager() {};
};

