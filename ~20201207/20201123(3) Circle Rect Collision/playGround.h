#pragma once
#include "gameNode.h"


class playGround : public gameNode
{
private:
	RECT _rc1;
	RECT _rc2;

	POINT _LT;

	int _x, _y, _h;
	// h�� ������ �ƴ϶� ������ ������

	int _edge1, _edge2, _edge3, _edge4; // ������������ �Ÿ�
	int _rr; // �񱳿�
	int _cc;

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ����
	virtual void render(HDC hdc);	//�׸��� ����



};

