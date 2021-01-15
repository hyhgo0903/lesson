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
{ // ���� ����
	gameNode::init();

	_p1mode = NORMAL;	_p2mode = NORMAL; // ���

	_player1 = RectMakeCenter(WINSIZEX / 2 - 400, WINSIZEY / 2, 100, 50); // �÷��̾� �簢��
	_player2 = RectMakeCenter(WINSIZEX / 2 + 400, WINSIZEY / 2, 100, 50);
	
	_obstacle = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 20, 100); //�߰� ��ֹ�

	for (int i = 0; i < BULLETMAX; i++)
	{ // �Ѿ� ����(�⺻��)
		_bulletP1[i].isFire = false;		_bulletP2[i].isFire = false;
		_bulletP1[i].isYudo = false;		_bulletP2[i].isYudo = false;
		_bulletP1[i].betrayed = false;		_bulletP2[i].betrayed = false;
		_bulletP1[i].x = 10; _bulletP2[i].x = -10; // �� �ο������� �ȵֵ� �ɰŰ��� �ѵ� �ϴ�..
		_bulletP1[i].y = 0; _bulletP2[i].y = 0;
	}

	_backGauge = RectMakeCenter(WINSIZEX / 2 - 300, 70, 400, 50); // ������
	_frontGauge = RectMakeCenter(WINSIZEX / 2 - 300, 70, 400, 50);
	_backGauge2 = RectMakeCenter(WINSIZEX / 2 + 300, 70, 400, 50);
	_frontGauge2 = RectMakeCenter(WINSIZEX / 2 + 300, 70, 400, 50);

	_r = 0;	_g = 255; // �ʱ� ����
	_r2 = 0;	_g2 = 255;

	_direction = 1; // ��ֹ� ���� (+1/-1)

	_reloadCount1 = _reloadCount2 = 0; // ����ī��Ʈ
	
	_isDeadP1 = _isDeadP2 = _canUltiP1 = _canUltiP2 = _effectOn = false;
	// �׾������� �ý�� �ִ���(�̰� ����Ƕ� Ȱ��ȭ��) ����Ʈ��������

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


	_reloadCount1++; _reloadCount2++; // ������ī��Ʈ

	//����ź ���� ������ �簢��(����) p1�̳� p2�� �پ �ʺ� ���� 300��ŭ ����
	_bigRect1 = RectMakeCenter((_player1.left + _player1.right) / 2, (_player1.top + _player1.bottom) / 2, 300, 300);
	_bigRect2 = RectMakeCenter((_player2.left + _player2.right) / 2, (_player2.top + _player2.bottom) / 2, 300, 300);

	if (!_isDeadP1 && !_isDeadP2) // �Ѵ� ���������
	{
		if (_ultiCount1 < 300) _ultiCount1++;
		if (_ultiCount2 < 300) _ultiCount2++;
		//����
		if (_obstacle.top <= 0) _direction *= -1; // õ��ġ�� ������ȯ
		if (_obstacle.bottom >= WINSIZEY) _direction *= -1; // �ٴ�ġ�� ������ȯ
		OffsetRect(&_obstacle, 0, 5 * _direction); // ��ֹ� �̵�

		keyControl();

		bulletMove();

		collision();		collision2();

		collisionObstacle();

		Yudo();		Yudo2();
		// �����Լ� ����(�ؿ�)
		
		if (_frontGauge.right - _frontGauge.left < 250) { _canUltiP1 = true; }
		if (_frontGauge2.right - _frontGauge2.left < 250) { _canUltiP2 = true; }
		// �þ��� �ִ���
		if (_frontGauge.right <= _frontGauge.left)	_isDeadP1 = true;
		if (_frontGauge2.right <= _frontGauge2.left)	_isDeadP2 = true;
		// �� �� ������ ����
	}
	if (_isDeadP1 && !_effectOn)
	{
		_effectOn = true;
		_reloadCount1 = 0; // ��Ȱ��.. ������ �׾����ϱ�
		for (int i = 0; i < 8; i++)
		{
			_effect[i] = RectMakeCenter((_player1.left + _player1.right) / 2,
				(_player1.top + _player1.bottom) / 2, 15, 15);
		}
	}
	if (_isDeadP2 && !_effectOn)
	{
		_effectOn = true;
		_reloadCount1 = 0;
		for (int i = 0; i < 8; i++)
		{
			_effect[i] = RectMakeCenter((_player2.left + _player2.right) / 2,
				(_player2.top + _player2.bottom) / 2, 15, 15);
		}
	}
	if ((_isDeadP1 || _isDeadP2) && _reloadCount1 <100)
	{
		OffsetRect(&_effect[0], 7, 0);
		OffsetRect(&_effect[1], 0, 7);
		OffsetRect(&_effect[2], -7, 0);
		OffsetRect(&_effect[3], 0, -7);
		OffsetRect(&_effect[4], 5, -5);
		OffsetRect(&_effect[5], -5, -5);
		OffsetRect(&_effect[6], -5, 5);
		OffsetRect(&_effect[7], 5, 5);
		_reloadCount1++;
	}

	if ((_isDeadP1 || _isDeadP2) && KEYMANAGER->isOnceKeyDown('R')) this->init();
		// �׾����� R�� �����

}

