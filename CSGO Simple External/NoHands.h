#pragma once

class cNoHands
{
public:
	cNoHands();
	~cNoHands();
	void NoHands();
	void HandsToggle();
	bool NoHandsToggle = false;
	bool getHandsNum = true;
	int hands = NULL;
};

extern cNoHands *pNoHands;