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
	weapon1.name = "1. ���� �޸� ��";
	weapon1.price = 64;
	_vItem.push_back(weapon1);

	tagItemInfo weapon2;
	weapon2.itemKind = ITEM_WEAPON;
	weapon2.name = "2. �������� ����ä��";
	weapon2.price = 77;
	_vItem.push_back(weapon2);

	tagItemInfo armor1;
	armor1.itemKind = ITEM_ARMOR;
	armor1.name = "1. â������ �е�";
	armor1.price = 10;
	_vItem.push_back(armor1);

	tagItemInfo armor2;
	armor2.itemKind = ITEM_ARMOR;
	armor2.name = "2. ��ȣ�� ����";
	armor2.price = 50000;
	_vItem.push_back(armor2);
}

void shop::itemOutput(int itemNum)
{
	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); ++_viItem)
	{
		if (_viItem->itemKind != itemNum) continue;

		cout << " ======================= 25�� ���� =====================" << endl;
		cout << "��  �� : " << _viItem->name << endl;
		cout << "��  �� : " << _viItem->price << endl;
		cout << "========================================================" << endl;
	}
}

