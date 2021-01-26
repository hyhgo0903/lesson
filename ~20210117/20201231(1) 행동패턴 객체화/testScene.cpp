#include "stdafx.h"
#include "testScene.h"

HRESULT testScene::init()
{
	_funTest = new fun;
	_funTest->init();

	IMAGEMANAGER->findImage("�Ѿ�")->setX(WINSIZEX / 2);
	IMAGEMANAGER->findImage("�Ѿ�")->setY(WINSIZEY / 2);

	_funTest->moveTo(IMAGEMANAGER->findImage("�Ѿ�"), 100, 100, 5.0f);

	//=================================================================
	_btnSceneChange = new button;
	_btnSceneChange->init("��ư", WINSIZEX / 2, WINSIZEY / 2,
		PointMake(0, 1), PointMake(0, 0), cbSceneChange);




	return S_OK;
}

void testScene::release()
{

}

void testScene::update()
{
	_funTest->update();
	_btnSceneChange->update();
}

void testScene::render()
{
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	IMAGEMANAGER->findImage("�Ѿ�")->render(getMemDC(), IMAGEMANAGER->findImage("�Ѿ�")->getX(), IMAGEMANAGER->findImage("�Ѿ�")->getY());

	_btnSceneChange->render();

	TextOut(getMemDC(), WINSIZEX / 2, WINSIZEY - 100, "�׽�Ʈ��", strlen("�׽�Ʈ��"));
}

void testScene::cbSceneChange()
{
	SCENEMANAGER->changeScene("�����");
}
