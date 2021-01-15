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

	_isDead = _isDeadAI = _isNorang= false;

	_ourHPBack = RectMake(50, 50, 400, 50); // 400���� �ϰ� 40�� ������
	_AIHPBack = RectMake(WINSIZEX - 450, 50, 400, 50);
	_ourHP = RectMake(50, 50, 400, 50); // 400���� �ϰ� 40�� ������
	_AIHP = RectMake(WINSIZEX - 450, 50, 400, 50);

	_reloadBack = RectMake(50, 120, 200, 20);
	_reloadAIBack = RectMake(WINSIZEX - 250, 120, 200, 20);
	_reload = RectMake(50, 120, 0, 20);
	_reloadAI = RectMake(WINSIZEX - 50, 120, 0, 20);
	// ���� ü�¹ٳ� ��������

	_cannon.angle = PI / 4;
	_cannon.cannon = 80;
	_cannon.center.x = 200;	_cannon.center.y = WINSIZEY;

	_cannonAI.angle = 3 * PI / 4;
	_cannonAI.cannon = 80;
	_cannonAI.center.x = WINSIZEX - 200; 	_cannonAI.center.y = WINSIZEY;

	for (int i = 0; i < BULLETMAX; i++)
	{
		_bullet[i].speed = _speed;
		_bullet[i].radius = BULLETRADIUS;
		_bullet[i].isFire = false;
		_bullet[i].gravity = 0;

		_bulletAI[i].speed = _speed;
		_bulletAI[i].radius = BULLETRADIUS;
		_bulletAI[i].isFire = false;
		_bulletAI[i].gravity = 0;

		_track[i].speed = _speed; // �Ѿ��̶� Ʈ�� �迭�� �����ؼ� ����� �̿�
		_track[i].radius = TRACKSIZE;
		_track[i].gravity = 0; // �� �������̾����

		_trackAI[i].speed = _speed;
		_trackAI[i].radius = TRACKSIZE;
		_trackAI[i].gravity = 0;
	}

	_angleDirection = 1; // AI������ �ö󰡰��ִ��� �����ϰ��ִ���(�׳� �Ұ����� �� ������..)
	trackSet(); // �ʱ� �� �� �׷��ش�

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
	if (!_isDead && !_isDeadAI)
	{
		if (_reload.left + 200 > _reload.right) _reload.right += 2;
		if (_reloadAI.left + 200 > _reloadAI.right) _reloadAI.left -= 2;
		if (_reloadAI.left + 200 > _reloadAI.right && _isNorang) _reloadAI.left -= 8; // ����̸� �߰���

		if (_AIHP.right - _AIHP.left < 200 && _AIHP.right - _AIHP.left >= 100)_isNorang = true;

		if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _cannon.center.x > CANNONRADIUS)
		{
			_cannon.center.x -= 3;
			if (_cannon.angle < PI / 2) _cannon.angle = PI - _cannon.angle; // ������ȯ
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _cannon.center.x < WINSIZEX / 2 - 100)
		{
			_cannon.center.x += 3;
			if (_cannon.angle > PI / 2) _cannon.angle = PI - _cannon.angle; // ������ȯ
		}

		if (KEYMANAGER->isStayKeyDown(VK_UP) && _cannon.angle < PI / 2 - 0.20)	{_cannon.angle += 0.04f;}
		if (KEYMANAGER->isStayKeyDown(VK_UP) && _cannon.angle > PI / 2 + 0.20)	{_cannon.angle -= 0.04f;}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _cannon.angle < PI / 2 && _cannon.angle > 0.50) {_cannon.angle -= 0.04f;}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _cannon.angle > PI / 2 && _cannon.angle < 2.64) {_cannon.angle += 0.04f;}

		if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && _reload.left + 200 <= _reload.right) bulletFire();

		//���� ���� (���� ��ȣ�� �񿡼� �ǳ����� �����ϸ鼭 ���ƴٴϴ� �װ�)
		_cannon.cannonEnd.x = cosf(_cannon.angle) * _cannon.cannon + _cannon.center.x;
		_cannon.cannonEnd.y = -sinf(_cannon.angle) * _cannon.cannon + _cannon.center.y;

		_cannonAI.cannonEnd.x = cosf(_cannonAI.angle) * _cannonAI.cannon + _cannonAI.center.x;
		_cannonAI.cannonEnd.y = -sinf(_cannonAI.angle) * _cannonAI.cannon + _cannonAI.center.y;

		trackSet();		trackSetAI();		bulletMove();
		AIangleSet();		collide();		evasion();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN) &&(_isDead || _isDeadAI))
	{
		this->init();
	}
	
}

