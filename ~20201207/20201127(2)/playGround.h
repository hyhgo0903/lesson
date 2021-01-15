#pragma once
#include "gameNode.h"

//���� �����ϰ� �ִ� ����ü!
struct tagBird
{
	float x, y;			//���� x,y
	RECT rc;			//�浹�� ��Ʈ
	float gravity;		//�����̰� �Ⱦ��ϴ� �׶��Ƽ
	float jumpPower;	//����� �����ϴ� ���ں���~
	image* img;			//�� �̹���
};

class playGround : public gameNode
{
private:
	image* _background;
	image* _day;
	image* _night;

	bool _isNight;
	int _count;

	tagBird _bird;

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ����
	virtual void render(HDC hdc);	//�׸��� ����



};

