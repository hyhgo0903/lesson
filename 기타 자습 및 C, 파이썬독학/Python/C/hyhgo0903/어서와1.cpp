#include <iostream> // ��� ����
#include <string>
using namespace std; // std::cout -> ����::�̸�
// ���� ����ϴ� �̸� ������ std�� ����
// std���� ��� �̸��� std���� ��밡��

float transform(int a);
int main22()
{
	int s1{ 1000%300 };
	int s2 = 1500;
	cout << s1 <<" "<< to_string(s2) << "\n";
	cout << "�����µ� �Է� : ";
	cin >> s1;
	cout << s1 << "�� �Է��߽��ϴ�.\nȭ�� �µ���";
	cout << transform(s1);
	
	return 0;
}


float transform(int a)
{
	return (5.0 / 9.0) * (a - 32); // 5.0, 9.0��� 5, 9�� ���� ������ ��ȯ -> 5/9=0�Ź���
}