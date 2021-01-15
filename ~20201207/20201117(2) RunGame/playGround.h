#pragma once
#include "gameNode.h"


class playGround : public gameNode
{
private:
	RECT _rc;
	float _x, _y;


	RECT _rc2; // �ٴڰ˻��

	RECT _obstacle[3]; // ��ֹ�
	RECT _ground[3]; // �ٴ�
	int _jumpCount; // �������� Ƚ��
	bool _isStart; // ���� �����ߴ���
	bool _isDead; // �׾�����
	bool _isSlide; // �����ȴ���

	float _jumpPower; // �����Ŀ�
	float _gravity; // �߷�

	char str[256];

	int randNum; // �����뺯��
	int score, highScore; // ���ھ�
	STATUS status;

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ����
	virtual void render(HDC hdc);	//�׸��� ����
};

