#pragma once
#include "unit.h"
class zergling :
	public unit
{
private:

public:
	zergling();
	~zergling();

	virtual HRESULT init();	//�ʱ�ȭ ���� �Լ�
	virtual void release();	//�޸� ���� �Լ�
	virtual void update();	//���� ����
	virtual void render();	//�׸��� ����

};