//���� ����� �׷��� ��...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ ���� �ǵ��� ���� ==============================
	

	Rectangle(backDC, _reloadBack);
	Rectangle(backDC, _reloadAIBack);
	Rectangle(backDC, _AIHPBack);
	Rectangle(backDC, _ourHPBack);

	if (_ourHP.right - _ourHP.left >= 200)
	{ // �ʷ�
		HBRUSH brush = CreateSolidBrush(RGB(0, 255, 0));		HBRUSH oldbrush = (HBRUSH)SelectObject(backDC, brush);
		Rectangle(backDC, _ourHP);		SelectObject(backDC, oldbrush);		DeleteObject(brush);
	}
	else if (_ourHP.right - _ourHP.left >= 100)
	{ // ���
		HBRUSH brush = CreateSolidBrush(RGB(255, 212, 0));		HBRUSH oldbrush = (HBRUSH)SelectObject(backDC, brush);
		Rectangle(backDC, _ourHP);		SelectObject(backDC, oldbrush);		DeleteObject(brush);
	}
	else
	{ // ����
		HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));		HBRUSH oldbrush = (HBRUSH)SelectObject(backDC, brush);
		Rectangle(backDC, _ourHP);		SelectObject(backDC, oldbrush);		DeleteObject(brush);
	}

	if (_AIHP.right - _AIHP.left >= 200)
	{ // �ʷ�
		HBRUSH brush = CreateSolidBrush(RGB(0, 255, 0));		HBRUSH oldbrush = (HBRUSH)SelectObject(backDC, brush);
		Rectangle(backDC, _AIHP);		SelectObject(backDC, oldbrush);		DeleteObject(brush);
	}
	else if (_AIHP.right - _AIHP.left >= 100)
	{ // ���
		HBRUSH brush = CreateSolidBrush(RGB(255, 212, 0));		HBRUSH oldbrush = (HBRUSH)SelectObject(backDC, brush);
		Rectangle(backDC, _AIHP);		SelectObject(backDC, oldbrush);		DeleteObject(brush);
	}
	else
	{ // ����
		HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));		HBRUSH oldbrush = (HBRUSH)SelectObject(backDC, brush);
		Rectangle(backDC, _AIHP);		SelectObject(backDC, oldbrush);		DeleteObject(brush);
	}

	// ������ ��
	HBRUSH brush = CreateSolidBrush(RGB(200, 200, 200));	HBRUSH oldbrush = (HBRUSH)SelectObject(backDC, brush);
	Rectangle(backDC, _reload);	Rectangle(backDC, _reloadAI);
	SelectObject(backDC, oldbrush);	DeleteObject(brush);


	// �� ĳ��
	brush = CreateSolidBrush(RGB(220, 220, 255));	oldbrush = (HBRUSH)SelectObject(backDC, brush);
	EllipseMakeCenter(backDC, _cannon.center.x, _cannon.center.y, 2 * CANNONRADIUS, 2 * CANNONRADIUS);
	SelectObject(backDC, oldbrush);	DeleteObject(brush);
	LineMake(backDC, _cannon.center.x, _cannon.center.y, _cannon.cannonEnd.x, _cannon.cannonEnd.y);

	// �� ĳ��
	brush = CreateSolidBrush(RGB(255, 220, 220));	oldbrush = (HBRUSH)SelectObject(backDC, brush);
	EllipseMakeCenter(backDC, _cannonAI.center.x, _cannonAI.center.y, 2 * CANNONRADIUS, 2 * CANNONRADIUS);
	SelectObject(backDC, oldbrush);	DeleteObject(brush);
	LineMake(backDC, _cannonAI.center.x, _cannonAI.center.y, _cannonAI.cannonEnd.x, _cannonAI.cannonEnd.y);

	for (int i = BULLETMAX-1; i >=0; i=i-1)
	{ // ���Ѿ�
		if (!_bullet[i].isFire) continue;
		HBRUSH brush = CreateSolidBrush(RGB(200, 200, 255));	HBRUSH oldbrush = (HBRUSH)SelectObject(backDC, brush);
		EllipseMakeCenter(backDC, _bullet[i].x, _bullet[i].y, 2*BULLETRADIUS, 2*BULLETRADIUS);
		SelectObject(backDC, oldbrush);	DeleteObject(brush);
	}

	for (int i = BULLETMAX - 1; i >= 0; i = i - 1)
	{ // ���Ѿ�
		if (!_bulletAI[i].isFire) continue;
		HBRUSH brush = CreateSolidBrush(RGB(255, 200, 200));	HBRUSH oldbrush = (HBRUSH)SelectObject(backDC, brush);
		EllipseMakeCenter(backDC, _bulletAI[i].x, _bulletAI[i].y, 2 * BULLETRADIUS, 2 * BULLETRADIUS);
		SelectObject(backDC, oldbrush);	DeleteObject(brush);
	}
	
	char str[256];
	if (_isDead || _isDeadAI)
	{
		sprintf_s(str, "���ӿ���");
		TextOut(backDC, WINSIZEX / 2-50, WINSIZEY / 2-20, str, strlen(str));
		sprintf_s(str, "����������? ENTER��.");
		TextOut(backDC, WINSIZEX / 2 - 100, WINSIZEY / 2, str, strlen(str));
	}

	if (_isNorang)
	{
		sprintf_s(str, "������ ��� (��ģ����ӵ�)");
		TextOut(backDC, WINSIZEX - 200, 20, str, strlen(str));
	}


	// Ʈ�� �Ⱥ��̰� �ּ�ó��
	/*
	for (int i = BULLETMAX-1; i >=0 ; i--)
	{
		EllipseMakeCenter(backDC, _track[i].x, _track[i].y, _track[i].radius * 2, _track[i].radius * 2);
		EllipseMakeCenter(backDC, _trackAI[i].x, _trackAI[i].y, _trackAI[i].radius * 2, _trackAI[i].radius * 2);
	} */
	
	
	//================= �Ʒ��� �ǵ��� ���� ==============================
	this->getBackBuffer()->render(hdc, 0, 0);
}

