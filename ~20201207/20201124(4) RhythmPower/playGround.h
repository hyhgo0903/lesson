#pragma once
#include "gameNode.h"

#define PI 3.14f
#define BARMAX 30

struct tagBar
{
	RECT rc;
	int status; // �̳Ѿ����ߴµ� ���ϰ�
	bool isOnScreen;	//������̴�?
	bool isRight;
};

class playGround : public gameNode
{
private:
	tagBar _bar[BARMAX];
	int _musicCount;
	int _score, _combo;

	RECT _refereeRect[7];
	RECT temp;

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ����
	virtual void render(HDC hdc);	//�׸��� ����

	void pressS();	void pressD();	void pressF();
	void pressSpace();
	void pressJ();	void pressK();	void pressL();
	
	void MakeS();	void MakeD();	void MakeF();
	void MakeSpace();
	void MakeJ();	void MakeK();	void MakeL();
	void MakeRandom();
};

