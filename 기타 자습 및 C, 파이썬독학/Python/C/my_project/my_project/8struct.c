#include <stdio.h>
// 구조체 선언
struct GameInfo {
	char* name;
	int year;
	int price;

	struct GameInfo* friendGame;
	// 연관업체게임. 구조체안의 구조체
};

typedef struct {
	char* name;
	int year;
	int price;

	struct GameInfo* friendGame;
} GAME_INFO; // 맨 아랫줄에 설명

int main_struct(void)
{
	// 구조체 사용
	struct GameInfo gameInfo1;
	gameInfo1.name = "나도게임";
	gameInfo1.year = 2017;
	gameInfo1.price = 1000;

	// 구조체 출력
	printf("== 게임 출시 정보 ==\n");
	printf("게임명   : %s\n", gameInfo1.name);
	printf("출시연도 : %d\n", gameInfo1.year);
	printf("가격     : %d\n", gameInfo1.price);

	// 구조체를 배열처럼 초기화
	struct GameInfo gameInfo2 = {"너도게임",2020,2000,"너도회사"};
	printf("== 또다른 게임 출시 정보 ==\n");
	printf("게임명   : %s\n", gameInfo2.name);
	printf("출시연도 : %d\n", gameInfo2.year);
	printf("가격     : %d\n", gameInfo2.price);

	// 구조체 배열
	struct GameInfo gameArray[2] = {
	{"나도",2010,5000,"나회"} ,
	{"너도",2030,7000,"너회"}
	};

	// 구조체 포인터
	struct GameInfo* gamePtr;
	gamePtr = &gameInfo1;
	printf("\n\n== 포인터 정보 ==\n");
	printf("게임명   : %s\n", (*gamePtr).name);
	printf("출시연도 : %d\n", (*gamePtr).year);
	printf("가격     : %d\n", gamePtr->price);
	// 포인터일때는 위와같이 . 안쓰고 화살표를 이용가능

	//연관업체 게임소개
	gameInfo1.friendGame = &gameInfo2;
	// friendGame이라는 구조체 자체가 포인터
	printf("\n\n== 연관업체 정보 ==\n");
	printf("게임명   : %s\n", (*gameInfo1.friendGame).name);
	printf("출시연도 : %d\n", (*gameInfo1.friendGame).year);
	printf("가격     : %d\n", gameInfo1.friendGame->price);

	// typedef
	// 자료형에 별명 지정
	int i = 1;
	typedef int 정수;
	// 이제 "정수"를 "int"와 동일하게 사용가능
	정수 j = 3;
	typedef float 실수;
	실수 실수변수1 = 4.3218f;
	printf("\ni = %d\nj = %d\n실수변수1 = %.3f\n",
		i, j, 실수변수1);

	typedef struct GameInfo 게임정보;
	게임정보 game1; // == struct GameInfo game1;
	game1.name = "한글게임";
	game1.year = 1991;

	GAME_INFO game2;
	game2.name = "한글게임2";
	game2.year = 1891;
	// 이렇게 해도 가능
	// 단 이런식으로 한 경우 struct GameInfo game2;
	// 이런식으로는 정의 못함(별명대로 써야)

	return 0;
}