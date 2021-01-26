#pragma once
#include "enemy.h"

enum enemyState
{
	IDLE, WALK, ATTACK
};

class groundEnemy : public enemy
{
private:
	int _left; // �����̸� 1�� �ǰ� �������̸� 0. 0���� Ŭ�� �̻��Ϲ߻�� x�ӵ��� -1�� ������	
	int _playerX; // �÷��̾��� ��ġ
	enemyState _state;
	float _ySpd; // �߷²� ��������
	int _probeY; // �ȼ��浹��
	int _destX; // ������
	bool _offGround; // ���� ������

public:
	groundEnemy() {};
	~groundEnemy() {};

	virtual HRESULT init(int ID, float x, float y);
	virtual void release();
	virtual void update();
	virtual void render();

	void pixelCollision();
	void frameXUpdate();
	void stateChange();
	void stateRender();
	void fireReady();
	void groundMove();

	inline int getLeft() { return _left; }
	inline void setPlayerX(int playerX) { _playerX = playerX; }
};

