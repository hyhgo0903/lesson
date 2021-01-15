#pragma once
#include "gameNode.h"


class playGround : public gameNode
{
private:
	image* _background;
	int _loopX, _loopY;

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ����
	virtual void render(HDC hdc);	//�׸��� ����

	void setImage();

};

