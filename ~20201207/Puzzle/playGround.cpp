#include "stdafx.h"
#include "playGround.h"

playGround::playGround()
{
}


playGround::~playGround()
{
}

//�ʱ�ȭ�� ����� �ϼ���
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

//�޸� ������ ����� �ϼ���
void playGround::release()
{
	gameNode::release();


}

//����(���)�� ����� �ϼ���
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
		{ // �ڸ��ٲٱ�
			up(); down(); left(); right(); // �����¿� ���ؼ� �̵��ϴ� �Լ���
			_changed = false;
		}
	}

}

//���� ����� �׷��� ��...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ ���� �ǵ��� ���� ==============================
	
	if (_isSelect)
	{
		_select->render(backDC, 0, 0);
	}
	else
	{

		for (int i = 0; i < _size*_size - 1; i++)
		{
			_background->render(backDC, _location[i].xx * 525 / _size, // ��� ��ġ�� �ٲ�
				_location[i].yy * 525 / _size,
				(_location[i].ID%_size) * 525 / _size, // ��������ϴ� ������ �Һ�
				(_location[i].ID/_size) * 525 / _size,
				525 / _size + 1, 525 / _size + 1); // +1�ؾ� ������ �ȳ���			
		}

		_thumbnail->render(backDC, 538, 30);
		sprintf_s(str, "%d X %d", _size, _size);
		TextOut(backDC, 620, 250, str, strlen(str));
		if (_size > 5)
		{
			sprintf_s(str, "�� �̷� ������..");
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
			sprintf_s(str, "�� ������ϴ�~!");
			TextOut(backDC, 600, 275, str, strlen(str));
		}

	}
	
	//================= �Ʒ��� �ǵ��� ���� ==============================
	this->getBackBuffer()->render(hdc, 0, 0);
}

int playGround::select() // �� ÷�� ���� �Լ�
{
	if (_ptMouse.x < 0 || _ptMouse.x>525 || _ptMouse.y < 0 || _ptMouse.y>525) return 0;
	if (_ptMouse.x >= 0 && _ptMouse.x < 175 && _ptMouse.y >= 0 && _ptMouse.y < 175)
	{ // 3x3����
		_size = 3;	selectInit();
	}
	else if (_ptMouse.x >= 175 && _ptMouse.x < 350
		&& _ptMouse.y >= 0 && _ptMouse.y < 175) // 175�� 525/3
	{ // 4x4����
		_size = 4;	selectInit();
	}
	else if (_ptMouse.x >= 350 && _ptMouse.x < 525
		&& _ptMouse.y >= 0 && _ptMouse.y < 175)
	{ // 5x5����
		_size = 5;	selectInit();
	}
	else if (_ptMouse.x >= 0 && _ptMouse.x < 175
		&& _ptMouse.y >= 175 && _ptMouse.y < 350)
	{ // 6x6����
		_size = 6;	selectInit();
	}
	else if (_ptMouse.x >= 175 && _ptMouse.x < 350
		&& _ptMouse.y >= 175 && _ptMouse.y < 350)
	{ // 7x7����
		_size = 7;	selectInit();
	}
	else if (_ptMouse.x >= 350 && _ptMouse.x < 525
		&& _ptMouse.y >= 175 && _ptMouse.y < 350)
	{ // 8x8����
		_size = 8;	selectInit();
	}
	else if (_ptMouse.x >= 0 && _ptMouse.x < 175
		&& _ptMouse.y >= 350 && _ptMouse.y < 525)
	{ // 9x9����
		_size = 9;	selectInit();
	}
	else if (_ptMouse.x >= 175 && _ptMouse.x < 350
		&& _ptMouse.y >= 350 && _ptMouse.y < 525)
	{ // 10x10����
		_size = 10;	selectInit();	
	}
	return 0;
}

void playGround::selectInit()
{
	for (int i = 0; i < _size*_size; i++)
	{
		_isSelect = false;
		_location[i].ID = i; // ������ �� �ο��� (_size*_size-1)�̸� ��ĭ��
		_location[i].xx = i % _size;
		_location[i].yy = i / _size; // ��� �ٲ�
	}
	mix();
}

