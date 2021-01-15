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

	_select = new image;
	_select->init("select.bmp", 750, 525);

	_background = new image;
	_background->init("puzzle.bmp", 525, 525);

	_background = new image;
	_background->init("puzzle.bmp", 525, 525);
		
	_thumbnail = new image;
	_thumbnail->init("thumbnail.bmp", 200, 200);

	_isSelect = true;

	_changed = false;

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

	if (_isSelect)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) select();
	}
	else
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && _ptMouse.x > 0 && _ptMouse.x < 525 && _ptMouse.y > 0 && _ptMouse.y < 525)
		{ // 자리바꾸기
			up(); down(); left(); right(); // 상하좌우 비교해서 이동하는 함수들
			_changed = false;
		}
	}

}

//제발 여기다 그려라 좀...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ 위에 건들지 마라 ==============================
	
	if (_isSelect)
	{
		_select->render(backDC, 0, 0);
	}
	else
	{

		for (int i = 0; i < _size*_size - 1; i++)
		{
			_background->render(backDC, _location[i].xx * 525 / _size, // 출력 위치는 바뀜
				_location[i].yy * 525 / _size,
				(_location[i].ID%_size) * 525 / _size, // 출력참고하는 지점은 불변
				(_location[i].ID/_size) * 525 / _size,
				525 / _size + 1, 525 / _size + 1); // +1해야 빈줄이 안나옴			
		}

		_thumbnail->render(backDC, 538, 30);
		sprintf_s(str, "%d X %d", _size, _size);
		TextOut(backDC, 620, 250, str, strlen(str));
		if (_size > 5)
		{
			sprintf_s(str, "왜 이런 선택을..");
			TextOut(backDC, 580, 275, str, strlen(str));
		}
		
		_count = 0;
		for (int i = 0; i < _size*_size; i++)
		{
			if (_location[i].xx == i % _size && _location[i].yy == i / _size)
			{
				_count += 1;
			}
		}
		if (_count == _size * _size)
		{
			sprintf_s(str, "다 맞췄습니다~!");
			TextOut(backDC, 600, 275, str, strlen(str));
		}

	}
	
	//================= 아래도 건들지 마라 ==============================
	this->getBackBuffer()->render(hdc, 0, 0);
}

int playGround::select() // 맨 첨에 고르는 함수
{
	if (_ptMouse.x < 0 || _ptMouse.x>525 || _ptMouse.y < 0 || _ptMouse.y>525) return 0;
	if (_ptMouse.x >= 0 && _ptMouse.x < 175 && _ptMouse.y >= 0 && _ptMouse.y < 175)
	{ // 3x3선택
		_size = 3;	selectInit();
	}
	else if (_ptMouse.x >= 175 && _ptMouse.x < 350
		&& _ptMouse.y >= 0 && _ptMouse.y < 175) // 175는 525/3
	{ // 4x4선택
		_size = 4;	selectInit();
	}
	else if (_ptMouse.x >= 350 && _ptMouse.x < 525
		&& _ptMouse.y >= 0 && _ptMouse.y < 175)
	{ // 5x5선택
		_size = 5;	selectInit();
	}
	else if (_ptMouse.x >= 0 && _ptMouse.x < 175
		&& _ptMouse.y >= 175 && _ptMouse.y < 350)
	{ // 6x6선택
		_size = 6;	selectInit();
	}
	else if (_ptMouse.x >= 175 && _ptMouse.x < 350
		&& _ptMouse.y >= 175 && _ptMouse.y < 350)
	{ // 7x7선택
		_size = 7;	selectInit();
	}
	else if (_ptMouse.x >= 350 && _ptMouse.x < 525
		&& _ptMouse.y >= 175 && _ptMouse.y < 350)
	{ // 8x8선택
		_size = 8;	selectInit();
	}
	else if (_ptMouse.x >= 0 && _ptMouse.x < 175
		&& _ptMouse.y >= 350 && _ptMouse.y < 525)
	{ // 9x9선택
		_size = 9;	selectInit();
	}
	else if (_ptMouse.x >= 175 && _ptMouse.x < 350
		&& _ptMouse.y >= 350 && _ptMouse.y < 525)
	{ // 10x10선택
		_size = 10;	selectInit();	
	}
	return 0;
}

void playGround::selectInit()
{
	for (int i = 0; i < _size*_size; i++)
	{
		_isSelect = false;
		_location[i].ID = i; // 고유의 값 부여함 (_size*_size-1)이면 빈칸임
		_location[i].xx = i % _size;
		_location[i].yy = i / _size; // 계속 바뀜
	}
	mix();
}

int playGround::up() // 윗칸과 비교를 한다
{
	_xx = _ptMouse.x* _size / 525;
	_yy = _ptMouse.y* _size / 525;
	if (_yy == 0 || _changed) return 0;
	for (int i = 0; i < _size*_size; i++) // 해당위치 찾는다
	{
		if (_location[i].xx == _xx && _location[i].yy == _yy) _number = i;
		if (_location[i].xx == _xx && _location[i].yy == _yy-1) _compare = i; // 비교할거
	}
	if (_location[_compare].ID == _size*_size-1) // 빈칸이면
	{
		_temp = _location[_number].yy;
		_location[_number].yy = _location[_compare].yy;
		_location[_compare].yy = _temp;
		_changed = true;
	}
}

