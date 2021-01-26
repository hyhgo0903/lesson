#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}

HRESULT playGround::init()
{
	gameNode::init(true);
	srand(time(NULL));
	soundInit();
	imageInitChanho(); imageInitDeokho(); imageInitHyunjeong(); imageInitYoongho(); imageInitYounghan();
	SCENEMANAGER->addScene("메인씬", new mainScene);
	SCENEMANAGER->addScene("타이틀씬", new titleScene);
	SCENEMANAGER->addScene("엔딩씬", new endingScene);
	SCENEMANAGER->addScene("비디오씬", new videoScene);
	_x = _y = 0;
	SCENEMANAGER->changeScene("비디오씬");
	_videoPlaying = true;

	return S_OK;
}


void playGround::release()
{
	gameNode::release();

	SCENEMANAGER->release();
}

void playGround::update()
{
	gameNode::update();

	if (_videoPlaying)
	{ // 이렇게 안걸면 다른곳에 쓰인 isOnceKeyDown(VK_RETURN)이 먹통되는거 같음
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			SOUNDMANAGER->play("선택", 1.0f);
			SCENEMANAGER->changeScene("타이틀씬");
			_videoPlaying = false;
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD0))
	{
		++_x; ++_y;
	}
	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD1))
	{
		if (_x> 0 ) --_x;
		if (_y > 0)	--_y;
	}
	SCENEMANAGER->update();
	EFFECTMANAGER->update();
}


void playGround::render()
{
	if (_videoPlaying) return;
	PatBlt(getMemDC(), 0, 0, CAMX + WINSIZEX, CAMY + WINSIZEY, WHITENESS);
	//================ 위에 건들지 마라 ==============================

	SCENEMANAGER->render();
	EFFECTMANAGER->render();
	//================= 아래도 건들지 마라 ==============================
	_tempDC = IMAGEMANAGER->addImage("backBuffer", WINSIZEX - 2 * _x, WINSIZEY-2*_y);
	_backBuffer->render(_tempDC->getMemDC(), 0, 0, CAMX + _x, CAMY + _y, WINSIZEX - 2 * _x, WINSIZEY - 2 * _y);
	_tempDC->resizedRender(getHDC(),0,0,0,0, WINSIZEX, WINSIZEY, WINSIZEX-2*_x,WINSIZEY-2*_y);
}