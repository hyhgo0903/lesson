#include "stdafx.h"
#include "combo22.h"
#include "player.h"

void combo22::EnterState()
{
	_pl->getIndex() = 0;
	if (!_pl->getLeft()) { _pl->getAttack()->Attack(_pl->getGroundRc().right, _pl->getGroundRc().top); }
	if (_pl->getLeft()) { _pl->getAttack()->Attack(_pl->getGroundRc().left - 150, _pl->getGroundRc().top); }
}

void combo22::updateState()
{

    

    if (KEYMANAGER->isOnceKeyDown('Z'))
    {
        _pl->setState(COMBO23);
    }

}

void combo22::ExitState()
{
}
