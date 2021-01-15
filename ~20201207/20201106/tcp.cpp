#include <iostream>
using namespace std;

double Add(double num1, double num2) { return num1 + num2; }
double Sub(double num1, double num2) { return num1 - num2; }
double Calculator(double num1, double num2, double(*func)(double, double))
{
	return func(num1, num2);
}

int main_tcp_ex(void)
{
	double(*calc)(double, double) = NULL; // �Լ� ������ ����
	double num1 = 3, num2 = 4, result = 0;
	char oper = '+';

	switch (oper)
	{
	case '+':		calc = Add;		break;
	case '-':		calc = Sub;		break;
	default:		cout << "+, -���� �����մϴ�.";	break;
	}

result = Calculator(num1, num2, calc);
cout << "��Ģ ������ ����� " << result << "�Դϴ�.";
return 0;
}
