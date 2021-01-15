#include "stdafx.h"
#include "playGround.h"

playGround::playGround()
{
}


playGround::~playGround()
{
}

//초기화는 여기다 하세요
HRESULT playGround::init()
{
	gameNode::init();

	_isDead = _isDeadAI = _isNorang= false;

	_ourHPBack = RectMake(50, 50, 400, 50); // 400으로 하고 40씩 줄이자
	_AIHPBack = RectMake(WINSIZEX - 450, 50, 400, 50);
	_ourHP = RectMake(50, 50, 400, 50); // 400으로 하고 40씩 줄이자
	_AIHP = RectMake(WINSIZEX - 450, 50, 400, 50);

	_reloadBack = RectMake(50, 120, 200, 20);
	_reloadAIBack = RectMake(WINSIZEX - 250, 120, 200, 20);
	_reload = RectMake(50, 120, 0, 20);
	_reloadAI = RectMake(WINSIZEX - 50, 120, 0, 20);
	// 각종 체력바나 장전대기바

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

		_track[i].speed = _speed; // 총알이랑 트랙 배열수 같게해서 겸사겸사 이용
		_track[i].radius = TRACKSIZE;
		_track[i].gravity = 0; // 얜 이즈파이어생략

		_trackAI[i].speed = _speed;
		_trackAI[i].radius = TRACKSIZE;
		_trackAI[i].gravity = 0;
	}

	_angleDirection = 1; // AI각도가 올라가고있는지 감소하고있는지(그냥 불값으로 썼어도 됐을듯..)
	trackSet(); // 초기 한 번 그려준다

	return S_OK;
}

//메모리 해제는 여기다 하세요
void playGround::release()
{
	gameNode::release();


}

//연산(계산)은 여기다 하세요
void playGround::update()
{
	gameNode::update();
	if (!_isDead && !_isDeadAI)
	{
		if (_reload.left + 200 > _reload.right) _reload.right += 2;
		if (_reloadAI.left + 200 > _reloadAI.right) _reloadAI.left -= 2;
		if (_reloadAI.left + 200 > _reloadAI.right && _isNorang) _reloadAI.left -= 8; // 노랑이면 추가로

		if (_AIHP.right - _AIHP.left < 200 && _AIHP.right - _AIHP.left >= 100)_isNorang = true;

		if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _cannon.center.x > CANNONRADIUS)
		{
			_cannon.center.x -= 3;
			if (_cannon.angle < PI / 2) _cannon.angle = PI - _cannon.angle; // 방향전환
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _cannon.center.x < WINSIZEX / 2 - 100)
		{
			_cannon.center.x += 3;
			if (_cannon.angle > PI / 2) _cannon.angle = PI - _cannon.angle; // 방향전환
		}

		if (KEYMANAGER->isStayKeyDown(VK_UP) && _cannon.angle < PI / 2 - 0.20)	{_cannon.angle += 0.04f;}
		if (KEYMANAGER->isStayKeyDown(VK_UP) && _cannon.angle > PI / 2 + 0.20)	{_cannon.angle -= 0.04f;}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _cannon.angle < PI / 2 && _cannon.angle > 0.50) {_cannon.angle -= 0.04f;}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _cannon.angle > PI / 2 && _cannon.angle < 2.64) {_cannon.angle += 0.04f;}

		if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && _reload.left + 200 <= _reload.right) bulletFire();

		//포신 끝점 (어제 덕호가 목에서 피나오게 설명하면서 돌아다니던 그것)
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

