#include "Includes.h"

cNoHands *pNoHands = new cNoHands();

cNoHands::cNoHands()
{

}

cNoHands::~cNoHands()
{

}

void cNoHands::NoHands()
{
	if (getHandsNum == true)
	{
		hands = pLocalPlayer->getHandsVal();
		getHandsNum = false;
	}

	if (NoHandsToggle) {
		Mem->Write<int>(pLocalPlayer->getLocalPLayer() + 0x254, 0);
	}
	else if(!NoHandsToggle) {
		Mem->Write<int>(pLocalPlayer->getLocalPLayer() + 0x254, hands);
	}
}

void cNoHands::HandsToggle()
{
	NoHandsToggle = !NoHandsToggle;
}