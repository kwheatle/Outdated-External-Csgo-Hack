#pragma once
#include <d3dx9.h>

struct visibleStruct_t
{
	bool player[128];
};

class CVisibleCheck
{
public:
	CVisibleCheck() { hooked = false; }
	bool InitCreateMoveHook();
	bool UpdateVisibleStruct();
	bool IsVisible();
	bool IsVisible(int entityId);
	void Hook(DWORD Instance, int Index, DWORD HookFunc);
private:
	bool hooked;
	DWORD dwVisibleStruct;
	visibleStruct_t visibleStruct;
	
	DWORD GetVFunc(DWORD inst, int Index);
};

extern CVisibleCheck* VisibleCheck;

struct Vector
{
	float x, y, z;
};
struct Angle
{
	float x, y;
};

typedef int(__fastcall* UTIL_TraceLine_t)(const Vector&, const Vector&, unsigned int, const ULONG_PTR, int, ULONG_PTR);

struct hkCreateMoveVars_t
{
// Offsets
	DWORD m_dwUTIL_TraceLine;
	DWORD m_dwClientState;
	DWORD m_dwEntityList;
	DWORD m_dwLocalPlayer;
	DWORD m_dwBoneMatrix;
	DWORD m_vecViewOffset;
	DWORD m_vecOrigin;
	DWORD m_lifeState;
	DWORD m_iTeamNum;
	DWORD m_iHealth;
	DWORD m_bDormant;
	DWORD m_dwTraceOutput; // Output trace_t struct
	visibleStruct_t* visibleStruct; // Player's visible struct
// Local variables
	Vector localOrigin;
	Vector localViewOffset;
	Vector localEyePosition;
	Vector enemyHeadPosition;
	float min_fraction;
};

class CUserCmd
{
public:
	virtual ~CUserCmd( ) { };
	int		command_number;
	int		tick_count;
	Vector	viewangles;
	Vector	aimdirection;
	float	forwardmove;
	float	sidemove;
	float	upmove;
	int		buttons;
	BYTE    impulse;
	int		weaponselect;
	int		weaponsubtype;
	int		random_seed;
	short	mousedx;
	short	mousedy;
	bool	hasbeenpredicted;
	char	pad_0x4C[0x18];
};

struct UserCmd_t
{
	uintptr_t pVft;                // 0x00
	int32_t   m_iCmdNumber;        // 0x04
	int32_t   m_iTickCount;        // 0x08
	Vector    m_vecViewAngles;     // 0x0C
	Vector    m_vecAimDirection;   // 0x18
	float     m_flForwardmove;     // 0x24
	float     m_flSidemove;        // 0x28
	float     m_flUpmove;          // 0x2C
	int32_t   m_iButtons;          // 0x30
	uint8_t   m_bImpulse;          // 0x34
	uint8_t   Pad1[3];
	int32_t   m_iWeaponSelect;     // 0x38
	int32_t   m_iWeaponSubtype;    // 0x3C
	int32_t   m_iRandomSeed;       // 0x40
	int16_t   m_siMouseDx;         // 0x44
	int16_t   m_siMouseDy;         // 0x46
	bool      m_bHasBeenPredicted; // 0x48
	uint8_t   Pad2[27];
};

struct VerifiedUserCmd_t
{
	UserCmd_t m_Command;
	uint32_t  m_Crc;
};

struct Input_t
{
    uintptr_t m_pVftable;                   // 0x00
    bool      m_bTrackIRAvailable;          // 0x04
    bool      m_bMouseInitialized;          // 0x05
    bool      m_bMouseActive;               // 0x06
    bool      m_bJoystickAdvancedInit;      // 0x07
    uint8_t   Unk1[44];                     // 0x08
    uintptr_t m_pKeys;                      // 0x34
    uint8_t   Unk2[100];                    // 0x38
    bool      m_bCameraInterceptingMouse;   // 0x9C
    bool      m_bCameraInThirdPerson;       // 0x9D
    bool      m_bCameraMovingWithMouse;     // 0x9E
    Vector    m_vecCameraOffset;            // 0xA0
    bool      m_bCameraDistanceMove;        // 0xAC
    int32_t   m_nCameraOldX;                // 0xB0
    int32_t   m_nCameraOldY;                // 0xB4
    int32_t   m_nCameraX;                   // 0xB8
    int32_t   m_nCameraY;                   // 0xBC
    bool      m_bCameraIsOrthographic;      // 0xC0
    Vector    m_vecPreviousViewAngles;      // 0xC4
    Vector    m_vecPreviousViewAnglesTilt;  // 0xD0
    float     m_flLastForwardMove;          // 0xDC
    int32_t   m_nClearInputState;           // 0xE0
    uint8_t   Unk3[0x8];                    // 0xE4
    uintptr_t m_pCommands;                  // 0xEC
    uintptr_t m_pVerifiedCommands;          // 0xF0
};

/*class CVerifiedUserCmd {
public:
	CUserCmd  m_cmd;
	CRC32_t   m_crc;
};

typedef unsigned long CRC32_t;

void      CRC32_Init(CRC32_t *pulCRC);
void      CRC32_ProcessBuffer(CRC32_t *pulCRC, const void *p, int len);
void      CRC32_Final(CRC32_t *pulCRC);
CRC32_t	CRC32_GetTableEntry(unsigned int slot);

inline CRC32_t CRC32_ProcessSingleBuffer(const void *p, int len) {
	CRC32_t crc;

	CRC32_Init(&crc);
	CRC32_ProcessBuffer(&crc, p, len);
	CRC32_Final(&crc);

	return crc;
}*/