int playGround::down() // 아랫칸과 비교를 한다
{
	_xx = _ptMouse.x* _size / 525;
	_yy = _ptMouse.y* _size / 525;
	if (_yy == _size-1 || _changed) return 0;
	for (int i = 0; i < _size*_size; i++) // 해당위치 찾는다
	{
		if (_location[i].xx == _xx && _location[i].yy == _yy) _number = i;
		if (_location[i].xx == _xx && _location[i].yy == _yy + 1) _compare = i;
	}
	if (_location[_compare].ID == _size * _size - 1) // 빈칸이면
	{
		_temp = _location[_number].yy;
		_location[_number].yy = _location[_compare].yy;
		_location[_compare].yy = _temp;
		_changed = true;
	}
}

int playGround::left()
{
	_xx = _ptMouse.x* _size / 525;
	_yy = _ptMouse.y* _size / 525;
	if (_xx == 0 || _changed) return 0;
	for (int i = 0; i < _size*_size; i++) // 해당위치 찾는다
	{
		if (_location[i].xx == _xx && _location[i].yy == _yy) _number = i;
		if (_location[i].xx == _xx -1 && _location[i].yy == _yy) _compare = i;
	}
	if (_location[_compare].ID == _size * _size - 1) // 빈칸이면
	{
		_temp = _location[_number].xx;
		_location[_number].xx = _location[_compare].xx;
		_location[_compare].xx = _temp;
		_changed = true;
	}
}

int playGround::right()
{
	_xx = _ptMouse.x* _size / 525;
	_yy = _ptMouse.y* _size / 525;
	if (_xx == _size-1 || _changed) return 0;
	for (int i = 0; i < _size*_size; i++) // 해당위치 찾는다
	{
		if (_location[i].xx == _xx && _location[i].yy == _yy) _number = i;
		if (_location[i].xx == _xx + 1 && _location[i].yy == _yy) _compare = i;
	}
	if (_location[_compare].ID == _size * _size - 1) // 빈칸이면
	{
		_temp = _location[_number].xx;
		_location[_number].xx = _location[_compare].xx;
		_location[_compare].xx = _temp;
		_changed = true;
	}
}

void playGround::mix()
{
	srand(time(NULL)); // 안했더니 제대로 안됨
	for (int i = 0; i < 10000; i++) // 1000번 섞는다.(10x10은 100칸이라서 오지게 안섞임)
	{
		mixTry();
	}
	for (int i = 0; i < _size; i++) // 오른쪽 아래로 보내기
	{
		if (_location[_size*_size - 1].yy != _size-1) // 아래로
		{
			_location[_size*_size - 1].yy += 1;
			for (int i = 0; i < _size*_size - 1; i++) // 해당위치 찾는다
			{
				if (_location[i].xx == _location[_size*_size - 1].xx
					&& _location[i].yy == _location[_size*_size - 1].yy)
				{
					_number = i;
					break;
				}
			}
			_location[_number].yy -= 1;
		}
		if (_location[_size*_size - 1].xx != _size - 1) // 아래로
		{
			_location[_size*_size - 1].xx += 1;
			for (int i = 0; i < _size*_size - 1; i++) // 해당위치 찾는다
			{
				if (_location[i].xx == _location[_size*_size - 1].xx
					&& _location[i].yy == _location[_size*_size - 1].yy)
				{
					_number = i;
					break;
				}
			}
			_location[_number].xx -= 1;
		}

	}
}

void playGround::mixTry()
{
	_randNum = rand() % 4;
	if (_randNum == 0 && _location[_size*_size-1].yy != 0) // 위로
	{
		_location[_size*_size - 1].yy -= 1;
		for (int i = 0; i < _size*_size - 1; i++) // 해당위치 찾는다
		{
			if (_location[i].xx == _location[_size*_size - 1].xx
				&& _location[i].yy == _location[_size*_size - 1].yy)
			{
				_number = i;
				break;
			}
		}
		_location[_number].yy += 1;
	}
	else if (_randNum == 1 && _location[_size*_size - 1].yy != _size-1) // 아래로
	{
		_location[_size*_size - 1].yy += 1;
		for (int i = 0; i < _size*_size - 1; i++) // 해당위치 찾는다
		{
			if (_location[i].xx == _location[_size*_size - 1].xx
				&& _location[i].yy == _location[_size*_size - 1].yy)
			{
				_number = i;
				break;
			}
		}
		_location[_number].yy -= 1;
	}
	else if (_randNum == 2 && _location[_size*_size - 1].xx != 0) // 왼쪽으로
	{
		_location[_size*_size - 1].xx -= 1;
		for (int i = 0; i < _size*_size - 1; i++) // 해당위치 찾는다
		{
			if (_location[i].xx == _location[_size*_size - 1].xx
				&& _location[i].yy == _location[_size*_size - 1].yy)
			{
				_number = i;
				break;
			}
		}
		_location[_number].xx += 1;
	}
	else if (_randNum == 3 && _location[_size*_size - 1].xx != _size-1) // 오른쪽으로
	{
		_location[_size*_size - 1].xx += 1;
		for (int i = 0; i < _size*_size - 1; i++) // 해당위치 찾는다
		{
			if (_location[i].xx == _location[_size*_size - 1].xx
				&& _location[i].yy == _location[_size*_size - 1].yy)
			{
				_number = i;
				break;
			}
		}
		_location[_number].xx -= 1;
	}
}
