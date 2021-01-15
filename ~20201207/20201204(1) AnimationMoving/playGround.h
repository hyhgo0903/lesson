#pragma once
#include "gameNode.h"

#define SONICWIDTH 70
#define SONICHEIGHT 84 // 계속쓰다 기억안날까봐 렉트크기 지정해놨음


enum SIVADIRECTION
{
	LEFT_RUN, // 달려
	RIGHT_RUN,
	LEFT_HANG, // 벽잡
	RIGHT_HANG,
	LEFT_IDLE, // 가만히
	RIGHT_IDLE,
	LEFT_ATTACK, // 공격
	RIGHT_ATTACK,
	LEFT_JUMP, // 떠있음
	RIGHT_JUMP
};

class playGround : public gameNode
{
private:
	image* _background; // 백그라운드에 오브젝트 같이 그려넣었음 편하게
	image* _sonicImg; // 소닉이미지
	SIVADIRECTION _direction; // 이넘

	RECT _sonicRc; // 소닉
	RECT _bottom; // 바닥
	RECT _object[6]; //오브젝트(0=집1, 1=집2, 2~4=오브젝트3개, 5=바닥)
	bool _objectIsNotCollide[6]; // 구조체로 만들었어야했는데 ㄲㅂ(바닥 충돌X)
	RECT _temp; // 충돌용
	
	char str[256]; // 글자 출력용
	int _attackReturn; // 어택중이면 돌아오게끔 리턴(어택쿨타임겸)

	int _count, _index;
	float _jumpPower; // 점프파워
	float _gravity; // 중력
	bool _onGround; // 땅에 있는지
	bool _isHang;	// 매달렸는지
	bool _isGapEum; // 매달렸을때 아예 잡은 경우랑 그냥 밀리는 경우를 나눔

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//초기화 전용 함수
	virtual void release();			//메모리 해제 함수
	virtual void update();			//연산 전용
	virtual void render(HDC hdc);	//그리기 전용

	void rectMove();		// 렉트이동
	void keyInput();		// 키매니저관련
	void animation();		// 애니메이숀
	void collision();		// 충돌
	void jumpingCheck();	// 바닥 꺼졌나 체크
	void hangingCheck();	// 매달렸나 체크
	void objectRegen();		// 없애버린 오브젝트(↓ + SPACE로) 복구

};

