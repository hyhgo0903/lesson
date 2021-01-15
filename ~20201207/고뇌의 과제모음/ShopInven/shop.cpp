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
	weapon1.description = "�ٵ���... ��� �õ�� ��ġ�� ���̸�ŭ �Ҵ�޾� ���ȴ�. (����� �Ⱦ��Ѵ�)";
	weapon1.ability = 32;
	weapon1.price = 64;

	_vItem.push_back(weapon1);

	tagItemInfo weapon2;
	weapon2.itemKind = ITEM_WEAPON;
	weapon2.name = "2. �������� ����ä��";
	weapon2.description = "�����ϰ� ������� �Ӱ��� �鸰��";
	weapon2.ability = 45;
	weapon2.price = 77;

	_vItem.push_back(weapon2);

	tagItemInfo weapon3;
	weapon3.itemKind = ITEM_WEAPON;
	weapon3.name = "3. ���� ���� �Ļ� (��Ʈ ������)";
	weapon3.description = "���ߵ� ��Ʈ������ ����. �����鼭 �ʵ� ������ ������ ���� ����";
	weapon3.ability = 40;
	weapon3.price = 1400;

	_vItem.push_back(weapon3);

	tagItemInfo armor1;
	armor1.itemKind = ITEM_ARMOR;
	armor1.name = "1. â������ �е�";
	armor1.description = "������ �ȿ� �������� �� ���̴�";
	armor1.ability = 5;
	armor1.price = 10;

	_vItem.push_back(armor1);

	tagItemInfo armor2;
	armor2.itemKind = ITEM_ARMOR;
	armor2.name = "2. ��ȣ�� ����";
	armor2.description = "������� ���з� �����ִ�. (�ȿ� ����å �Ѱ���)";
	armor2.ability = 13;
	armor2.price = 50000;

	_vItem.push_back(armor2);

	tagItemInfo armor3;
	armor3.itemKind = ITEM_ARMOR;
	armor3.name = "3. ��ȣ�� ��Ʈ";
	armor3.description = "������";
	armor3.ability = 87;
	armor3.price = 250;

	_vItem.push_back(armor3);

	tagItemInfo acce1;

	acce1.itemKind = ITEM_ACCESORY;
	acce1.name = "1. �������� ȸ���ð�";
	acce1.description = "�ŷ��� �Ϸ��Դ� ��������(������ ��)";
	acce1.ability = 50;
	acce1.price = 30;

	_vItem.push_back(acce1);

	tagItemInfo acce2;
	acce2.itemKind = ITEM_ACCESORY;
	acce2.name = "2. ��ȯ���� ����Ʈ��";
	acce2.description = "�۵��̰� �� �Ǽ������� �Ⱦ��մϴ�";
	acce2.ability = 100;
	acce2.price = 1000;
	
	_vItem.push_back(acce2);

	tagItemInfo acce3;
	acce3.itemKind = ITEM_ACCESORY;
	acce3.name = "3. �������� �����е�";
	acce3.description = "�⽺�� ������ �� �̷�";
	acce3.ability = 200;
	acce3.price = 3000;

	_vItem.push_back(acce3);

	tagItemInfo potion1;
	potion1.itemKind = ITEM_POTION;
	potion1.name = "1. ������ �Ź߸� ����";
	potion1.description = "������ �ߵ�� ȿ���� �پ�� ȿ����!!!";
	potion1.ability = 100;
	potion1.price = 100;
	_vItem.push_back(potion1);

	tagItemInfo potion2;
	potion2.itemKind = ITEM_POTION;
	potion2.name = "2. �������� (������) ��";
	potion2.description = "���� ������ȿ (������ �Ƹ����� �����)";
	potion2.ability = 200;
	potion2.price = 200;
	_vItem.push_back(potion2);



}

void shop::itemOutput(int itemNum)
{
	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); ++_viItem)
	{
		if (_viItem->itemKind != itemNum) continue;

		cout << " ======================= 25�� ���� =====================" << endl;
		cout << "��  �� : " << _viItem->name << endl;
		cout << "��  �� : " << _viItem->ability << endl;
		cout << "��  �� : " << _viItem->price << endl;
		cout << "��  �� : " << _viItem->description << endl;
		cout << "========================================================" << endl;
	}
}

