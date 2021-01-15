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
{ // 게임 시작
	gameNode::init();

	_p1mode = NORMAL;	_p2mode = NORMAL; // 노멀

	_player1 = RectMakeCenter(WINSIZEX / 2 - 400, WINSIZEY / 2, 100, 50); // 플레이어 사각형
	_player2 = RectMakeCenter(WINSIZEX / 2 + 400, WINSIZEY / 2, 100, 50);
	
	_obstacle = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 20, 100); //중간 장애물

	for (int i = 0; i < BULLETMAX; i++)
	{ // 총알 상태(기본값)
		_bulletP1[i].isFire = false;		_bulletP2[i].isFire = false;
		_bulletP1[i].isYudo = false;		_bulletP2[i].isYudo = false;
		_bulletP1[i].betrayed = false;		_bulletP2[i].betrayed = false;
		_bulletP1[i].x = 10; _bulletP2[i].x = -10; // 쏠때 부여받으니 안둬도 될거같긴 한데 일단..
		_bulletP1[i].y = 0; _bulletP2[i].y = 0;
	}

	_backGauge = RectMakeCenter(WINSIZEX / 2 - 300, 70, 400, 50); // 게이지
	_frontGauge = RectMakeCenter(WINSIZEX / 2 - 300, 70, 400, 50);
	_backGauge2 = RectMakeCenter(WINSIZEX / 2 + 300, 70, 400, 50);
	_frontGauge2 = RectMakeCenter(WINSIZEX / 2 + 300, 70, 400, 50);

	_r = 0;	_g = 255; // 초기 색상
	_r2 = 0;	_g2 = 255;

	_direction = 1; // 장애물 방향 (+1/-1)

	_reloadCount1 = _reloadCount2 = 0; // 장전카운트
	
	_isDeadP1 = _isDeadP2 = _canUltiP1 = _canUltiP2 = _effectOn = false;
	// 죽었는지랑 궁쏠수 있는지(이건 노랑피때 활성화됨) 이펙트켜졌는지

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


	_reloadCount1++; _reloadCount2++; // 재장전카운트

	//유도탄 감지 범위용 사각형(가상) p1이나 p2에 붙어서 너비 높이 300만큼 만듦
	_bigRect1 = RectMakeCenter((_player1.left + _player1.right) / 2, (_player1.top + _player1.bottom) / 2, 300, 300);
	_bigRect2 = RectMakeCenter((_player2.left + _player2.right) / 2, (_player2.top + _player2.bottom) / 2, 300, 300);

	if (!_isDeadP1 && !_isDeadP2) // 둘다 살아있을때
	{
		if (_ultiCount1 < 300) _ultiCount1++;
		if (_ultiCount2 < 300) _ultiCount2++;
		//궁쿨
		if (_obstacle.top <= 0) _direction *= -1; // 천장치면 방향전환
		if (_obstacle.bottom >= WINSIZEY) _direction *= -1; // 바닥치면 방향전환
		OffsetRect(&_obstacle, 0, 5 * _direction); // 장애물 이동

		keyControl();

		bulletMove();

		collision();		collision2();

		collisionObstacle();

		Yudo();		Yudo2();
		// 각종함수 실행(밑에)
		
		if (_frontGauge.right - _frontGauge.left < 250) { _canUltiP1 = true; }
		if (_frontGauge2.right - _frontGauge2.left < 250) { _canUltiP2 = true; }
		// 궁쓸수 있는지
		if (_frontGauge.right <= _frontGauge.left)	_isDeadP1 = true;
		if (_frontGauge2.right <= _frontGauge2.left)	_isDeadP2 = true;
		// 피 다 닳으면 죽음
	}
	if (_isDeadP1 && !_effectOn)
	{
		_effectOn = true;
		_reloadCount1 = 0; // 재활용.. 어차피 죽었으니까
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
		// 죽었을떄 R로 재시작

}

