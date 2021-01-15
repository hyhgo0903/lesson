#pragma once
#include <iostream>
using namespace std;
class mainGame
{

public:
	mainGame();

	template <typename T>
	void output(T t);
	// STL : Standard Template Library
	// 함수템플릿. 내가 뭘 담겠다 선언을 하는것
	// 얘 만들땐 헤더파일에 정의되네

};

template<typename T>
inline void mainGame::output(T t)
{
	cout << t << endl;
}