//���� ����� �׷��� ��...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ ���� �ǵ��� ���� ==============================
	   	
	// ��
	Rectangle(backDC, 20, 110, WINSIZEX / 2 - 50, WINSIZEY - 20);
	Rectangle(backDC, WINSIZEX / 2 + 50, 110, WINSIZEX - 20, WINSIZEY - 20);

	// ��ֹ�
	Rectangle(backDC, _obstacle);

	if (!_isDeadP1)
	{
		if (_p1mode == NORMAL ||
			(_p1mode != NORMAL && _reloadCount1 > 30))
		{ // p1����ִ� ���¿��� ���(£��)
			HBRUSH brush = CreateSolidBrush(RGB(110, 110, 190));
			Rectangle(backDC, _player1);
			FillRect(backDC, &_player1, brush);
			DeleteObject(brush);
		}
		else
		{ // p1������� ���¿��� ���(����)
			HBRUSH brush = CreateSolidBrush(RGB(210, 210, 255));
			Rectangle(backDC, _player1);
			FillRect(backDC, &_player1, brush);
			DeleteObject(brush);
		}
	}
	if (!_isDeadP2)
	{
		if (_p2mode == NORMAL ||
			(_p2mode != NORMAL && _reloadCount2 > 30))
		{ // p2����ִ� ���¿��� ���(£��)
			HBRUSH brush = CreateSolidBrush(RGB(190, 110, 110));
			Rectangle(backDC, _player2);
			FillRect(backDC, &_player2, brush);
			DeleteObject(brush);
		}
		else
		{ // p2������� ���¿��� ���(����)
			HBRUSH brush = CreateSolidBrush(RGB(255, 210, 210));
			Rectangle(backDC, _player2);
			FillRect(backDC, &_player2, brush);
			DeleteObject(brush);
		}
	}
		
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (!_bulletP1[i].isFire) continue; // isFire�� false�� ���X
		if (_bulletP1[i].isYudo) 
		{// ����ź�̸� �Ķ����簢�� (��ĥ�� �簢���� �� �� �˾Ƽ� �簢��)
			HBRUSH brush = CreateSolidBrush(RGB(0, 0, 255));
			Ellipse(backDC, _bulletP1[i].rc);
			FillRect(backDC, &_bulletP1[i].rc, brush);
			DeleteObject(brush);
		}
		else Ellipse(backDC, _bulletP1[i].rc);	 // �ƴϸ� �׳� ��
	}
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (!_bulletP2[i].isFire) continue;
		if (_bulletP2[i].isYudo)
		{
			HBRUSH brush = CreateSolidBrush(RGB(0, 0, 255));
			Ellipse(backDC, _bulletP2[i].rc);
			FillRect(backDC, &_bulletP2[i].rc, brush);
			DeleteObject(brush);
		}
		else Ellipse(backDC, _bulletP2[i].rc);
	}

	Rectangle(backDC, _backGauge); // ü�¹ٵ�ĭ
	Rectangle(backDC, _backGauge2);

	HBRUSH brush = CreateSolidBrush(RGB(_r2, _g2, 0));
	Rectangle(backDC, _frontGauge2);
	FillRect(backDC, &_frontGauge2, brush);
	DeleteObject(brush); // ü�¹پ�ĭ(���� ���� ���)
	
	brush = CreateSolidBrush(RGB(_r, _g, 0));
	Rectangle(backDC, _frontGauge);
	FillRect(backDC, &_frontGauge, brush);
	DeleteObject(brush);

	char str[256]; // ����ġ��Ŀ

	sprintf_s(str, "�� ���� : ��� �Ѿ���");
	TextOut(backDC, WINSIZEX/2 - 70 , 30, str, strlen(str));
	sprintf_s(str, "��븦 ���մϴ�.");
	TextOut(backDC, WINSIZEX / 2 - 40, 50, str, strlen(str));

	sprintf_s(str, "�����̽�: �߻� /WASD�̵� /  Q:�����ȯ / E:��(���������)");
	TextOut(backDC, 20, WINSIZEY - 20, str, strlen(str));
	sprintf_s(str, "����: �߻� / (NumPad) 8456�̵� / 7:�����ȯ / 9:��(���������)");
	TextOut(backDC, 590, WINSIZEY - 20, str, strlen(str));
	

	if (_canUltiP1)
	{ // ��üũ
		sprintf_s(str, "���� (0 �̸� �ÿ�) : %d", (300 - _ultiCount1)/10);
		TextOut(backDC, 20, 20, str, strlen(str));
	}
	if (_canUltiP2)
	{
		sprintf_s(str, "���� (0 �̸� �ÿ�): %d", (300 - _ultiCount2)/10);
		TextOut(backDC, WINSIZEX - 200, 20, str, strlen(str));
	}
	

	switch (_p1mode)
	{ // ��庰�� �۾����
	case NORMAL: sprintf_s(str, "�ܹ� ���"); break;
	case MULTI: sprintf_s(str, "��Ƽ�� ���"); break;
	case YUDO: sprintf_s(str, "����ź ���"); break;
	}
	TextOut(backDC, 320, 20, str, strlen(str));

	switch (_p2mode)
	{
	case NORMAL: sprintf_s(str, "�ܹ� ���"); break;
	case MULTI: sprintf_s(str, "��Ƽ�� ���"); break;
	case YUDO: sprintf_s(str, "����ź ���"); break;
	}
	TextOut(backDC, WINSIZEX - 400, 20, str, strlen(str));

	if (_isDeadP1)
	{
		for (int i = 0; i < 8; i++)
		{
			HBRUSH brush = CreateSolidBrush(RGB(110, 110, 190));
			Rectangle(backDC, _effect[i]);
			FillRect(backDC, &_effect[i], brush);
			DeleteObject(brush);
		}
	}
	if (_isDeadP2)
	{
		for (int i = 0; i < 8; i++)
		{
			HBRUSH brush = CreateSolidBrush(RGB(190, 110, 110));
			Rectangle(backDC, _effect[i]);
			FillRect(backDC, &_effect[i], brush);
			DeleteObject(brush);
		}
	}
	if (_isDeadP1)
	{ // �׾����� ���
		sprintf_s(str, "PLAYER2 WINS!");
		TextOut(backDC, WINSIZEX / 2 - 55, WINSIZEY / 2, str, strlen(str));
		sprintf_s(str, "������Ϸ��� 'R'Ű�� ��������");
		TextOut(backDC, WINSIZEX / 2 - 110, WINSIZEY / 2 + 20, str, strlen(str));
	}
	if (_isDeadP2)
	{
		sprintf_s(str, "PLAYER1 WINS!");
		TextOut(backDC, WINSIZEX / 2 - 55, WINSIZEY / 2, str, strlen(str));
		sprintf_s(str, "������Ϸ��� 'R'Ű�� ��������");
		TextOut(backDC, WINSIZEX / 2 - 110, WINSIZEY / 2 + 20, str, strlen(str));
	}



	//================= �Ʒ��� �ǵ��� ���� ==============================
	this->getBackBuffer()->render(hdc, 0, 0);
}

