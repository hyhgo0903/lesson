#pragma once
#include "gameNode.h"
#include <vector>

struct tagEnemyBullet
{
	image* enemyBulletImage;		//�Ѿ��� �̹���
	RECT rc;				//�Ѿ��浹�� ���� ��Ʈ
	float x, y;				//���� ��ǥ
	float angle;			//����
	float radius;			//������
	float speed;			//���ǵ�
	float fireX, fireY;		//�߻���ġ
	bool isFire;			//�߻��ߴ�?
	int count;				//������ �̹��� ī��Ʈ��
};

//�̸� �����صΰ� �߻��ϴ� �Ѿ�
class enemyBullets : public gameNode
{
private:
	vector<tagEnemyBullet> _vEnemyBullet;
	vector<tagEnemyBullet>::iterator _viEnemyBullet;

	float _range;		// ��Ÿ� �� ����


public:
	enemyBullets() {};
	~enemyBullets() {};

	HRESULT init(int bulletMax, float range);
	virtual void release();
	virtual void update();
	virtual void render();

	void fire(float x, float y);	//�߻�

	void move();					//�̵�
};