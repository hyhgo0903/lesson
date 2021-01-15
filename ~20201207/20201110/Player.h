#pragma once
#include <iostream>
using namespace std;

class Player
{
private:
	int _hp; // 전역변수라 "_"붙여서 구분해놓는것(혼돈방지)
	int _atk;
public:
	Player();
	~Player();
	int getPlayerHP() {	return _hp;	} // 접근자 getter
	// 자료형은 변수와 동일하게 맞춰줌

	int getPlayerAtk() { return _atk; }
	void setPlayerHP(int hp) { _hp = hp; } // 설정자 setter

	// 접근자 설정자 정의는 헤더파일(cpp말고)에 넣는게 관례임
	// 함수명에 get set붙이는것도 관례
};