//제발 여기다 그려라 좀...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ 위에 건들지 마라 ==============================
	   	
	// 판
	Rectangle(backDC, 20, 110, WINSIZEX / 2 - 50, WINSIZEY - 20);
	Rectangle(backDC, WINSIZEX / 2 + 50, 110, WINSIZEX - 20, WINSIZEY - 20);

	// 장애물
	Rectangle(backDC, _obstacle);

	if (!_isDeadP1)
	{
		if (_p1mode == NORMAL ||
			(_p1mode != NORMAL && _reloadCount1 > 30))
		{ // p1쏠수있는 상태에서 출력(짙게)
			HBRUSH brush = CreateSolidBrush(RGB(110, 110, 190));
			Rectangle(backDC, _player1);
			FillRect(backDC, &_player1, brush);
			DeleteObject(brush);
		}
		else
		{ // p1쏠수없는 상태에서 출력(옅게)
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
		{ // p2쏠수있는 상태에서 출력(짙게)
			HBRUSH brush = CreateSolidBrush(RGB(190, 110, 110));
			Rectangle(backDC, _player2);
			FillRect(backDC, &_player2, brush);
			DeleteObject(brush);
		}
		else
		{ // p2쏠수없는 상태에서 출력(옅게)
			HBRUSH brush = CreateSolidBrush(RGB(255, 210, 210));
			Rectangle(backDC, _player2);
			FillRect(backDC, &_player2, brush);
			DeleteObject(brush);
		}
	}
		
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (!_bulletP1[i].isFire) continue; // isFire가 false면 출력X
		if (_bulletP1[i].isYudo) 
		{// 유도탄이면 파랑색사각형 (색칠을 사각형만 할 줄 알아서 사각형)
			HBRUSH brush = CreateSolidBrush(RGB(0, 0, 255));
			Ellipse(backDC, _bulletP1[i].rc);
			FillRect(backDC, &_bulletP1[i].rc, brush);
			DeleteObject(brush);
		}
		else Ellipse(backDC, _bulletP1[i].rc);	 // 아니면 그냥 원
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

	Rectangle(backDC, _backGauge); // 체력바뒷칸
	Rectangle(backDC, _backGauge2);

	HBRUSH brush = CreateSolidBrush(RGB(_r2, _g2, 0));
	Rectangle(backDC, _frontGauge2);
	FillRect(backDC, &_frontGauge2, brush);
	DeleteObject(brush); // 체력바앞칸(색상에 따라 출력)
	
	brush = CreateSolidBrush(RGB(_r, _g, 0));
	Rectangle(backDC, _frontGauge);
	FillRect(backDC, &_frontGauge, brush);
	DeleteObject(brush);

	char str[256]; // 투머치토커

	sprintf_s(str, "궁 설명 : 모든 총알이");
	TextOut(backDC, WINSIZEX/2 - 70 , 30, str, strlen(str));
	sprintf_s(str, "상대를 향합니다.");
	TextOut(backDC, WINSIZEX / 2 - 40, 50, str, strlen(str));

	sprintf_s(str, "스페이스: 발사 /WASD이동 /  Q:모드전환 / E:궁(노랑피이하)");
	TextOut(backDC, 20, WINSIZEY - 20, str, strlen(str));
	sprintf_s(str, "엔터: 발사 / (NumPad) 8456이동 / 7:모드전환 / 9:궁(노랑피이하)");
	TextOut(backDC, 590, WINSIZEY - 20, str, strlen(str));
	

	if (_canUltiP1)
	{ // 궁체크
		sprintf_s(str, "궁쿨 (0 이면 궁온) : %d", (300 - _ultiCount1)/10);
		TextOut(backDC, 20, 20, str, strlen(str));
	}
	if (_canUltiP2)
	{
		sprintf_s(str, "궁쿨 (0 이면 궁온): %d", (300 - _ultiCount2)/10);
		TextOut(backDC, WINSIZEX - 200, 20, str, strlen(str));
	}
	

	switch (_p1mode)
	{ // 모드별로 글씨출력
	case NORMAL: sprintf_s(str, "단발 모드"); break;
	case MULTI: sprintf_s(str, "멀티샷 모드"); break;
	case YUDO: sprintf_s(str, "유도탄 모드"); break;
	}
	TextOut(backDC, 320, 20, str, strlen(str));

	switch (_p2mode)
	{
	case NORMAL: sprintf_s(str, "단발 모드"); break;
	case MULTI: sprintf_s(str, "멀티샷 모드"); break;
	case YUDO: sprintf_s(str, "유도탄 모드"); break;
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
	{ // 죽었을때 출력
		sprintf_s(str, "PLAYER2 WINS!");
		TextOut(backDC, WINSIZEX / 2 - 55, WINSIZEY / 2, str, strlen(str));
		sprintf_s(str, "재시작하려면 'R'키를 누르세요");
		TextOut(backDC, WINSIZEX / 2 - 110, WINSIZEY / 2 + 20, str, strlen(str));
	}
	if (_isDeadP2)
	{
		sprintf_s(str, "PLAYER1 WINS!");
		TextOut(backDC, WINSIZEX / 2 - 55, WINSIZEY / 2, str, strlen(str));
		sprintf_s(str, "재시작하려면 'R'키를 누르세요");
		TextOut(backDC, WINSIZEX / 2 - 110, WINSIZEY / 2 + 20, str, strlen(str));
	}



	//================= 아래도 건들지 마라 ==============================
	this->getBackBuffer()->render(hdc, 0, 0);
}

void playGround::keyControl() // 키 콘트롤
{// 이동키 <- 경계 닿지 않았을때만 작동
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

	// 모드전환 (스위치문)
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

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) bulletFireP1(); // 쏘기
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN)) bulletFireP2();


	if (KEYMANAGER->isOnceKeyDown('E') && _ultiCount1 >= 300 && _canUltiP1) ultiP1(); // 궁쏘기
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD9) && _ultiCount2 >= 300 && _canUltiP2) ultiP2();

}

