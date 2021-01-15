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

	_degree = 180.0f;
	_radian = PI;
	

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

	
}

//제발 여기다 그려라 좀...
void playGround::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================ 위에 건들지 마라 ==============================

	char strRadian[256];
	char strDegree[256];

	sprintf_s(strRadian, "%.2f 라디안 값은 %.2f 디그리 값과 같다",
		_radian, _radian * (180 / PI)); // %.2f : 소수점 둘째자리까지 나옴
	TextOut(backDC, 50, 50, strRadian, strlen(strRadian));

	sprintf_s(strDegree, "%.2f 디그리 값은 %.2f 라디안 값과 같다",
		_degree, _degree * (PI / 180));
	TextOut(backDC, 50, 50, strDegree, strlen(strDegree));

	// sqrt() 느려서 가급적 안씀
	// r1+r2 > h면 충돌(이건 (2)번부터할거
	// AABB / OBB충돌



	
	//================= 아래도 건들지 마라 ==============================
	this->getBackBuffer()->render(hdc, 0, 0);
}
