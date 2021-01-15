#pragma once
#include "gameNode.h"

//퍼즐 구간 
enum PUZZLE
{
	PUZZLE_1, PUZZLE_2, PUZZLE_3,
	PUZZLE_4, PUZZLE_5, PUZZLE_6,
	PUZZLE_7, PUZZLE_8, PUZZLE_NULL
};

//퍼즐 구조체
struct tagPuzzle
{
	PUZZLE puzzle;		//이넘문
	RECT rc;			//렉트
	POINT ptDraw;		//그려줄 위치
	int num;
};

class playGround : public gameNode
{
private:
	image* _puzzleImage;

	tagPuzzle _puzzle[9];

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//초기화 전용 함수
	virtual void release();			//메모리 해제 함수
	virtual void update();			//연산 전용
	virtual void render(HDC hdc);	//그리기 전용

	void shuffle(int count);
	void retracePuzzle(void);
	void puzzleMove(void);
	void swapPuzzle(tagPuzzle* puzzle1, tagPuzzle* puzzle2);

};

