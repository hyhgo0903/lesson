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

	INIDATA->addData("����", "�帳��", "1300");
	INIDATA->addData("����", "�帳������", "0");
	INIDATA->addData("����", "�帳��������", "13");

	INIDATA->addData("â��", "����������", "20");
	INIDATA->addData("â��", "�Ŀ�������", "1");

	INIDATA->iniSave("25��");

	_str = INIDATA->loadDataString("25��", "����", "�帳��");
	_test = INIDATA->loadDataInterger("25��", "â��", "����������");

	return S_OK;
}


void playGround::release()
{
	gameNode::release();

	
}

void playGround::update()
{
	gameNode::update();


	
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ ���� �ǵ��� ���� ==============================
	
	

	TIMEMANAGER->render(getMemDC());
	//================= �Ʒ��� �ǵ��� ���� ==============================
	_backBuffer->render(getHDC());
}

