#include "SkeletonWarrior.h"

SkeletonWarrior::SkeletonWarrior()
{
	_hp = 300;
	_mp = 150;
	_phyAttack = 150;
	_magAttack = 15;
	output();
}

SkeletonWarrior::~SkeletonWarrior()
{
	cout << "���̷��� �������� �Ҹ���\n";
}

void SkeletonWarrior::Qskill()
{
	cout << "���̷����� Q��ų\n";
}

void SkeletonWarrior::Wskill()
{
	cout << "���̷����� W��ų\n";
}
