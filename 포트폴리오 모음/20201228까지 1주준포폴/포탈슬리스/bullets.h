#pragma once
#include "gameNode.h"

#define BULLETDURATION 1000
// _duration : ī��Ʈ�� ���׳��� ���������� ���ӽð� ������ ������

// �⺻���� ���� ����. �������ΰ� ����ϰ� �����ҿ���
class bullets :	public gameNode
{
protected:
	int _ID;				// �Ѿ��� ����
	RECT _rc;			// �浹�� �簢��
	float _x, _y;		// x,y��ǥ
	int _width, _height;// �Ѿ� ID�� ���� �ο�
	float _xSpd, _ySpd;	// x,y�ӵ�
	bool _isFire;		// 
	int _duration;		// �ʹ� ���������� �˾Ƽ� ��������Ϸ���
	int _frameX;		// ������ �ε���
	int _frameCount;	// ������ī��Ʈ��
	float _damage;
	float _wind;		// UI���� ����°� �����ϵ���...

public:
	bullets() {};
	~bullets() {};

	void move();
	bool& getIsFire() { return _isFire; }
	RECT getRect() { return _rc; }

	float getDamage() { return _damage; } // ��������ŭ ü�±�� �Լ��� �־��ش�
	void setWind(float wind) { _wind = 0.15f * wind; } // �ٶ����� ��� �ٲ��ش�

	int& getDuration() { return _duration; } // duration�� ������� ������ �ϱ� ���� �����ڷ�..
	float getID() { return _ID; } // ����ź �������� �Ǻ��Ϸ��� �߰�

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};

