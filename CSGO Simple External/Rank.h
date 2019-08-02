#pragma once
#include <fstream>
using namespace std;
typedef unsigned char byte;
class cRank
{
public:
	cRank();
	~cRank();
	void setupRank();
	void showRanks();
	void getRanks();
	int ranks[64];
	DWORD Temporary;
	fstream RankFile;
	DWORD temp = 0x398F60;
private:
	bool once = false;
	LPVOID shellCodeAdd, VectorAdd;
	byte asm_code[20] =
	{
		0x68, 0x00, 0x00, 0x00, 0x00,   // push float* (1)
		0x55, 0x89, 0xE5,               // cdecl call frame
		0xB8, 0x00, 0x00, 0x00, 0x00,   // mov    eax,0x00000000 (9)
		0xFF, 0xD0,                     // call   eax
		0x83, 0xC4, 0x4,                // clear stack
		0x5D,                           // reset call frame
		0xC3                            // return
	};
	const static unsigned int shellSize = sizeof(byte[20]) + 1;
	const unsigned int dataSize = (sizeof(LPVOID) + sizeof(DWORD)) + 2;
	struct Vector3
	{
		float x, y, z;
	};
};

extern cRank *pRank;