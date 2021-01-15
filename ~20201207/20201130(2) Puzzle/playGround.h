#pragma once
#include "gameNode.h"

struct location
{
	int ID; // 출력용 좌표(ID값. 최초 부여되고 안바뀜)
	int xx, yy; // 어디에 있는지 (계속 바뀜) x좌표 y좌표
};

class playGround : public gameNode
{
private:
	image* _background; // 퍼즐 그림(-7-)
	image* _select; // 고르는거(허접함)
	image* _thumbnail; // 작은 그림
	int _size; //고르면 할당받음. 사이즈
	int _temp; //자리바꾸기용

	int _xx, _yy; // 임시로 받는 x,y좌표(for문으로 검사해서 받음)
	int _number, _compare; // 자리찾기용 임시
	int _randNum; // 상하좌우 랜덤
	int _count; // 얼마나 맞췄는지
	int _tryCount; // 시도횟수. 1이상이어야 정답처리됨(섞일때 정답처리 되면 안되니깐..)

	location _location[100];

	char str[256]; // 글자 출력할떄
	bool _changed; // 한번 바꿨으면 그외 4방향검사 안하려고 있는 불값(break느낌)
	bool _isEnd; // 정답 다맞췄으면 게임끝

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
	int right(); // 4방향 검사해서 빈칸이면 자리바꾸는 함수

	void mix(); // 섞는 함수. for문의 mixTry로 섞고 빈칸은 오른쪽 아래로 보내는 과정
	void mixTry(); // 한번 섞을때. 상하좌우중 하나 받아서 자리바꿈
};

