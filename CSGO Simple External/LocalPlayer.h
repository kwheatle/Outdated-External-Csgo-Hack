#pragma once

class LocalPlayer
{

public:
	LocalPlayer();
	~LocalPlayer();

	DWORD ClientDLL;
	DWORD EngineDLL;

	DWORD getClientDLL();
	bool getInGame();
	DWORD getLocalPLayer();
	int getFOV();
	DWORD getHandleWeap();
	DWORD getWeaponEntity();
	DWORD getCurrentWeapon();
	DWORD getEngineDLL();
	DWORD getEnemyInCH();
	DWORD getGlowPointer();
	DWORD getLocalEntity();
	DWORD getEnginePointer();
	//DWORD getShotsFired();

	DWORD player;
	DWORD m_dwInGame;

	int getGlowCurrentPlayer(int);
	DWORD getPlayerResource();
	int getPlayerRank(int index);
	int getWeaponID();
	DWORD currentWeaponIndex();
	int getLocalTeam();
	int getCrossHairID();
	int getEnemyHealth();
	int getEnemyTeam();
	int getFlags();
	int getTeam();
	int getHealth();
	int getHandsVal();

	float getFlashMaxAlpha();

	//float getSensitivity();

	//void setSensitivity(float x);
	void getPlayer(int i);

	bool inAir();
	bool isDormant();


};

extern LocalPlayer* pLocalPlayer;