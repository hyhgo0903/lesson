#pragma once // 어떠한 코드나 헤더파일이 다른 코드나 헤더에서 include 될때,
// 중복되어 복사되는 것을 방지하는 기능을 한다.
#include <iostream>
#include <map>

using namespace std;


class mapTest
{
private:
	// 연관 컨테이너 종류 중 하나
	// first, second 이렇게 인자를 2개 가짐
	// 자료구조 중에 레드 블랙 트리 구조로 되어있음.
	// 데이터를 담을떄 키값과 실제 값을 저장해서
	// 키 값으로 어떠한 값을 불러올떄 사용됨 // 오케이 접수

	map<const char*, int>			_mapTest;
	map<const char*, int>::iterator _mi;

	// 1만개 이하의 데이터 -> 벡터(배열로 순차적)
	// 1만개 이상의 데이터 -> 리스트가 유리
	// 10만개 이상의 데이터 -> 맵이 유리
	// 100만개 이상의 데이터 -> 해쉬맵이 유리
	// 해쉬테이블은 면접질문 간혹나옴

	// but, hash_map은 C++버전이 올라감에따라
	// unordered_map으로 사용하길 권장하고 있음.




public:
	mapTest();
	~mapTest();
};

