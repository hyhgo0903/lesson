#pragma once
#include "gameNode.h"
class victoryScene :	public gameNode
{

private:
	int _score;
	int _highScore;
	
public:
	victoryScene();
	~victoryScene();

	virtual HRESULT init();	//�ʱ�ȭ ���� �Լ�
	virtual void release();	//�޸� ���� �Լ�
	virtual void update();	//���� ����
	virtual void render();	//�׸��� ����
};

