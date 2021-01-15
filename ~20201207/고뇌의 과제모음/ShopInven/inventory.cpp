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
		cout << "��  �� : " << _vInven[i].ability << endl;
		cout << "��  �� : " << _vInven[i].price << endl;
		cout << "��  �� : " << _vInven[i].description << endl;
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
		cout << "��  �� : " << _vInven[i].ability << endl;
		cout << "��  �� : " << _vInven[i].price << endl;
		cout << "��  �� : " << _vInven[i].description << endl;
		cout << "========================================================" << endl;
	}
}
void inventory::itemSetup2()
{
	weapon1.itemKind = 1;
	weapon1.name = "���� �޸� ��";
	weapon1.description = "�ٵ���... ��� �õ�� ��ġ�� ���̸�ŭ �Ҵ�޾� ���ȴ�. (����� �Ⱦ��Ѵ�)";
	weapon1.ability = 32;
	weapon1.price = 64;
	weapon2.itemKind = 1;
	weapon2.name = "�������� ����ä��";
	weapon2.description = "�����ϰ� ������� �Ӱ��� �鸰��";
	weapon2.ability = 45;
	weapon2.price = 77;
	weapon3.itemKind = 1;
	weapon3.name = "���� ���� �Ļ� (��Ʈ ������)";
	weapon3.description = "���ߵ� ��Ʈ������ ����. �����鼭 �ʵ� ������ ������ ���� ����";
	weapon3.ability = 40;
	weapon3.price = 1400;
	armor1.itemKind = 2;
	armor1.name = "â������ �е�";
	armor1.description = "������ �ȿ� �������� �� ���̴�";
	armor1.ability = 5;
	armor1.price = 10;
	armor2.itemKind = 2;
	armor2.name = "��ȣ�� ����";
	armor2.description = "������� ���з� �����ִ�. (�ȿ� ����å �Ѱ���)";
	armor2.ability = 13;
	armor2.price = 50000;
	armor3.itemKind = 2;
	armor3.name = "��ȣ�� ��Ʈ";
	armor3.description = "������";
	armor3.ability = 87;
	armor3.price = 250;
	acce1.itemKind = 3;
	acce1.name = "�������� ȸ���ð�";
	acce1.description = "�ŷ��� �Ϸ��Դ� ��������(������ ��)";
	acce1.ability = 50;
	acce1.price = 30;
	acce2.itemKind = 3;
	acce2.name = "��ȯ���� ����Ʈ��";
	acce2.description = "�۵��̰� �� �Ǽ������� �Ⱦ��մϴ�";
	acce2.ability = 100;
	acce2.price = 1000;
	acce3.itemKind = 3;
	acce3.name = "�������� �����е�";
	acce3.description = "�⽺�� ������ �� �̷�";
	acce3.ability = 200;
	acce3.price = 3000;
	potion1.itemKind = 4;
	potion1.name = "������ �Ź߸� ����";
	potion1.description = "������ �ߵ�� ȿ���� �پ�� ȿ����!!!";
	potion1.ability = 100;
	potion1.price = 100;
	potion2.itemKind = 4;
	potion2.name = "�������� (������) ��";
	potion2.description = "���� ������ȿ (������ �Ƹ����� �����)";
	potion2.ability = 200;
	potion2.price = 200;
}

void inventory::itemBuy(int x)
{
	switch (x)
	{
	case 0:
		_vInven.push_back(weapon1);
		break;
	case 1:
		_vInven.push_back(weapon2);
		break;
	case 2:
		_vInven.push_back(weapon3);
		break;
	case 3:
		_vInven.push_back(armor1);
		break;
	case 4:
		_vInven.push_back(armor2);
		break;
	case 5:
		_vInven.push_back(armor3);
		break;
	case 6:
		_vInven.push_back(acce1);
		break;
	case 7:
		_vInven.push_back(acce2);
		break;
	case 8:
		_vInven.push_back(acce3);
		break;
	case 9:
		_vInven.push_back(potion1);
		break;
	case 10:
		_vInven.push_back(potion2);
		break;
	}
}
