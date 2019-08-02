#include "Includes.h"

cNoFlash *pNoFlash = new cNoFlash();

cNoFlash::cNoFlash()
{

}

cNoFlash::~cNoFlash()
{

}

void cNoFlash::noFlash()
{
	if (pMisc->Noflash)
	{
		Mem->Write<float>(pLocalPlayer->getLocalPLayer() + FlashMaxAlpha, 0.f);
	}
}

