#include <iostream>
using namespace std;

enum STATE
{
	AIR,
	GROUND
};

enum PLAYERSTATE
{ // ����üó�� ��� ��������
  // switch���� ������ ����
	IDLE,
	POWER1,
	POWER2,
	POWER3,
	POWERMAX = 15,
	// << ���������ؼ� ���� ����
	FLYING // <<��� 16(15+1)
};

struct tagPlayer
{ // ����ü�� �̳��� ������ ����
	int hp;
	STATE state;
	PLAYERSTATE playerState;
};
// tagPlayer�Ǻ���.playerState = POWER3; << �䷸�� ������?

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
	// �̳ѹ� ���� �׳ɵ� �� �� �־�
	for (int i = 0; i < POWER2 + 1; i++)
	{
		// �䷱������ ������ �־��
	}

	PLAYERSTATE state;
	// �̳��� ����

	state = POWERMAX; // 15�� ����

	if (state == POWERMAX)
	{
		cout << "�ƽ��� �Ŀ��ΰ�" << "\n";
		state = IDLE;
	}


	int power = 1;
	//state = power;���� state = 1;    << �̰Ŵ� ��������.
	// �Ŀ��� �������ε� �̳�(state)�� ����ü
	state = (PLAYERSTATE)power; // �ҰŸ� �̷���
	// power = state; // ��Ŵ� �� �ǳ�?;;
	// cout << power << "\n"; // 15
	cout << state << "\n";

	switch (state)
		// ���� �Ǵ����� �˾Ƽ� ������ش� (�ڵ��ϼ�)
		// switchġ�� �� �̳ѹ� �ְ� ����
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
	} // ����ڷ� ���´�.


	return 0;
}