void playGround::bulletFireP1() // player1의 총알 나갈떄
{
	switch (_p1mode) // 스위치문으로 구분
	{
	case NORMAL:
	{ // 노멀할떄
		for (int i = 0; i < BULLETMAX; i++)
		{
			if (_bulletP1[i].isFire) continue; // 발사중인 총알은 이용X
			_bulletP1[i].rc = RectMakeCenter(_player1.right + 5,
				(_player1.top + _player1.bottom) / 2, 10, 10); // 총알 만들기
			_bulletP1[i].isFire = true; // 발사중
			_bulletP1[i].x = 10; // x속도 할당
			_bulletP1[i].y = 0; // y속도 할당
			_bulletP1[i].isYudo = false; // 유도탄아님
			_bulletP1[i].betrayed = false; // 적궁맞은탄(배신당한 탄) 아님
			break;
		}
	}
	break;
	case MULTI:
	{
		if (_reloadCount1 <= 30) break; // 장전쿨 이하면 작동안함
		else _reloadCount1 = 0; // 쏘면 쿨돌음
		for (int j = 0; j < 5; j++)
		{ // 5발씩
			for (int i = 0; i < BULLETMAX; i++)
			{
				if (_bulletP1[i].isFire) continue; // 발사중인 총알은 이용X
				_bulletP1[i].rc = RectMakeCenter(_player1.right + 5,
					(_player1.top + _player1.bottom) / 2, 10, 10); // 총알 만들기
				_bulletP1[i].isFire = true; // 발사중
				if (j == 0 || j == 4) _bulletP1[i].x = 6;
				else if (j == 1 || j == 3) _bulletP1[i].x = 8;
				else _bulletP1[i].x = 10;  // x속도 할당(j에 따라)
				_bulletP1[i].y = 10 - j * 5; // y속도 할당(j에 따라)
				_bulletP1[i].isYudo = false; // 유도탄아님
				_bulletP1[i].betrayed = false; // 적궁맞은탄(배신당한 탄) 아님
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
			if (_bulletP1[i].isFire) continue; // 발사중인 총알은 이용X
			_bulletP1[i].rc = RectMakeCenter(_player1.right + 5,
				(_player1.top + _player1.bottom) / 2, 10, 10); // 총알 만들기
			_bulletP1[i].isFire = true; // 발사중
			_bulletP1[i].x = 10;  // x속도 할당
			_bulletP1[i].y = 0; // y속도 할당
			_bulletP1[i].isYudo = true; // 유도탄임
			_bulletP1[i].betrayed = false; // 적궁맞은탄(배신당한 탄) 아님
			break;
		}
	}
	break;
	}
}

void playGround::bulletFireP2() // player2의 총알 나갈떄 (주석은 위 참고)
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
	{ // 화면밖으로 가면 isfire 아님
		if (_bulletP1[i].rc.left > WINSIZEX || _bulletP1[i].rc.right < 0 ||
			_bulletP1[i].rc.top < 0 || _bulletP1[i].rc.bottom > WINSIZEY) _bulletP1[i].isFire = false;
		if (!_bulletP1[i].isFire) continue; // fire아닌건 움직일 필요 없으니까
		_bulletP1[i].rc.left += _bulletP1[i].x; // x축으로 x값만큼
		_bulletP1[i].rc.right += _bulletP1[i].x;
		_bulletP1[i].rc.top += _bulletP1[i].y; // y축으로 y값만큼
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
		if (!_bulletP1[i].isFire) continue; // 안쏘는 중인건 부딪히지 않음
		if (IntersectRect(&temp, &_bulletP1[i].rc, &_player2)) // 부딪혔다
		{
			_bulletP1[i].isFire = false; // 더이상 안부딪히게 + 쏜거 없애야하니까 false로
			if (_frontGauge2.left >= _frontGauge2.right) return;
			_frontGauge2.left += 10; // 죽으면(게이지 좌우 닿으면) 리턴해버리고 아니면 게이지왼쪽을 10이동
			if (_frontGauge2.right - _frontGauge2.left < 250){	_r2 = 255;	_g2 = 255;} // 노랑피
			if (_frontGauge2.right - _frontGauge2.left < 100){	_r2 = 255;	_g2 = 0;} // 빨피
			break;
		}
	}
	for (int i = 0; i < BULLETMAX; i++)
	{ // 내 총알 중 배신중(상대궁으로)인게 닿으면.. 총알 클래스에 '소속'을 뒀으면 더 좋았을듯
		if (!_bulletP2[i].isFire || !_bulletP2[i].betrayed) continue; // 쏘는중이아니거나 배신총아니면 패스
		if (IntersectRect(&temp, &_bulletP2[i].rc, &_player2)) // 부딪혔다
		{
			_bulletP2[i].isFire = false; // 안쏘게
			_bulletP2[i].betrayed = false; // 배신끝
			if (_frontGauge2.left >= _frontGauge2.right) return; //이하는 위와 같음
			_frontGauge2.left += 10;
			if (_frontGauge2.right - _frontGauge2.left < 250) { _r2 = 255;	_g2 = 255; }
			if (_frontGauge2.right - _frontGauge2.left < 100) { _r2 = 255;	_g2 = 0; }
			break;
		}
	}
}

