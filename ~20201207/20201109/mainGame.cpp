#include "mainGame.h"

void mainGame::attack()
{
	cout << "기본공격입니다.\n";
}

void mainGame::attack(int mp)
{
	cout << mp << "를 사용한 공격입니다.\n";
}

mainGame::mainGame()
{
	cout << "생성되었습니다.\n";
}

mainGame::~mainGame()
{
	cout << "소멸되었습니다.\n";
}
