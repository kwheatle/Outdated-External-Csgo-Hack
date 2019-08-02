#include "Interfaces.h"
#include "Offsets.h"
#include "includes.h"

Interfaces I;
bool CInterfaces::UpdateInterfaces() {
	Mem->Process((XOR("csgo.exe")));
	if (Mem->Module(XOR("client.dll")) == 0) {
		Sleep(300);
		return false;
	}
	if (Mem->Module(XOR("client.dll")) == 0) {
		Sleep(300);
		return false;
	}
	//I.ClientDLL = b.Module("client.dll");
	//I.EngineDLL = b.Module("engine.dll");
	//ReadProcessMemory(b.hProcess, (LPVOID)(I.EngineDLL + m_dwClientState), &I.EnginePointer, sizeof(DWORD), 0);
	//I.EnginePointer = b.Read<DWORD>(I.EngineDLL + m_dwClientState);
	return true;
}