void playGround::keyControl() // Ű ��Ʈ��
{// �̵�Ű <- ��� ���� �ʾ������� �۵�
	if (KEYMANAGER->isStayKeyDown('W') && _player1.top >110 )
	{	_player1.top -= 5;		_player1.bottom -= 5;	}
	if (KEYMANAGER->isStayKeyDown('S') && _player1.bottom < WINSIZEY-20)
	{	_player1.top += 5;		_player1.bottom += 5;	}
	if (KEYMANAGER->isStayKeyDown('A') && _player1.left > 20)
	{	_player1.left -= 5;		_player1.right -= 5;	}
	if (KEYMANAGER->isStayKeyDown('D') && _player1.right < WINSIZEX/2-50)
	{	_player1.left += 5;		_player1.right += 5;	}
	
	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD8) && _player2.top > 110)
	{ _player2.top -= 5;		_player2.bottom -= 5; }
	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD5) && _player2.bottom < WINSIZEY - 20)
	{ _player2.top += 5;	_player2.bottom += 5; }
	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD4) && _player2.left > WINSIZEX/2+50)
	{ _player2.left -= 5;		_player2.right -= 5; }
	if (KEYMANAGER->isStayKeyDown(VK_NUMPAD6) && _player2.right < WINSIZEX - 20)
	{ _player2.left += 5;		_player2.right += 5; }

	// �����ȯ (����ġ��)
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		switch (_p1mode)
		{
		case NORMAL: _p1mode = MULTI;		break;
		case MULTI: _p1mode = YUDO;			break;
		case YUDO: _p1mode = NORMAL;		break;
		}
	}
	
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD7))
	{
		switch (_p2mode)
		{
		case NORMAL: _p2mode = MULTI;		break;
		case MULTI: _p2mode = YUDO;			break;
		case YUDO: _p2mode = NORMAL;		break;
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) bulletFireP1(); // ���
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN)) bulletFireP2();


	if (KEYMANAGER->isOnceKeyDown('E') && _ultiCount1 >= 300 && _canUltiP1) ultiP1(); // �ý��
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD9) && _ultiCount2 >= 300 && _canUltiP2) ultiP2();

}

