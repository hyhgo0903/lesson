#include <iostream>
#include <time.h>

using namespace std;

struct tagBullet
{
	int dmg;
	float spd;
	float fireRange;
};

#define BULLETMAX 100 // �����ݷ� ������ �ȵ�
// �����ι��� ��ó����⶧���� ������ ����� ���
#define PLUS(x) x + x
#define MULTIPLE(x) x * x

int main333()
{
	cout << PLUS(3) << endl; // cout << 3 + 3 �� �ѰͰ� ����(��ġ)

	cout << MULTIPLE(3 + 2) << endl;
	// cout << 3 + 2 * 3 + 2�̹Ƿ� 11
	// ���� �����Ѵ�.
	cout << MULTIPLE((3 + 2)) << endl;
	// cout << (3 + 2) * (3 + 2)�̹Ƿ� 25

	//���� ������ ����
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
