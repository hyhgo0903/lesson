#pragma once
#include "gameNode.h"


class playGround : public gameNode
{
private:
	RECT _rc;

	int _count;


public:
	playGround();
	~playGround();

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ����
	virtual void render(HDC hdc);	//�׸��� ����
};

