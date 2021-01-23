#pragma once
#include "gameNode.h"
#include "playScene.h"
#include "selectScene.h"
#include "gameOverScene.h"
#include "victoryScene.h"

class playGround : public gameNode
{
private:


public:
	playGround();
	~playGround();

	virtual HRESULT init();	//�ʱ�ȭ ���� �Լ�
	virtual void release();	//�޸� ���� �Լ�
	virtual void update();	//���� ����
	virtual void render();	//�׸��� ����

	void imageInit();
	void saveRecord(); // ����� ����(��������, �ִ����� ����)
};