void playGround::bulletFire()
{ // �� �Ѿ� �߻�
	for (int i = 0; i < BULLETMAX; i++)
	{
		_reload.right = _reload.left; // ���� �ʱ�ȭ
		if (_bullet[i].isFire) continue; // �Ƚ�°� ����
		_bullet[i].isFire = true; // ���
		_bullet[i].angle = _cannon.angle; // �ޱ�
		_bullet[i].x = cosf(_cannon.angle) * (_cannon.cannon + 3) + _cannon.center.x; // ��ġ
		_bullet[i].y = -sinf(_cannon.angle) * (_cannon.cannon + 3) + _cannon.center.y;
		break;
	}
}

void playGround::bulletFireAI()
{ // �� �Ѿ˹߻� (�ּ��� ���� ����)
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (_bulletAI[i].isFire) continue;
		_bulletAI[i].isFire = true;
		_bulletAI[i].angle = _cannonAI.angle;
		_bulletAI[i].x = cosf(_cannonAI.angle) * (_cannonAI.cannon + 3) + _cannonAI.center.x;
		_bulletAI[i].y = -sinf(_cannonAI.angle) * (_cannonAI.cannon + 3) + _cannonAI.center.y;
		break;
	}
}


void playGround::bulletMove()
{ // �Ѿ��̵�
	for (int i = 0; i < BULLETMAX; i++)
	{ // �� �ο�
		if (!_bullet[i].isFire) continue;
		_bullet[i].gravity += 0.08;
		_bullet[i].x += cosf(_bullet[i].angle) * _speed;
		_bullet[i].y += -sinf(_bullet[i].angle) * _speed + _bullet[i].gravity;

		//ȭ�� �������� ������
		if (_bullet[i].x + _bullet[i].radius < 0)
		{_bullet[i].isFire = false;			_bullet[i].gravity = 0;}

		//ȭ�� ���������� ������
		if (_bullet[i].x - _bullet[i].radius > WINSIZEX)
		{_bullet[i].isFire = false;			_bullet[i].gravity = 0;}

		//ȭ�� �������� ������
		if (_bullet[i].y - _bullet[i].radius < 0)
		{_bullet[i].isFire = false;			_bullet[i].gravity = 0;}

		//ȭ�� �Ʒ������� ������
		if (_bullet[i].y - _bullet[i].radius > WINSIZEY)
		{_bullet[i].isFire = false;			_bullet[i].gravity = 0;}

	}

	for (int i = 0; i < BULLETMAX; i++)
	{ // �� �Ѿ� �̵�
		if (!_bulletAI[i].isFire) continue;
		_bulletAI[i].gravity += 0.08;
		_bulletAI[i].x += cosf(_bulletAI[i].angle) * _speed;
		_bulletAI[i].y += -sinf(_bulletAI[i].angle) * _speed + _bulletAI[i].gravity;

		if (_bulletAI[i].x + _bulletAI[i].radius < 0)
		{_bulletAI[i].isFire = false;			_bulletAI[i].gravity = 0;}
		if (_bulletAI[i].x - _bulletAI[i].radius > WINSIZEX)
		{_bulletAI[i].isFire = false;			_bulletAI[i].gravity = 0;}
		if (_bulletAI[i].y - _bulletAI[i].radius < 0)
		{_bulletAI[i].isFire = false;			_bulletAI[i].gravity = 0;}
		if (_bulletAI[i].y - _bulletAI[i].radius > WINSIZEY)
		{_bulletAI[i].isFire = false;			_bulletAI[i].gravity = 0;}

	}
}

