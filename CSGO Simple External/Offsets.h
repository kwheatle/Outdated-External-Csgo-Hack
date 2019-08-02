#pragma once

#include <cstddef>

#define M_RADPI 57.295779513082f
#define M_PI 3.14159265358979323846f
#define ScreenWidth 1280
#define ScreenHeight 720


//Big antipaste: if you dont know what some of the offsets are by the names i use, you can figure them out pretty easily from the functions
#pragma region offsets
namespace offset {
	// Offsets timestamp
	// Wed, 25 Oct 2017 17:58:41 +0200

	constexpr ::std::ptrdiff_t m_ArmorValue = 0xB238;
	constexpr ::std::ptrdiff_t m_Collision = 0x318;
	constexpr ::std::ptrdiff_t m_CollisionGroup = 0x470;
	constexpr ::std::ptrdiff_t m_Local = 0x2FAC;
	constexpr ::std::ptrdiff_t m_MoveType = 0x258;
	constexpr ::std::ptrdiff_t m_OriginalOwnerXuidHigh = 0x316C;
	constexpr ::std::ptrdiff_t m_OriginalOwnerXuidLow = 0x3168;
	constexpr ::std::ptrdiff_t m_aimPunchAngle = 0x301C;
	constexpr ::std::ptrdiff_t m_aimPunchAngleVel = 0x3028;
	constexpr ::std::ptrdiff_t m_bGunGameImmunity = 0x3894;
	constexpr ::std::ptrdiff_t m_bHasDefuser = 0xB248;
	constexpr ::std::ptrdiff_t m_bHasHelmet = 0xB22C;
	constexpr ::std::ptrdiff_t m_bInReload = 0x3245;
	constexpr ::std::ptrdiff_t m_bIsDefusing = 0x3888;
	constexpr ::std::ptrdiff_t m_bIsScoped = 0x387E;
	constexpr ::std::ptrdiff_t m_bSpotted = 0x939;
	constexpr ::std::ptrdiff_t m_bSpottedByMask = 0x97C;
	constexpr ::std::ptrdiff_t m_dwBoneMatrix = 0x2698;
	constexpr ::std::ptrdiff_t m_fAccuracyPenalty = 0x32B0;
	constexpr ::std::ptrdiff_t m_fFlags = 0x100;
	constexpr ::std::ptrdiff_t m_flFallbackWear = 0x3178;
	constexpr ::std::ptrdiff_t m_flFlashDuration = 0xA2F8;
	constexpr ::std::ptrdiff_t m_flFlashMaxAlpha = 0xA2F4;
	constexpr ::std::ptrdiff_t m_flNextPrimaryAttack = 0x31D8;
	constexpr ::std::ptrdiff_t m_hActiveWeapon = 0x2EE8;
	constexpr ::std::ptrdiff_t m_hMyWeapons = 0x2DE8;
	constexpr ::std::ptrdiff_t m_hObserverTarget = 0x3360;
	constexpr ::std::ptrdiff_t m_hOwner = 0x29BC;
	constexpr ::std::ptrdiff_t m_hOwnerEntity = 0x148;
	constexpr ::std::ptrdiff_t m_iAccountID = 0x2FA8;
	constexpr ::std::ptrdiff_t m_iClip1 = 0x3204;
	constexpr ::std::ptrdiff_t m_iCompetitiveRanking = 0x1A44;
	constexpr ::std::ptrdiff_t m_iCompetitiveWins = 0x1B48;
	constexpr ::std::ptrdiff_t m_iCrosshairId = 0xB2A4;
	constexpr ::std::ptrdiff_t m_iEntityQuality = 0x2F8C;
	constexpr ::std::ptrdiff_t m_iFOVStart = 0x31D8;
	constexpr ::std::ptrdiff_t m_iGlowIndex = 0xA310;
	constexpr ::std::ptrdiff_t m_iHealth = 0xFC;
	constexpr ::std::ptrdiff_t m_iItemDefinitionIndex = 0x2F88;
	constexpr ::std::ptrdiff_t m_iItemIDHigh = 0x2FA0;
	constexpr ::std::ptrdiff_t m_iObserverMode = 0x334C;
	constexpr ::std::ptrdiff_t m_iShotsFired = 0xA2B0;
	constexpr ::std::ptrdiff_t m_iState = 0x31F8;
	constexpr ::std::ptrdiff_t m_iTeamNum = 0xF0;
	constexpr ::std::ptrdiff_t m_lifeState = 0x25B;
	constexpr ::std::ptrdiff_t m_nFallbackPaintKit = 0x3170;
	constexpr ::std::ptrdiff_t m_nFallbackSeed = 0x3174;
	constexpr ::std::ptrdiff_t m_nFallbackStatTrak = 0x317C;
	constexpr ::std::ptrdiff_t m_nForceBone = 0x267C;
	constexpr ::std::ptrdiff_t m_nTickBase = 0x3404;
	constexpr ::std::ptrdiff_t m_rgflCoordinateFrame = 0x440;
	constexpr ::std::ptrdiff_t m_szCustomName = 0x301C;
	constexpr ::std::ptrdiff_t m_szLastPlaceName = 0x3588;
	constexpr ::std::ptrdiff_t m_vecOrigin = 0x134;
	constexpr ::std::ptrdiff_t m_vecVelocity = 0x110;
	constexpr ::std::ptrdiff_t m_vecViewOffset = 0x104;
	constexpr ::std::ptrdiff_t m_viewPunchAngle = 0x3010;

