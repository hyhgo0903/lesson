#pragma once
#include "gameNode.h"

class RealTarget
{
public:
	RECT rc;
	float x;
	float y;
	RealTarget()
	{
		rc = { 0,0,0,0 };
		x = 0;
		y = 0;
	}


};

class playGround : public gameNode
{
private:
	RECT _effect[8]; // �����

	int _timeCount; // ������� or �ð������� ������ ���� ī��Ʈ

	int _leftCount; // ���� ���Ƚ��
	int _score; // ����
	int _highScore; // ����
	int _randNum; // ������ ����
	float _gravity;
	int _direction;

	bool _isStand; // ǥ���� ����������
	bool _animation; // ������ ����
	bool _offset;

	RealTarget tar;

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ����
	virtual void render(HDC hdc);	//�׸��� ����
};

