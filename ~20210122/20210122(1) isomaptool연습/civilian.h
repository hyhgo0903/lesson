#pragma once
#include "unit.h"
class civilian :
	public unit
{

private:

public:
	civilian();
	~civilian();

	virtual HRESULT init();	//�ʱ�ȭ ���� �Լ�
	virtual void release();	//�޸� ���� �Լ�
	virtual void update();	//���� ����
	virtual void render();	//�׸��� ����
};

