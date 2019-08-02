#pragma once

class cTrigger
{
public:
	cTrigger();
	~cTrigger();
	void Trigger();
	DWORD getTriggerKey();
private:
	const DWORD triggerKey = 0x03;
	bool once = false;
	HWND wnd;
};

extern cTrigger *pTrigger;

