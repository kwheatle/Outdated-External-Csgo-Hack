#pragma once

class cIni
{
public:
	cIni();
	~cIni();
	//static string utf16ToUTF8(const wstring &s);
	void __fastcall readIni();
	void setDllPath();
	char path[MAX_PATH];
	std::string sPath;

private:
	LPSTR lpStr;
};

extern cIni *ini;