//제발 여기다 그려라 좀...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ 위에 건들지 마라 ==============================
	

	Rectangle(backDC, _reloadBack);
	Rectangle(backDC, _reloadAIBack);
	Rectangle(backDC, _AIHPBack);
	Rectangle(backDC, _ourHPBack);

	if (_ourHP.right - _ourHP.left >= 200)
	{ // 초록
		HBRUSH brush = CreateSolidBrush(RGB(0, 255, 0));		HBRUSH oldbrush = (HBRUSH)SelectObject(backDC, brush);
		Rectangle(backDC, _ourHP);		SelectObject(backDC, oldbrush);		DeleteObject(brush);
	}
	else if (_ourHP.right - _ourHP.left >= 100)
	{ // 노랑
		HBRUSH brush = CreateSolidBrush(RGB(255, 212, 0));		HBRUSH oldbrush = (HBRUSH)SelectObject(backDC, brush);
		Rectangle(backDC, _ourHP);		SelectObject(backDC, oldbrush);		DeleteObject(brush);
	}
	else
	{ // 빨강
		HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));		HBRUSH oldbrush = (HBRUSH)SelectObject(backDC, brush);
		Rectangle(backDC, _ourHP);		SelectObject(backDC, oldbrush);		DeleteObject(brush);
	}

	if (_AIHP.right - _AIHP.left >= 200)
	{ // 초록
		HBRUSH brush = CreateSolidBrush(RGB(0, 255, 0));		HBRUSH oldbrush = (HBRUSH)SelectObject(backDC, brush);
		Rectangle(backDC, _AIHP);		SelectObject(backDC, oldbrush);		DeleteObject(brush);
	}
	else if (_AIHP.right - _AIHP.left >= 100)
	{ // 노랑
		HBRUSH brush = CreateSolidBrush(RGB(255, 212, 0));		HBRUSH oldbrush = (HBRUSH)SelectObject(backDC, brush);
		Rectangle(backDC, _AIHP);		SelectObject(backDC, oldbrush);		DeleteObject(brush);
	}
	else
	{ // 빨강
		HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));		HBRUSH oldbrush = (HBRUSH)SelectObject(backDC, brush);
		Rectangle(backDC, _AIHP);		SelectObject(backDC, oldbrush);		DeleteObject(brush);
	}

	// 재장전 바
	HBRUSH brush = CreateSolidBrush(RGB(200, 200, 200));	HBRUSH oldbrush = (HBRUSH)SelectObject(backDC, brush);
	Rectangle(backDC, _reload);	Rectangle(backDC, _reloadAI);
	SelectObject(backDC, oldbrush);	DeleteObject(brush);


	// 내 캐논
	brush = CreateSolidBrush(RGB(220, 220, 255));	oldbrush = (HBRUSH)SelectObject(backDC, brush);
	EllipseMakeCenter(backDC, _cannon.center.x, _cannon.center.y, 2 * CANNONRADIUS, 2 * CANNONRADIUS);
	SelectObject(backDC, oldbrush);	DeleteObject(brush);
	LineMake(backDC, _cannon.center.x, _cannon.center.y, _cannon.cannonEnd.x, _cannon.cannonEnd.y);

	// 쟤 캐논
	brush = CreateSolidBrush(RGB(255, 220, 220));	oldbrush = (HBRUSH)SelectObject(backDC, brush);
	EllipseMakeCenter(backDC, _cannonAI.center.x, _cannonAI.center.y, 2 * CANNONRADIUS, 2 * CANNONRADIUS);
	SelectObject(backDC, oldbrush);	DeleteObject(brush);
	LineMake(backDC, _cannonAI.center.x, _cannonAI.center.y, _cannonAI.cannonEnd.x, _cannonAI.cannonEnd.y);

	for (int i = BULLETMAX-1; i >=0; i=i-1)
	{ // 내총알
		if (!_bullet[i].isFire) continue;
		HBRUSH brush = CreateSolidBrush(RGB(200, 200, 255));	HBRUSH oldbrush = (HBRUSH)SelectObject(backDC, brush);
		EllipseMakeCenter(backDC, _bullet[i].x, _bullet[i].y, 2*BULLETRADIUS, 2*BULLETRADIUS);
		SelectObject(backDC, oldbrush);	DeleteObject(brush);
	}

	for (int i = BULLETMAX - 1; i >= 0; i = i - 1)
	{ // 쟤총알
		if (!_bulletAI[i].isFire) continue;
		HBRUSH brush = CreateSolidBrush(RGB(255, 200, 200));	HBRUSH oldbrush = (HBRUSH)SelectObject(backDC, brush);
		EllipseMakeCenter(backDC, _bulletAI[i].x, _bulletAI[i].y, 2 * BULLETRADIUS, 2 * BULLETRADIUS);
		SelectObject(backDC, oldbrush);	DeleteObject(brush);
	}
	
	char str[256];
	if (_isDead || _isDeadAI)
	{
		sprintf_s(str, "게임오바");
		TextOut(backDC, WINSIZEX / 2-50, WINSIZEY / 2-20, str, strlen(str));
		sprintf_s(str, "재시작은모다? ENTER다.");
		TextOut(backDC, WINSIZEX / 2 - 100, WINSIZEY / 2, str, strlen(str));
	}

	if (_isNorang)
	{
		sprintf_s(str, "레이지 모드 (무친연사속도)");
		TextOut(backDC, WINSIZEX - 200, 20, str, strlen(str));
	}


	// 트랙 안보이게 주석처리
	/*
	for (int i = BULLETMAX-1; i >=0 ; i--)
	{
		EllipseMakeCenter(backDC, _track[i].x, _track[i].y, _track[i].radius * 2, _track[i].radius * 2);
		EllipseMakeCenter(backDC, _trackAI[i].x, _trackAI[i].y, _trackAI[i].radius * 2, _trackAI[i].radius * 2);
	} */
	
	
	//================= 아래도 건들지 마라 ==============================
	this->getBackBuffer()->render(hdc, 0, 0);
}