void playGround::collision2()
{// collision의 주석 참고
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
{//장애물과 충돌시
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (!_bulletP1[i].isFire) continue; // 이즈파이어아니면 패스
		if (IntersectRect(&temp, &_bulletP1[i].rc, &_obstacle))	_bulletP1[i].isFire = false; // 충돌시 이즈파이어면 끔
	}
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (!_bulletP2[i].isFire) continue; // 위와 같음
		if (IntersectRect(&temp, &_bulletP2[i].rc, &_obstacle))	_bulletP2[i].isFire = false;		
	}
}

void playGround::Yudo()
{ // 유도 감지하는거
	for (int i = 0; i < BULLETMAX; i++)
	{
		if (!_bulletP1[i].isFire || !_bulletP1[i].isYudo) continue; // 쏘는중아니거나 유도가 아니면 해당안됨
		if (IntersectRect(&temp, &_bulletP1[i].rc, &_bigRect2))
		{ // 빅렉트 = 유도탄 감지용 큰사각형 .. 무튼 빅렉트랑 탄알이 겹치면
			_yudoFrom = { (float)(_bulletP1[i].rc.left + _bulletP1[i].rc.right) / 2, (float)(_bulletP1[i].rc.top + _bulletP1[i].rc.bottom) / 2 };
			_yudoTo = { (float)(_player2.left + _player2.right) / 2, (float)(_player2.top + _player2.bottom) / 2 };
			// 유도탄 출발점은 총알 중점으로, 유토탄 도달점은 플레이어 중점으로.
			// _yudoFrom이랑 _yudoTo는 POINTFLOAT로 {x, y}꼴임
			angle = calcAngleFromPoints(_yudoFrom, _yudoTo); // 두 점간 각도 구함
			_bulletP1[i].x = -10 * cos(angle); // x속도는 -10곱하기 코사인(각도)
			_bulletP1[i].y = -10 * sin(angle); // y는 사인
		}
	}
}

