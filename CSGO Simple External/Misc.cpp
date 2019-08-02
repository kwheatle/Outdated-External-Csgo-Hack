#include "Includes.h"
using namespace std;

cMisc *pMisc = new cMisc();

cMisc::cMisc()
{

}

cMisc::~cMisc()
{

}

void cMisc::setClientDLL()
{
	pLocalPlayer->ClientDLL = pLocalPlayer->getClientDLL();
}

void cMisc::setEngineDLL()
{
	pLocalPlayer->EngineDLL = pLocalPlayer->getEngineDLL();
}


/*void cMisc::forceJump()
{
	Mem->Write<int>(pLocalPlayer->ClientDLL + ForceJump, 1);
	Sleep(30);
	Mem->Write<int>(pLocalPlayer->ClientDLL + ForceJump, 0);
}*/

bool cMisc::isFocused()
{
	HWND tWnd = FindWindowA(0, XOR("Counter-Strike: Global Offensive"));

	if (GetForegroundWindow() == tWnd)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void cMisc::watermark()
{
	system("cls");
	cout << "     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "     |///////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\|" << endl;
	cout << "     " << XOR(watermarkstrp1) << endl;
	cout << "     " << XOR(watermarkstrp2) << endl;
	cout << "     |///////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\|" << endl;
	cout << "     |//////     NUMPAD 1: BHOP       //////|" << endl;
	cout << "     |/////      NUMPAD 2: GLOW      ///////|" << endl;
	cout << "     |////       NUMPAD 3: NOHANDS  ////////|" << endl;
	cout << "     |\\\\\\\\       NUMPAD 4: NOFLASH  \\\\\\\\\\\\\\\\|" << endl;
	cout << "     |\\\\\\\\\\      NUMPAD 5: TRIGGER   \\\\\\\\\\\\\\|" << endl;
	cout << "     |\\\\\\\\\\\\     NUMPAD 6:            \\\\\\\\\\\\|" << endl;
	cout << "     |///////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\|" << endl;
	cout << "     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	
	cout << "fov: " << pFov->fov << endl;
	cout << "bhop: " << booltostring(Bhop) << endl;
	cout << "glow: " << booltostring(Glow) << endl;
	cout << "nohands: " << booltostring(pNoHands->NoHandsToggle) << endl;
	cout << "noflash: " << booltostring(Noflash) << endl;
	cout << "triggerbot: " << booltostring(Trigger) << endl;
	cout << "Config Path: " << ini->path << endl;
	cout << "Aimbot FOV: " << pAimbot->AimbotFOV << endl;
	//cout << "(DEBUG)hands Value: " << pNoHands->hands << endl;

	cout << "\n\nNOTE: use page up/down to change fov by 10 or type 'fov [num]' in the console" << endl;
}

void cMisc::bhopEnabled()
{
	if (GetAsyncKeyState(bhopToggleKey) & 1)
	{
		Bhop = !Bhop;
		Beep(750, 100);
		watermark();
	}
}

void cMisc::GlowEnabled()
{
	if (GetAsyncKeyState(glowToggleKey) & 1)
	{
		Glow = !Glow;
		Beep(750, 100);
		watermark();
	}
}

void cMisc::handsEnabled()
{
	if (GetAsyncKeyState(handsToggleKey) & 1)
	{
		NoHands = !NoHands;
		Beep(750, 100);
		watermark();
	}
}

void cMisc::flashEnabled()
{
	if (GetAsyncKeyState(flashToggleKey) & 1)
	{
		Noflash = !Noflash;
		Beep(750, 100);
		watermark();
	}
}

void cMisc::triggerEnabled()
{
	if (GetAsyncKeyState(triggerToggleKey) & 1)
	{
		Trigger = !Trigger;
		Beep(750, 100);
		watermark();
	}
}

std::string cMisc::booltostring(bool value)
{
	if (value == 1)
	{
		return "on";
	}
	else
	{
		return "off";
	}
}

/*bool cMisc::isWeapon()
{
	if (pLocalPlayer->getWeaponID() != weapon_knife && pLocalPlayer->getWeaponID() != weapon_c4 && pLocalPlayer->getWeaponID() != weapon_molotov && pLocalPlayer->getWeaponID() != weapon_hegrenade
		&& pLocalPlayer->getWeaponID() != weapon_flashbang && pLocalPlayer->getWeaponID() != weapon_smokegrenade && pLocalPlayer->getWeaponID() != weapon_incgrenade && pLocalPlayer->getWeaponID() != weapon_decoy
		&& pLocalPlayer->getWeaponID() != weapon_taser)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool cMisc::isPistol()
{
	if (pLocalPlayer->getWeaponID() == weapon_glock || pLocalPlayer->getWeaponID() == weapon_usp || pLocalPlayer->getWeaponID() == weapon_deagle || pLocalPlayer->getWeaponID() == weapon_p250
		|| pLocalPlayer->getWeaponID() == weapon_tec9 || pLocalPlayer->getWeaponID() == weapon_hkp2000 || pLocalPlayer->getWeaponID() == weapon_elite || pLocalPlayer->getWeaponID() == weapon_fiveseven)
	{
		return true;
	}
	else
	{
		return false;
	}
}*/

void cMisc::getOffsets()
{
	ViewAngle = Mem->SigScan(pLocalPlayer->EngineDLL, pMisc->EngineSize, "\xF3\x0F\x11\x80\x00\x00\x00\x00\xD9\x46\x04\xD9\x05\x00\x00\x00\x00", "xxxx????xxxxx????") + 0x4;
	ViewAngle = Mem->Read<DWORD>(ViewAngle);
	ClientState = Mem->SigScan(pLocalPlayer->EngineDLL, pMisc->EngineSize, "\xA1\x00\x00\x00\x00\xF3\x0F\x11\x80\x00\x00\x00\x00\xD9\x46\x04\xD9\x05", "x????xxxx????xxxxx") + 0x1;
	ClientState = Mem->Read<DWORD>(clientState);
	ClientState = Mem->Read<DWORD>(clientState);
	IClientMode = Mem->SigScan(pLocalPlayer->ClientDLL, pMisc->ClientSize, "\x8B\x0D\x00\x00\x00\x00\x8B\x01\xFF\x50\x04\x85\xF6", "xx????xxxxxxx") + 0x2;
	IClientMode = Mem->Read<DWORD>(IClientMode);
	IClientMode = Mem->Read<DWORD>(IClientMode);
}


void cMisc::hkCreateMove()
{
		BYTE hook[] = "\x55\x89\xE5\x8B\x55\x0C\x8B\x0D\x00\x00\x00\x00\x83\xF9\x01\x74\x02\xEB\x1A\xA1\x00\x00\x00\x00\x89\x42\x0C\xA1\x00\x00\x00\x00\x89\x42\x10\xA1\x00\x00\x00\x00\x89\x42\x14\xEB\x00\x5D\xC2\x08\x00";
		//full assembly function:
		/*
		push ebp
		mov ebp,esp
		mov edx,DWORD PTR [ebp+0xc]
		mov ecx,[0x00000000]
		cmp ecx, 1
		je setCMDViewAngles
		jmp done
		setCMDViewAngles:
		mov eax,[0x00000000]
		mov [edx+0xc], eax
		mov eax,[0x00000000]
		mov [edx+0x10], eax
		mov eax,[0x00000000]
		mov [edx+0x14], eax
		jmp done
		done:
		pop ebp
		ret 8
		*/
		cmdAngleX = (DWORD)VirtualAllocEx(Mem->hProcess, NULL, sizeof(float) + 1, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
		cmdAngleY = (DWORD)VirtualAllocEx(Mem->hProcess, NULL, sizeof(float) + 1, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
		cmdAngleZ = (DWORD)VirtualAllocEx(Mem->hProcess, NULL, sizeof(float) + 1, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
		shouldSetAngles = (DWORD)VirtualAllocEx(Mem->hProcess, NULL, sizeof(bool) + 1, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
		void* shellCodeAddress = VirtualAllocEx(Mem->hProcess, NULL, sizeof(hook) + 1, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
		if (!Mem->WriteB<float>(cmdAngleX, 0.f))
			return;
		if (!Mem->WriteB<float>(cmdAngleY, 0.f))
			return;
		if (!Mem->WriteB<float>(cmdAngleZ, 0.f))
			return;
		if (!Mem->WriteB<bool>(shouldSetAngles, true))
			return;
		//fill in addresses that (inside CS:GO) point towards the values we set
		*(DWORD*)(&hook[0x8]) = shouldSetAngles;
		*(DWORD*)(&hook[0x14]) = cmdAngleX;
		*(DWORD*)(&hook[0x1C]) = cmdAngleY;
		*(DWORD*)(&hook[0x24]) = cmdAngleZ;
		//directly use wpm since we cant use our hook as a datatype for templates
		if (!WriteProcessMemory(Mem->hProcess, shellCodeAddress, &hook[0], sizeof(hook), NULL))
			return;
		//hook createmove
		VisibleCheck->Hook(IClientMode, 24, (DWORD)shellCodeAddress);
}

const char* AnimatedClantag(std::string tag) {
	static int ticks;
	static std::string _tag = tag;
	if (ticks > 80) {
		ticks = 0;
		int length = tag.length();
		if (length <= 15) {
			for (int i = 0; i <= 15 - length + 1; i++)
				_tag.insert(_tag.length(), " ");
		}
		_tag.insert(0, 1, _tag[15 - 2]);
		_tag.erase(15 - 1, 1);
	}
	else {
		ticks++;
	}
	return _tag.c_str();
}

void cMisc::SetClanTag(const char* tag, const char* name) {

	unsigned char Shellcode[] =
		"\x51"                    //push ecx
		"\x52"                    //push edx
		"\xB9\x00\x00\x00\x00"    //mov ecx,00000000 { 0 }
		"\xBA\x00\x00\x00\x00"    //mov edx,00000000 { 0 }
		"\xE8\x00\x00\x00\x00"    //call 0
		"\x83\x04\x24\x0A"        //add dword ptr [esp],0A { 10 }
		"\x68\x00\x00\x00\x00"    //push engine.dll+9AC90
		"\xC3"                    //ret
		"\x5A"                    //pop edx
		"\x59"                    //pop ecx
		"\xC3"                    //ret
		"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" //reserve memory[0x10]
		"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" //reserve memory[0x10]
		;

	static unsigned int SHELLCODE_SIZE = sizeof(Shellcode) - 0x21;
	unsigned int TAG_SIZE = (strlen(tag) > 15) ? 15 : strlen(tag);
	unsigned int NAME_SIZE = (strlen(name) > 15) ? 15 : strlen(name);
	unsigned int DATA_SIZE = TAG_SIZE + NAME_SIZE + 2;

	void* pShellCodeAdress = VirtualAllocEx(
		Mem->hProcess,
		0,
		SHELLCODE_SIZE + DATA_SIZE,
		MEM_COMMIT | MEM_RESERVE,
		PAGE_EXECUTE_READWRITE
	);

	uintptr_t tagAdress = reinterpret_cast<uintptr_t>(pShellCodeAdress) + SHELLCODE_SIZE;
	uintptr_t nameAdress = reinterpret_cast<uintptr_t>(pShellCodeAdress) + SHELLCODE_SIZE + TAG_SIZE + 1;
	uintptr_t fnSetClanAdress = pLocalPlayer->EngineDLL + clantagOffset;

	memcpy(Shellcode + 0x3, &tagAdress, sizeof(unsigned long));
	memcpy(Shellcode + 0x8, &nameAdress, sizeof(unsigned long));
	memcpy(Shellcode + 0x16, &fnSetClanAdress, sizeof(unsigned long));
	memcpy(Shellcode + SHELLCODE_SIZE, tag, TAG_SIZE);
	memcpy(Shellcode + SHELLCODE_SIZE + TAG_SIZE + 1, name, NAME_SIZE);

	WriteProcessMemory(Mem->hProcess, pShellCodeAdress, Shellcode, SHELLCODE_SIZE + DATA_SIZE, 0);

	HANDLE hThread = CreateRemoteThread(Mem->hProcess, NULL, NULL, (LPTHREAD_START_ROUTINE)pShellCodeAdress, NULL, NULL, NULL);
	WaitForSingleObject(hThread, INFINITE);
	VirtualFreeEx(Mem->hProcess, pShellCodeAdress, 0, MEM_RELEASE);
}

void cMisc::TagChanger() {
	if (!animated) {
		if (clantag == 1) {
			SetClanTag("nohat.", "nohat.");
		}
		else if (clantag == 2) {
			SetClanTag("\n", "\n");
		}
		else if (clantag == 3)
		{
			SetClanTag(cClantag, cClantag);
		}
		else {
			SetClanTag("", "");
		}
	}
	else 
	{
		if (clantag == 1) {
			SetClanTag(AnimatedClantag("nohat."), "nohat.");
		}
		else if (clantag == 2) {
			SetClanTag(AnimatedClantag("\n"), "\n");
		}
		else if (clantag == 3)
		{
			SetClanTag(AnimatedClantag(cClantag), cClantag);
		}
		else {
			SetClanTag("", "");
		}
	}
}

/*
auto dwClientCMD = g_pMemory->FindPattern(Variable->Engine_DLL, "\x55\x8B\xEC\xA1\x00\x00\x00\x00\x81\xEC\x00\x00\x00\x00\x80\xB8", "xxxx????xx????xx");
...
void ClientCMD(const char* command)
{
auto vCommand = (LPVOID)VirtualAllocEx(g_pMemory->GetProcess(), NULL, strlen(command) + 1, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
WriteProcessMemory(g_pMemory->GetProcess(), vCommand, command, strlen(command), NULL);
auto hThread = CreateRemoteThread(g_pMemory->GetProcess(), NULL, NULL, (LPTHREAD_START_ROUTINE)dwClientCMD, vCommand, NULL, NULL);
WaitForSingleObject(hThread, INFINITE);
CloseHandle(hThread);
VirtualFreeEx(g_pMemory->GetProcess(), vCommand, strlen(command) + 1, MEM_RELEASE);
}

void cMisc::SetClanTag(const char* tag, const char* name) {

unsigned char Shellcode[] =
"\x51"                    //push ecx
"\x52"                    //push edx
"\xB9\x00\x00\x00\x00"    //mov ecx,00000000 { 0 }
"\xBA\x00\x00\x00\x00"    //mov edx,00000000 { 0 }
"\xE8\x00\x00\x00\x00"  //call 0
"\x83\x04\x24\x0A"      //add dword ptr [esp],0A { 10 }
"\x68\x00\x00\x00\x00"    //push engine.dll+9AC90
"\xC3"                    //ret
"\x5A"                    //pop edx
"\x59"                    //pop ecx
"\xC3"                    //ret
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" //reserve memory[0x10]
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" //reserve memory[0x10]
;

static unsigned int SHELLCODE_SIZE = sizeof(Shellcode) - 0x21;
unsigned int TAG_SIZE = (strlen(tag) > 15) ? 15 : strlen(tag);
unsigned int NAME_SIZE = (strlen(name) > 15) ? 15 : strlen(name);
unsigned int DATA_SIZE = TAG_SIZE + NAME_SIZE + 2;

void* pShellCodeAdress = VirtualAllocEx(
Core::Mem->hProcess,
0,
SHELLCODE_SIZE + DATA_SIZE,
MEM_COMMIT | MEM_RESERVE,
PAGE_EXECUTE_READWRITE
);

uintptr_t tagAdress = reinterpret_cast<uintptr_t>(pShellCodeAdress) + SHELLCODE_SIZE;
uintptr_t nameAdress = reinterpret_cast<uintptr_t>(pShellCodeAdress) + SHELLCODE_SIZE + TAG_SIZE + 1;
uintptr_t fnSetClanAdress = Csgo::Process::EngineDLL + Csgo::Offsets::Signatures::clantagOffset;

memcpy(Shellcode + 0x3, &tagAdress, sizeof(unsigned long));
memcpy(Shellcode + 0x8, &nameAdress, sizeof(unsigned long));
memcpy(Shellcode + 0x16, &fnSetClanAdress, sizeof(unsigned long));
memcpy(Shellcode + SHELLCODE_SIZE, tag, TAG_SIZE);
memcpy(Shellcode + SHELLCODE_SIZE + TAG_SIZE + 1, name, NAME_SIZE);

WriteProcessMemory(Core::Mem->hProcess, pShellCodeAdress, Shellcode, SHELLCODE_SIZE + DATA_SIZE, 0);

HANDLE hThread = CreateRemoteThread(Core::Mem->hProcess, NULL, NULL, (LPTHREAD_START_ROUTINE)pShellCodeAdress, NULL, NULL, NULL);
WaitForSingleObject(hThread, INFINITE);
VirtualFreeEx(Core::Mem->hProcess, pShellCodeAdress, 0, MEM_RELEASE);
}

*/

