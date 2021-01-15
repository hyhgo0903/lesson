#include <iostream>
using namespace std;

enum STATE
{
	AIR,
	GROUND
};

enum PLAYERSTATE
{ // 구조체처럼 계속 나열가능
  // switch문과 궁합이 좋다
	IDLE,
	POWER1,
	POWER2,
	POWER3,
	POWERMAX = 15,
	// << 숫자지정해서 선언도 가능
	FLYING // <<얘는 16(15+1)
};

struct tagPlayer
{ // 구조체에 이넘을 선언한 예시
	int hp;
	STATE state;
	PLAYERSTATE playerState;
};
// tagPlayer의변수.playerState = POWER3; << 요렇게 쓰겠지?

int main2222()
{
	tagPlayer hyh;
	hyh.hp = 100;
	hyh.state = AIR;
	hyh.playerState = POWER3;
	cout << hyh.state << endl << hyh.playerState << endl;

	int num[3]{ 11,22,33 };
	cout << num[IDLE] << endl;
	num[POWER1] = 2;
	// 이넘문 말고 그냥도 쓸 수 있어
	for (int i = 0; i < POWER2 + 1; i++)
	{
		// 요런식으로 쓸수도 있어요
	}

	PLAYERSTATE state;
	// 이넘을 정의

	state = POWERMAX; // 15가 들어간다

	if (state == POWERMAX)
	{
		cout << "맥스한 파워인걸" << "\n";
		state = IDLE;
	}


	int power = 1;
	//state = power;내지 state = 1;    << 이거는 에러난다.
	// 파워는 정수형인데 이넘(state)은 열거체
	state = (PLAYERSTATE)power; // 할거면 이렇게
	// power = state; // 요거는 또 되네?;;
	// cout << power << "\n"; // 15
	cout << state << "\n";

	switch (state)
		// 쓰고 탭누르면 알아서 만들어준다 (자동완성)
		// switch치고 탭 이넘문 넣고 엔터
	{
	case IDLE:
		break;
	case POWER1:
		break;
	case POWER2:
		break;
	case POWER3:
		break;
	case POWERMAX:
		break;
	case FLYING:
		break;
	default:
		break;
	} // 요로코롬 나온다.


	return 0;
}
