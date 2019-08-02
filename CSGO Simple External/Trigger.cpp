#include "Includes.h"

cTrigger *pTrigger = new cTrigger();

cTrigger::cTrigger()
{

}

cTrigger::~cTrigger()
{

}

DWORD cTrigger::getTriggerKey()
{
	return triggerKey;
}

void cTrigger::Trigger()
{
	if (!once)
	{
		wnd = FindWindow(NULL, "Counter-Strike: Global Offensive");
		once = true;
	}
	if (pLocalPlayer->getLocalTeam() != pLocalPlayer->getEnemyTeam() && pLocalPlayer->getCrossHairID() > 0 && pLocalPlayer->getEnemyHealth() > 0) {
		PostMessage(wnd, WM_LBUTTONDOWN, MK_LBUTTON, 0);
		Sleep(1);
		PostMessage(wnd, WM_LBUTTONUP, MK_LBUTTON, 0);
		Sleep(50);
	}
}
