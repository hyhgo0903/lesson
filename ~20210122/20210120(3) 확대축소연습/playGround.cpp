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
	SCENEMANAGER->addScene("���ξ�", new mainScene);
	SCENEMANAGER->addScene("Ÿ��Ʋ��", new titleScene);
	SCENEMANAGER->addScene("������", new endingScene);
	SCENEMANAGER->addScene("������", new videoScene);
	_x = _y = 0;
	SCENEMANAGER->changeScene("������");
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
	{ // �̷��� �Ȱɸ� �ٸ����� ���� isOnceKeyDown(VK_RETURN)�� ����Ǵ°� ����
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			SOUNDMANAGER->play("����", 1.0f);
			SCENEMANAGER->changeScene("Ÿ��Ʋ��");
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
	//================ ���� �ǵ��� ���� ==============================

	SCENEMANAGER->render();
	EFFECTMANAGER->render();
	//================= �Ʒ��� �ǵ��� ���� ==============================
	_tempDC = IMAGEMANAGER->addImage("backBuffer", WINSIZEX - 2 * _x, WINSIZEY-2*_y);
	_backBuffer->render(_tempDC->getMemDC(), 0, 0, CAMX + _x, CAMY + _y, WINSIZEX - 2 * _x, WINSIZEY - 2 * _y);
	_tempDC->resizedRender(getHDC(),0,0,0,0, WINSIZEX, WINSIZEY, WINSIZEX-2*_x,WINSIZEY-2*_y);
}