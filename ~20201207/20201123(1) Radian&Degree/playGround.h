#pragma once
#include "gameNode.h"

#define PI 3.14f // ����� �̷��Ը� �ص� 180���� �ν����ش�.

class playGround : public gameNode
{
private:
	//Radian : ȣ�� ���̶� �������� ������ 1�����̶� ��
	//			�뷫 1���� : 57.3��

	//Degree : ���� ��ġ�� ��Ʊ� ������ ����� ���ǻ� ���� ��.

	//PI(3.14) : 180��
	//PI / 2   : 90��
	//PI / 4   : 45��
	//PI / 180 : 1��

	float _radian;
	float _degree;

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ����
	virtual void render(HDC hdc);	//�׸��� ����



};

