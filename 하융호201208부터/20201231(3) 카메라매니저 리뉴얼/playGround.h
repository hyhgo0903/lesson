#pragma once
#include "gameNode.h"
#include "ghostScene.h"
#include "siva.h"

class playGround : public gameNode
{
private:
	

public:
	playGround();
	~playGround();

	virtual HRESULT init();	//�ʱ�ȭ ���� �Լ�
	virtual void release();	//�޸� ���� �Լ�
	virtual void update();	//���� ����
	virtual void render();	//�׸��� ����

};

