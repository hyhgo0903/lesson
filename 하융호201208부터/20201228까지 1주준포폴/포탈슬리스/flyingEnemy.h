#pragma once
#include "enemy.h"
class flyingEnemy : public enemy
{
private:
	int _phase; // ������ �������ּ��� ����� �����Ѵ�.

	float _destX, _destY; // ���������� (������ ������ ���� ������ �����ʿ��� ��)
	int _destinationCount;	// ������ �ٲٴ� ī��Ʈ

public:
	flyingEnemy() {};
	~flyingEnemy() {};

	virtual HRESULT init(int ID, float x, float y);
	virtual void release();
	virtual void update();
	virtual void render();

	void frameXUpdate();
	void fireReady();
	void flyingMove();

	inline int& getPhase() { return _phase; }
};