void playGround::trackSet()
{ // �˵� (������ �ߴ��� ������)
	_track[0].x = cosf(_cannon.angle) * (_cannon.cannon + 3) + _cannon.center.x;
	_track[0].y = -sinf(_cannon.angle) * (_cannon.cannon + 3) + _cannon.center.y;
	_track[0].angle = _cannon.angle;
	float gravity = 0.08f;
	for (int i = 1; i < BULLETMAX; i++)
	{
		_track[i].x = _track[0].x + (4*i) * cosf(_track[0].angle) * _speed;
		_track[i].y = _track[0].y + (4*i) * (-sinf(_track[0].angle) * _speed)+ (4*i)*(4*i)/2* gravity;
		if (_track[i].y > WINSIZEY + TRACKSIZE) { _track[i].x = WINSIZEX + 10; } // ������ ġ������
	}
}

void playGround::trackSetAI()
{ // �� �˵�(�̻��� ���� �����ϴµ� �ʿ�)
	_trackAI[0].x = cosf(_cannonAI.angle) * (_cannonAI.cannon + 3) + _cannonAI.center.x;
	_trackAI[0].y = -sinf(_cannonAI.angle) * (_cannonAI.cannon + 3) + _cannonAI.center.y;
	_trackAI[0].angle = _cannonAI.angle;
	float gravity = 0.08f;
	for (int i = 1; i < BULLETMAX; i++)
	{
		_trackAI[i].x = _trackAI[0].x + (4 * i) * cosf(_trackAI[0].angle) * _speed;
		_trackAI[i].y = _trackAI[0].y + (4 * i) * (-sinf(_trackAI[0].angle) * _speed) + (4 * i)*(4 * i) / 2 * gravity;
		if (_trackAI[i].y > WINSIZEY + TRACKSIZE) { _trackAI[i].x = WINSIZEX + 10;} // ������ ġ������
	}
}

