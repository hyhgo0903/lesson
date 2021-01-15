#include "stdafx.h"
#include "playGround.h"

playGround::playGround()
{
}


playGround::~playGround()
{
}

//초기화는 여기다 하세요
HRESULT playGround::init()
{
	gameNode::init();

	_puzzleImage = new image;
	_puzzleImage->init("코기.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	//9등분
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			_puzzle[i * 3 + j].puzzle = PUZZLE(i * 3 + j);
			_puzzle[i * 3 + j].num = i * 3 + j;
			_puzzle[i * 3 + j].rc = RectMake(i * 200, j * 200, 200, 200);
			_puzzle[i * 3 + j].ptDraw = PointMake(_puzzle[i * 3 + j].rc.left,
				_puzzle[i * 3 + j].rc.top);
		}
	}

	shuffle(10);

	retracePuzzle();

	return S_OK;
}

//메모리 해제는 여기다 하세요
void playGround::release()
{
	gameNode::release();


}

//연산(계산)은 여기다 하세요
void playGround::update()
{
	gameNode::update();


	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) puzzleMove();
}

//제발 여기다 그려라 좀...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ 위에 건들지 마라 ==============================
	
	for (int i = 0; i < 9; i++)
	{
		if (_puzzle[i].puzzle == PUZZLE_NULL) continue;
		_puzzleImage->render(backDC, _puzzle[i].rc.left, _puzzle[i].rc.top,
			_puzzle[i].ptDraw.x, _puzzle[i].ptDraw.y, 200, 200);

	}
	
	//================= 아래도 건들지 마라 ==============================
	this->getBackBuffer()->render(hdc, 0, 0);
}


void playGround::shuffle(int count)
{
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (_puzzle[j].puzzle == PUZZLE_NULL)
			{
				if (j == 8)
				{
					int rnd = RND->getInt(2);
					if (rnd == 0) swapPuzzle(&_puzzle[j], &_puzzle[j - 1]);
					else swapPuzzle(&_puzzle[j], &_puzzle[j - 3]);
					break;
				}
				else if (j == 6)
				{
					int rnd = RND->getInt(2);
					if (rnd == 0) swapPuzzle(&_puzzle[j], &_puzzle[j + 1]);
					else swapPuzzle(&_puzzle[j], &_puzzle[j - 3]);
					break;
				}
				else if (j == 2)
				{
					int rnd = RND->getInt(2);
					if (rnd == 0) swapPuzzle(&_puzzle[j], &_puzzle[j - 1]);
					else swapPuzzle(&_puzzle[j], &_puzzle[j + 3]);
					break;
				}
				else if (j == 0)
				{
					int rnd = RND->getInt(2);
					if (rnd == 0) swapPuzzle(&_puzzle[j], &_puzzle[j + 1]);
					else swapPuzzle(&_puzzle[j], &_puzzle[j + 3]);
					break;
				}
				else if (j == 7)
				{
					int rnd = RND->getInt(3);
					if (rnd == 0) swapPuzzle(&_puzzle[j], &_puzzle[j - 3]);
					else if (rnd == 1) swapPuzzle(&_puzzle[j], &_puzzle[j - 1]);
					else swapPuzzle(&_puzzle[j], &_puzzle[j + 1]);
					break;
				}
				else if (j == 5)
				{
					int rnd = RND->getInt(3);
					if (rnd == 0) swapPuzzle(&_puzzle[j], &_puzzle[j - 1]);
					else if (rnd == 1) swapPuzzle(&_puzzle[j], &_puzzle[j - 3]);
					else swapPuzzle(&_puzzle[j], &_puzzle[j + 3]);
					break;
				}
				else if (j == 3)
				{
					int rnd = RND->getInt(3);
					if (rnd == 0) swapPuzzle(&_puzzle[j], &_puzzle[j + 1]);
					else if (rnd == 1) swapPuzzle(&_puzzle[j], &_puzzle[j - 3]);
					else swapPuzzle(&_puzzle[j], &_puzzle[j + 3]);
					break;
				}
				else if (j == 1)
				{
					int rnd = RND->getInt(3);
					if (rnd == 0) swapPuzzle(&_puzzle[j], &_puzzle[j + 1]);
					else if (rnd == 1) swapPuzzle(&_puzzle[j], &_puzzle[j - 1]);
					else swapPuzzle(&_puzzle[j], &_puzzle[j + 3]);
					break;
				}
				else if (j == 4)
				{
					int rnd = RND->getInt(4);
					if (rnd == 0) swapPuzzle(&_puzzle[j], &_puzzle[j - 1]);
					else if (rnd == 1) swapPuzzle(&_puzzle[j], &_puzzle[j + 1]);
					else if (rnd == 2) swapPuzzle(&_puzzle[j], &_puzzle[j - 3]);
					else swapPuzzle(&_puzzle[j], &_puzzle[j + 3]);
					break;
				}
			}
		}
	}
}

