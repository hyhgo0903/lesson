#pragma once
#include "singletonBase.h"
#include <time.h>

class randomFunction : public singletonBase<randomFunction>
{
public:
	randomFunction()
	{
		srand(GetTickCount());
	}
	~randomFunction()
	{
	}

	//매개변수에 넣은 숫자의 -1만큼 범위가 랜덤하게 나온다
	inline int getInt(int num) { return rand() % num; }

	//     정수형 난수발생함수(범위시작, 범위 끝)
	inline int getFromIntTo(int fromNum, int toNum)
	{
		return rand() % (toNum - fromNum) + fromNum;
	}
};