#pragma once
#include "gameNode.h"

//���� �����ϰ� �ִ� ����ü!
struct tagBird
{
	float x, y;			//���� x,y
	RECT rc;			//�浹�� ��Ʈ
	RECT rc2;			//�� ������ �浹�������� �ΰ��� �̿�
	float gravity;		//�����̰� �Ⱦ��ϴ� �׶��Ƽ
	float jumpPower;	//����� �����ϴ� ���ں���~
};

class playGround : public gameNode
{
private:
	image* _background;	image* _day;	image* _night; // ����̹���
	image* _uppipe;	image* _downpipe; // ���̻��̹���
	image* _number[10]; // ���ھ�� ����
	image* _restart; // �ټ� ���Ǿ��� �������� �𸣴� ���ͱ׸�

	image* _alki; // ���¾�Ű
	image* _alki2; // ��ǥ����Ű

	RECT _upPipeRc[2]; // ���̻�
	RECT _downPipeRc[2];

	RECT _temp; // ���ͼ�Ʈ��Ʈ ������

	bool _isNight; // ���̸�
	int _count; // �������� ī��Ʈ
	int _score; // ����� �����ɶ����� ���ھ����

	int _upPipeWitch; // �� ������ ��ġ�� �������� ����ÿ���
	bool _isDead; // �׾����� �����ߴ�

	tagBird _bird;

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ����
	virtual void render(HDC hdc);	//�׸��� ����



};