void playGround::retracePuzzle(void)
{
	while (true)
	{
		shuffle(1);
		if (_puzzle[PUZZLE_NULL].puzzle == PUZZLE_NULL) return;
	}
}

void playGround::puzzleMove(void)
{
	for (int i = 0; i < 9; i++)
	{
		if (PtInRect(&_puzzle[i].rc, _ptMouse))
		{
			switch (i)
			{
			case 0:
				if (_puzzle[i + 1].puzzle == PUZZLE_NULL) swapPuzzle(&_puzzle[i], &_puzzle[i + 1]);
				else if (_puzzle[i + 3].puzzle == PUZZLE_NULL) swapPuzzle(&_puzzle[i], &_puzzle[i + 3]);
				break;
			case 2:
				if (_puzzle[i - 1].puzzle == PUZZLE_NULL) swapPuzzle(&_puzzle[i], &_puzzle[i - 1]);
				else if (_puzzle[i + 3].puzzle == PUZZLE_NULL) swapPuzzle(&_puzzle[i], &_puzzle[i + 3]);
				break;
			case 6:
				if (_puzzle[i + 1].puzzle == PUZZLE_NULL) swapPuzzle(&_puzzle[i], &_puzzle[i + 1]);
				else if (_puzzle[i - 3].puzzle == PUZZLE_NULL) swapPuzzle(&_puzzle[i], &_puzzle[i - 3]);
				break;
			case 8:
				if (_puzzle[i - 1].puzzle == PUZZLE_NULL) swapPuzzle(&_puzzle[i], &_puzzle[i - 1]);
				else if (_puzzle[i - 3].puzzle == PUZZLE_NULL) swapPuzzle(&_puzzle[i], &_puzzle[i - 3]);
				break;
			case 1:
				if (_puzzle[i - 1].puzzle == PUZZLE_NULL) swapPuzzle(&_puzzle[i], &_puzzle[i - 1]);
				else if (_puzzle[i + 1].puzzle == PUZZLE_NULL) swapPuzzle(&_puzzle[i], &_puzzle[i + 1]);
				else if (_puzzle[i + 3].puzzle == PUZZLE_NULL) swapPuzzle(&_puzzle[i], &_puzzle[i + 3]);
				break;
			case 3:
				if (_puzzle[i + 1].puzzle == PUZZLE_NULL) swapPuzzle(&_puzzle[i], &_puzzle[i + 1]);
				else if (_puzzle[i - 3].puzzle == PUZZLE_NULL) swapPuzzle(&_puzzle[i], &_puzzle[i - 3]);
				else if (_puzzle[i + 3].puzzle == PUZZLE_NULL) swapPuzzle(&_puzzle[i], &_puzzle[i + 3]);
				break;
			case 5:
				if (_puzzle[i - 1].puzzle == PUZZLE_NULL) swapPuzzle(&_puzzle[i], &_puzzle[i - 1]);
				else if (_puzzle[i - 3].puzzle == PUZZLE_NULL) swapPuzzle(&_puzzle[i], &_puzzle[i - 3]);
				else if (_puzzle[i + 3].puzzle == PUZZLE_NULL) swapPuzzle(&_puzzle[i], &_puzzle[i + 3]);
				break;
			case 7:
				if (_puzzle[i + 1].puzzle == PUZZLE_NULL) swapPuzzle(&_puzzle[i], &_puzzle[i + 1]);
				else if (_puzzle[i - 1].puzzle == PUZZLE_NULL) swapPuzzle(&_puzzle[i], &_puzzle[i - 1]);
				else if (_puzzle[i - 3].puzzle == PUZZLE_NULL) swapPuzzle(&_puzzle[i], &_puzzle[i - 3]);
				break;

			case 4:
				if (_puzzle[i + 1].puzzle == PUZZLE_NULL) swapPuzzle(&_puzzle[i], &_puzzle[i + 1]);
				else if (_puzzle[i - 1].puzzle == PUZZLE_NULL) swapPuzzle(&_puzzle[i], &_puzzle[i - 1]);
				else if (_puzzle[i - 3].puzzle == PUZZLE_NULL) swapPuzzle(&_puzzle[i], &_puzzle[i - 3]);
				else if (_puzzle[i + 3].puzzle == PUZZLE_NULL) swapPuzzle(&_puzzle[i], &_puzzle[i + 3]);
				break;
			}
		}
	}
}

void playGround::swapPuzzle(tagPuzzle* puzzle1, tagPuzzle* puzzle2)
{
	PUZZLE PZ;
	POINT ptDraw;

	PZ = puzzle1->puzzle;
	puzzle1->puzzle = puzzle2->puzzle;
	puzzle2->puzzle = PZ;

	ptDraw = puzzle1->ptDraw;
	puzzle1->ptDraw = puzzle2->ptDraw;
	puzzle2->ptDraw = ptDraw;

}
