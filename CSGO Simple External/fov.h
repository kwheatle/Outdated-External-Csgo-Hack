#pragma once
class cFov
{
public:
	cFov();
	~cFov();
	float default;
	bool once = false;
	void setViewFov();
	int fov = 90;
private:

};
extern cFov *pFov;