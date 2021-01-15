#pragma once
#include "gameNode.h"

class playGround : public gameNode
{
private:
	RECT _rc;
	bool _isCrash;
	float _speed;

	int _r, _g, _b;

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ����
	virtual void render(HDC hdc);	//�׸��� ����
};

