//#include "CGeneralEntity.h"
#include "Includes.h"

/*enum ItemDefinitionIndex
{
	WEAPON_NONE,
	WEAPON_DEAGLE = 1,
	WEAPON_ELITE = 2,
	WEAPON_FIVESEVEN = 3,
	WEAPON_GLOCK = 4,
	WEAPON_AK47 = 7,
	WEAPON_AUG = 8,
	WEAPON_AWP = 9,
	WEAPON_FAMAS = 10,
	WEAPON_G3SG1 = 11,
	WEAPON_GALILAR = 13,
	WEAPON_M249 = 14,
	WEAPON_M4A1 = 16,
	WEAPON_MAC10 = 17,
	WEAPON_P90 = 19,
	WEAPON_UMP45 = 24,
	WEAPON_XM1014 = 25,
	WEAPON_BIZON = 26,
	WEAPON_MAG7 = 27,
	WEAPON_NEGEV = 28,
	WEAPON_SAWEDOFF = 29,
	WEAPON_TEC9 = 30,
	WEAPON_TASER = 31,
	WEAPON_HKP2000 = 32,
	WEAPON_MP7 = 33,
	WEAPON_MP9 = 34,
	WEAPON_NOVA = 35,
	WEAPON_P250 = 36,
	WEAPON_SCAR20 = 38,
	WEAPON_SG556 = 39,
	WEAPON_SSG08 = 40,
	WEAPON_KNIFEGG = 41,
	WEAPON_KNIFE = 42,
	WEAPON_FLASHBANG = 43,
	WEAPON_HEGRENADE = 44,
	WEAPON_SMOKEGRENADE = 45,
	WEAPON_MOLOTOV = 46,
	WEAPON_DECOY = 47,
	WEAPON_INCGRENADE = 48,
	WEAPON_C4 = 49,
	WEAPON_KNIFE_T = 59,
	WEAPON_M4A1_SILENCER = 60,
	WEAPON_USP_SILENCER = 61,
	WEAPON_CZ75A = 63,
	WEAPON_R8REVOLVER = 64,
	WEAPON_KNIFE_BAYONET = 500,
	WEAPON_KNIFE_FLIP = 505,
	WEAPON_KNIFE_GUT = 506,
	WEAPON_KNIFE_KARAMBIT = 507,
	WEAPON_KNIFE_M9_BAYONET = 508,
	WEAPON_KNIFE_TACTICAL = 509,
	WEAPON_KNIFE_FALCHION = 512,
	WEAPON_KNIFE_BUTTERFLY = 515,
	WEAPON_KNIFE_PUSH = 516
};*/

CGeneralEntity::CGeneralEntity() {
	// Create CGeneralEntity object
	//ReadProcessMemory(b.hProcess, (LPVOID)(I.ClientDLL + m_dwLocalPlayer), &LocalPlayer, sizeof(DWORD), NULL);
}

CGeneralEntity::CGeneralEntity(DWORD Player) :LocalPlayer(Player) {
	// Overrided constructor, used for setting up a NON-LOCAL player with a given LocalPlayer
}

CGeneralEntity::~CGeneralEntity() {
	// Destroy CGeneralEntity object
}

bool CGeneralEntity::SetAndValidate() {
	LocalPlayer = pLocalPlayer->getLocalPLayer();
	//cout << LocalPlayer << endl;
	if (LocalPlayer != 0) {
		Dormant = Mem->Read<bool>(LocalPlayer + isDormant);
		if (!Dormant) {
			//ReadProcessMemory(b.hProcess, (LPVOID)(LocalPlayer + m_lifeState), &LifeState, sizeof(bool), NULL);
			LifeState = Mem->Read<bool>(LocalPlayer + offset::m_lifeState);
			if (!LifeState) {
				//std::cout << "Reading Shit!";
				//ReadProcessMemory(b.hProcess, (LPVOID)(LocalPlayer + m_iTeamNum), &TeamNumber, sizeof(int), NULL);
				TeamNumber = Mem->Read<int>(LocalPlayer + TeamNumber);
				ReadProcessMemory(Mem->hProcess, (LPVOID)(LocalPlayer + offset::m_viewPunchAngle), &PunchAngles, sizeof(D3DXVECTOR3), NULL);
				//ReadProcessMemory(b.hProcess, (LPVOID)(LocalPlayer + m_fFlags), &Flags, sizeof(BYTE), NULL);
				//Flags = pLocalPlayer->getFlags();
				ReadProcessMemory(Mem->hProcess, (LPVOID)(pLocalPlayer->getEnginePointer() + offset::dwClientState_ViewAngles), &ViewAngles, sizeof(D3DXVECTOR3), NULL);
				ReadProcessMemory(Mem->hProcess, (LPVOID)(LocalPlayer + offset::m_vecOrigin), &VecOrigin, sizeof(D3DXVECTOR3), NULL);
				ReadProcessMemory(Mem->hProcess, (LPVOID)(LocalPlayer + offset::m_vecViewOffset), &VecView, sizeof(D3DXVECTOR3), NULL);
				ReadProcessMemory(Mem->hProcess, (LPVOID)(pLocalPlayer->ClientDLL + offset::dwViewMatrix), &WorldToScreenMatrix, sizeof(WorldToScreenMatrix_t), NULL);
				ReadProcessMemory(Mem->hProcess, (LPVOID)(LocalPlayer + offset::m_vecVelocity), &Velocity , sizeof(D3DXVECTOR3), NULL);
				//ReadProcessMemory(b.hProcess, (LPVOID)(LocalPlayer + 0x2670), &vecForce, sizeof(D3DXVECTOR3), NULL);
				LocalPos = VecOrigin + VecView; //Position of eyes
				localPlayerWeaponID = getWeaponId();
				return true;
				//ReadProcessMemory(b.hProcess, (LPVOID)(LocalPlayer + m_dwBoneMatrix), &BoneMatrix, sizeof(tDataStructs::tBoneMatrix), NULL);
			}
			return false;
		}
		return false;
	}
	return false;
}

