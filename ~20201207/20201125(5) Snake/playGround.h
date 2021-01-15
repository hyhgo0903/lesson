#pragma once
#include "gameNode.h"

#define PI 3.141592f
#define SNAKEBODY 200
#define RADIUS 30
#define SPEED 10

struct tagObj
{
	float x, y;
	float angle;

	float toX, toY;
	
};

class playGround : public gameNode
{
private:
	tagObj _snake[SNAKEBODY];


public:
	playGround();
	~playGround();
	
	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ����
	virtual void render(HDC hdc);	//�׸��� ����

	void bodyMove();

};

