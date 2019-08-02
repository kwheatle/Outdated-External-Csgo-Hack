#include "Includes.h"

cBhop *pBhop = new cBhop();

cBhop::cBhop()
{

}

cBhop::~cBhop()
{

}

int cBhop::fl_onGround()
{
	return onGround;
}

DWORD cBhop::getBhopKey()
{
	return bhopKey;
}

void cBhop::Bhop()
{
	if (!once)
	{
		wnd = FindWindowA(0, XOR("Counter-Strike: Global Offensive"));
		once = true;
	}

	if (!pLocalPlayer->inAir())
	{
		SendMessage(wnd, WM_KEYDOWN, VK_SPACE, 0x390000);
		Sleep(1);
		
		//Mem->Write<int>(pLocalPlayer->ClientDLL + ForceJump, 5);
	}
	/*else if (pLocalPlayer->inAir())
	{
		Mem->Write<int>(pLocalPlayer->ClientDLL + ForceJump, 4);
		Mem->Write<int>(pLocalPlayer->ClientDLL + ForceJump, 5);
		Mem->Write<int>(pLocalPlayer->ClientDLL + ForceJump, 4);
	}*/
	else
	{
		SendMessage(wnd, WM_KEYUP, VK_SPACE, 0x390000);
		//Mem->Write<int>(pLocalPlayer->ClientDLL + ForceJump, 4);
	}
}
