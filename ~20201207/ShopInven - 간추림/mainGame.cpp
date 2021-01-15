#include "mainGame.h"


mainGame::mainGame()
{
	_shop = new shop;
	_shop->itemSetup();
	_inven = new inventory;
	_inven->itemSetup2();
	_money = 100000;
	_selectNum = 0;
	_selectNum2 = 0;

	setMainPage();

}

mainGame::~mainGame()
{
	delete _shop;
	delete _inven;
}

void mainGame::setLocation(int number)
{
	switch (number)
	{
		case LOCATION_SHOP:
			setShopPage();
		break;
		case LOCATION_INVEN:
			setInvenPage();
		break;
		default:
			setMainPage();
		break;
	}
}

void mainGame::setMainPage()
{
	cout << "============= 25�� ���� ==============			������ : "<< _money << endl;
	cout << "1. ����              2. �κ��丮" << endl;
	cout << "======================================" << endl;

	cin >> _selectNum;
	system("cls");
	setLocation(_selectNum);
}

void mainGame::setShopPage()
{
	while (true)
	{
		_selectNum = 5;
		_selectNum2 = 5;
		cout << "================= 25�� ���� ================		������ : " << _money << endl;
		cout << "1. ���ⱸ, 2. ��, 3. �Ǽ�����, 4. ����" << endl;
		cout << "============================================" << endl;
		cout << "����ȭ������ ������ �� 0�� : ";

		cin >> _selectNum;

		system("cls");
		if (_selectNum == 0)
		{
			setMainPage();
			break;
		}
		cout << "							������ : " << _money << endl;
		_shop->itemOutput(_selectNum);

		cout << "������ ������ ��ȣ�� �Է��ϼ���" << endl;
		cout << "(�� ������ �� ����)" << endl;
		cout << "���� ȭ������ ������ �� 0�� : ";
		cin >> _selectNum2;
		system("cls");
		if (_selectNum2 == 0)
		{
			continue;
		}
		else if (_selectNum2 == 1)
		{
			switch (_selectNum)
			{
			case 1:
				if (_money < _inven->weapon1.price) break;
				_money -= _inven->weapon1.price;
				_inven->itemBuy(0);
				break;
			case 2:
				if (_money < _inven->armor1.price) break;
				_money -= _inven->armor1.price;
				_inven->itemBuy(3);
				break;
			}
		}
		else if (_selectNum2 == 2)
		{
			switch (_selectNum)
			{
			case 1:
				if (_money < _inven->weapon2.price) break;
				_money -= _inven->weapon2.price;
				_inven->itemBuy(1);
				break;
			case 2:
				if (_money < _inven->armor2.price) break;
				_money -= _inven->armor2.price;
				_inven->itemBuy(4);
				break;
			}
		}		
	}
}

void mainGame::setInvenPage()
{
	while (true)
	{
		cout << "================ �� ���� =================		������ : " << _money << endl;
		cout << "	 1. ��� ����" << endl;
		cout << "	���������� ����" << endl;
		cout << "2. ���ⱸ, 3. ��, 4. �Ǽ�����, 5. ����" << endl;
		cout << "============================================" << endl;
		cout << "����ȭ������ ������ �� 0�� : ";

		cin >> _selectNum;

		system("cls");
		if (_selectNum == 0)
		{
			setMainPage();
			break;
		}
		cout << "================ �� ���� =================		������ : " << _money << endl;
		if (_selectNum == 1)
		{
			_inven->inventoryOutput();
		}
		else _inven->inventoryOutput(_selectNum-1);

		cout << "����ȭ������ ���ư����� �ƹ�Ű�� ��������" << endl;
		cin >> _selectNum;
		system("cls");

	}

}
