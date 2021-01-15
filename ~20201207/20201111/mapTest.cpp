#include "mapTest.h"


mapTest::mapTest()
{
	//맵에는 push_back()이 없다.
	//insert로 넣게 되어있는데
	//pair, make_pair 이렇게 존재
	//차이점을 각자 조사

	//map<first, second>
	// 맵컨테이너에 자료넣으면 자동으로 오름차순 정렬된다.

	_mapTest.insert(pair<const char*, int>("반장", 7));
	_mapTest.insert(pair<const char*, int>("현종", 13));
	_mapTest.insert(pair<const char*, int>("찬호", 9));

	_mi = _mapTest.find("현종"); // 해당이름으로 있니?

	// 맵이터레이터가 맵의 엔드와 같지 않다?!?!
	if (_mi != _mapTest.end())
	{ // 만약 키 값이 존재하면
		cout << _mi->first << "가 좋아하는 숫자는 " << _mi->second << "입니다." << endl;
	}
	else // 키 값이 없으면(엔드에 도달 = 해당키값이 없다.)
	{
		cout << "그런 애는.. 없는데.." << endl;
	}
}


mapTest::~mapTest()
{


}
