#pragma once
#include "gameNode.h"

//���� ���� 
enum PUZZLE
{
	PUZZLE_1, PUZZLE_2, PUZZLE_3,
	PUZZLE_4, PUZZLE_5, PUZZLE_6,
	PUZZLE_7, PUZZLE_8, PUZZLE_NULL
};

//���� ����ü
struct tagPuzzle
{
	PUZZLE puzzle;		//�̳ѹ�
	RECT rc;			//��Ʈ
	POINT ptDraw;		//�׷��� ��ġ
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

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ����
	virtual void render(HDC hdc);	//�׸��� ����

	void shuffle(int count);
	void retracePuzzle(void);
	void puzzleMove(void);
	void swapPuzzle(tagPuzzle* puzzle1, tagPuzzle* puzzle2);

};

