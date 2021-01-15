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

	_cannon.angle = PI / 2;
	_cannon.cannon = 100;
	_cannon.radius = 100;
	_cannon.center.x = WINSIZEX / 2;
	_cannon.center.y = WINSIZEY;

	for (int i = 0; i < BULLETMAX; i++)
	{
		_bullet[i].speed = _speed;
		_bullet[i].radius = 20;
		_bullet[i].isFire = false;
		_bullet[i].gravity = 0;

		_track[i].speed = _speed; // �Ѿ��̶� Ʈ�� �迭�� �����ؼ� ����� �̿�
		_track[i].radius = TRACKSIZE;
		_track[i].gravity = 0; // �� �������̾����
	}


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

	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _cannon.angle <= 3.04)
	{
		_cannon.angle += 0.04f;
		trackSet(); // ����Ű ������ �Լ��ߵ�
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _cannon.angle >= 0.08)
	{
		_cannon.angle -= 0.04f;
		trackSet(); // ����Ű ������ �Լ��ߵ�
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) bulletFire();

	//���� ���� (���� ��ȣ�� �񿡼� �ǳ����� �����ϸ鼭 ���ƴٴϴ� �װ�)
	_cannon.cannonEnd.x = cosf(_cannon.angle) * _cannon.cannon + _cannon.center.x;
	_cannon.cannonEnd.y = -sinf(_cannon.angle) * _cannon.cannon + _cannon.center.y;


	bulletMove();

}

//���� ����� �׷��� ��...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ ���� �ǵ��� ���� ==============================

	EllipseMakeCenter(backDC, _cannon.center.x, _cannon.center.y, 100, 100);
	LineMake(backDC, _cannon.center.x, _cannon.center.y, _cannon.cannonEnd.x, _cannon.cannonEnd.y);

	for (int i = BULLETMAX-1; i >=0; i=i-1)
	{
		if (!_bullet[i].isFire) continue;
		EllipseMakeCenter(backDC, _bullet[i].x, _bullet[i].y, _bullet[i].radius * 2, _bullet[i].radius * 2);
	}


	for (int i = BULLETMAX-1; i >=0 ; i--)
	{
		EllipseMakeCenter(backDC, _track[i].x, _track[i].y, _track[i].radius * 2, _track[i].radius * 2);
	}  // Ʈ���� �������̾� �������
	
	
	//================= �Ʒ��� �ǵ��� ���� ==============================
	this->getBackBuffer()->render(hdc, 0, 0);
}

void playGround::bulletFire()
{
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (_bullet[i].isFire) continue;

		_bullet[i].isFire = true;
		_bullet[i].x = cosf(_cannon.angle) * (_cannon.cannon + 3) + _cannon.center.x;
		_bullet[i].y = -sinf(_cannon.angle) * (_cannon.cannon + 3) + _cannon.center.y;
		_bullet[i].angle = _cannon.angle;

		break;
	}
}


void playGround::bulletMove()
{
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (!_bullet[i].isFire) continue;
		_bullet[i].gravity += 0.08;
		_bullet[i].x += cosf(_bullet[i].angle) * _speed;
		_bullet[i].y += -sinf(_bullet[i].angle) * _speed + _bullet[i].gravity;

		//ȭ�� �������� ������
		if (_bullet[i].x - _bullet[i].radius < 0)
		{
			_bullet[i].isFire = false;
			_bullet[i].gravity = 0;
		}

		//ȭ�� ���������� ������
		if (_bullet[i].x + _bullet[i].radius > WINSIZEX)
		{
			_bullet[i].isFire = false;
			_bullet[i].gravity = 0;
		}

		//ȭ�� �������� ������
		if (_bullet[i].y - _bullet[i].radius < 0)
		{
			_bullet[i].isFire = false;
			_bullet[i].gravity = 0;
		}

		//ȭ�� �Ʒ������� ������
		if (_bullet[i].y + _bullet[i].radius > WINSIZEY)
		{
			_bullet[i].isFire = false;
			_bullet[i].gravity = 0;
		}

	}
}

void playGround::trackSet()
{
	_track[0].x = cosf(_cannon.angle) * (_cannon.cannon + 3) + _cannon.center.x;
	_track[0].y = -sinf(_cannon.angle) * (_cannon.cannon + 3) + _cannon.center.y;
	_track[0].angle = _cannon.angle;	// ���������� _track[0]

	float gravity = 0.08f;

	for (int i = 1; i < BULLETMAX; i++)
	{
		_track[i].x = _track[0].x + (5*i) * cosf(_track[0].angle) * _speed;
		// �ӵ��� cos(angle)*spd�̹Ƿ� i�� ���ؼ� �����ϸ� i*cos(angle)*spd
		// ���л�� C�� �������� _track[0].x
		// 5�ֱ⸶�ٶ� i��� 5*i�� ����
		_track[i].y = _track[0].y + (5*i) * (-sinf(_track[0].angle) * _speed)+ (5*i)*(5*i)/2* gravity;
		// �ӵ��� -sin(angle)*spd + i*gravity�̹Ƿ� i�� ���ؼ� �����ϸ� -i*sin*spd + i^2/2*gravity
		// ���л�� C�� �������� _track[0].y
		// 5�ֱ⸶�ٶ� i��� 5*i�� ����. (i^2�� 25i^2)
		if (_track[i].y > WINSIZEY + TRACKSIZE) break;
	}
}
