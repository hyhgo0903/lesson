#pragma once
#include <iostream>
#include "shop.h"
#include "inventory.h"

using namespace std;

enum LOCATION
{
	LOCATION_SHOP = 1,
	LOCATION_INVEN
};

class mainGame
{
private:
	shop* _shop;
	inventory* _inven;

	LOCATION _location;

	int _money;			//������
	int _selectNum;		//���� ����
	int _selectNum2;


public:
	mainGame();
	~mainGame();

	void setLocation(int number);
	void setMainPage();
	void setShopPage();
	void setInvenPage();
};

