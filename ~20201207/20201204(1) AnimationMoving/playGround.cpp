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

	_background = IMAGEMANAGER->addImage("���", "image/background.bmp", 922, 630, false, RGB(255, 0, 255));
	_sonicImg = IMAGEMANAGER->addFrameImage("�Ҵ�", "image/sonic.bmp", 1100, 1000, 11, 10, true, RGB(255, 0, 255));
	// X �ε��� �� 0~10 Y�� 0~9

	_isGapEum = _onGround = _isHang = false; // �������
	_sonicRc = RectMake(50, 300, SONICWIDTH, SONICHEIGHT); // �Ҵ�
	
	_object[0] = { 211, 357, 584, 630 }; // ���־�â
	_object[1] = { 672, 278, 922, 630 }; // �Ӽ�â

	_object[2] = { 0, 129, 180, 160 }; // ���� ��
	_object[3] = { 827, 129, 922, 161 }; // ������ ��
	_object[4] = { 319, 60, 581, 90 }; // ��� ��

	_object[5] = { 0, 590, 922, 630 }; // �ؿ� ��

	for (int i = 0; i < 6; i++)
	{
		_objectIsNotCollide[i] = false;
	}

	_sonicImg->setFrameY(0);

	_count = _index = 0;

	_direction = RIGHT_JUMP;

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

	rectMove(); 	keyInput(); 	collision(); 	objectRegen(); // �����Լ�

	// �������̳� �Ŵ޸����°� �ƴϸ� ����üũ
	if (_direction != LEFT_JUMP && _direction != RIGHT_JUMP 
		&& _direction != LEFT_HANG && _direction != RIGHT_HANG) jumpingCheck();

	// �Ŵ޸����¸� �Ŵ޷ȴ��� üũ
	if (_direction == LEFT_HANG || _direction == RIGHT_HANG) hangingCheck();

	if (_count % 10 == 0)
	{
		animation();
		if (_count >= 100) _count = 0;	
	}


	_count++;

	if (_attackReturn < 30) _attackReturn++; // 30�ɶ����� ��������
	else // 30�� �Ǿ����� �������̸� ��������
	{
		if (_direction == RIGHT_ATTACK)
		{
			_direction = RIGHT_IDLE;			_index = 0;
			// �ڸ� �ٲܶ����� �ε����� �ο�����(�̺� ������..)
		}
		else if (_direction == LEFT_ATTACK)
		{
			_direction = LEFT_IDLE;			_index = 10;
		}
	}
}

//���� ����� �׷��� ��...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ ���� �ǵ��� ���� ==============================
	
	_background->render(backDC); // ���
	_sonicImg->frameRender(backDC, _sonicRc.left - 16, _sonicRc.top -10); // �Ҵ�

	if (KEYMANAGER->isToggleKey(VK_TAB)) // �Ǵ����� �簢������ ���̴°�
	{		
		for (int i = 0; i < 6; i++)
		{
			Rectangle(backDC, _object[i]);			
		}
		Rectangle(backDC, _sonicRc);
	}

	switch (_direction) // ���� ǥ��
	{
	case LEFT_RUN:		sprintf_s(str, "LEFT  _RUN");				break;
	case RIGHT_RUN:		sprintf_s(str, "RIGHT_RUN");				break;
	case LEFT_HANG:		if (_isGapEum)	sprintf_s(str, "LEFT  _HANG (������ ������)");
						else sprintf_s(str, "LEFT  _HANG (�̲���)");	break;
	case RIGHT_HANG:	if (_isGapEum)sprintf_s(str, "RIGHT_HANG (������ ������)");
						else sprintf_s(str, "RIGHT_HANG (�̲���)");	break;
	case LEFT_IDLE:		sprintf_s(str, "LEFT  _IDLE");				break;
	case RIGHT_IDLE:	sprintf_s(str, "RIGHT_IDLE");				break;
	case LEFT_ATTACK:	sprintf_s(str, "LEFT  _ATTACK");			break;
	case RIGHT_ATTACK:	sprintf_s(str, "RIGHT_ATTACK");				break;
	case LEFT_JUMP:		sprintf_s(str, "LEFT  _JUMP");				break;
	case RIGHT_JUMP:	sprintf_s(str, "RIGHT_JUMP");				break;
	}
	TextOut(backDC, 87, 603, str, strlen(str));


	
	//================= �Ʒ��� �ǵ��� ���� ==============================
	this->getBackBuffer()->render(hdc, 0, 0);
}

