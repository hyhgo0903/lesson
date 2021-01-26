#include "stdafx.h"
#include "testScene.h"

HRESULT testScene::init()
{
	_funTest = new fun;
	_funTest->init();

	IMAGEMANAGER->findImage("ÃÑ¾Ë")->setX(WINSIZEX / 2);
	IMAGEMANAGER->findImage("ÃÑ¾Ë")->setY(WINSIZEY / 2);

	_funTest->moveTo(IMAGEMANAGER->findImage("ÃÑ¾Ë"), 100, 100, 5.0f);

	//=================================================================
	_btnSceneChange = new button;
	_btnSceneChange->init("¹öÆ°", WINSIZEX / 2, WINSIZEY / 2,
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
	IMAGEMANAGER->findImage("ÃÑ¾Ë")->render(getMemDC(), IMAGEMANAGER->findImage("ÃÑ¾Ë")->getX(), IMAGEMANAGER->findImage("ÃÑ¾Ë")->getY());

	_btnSceneChange->render();

	TextOut(getMemDC(), WINSIZEX / 2, WINSIZEY - 100, "Å×½ºÆ®¾À", strlen("Å×½ºÆ®¾À"));
}

void testScene::cbSceneChange()
{
	SCENEMANAGER->changeScene("»ç¿îµå¾À");
}
