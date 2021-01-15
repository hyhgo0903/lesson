#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum ITEM
{
	ITEM_WEAPON = 1,
	ITEM_ARMOR,
	ITEM_END
};

struct tagItemInfo
{
	ITEM itemKind;			//아이템 종류
	string name;			//아이템 이름
	int price;				//아이템 가격
};


class shop
{
private:
	vector<tagItemInfo>				_vItem;
	vector<tagItemInfo>::iterator	_viItem;

public:
	shop();
	~shop();

	void itemSetup();	//아이템 세팅
	void itemOutput(int itemNum);	//아이템 출력

	vector<tagItemInfo> get_vItem() { return _vItem; }
};

