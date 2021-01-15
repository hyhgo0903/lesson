#pragma once
#include "gameNode.h"

#define REGENTIME 50

struct taxi
{
	RECT rc;
	bool appear;
	float speed; // ������� ���� �ӵ��� �����״�
};


class playGround : public gameNode
{
private:
	image* _backgroundImg;
	image* _ambulImg;
	image* _taxiImg;
	image* _gauge;
	image* _restartImg;
	int _loopX, _loopY;
	image* _number[10];

	RECT _ambul;
	taxi _taxi[5];

	int _regenCount;
	int _appearCount;
	int _randNum;
	int _score;

	RECT _temp; // �浹������

	float _speed; // �ں� �ӵ�
	float _oil;
	float _speedAngle;
	float _oilAngle; // ����ǿ� �ޱ�
	float _sideSpeed; // �¿�ӵ�(�¿�� ������)


public:
	playGround();
	~playGround();

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ����
	virtual void render(HDC hdc);	//�׸��� ����

	void setImage();
	void taxiRegen();
	void collision();
	void taxiTaxiCollision();
	void gaugeAngle();

};

