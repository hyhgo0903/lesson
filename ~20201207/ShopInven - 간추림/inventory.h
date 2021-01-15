#pragma once
#include "shop.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;
struct tagInvenInfo
{
	int itemKind;			//아이템 종류
	string name;			//아이템 이름
	int price;				//아이템 가격
};


class inventory
{
private:
	vector<tagInvenInfo>			_vInven;
	vector<tagInvenInfo>::iterator	_viInven;
public:
	inventory();
	~inventory();
	void inventoryOutput();
	void inventoryOutput(int itemNum);

	void itemBuy(int x)
	{
		shop->get_vItem();
	}
};