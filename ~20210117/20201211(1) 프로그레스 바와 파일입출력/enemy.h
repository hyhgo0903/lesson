#pragma once
#include "gameNode.h"
#include "progressBar.h"



class enemy : public gameNode
{
protected:
	image*	_imageName;			//���� ���� �̹����� ���� �� ����
	RECT	_rc;				//���� ���� ��Ʈ

	int		_currentFrameX;		//���� ������ ��ȣ X
	int		_currentFrameY;		//���� ������ ��ȣ Y

	int		_count;				//ī��Ʈ
	int		_fireCount;			//�߻� ī��Ʈ
	int		_rndFireCount;		//���� �߻� ī��Ʈ

	float _currentHP, _maxHP;

	progressBar* _hpBar;

public:
	enemy();
	~enemy();

	HRESULT init();
	HRESULT init(const char* imageName, POINT position);
	void release();
	void update();
	void render();

	void move();
	void draw();

	bool bulletCountFire();

	//ȣ��!
	inline RECT getRect() { return _rc; }

};

