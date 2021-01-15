#pragma once
#include "gameNode.h"

struct location
{
	int ID; // ��¿� ��ǥ(ID��. ���� �ο��ǰ� �ȹٲ�)
	int xx, yy; // ��� �ִ��� ��ǥ
};

class playGround : public gameNode
{
private:
	image* _background;
	image* _select;
	image* _thumbnail;
	int _size;
	int _temp; //�ڸ��ٲٱ��

	int _xx, _yy;
	int _number, _compare; // �ڸ�ã��� �ӽ�
	int _randNum; // �����¿� ����
	int _count;

	location _location[100];

	char str[256];
	bool _changed;

	bool _isSelect; // ó���� ���ڰ��� �Լ�

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ����
	virtual void render(HDC hdc);	//�׸��� ����

	int select();
	void selectInit();

	int up();
	int down();
	int left();
	int right();

	void mix();
	void mixTry();
	void check();
};

