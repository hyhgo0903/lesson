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
	// �Լ����ø�. ���� �� ��ڴ� ������ �ϴ°�
	// �� ���鶩 ������Ͽ� ���ǵǳ�

};

template<typename T>
inline void mainGame::output(T t)
{
	cout << t << endl;
}