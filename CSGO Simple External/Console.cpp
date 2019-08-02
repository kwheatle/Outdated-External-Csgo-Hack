#include "includes.h"

cCon *pCon = new cCon;

cCon::cCon()
{

}

cCon::~cCon()
{

}

void cCon::makeCon()
{
	if (FreeConsole()) {
		check = AllocConsole();
	}
	if (check == true)
	{
		freopen("CONIN$", "r", stdin);
		freopen("CONOUT$", "w", stdout);
		freopen("CONIN$", "w", stderr);
	}

}
bool cCon::isCommand(std::string s)
{
	if (s == "FOV")
		return true;
	else if (s == "fov")
		return true;
	else if (s == "knife")
		return true;
	else
		return false;
}
/*
freopen("CONIN$", "r", stdin);
freopen("CONOUT$", "w", stdout);
freopen("CONOUT$", "w", stderr);
*/