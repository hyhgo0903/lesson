#pragma once
class motherClass
{
private:
	int _motherMoney; // 비자금
	// motherClass에서만 사용하는 멤버변수
	// 전역변수로서 _를 붙였음.

protected:
	int _familyMoney; // 생활비

public:
	int _freeMoney; // 꽁돈

	motherClass();
	~motherClass();
};

