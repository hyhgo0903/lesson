#pragma once
#include "Undead.h"
class SkeletonWarrior :
	public Undead
{
public:
	SkeletonWarrior();
	~SkeletonWarrior();
	void Qskill();
	// virtual void Qskill(); overide
	// �θ� virtual �ɾ��ָ� �ڽ��Լ����� �ɾ����
	void Wskill();
};

