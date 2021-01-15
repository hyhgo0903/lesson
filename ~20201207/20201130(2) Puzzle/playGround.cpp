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
	// 각종 이미지
	_isSelect = true;
	// 고르는중
	_changed = false;
	// 바꿨는지 (자리바꾸면 다른거 검사 안하려고 만든 불값)
	_isEnd = false;
	// 끝났는지 (다 맞추면 끝남)
	_count = _tryCount = _number = _compare = _randNum = _xx = _yy = _size = 0;
	// 헤더에 설명

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
	
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{ // 밑도끝도없이 초기화 가능
		this->init();
	}

	if (_isSelect && _size == 0)
	{ // 고르는함수 소환
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) select();
	}
	else
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) &&
			_ptMouse.x > 0 && _ptMouse.x < 525 && _ptMouse.y > 0 && _ptMouse.y < 525
			&& !_isEnd)
		{ // 자리바꾸기
			up(); down(); left(); right(); // 상하좌우 비교해서 자리바꾸는 함수
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
	{// 선택 페이즈면 셀렉트
		_select->render(backDC, 0, 0);
	}
	else
	{ // 아니면 그림이랑 이것저것 보여줌
		for (int i = 0; i < _size*_size - 1; i++)
		{
			_background->render(backDC, _location[i].xx * 525 / _size, // 출력 위치는 바뀜
				_location[i].yy * 525 / _size,
				(_location[i].ID%_size) * 525 / _size, // 출력참고하는 지점은 불변
				(_location[i].ID/_size) * 525 / _size,
				525 / _size + 1, 525 / _size + 1); // +1해야 빈줄이 안나옴			
		}

		_thumbnail->render(backDC, 538, 30); // 작은 그림 보여줌
		sprintf_s(str, "%d X %d", _size, _size); // 몇X몇인지
		TextOut(backDC, 610, 250, str, strlen(str));
		sprintf_s(str, "시도 : %d", _tryCount); // 시도횟수
		TextOut(backDC, 605, 270, str, strlen(str));
		sprintf_s(str, "재시작은 ENTER");
		TextOut(backDC, 580, 335, str, strlen(str));
		
		
		_count = 0; // 초기화시키고
		for (int i = 0; i < _size*_size; i++)
		{
			if (_location[i].xx == i % _size && _location[i].yy == i / _size)
			{ // 제자리에 맞게(?)있는걸 세어준다
				_count += 1;				
			}
		}
		if (_count == _size * _size && _tryCount > 0)
		{ // 제자리에 맞게 다 와있고 시도횟수가 1이상인 경우 정답처리
			sprintf_s(str, "다 맞췄습니다!");
			_background->render(backDC, 0,0); // 까짓거 다 그려서 덮어줌
			TextOut(backDC, 580, 300, str, strlen(str));
			_isEnd = true;
		}
		else if (_size > 5)
		{
			sprintf_s(str, "왜 이런 선택을..");
			TextOut(backDC, 580, 300, str, strlen(str));
		}

	}
	
	//================= 아래도 건들지 마라 ==============================
	this->getBackBuffer()->render(hdc, 0, 0);
}

int playGround::select() // 맨 첨에 고르는 함수
{
	if (_ptMouse.x < 0 || _ptMouse.x>525 || _ptMouse.y < 0 || _ptMouse.y>525) return 0;
	if (_ptMouse.x >= 0 && _ptMouse.x < 175 && _ptMouse.y >= 0 && _ptMouse.y < 175) // 175는 525/3
	{ // 3x3선택
		_size = 3;	selectInit();
	}
	else if (_ptMouse.x >= 175 && _ptMouse.x < 350
		&& _ptMouse.y >= 0 && _ptMouse.y < 175)
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
{// 처음 고르고나서 초기화(사이즈에 맞게 값부여)
	for (int i = 0; i < _size*_size; i++)
	{
		_isSelect = false;
		_location[i].ID = i; // 고유의 값 부여함 (_size*_size-1)이면 빈칸임
		_location[i].xx = i % _size;
		_location[i].yy = i / _size; // 계속 바뀜
	}
	mix(); // 섞는함수소환
}

int playGround::up() // 윗칸과 비교를 하여 빈칸이면 자리 바꿈
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
		_tryCount++;
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
		_tryCount++;
	}
}

int playGround::left() // 왼쪽과 비교
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
		_tryCount++;
	}
}

int playGround::right() // 오른쪽
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
		_tryCount++;
	}
}

void playGround::mix()
{
	srand(time(NULL)); // 안했더니 제대로 안됨.. RND만들때 있지 않았나?
	for (int i = 0; i < 100*_size*_size; i++) // 사이즈에 맞게 섞는다.(10x10은 100칸이라서 오지게 안섞임)
	{
		mixTry(); // 한번섞는 함수 소환
	}
	for (int i = 0; i < _size; i++) // 다 섞고나면 오른쪽 아래로 보내기
	{
		if (_location[_size*_size - 1].yy != _size-1) // 아래랑 자리바꿈(끝도달하면 X)
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
		if (_location[_size*_size - 1].xx != _size - 1) // 오른쪽이랑 자리바꿈(끝도달하면 X)
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

void playGround::mixTry() // 한번 섞는 함수
{
	_randNum = rand() % 4; // 상하좌우
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
