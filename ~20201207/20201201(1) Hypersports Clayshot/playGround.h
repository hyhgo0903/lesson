#pragma once
#include "gameNode.h"

#define RELOADCOUNT 70
#define BOWLMAX 20
#define REGENTIME 50

enum SHOOTERSTATE
{
	CENTER,
	LEFT,
	RIGHT
};

struct bowl
{
	RECT rc;
	float xSpd;
	float ySpd;
	float gravity;
	bool isFire;
};


class playGround : public gameNode
{
private:
	image* _background;
	image* _bowlimg;

	SHOOTERSTATE _shooterState; // �÷��̾� ����(��¿�)

	image* _shooterCenter;
	image* _shooterLeft;
	image* _shooterRight;
	image* _targetImg; // ���� �̹���
	image* _number[10];
	image* _timeUp;

	int _reloadCount; // ���� ī��Ʈ

	RECT _leftTarget; // ���� ������ ����
	RECT _rightTarget;
	RECT _temp; // �浹������
	RECT _reloadRc; // �������̸� ��

	bowl _bowl[BOWLMAX]; // �� 10����?

	bool _isEnd;
	int _randNum;
	int _regenTimer; // �����ð�
	int _score;
	int _standCount;
	int _leftChaseCount, _rightChaseCount, _tempI;
	int _gameCount;
	float _min;

	RECT _effect[8];

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ����
	virtual void render(HDC hdc);	//�׸��� ����

	void left();
	void right();
	void bowlRefill();
	void bowlMove();
	void bowlSpot();
	void effect();
};