void playGround::bulletFireP1() // player1�� �Ѿ� ������
{
	switch (_p1mode) // ����ġ������ ����
	{
	case NORMAL:
	{ // ����ҋ�
		for (int i = 0; i < BULLETMAX; i++)
		{
			if (_bulletP1[i].isFire) continue; // �߻����� �Ѿ��� �̿�X
			_bulletP1[i].rc = RectMakeCenter(_player1.right + 5,
				(_player1.top + _player1.bottom) / 2, 10, 10); // �Ѿ� �����
			_bulletP1[i].isFire = true; // �߻���
			_bulletP1[i].x = 10; // x�ӵ� �Ҵ�
			_bulletP1[i].y = 0; // y�ӵ� �Ҵ�
			_bulletP1[i].isYudo = false; // ����ź�ƴ�
			_bulletP1[i].betrayed = false; // ���ø���ź(��Ŵ��� ź) �ƴ�
			break;
		}
	}
	break;
	case MULTI:
	{
		if (_reloadCount1 <= 30) break; // ������ ���ϸ� �۵�����
		else _reloadCount1 = 0; // ��� ����
		for (int j = 0; j < 5; j++)
		{ // 5�߾�
			for (int i = 0; i < BULLETMAX; i++)
			{
				if (_bulletP1[i].isFire) continue; // �߻����� �Ѿ��� �̿�X
				_bulletP1[i].rc = RectMakeCenter(_player1.right + 5,
					(_player1.top + _player1.bottom) / 2, 10, 10); // �Ѿ� �����
				_bulletP1[i].isFire = true; // �߻���
				if (j == 0 || j == 4) _bulletP1[i].x = 6;
				else if (j == 1 || j == 3) _bulletP1[i].x = 8;
				else _bulletP1[i].x = 10;  // x�ӵ� �Ҵ�(j�� ����)
				_bulletP1[i].y = 10 - j * 5; // y�ӵ� �Ҵ�(j�� ����)
				_bulletP1[i].isYudo = false; // ����ź�ƴ�
				_bulletP1[i].betrayed = false; // ���ø���ź(��Ŵ��� ź) �ƴ�
				break;
			}
		}
	}
	break;
	case YUDO:
	{
		if (_reloadCount1 <= 30) break;
		else _reloadCount1 = 0;
		for (int i = 0; i < BULLETMAX; i++)
		{
			if (_bulletP1[i].isFire) continue; // �߻����� �Ѿ��� �̿�X
			_bulletP1[i].rc = RectMakeCenter(_player1.right + 5,
				(_player1.top + _player1.bottom) / 2, 10, 10); // �Ѿ� �����
			_bulletP1[i].isFire = true; // �߻���
			_bulletP1[i].x = 10;  // x�ӵ� �Ҵ�
			_bulletP1[i].y = 0; // y�ӵ� �Ҵ�
			_bulletP1[i].isYudo = true; // ����ź��
			_bulletP1[i].betrayed = false; // ���ø���ź(��Ŵ��� ź) �ƴ�
			break;
		}
	}
	break;
	}
}

