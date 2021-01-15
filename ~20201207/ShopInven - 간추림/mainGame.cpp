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
	cout << "============= 25기 상점 ==============			소지금 : "<< _money << endl;
	cout << "1. 상점              2. 인벤토리" << endl;
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
		cout << "================= 25기 상점 ================		소지금 : " << _money << endl;
		cout << "1. 무기구, 2. 방어구, 3. 악세서리, 4. 포션" << endl;
		cout << "============================================" << endl;
		cout << "메인화면으로 가려면 ▷ 0번 : ";

		cin >> _selectNum;

		system("cls");
		if (_selectNum == 0)
		{
			setMainPage();
			break;
		}
		cout << "							소지금 : " << _money << endl;
		_shop->itemOutput(_selectNum);

		cout << "구매할 아이템 번호를 입력하세요" << endl;
		cout << "(돈 없으면 안 사짐)" << endl;
		cout << "이전 화면으로 가려면 ▷ 0번 : ";
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
		cout << "================ 내 가방 =================		소지금 : " << _money << endl;
		cout << "	 1. 모두 보기" << endl;
		cout << "	▽종류별로 보기" << endl;
		cout << "2. 무기구, 3. 방어구, 4. 악세서리, 5. 포션" << endl;
		cout << "============================================" << endl;
		cout << "메인화면으로 가려면 ▷ 0번 : ";

		cin >> _selectNum;

		system("cls");
		if (_selectNum == 0)
		{
			setMainPage();
			break;
		}
		cout << "================ 내 가방 =================		소지금 : " << _money << endl;
		if (_selectNum == 1)
		{
			_inven->inventoryOutput();
		}
		else _inven->inventoryOutput(_selectNum-1);

		cout << "이전화면으로 돌아가려면 아무키나 누르세욥" << endl;
		cin >> _selectNum;
		system("cls");

	}

}
