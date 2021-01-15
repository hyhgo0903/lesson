#pragma once
#include "gameNode.h"

struct location
{
	int ID; // 출력용 좌표(ID값. 최초 부여되고 안바뀜)
	int xx, yy; // 어디에 있는지 좌표
};

class playGround : public gameNode
{
private:
	image* _background;
	image* _select;
	image* _thumbnail;
	int _size;
	int _temp; //자리바꾸기용

	int _xx, _yy;
	int _number, _compare; // 자리찾기용 임시
	int _randNum; // 상하좌우 랜덤
	int _count;

	location _location[100];

	char str[256];
	bool _changed;

	bool _isSelect; // 처음에 숫자고르는 함수

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//초기화 전용 함수
	virtual void release();			//메모리 해제 함수
	virtual void update();			//연산 전용
	virtual void render(HDC hdc);	//그리기 전용

	int select();
	void selectInit();

	int up();
	int down();
	int left();
	int right();

	void mix();
	void mixTry();
	void check();
};

