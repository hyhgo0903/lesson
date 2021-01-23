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
	//================ ���� �ǵ��� ���� ==============================
	
	//IMAGEMANAGER->findImage("�����")->render(getMemDC());	
	
	SCENEMANAGER->render();

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		TIMEMANAGER->render(getMemDC());
	}
	_pl->render();

	int temp;
	for (int i = 0; i < _em->getVEnemy().size(); ++i)
	{ // ���Ϳ� ������ y���� �ִ´�
		temp = _em->getVEnemy()[i]->getRect().bottom;
		bottomY.push_back(temp);
	}
	temp = _pl->getGroundRc().bottom;
	bottomY.push_back(temp);
	// y���� �ϳ��ϳ� �־���

	sprintf_s(_str, "������:");
	TextOut(getMemDC(), 440, 0, _str, strlen(_str));
	for (int i = 0; i < bottomY.size(); ++i)
	{
		sprintf_s(_str, "%d", bottomY[i]);
		TextOut(getMemDC(), 500+i * 30, 0, _str, strlen(_str));
	} // �ؽ�Ʈ�� ��������� �־



	for (int i = 0; i < bottomY.size()-1; ++i)
	{
		for (int j = i + 1; j > 0 && bottomY[j] < bottomY[j - 1]; --j)
		{
			swap(bottomY[j], bottomY[j - 1]);
		}
	}	// ������ ����


	sprintf_s(_str, "������:");
	TextOut(getMemDC(), 440, 20, _str, strlen(_str));
	for (int i = 0; i < bottomY.size(); ++i)
	{
		sprintf_s(_str, "%d", bottomY[i]);
		TextOut(getMemDC(), 500 + i * 30, 20, _str, strlen(_str));
	} // �ؽ�Ʈ�� ��������� �־

	for (int i = 0; i < bottomY.size(); ++i)
	{ // ���������� ���Ϳ� ��� ������� �׸���� ��
		if (_pl->getGroundRc().bottom == bottomY[i])
		{ // ���� ã�� ���Ұ��� �����ϸ� ����
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
	bottomY.clear(); // �Ź� Ŭ���� �ؾ߸� �ϴ°ɱ�..?
	//�ʹ� ��ȿ�������� ������..

	
	//================= �Ʒ��� �ǵ��� ���� ==============================
	_backBuffer->render(getHDC());
}
