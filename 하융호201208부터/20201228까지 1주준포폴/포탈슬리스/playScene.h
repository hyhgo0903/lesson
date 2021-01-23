#pragma once
#include "gameNode.h"
#include "playerManager.h"
#include "UIManager.h"
#include "itemManager.h"
#include "bulletManager.h"
#include "enemyManager.h"

#pragma warning(disable:4996) // itoa�� ����;��..

class playScene : public gameNode
{
private:	
	playerManager*	_pm;
	UIManager*		_um;
	itemManager*	_im;
	bulletManager*	_bm;
	enemyManager*	_em;
	int _scoreSum;
	int _highScore;
	int _goCount; // ī�޶� �ȸ����µ� �۶������ �̰� ��� �ö󰡸� �����ð� �̻��̸� �����ϴ� �׸��� ���´�.
	int _goFrameX; // �����ϴ°� �����ӿ�
	int _idleTime; // �̰� �׿��� ������ ��
	float _wind; // um�� �ٶ����� �޾Ƽ� bm,im�� ����

public:
	playScene();
	~playScene();

	HRESULT init(int data);	//�ʱ�ȭ ���� �Լ�
	HRESULT init();	//�ʱ�ȭ ���� �Լ�
	virtual void release();	//�޸� ���� �Լ�
	virtual void update();	//���� ����
	virtual void render();	//�׸��� ����

	void interfaceRender(); // �̴ϸ��� ���� �������� �׷����� �ϹǷ� ���⼭ ���� �������� �׸���� ��
	void saveRecord();
};