bool CGeneralEntity::SetAndValidateEntity() {
	if (LocalPlayer != 0) {
		//ReadProcessMemory(Mem->hProcess, (LPVOID)(LocalPlayer + m_bDormant), &Dormant, sizeof(bool), NULL);
		Dormant = Mem->Read<bool>(LocalPlayer + isDormant);
		if (!Dormant) {
			//ReadProcessMemory(Mem->hProcess, (LPVOID)(LocalPlayer + m_lifeState), &LifeState, sizeof(bool), NULL);
			LifeState = Mem->Read<bool>(LocalPlayer + offset::m_lifeState);
			if (!LifeState) {
				//ReadProcessMemory(Mem->hProcess, (LPVOID)(LocalPlayer + m_iTeamNum), &TeamNumber, sizeof(int), NULL);
				TeamNumber = Mem->Read<int>(LocalPlayer + teamOffset);
				//ReadProcessMemory(Mem->hProcess, (LPVOID)(LocalPlayer + m_fFlags), &Flags, sizeof(BYTE), NULL);
				//Flags = pLocalPlayer->getFlags();
				//ReadProcessMemory(b.hProcess, (LPVOID)(LocalPlayer + m_dwViewAngles), &ViewAngles, sizeof(D3DXVECTOR3), NULL); DEFAULT COMMENTED
				//ReadProcessMemory(b.hProcess, (LPVOID)(LocalPlayer + m_dwBoneMatrix), &BoneMatrixAddress, sizeof(DWORD), NULL);
				BoneMatrixAddress = Mem->Read<DWORD>(LocalPlayer + offset::m_dwBoneMatrix);
				ReadProcessMemory(Mem->hProcess, (LPVOID)(BoneMatrixAddress), &BoneMatrix, sizeof(tDataStructs::tBoneMatrix), NULL);
				//ReadProcessMemory(b.hProcess, (LPVOID)(LocalPlayer + offset::m_bSpotted), &Spotted, sizeof(bool), NULL);
				Spotted = Mem->Read<bool>(LocalPlayer + offset::m_bSpotted);
				LocalPos = VecOrigin + VecView;
				ReadProcessMemory(Mem->hProcess, (LPVOID)(LocalPlayer + offset::m_vecOrigin), &VecOrigin, sizeof(D3DXVECTOR3), NULL);
				ReadProcessMemory(Mem->hProcess, (LPVOID)(LocalPlayer + offset::m_vecViewOffset), &VecView, sizeof(D3DXVECTOR3), NULL);
				ReadProcessMemory(Mem->hProcess, (LPVOID)(LocalPlayer + offset::m_vecVelocity), &Velocity, sizeof(D3DXVECTOR3), NULL);
				getClassID();
				return true;
			}
			return false;
		}
		return false;
	}
	return false;
}

D3DXVECTOR3 CGeneralEntity::GetBonePosition(int BoneNumber)
{
	D3DXVECTOR3 BonePosition;
	BonePosition.x = BoneMatrix.Bones[BoneNumber].x;
	BonePosition.y = BoneMatrix.Bones[BoneNumber].y;
	BonePosition.z = BoneMatrix.Bones[BoneNumber].z;
	return BonePosition;
}

