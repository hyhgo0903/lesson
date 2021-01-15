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
	// 부모에 virtual 걸어주면 자식함수에도 걸어줘야
	void Wskill();
};

