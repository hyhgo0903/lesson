#include "vectorTest.h"
#include <iostream>

using namespace std;

//벡터 메모리 크기 원래는 2배씩잡았는데 지금은 1.5배씩

vectorTest::vectorTest()
{
	//1. 컨테이너에 값을 순차적으로 넣고 싶을떈
	// push_back() - 값을 한번 복사한 다음 넣는다
	// 참고 : emplace_back() - 값을 복사하지 않고 넣는다
	
	// 얕은복사 깊은복사
	// 복사생성자 / 이동생성자(move)
	
	_vNum.push_back(1); // {1}

	for (int i=0; i<3; i++)
		_vNum.push_back(i*10); // {1, 0, 10, 20}

	//2. 벡터의 크기를 알려주는 size()
	cout << "벡터의 현재 크기 : " << _vNum.size() << endl; // 4

	//3. 순차적으로 뒤에서부터 삭제하는 pop_back()
	_vNum.pop_back(); // {1, 0, 10}
	_vNum.pop_back(); // {1, 0}

	// cout << _vNum.begin(); <<안된다

	//4. 벡터 중간에 값 삽입 insert()
	_vNum.insert(_vNum.begin() + 1, 777);  // {1, 777, 0}
	// 벡터 시작에서 2번째자리에서 777을 넣고 나머지를 한칸씩 밀어냄

	_vNum.insert(_vNum.end() - 1, 333);  // {1, 777, 333, 0}
	// 벡터 끝에서 2번째자리에서 333을 넣고 나머지를 한칸씩 밀어냄

	//벡터 중간의 값을 삭제할떈 erase()
	_vNum.erase(_vNum.begin() + 2); // {1, 777, 0}
	_vNum.erase(_vNum.end() - 2); // {1, 0}

	_vNum.clear(); // 벡터 클리어한다고 메모리가 사라지진 않음

	for (int i = 0; i < _vNum.size(); i++)
		cout << _vNum[i] << " ";
	cout << "\n";
}

vectorTest::~vectorTest()
{
}
