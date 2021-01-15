#pragma once
#include "gameNode.h"

#define SNAKEBODY 50

//�� ����ü
struct tagSnake
{
	float x, y;		//������ǥ
	float angle;	//����
	float speed;	//���ǵ�
	float radius;	//������
};

class playGround : public gameNode
{
private:
	tagSnake _snake[SNAKEBODY];

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ����
	virtual void render(HDC hdc);	//�׸��� ����

	void snakeMove();

};

