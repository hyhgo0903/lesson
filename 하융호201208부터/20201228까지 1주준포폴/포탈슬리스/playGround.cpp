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
	imageInit();	
	SCENEMANAGER->addScene("����Ʈ��", new selectScene);
	SCENEMANAGER->addScene("�÷��̾�", new playScene);
	SCENEMANAGER->addScene("���ӿ�����", new gameOverScene);
	SCENEMANAGER->addScene("�¸���", new victoryScene);
	SCENEMANAGER->changeScene("����Ʈ��");
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
	SCENEMANAGER->update();
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, GETCAM+WINSIZEX, WINSIZEY, WHITENESS);
	//================ ���� �ǵ��� ���� ==============================
	SCENEMANAGER->render();
	//================= �Ʒ��� �ǵ��� ���� ==============================
	_backBuffer->render(getHDC(), 0, 0, GETCAM, CAMERAMANAGER->getCameraY(), WINSIZEX, WINSIZEY);
}