void playGround::Yudo2()
{ // 주석은 Yudo참고
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
{ // 궁쏘기
	for (int i = 0; i < BULLETMAX; i++)
	{ // P2의 경우 총알
		if (!_bulletP2[i].isFire) continue; // 발사중이 아니면 패스
		_yudoFrom = { (float)(_bulletP2[i].rc.left + _bulletP2[i].rc.right) / 2, (float)(_bulletP2[i].rc.top + _bulletP2[i].rc.bottom) / 2 };
		_yudoTo = { (float)(_player2.left + _player2.right) / 2, (float)(_player2.top + _player2.bottom) / 2 };
		angle = calcAngleFromPoints(_yudoFrom, _yudoTo);
		_bulletP2[i].x = -10 * cos(angle);
		_bulletP2[i].y = -10 * sin(angle);
		// 이상은 Yudo함수에서 썼던 그대로임. 각도를 구해서 10의 속도로서 글로 보냄
		_bulletP2[i].betrayed = true; // 배신했다 true로
		_bulletP2[i].isYudo = false; // 유도탄이면 일반탄으로
	}

	for (int i = 0; i < BULLETMAX; i++)
	{
		if (!_bulletP1[i].isFire) continue; // 발사중이 아니면 패스
		_yudoFrom = { (float)(_bulletP1[i].rc.left + _bulletP1[i].rc.right) / 2, (float)(_bulletP1[i].rc.top + _bulletP1[i].rc.bottom) / 2 };
		_yudoTo = { (float)(_player2.left + _player2.right) / 2, (float)(_player2.top + _player2.bottom) / 2 };
		angle = calcAngleFromPoints(_yudoFrom, _yudoTo);
		_bulletP1[i].x = -10 * cos(angle);
		_bulletP1[i].y = -10 * sin(angle); // 이상은 Yudo함수에서 썼던 그대로임. 각도를 구해서 10의 속도로서 글로 보냄
		_bulletP1[i].betrayed = false; // 혹시 배신한탄이면 다시 배신하게끔
		_bulletP1[i].isYudo = false; // 유도탄이면 일반탄으로
	}

	_ultiCount1 = 0;
}

void playGround::ultiP2()
{ // 주석은 ultiP1참고
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
{ // 두 점(포인트플로트)간 각도 구하는 함수(from 구글링)
	float fAngle;
	float fdX = _ptFirst.x - _ptSecond.x;
	float fdY = _ptFirst.y - _ptSecond.y;

	float dRad = atan2(fdY, fdX);
	return dRad;
}
