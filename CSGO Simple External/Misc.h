#pragma once
#include <string>
#include <windows.h>
class cMisc
{
public:
	cMisc();
	~cMisc();

	
	DWORD EngineSize;
	DWORD ClientSize;
	DWORD LocalBase;
	//bool isWeapon();
	//bool isPistol();

	bool glowToggleKeyPressed = true;
	bool bhopToggleKeyPressed = true;
	bool triggerToggleKeyPressed = true;
	bool handsToggleKeyPressed = true;

	bool Trigger = false; //Disabled
	bool NoHands = false;
	bool Noflash = false;
	bool Glow = false;
	bool Bhop = false;
	bool animated = false;
	bool Test;

	float fClosest;
	char cClantag[255] = "Kwell the god";
	bool isFocused();

	void watermark();
	std::string watermarkstrp1 = XOR("|//////    MEME-WARE by Kwell    //////|");
	std::string watermarkstrp2 = XOR("|\\\\\\\\\\\\   youtube.com/c/kwellcs  \\\\\\\\\\\\|");
	int clantag = 0;
	DWORD clantagOffset;

	void bhopEnabled();
	void GlowEnabled();
	void handsEnabled();
	void flashEnabled();
	void triggerEnabled();
	std::string booltostring(bool value);

	void getOffsets();


	void hkCreateMove();

	void SetClanTag(const char * tag, const char * name);

	void TagChanger();
	
	//void forceJump();
	void forceUpdate();
	
	void setClientDLL();
	void setEngineDLL();


	//int getHandsValue();
private:
	DWORD IClientMode;
	DWORD ClientState;
	DWORD ViewAngle;
	DWORD shouldSetAngles, cmdAngleX, cmdAngleY, cmdAngleZ;

};

extern cMisc* pMisc;