void playGround::rectMove() // ��Ʈ�� �߷¹ް� �������°�
{
	if (_direction == LEFT_JUMP || _direction == RIGHT_JUMP)
	{
		_sonicRc.top -= _jumpPower;
		_sonicRc.bottom = _sonicRc.top + SONICHEIGHT;
		_jumpPower -= 0.25f;
	}
	else if (_direction == LEFT_HANG || _direction == RIGHT_HANG)
	{ // ������ ��������� �ȳ������� �Ŵ޷����� õõ�� ����
		_sonicRc.top -= _jumpPower;
		_sonicRc.bottom = _sonicRc.top + SONICHEIGHT;
		if (!_isGapEum) _jumpPower -= 0.05f;
	}
}

void playGround::keyInput() // Ű�Է� ����
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _sonicRc.left > 0)
	{ // ȭ�� �ȿ��� ���ʴ��� ����
		_sonicRc.left -= 5; // �̵���Ű��
		_sonicRc.right = _sonicRc.left + SONICWIDTH;
		if (_direction == LEFT_IDLE || _direction == RIGHT_IDLE ||
			_direction == RIGHT_ATTACK || _direction == RIGHT_RUN)
		{ // �� �װ��� ���� �޸���� �ٲ���
			_direction = LEFT_RUN;			_index = 5;
		}
		else if (_direction == RIGHT_JUMP || _direction == RIGHT_HANG)
		{ // �� �ΰ��� ���� ������ �ٲ��� (���� ��Ҵ����� ������ �ɶ� �ʱ�ȭ��Ŵ. ��°� �����϶��ϱ�)
			_direction = LEFT_JUMP;			_index = 4;
			_isGapEum = false;
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{ // ����Ű�� �� ����
		if (_direction == LEFT_RUN)
		{ // �޸��� �־����� �������� �ٲ���
			_direction = LEFT_IDLE;			_index = 10;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _sonicRc.right < WINSIZEX
		&& !KEYMANAGER->isStayKeyDown(VK_LEFT))
	{ // ȭ�� �ȿ��� �����ʴ��� ����(���� �������¸� ����)
		_sonicRc.left += 5;
		_sonicRc.right = _sonicRc.left + SONICWIDTH;
		if (_direction == RIGHT_IDLE || _direction == LEFT_IDLE ||
			_direction == LEFT_ATTACK || _direction == LEFT_RUN)
		{ // �� �װ��� ������ �޸���� �ٲ���
			_direction = RIGHT_RUN;
			_index = 5;
		}
		else if (_direction == LEFT_JUMP || _direction == LEFT_HANG)
		{ // �� �ΰ��� ������ ������ �ٲ��� (���� ��Ҵ����� ������ �ɶ� �ʱ�ȭ��Ŵ. ��°� �����϶��ϱ�)
			_direction = RIGHT_JUMP;
			_isGapEum = false;
			_index = 3;
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{  // ������Ű�� �� ����
		if (_direction == RIGHT_RUN)
		{ // �޸��� �־����� �������� �ٲ���
			_direction = RIGHT_IDLE;
			_index = 0;
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_SPACE) && _direction != RIGHT_JUMP && _direction != LEFT_JUMP
		&& !KEYMANAGER->isStayKeyDown(VK_DOWN))
	{ // �������� : �����̽� ������ �������� �ƴҶ� �Ʒ���ư�� ������ ���� ����(�Ʒ��������������� ���� �۵�)
		switch (_direction)
		{
		case RIGHT_IDLE:		case RIGHT_RUN:		case RIGHT_ATTACK:		case RIGHT_HANG:
			_direction = RIGHT_JUMP; // ���� �װ��� ������������
			_index = 0;
			_isGapEum = false;
			break;
		case LEFT_IDLE:		case LEFT_RUN:		case LEFT_ATTACK:		case LEFT_HANG:
			_direction = LEFT_JUMP; // ���� �װ��� ����������
			_index = 7;
			_isGapEum = false;
			break;
		}
		_jumpPower = 8;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && KEYMANAGER->isStayKeyDown(VK_DOWN))
	{ // ������
		for (int i = 2; i < 5; i++) // 234�� ���� Ȯ��
		{
			if (_sonicRc.bottom + 1 > _object[i].top && _sonicRc.right > _object[i].left &&
				_sonicRc.left < _object[i].right && _sonicRc.top < _object[i].bottom)
			{
				_objectIsNotCollide[i] = true; // ��������
				switch (_direction)
				{
				case LEFT_IDLE:				case LEFT_RUN:				case LEFT_ATTACK:
					_jumpPower = 0; // �� ������ ����������
					_direction = LEFT_JUMP;
					_isGapEum = false;
					_index = 5;
					break;
				case RIGHT_IDLE:				case RIGHT_RUN: 				case RIGHT_ATTACK:
					_jumpPower = 0; // �� ������ ������������
					_direction = RIGHT_JUMP;
					_isGapEum = false;
					_index = 3;
					break;
				}
				break;
			}
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && (_direction == LEFT_IDLE || _direction == RIGHT_IDLE)
		&& _attackReturn >=30) // �������� : ���ʹ����� ������ �ִ� �����̸� �𵹾�����
	{
		switch (_direction)
		{
		case LEFT_IDLE: _direction = LEFT_ATTACK; // ���� ��������
			_index = 2;
			_attackReturn = 0;
			break;
		case RIGHT_IDLE: _direction = RIGHT_ATTACK; // ������ ��������
			_index = 0;
			_attackReturn = 0;
			break;
		}
	}
}

void playGround::animation()
{ // �ִϸ��̼� �ܶ� ��Ƴ�����
	switch (_direction)
	{
	case LEFT_IDLE:
		if (_index < 0 || _index>10) _index = 10;
		_sonicImg->setFrameY(5);
		_sonicImg->setFrameX(_index);
		if (_index == 10 && _count % 100 != 0) break; // 10������ ���ð��� �� ����Ϸ���
		_index--; // 10->9->8->...->0 ���� ��ȯ
		break;
	case RIGHT_IDLE:
		if (_index < 0 || _index>10) _index = 0;
		_sonicImg->setFrameY(4);
		_sonicImg->setFrameX(_index);
		if (_index == 0 && _count % 100 != 0) break;
		_index++; // 0->1->2->...->10 ���� ��ȯ
		break;

	case LEFT_RUN:
		if (_index < 0 || _index > 5) _index = 5;
		_sonicImg->setFrameY(1);
		_sonicImg->setFrameX(_index);
		_index--;
		break;
	case RIGHT_RUN:
		if (_index < 0 || _index > 5) _index = 0;
		_sonicImg->setFrameY(0);
		_sonicImg->setFrameX(_index);
		_index++;
		break;
	case LEFT_HANG:
		if (_index < 0 || _index > 3) _index = 3;
		_sonicImg->setFrameY(3);
		_sonicImg->setFrameX(_index);
		_index--;
		break;
	case RIGHT_HANG:
		if (_index < 0 || _index > 3) _index = 0;
		_sonicImg->setFrameY(2);
		_sonicImg->setFrameX(_index);
		_index++;
		break;
	case LEFT_ATTACK:
		if (_index < 0 || _index > 2) _index = 2;
		_sonicImg->setFrameY(7);
		_sonicImg->setFrameX(_index);
		_index--;
		break;
	case RIGHT_ATTACK:
		if (_index < 0 || _index > 2) _index = 0;
		_sonicImg->setFrameY(6);
		_sonicImg->setFrameX(_index);
		_index++;
		break;
	case LEFT_JUMP:
		if (_index < 0 || _index > 7) _index = 7;
		if (_index == 2) _index = 4; // ���� ��� ��Ű����.. 4->3->2 ��ȯ
		_sonicImg->setFrameY(9);
		_sonicImg->setFrameX(_index);
		_index--;
		break;
	case RIGHT_JUMP:
		if (_index < 0 || _index > 7) _index = 0;
		if (_index == 5) _index = 3; // ���� ��� ��Ű����.. 3->4->5 ��ȯ
		_sonicImg->setFrameY(8);
		_sonicImg->setFrameX(_index);
		_index++;
		break;
	}
}

void playGround::collision()
{ // ���ͼ�Ʈ��Ʈ
	for (int i = 0; i < 6; i++)
	{
		if (IntersectRect(&_temp, &_sonicRc, &_object[i]) && _objectIsNotCollide[i] == false)
		{
			if (_temp.right - _temp.left > _temp.bottom - _temp.top &&
				_object[i].top < _temp.bottom && _object[i].bottom > _temp.bottom && _jumpPower<0) // �����ߴ�
			{ // ������ ���� ���̺��� ũ��, ������ �Ʒ��� ������Ʈ ž���һ��̿� ������ �������� 0���� ������(�Ʒ��ΰ���������)
				_sonicRc.bottom = _object[i].top; // �о��ְ�
				_sonicRc.top = _sonicRc.bottom - SONICHEIGHT;
				switch (_direction) // ���̵�� �ٲ���
				{
				case LEFT_JUMP:					case LEFT_HANG:
					_direction = LEFT_IDLE;
					_index = 10;
					break;
				case RIGHT_JUMP:				case RIGHT_HANG:
					_direction = RIGHT_IDLE;
					_index = 0;
					break;
				}
			}
			else if (_temp.right - _temp.left > _temp.bottom - _temp.top &&
				_object[i].top < _temp.top && _object[i].bottom > _temp.top) // �Ʒ��� �ھҴ�
			{
				if (_jumpPower >0) _jumpPower = 0; // �����Ŀ��� 0�̻��̸� ���ֹ���
			}
			else if (_temp.right - _temp.left <= _temp.bottom - _temp.top &&
				_object[i].left < _temp.right && _object[i].right > _temp.right)
			{ // ���ʺ��� ����
				_sonicRc.right = _object[i].left;
				_sonicRc.left = _sonicRc.right - SONICWIDTH;
				if (_direction == RIGHT_JUMP && _jumpPower <0 &&
					(_sonicRc.top + _sonicRc.bottom) / 2 < _object[i].bottom &&// �Ҵ��� ������ ������Ʈ �ٴں��� �����־�� ����
					(_sonicRc.top + _sonicRc.bottom) / 2 > _object[i].top) // �Ҵ��� ������ ������Ʈ ž���� �Ʒ��־�� ����					
				{// ����� (�ƴϸ� �׳� �ε�����)
					if (_temp.bottom - _temp.top < 80) _isGapEum = true;
					// temp�� �浹������ ���ٸ� ������ ��Ƽ� �������� ����
					_direction = RIGHT_HANG;
					_jumpPower = 0;
					_index = 0;
				}
			}
			else if (_temp.right - _temp.left <= _temp.bottom - _temp.top &&
				_object[i].left < _temp.left && _object[i].right > _temp.left)
			{ // �����ʺ��� ����
				_sonicRc.left = _object[i].right;
				_sonicRc.right = _sonicRc.left + SONICWIDTH;
				if (_direction == LEFT_JUMP && _jumpPower < 0 && 
					(_sonicRc.top+_sonicRc.bottom) /2 < _object[i].bottom && // �Ҵ��� ������ ������Ʈ �ٴں��� �����־�� ����
					(_sonicRc.top + _sonicRc.bottom) / 2 > _object[i].top) // �Ҵ��� ������ ������Ʈ ž���� �Ʒ��־�� ����
				{// ����� (�ƴϸ� �׳� �ε�����)
					if (_temp.bottom - _temp.top < 80) _isGapEum = true;
					_direction = LEFT_HANG;
					_jumpPower = 0;
					_index = 3;
				}
			}
		}
	}
}

// �ٴ��� �������� üũ�մϴ�.
void playGround::jumpingCheck()
{
	_onGround = false; // �޽��� �ʱ�ȭ
	for (int i = 0; i < 6; i++)
	{
		if (_sonicRc.bottom + 1 > _object[i].top && _sonicRc.right > _object[i].left &&
			_sonicRc.left < _object[i].right && _sonicRc.top < _object[i].bottom)
		{ // �� ������Ʈ���� ���� ���ִ��� �Ǵ�(�Ҵй��� +1�� ������ �簢������ ����)
			_onGround = true; // ã���� true�� �ٲٰ� �극��ũ
			break;
		}
	}
	if (!_onGround)
	{ // ���� ���ִ� ����(������ �ٲ���)
		switch (_direction)
		{
		case LEFT_RUN: // IDLE�̸� �ۿ� ������ �����ϱ� ����..
		case LEFT_ATTACK:
			_jumpPower = 0;
			_direction = LEFT_JUMP;
			_isGapEum = false;
			_index = 5;
			break;
		case RIGHT_RUN: // IDLE�̸� �ۿ� ������ �����ϱ� ����..
		case RIGHT_ATTACK:
			_jumpPower = 0;
			_direction = RIGHT_JUMP;
			_isGapEum = false;
			_index = 3;
			break;
		}
	}
}

// �Ŵ޷��ִ��� üũ�մϴ�.
void playGround::hangingCheck()
{
	_isHang = false;
	for (int i = 0; i < 6; i++)
	{
		if (_sonicRc.bottom > _object[i].top && _sonicRc.right > _object[i].left &&
			_sonicRc.left-1 < _object[i].right && _sonicRc.top < _object[i].bottom)
		{ // �� ������Ʈ���� ���� �پ� �ִ��� �Ǵ�(�Ҵз���Ʈ -1�� ������ �簢������ ����)
			_isHang = true;
			break;
		}
		else if (_sonicRc.bottom > _object[i].top && _sonicRc.right+1 > _object[i].left &&
			_sonicRc.left < _object[i].right && _sonicRc.top < _object[i].bottom)
		{ // �� ������Ʈ���� ���� �پ� �ִ��� �Ǵ�(�Ҵж���Ʈ +1�� ������ �簢������ ����)
			_isHang = true;
			break;
		}
	}
	if (!_isHang)
	{ // ���� �Ⱥ�������(������ �ٲ���)
		switch (_direction)
		{
		case LEFT_HANG:
			_direction = LEFT_JUMP;
			_isGapEum = false;
			_index = 5;
			break;
		case RIGHT_HANG:
			_direction = RIGHT_JUMP;
			_isGapEum = false;

			_index = 3;
			break;
		}
	}
}

//���� �Ÿ� ������ ������Ʈ�� �ٽ� �浹����
void playGround::objectRegen()
{
	/*if (!IntersectRect(&_temp,&_object[0],&_sonicRc)) _objectIsNotCollide[0] = false;
	if (!IntersectRect(&_temp, &_object[1], &_sonicRc)) _objectIsNotCollide[1] = false;*/
	if (_sonicRc.top > 160) _objectIsNotCollide[2] = false;// ���� ��
	if (_sonicRc.top > 161)	_objectIsNotCollide[3] = false; // ������ ��
	if (_sonicRc.top > 90)	_objectIsNotCollide[4] = false;// �����
}