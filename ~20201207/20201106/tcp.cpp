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
	double(*calc)(double, double) = NULL; // 함수 포인터 선언
	double num1 = 3, num2 = 4, result = 0;
	char oper = '+';

	switch (oper)
	{
	case '+':		calc = Add;		break;
	case '-':		calc = Sub;		break;
	default:		cout << "+, -만을 지원합니다.";	break;
	}

result = Calculator(num1, num2, calc);
cout << "사칙 연산의 결과는 " << result << "입니다.";
return 0;
}
