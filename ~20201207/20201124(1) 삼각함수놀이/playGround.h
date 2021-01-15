#pragma once
#include "gameNode.h"

#define PI 3.14f
#define BULLETMAX 30

struct tagBullet
{
	float x, y;		//���� x, y
	float speed;	//���ǵ�
	float angle;	//����
	// ���� x�ӵ� y�ӵ��� �ߴµ� ���� ������ �����ϴ� ����� ���̴�
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

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ����
	virtual void render(HDC hdc);	//�׸��� ����

	void bulletFire();
	void bulletMove();

};