void playGround::AIangleSet()
{
	if (_cannon.center.x > _cannonAI.center.x && _cannonAI.angle > PI / 2)
	{ // ��x���� ��x������ ũ�� �� �ޱ��� 90������ ū ��� ���������
		_cannonAI.angle = PI - _cannonAI.angle;
	}
	if (_cannon.center.x < _cannonAI.center.x && _cannonAI.angle < PI / 2)
	{
		_cannonAI.angle = PI - _cannonAI.angle;
	} // ���� ������ ������ or �������� ���� �¿� �ٲ�

	if (_angleDirection == 1)
	{ // �ޱ۹����� 1�̸� �ø���
		_cannonAI.angle += 0.02f;
	}
	else
	{ // �ƴϸ� ������
		_cannonAI.angle -= 0.02f;
	}
	if (_cannonAI.angle >= PI / 2 - 0.2 && _cannonAI.angle <= PI / 2 + 0.2) _angleDirection *= -1;
	if (_cannonAI.angle >= 2.74 || _cannonAI.angle <= 0.4) _angleDirection *= -1;
	// �ּҰ��̳� �ִ밢�� �����ϸ� �ޱ۹����� �ݴ�� �ٲ۴�

	for (int i = 0; i < BULLETMAX; i++)
	{ // �˵�(���� ��)�� �� ĳ�� ��Ұ� �����Ϸ������
		if (getDistance(_trackAI[i].x, _trackAI[i].y, _cannon.center.x, _cannon.center.y)<CANNONRADIUS			
			&& _reloadAI.left+200 <= _reloadAI.right)
		{
			_reloadAI.left = _reloadAI.right; // ���� �ʱ�ȭ
			bulletFireAI(); // �߻�
		}
	}


}

void playGround::collide()
{// �ǰ�
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (getDistance(_bullet[i].x, _bullet[i].y, _cannonAI.center.x, _cannonAI.center.y) < CANNONRADIUS+BULLETRADIUS
			&& _bullet[i].isFire)
		{
			_bullet[i].isFire = false;
			_bullet[i].gravity = 0;
			if ( _AIHP.left != _AIHP.right) _AIHP.left += 40;
			if (_AIHP.left == _AIHP.right) _isDeadAI = true;
		}

		if (getDistance(_bulletAI[i].x, _bulletAI[i].y, _cannon.center.x, _cannon.center.y) < CANNONRADIUS + BULLETRADIUS
			&& _bulletAI[i].isFire)
		{
			_bulletAI[i].isFire = false;
			_bulletAI[i].gravity = 0;
			if (_ourHP.left != _ourHP.right) _ourHP.right -= 40;
			if (_ourHP.left == _ourHP.right) _isDead = true;
		}
	}
}

void playGround::evasion()
{// ȸ�Ǳ⵿
	_bigRect = RectMakeCenter(_cannonAI.center.x, _cannonAI.center.y, 500, 300);
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (_bullet[i].x > _bigRect.left && _bullet[i].x < _bigRect.right &&
			_bullet[i].y > _bigRect.top && _bullet[i].y < _bigRect.bottom &&
			_bullet[i].isFire) // ���������� �Ѿ��� ������
		{
			_predictX = _bullet[i].x + (WINSIZEY - _bullet[i].y) / tanf(_bullet[i].angle); // ����x�� ����
			if (_predictX > _cannonAI.center.x) _cannonAI.center.x -= 3; // ���������� �̵�
			if (_predictX <= _cannonAI.center.x && _cannonAI.center.x < WINSIZEX - CANNONRADIUS) _cannonAI.center.x += 3;
			break;
		}
	}

	_peaceCount = 0;
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (_bullet[i].x > _bigRect.left && _bullet[i].x < _bigRect.right &&
			_bullet[i].y > _bigRect.top && _bullet[i].y < _bigRect.bottom &&
			_bullet[i].isFire) // �߻����ΰ� ��Ʈ�� �浹�ߴ�
		{
			_peaceCount++; // �浹�Ѱ� �ϳ��� ������ _peaceCount�� 1
			break;
		}
	}
	if (_peaceCount == 0) _peace = true; // �浹�Ѱ� ������ ��ȭ
	else _peace = false; // �ƴϸ� ����ȭ
	if (_peace) // ��ȭ�� ���ڸ���
	{
		if (_cannonAI.center.x <WINSIZEX - 200)	_cannonAI.center.x += 3;
		if (_cannonAI.center.x > WINSIZEX - 200) _cannonAI.center.x -= 3;
	}
}