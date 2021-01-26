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
//상태도 매개변수에 넣어서 스위치문 쓴거라 엄청나게 복잡함
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
		_bossPhase = 1; // 보스 페이즈는 1,2,3으로 돌아가고 0이면 보스출현 이전인거
		_count = -300; // 도착시간 길어서 페이즈씹힘방지
		break;
	}
	if (_state == PHASE_BOSS)
	{ // 이미지 차이 떄매 다르게..
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
	if(_count <300)_count++; // 보스아니면 이미지용으로 스지만 보스면 페이즈바뀌는 쿨타임으로 재활용했음
	move();
	if (_count % 2 == 0 && _state != PHASE_BOSS) // 보스는 프레임이미지 안쓰고 있어서
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
		if (!_arrived) // 첫 리젠장소에서 도착하지 않았으면
		{ // 보스는 프레임이미지 안쓰고 있어서
			_rc.left -= 8; _rc.right -= 8;
			if ((_rc.left + _rc.right) / 2 <= _toX) _arrived = true;
			_direction = 1;
		}
		else // 첫리젠후 도착했으면
		{
			_rc.left -= _direction * 3; _rc.right -= _direction * 3;
			if ((_rc.left + _rc.right) / 2 - _toX < -70 ||
				(_rc.left + _rc.right) / 2 - _toX > 70) _direction *= -1;
		}
		break;
	case PHASE_2:
		if (!_arrived) // 첫 리젠장소에서 도착하지 않았으면
		{
			_rc.top += 8; _rc.bottom += 8;
			if ((_rc.top + _rc.bottom) / 2 >= _toY) _arrived = true;
			_direction = 1;
		}
		else // 첫리젠후 도착했으면
		{
			_rc.top += _direction * 3; _rc.bottom += _direction * 3;
			if ((_rc.top + _rc.bottom) / 2 - _toY < -70 ||
				(_rc.top + _rc.bottom) / 2 - _toY > 70) _direction *= -1;
		}
		break;
	case PHASE_3:
		if (!_arrived) // 첫 리젠장소에서 도착하지 않았으면
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
		else // 첫리젠후 도착했으면
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
				_tempX, _tempY) > 5 ) // temp랑 거리가 좀 있을때만
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
		if (!_arrived) // 첫 리젠장소에서 도착하지 않았으면
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
		else if (_bossPhase == 2)//두번째 패턴은 좌우이동하도록(하고나서 나중에 추가)
		{
			_rc.left += _direction * 2;
			_rc.right += _direction * 2;
			if (_direction == 1 && _rc.right >= WINSIZEX) _direction *= -1;
			else if (_direction == -1 && _rc.left <= 0) _direction *= -1;
		}
		else
		{// 한번쓰고 아까우니 또 쓴다
			_countAgain++;
			if (_countAgain % 200 == 0)
			{
				_tempX = _toX + rand() % 401 - 200; // -200~200
				_tempY = _toY + rand() % 201 - 100;
				_countAgain = 0;
			}
			if (getDistance((_rc.left + _rc.right) / 2, (_rc.bottom + _rc.top) / 2,
				_tempX, _tempY) > 10 ) // 목적지랑 거리가 좀 있을때만
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
	if (!_arrived) return false; // 아직 도착안하면 쏘지않음
	_fireCount++;
	if(_fireCount % _rndFireCount == 0 && _state != PHASE_BOSS)
	{
		_fireCount = 0;
		_rndFireCount = RND->getFromIntTo(1, 800);

		return true;
	}
	else if (_bossPhase == 1)
	{ // 페이즈1에서는 계속 이 함수가 온됨
		_fireCount = 0;
		return true;
	}
	else if (_fireCount % 2 == 0 &&_bossPhase == 2)
	{ // 페이즈2에서는 2마다 이 함수가 온됨
		_fireCount = 0;
		return true;
	}
	else if (_fireCount % 40 == 0 && _bossPhase == 3)
	{ // 페이즈3에서는 40마다 이 함수가 온됨
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
