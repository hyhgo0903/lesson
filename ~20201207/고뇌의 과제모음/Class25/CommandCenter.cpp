#include "CommandCenter.h"

CommandCenter::CommandCenter()
{
	_hp = 800;
	_atk = 0;
	cout << "CommandCenter Ŭ������ �������Դϴ�. \n\n";
}

CommandCenter::~CommandCenter()
{
	cout << "CommandCenter Ŭ������ �Ҹ����Դϴ�. \n\n";
}

void CommandCenter::output()
{
	cout << "CommandCenter�� HP : " << _hp << endl;
	cout << "CommandCenter�� ���ݷ� : " << _atk << endl;
}

void CommandCenter::Qskill()
{
	cout << "CommandCenter�� Q ��ų : SCV �����\n";
	cout << "���ڸ��ƿ� ���� SCV�� �����մϴ�.\n";
}

void CommandCenter::Wskill()
{
	cout << "CommandCenter�� W ��ų : Ŀ�ǵ� ����\n";
	cout << "�������� �׵� ���� �˹� �ƴմϴ�.\n\n\n";
}
