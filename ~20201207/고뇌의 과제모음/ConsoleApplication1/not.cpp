#include <iostream>
using namespace std;

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	// ������ �𸣰ڴ� �̰��� �ǹ̸�

	cout << fixed;
	cout.precision(10); // ��͵� �˾Ƶ���

	int aa = 0;
	int bb = 0;

	while (cin >> aa >> bb) // ���������� �Է¹޴� ���� �̶� ����
		// �Է� �� ������ true �ƴϸ� false��ȯ
	{
		cout << aa+bb << endl;
	}	
	return 0;
}