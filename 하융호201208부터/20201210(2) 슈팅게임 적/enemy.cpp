#include "stdafx.h"
#include "enemy.h"

enemy::enemy()
{
}

enemy::~enemy()
{
}

HRESULT enemy::init()
{
	return S_OK;
}
//���µ� �Ű������� �־ ����ġ�� ���Ŷ� ��û���� ������
HRESULT enemy::init(const char* imageName, POINT position, STATE state)
{
	_currentFrameX = _currentFrameY = 0;
	_count = _fireCount = _bossPhase= 0;
	_toX = position.x;
	_toY = position.y;
	_arrived = false;	
	_state = state;

	_imageName = IMAGEMANAGER->findImage(imageName);
	switch (_state)
	{
	case PHASE_1:
		_x = position.x + WINSIZEX;
		_y = position.y;
		_rc = RectMakeCenter(_x, _y,
			_imageName->getFrameWidth(),
			_imageName->getFrameHeight());
		break;
	case PHASE_2:
		_x = position.x;
		_y = position.y - WINSIZEY / 2;
		_rc = RectMakeCenter(_x, _y,
			_imageName->getFrameWidth(),
			_imageName->getFrameHeight());
		break;
	case PHASE_3:
		_x = position.x - WINSIZEX;
		_y = position.y;
		break;
	case PHASE_BOSS:
		_x = WINSIZEX / 2;
		_y = -175;
		_bossPhase = 1; // ���� ������� 1,2,3���� ���ư��� 0�̸� �������� �����ΰ�
		_count = -300; // �����ð� �� �������������
		break;
	}
	if (_state == PHASE_BOSS)
	{ // �̹��� ���� ���� �ٸ���..
		_rc = RectMakeCenter(_x, _y,
			_imageName->getWidth(),
			_imageName->getHeight());
	}
	else
	{
		_rc = RectMakeCenter(_x, _y,
			_imageName->getFrameWidth(),
			_imageName->getFrameHeight());
	}
	_rndFireCount = RND->getFromIntTo(1, 800);

	return S_OK;
}

void enemy::release()
{
}

void enemy::update()
{
	if(_count <300)_count++; // �����ƴϸ� �̹��������� ������ ������ ������ٲ�� ��Ÿ������ ��Ȱ������
	move();
	if (_count % 2 == 0 && _state != PHASE_BOSS) // ������ �������̹��� �Ⱦ��� �־
	{
		if (_currentFrameX >= _imageName->getMaxFrameX())  _currentFrameX = 0;

		_imageName->setFrameX(_currentFrameX);
		_currentFrameX++;

		_count = 0;
	}

	phaseShift();

}

void enemy::render()
{
	draw();
}

