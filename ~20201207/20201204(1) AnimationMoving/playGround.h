#pragma once
#include "gameNode.h"

#define SONICWIDTH 70
#define SONICHEIGHT 84 // ��Ӿ��� ���ȳ���� ��Ʈũ�� �����س���


enum SIVADIRECTION
{
	LEFT_RUN, // �޷�
	RIGHT_RUN,
	LEFT_HANG, // ����
	RIGHT_HANG,
	LEFT_IDLE, // ������
	RIGHT_IDLE,
	LEFT_ATTACK, // ����
	RIGHT_ATTACK,
	LEFT_JUMP, // ������
	RIGHT_JUMP
};

class playGround : public gameNode
{
private:
	image* _background; // ��׶��忡 ������Ʈ ���� �׷��־��� ���ϰ�
	image* _sonicImg; // �Ҵ��̹���
	SIVADIRECTION _direction; // �̳�

	RECT _sonicRc; // �Ҵ�
	RECT _bottom; // �ٴ�
	RECT _object[6]; //������Ʈ(0=��1, 1=��2, 2~4=������Ʈ3��, 5=�ٴ�)
	bool _objectIsNotCollide[6]; // ����ü�� ���������ߴµ� ����(�ٴ� �浹X)
	RECT _temp; // �浹��
	
	char str[256]; // ���� ��¿�
	int _attackReturn; // �������̸� ���ƿ��Բ� ����(������Ÿ�Ӱ�)

	int _count, _index;
	float _jumpPower; // �����Ŀ�
	float _gravity; // �߷�
	bool _onGround; // ���� �ִ���
	bool _isHang;	// �Ŵ޷ȴ���
	bool _isGapEum; // �Ŵ޷����� �ƿ� ���� ���� �׳� �и��� ��츦 ����

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ����
	virtual void render(HDC hdc);	//�׸��� ����

	void rectMove();		// ��Ʈ�̵�
	void keyInput();		// Ű�Ŵ�������
	void animation();		// �ִϸ��̼�
	void collision();		// �浹
	void jumpingCheck();	// �ٴ� ������ üũ
	void hangingCheck();	// �Ŵ޷ȳ� üũ
	void objectRegen();		// ���ֹ��� ������Ʈ(�� + SPACE��) ����

};

