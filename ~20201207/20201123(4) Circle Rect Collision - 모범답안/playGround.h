#pragma once
#include "gameNode.h"

#define PI 3.14f

class playGround : public gameNode
{
private:
	RECT _rectangle;
	RECT _ellipse;

	bool _isCollision;

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ����
	virtual void render(HDC hdc);	//�׸��� ����

	bool isCollision(RECT& rc1, RECT& rc2);

	bool getDistance(RECT& rc, float x, float y);


};

