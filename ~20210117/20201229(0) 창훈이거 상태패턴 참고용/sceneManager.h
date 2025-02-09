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

private:
	static gameNode* _currentScene;

	mapSceneList _mSceneList;

public:
	HRESULT init();
	void release();
	void update();
	void render();
	void render(POINT camera);
	//���߰� �Լ�
	gameNode* addScene(string sceneName, gameNode* scene);

	//�� ���� �Լ�
	HRESULT changeScene(string sceneName);
	HRESULT changeScene(string sceneName,bool check);
	sceneManager() {};
	~sceneManager() {};
};

