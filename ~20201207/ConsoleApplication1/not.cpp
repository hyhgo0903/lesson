#include <iostream>
using namespace std;

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	// 아직도 모르겠다 이거의 의미를

	cout << fixed;
	cout.precision(10); // 요것도 알아두자

	int aa = 0;
	int bb = 0;

	while (cin >> aa >> bb) // 성공적으로 입력받는 동안 이란 뜻임
		// 입력 잘 받으면 true 아니면 false반환
	{
		cout << aa+bb << endl;
	}	
	return 0;
}