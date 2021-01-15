#pragma once
#include "gameNode.h"

enum SIVADIRECTION
{
	SIVA_LEFT_IDLE,
	SIVA_RIGHT_IDLE,
	SIVA_LEFT_RUN,
	SIVA_RIGHT_RUN
};

class playGround : public gameNode
{
private:
	image* _background;
	image* _siva;
	SIVADIRECTION _direction;

	int _count, _index;

	RECT _miniMap;
	RECT _miniP;

	int _cameraX;

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ����
	virtual void render(HDC hdc);	//�׸��� ����


};