int playGround::up() // ��ĭ�� �񱳸� �Ѵ�
{
	_xx = _ptMouse.x* _size / 525;
	_yy = _ptMouse.y* _size / 525;
	if (_yy == 0 || _changed) return 0;
	for (int i = 0; i < _size*_size; i++) // �ش���ġ ã�´�
	{
		if (_location[i].xx == _xx && _location[i].yy == _yy) _number = i;
		if (_location[i].xx == _xx && _location[i].yy == _yy-1) _compare = i; // ���Ұ�
	}
	if (_location[_compare].ID == _size*_size-1) // ��ĭ�̸�
	{
		_temp = _location[_number].yy;
		_location[_number].yy = _location[_compare].yy;
		_location[_compare].yy = _temp;
		_changed = true;
	}
}

int playGround::down() // �Ʒ�ĭ�� �񱳸� �Ѵ�
{
	_xx = _ptMouse.x* _size / 525;
	_yy = _ptMouse.y* _size / 525;
	if (_yy == _size-1 || _changed) return 0;
	for (int i = 0; i < _size*_size; i++) // �ش���ġ ã�´�
	{
		if (_location[i].xx == _xx && _location[i].yy == _yy) _number = i;
		if (_location[i].xx == _xx && _location[i].yy == _yy + 1) _compare = i;
	}
	if (_location[_compare].ID == _size * _size - 1) // ��ĭ�̸�
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
	for (int i = 0; i < _size*_size; i++) // �ش���ġ ã�´�
	{
		if (_location[i].xx == _xx && _location[i].yy == _yy) _number = i;
		if (_location[i].xx == _xx -1 && _location[i].yy == _yy) _compare = i;
	}
	if (_location[_compare].ID == _size * _size - 1) // ��ĭ�̸�
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
	for (int i = 0; i < _size*_size; i++) // �ش���ġ ã�´�
	{
		if (_location[i].xx == _xx && _location[i].yy == _yy) _number = i;
		if (_location[i].xx == _xx + 1 && _location[i].yy == _yy) _compare = i;
	}
	if (_location[_compare].ID == _size * _size - 1) // ��ĭ�̸�
	{
		_temp = _location[_number].xx;
		_location[_number].xx = _location[_compare].xx;
		_location[_compare].xx = _temp;
		_changed = true;
	}
}

void playGround::mix()
{
	srand(time(NULL)); // ���ߴ��� ����� �ȵ�
	for (int i = 0; i < 10000; i++) // 1000�� ���´�.(10x10�� 100ĭ�̶� ������ �ȼ���)
	{
		mixTry();
	}
	for (int i = 0; i < _size; i++) // ������ �Ʒ��� ������
	{
		if (_location[_size*_size - 1].yy != _size-1) // �Ʒ���
		{
			_location[_size*_size - 1].yy += 1;
			for (int i = 0; i < _size*_size - 1; i++) // �ش���ġ ã�´�
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
		if (_location[_size*_size - 1].xx != _size - 1) // �Ʒ���
		{
			_location[_size*_size - 1].xx += 1;
			for (int i = 0; i < _size*_size - 1; i++) // �ش���ġ ã�´�
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
	if (_randNum == 0 && _location[_size*_size-1].yy != 0) // ����
	{
		_location[_size*_size - 1].yy -= 1;
		for (int i = 0; i < _size*_size - 1; i++) // �ش���ġ ã�´�
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
	else if (_randNum == 1 && _location[_size*_size - 1].yy != _size-1) // �Ʒ���
	{
		_location[_size*_size - 1].yy += 1;
		for (int i = 0; i < _size*_size - 1; i++) // �ش���ġ ã�´�
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
	else if (_randNum == 2 && _location[_size*_size - 1].xx != 0) // ��������
	{
		_location[_size*_size - 1].xx -= 1;
		for (int i = 0; i < _size*_size - 1; i++) // �ش���ġ ã�´�
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
	else if (_randNum == 3 && _location[_size*_size - 1].xx != _size-1) // ����������
	{
		_location[_size*_size - 1].xx += 1;
		for (int i = 0; i < _size*_size - 1; i++) // �ش���ġ ã�´�
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