	constexpr ::std::ptrdiff_t dwClientState = 0x5A765C;
	constexpr ::std::ptrdiff_t dwClientState_GetLocalPlayer = 0x180;
	constexpr ::std::ptrdiff_t dwClientState_Map = 0x28C;
	constexpr ::std::ptrdiff_t dwClientState_MapDirectory = 0x188;
	constexpr ::std::ptrdiff_t dwClientState_MaxPlayer = 0x310;
	constexpr ::std::ptrdiff_t dwClientState_PlayerInfo = 0x5240;
	constexpr ::std::ptrdiff_t dwClientState_State = 0x108;
	constexpr ::std::ptrdiff_t dwClientState_ViewAngles = 0x4D10;
	constexpr ::std::ptrdiff_t dwClientState_IsHLTV = 0x4CC8;
	constexpr ::std::ptrdiff_t dwEntityList = 0x4A8D1AC;
	constexpr ::std::ptrdiff_t dwForceAttack = 0x2ECF568;
	constexpr ::std::ptrdiff_t dwForceAttack2 = 0x2ECF574;
	constexpr ::std::ptrdiff_t dwForceBackward = 0x2ECF550;
	constexpr ::std::ptrdiff_t dwForceForward = 0x2ECF5A4;
	constexpr ::std::ptrdiff_t dwForceJump = 0x4F2405C;
	constexpr ::std::ptrdiff_t dwForceLeft = 0x2ECF55C;
	constexpr ::std::ptrdiff_t dwForceRight = 0x2ECF538;
	constexpr ::std::ptrdiff_t dwGameDir = 0x645EE8;
	constexpr ::std::ptrdiff_t dwGameRulesProxy = 0x4F8E3A4;
	constexpr ::std::ptrdiff_t dwGetAllClasses = 0x4F8E478;
	constexpr ::std::ptrdiff_t dwGlobalVars = 0x5A7360;
	constexpr ::std::ptrdiff_t dwGlowObjectManager = 0x4FA9C08;
	constexpr ::std::ptrdiff_t dwInput = 0x4ED7D70;
	constexpr ::std::ptrdiff_t dwInterfaceLinkList = 0x6EC074;
	constexpr ::std::ptrdiff_t dwLocalPlayer = 0xAAFD7C;
	constexpr ::std::ptrdiff_t dwMouseEnable = 0xAB55E0;
	constexpr ::std::ptrdiff_t dwMouseEnablePtr = 0xAB55B0;
	constexpr ::std::ptrdiff_t dwPlayerResource = 0x2ECD8BC;
	constexpr ::std::ptrdiff_t dwRadarBase = 0x4EC1EA4;
	constexpr ::std::ptrdiff_t dwSensitivity = 0xAB547C;
	constexpr ::std::ptrdiff_t dwSensitivityPtr = 0xAB5450;
	constexpr ::std::ptrdiff_t dwViewMatrix = 0x4A7EC04;
	constexpr ::std::ptrdiff_t dwWeaponTable = 0x4ED8964;
	constexpr ::std::ptrdiff_t dwWeaponTableIndex = 0x31FC;
	constexpr ::std::ptrdiff_t dwYawPtr = 0xAB5240;
	constexpr ::std::ptrdiff_t dwZoomSensitivityRatioPtr = 0xABA2A8;
	constexpr ::std::ptrdiff_t dwbSendPackets = 0xCCB8A;
	constexpr ::std::ptrdiff_t dwppDirect3DDevice9 = 0xA1F40;
	constexpr ::std::ptrdiff_t dwSetClanTag = 0x86820;
	constexpr ::std::ptrdiff_t m_pStudioHdr = 0x293C;
}
#pragma endregion


const DWORD playerBase = offset::dwLocalPlayer; //dwlocalPlayer
const DWORD dwPlayerResource = offset::dwPlayerResource;
const DWORD entityBase = offset::dwEntityList; //dwEntityList
const DWORD crosshairOffset = offset::m_iCrosshairId;
const DWORD Flags = 0x00000100;
const DWORD ForceJump = offset::dwForceJump;
const DWORD GlowIndex = offset::m_iGlowIndex;
const DWORD GlowObject = offset::dwGlowObjectManager;
const DWORD Dormant = 0x000000E9;
const DWORD isDormant = 0x000000E9; //Ingore only for aimbot
const DWORD ActiveWeapon = 0x00002EE8;
const DWORD iWeaponID = 0x000032DC;
const DWORD FlashMaxAlpha = offset::m_flFlashMaxAlpha;
const DWORD ForceAttack = offset::dwForceAttack;
const DWORD clientState = offset::dwClientState;
const DWORD m_iFOV = 0x330C;
const DWORD m_hViewModel = 0x32FC;
const DWORD m_hMyWeapons = 0x2DE8;
const DWORD m_iObserverMode = 0x336C;
const DWORD m_iItemDefinitionIndex = 0x2F88;
const DWORD m_iWorldModelIndex = 0x31E4;
const DWORD m_nModelIndex = 0x0254;
const DWORD m_iViewModelIndex = 0x31E0;

//const DWORD dwSensitivityPtr = 0xAB56D0;
//const DWORD dwSensitivity = 0xAB56FC;

const DWORD teamOffset = 0xF0;
const DWORD healthOffset = 0xFC;
const DWORD EntLoopDist = 0x10;

const DWORD bhopToggleKey = 0x61;
const DWORD glowToggleKey = 0x62;
const DWORD handsToggleKey = 0x63;
const DWORD flashToggleKey = 0x64;
const DWORD triggerToggleKey = 0x65;

const DWORD m_szArmsModel = 0x38F3;
const DWORD m_iCompetitiveRanking = 0x1A44;




//const DWORD m_iShotsFired = 0x0000A2C0;