void playGround::bulletFireP2() // player2�� �Ѿ� ������ (�ּ��� �� ����)
{
	switch (_p2mode)
	{
	case NORMAL:
	{
		for (int i = 0; i < BULLETMAX; i++)
		{
			if (_bulletP2[i].isFire) continue;
			_bulletP2[i].rc = RectMakeCenter(_player2.left - 5,
				(_player2.top + _player2.bottom) / 2, 10, 10);
			_bulletP2[i].isFire = true;
			_bulletP2[i].x = -10;
			_bulletP2[i].y = 0;
			_bulletP2[i].isYudo = false;
			_bulletP2[i].betrayed = false;
			break;
		}
	}
	break;
	case MULTI:
	{
		if (_reloadCount2 <= 30) break;
		else _reloadCount2 = 0;
		for (int j = 0; j < 5; j++)
		{
			for (int i = 0; i < BULLETMAX; i++)
			{
				if (_bulletP2[i].isFire) continue;
				_bulletP2[i].isYudo = false;
				_bulletP2[i].betrayed = false;
				_bulletP2[i].rc = RectMakeCenter(_player2.left - 5,
					(_player2.top + _player2.bottom) / 2, 10, 10);
				_bulletP2[i].isFire = true;
				if (j == 0 || j == 4) _bulletP2[i].x = -6;
				else if (j == 1 || j == 3) _bulletP2[i].x = -8;
				else _bulletP2[i].x = -10;
				_bulletP2[i].y = 10 - j * 5;
				break;
			}
		}
	}
	break;
	case YUDO:
	{
		if (_reloadCount2 <= 30) break;
		else _reloadCount2 = 0;
		for (int i = 0; i < BULLETMAX; i++)
		{
			if (_bulletP2[i].isFire) continue;
			_bulletP2[i].rc = RectMakeCenter(_player2.left - 5,
				(_player2.top + _player2.bottom) / 2, 10, 10);
			_bulletP2[i].isFire = true;
			_bulletP2[i].x = -10;
			_bulletP2[i].y = 0;
			_bulletP2[i].isYudo = true;
			_bulletP2[i].betrayed = false;
			break;
		}
	}
	break;
	}
}

