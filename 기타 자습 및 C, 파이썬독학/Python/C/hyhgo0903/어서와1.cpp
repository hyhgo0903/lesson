#include <iostream> // 헤더 파일
#include <string>
using namespace std; // std::cout -> 공간::이름
// 현재 사용하는 이름 공간을 std로 설정
// std안의 모든 이름을 std없이 사용가능

float transform(int a);
int main22()
{
	int s1{ 1000%300 };
	int s2 = 1500;
	cout << s1 <<" "<< to_string(s2) << "\n";
	cout << "섭씨온도 입력 : ";
	cin >> s1;
	cout << s1 << "을 입력했습니다.\n화씨 온도는";
	cout << transform(s1);
	
	return 0;
}


float transform(int a)
{
	return (5.0 / 9.0) * (a - 32); // 5.0, 9.0대신 5, 9를 쓰면 정수값 반환 -> 5/9=0돼버림
}