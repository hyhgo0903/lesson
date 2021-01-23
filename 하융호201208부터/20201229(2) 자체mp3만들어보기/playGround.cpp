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
	IMAGEMANAGER->addImage("���", "image/uiback.bmp", 340, 520, false, RGB(0,0,0));
	IMAGEMANAGER->addImage("����", "image/random.bmp", 25, 20, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("����", "image/selected.bmp", 330, 23, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�÷��̹�ư", "image/playbutton.bmp", 27, 27, false, RGB(0, 0, 0));

	IMAGEMANAGER->addFrameImage("pic", "image/pic.bmp", 1000, 100, 10, 1, false, RGB(0, 0, 0));
	
	IMAGEMANAGER->addImage("�Ѱ�", "image/mode1.bmp", 23, 22, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("�ݺ�����", "image/modex.bmp", 23, 22, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("����", "image/volumebar.bmp", 53, 10, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("�����", "image/playingbar.bmp", 319, 2, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("���Ұ�", "image/silenced.bmp", 16, 14, false, RGB(0, 0, 0));

	SCENEMANAGER->addScene("�����", new myLittleMP3);

	SCENEMANAGER->changeScene("�����");
	
	return S_OK;
}


void playGround::release()
{
	gameNode::release();

	
}

void playGround::update()
{
	gameNode::update();


	SCENEMANAGER->update();
	
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ ���� �ǵ��� ���� ==============================
	
	SCENEMANAGER->render();
	//================= �Ʒ��� �ǵ��� ���� ==============================
	_backBuffer->render(getHDC());
}

