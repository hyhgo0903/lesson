#pragma once
#include "gameNode.h"
#include "Messenger.h"
#include "enemyManager.h"
#include "MainStage.h"
#include "BossStage.h"
#include "StartScene.h"
#include"DeadScene.h"
class playGround : public gameNode
{
private:
	Messenger* _messenger;
	enemyManager* em;
	POINT camera;//ī�޶� ��ǥ�� �Է¹ޱ� ���� ��������
	float probeDY;//�Ʒ� �浹 Ž��
	float probeUY;//�� �浹 Ž��
	float EprobeDY;//���ʹ̵� �߷��� ����
	float probeX;//�¿��� �浹��
public:
	playGround();
	~playGround();

	virtual HRESULT init();	//�ʱ�ȭ ���� �Լ�
	virtual void release();	//�޸� ���� �Լ�
	virtual void update();	//���� ����
	virtual void render();	//�׸��� ����
	void addImage();
	void pixelCollision();
	void RectCollision();
	POINT getCamera() { return camera; }
};
