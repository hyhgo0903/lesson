#pragma once
#include "gameNode.h"
class gameOverScene :	public gameNode
{

private:
	int _score;
	int _highScore;
public:
	gameOverScene();
	~gameOverScene();

	virtual HRESULT init();	//�ʱ�ȭ ���� �Լ�
	virtual void release();	//�޸� ���� �Լ�
	virtual void update();	//���� ����
	virtual void render();	//�׸��� ����
};

