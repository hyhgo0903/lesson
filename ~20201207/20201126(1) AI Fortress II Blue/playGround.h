#pragma once
#include "gameNode.h"

#define PI 3.14f
#define BULLETMAX 70
#define TRACKSIZE 1
#define CANNONRADIUS 50
#define BULLETRADIUS 5

struct tagBullet
{
	float x, y;		//���� x, y
	float speed;	//���ǵ�
	float angle;	//����
	float radius;	//������
	bool isFire;	//�߽��ߴ�?
	float gravity;
};

struct tagCannon
{
	POINT center;		//ĳ�� ����
	POINT cannonEnd;	//ĳ�� ���� ����
	float cannon;			//����(?) ����
	float angle;		//����
};


class playGround : public gameNode
{
private:
	tagBullet _bullet[BULLETMAX];
	tagBullet _bulletAI[BULLETMAX];
	tagCannon _cannon;

	tagCannon _cannonAI;

	tagBullet _track[BULLETMAX];
	tagBullet _trackAI[BULLETMAX];

	RECT _ourHP;
	RECT _ourHPBack; // ü�¹ٶ� ü�¹� ��
	RECT _AIHP;
	RECT _AIHPBack; // ��ü�¹ٶ� ü�¹� ��
	RECT _reload;
	RECT _reloadBack; // ���ε�ٶ� ���ε�� ��
	RECT _reloadAI;
	RECT _reloadAIBack; // �� ���ε�ٶ� ���ε�� ��

	RECT _temp; // �浹������
	RECT _bigRect; // ������ �簢��

	const int _speed = 8; // �Ѿ� ���ǵ�� ���⼭ (������ ����)

	float _predictX; // ������ x

	int _angleDirection; // AI������ �ö󰡰��ִ��� �����ϰ��ִ���(�׳� �Ұ����� �� ������..)

	int _peaceCount; // �����ϸ� ���ͽ�Ű����
	bool _peace; // �����ϸ� ����

	bool _isDead;
	bool _isDeadAI;

	bool _isNorang;

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ����
	virtual void render(HDC hdc);	//�׸��� ����

	void bulletFire();
	void bulletFireAI();
	void bulletMove();

	void trackSet(); // Ʈ������ �Լ�
	void trackSetAI(); // AI�� Ʈ������ �Լ�
	void AIangleSet(); // AI�� �ޱ����� �Լ�

	void collide(); //������

	void evasion(); // ȸ�Ǳ⵿
};

