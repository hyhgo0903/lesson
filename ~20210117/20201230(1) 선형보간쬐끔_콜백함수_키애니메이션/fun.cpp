#include "stdafx.h"
#include "fun.h"

HRESULT fun::init()
{
	_worldTimeCount = 0;
	_isMoving = false;

	return S_OK;
}

void fun::release()
{
}

void fun::update()
{
	moving();
}

void fun::render()
{
}

void fun::moveTo(image* image, float endX, float endY, float time)
{
	if (!_isMoving)
	{
		_image = image;

		_startX = _image->getX();
		_startY = _image->getY();

		_endX = endX;
		_endY = endY;

		_travelRange = getDistance(_startX, _startY, _endX, _endY);

		_angle = getAngle(_startX, _startY, _endX, _endY);

		_worldTimeCount = TIMEMANAGER->getWorldTime();
		// 초기에만 불러준다
		_time = time;

		_isMoving = true;
	}
}
// 선형보간 나도알고 너도 아는 그 속도
// 구형보간 쫓아올떄 쓴다??
void fun::moving()
{
	//Not~ 
	if (!_isMoving) return;

	// 그냥 1/60초라고 생각합시다. 헷갈리지 않게
	float elapsedTime = TIMEMANAGER->getElapsedTime();


	//이게 하이라이뜨 입니다 
	float moveSpeed = (elapsedTime / _time) * _travelRange;
	// 속도 = (1/60(초)) / (지속시간(초)) * 총 이동거리
	// 속도 = 1/60 / 이동시간 * 총 이동거리

	// time 10초, 이동거리 600pixel이라고치면 (대략 가로길이 반이상쯤이라고 봅시다)
	// 1/60/1*600인 10pixel/s가 된다.(속도는 10)

	_image->setX(_image->getX() + cosf(_angle) * moveSpeed);
	_image->setY(_image->getY() + (-sinf(_angle) * moveSpeed));
	// 속도만큼이동
	
	if (_time + _worldTimeCount <= TIMEMANAGER->getWorldTime())
	{ // 초기 저장한 타임카운트에 지정한 지속시간을 더한 시점에 도달(말이 어렵지만 시간이 되면이란뜻)
		_worldTimeCount = TIMEMANAGER->getWorldTime();
		// 타임카운트는 갱신(또 쓰려고..?)
		_image->setX(_endX);
		_image->setY(_endY);

		_isMoving = false; // 이동안함
	}
}
