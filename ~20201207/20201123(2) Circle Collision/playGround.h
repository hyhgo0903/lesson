#pragma once
#include "gameNode.h"


class playGround : public gameNode
{
private:
	RECT _rc1;
	RECT _rc2;

	int x, y, h;
	// h�� ������ �ƴ϶� ������ ������
	int rr; // �񱳿�

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ����
	virtual void render(HDC hdc);	//�׸��� ����



};

