#pragma once
#include <iostream>

using namespace std;


class mainGame
{
private: // 객체 고유. 외부접근X. Class의 default
	// 주로 클래스의 변수(필드)를 넣고 쓴다.(절대적인건X)

protected: // 자기 or 상속관계에서만 접근가능.
	// 상속, 상상속, 상상상속...들도 됨.

public: // 걍 접근가능. Struct의 default
	// 주로 클래스의 함수(메소드)를 넣고 쓴다.
	void attack();
	void attack(int mp); // 오버로드. 매개변수 형태가 달라야

	/* 오버라이딩 : 부모클래스에 있는 함수를
				자식클래스에서 재정의해서 사용.

	이 과정에서 사용하는게 가상함수

	가상함수 : 부모클래스에 있는 함수가 자식클래스에 오버라이드 안 되어있으면
	부모의 것이 실행되고, 오버라이드 되어있으면 자식의 함수가 실행되는 것.
	->
	if (자식클래스에 부모의 함수가 오버라이드 돼있나?) {자식거 실행};
	else {부모거 실행};

	*/
	mainGame();
	~mainGame();
};