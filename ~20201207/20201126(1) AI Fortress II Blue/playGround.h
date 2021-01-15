#pragma once
#include "gameNode.h"

#define PI 3.14f
#define BULLETMAX 70
#define TRACKSIZE 1
#define CANNONRADIUS 50
#define BULLETRADIUS 5

struct tagBullet
{
	float x, y;		//중점 x, y
	float speed;	//스피드
	float angle;	//각도
	float radius;	//반지름
	bool isFire;	//발쏴했니?
	float gravity;
};

struct tagCannon
{
	POINT center;		//캐논 중점
	POINT cannonEnd;	//캐논 포신 끝점
	float cannon;			//포신(?) 길이
	float angle;		//각도
};


class playGround : public gameNode
{
private:
	tagBullet _bullet[BULLETMAX];
	tagBullet _bulletAI[BULLETMAX];
	tagCannon _cannon;

	tagCannon _cannonAI;

	tagBullet _track[BULLETMAX];
	tagBullet _trackAI[BULLETMAX];

	RECT _ourHP;
	RECT _ourHPBack; // 체력바랑 체력바 뒤
	RECT _AIHP;
	RECT _AIHPBack; // 적체력바랑 체력바 뒤
	RECT _reload;
	RECT _reloadBack; // 리로드바랑 리로드바 뒤
	RECT _reloadAI;
	RECT _reloadAIBack; // 적 리로드바랑 리로드바 뒤

	RECT _temp; // 충돌판정용
	RECT _bigRect; // 감지용 사각형

	const int _speed = 8; // 총알 스피드는 여기서 (궤적도 같이)

	float _predictX; // 예상경로 x

	int _angleDirection; // AI각도가 올라가고있는지 감소하고있는지(그냥 불값으로 썼어도 됐을듯..)

	int _peaceCount; // 안전하면 복귀시키려고
	bool _peace; // 안전하면 복귀

	bool _isDead;
	bool _isDeadAI;

	bool _isNorang;

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//초기화 전용 함수
	virtual void release();			//메모리 해제 함수
	virtual void update();			//연산 전용
	virtual void render(HDC hdc);	//그리기 전용

	void bulletFire();
	void bulletFireAI();
	void bulletMove();

	void trackSet(); // 트랙세팅 함수
	void trackSetAI(); // AI의 트랙세팅 함수
	void AIangleSet(); // AI의 앵글조정 함수

	void collide(); //맞으면

	void evasion(); // 회피기동
};

