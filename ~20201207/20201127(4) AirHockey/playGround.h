#pragma once
#include "gameNode.h"

#define BALLRADIAN 10
#define PLAYERRADIAN 20
#define BALLSPEED 20. // �����Ҷ��� �浹�� �ӵ�

class playGround : public gameNode
{
private:
	image* _board; // 800*560
	image* _number[10]; // ���ھ�� �����

	image* _p1win;
	image* _p2win;
	image* _p1img;
	image* _p2img;
	image* _ballimg;

	RECT _temp; // �浹������

	RECT _p1; // ���� �÷��̾�
	RECT _p2; // ������ �÷��̾�
	RECT _ball; // ��
	float _ballSpd; // ���ӵ�
	float _ballAngle; // ����
	float _angle; // �浹�� �پޱۿ�

	char str[256];

	int _scoreP1; // 1P����
	int _scoreP2; // 2P����

	int _count; // ����۽� ����

	int _p1isStanding; // ���߸� 20���� ������ �����϶� �پ����(������ ��ƨ�ܳ���)
	int _p2isStanding; // ���߸� 20���� ������ �����϶� �پ����(������ ��ƨ�ܳ���)

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ����
	virtual void render(HDC hdc);	//�׸��� ����

	void playerMove();	//�÷��̾��̵�
	void ballMove(); // ���̵�
	void collide(); // ������
	void collideWall(); // ���ε�
	void scoring(); // ���ھ� ���

};

