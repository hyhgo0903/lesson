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

	_pl = new player;		_pl->init();
	_em = new enemyManager;	_em->init();

	
	return S_OK;
}


void playGround::release()
{
	gameNode::release();

	_pl->release();
	_em->release();
	
}

void playGround::update()
{
	gameNode::update();

	_pl->update();
	_em->update();
	SCENEMANAGER->update();
	
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ 위에 건들지 마라 ==============================
	
	//IMAGEMANAGER->findImage("새배경")->render(getMemDC());	
	
	SCENEMANAGER->render();

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		TIMEMANAGER->render(getMemDC());
	}
	_pl->render();

	int temp;
	for (int i = 0; i < _em->getVEnemy().size(); ++i)
	{ // 벡터에 바텀의 y값을 넣는다
		temp = _em->getVEnemy()[i]->getRect().bottom;
		bottomY.push_back(temp);
	}
	temp = _pl->getGroundRc().bottom;
	bottomY.push_back(temp);
	// y값을 하나하나 넣었음

	sprintf_s(_str, "정렬전:");
	TextOut(getMemDC(), 440, 0, _str, strlen(_str));
	for (int i = 0; i < bottomY.size(); ++i)
	{
		sprintf_s(_str, "%d", bottomY[i]);
		TextOut(getMemDC(), 500+i * 30, 0, _str, strlen(_str));
	} // 텍스트는 참고용으로 넣어봄



	for (int i = 0; i < bottomY.size()-1; ++i)
	{
		for (int j = i + 1; j > 0 && bottomY[j] < bottomY[j - 1]; --j)
		{
			swap(bottomY[j], bottomY[j - 1]);
		}
	}	// 정렬을 했음


	sprintf_s(_str, "정렬후:");
	TextOut(getMemDC(), 440, 20, _str, strlen(_str));
	for (int i = 0; i < bottomY.size(); ++i)
	{
		sprintf_s(_str, "%d", bottomY[i]);
		TextOut(getMemDC(), 500 + i * 30, 20, _str, strlen(_str));
	} // 텍스트는 참고용으로 넣어봄

	for (int i = 0; i < bottomY.size(); ++i)
	{ // 정렬했으니 벡터에 담긴 순서대로 그리기로 함
		if (_pl->getGroundRc().bottom == bottomY[i])
		{ // 내가 찾는 바텀값과 동일하면 렌더
			_pl->rectRender();
		}
		for (int j = 0; j < _em->getVEnemy().size(); ++j)
		{
			if (_em->getVEnemy()[j]->getRect().bottom == bottomY[i])
			{
				_em->getVEnemy()[j]->rectRender();
			}
		}
	}
	bottomY.clear(); // 매번 클리어 해야만 하는걸까..?
	//너무 비효율적이지 않을까..

	
	//================= 아래도 건들지 마라 ==============================
	_backBuffer->render(getHDC());
}
