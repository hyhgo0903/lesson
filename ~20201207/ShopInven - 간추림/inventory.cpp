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
		cout << " ======================= ���� ������ =====================" << endl;
		cout << "��  �� : " << _vInven[i].name << endl;
		cout << "��  �� : " << _vInven[i].price << endl;
		cout << "========================================================" << endl;
	}
}

void inventory::inventoryOutput(int itemNum)
{
	for (int i = 0; i < _vInven.size(); i++)
	{
		if (_vInven[i].itemKind != itemNum) continue;

		cout << " ======================= 25�� ���� =====================" << endl;
		cout << "��  �� : " << _vInven[i].name << endl;
		cout << "��  �� : " << _vInven[i].price << endl;
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
