#pragma once
#include "gameNode.h"

#define PI 3.141592f
#define BULLETMAX 30
#define RADIUS 20

struct tagBullet
{
	float x, y;		//���� x, y
	float speed;	//���ǵ�
	float angle;	//����
	float radius;	//������
	bool isFire;	//�߽��ߴ�?
	float gravity;
};

struct tagCannon
{
	POINT center;		//ĳ�� ����
	POINT cannonEnd;	//ĳ�� ���� ����
	int radius;			//������
	int cannon;			//����(?) ����
	float angle;		//����
};

class playGround : public gameNode
{
private:
	tagBullet _bullet[BULLETMAX];
	tagCannon _cannon;
	float _angleTemp;

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ����
	virtual void render(HDC hdc);	//�׸��� ����

	void bulletFire();
	void bulletMove();

	void bulletCollision();
};

