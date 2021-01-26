#pragma once
#include "gameNode.h"

enum STATE
{
	PHASE_1,
	PHASE_2,
	PHASE_3,
	PHASE_BOSS
};

class enemy : public gameNode
{
protected:
	image*	_imageName;			//���� ���� �̹����� ���� �� ����
	RECT	_rc;				//���� ���� ��Ʈ

	int		_currentFrameX;		//���� ������ ��ȣ X
	int		_currentFrameY;		//���� ������ ��ȣ Y

	int _toX, _toY; // ������
	int _tempX, _tempY; // ������3���� ������ ������
	int _x, _y; // ������ġ
	bool _arrived; // ù�����ؼ� �����ߴ���
	int _direction; // ���� 1�̳� -1��
	float _angle;


	int		_count;				//ī��Ʈ
	int		_fireCount;			//�߻� ī��Ʈ
	int		_rndFireCount;		//���� �߻� ī��Ʈ
	int     _countAgain;		//�� ī��Ʈ..(������3���� �ڸ� ���ϴ°�)

	int _bossPhase; // ���������°� ��������

	STATE _state;
public:
	enemy();
	~enemy();

	HRESULT init();
	HRESULT init(const char* imageName, POINT position, STATE state);
	void release();
	void update();
	void render();

	void move();
	void draw();

	bool bulletCountFire();

	//ȣ��!
	inline RECT getRect() { return _rc; }
	inline STATE getState() { return _state; }
	inline int getBossState() { return _bossPhase; }
	void phaseShift();
};