void playGround::bulletMove()
{
	for (int i = 0; i < BULLETMAX; i++)
	{ // ȭ������� ���� isfire �ƴ�
		if (_bulletP1[i].rc.left > WINSIZEX || _bulletP1[i].rc.right < 0 ||
			_bulletP1[i].rc.top < 0 || _bulletP1[i].rc.bottom > WINSIZEY) _bulletP1[i].isFire = false;
		if (!_bulletP1[i].isFire) continue; // fire�ƴѰ� ������ �ʿ� �����ϱ�
		_bulletP1[i].rc.left += _bulletP1[i].x; // x������ x����ŭ
		_bulletP1[i].rc.right += _bulletP1[i].x;
		_bulletP1[i].rc.top += _bulletP1[i].y; // y������ y����ŭ
		_bulletP1[i].rc.bottom += _bulletP1[i].y;
	}
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (_bulletP2[i].rc.left > WINSIZEX || _bulletP2[i].rc.right < 0 ||
			_bulletP2[i].rc.top < 0 || _bulletP2[i].rc.bottom > WINSIZEY) _bulletP2[i].isFire = false;
		if (!_bulletP2[i].isFire) continue;
		_bulletP2[i].rc.left += _bulletP2[i].x;
		_bulletP2[i].rc.right += _bulletP2[i].x;
		_bulletP2[i].rc.top += _bulletP2[i].y;
		_bulletP2[i].rc.bottom += _bulletP2[i].y;
	}
}

void playGround::collision()
{
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (!_bulletP1[i].isFire) continue; // �Ƚ�� ���ΰ� �ε����� ����
		if (IntersectRect(&temp, &_bulletP1[i].rc, &_player2)) // �ε�����
		{
			_bulletP1[i].isFire = false; // ���̻� �Ⱥε����� + ��� ���־��ϴϱ� false��
			if (_frontGauge2.left >= _frontGauge2.right) return;
			_frontGauge2.left += 10; // ������(������ �¿� ������) �����ع����� �ƴϸ� ������������ 10�̵�
			if (_frontGauge2.right - _frontGauge2.left < 250){	_r2 = 255;	_g2 = 255;} // �����
			if (_frontGauge2.right - _frontGauge2.left < 100){	_r2 = 255;	_g2 = 0;} // ����
			break;
		}
	}
	for (int i = 0; i < BULLETMAX; i++)
	{ // �� �Ѿ� �� �����(��������)�ΰ� ������.. �Ѿ� Ŭ������ '�Ҽ�'�� ������ �� ��������
		if (!_bulletP2[i].isFire || !_bulletP2[i].betrayed) continue; // ������̾ƴϰų� ����Ѿƴϸ� �н�
		if (IntersectRect(&temp, &_bulletP2[i].rc, &_player2)) // �ε�����
		{
			_bulletP2[i].isFire = false; // �Ƚ��
			_bulletP2[i].betrayed = false; // ��ų�
			if (_frontGauge2.left >= _frontGauge2.right) return; //���ϴ� ���� ����
			_frontGauge2.left += 10;
			if (_frontGauge2.right - _frontGauge2.left < 250) { _r2 = 255;	_g2 = 255; }
			if (_frontGauge2.right - _frontGauge2.left < 100) { _r2 = 255;	_g2 = 0; }
			break;
		}
	}
}

