#include "DarkArchon.h"

DarkArchon::DarkArchon()
{
	_hp = 20;
	_atk = 0;
	cout << "DarkArchon Ŭ������ �������Դϴ�. \n\n";
}

DarkArchon::~DarkArchon()
{
	cout << "DarkArchon Ŭ������ �Ҹ����Դϴ�. \n\n";
}

void DarkArchon::output()
{
	cout << "DarkArchon�� HP : " << _hp << endl;
	cout << "DarkArchon�� ���ݷ� : " << _atk << endl;
}

void DarkArchon::Qskill()
{
	cout << "DarkArchon�� Q ��ų : �ǵ��\n";
	cout << "�����¿�� �׸�ŭ ������.\n";
}

void DarkArchon::Wskill()
{
	cout << "DarkArchon�� W ��ų : ���ε� ��Ʈ��\n";
	cout << "���� ��\n\n\n";
}
