#include "motherClass.h"

motherClass::motherClass()
{
	int money = 200; // 지역변수
	_motherMoney = 500; // 전역변수
}

motherClass::~motherClass()
{
	_motherMoney = 500; // 전역변수
}