void CGeneralEntity::getClassID()
{
	int vt = Mem->Read<DWORD>(LocalPlayer + 0x8);
	int fn = Mem->Read<DWORD>(vt + 2 * 0x4);
	int cls = Mem->Read<DWORD>(fn + 0x1);
	int clsn = Mem->Read<DWORD>(cls + 8);
	ClassID = Mem->Read<int>(cls + 20);
}

#pragma region WEAPON CHECKS
bool CGeneralEntity::isNonAimWeapon()
{
	if (isWeaponKnife() || isWeaponGrenade() || isWeaponBomb() || isWeaponTaser() || isWeaponShotgun())
		return true;

	return false;
}
int CGeneralEntity::getWeaponId()
{
	return Mem->Read<int>(getCurrentWeapon() + m_iItemDefinitionIndex);
}
DWORD CGeneralEntity::getCurrentWeapon()
{
	return Mem->Read<DWORD>(I.ClientDLL + entityBase + (getWeapEnt() - 1) * 0x10);
}
int CGeneralEntity::getWeapEnt()
{
	return getHandleWeap() & 0xFFF;
}
DWORD CGeneralEntity::getHandleWeap()
{
	return Mem->Read<DWORD>(LocalPlayer + offset::m_hActiveWeapon);
}

bool CGeneralEntity::isWeaponRifle() {

	if (localPlayerWeaponID == WEAPON_AK47 || localPlayerWeaponID == WEAPON_AUG || localPlayerWeaponID == WEAPON_BIZON || localPlayerWeaponID == WEAPON_FAMAS || localPlayerWeaponID == WEAPON_GALILAR
		|| localPlayerWeaponID == WEAPON_M249 || localPlayerWeaponID == WEAPON_M4A1 || localPlayerWeaponID == WEAPON_M4A1_SILENCER || localPlayerWeaponID == WEAPON_MAC10 || localPlayerWeaponID == WEAPON_MP7
		|| localPlayerWeaponID == WEAPON_MP9 || localPlayerWeaponID == WEAPON_NEGEV || localPlayerWeaponID == WEAPON_SG556 || localPlayerWeaponID == WEAPON_UMP45)
		return true;
	else
		return false;
}

bool CGeneralEntity::isWeaponSniper() {
	if (localPlayerWeaponID == WEAPON_AWP || localPlayerWeaponID == WEAPON_SCAR20 || localPlayerWeaponID == WEAPON_G3SG1 || localPlayerWeaponID == WEAPON_SSG08) {
		return true;
	}
	else
		return false;
}
bool CGeneralEntity::isWeaponPistol() {
	if (localPlayerWeaponID == WEAPON_CZ75A || localPlayerWeaponID == WEAPON_DEAGLE || localPlayerWeaponID == WEAPON_ELITE || localPlayerWeaponID == WEAPON_GLOCK || localPlayerWeaponID == WEAPON_FIVESEVEN
		|| localPlayerWeaponID == WEAPON_HKP2000 || localPlayerWeaponID == WEAPON_R8REVOLVER || localPlayerWeaponID == WEAPON_USP_SILENCER || localPlayerWeaponID == WEAPON_P250 || localPlayerWeaponID == WEAPON_TEC9) {
		return true;
	}
	else
		return false;
}
bool CGeneralEntity::isWeaponKnife()
{
	if (localPlayerWeaponID == WEAPON_KNIFE || localPlayerWeaponID == WEAPON_KNIFE_T || localPlayerWeaponID == WEAPON_KNIFEGG)
		return true;

	return false;
}
bool CGeneralEntity::isWeaponGrenade()
{
	if (localPlayerWeaponID == WEAPON_FLASHBANG || localPlayerWeaponID == WEAPON_HEGRENADE || localPlayerWeaponID == WEAPON_SMOKEGRENADE || localPlayerWeaponID == WEAPON_MOLOTOV || localPlayerWeaponID == WEAPON_INCGRENADE || localPlayerWeaponID == WEAPON_DECOY)
		return true;

	return false;
}

bool CGeneralEntity::isWeaponBomb()
{
	if (localPlayerWeaponID == WEAPON_C4)
		return true;

	return false;
}

bool CGeneralEntity::isWeaponTaser()
{
	if (localPlayerWeaponID == WEAPON_TASER)
		return true;

	return false;
}

bool CGeneralEntity::isWeaponShotgun()
{
	if (localPlayerWeaponID == WEAPON_NOVA || localPlayerWeaponID == WEAPON_SAWEDOFF || localPlayerWeaponID == WEAPON_XM1014 || localPlayerWeaponID == WEAPON_MAG7)
		return true;

	return false;
}
#pragma endregion