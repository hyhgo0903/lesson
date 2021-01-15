#pragma once
#include "gameNode.h"

#define PI 3.14f
#define BARMAX 30

struct tagBar
{
	RECT rc;
	int status; // 이넘쓸라했는데 편하게
	bool isOnScreen;	//출력중이니?
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

	virtual HRESULT init();			//초기화 전용 함수
	virtual void release();			//메모리 해제 함수
	virtual void update();			//연산 전용
	virtual void render(HDC hdc);	//그리기 전용

	void pressS();	void pressD();	void pressF();
	void pressSpace();
	void pressJ();	void pressK();	void pressL();
	
	void MakeS();	void MakeD();	void MakeF();
	void MakeSpace();
	void MakeJ();	void MakeK();	void MakeL();
	void MakeRandom();
};

