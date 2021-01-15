#include "shop.h"

shop::shop()
{
}


shop::~shop()
{
}

void shop::itemSetup()
{
	tagItemInfo weapon1;
	weapon1.itemKind = ITEM_WEAPON;
	weapon1.name = "1. 뚜의 메모리 검";
	weapon1.price = 64;
	_vItem.push_back(weapon1);

	tagItemInfo weapon2;
	weapon2.itemKind = ITEM_WEAPON;
	weapon2.name = "2. 남영이의 동물채찍";
	weapon2.price = 77;
	_vItem.push_back(weapon2);

	tagItemInfo armor1;
	armor1.itemKind = ITEM_ARMOR;
	armor1.name = "1. 창훈이의 패딩";
	armor1.price = 10;
	_vItem.push_back(armor1);

	tagItemInfo armor2;
	armor2.itemKind = ITEM_ARMOR;
	armor2.name = "2. 찬호의 백팩";
	armor2.price = 50000;
	_vItem.push_back(armor2);
}

void shop::itemOutput(int itemNum)
{
	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); ++_viItem)
	{
		if (_viItem->itemKind != itemNum) continue;

		cout << " ======================= 25기 상점 =====================" << endl;
		cout << "이  름 : " << _viItem->name << endl;
		cout << "가  격 : " << _viItem->price << endl;
		cout << "========================================================" << endl;
	}
}

