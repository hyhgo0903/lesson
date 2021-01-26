#pragma once
#include "gameNode.h"
#include<vector>
struct tagBullet
{
	image* bulletImage;		//�Ѿ��� �̹���
	RECT rc;				//�Ѿ��浹�� ���� ��Ʈ
	float x, y;				//���� ��ǥ
	int width;
	int height;
	float speed;			//���ǵ�
	float fireX, fireY;		//�߻���ġ
	bool isFire;			//�߻��ߴ�?
	int count;				//������ �̹��� ī��Ʈ��
	int direction;
};

class Bullet :
    public gameNode
{
private:
	vector<tagBullet>_vBullet;
	vector<tagBullet>::iterator _viBullet;
	const char* _imgName;
	float _range;
	int _bulletMax;
public:
	Bullet() {};
	~Bullet() {};

	HRESULT init(const char* imageName, int bulletMax, float range);
	void release();
	void update();
	void render(POINT camera);

	void fire(float x, float y,float speed,int direction);

	void move();

	void removeMissile(int arrNum);

	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getViBullet() { return _viBullet; }
};


