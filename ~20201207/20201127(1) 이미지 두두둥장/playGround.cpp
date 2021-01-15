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



	for (int i = 0; i < SNAKEBODY; i++)
	{
		//�ޱ۰� ������ġ�� �����ϰ� �����. ���� �� �̷��� ���ص� �˴ϴ�
		_snake[i].angle = (i == 0) ? RND->getFloat(PI2) : _snake[i - 1].angle;
		_snake[i].x = (i == 0) ? RND->getFromFloatTo(100, WINSIZEX - 100) : _snake[i - 1].x - cosf(_snake[i].angle) * (_snake[i].radius * 2 + _snake[i - 1].radius * 2);
		_snake[i].y = (i == 0) ? RND->getFromFloatTo(100, WINSIZEY - 100) : _snake[i - 1].y - (-sinf(_snake[i].angle) * (_snake[i].radius * 2 + _snake[i - 1].radius * 2));
		_snake[i].radius = 42;
		_snake[i].speed = 6.0f;
	}

	_background = new image;
	_background->init("�޸𸮺���.bmp", 614, 768, false, RGB(0, 0, 0));
	// �ش� ������ �־��.
	// �ش������� �����ӿ� ������ ������\�޸𸮺���.bmp
	_donut = new image;
	_donut->init("mintDonut.bmp", 92, 84, true, RGB(255, 0, 255));

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

	//�迭 0��° �ε����� �Ӹ�����
	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) _snake[0].angle += 0.08f;
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) _snake[0].angle -= 0.08f;

	snakeMove();

}

//���� ����� �׷��� ��...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ ���� �ǵ��� ���� ==============================

	_background->render(backDC, 0, 0);

	for (int i = 0; i < SNAKEBODY; i++)
	{
		_donut->render(backDC, _snake[i].x - _snake[i].radius,
			_snake[i].y - _snake[i].radius);

		//EllipseMakeCenter(backDC, _snake[i].x, _snake[i].y, _snake[i].radius * 2, _snake[i].radius * 2);
	}
	
	//================= �Ʒ��� �ǵ��� ���� ==============================
	this->getBackBuffer()->render(hdc, 0, 0);
}

void playGround::snakeMove()
{
	for (int i = 0; i < SNAKEBODY; i++)
	{
		//�Ӹ���
		if (i == 0)
		{
			_snake[i].x += cosf(_snake[i].angle) * _snake[i].speed;
			_snake[i].y += -sinf(_snake[i].angle) * _snake[i].speed;

			if (_snake[i].x - _snake[i].radius < 0)
			{
				_snake[i].x = _snake[i].radius;
				_snake[i].angle = PI - _snake[i].angle;
			}
			if (_snake[i].x + _snake[i].radius > WINSIZEX)
			{
				_snake[i].x = WINSIZEX - _snake[i].radius;
				_snake[i].angle = PI - _snake[i].angle;
			}
			if (_snake[i].y - _snake[i].radius < 0)
			{
				_snake[i].y = _snake[i].radius;
				_snake[i].angle = PI2 - _snake[i].angle;
			}
			if (_snake[i].y + _snake[i].radius > WINSIZEY)
			{
				_snake[i].y = WINSIZEY - _snake[i].radius;
				_snake[i].angle = PI2 - _snake[i].angle;
			}

		}
		else //�����̸�
		{
			//�������� �������� Ŀ���� == ȸ���ߴ�
			if (_snake[i].radius * 2 < getDistance(_snake[i].x, _snake[i].y, _snake[i - 1].x, _snake[i - 1].y))
			{
				//�ٷ� �� �ջ���� ������ �����´�
				_snake[i].angle = getAngle(_snake[i].x, _snake[i].y, _snake[i - 1].x, _snake[i - 1].y);

				//�տ� �Ӹ� �Ǵ� ������ ������ ��ŭ �� �о��༭ ���ս� ���´� �� �� �� �ּ� ó���ϰ� ������ ��׷���
				_snake[i].x = _snake[i - 1].x - (cosf(_snake[i].angle) * (_snake[i].radius + _snake[i - 1].radius));
				_snake[i].y = _snake[i - 1].y - (-sinf(_snake[i].angle) * (_snake[i].radius + _snake[i - 1].radius));
			}
			_snake[i].x += cosf(_snake[i].angle) * _snake[i].speed;
			_snake[i].y += -sinf(_snake[i].angle) * _snake[i].speed;
		}
	}
}
