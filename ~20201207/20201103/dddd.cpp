#include <iostream>
#include <time.h>

using namespace std;

int main1212()
{
	// Casting - 형변환

	float moveDistance{3.3f };
	// f안붙여도 되는데 C#에선 꼭 붙여야함

	int totalDistnace = moveDistance * 4;
	cout << "총 이동거리 : " << totalDistnace << endl;
	// 13.2가 아니라 13으로 출력. 소수점을 날리고 함

	// 명시적 형변환. (int로 쓸거야) C스타일의 예
	cout << "대략 이동거리 : " << (int)moveDistance << endl;

	// C++스타일
	// static_cast<변환할형>(변수) 위와 같은 역할
	// reinterpret_cast - 시간이 남으면 조사해보세요
	// const_cast - const(상수)형을 풀어버림(쓰지 않음)
	// dynamic_cast - 상속관계에서 많이 사용함 (쓰게 될듯)

	int num = 65;
	cout << num << endl;
	cout << (char)num << endl; // 아스키코드상 'A'의 10진 65
	cout << (int)'A' << endl;
	
	int board[2][2] = { 150 };
	cout << board[0][1] << "\n";

	int i;
	for (i = 0; i < 10; i++) {}
	cout << i << "\n";
	i = -2;
	while (++i) { cout << "하이\n"; }
	int test[10];
	for (int & i : test)
	{
		i = 0;
	}
	cout << test[9];


	return 0;
}