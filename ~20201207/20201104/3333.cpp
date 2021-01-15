#include <iostream>
#include <time.h>

using namespace std;

struct tagBullet
{
	int dmg;
	float spd;
	float fireRange;
};

#define BULLETMAX 100 // 세미콜론 찍으면 안됨
// 디파인문은 전처리기기때문에 문제시 디버그 어렵
#define PLUS(x) x + x
#define MULTIPLE(x) x * x

int main333()
{
	cout << PLUS(3) << endl; // cout << 3 + 3 을 한것과 동일(대치)

	cout << MULTIPLE(3 + 2) << endl;
	// cout << 3 + 2 * 3 + 2이므로 11
	// 고대로 대입한다.
	cout << MULTIPLE((3 + 2)) << endl;
	// cout << (3 + 2) * (3 + 2)이므로 25

	//더블 포인터 변수
	tagBullet bullet[BULLETMAX];

	for (int i = 0; i < BULLETMAX; i++)
	{
		bullet[i].dmg = 10;
	}
/*
#ifdef _DEBUG
	{

	}
#else
	{

	}
*/

	return 0;
}
