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
		// �ʱ⿡�� �ҷ��ش�
		_time = time;

		_isMoving = true;
	}
}
// �������� �����˰� �ʵ� �ƴ� �� �ӵ�
// �������� �ѾƿË� ����??
void fun::moving()
{
	//Not~ 
	if (!_isMoving) return;

	// �׳� 1/60�ʶ�� �����սô�. �򰥸��� �ʰ�
	float elapsedTime = TIMEMANAGER->getElapsedTime();


	//�̰� ���̶��̶� �Դϴ� 
	float moveSpeed = (elapsedTime / _time) * _travelRange;
	// �ӵ� = (1/60(��)) / (���ӽð�(��)) * �� �̵��Ÿ�
	// �ӵ� = 1/60 / �̵��ð� * �� �̵��Ÿ�

	// time 10��, �̵��Ÿ� 600pixel�̶��ġ�� (�뷫 ���α��� ���̻����̶�� ���ô�)
	// 1/60/1*600�� 10pixel/s�� �ȴ�.(�ӵ��� 10)

	_image->setX(_image->getX() + cosf(_angle) * moveSpeed);
	_image->setY(_image->getY() + (-sinf(_angle) * moveSpeed));
	// �ӵ���ŭ�̵�
	
	if (_time + _worldTimeCount <= TIMEMANAGER->getWorldTime())
	{ // �ʱ� ������ Ÿ��ī��Ʈ�� ������ ���ӽð��� ���� ������ ����(���� ������� �ð��� �Ǹ��̶���)
		_worldTimeCount = TIMEMANAGER->getWorldTime();
		// Ÿ��ī��Ʈ�� ����(�� ������..?)
		_image->setX(_endX);
		_image->setY(_endY);

		_isMoving = false; // �̵�����
	}
}