void playGround::collision2()
{// collision�� �ּ� ����
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (!_bulletP2[i].isFire) continue;

		if (IntersectRect(&temp, &_bulletP2[i].rc, &_player1))
		{
			_bulletP2[i].isFire = false;
			if (_frontGauge.left >= _frontGauge.right) return;
			_frontGauge.right -= 10;
			if (_frontGauge.right - _frontGauge.left < 250) { _r = 255;	_g = 255; }
			if (_frontGauge.right - _frontGauge.left < 100) { _r = 255;	_g = 0; }
			break;
		}
	}
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (!_bulletP1[i].isFire || !_bulletP1[i].betrayed) continue;
		if (IntersectRect(&temp, &_bulletP1[i].rc, &_player1))
		{
			_bulletP1[i].isFire = false;
			_bulletP1[i].betrayed = false;
			if (_frontGauge.left >= _frontGauge.right) return;
			_frontGauge.right -= 10;
			if (_frontGauge.right - _frontGauge.left < 250) { _r = 255;	_g = 255; }
			if (_frontGauge.right - _frontGauge.left < 100) { _r = 255;	_g = 0; }
			break;
		}
	}
}

void playGround::collisionObstacle()
{//��ֹ��� �浹��
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (!_bulletP1[i].isFire) continue; // �������̾�ƴϸ� �н�
		if (IntersectRect(&temp, &_bulletP1[i].rc, &_obstacle))	_bulletP1[i].isFire = false; // �浹�� �������̾�� ��
	}
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (!_bulletP2[i].isFire) continue; // ���� ����
		if (IntersectRect(&temp, &_bulletP2[i].rc, &_obstacle))	_bulletP2[i].isFire = false;		
	}
}

void playGround::Yudo()
{ // ���� �����ϴ°�
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (!_bulletP1[i].isFire || !_bulletP1[i].isYudo) continue; // ����߾ƴϰų� ������ �ƴϸ� �ش�ȵ�
		if (IntersectRect(&temp, &_bulletP1[i].rc, &_bigRect2))
		{ // ��Ʈ = ����ź ������ ū�簢�� .. ��ư ��Ʈ�� ź���� ��ġ��
			_yudoFrom = { (float)(_bulletP1[i].rc.left + _bulletP1[i].rc.right) / 2, (float)(_bulletP1[i].rc.top + _bulletP1[i].rc.bottom) / 2 };
			_yudoTo = { (float)(_player2.left + _player2.right) / 2, (float)(_player2.top + _player2.bottom) / 2 };
			// ����ź ������� �Ѿ� ��������, ����ź �������� �÷��̾� ��������.
			// _yudoFrom�̶� _yudoTo�� POINTFLOAT�� {x, y}����
			angle = calcAngleFromPoints(_yudoFrom, _yudoTo); // �� ���� ���� ����
			_bulletP1[i].x = -10 * cos(angle); // x�ӵ��� -10���ϱ� �ڻ���(����)
			_bulletP1[i].y = -10 * sin(angle); // y�� ����
		}
	}
}

void playGround::Yudo2()
{ // �ּ��� Yudo����
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (!_bulletP2[i].isFire || !_bulletP2[i].isYudo) continue;
		if (IntersectRect(&temp, &_bulletP2[i].rc, &_bigRect1))
		{
			_yudoFrom = { (float)(_bulletP2[i].rc.left + _bulletP2[i].rc.right) / 2, (float)(_bulletP2[i].rc.top + _bulletP2[i].rc.bottom) / 2 };
			_yudoTo = { (float)(_player1.left + _player1.right) / 2, (float)(_player1.top + _player1.bottom) / 2 };
			angle = calcAngleFromPoints(_yudoFrom, _yudoTo);
			_bulletP2[i].x = -10 * cos(angle);
			_bulletP2[i].y = -10 * sin(angle);
		}
	}
}

