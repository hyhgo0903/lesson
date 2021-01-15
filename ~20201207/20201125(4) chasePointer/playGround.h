#pragma once
#include "gameNode.h"

#define PI 3.14159f

struct tagObj
{
	float x, y;
	float angle;
	
};

class playGround : public gameNode
{
private:
	tagObj _player;
	tagObj _enemy;

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ����
	virtual void render(HDC hdc);	//�׸��� ����

	

};

