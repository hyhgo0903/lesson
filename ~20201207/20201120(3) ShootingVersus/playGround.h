#pragma once
#include "gameNode.h"

struct tagBullet
{
	RECT rc;
	bool isFire;
	float x; // x�ӵ�
	float y; // y�ӵ�
	bool isYudo; // ����ź����?
	bool betrayed;
	// ��� �ÿ� �¾Ҵ���? ó������ '�Ҽ�'�̶�� ���������� �� ��������
};

enum PMODE
{ // ��带 �̳ѹ�����
	NORMAL = 0,
	MULTI,
	YUDO
};

#define BULLETMAX 30

class playGround : public gameNode
{
private:
	RECT _player1;	RECT _player2;	 // �÷��̾� �簢��
	RECT _bigRect1;	RECT _bigRect2; // ������ ���� �簢��(����ź��)


	RECT _obstacle; // ��ֹ�	
	RECT temp; // �浹
	PMODE _p1mode;	PMODE _p2mode; // ��带 �̳ѹ����� �����մϴ�.
	tagBullet _bulletP1[BULLETMAX];	tagBullet _bulletP2[BULLETMAX];
	// �Ѿ��� �� Ŭ������
	RECT _backGauge;	RECT _frontGauge; // �÷��̾�1 ü�¹�
	RECT _backGauge2;	RECT _frontGauge2; // �÷��̾�2 ü�¹�	
	POINTFLOAT _yudoFrom;	POINTFLOAT _yudoTo; // ����ź ������ ��ǥ���
	bool _isDeadP1; bool _isDeadP2; // ����
	bool _canUltiP1; bool _canUltiP2; // �û�밡��
	int _reloadCount1; int _reloadCount2; // ����ī��Ʈ
	int _ultiCount1; int _ultiCount2; // ��ī��Ʈ(��)
	double angle; // ����(����ź��)
	int _r, _g; 	int _r2, _g2; // ����
	int _direction; // ��ֹ��� ����(���Ʒ���)

	RECT _effect[8]; // ����Ʈ��
	bool _effectOn; //  ����Ʈ ��������

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ����
	virtual void render(HDC hdc);	//�׸��� ����

	void keyControl(); // Ű ��Ʈ��

	void bulletFireP1(); // �߻�
	void bulletFireP2();

	void bulletMove(); // �Ѿ��̵�(���)

	void collision(); // �浹(P2)
	void collision2(); // �浹(P1)

	void collisionObstacle(); // ��ֹ��� �Ѿ� ���

	void Yudo(); // ����ź �ν��ϴ°�
	void Yudo2();

	void ultiP1(); // �ùߵ�
	void ultiP2();

	float calcAngleFromPoints(POINTFLOAT _ptFirst, POINTFLOAT _ptSecond);
	// �� �ΰ��� �ޱ��� ���ϴ� �Լ�(from ���۸�)
};