void playGround::ultiP1()
{ // �ý��
	for (int i = 0; i < BULLETMAX; i++)
	{ // P2�� ��� �Ѿ�
		if (!_bulletP2[i].isFire) continue; // �߻����� �ƴϸ� �н�
		_yudoFrom = { (float)(_bulletP2[i].rc.left + _bulletP2[i].rc.right) / 2, (float)(_bulletP2[i].rc.top + _bulletP2[i].rc.bottom) / 2 };
		_yudoTo = { (float)(_player2.left + _player2.right) / 2, (float)(_player2.top + _player2.bottom) / 2 };
		angle = calcAngleFromPoints(_yudoFrom, _yudoTo);
		_bulletP2[i].x = -10 * cos(angle);
		_bulletP2[i].y = -10 * sin(angle);
		// �̻��� Yudo�Լ����� ��� �״����. ������ ���ؼ� 10�� �ӵ��μ� �۷� ����
		_bulletP2[i].betrayed = true; // ����ߴ� true��
		_bulletP2[i].isYudo = false; // ����ź�̸� �Ϲ�ź����
	}

	for (int i = 0; i < BULLETMAX; i++)
	{
		if (!_bulletP1[i].isFire) continue; // �߻����� �ƴϸ� �н�
		_yudoFrom = { (float)(_bulletP1[i].rc.left + _bulletP1[i].rc.right) / 2, (float)(_bulletP1[i].rc.top + _bulletP1[i].rc.bottom) / 2 };
		_yudoTo = { (float)(_player2.left + _player2.right) / 2, (float)(_player2.top + _player2.bottom) / 2 };
		angle = calcAngleFromPoints(_yudoFrom, _yudoTo);
		_bulletP1[i].x = -10 * cos(angle);
		_bulletP1[i].y = -10 * sin(angle); // �̻��� Yudo�Լ����� ��� �״����. ������ ���ؼ� 10�� �ӵ��μ� �۷� ����
		_bulletP1[i].betrayed = false; // Ȥ�� �����ź�̸� �ٽ� ����ϰԲ�
		_bulletP1[i].isYudo = false; // ����ź�̸� �Ϲ�ź����
	}

	_ultiCount1 = 0;
}

void playGround::ultiP2()
{ // �ּ��� ultiP1����
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (!_bulletP1[i].isFire) continue;
		_yudoFrom = { (float)(_bulletP1[i].rc.left + _bulletP1[i].rc.right) / 2, (float)(_bulletP1[i].rc.top + _bulletP1[i].rc.bottom) / 2 };
		_yudoTo = { (float)(_player1.left + _player1.right) / 2, (float)(_player1.top + _player1.bottom) / 2 };
		angle = calcAngleFromPoints(_yudoFrom, _yudoTo);
		_bulletP1[i].x = -10 * cos(angle);
		_bulletP1[i].y = -10 * sin(angle);
		_bulletP1[i].betrayed = true;
		_bulletP1[i].isYudo = false;
	}
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (!_bulletP2[i].isFire) continue;
		_yudoFrom = { (float)(_bulletP2[i].rc.left + _bulletP2[i].rc.right) / 2, (float)(_bulletP2[i].rc.top + _bulletP2[i].rc.bottom) / 2 };
		_yudoTo = { (float)(_player1.left + _player1.right) / 2, (float)(_player1.top + _player1.bottom) / 2 };
		angle = calcAngleFromPoints(_yudoFrom, _yudoTo);
		_bulletP2[i].x = -10 * cos(angle);
		_bulletP2[i].y = -10 * sin(angle);
		_bulletP2[i].betrayed = false;
		_bulletP2[i].isYudo = false;
	}

	_ultiCount2 = 0;
}

float playGround::calcAngleFromPoints(POINTFLOAT _ptFirst, POINTFLOAT _ptSecond)
{ // �� ��(����Ʈ�÷�Ʈ)�� ���� ���ϴ� �Լ�(from ���۸�)
	float fAngle;
	float fdX = _ptFirst.x - _ptSecond.x;
	float fdY = _ptFirst.y - _ptSecond.y;

	float dRad = atan2(fdY, fdX);
	return dRad;
}
