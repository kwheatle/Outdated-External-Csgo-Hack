#include "Includes.h"
cKnifeChanger *pKnife = new cKnifeChanger();

cKnifeChanger::cKnifeChanger()
{

}

cKnifeChanger::~cKnifeChanger()
{

}

void cKnifeChanger::changeKnife()
{
	while (true) {
		if (pLocalPlayer->getWeaponID() == WEAPON_KNIFE || pLocalPlayer->getWeaponID() == WEAPON_KNIFE_T) {
			for (int i = 0; i < 64; i++)
			{
				DWORD ViewModelEntityIndex = Mem->Read<DWORD>(pLocalPlayer->getLocalPLayer() + m_hViewModel +((i - 1) * 0x4)) & 0xFFF;
				DWORD ViewModel = Mem->Read<DWORD>(pLocalPlayer->ClientDLL + entityBase + (ViewModelEntityIndex - 1) * 0x10);
				//Mem->Write<DWORD>(ViewModel + m_nModelIndex, 507);
				Mem->Write<DWORD>(ViewModel + m_nModelIndex, 586);
				//Mem->Write<DWORD>(pLocalPlayer->getCurrentWeapon() + m_iItemDefinitionIndex, WEAPON_KNIFE_KARAMBIT);
				//Mem->Write<DWORD>(pLocalPlayer->getCurrentWeapon() + m_iViewModelIndex, 395);
				Mem->Write<DWORD>(ViewModel + m_iWorldModelIndex, 587);
				//Mem->Write<int>(pLocalPlayer->getEnginePointer() + 0x16C, -1);
			}
		}
	}
}