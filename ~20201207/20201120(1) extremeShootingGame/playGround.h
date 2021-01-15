#pragma once
#include "gameNode.h"
#include "vector"

struct bullet
{
	RECT rc; // _bullet.rc�� ����
	float x; // x�ӵ�
	float y; // y�ӵ�
};

class playGround : public gameNode
{
private:
	RECT _effect[8]; // �����

	RECT _player; // ���ΰ�

	bullet _playerBullet[50]; // �� 50����
	
	int _reloadCount; // ������ ī��Ʈ

	int _leftLife; // ���� ���Ƚ��
	int _score; // ����
	int _highScore; // ����
	int _randNum; // ������ ����
	int _direction;

	bool _isStand; // ǥ���� ����������
	bool _animation; // ������ ����
	bool _offset;

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ����
	virtual void render(HDC hdc);	//�׸��� ����
};

