#include "Includes.h"

cIni *ini = new cIni();

cIni::cIni()
{
}

cIni::~cIni()
{
}

void cIni::readIni()
{
	pAimbot->AimbotFOV = GetPrivateProfileInt("AIMBOT", "FOV", 2, path);
	pFov->fov = GetPrivateProfileInt("FOV", "startFov", 90, path);
}

void cIni::setDllPath()
{
	HMODULE hm = NULL;

	if (!GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
		GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
		(LPCSTR)"\\confing.ini",
		&hm))
	{
		int ret = GetLastError();
		fprintf(stderr, "GetModuleHandle returned %d\n", ret);
	}
	GetModuleFileNameA(hm, path, sizeof(path));
	sPath = path;
	sPath.erase(sPath.rfind('\\') + 1);
	sPath += "config.ini";
	strcpy(path, sPath.c_str());
}

//x.substr(x.find(":") + 1); 
