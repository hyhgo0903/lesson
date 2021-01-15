#pragma once
#include <iostream>
#include <vector>
using namespace std;
class vectorTest
{
private:
	// 벡터는 느린편
	vector<int> _vNum; // int형을 담는 벡터
	vector<int>::iterator _viNum;

public:
	vectorTest();
	~vectorTest();
};

