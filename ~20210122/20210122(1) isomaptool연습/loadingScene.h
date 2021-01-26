#pragma once
#include "gameNode.h"
#include "progressBar.h"
#include <string>

#define LOADINGMAX 20

class progressBar;

class loadingScene : public gameNode
{
private:
	progressBar* _loadingBar;
	image* _background;

public:
	loadingScene();
	~loadingScene();

	int _currentCount;
	bool _loadingEnd;

	HRESULT init();
	void release();
	void update();
	void render();

	void chanhoInit();
	void deokhoInit();
	void hyunjeonghoInit();
	void yoonghoInit();
	void younghanInit();
};

static DWORD CALLBACK threadFunction(LPVOID lpParameter);
