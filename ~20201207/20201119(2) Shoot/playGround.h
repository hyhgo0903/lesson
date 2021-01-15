#pragma once
#include "gameNode.h"


class playGround : public gameNode
{
private:
	RECT _target[12]; // Ÿ��
	RECT _animation; // �������°� �����ֱ��

	const int _rotation[20] = { 0,2,1,0,2,1,0,1,2,1,0,2,1,0,2,1,0,1,2,1 };// ����
	int _rotationCount; // �������

	int _timeCount; // ������� or �ð������� ������ ���� ī��Ʈ

	int _leftCount; // ���� ���Ƚ��
	int _score; // ����
	int _randNum; // ������ ����

	bool _isStand; // ǥ���� ����������
	bool _animationDown; // ������ ����


public:
	playGround();
	~playGround();

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ����
	virtual void render(HDC hdc);	//�׸��� ����
};

