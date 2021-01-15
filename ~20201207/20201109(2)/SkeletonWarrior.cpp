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
	cout << "½ºÄÌ·¹Åæ ¿ö¸®¾îÀÇ ¼Ò¸êÀÚ\n";
}

void SkeletonWarrior::Qskill()
{
	cout << "½ºÄÌ·¹ÅæÀÇ Q½ºÅ³\n";
}

void SkeletonWarrior::Wskill()
{
	cout << "½ºÄÌ·¹ÅæÀÇ W½ºÅ³\n";
}
