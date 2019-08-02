#pragma once
#include "d3d.h"
#include <vector>

#ifndef WINDOW_NAME
#define WINDOW_NAME "MemeWare by Kwell" //rename this to make ppl think u can code <<i cant>>
#endif

typedef void(*OnFrameFn)();



class C_GUIWindow
{
public:
	C_GUIWindow();
	~C_GUIWindow();

	bool					Create();

	void					OnFrame(int framerate);
	void					AddOnFrame(const OnFrameFn& pFunction) {
								OnFrameVec.push_back(pFunction);
							}

	HWND					GetHwnd() {
								return m_hWnd;
							}
private:
	bool					InitDirectX();

public:
	static LRESULT WINAPI	WndProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	
private:
	HWND							m_hWnd;
	int								m_nSize[2] = { 500, 550 };

	WNDCLASSEX						wc;
	MSG								msg;

	std::vector<OnFrameFn> OnFrameVec;
};