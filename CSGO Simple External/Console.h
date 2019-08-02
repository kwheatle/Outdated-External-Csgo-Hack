#pragma once
class cCon
{
public:
	cCon();
	~cCon();
	void makeCon();
	bool check = false;
	//string input;
	//string commands[2] = {"FOV", "fov"};
	int FovNum = 90;
	int tempFov = 0;
	bool isCommand(std::string s);
};

extern cCon *pCon;