void enemy::move()
{
	switch (_state)
	{
	case PHASE_1:
		if (!_arrived) // ù ������ҿ��� �������� �ʾ�����
		{ // ������ �������̹��� �Ⱦ��� �־
			_rc.left -= 8; _rc.right -= 8;
			if ((_rc.left + _rc.right) / 2 <= _toX) _arrived = true;
			_direction = 1;
		}
		else // ù������ ����������
		{
			_rc.left -= _direction * 3; _rc.right -= _direction * 3;
			if ((_rc.left + _rc.right) / 2 - _toX < -70 ||
				(_rc.left + _rc.right) / 2 - _toX > 70) _direction *= -1;
		}
		break;
	case PHASE_2:
		if (!_arrived) // ù ������ҿ��� �������� �ʾ�����
		{
			_rc.top += 8; _rc.bottom += 8;
			if ((_rc.top + _rc.bottom) / 2 >= _toY) _arrived = true;
			_direction = 1;
		}
		else // ù������ ����������
		{
			_rc.top += _direction * 3; _rc.bottom += _direction * 3;
			if ((_rc.top + _rc.bottom) / 2 - _toY < -70 ||
				(_rc.top + _rc.bottom) / 2 - _toY > 70) _direction *= -1;
		}
		break;
	case PHASE_3:
		if (!_arrived) // ù ������ҿ��� �������� �ʾ�����
		{
			_rc.left += 8; _rc.right += 8;
			if ((_rc.left + _rc.right) / 2 >= _toX)
			{
				_arrived = true;
				_tempX = _toX + rand() % 141 - 70; // -70~70
				_tempY = _toY + rand() % 141 - 70;
				_countAgain = rand() % 100;
			}
		}
		else // ù������ ����������
		{
			_countAgain++;
			if (_countAgain % 100 == 0)
			{
				_tempX = _toX + rand() % 141 - 70; // -70~70
				_tempY = _toY + rand() % 141 - 70;
				_angle = getAngle((_rc.left + _rc.right) / 2, (_rc.bottom + _rc.top) / 2,
					_tempX, _tempY);
				_countAgain = 0;
			}
			if (getDistance((_rc.left + _rc.right) / 2, (_rc.bottom + _rc.top) / 2,
				_tempX, _tempY) > 5 ) // temp�� �Ÿ��� �� ��������
			{
				_angle = getAngle((_rc.left + _rc.right) / 2, (_rc.bottom + _rc.top) / 2,
					_tempX, _tempY);
				_rc.left += 5.0 * cosf(_angle);
				_rc.right += 5.0 * cosf(_angle);
				_rc.top -= 5.0 * sinf(_angle);
				_rc.bottom -= 5.0 * sinf(_angle);
			}

		}
		break;
	case PHASE_BOSS:
		if (!_arrived) // ù ������ҿ��� �������� �ʾ�����
		{
			_rc.top += 1; _rc.bottom += 1;
			if ((_rc.top + _rc.bottom) / 2 >= _toY)
			{
				_count = 0;
				_arrived = true;
				_tempX = _toX + rand() % 401 - 200; // -200~200
				_tempY = _toY + rand() % 201 - 100;
				_angle = getAngle((_rc.left + _rc.right) / 2, (_rc.bottom + _rc.top) / 2,
					_tempX, _tempY);
				_countAgain = 0;
				_direction = 1;
			}
		}
		else if (_bossPhase == 2)//�ι�° ������ �¿��̵��ϵ���(�ϰ��� ���߿� �߰�)
		{
			_rc.left += _direction * 2;
			_rc.right += _direction * 2;
			if (_direction == 1 && _rc.right >= WINSIZEX) _direction *= -1;
			else if (_direction == -1 && _rc.left <= 0) _direction *= -1;
		}
		else
		{// �ѹ����� �Ʊ��� �� ����
			_countAgain++;
			if (_countAgain % 200 == 0)
			{
				_tempX = _toX + rand() % 401 - 200; // -200~200
				_tempY = _toY + rand() % 201 - 100;
				_countAgain = 0;
			}
			if (getDistance((_rc.left + _rc.right) / 2, (_rc.bottom + _rc.top) / 2,
				_tempX, _tempY) > 10 ) // �������� �Ÿ��� �� ��������
			{
				_angle = getAngle((_rc.left + _rc.right) / 2, (_rc.bottom + _rc.top) / 2,
					_tempX, _tempY);
				_rc.left += 2.0 * cosf(_angle);
				_rc.right += 2.0 * cosf(_angle);
				_rc.top -= 2.0 * sinf(_angle);
				_rc.bottom -= 2.0 * sinf(_angle);
			}
		}
		break;
	default:
		break;
	}
}

void enemy::draw()
{
	if (_state != PHASE_BOSS)
	{
		_imageName->frameRender(getMemDC(), _rc.left, _rc.top,
			_currentFrameX, _currentFrameY);
	}
	else
	{
		_imageName->render(getMemDC(), _rc.left, _rc.top);
	}
}

bool enemy::bulletCountFire()
{
	if (!_arrived) return false; // ���� �������ϸ� ��������
	_fireCount++;
	if(_fireCount % _rndFireCount == 0 && _state != PHASE_BOSS)
	{
		_fireCount = 0;
		_rndFireCount = RND->getFromIntTo(1, 800);

		return true;
	}
	else if (_bossPhase == 1)
	{ // ������1������ ��� �� �Լ��� �µ�
		_fireCount = 0;
		return true;
	}
	else if (_fireCount % 2 == 0 &&_bossPhase == 2)
	{ // ������2������ 2���� �� �Լ��� �µ�
		_fireCount = 0;
		return true;
	}
	else if (_fireCount % 40 == 0 && _bossPhase == 3)
	{ // ������3������ 40���� �� �Լ��� �µ�
		_fireCount = 0;
		return true;
	}

	return false;
}

void enemy::phaseShift()
{
	if (_state == PHASE_BOSS && _count >= 300)
	{
		++_bossPhase;
		if (_bossPhase > 3) _bossPhase = 1;
		_count = 0;
	}
}
