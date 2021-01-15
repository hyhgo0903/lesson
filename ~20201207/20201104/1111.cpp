#include <iostream>

using namespace std;

// 배열은 같은 변수가 연속적 나열
// 구조체 : 서로 다른 변수가 모여있는
// (→객체)  """public으로 된 class"""
// ##뭔소린지는 나중에 다시 와서 읽어볼것

struct tagUnit
{
	const char* name;
	int hp;
	int mp;
	float criPer;
	float spd;
	bool isDead;
};

int main1()
{

	// char name은 문자열 하나만 들어올수 있음. ex)char name = 'a';
	char name[4] = "BTS"; // 해줘야함
	// why not name[3]? -> 널값(\0)자리는 남겨줘야해서

	tagUnit player;
	// 정적할당. 도중에 메모리 삭제가 안된다.
	// 참고 :  <->동적할당. 도중에 메모리 삭제되면서 작동
	player.name = "융호";
	player.hp = 50;
	player.mp = 13;
	player.criPer = 1.0f;
	player.isDead = false;

	cout << player.name <<"\n";

	tagUnit goblin;
	goblin.hp = 100;

	tagUnit skeleton[3];
	for (int i = 0; i < 3; i++)
	{
		skeleton[i].hp = 100;
		skeleton[i].mp = 100;
	}

	// full oop (완전객체지향적 언어)
	// -> Java python C# ==>구조체를 잘 안쓴다.

	// half oop (반객체지향적 언어)
	// objective - c (애플)

	// c++는 객체지향이 가능한언어일뿐 객체지향적 언어는 X!

	int a = 3;
	int b = 5;
	int* c; // c는 포인터변수

	cout << b << endl;
	
	c = &b; // &는 참조자. 가리키는 것
	cout << c << endl; // &b : 실제로 b가 할당되어 있는 메모리 주소지
	*c = 7;
	// *c변수(포인터변수)는 주소할당시[c = &b;] 그냥 c를 쓰고
	// 값참고시[*c = 7;]엔 *c를 쓴다.
	cout << b << endl;


	return 0;
}
