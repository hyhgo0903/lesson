#pragma once
#include "gameNode.h"
class unit :	public gameNode
{
private:

public:
	unit();
	~unit();

	virtual HRESULT init();	//�ʱ�ȭ ���� �Լ�
	virtual void release();	//�޸� ���� �Լ�
	virtual void update();	//���� ����
	virtual void render();	//�׸��� ����
};

