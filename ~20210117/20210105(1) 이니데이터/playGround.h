#pragma once
#include "gameNode.h"
#include "inGameScene.h"
#include "loadingScene.h"

class playGround : public gameNode
{
private:
	string _str;
	int _test;

public:
	playGround();
	~playGround();

	virtual HRESULT init();	//�ʱ�ȭ ���� �Լ�
	virtual void release();	//�޸� ���� �Լ�
	virtual void update();	//���� ����
	virtual void render();	//�׸��� ����

};

