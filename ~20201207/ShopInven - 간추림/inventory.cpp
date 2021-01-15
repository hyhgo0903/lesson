#include "inventory.h"
inventory::inventory()
{
}

inventory::~inventory()
{
}

void inventory::inventoryOutput()
{	
	for (int i = 0; i<_vInven.size();i++)
	{
		cout << " ======================= 보유 아이템 =====================" << endl;
		cout << "이  름 : " << _vInven[i].name << endl;
		cout << "가  격 : " << _vInven[i].price << endl;
		cout << "========================================================" << endl;
	}
}

void inventory::inventoryOutput(int itemNum)
{
	for (int i = 0; i < _vInven.size(); i++)
	{
		if (_vInven[i].itemKind != itemNum) continue;

		cout << " ======================= 25기 상점 =====================" << endl;
		cout << "이  름 : " << _vInven[i].name << endl;
		cout << "가  격 : " << _vInven[i].price << endl;
		cout << "========================================================" << endl;
	}
}
void inventory::itemBuy(int x)
{
	switch (x)
	{
	case 0:
		break;
	case 1:
		break;
	case 3:
		break;
	case 4:
		break;	
	}
}
