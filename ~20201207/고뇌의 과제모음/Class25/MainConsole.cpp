#include <iostream>
#include "Queen.h"
#include "Zergling.h"
#include "HighTemplar.h"
#include "Reaver.h"
#include "DarkArchon.h"
#include "Wraith.h"
#include "CommandCenter.h"
// 상속받는 애 포함해놓으면 걔가 알아서 엄마 모셔오는듯

using namespace std;

int main()
{
	Zerg a;
	a.output();
	a.racePassive();
	a.Qskill();
	a.Wskill();
	
	Zergling b;
	b.output();
	b.racePassive();
	b.Qskill();
	b.Wskill();
	
	Queen c;
	c.output();
	c.racePassive();
	c.Qskill();
	c.Wskill();

	Protoss d;
	d.output();
	d.racePassive();
	d.Qskill();
	d.Wskill();

	HighTemplar e;
	e.output();
	e.racePassive();
	e.Qskill();
	e.Wskill();

	DarkArchon f;
	f.output();
	f.racePassive();
	f.Qskill();
	f.Wskill();

	Reaver g;
	g.output();
	g.racePassive();
	g.Qskill();
	g.Wskill();
	
	Terran j;
	j.output();
	j.racePassive();
	j.Qskill();
	j.Wskill();

	Wraith h;
	h.output();
	h.racePassive();
	h.Qskill();
	h.Wskill();

	CommandCenter i;
	i.output();
	i.racePassive();
	i.Qskill();
	i.Wskill();

	return 0;
}