#include "Includes.h"

cRank *pRank = new cRank();

cRank::cRank()
{

}

cRank::~cRank()
{

}

void cRank::setupRank()
{
	Vector3 bytes;
	bytes.x, bytes.y, bytes.z = 0;
	shellCodeAdd = VirtualAllocEx(Mem->hProcess, NULL, shellSize + dataSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	VectorAdd = VirtualAllocEx(Mem->hProcess, NULL, sizeof(bytes) + 1, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	Mem->WriteLP<Vector3>(VectorAdd, bytes);
	Mem->WriteLPA<byte[20]>(shellCodeAdd, asm_code);
	Mem->WriteLP<LPVOID>((LPVOID)((DWORD)shellCodeAdd + 0x1), VectorAdd);
	Mem->WriteLP<DWORD>((LPVOID)((DWORD)shellCodeAdd + 0x9), pLocalPlayer->ClientDLL + temp);
}

void cRank::showRanks()
{
	HANDLE ranks = CreateRemoteThread(Mem->hProcess, NULL, NULL, (LPTHREAD_START_ROUTINE)shellCodeAdd, NULL, NULL, NULL);
	WaitForSingleObject(ranks, INFINITE);
	CloseHandle(ranks);
}

void cRank::getRanks()
{
	if (!once)
	{
		RankFile.open("Ranks_file.txt", ios::out);

		for (int i = 0; i < 64; i++)
		{
			ranks[i] = pLocalPlayer->getPlayerRank(i);
			RankFile << ranks[i] << endl;
		}
		RankFile.close();
		once = true;
	}
}

/*fstream LogFile;

LogFile.open("Log_file.txt", ios::out);

LogFile << "HELLO" << endl;

LogFile.close();*/