void playGround::bulletFire()
{ // 내 총알 발사
	for (int i = 0; i < BULLETMAX; i++)
	{
		_reload.right = _reload.left; // 장전 초기화
		if (_bullet[i].isFire) continue; // 안쏘는걸 고른다
		_bullet[i].isFire = true; // 쏜다
		_bullet[i].angle = _cannon.angle; // 앵글
		_bullet[i].x = cosf(_cannon.angle) * (_cannon.cannon + 3) + _cannon.center.x; // 위치
		_bullet[i].y = -sinf(_cannon.angle) * (_cannon.cannon + 3) + _cannon.center.y;
		break;
	}
}

void playGround::bulletFireAI()
{ // 쟤 총알발사 (주석은 위와 같음)
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
{ // 총알이동
	for (int i = 0; i < BULLETMAX; i++)
	{ // 값 부여
		if (!_bullet[i].isFire) continue;
		_bullet[i].gravity += 0.08;
		_bullet[i].x += cosf(_bullet[i].angle) * _speed;
		_bullet[i].y += -sinf(_bullet[i].angle) * _speed + _bullet[i].gravity;

		//화면 왼쪽으로 나가면
		if (_bullet[i].x + _bullet[i].radius < 0)
		{_bullet[i].isFire = false;			_bullet[i].gravity = 0;}

		//화면 오른쪽으로 나가면
		if (_bullet[i].x - _bullet[i].radius > WINSIZEX)
		{_bullet[i].isFire = false;			_bullet[i].gravity = 0;}

		//화면 위쪽으로 나가면
		if (_bullet[i].y - _bullet[i].radius < 0)
		{_bullet[i].isFire = false;			_bullet[i].gravity = 0;}

		//화면 아래쪽으로 나가면
		if (_bullet[i].y - _bullet[i].radius > WINSIZEY)
		{_bullet[i].isFire = false;			_bullet[i].gravity = 0;}

	}

	for (int i = 0; i < BULLETMAX; i++)
	{ // 쟤 총알 이동
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
{ // 궤도 (저번에 했던거 복붙임)
	_track[0].x = cosf(_cannon.angle) * (_cannon.cannon + 3) + _cannon.center.x;
	_track[0].y = -sinf(_cannon.angle) * (_cannon.cannon + 3) + _cannon.center.y;
	_track[0].angle = _cannon.angle;
	float gravity = 0.08f;
	for (int i = 1; i < BULLETMAX; i++)
	{
		_track[i].x = _track[0].x + (4*i) * cosf(_track[0].angle) * _speed;
		_track[i].y = _track[0].y + (4*i) * (-sinf(_track[0].angle) * _speed)+ (4*i)*(4*i)/2* gravity;
		if (_track[i].y > WINSIZEY + TRACKSIZE) { _track[i].x = WINSIZEX + 10; } // 밖으로 치워버림
	}
}

void playGround::trackSetAI()
{ // 쟤 궤도(미사일 쏠지 결정하는데 필요)
	_trackAI[0].x = cosf(_cannonAI.angle) * (_cannonAI.cannon + 3) + _cannonAI.center.x;
	_trackAI[0].y = -sinf(_cannonAI.angle) * (_cannonAI.cannon + 3) + _cannonAI.center.y;
	_trackAI[0].angle = _cannonAI.angle;
	float gravity = 0.08f;
	for (int i = 1; i < BULLETMAX; i++)
	{
		_trackAI[i].x = _trackAI[0].x + (4 * i) * cosf(_trackAI[0].angle) * _speed;
		_trackAI[i].y = _trackAI[0].y + (4 * i) * (-sinf(_trackAI[0].angle) * _speed) + (4 * i)*(4 * i) / 2 * gravity;
		if (_trackAI[i].y > WINSIZEY + TRACKSIZE) { _trackAI[i].x = WINSIZEX + 10;} // 밖으로 치워버림
	}
}

void playGround::AIangleSet()
{
	if (_cannon.center.x > _cannonAI.center.x && _cannonAI.angle > PI / 2)
	{ // 내x값이 쟤x값보다 크고 쟤 앵글이 90도보다 큰 경우 돌려줘야함
		_cannonAI.angle = PI - _cannonAI.angle;
	}
	if (_cannon.center.x < _cannonAI.center.x && _cannonAI.angle < PI / 2)
	{
		_cannonAI.angle = PI - _cannonAI.angle;
	} // 내가 쟤보다 오른쪽 or 왼쪽으로 가면 좌우 바꿈

	if (_angleDirection == 1)
	{ // 앵글방향이 1이면 올리고
		_cannonAI.angle += 0.02f;
	}
	else
	{ // 아니면 내린다
		_cannonAI.angle -= 0.02f;
	}
	if (_cannonAI.angle >= PI / 2 - 0.2 && _cannonAI.angle <= PI / 2 + 0.2) _angleDirection *= -1;
	if (_cannonAI.angle >= 2.74 || _cannonAI.angle <= 0.4) _angleDirection *= -1;
	// 최소각이나 최대각에 도달하면 앵글방향을 반대로 바꾼다

	for (int i = 0; i < BULLETMAX; i++)
	{ // 궤도(작은 점)이 내 캐논에 닿았고 장전완료됐으면
		if (getDistance(_trackAI[i].x, _trackAI[i].y, _cannon.center.x, _cannon.center.y)<CANNONRADIUS			
			&& _reloadAI.left+200 <= _reloadAI.right)
		{
			_reloadAI.left = _reloadAI.right; // 장전 초기화
			bulletFireAI(); // 발사
		}
	}


}

void playGround::collide()
{// 피격
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
{// 회피기동
	_bigRect = RectMakeCenter(_cannonAI.center.x, _cannonAI.center.y, 500, 300);
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (_bullet[i].x > _bigRect.left && _bullet[i].x < _bigRect.right &&
			_bullet[i].y > _bigRect.top && _bullet[i].y < _bigRect.bottom &&
			_bullet[i].isFire) // 감지범위에 총알이 있으면
		{
			_predictX = _bullet[i].x + (WINSIZEY - _bullet[i].y) / tanf(_bullet[i].angle); // 도달x값 예측
			if (_predictX > _cannonAI.center.x) _cannonAI.center.x -= 3; // 예측에따라 이동
			if (_predictX <= _cannonAI.center.x && _cannonAI.center.x < WINSIZEX - CANNONRADIUS) _cannonAI.center.x += 3;
			break;
		}
	}

	_peaceCount = 0;
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (_bullet[i].x > _bigRect.left && _bullet[i].x < _bigRect.right &&
			_bullet[i].y > _bigRect.top && _bullet[i].y < _bigRect.bottom &&
			_bullet[i].isFire) // 발사중인게 빅렉트에 충돌했니
		{
			_peaceCount++; // 충돌한게 하나라도 있으면 _peaceCount는 1
			break;
		}
	}
	if (_peaceCount == 0) _peace = true; // 충돌한게 없으면 평화
	else _peace = false; // 아니면 안평화
	if (_peace) // 평화면 제자리로
	{
		if (_cannonAI.center.x <WINSIZEX - 200)	_cannonAI.center.x += 3;
		if (_cannonAI.center.x > WINSIZEX - 200) _cannonAI.center.x -= 3;
	}
}