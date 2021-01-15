#pragma once
#include "gameNode.h"

struct tagBullet
{
	RECT rc;
	bool isFire;
	float x; // x속도
	float y; // y속도
	bool isYudo; // 유도탄인지?
	bool betrayed;
	// 상대 궁에 맞았는지? 처음부터 '소속'이라고 변수뒀으면 더 좋았을듯
};

enum PMODE
{ // 모드를 이넘문으로
	NORMAL = 0,
	MULTI,
	YUDO
};

#define BULLETMAX 30

class playGround : public gameNode
{
private:
	RECT _player1;	RECT _player2;	 // 플레이어 사각형
	RECT _bigRect1;	RECT _bigRect2; // 감지용 가상 사각형(유도탄용)


	RECT _obstacle; // 장애물	
	RECT temp; // 충돌
	PMODE _p1mode;	PMODE _p2mode; // 모드를 이넘문으로 선언합니다.
	tagBullet _bulletP1[BULLETMAX];	tagBullet _bulletP2[BULLETMAX];
	// 총알을 두 클래스로
	RECT _backGauge;	RECT _frontGauge; // 플레이어1 체력바
	RECT _backGauge2;	RECT _frontGauge2; // 플레이어2 체력바	
	POINTFLOAT _yudoFrom;	POINTFLOAT _yudoTo; // 유도탄 각도용 좌표잡기
	bool _isDeadP1; bool _isDeadP2; // 죽음
	bool _canUltiP1; bool _canUltiP2; // 궁사용가능
	int _reloadCount1; int _reloadCount2; // 장전카운트
	int _ultiCount1; int _ultiCount2; // 궁카운트(쿨)
	double angle; // 각도(유도탄용)
	int _r, _g; 	int _r2, _g2; // 색상
	int _direction; // 장애물의 방향(위아래로)

	RECT _effect[8]; // 이펙트용
	bool _effectOn; //  이펙트 켜졌는지

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//초기화 전용 함수
	virtual void release();			//메모리 해제 함수
	virtual void update();			//연산 전용
	virtual void render(HDC hdc);	//그리기 전용

	void keyControl(); // 키 컨트롤

	void bulletFireP1(); // 발사
	void bulletFireP2();

	void bulletMove(); // 총알이동(계속)

	void collision(); // 충돌(P2)
	void collision2(); // 충돌(P1)

	void collisionObstacle(); // 장애물이 총알 흡수

	void Yudo(); // 유도탄 인식하는거
	void Yudo2();

	void ultiP1(); // 궁발동
	void ultiP2();

	float calcAngleFromPoints(POINTFLOAT _ptFirst, POINTFLOAT _ptSecond);
	// 점 두개로 앵글을 구하는 함수(from 구글링)
};

