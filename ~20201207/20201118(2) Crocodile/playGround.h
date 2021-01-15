#pragma once
#include "gameNode.h"

struct tagBox
{
	RECT rc;
	bool isRotten;
	bool isClicked;
};

class playGround : public gameNode
{
private:
	tagBox _tooth[20];
	bool _isAngry;
	int _down;
	RECT upperItmom;

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ����
	virtual void render(HDC hdc);	//�׸��� ����
};

