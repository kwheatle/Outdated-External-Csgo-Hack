#include "Includes.h"
#include "dropdownarrays.h"

/*
#include "imgui.h"
#include "imgui-sfml.h"

//#include <windows.h>
#include <d3d9.h>
//#include <iostream>
//#include <d3dx9.h>
#include <Dwmapi.h> 
#include <TlHelp32.h>
*/
#include "from dxtest\Globals.h"
#include "imgui.h"
#include "../../ImGUI/DX9/imgui_impl_dx9.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <windows.h>
#include <d3d9.h>
#include <iostream>
#include <d3dx9.h>
#include <Dwmapi.h> 
#include <TlHelp32.h>

#define EXPORTING_DLL
#define PGUP 33
#define PGDOWN 34
#define wndheight 514
#define wndwidth 485
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9")

HANDLE threadLoop;
HANDLE bhopLoop;
HANDLE noLoop;
HANDLE glowLoop;
HANDLE conLoop;
HANDLE fovLoop;
HANDLE triggerLoop;
HANDLE aimLoop;
HANDLE visLoop;
HWND newhwnd;

bool open = true;

int s_width = 800;
int s_height = 600;
#define CENTERX (GetSystemMetrics(SM_CXSCREEN)/2)-(s_width/2)
#define CENTERY (GetSystemMetrics(SM_CYSCREEN)/2)-(s_height/2)
IDirect3D9Ex* d3d;    // the pointer to our Direct3D interface
IDirect3DDevice9Ex* d3ddev;
HWND hWnd;
const MARGINS  margin = { 0,0,s_width,s_height };
ID3DXFont* pFont;


RECT rc;
int Default;

//int s_width, s_height = 500;
bool onetime = false;

string name = XOR("Memeware by youtube.com/c/kwellcs");
char cName[1024];



DWORD WINAPI no(LPVOID lpParam) {
	while (noLoop) {
		if (pLocalPlayer->getFlashMaxAlpha() > 50.f)
		{
			pNoFlash->noFlash();
		}

		if (pNoHands->NoHandsToggle)
		{
			pNoHands->NoHands();
		}
		Sleep(5);
	}
	return 0;
}

DWORD WINAPI glow(LPVOID lpParam) {
	while (glowLoop) {
		if (pMisc->Glow)
		{
			pGlow->GlowEsp();
			Sleep(1);
		}
	}
	return 0;
}

DWORD WINAPI console(LPVOID lpParam) {
	while (true) {
		//Overlay->RefreshOverlay();
	}
	return 0;
}

DWORD WINAPI aim(LPVOID lpParam) {
	Aimbot cAimbot;
	CGeneralEntity LocalPlayer;
	while (!LocalPlayer.SetAndValidate()) {
		//cout << "nope" << endl;
		Sleep(500);
	}
	while (aimLoop) {
		LocalPlayer.SetAndValidate();
		cAimbot.Tick(LocalPlayer);
		if (pMisc->Trigger && GetAsyncKeyState(0x03) & 0x8000)
		{
			pTrigger->Trigger();
		}
		Sleep(1);
	}
	return 0;
}

DWORD WINAPI vis(LPVOID lpParam) {
	VisibleCheck->InitCreateMoveHook();
	while (visLoop) {
		VisibleCheck->UpdateVisibleStruct();
		Sleep(1);
	}
	return 0;
}

DWORD WINAPI bhop(LPVOID lpParam) {
	while (bhopLoop)
	{
		if (pMisc->isFocused())
		{
			if ((pMisc->Bhop && GetAsyncKeyState(pBhop->getBhopKey()) & 0x8000))
			{
				pBhop->Bhop();
			}
		}

		Sleep(1);
	}
	return 0;
}

bool setTransparency(HWND hWnd, unsigned char alpha)
{
	SetWindowLongPtr(hWnd, GWL_EXSTYLE, GetWindowLongPtr(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	SetLayeredWindowAttributes(hWnd, COLORREF(0xFFFFFF), alpha, LWA_COLORKEY);
	return true;
}

bool WasInit;

void GUI_Init() {

	if (WasInit)
		return;

	ImGuiStyle& style = ImGui::GetStyle();

	style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.6f, 0.6f, 0.6f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.3f, 0.3f, 0.3f, 1.00f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.125f, 0.65f, 0.18f, 0.86f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.04f, 0.04f, 0.04f, 0.88f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.13f, 0.13f, 0.13f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.125f, 0.78f, 0.18f, 0.86f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.24f, 0.40f, 0.95f, 0.59f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.48f, 0.48f, 0.48f, 1.00f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.125f, 0.78f, 0.18f, 0.86f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.125f, 0.78f, 0.18f, 0.86f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.40f, 0.95f, 0.59f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.125f, 0.78f, 0.18f, 0.86f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.24f, 0.40f, 0.95f, 0.59f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.70f, 0.02f, 0.60f, 0.22f);
	style.Colors[ImGuiCol_CloseButton] = ImVec4(0.125f, 0.78f, 0.18f, 0.86f);
	style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.24f, 0.40f, 0.95f, 0.59f);
	style.Colors[ImGuiCol_ComboBg] = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);

	style.WindowRounding = 10.0f;
	style.WindowTitleAlign = ImVec2(0.5f, 5.f);
	style.FramePadding = ImVec2(0, 0);//(4, 1);
	style.ScrollbarSize = 10.f;
	style.ScrollbarRounding = 0.1f;
	style.GrabMinSize = 5.f;

	//strcpy(cName, name.c_str());

	FreeConsole();
	HWND cheatconsole = FindWindowA(NULL, "Kwell's External");
	CloseWindow(cheatconsole);

	WasInit = true;
}

bool getcsPos() {
	if (!onetime) {
		newhwnd = FindWindow(NULL, "Counter-Strike: Global Offensive");
		onetime = true;
	}
	if (newhwnd != NULL) {
		GetWindowRect(newhwnd, &rc);
		s_width = rc.right - rc.left;
		s_height = rc.bottom - rc.top;
		return true;
	}
	return false;
}

/*DWORD WINAPI OnFrame(LPVOID lpParam) {
	GUI_Init();
	//auto &io = ImGui::GetIO();
	//io.MouseDrawCursor = true;

	sf::RenderWindow window(sf::VideoMode(wndwidth, wndheight), XOR(cName), sf::Style::None);
	window.setPosition(ImVec2(rc.left + 20, rc.top + 50));
	window.setFramerateLimit(30);
	ImGui::SFML::Init(window);

	window.resetGLStates(); // call it if you only draw ImGui. Otherwise not needed.
	sf::Clock deltaClock;
	bool open = true;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);

			if (event.type == sf::Event::Closed) {
				window.close();
			}

			window.display();
			/*if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					grabbedOffset = window.getPosition() - sf::Mouse::getPosition();
					grabbedWindow = true;
				}
			}
			else if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
					grabbedWindow = false;
			}
			else if (event.type == sf::Event::MouseMoved)
			{
				if (grabbedWindow)
					window.setPosition(sf::Mouse::getPosition() + grabbedOffset);
			}
		}

		ImGui::SFML::Update(window, deltaClock.restart());

		
		if (GetAsyncKeyState(VK_INSERT) & 1) {
			open = !open;
			window.setVisible(open);
		}
		if (open) {
			getcsPos();
			if (!window.hasFocus()) {
				window.requestFocus();
			}
			window.setPosition(ImVec2(rc.left + 20, rc.top + 50));
			ImGui::SetNextWindowPos(ImVec2(0, 0));
			ImGui::Begin(XOR(cName), &open, ImVec2(wndwidth, wndheight), 0.9f, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus); {
				ImGui::Columns(1, "", false);
				ImGui::Text("Stuff");
				ImGui::Separator();
				ImGui::Checkbox("Bunnyhop", &pMisc->Bhop);
				ImGui::Checkbox("Glow", &pMisc->Glow);
				ImGui::Checkbox("Noflash", &pMisc->Noflash);
				ImGui::Checkbox("TriggerBot", &pMisc->Trigger);
				ImGui::Checkbox("Nohands", &pNoHands->NoHandsToggle);
				ImGui::Separator();

				if (ImGui::SliderInt("FOV", &pFov->fov, 10, 180)) {
					pFov->setViewFov();
				}
				ImGui::NextColumn();
				if (ImGui::Button("Reset Fov", ImVec2(100, 15))) {
					pFov->fov = 90;
					pFov->setViewFov();
				}
				ImGui::NewLine();
				if (ImGui::InputText("Custom ClanTag", pMisc->cClantag, sizeof(pMisc->cClantag))) {
					if (pMisc->clantag == 3) {
						pMisc->TagChanger();
					}
				}
				if (ImGui::Combo("Clantag changer", &pMisc->clantag, clantagTypes, ARRAYSIZE(clantagTypes))) {
					pMisc->TagChanger();
				}
				/*ImGui::NextColumn();
				ImGui::Checkbox("Animated Tag", &pMisc->animated);

				ImGui::NewLine();
				ImGui::NewLine();
				ImGui::NewLine();
				ImGui::NewLine();
				ImGui::NewLine();
				ImGui::NewLine();
				if (ImGui::Button("Close Cheat", ImVec2(100, 25))) {
					window.close();
					std::exit(0);
				}
				ImGui::SameLine();
				if (ImGui::Button("Reload Config", ImVec2(100, 25))) {
					ini->readIni();
					pFov->setViewFov();
				}
			}
			ImGui::End();
			window.clear(sf::Color(255, 255, 255));
			//window.setPosition(ImVec2(rc.left + 20, rc.top + 50));
			//setTransparency(window.getSystemHandle(), 255);
			ImGui::SFML::Render(window);
			window.display();
		}
	}
	pFov->fov = 90;
	pFov->setViewFov();
	ImGui::SFML::Shutdown();
	return 0;
}*/


DWORD WINAPI Loop(PVOID pThreadParameter)
{
	/*pCon->makeCon();
	//Done here incase a thread that prints to console loads faster than the console thread
	ini->setDllPath();
	ini->readIni();
	SetConsoleTitle("Kwell's External");
	pMisc->watermark();

	Mem->Process(XOR("csgo.exe"));

	pMisc->setClientDLL(); //getting DLL's
	pMisc->setEngineDLL();
	pMisc->ClientSize = Mem->ModuleSize("client.dll");
	pMisc->EngineSize = Mem->ModuleSize("engine.dll");

	pMisc->clantagOffset = Mem->SigScan(pLocalPlayer->EngineDLL, pMisc->EngineSize, "\x53\x56\x57\x8B\xDA\x8B\xF9\xFF\x15\x00\x00\x00\x00", "xxxxxxxxx????");
	pMisc->clantagOffset -= pLocalPlayer->EngineDLL;

	OnFrame();

	//GUIWindow->Create();
	//GUIWindow->AddOnFrame(OnFrame);
	//ImGui::ShowTestWindow();

	bhopLoop = CreateThread(0, 0, &bhop, 0, 0, NULL);
	aimLoop = CreateThread(0, 0, &aim, 0, 0, NULL);
	noLoop = CreateThread(0, 0, &no, 0, 0, NULL);
	visLoop = CreateThread(0, 0, &vis, 0, 0, NULL);
	glowLoop = CreateThread(0, 0, &glow, 0, 0, NULL);
	conLoop = CreateThread(0, 0, &console, 0, 0, NULL);
	fovLoop = CreateThread(0, 0, &fov, 0, 0, NULL);
	triggerLoop = CreateThread(0, 0, &trigger, 0, 0, NULL);


	//pRank->setupRank();

	//pMisc->getOffsets();
	//pMisc->hkCreateMove();*/

	while (threadLoop)
	{
		assert(threadLoop);

		if (pMisc->isFocused())
		{
			pMisc->handsEnabled();
			pMisc->flashEnabled();
			pMisc->triggerEnabled();
			pMisc->GlowEnabled();
			pMisc->bhopEnabled();

			//pRank->showRanks();
		}
		Sleep(1);
	}

	return 0;
}



/*int main(){

	//pCon->makeCon();
	//Done here incase a thread that prints to console loads faster than the console thread
	ini->setDllPath();
	ini->readIni();
	SetConsoleTitle("Kwell's External");
	pMisc->watermark();

	Mem->Process(XOR("csgo.exe"));

	getcsPos();

	pMisc->setClientDLL(); //getting DLL's
	pMisc->setEngineDLL();
	pMisc->ClientSize = Mem->ModuleSize("client.dll");
	pMisc->EngineSize = Mem->ModuleSize("engine.dll");

	pMisc->clantagOffset = Mem->SigScan(pLocalPlayer->EngineDLL, pMisc->EngineSize, "\x53\x56\x57\x8B\xDA\x8B\xF9\xFF\x15\x00\x00\x00\x00", "xxxxxxxxx????");
	pMisc->clantagOffset -= pLocalPlayer->EngineDLL;

	pFov->setViewFov();
	pMisc->watermark();

	GUI_Init();

	HANDLE rghThreads[] = {
	//CreateThread(0, 0, &OnFrame, 0, 0, NULL),
	bhopLoop = CreateThread(0, 0, &bhop, 0, 0, NULL),
	aimLoop = CreateThread(0, 0, &aim, 0, 0, NULL),
	noLoop = CreateThread(0, 0, &no, 0, 0, NULL),
	visLoop = CreateThread(0, 0, &vis, 0, 0, NULL),
	glowLoop = CreateThread(0, 0, &glow, 0, 0, NULL),
	conLoop = CreateThread(0, 0, &console, 0, 0, NULL),
	//fovLoop = CreateThread(0, 0, &clantag, 0, 0, NULL),
	//threadLoop = CreateThread(0, 0, Loop, 0, 0, NULL)
	};




	WaitForMultipleObjects(sizeof(rghThreads) / sizeof(HANDLE), rghThreads, TRUE, INFINITE);
	return(0);
}*/

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void initD3D(HWND hWnd)
{
	Direct3DCreate9Ex(D3D_SDK_VERSION, &d3d);    // create the Direct3D interface

	D3DPRESENT_PARAMETERS d3dpp;    // create a struct to hold various device information

	ZeroMemory(&d3dpp, sizeof(d3dpp));    // clear out the struct for use
	d3dpp.Windowed = TRUE;    // program windowed, not fullscreen
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;    // discard old frames
	d3dpp.hDeviceWindow = hWnd;    // set the window to be used by Direct3D
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8; // set the back buffer format to 32-bit
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE; //enable vsync
	d3dpp.BackBufferWidth = s_width;    // set the width of the buffer
	d3dpp.BackBufferHeight = s_height;    // set the height of the buffer

	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	// create a device class using this information and the info from the d3dpp stuct
	d3d->CreateDeviceEx(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		0,
		&d3ddev);

	D3DXCreateFont(d3ddev, 50, 0, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &pFont);
	ImGui_ImplDX9_Init(hWnd, d3ddev);

}

void DrawString(int x, int y, DWORD color, LPD3DXFONT g_pFont, const char *fmt)
{
	RECT FontPos = { x, y, x + 120, y + 16 };
	char buf[1024] = { '\0' };
	va_list va_alist;

	va_start(va_alist, fmt);
	vsprintf_s(buf, fmt, va_alist);
	va_end(va_alist);
	g_pFont->DrawText(NULL, buf, -1, &FontPos, DT_NOCLIP, color);
}

void render()
{
	
	// clear the window alpha
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 0.0f, 0);

	d3ddev->BeginScene();    // begins the 3D scene
	ImGui_ImplDX9_NewFrame();

	//DrawString(10, 50, D3DCOLOR_ARGB(255, 255, 0, 0), pFont, "Test rendering string :D");
	if (GetKeyState(VK_INSERT) == 1) {
		if (!ImGui::IsWindowFocused()) {
			ImGui::SetWindowFocus();
		}
		ImGui::GetIO().MouseDrawCursor = 1;
		if (!((int)GetWindowLong(hWnd, GWL_EXSTYLE) == Default)) {
			SetWindowLong(hWnd, -20, Default);
		}
		ImGui::SetNextWindowPos(ImVec2(20, 30));
		ImGui::Begin(XOR(cName), &open, ImVec2(wndwidth, wndheight), 0.9f, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus); {
			ImGui::Columns(1, "", false);
			ImGui::Text("Stuff");
			ImGui::Separator();
			ImGui::Checkbox("Bunnyhop", &pMisc->Bhop);
			ImGui::Checkbox("Glow", &pMisc->Glow);
			ImGui::Checkbox("Noflash", &pMisc->Noflash);
			ImGui::Checkbox("TriggerBot", &pMisc->Trigger);
			ImGui::Checkbox("Nohands", &pNoHands->NoHandsToggle);
			ImGui::Separator();

			if (ImGui::SliderInt("FOV", &pFov->fov, 10, 180)) {
				pFov->setViewFov();
			}
			ImGui::NextColumn();
			if (ImGui::Button("Reset Fov", ImVec2(100, 15))) {
				pFov->fov = 90;
				pFov->setViewFov();
			}
			ImGui::NewLine();
			if (ImGui::InputText("Custom ClanTag", pMisc->cClantag, sizeof(pMisc->cClantag))) {
				if (pMisc->clantag == 3) {
					pMisc->TagChanger();
				}
			}
			if (ImGui::Combo("Clantag changer", &pMisc->clantag, clantagTypes, ARRAYSIZE(clantagTypes))) {
				pMisc->TagChanger();
			}

			ImGui::NewLine();
			ImGui::NewLine();
			ImGui::NewLine();
			ImGui::NewLine();
			ImGui::NewLine();
			ImGui::NewLine();
			if (ImGui::Button("Close Cheat", ImVec2(100, 25))) {
				std::exit(0);
			}
			ImGui::SameLine();
			if (ImGui::Button("Reload Config", ImVec2(100, 25))) {
				ini->readIni();
				pFov->setViewFov();
			}
		}
		ImGui::End();
		ImGui::Render();
	}
	else {
		ImGui::GetIO().MouseDrawCursor = 0;
		if (!((int)GetWindowLong(hWnd, GWL_EXSTYLE) == Default)) {
			SetWindowLong(hWnd, GWL_EXSTYLE, (int)GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED | WS_EX_TRANSPARENT);
		}
		ImGui::End();
	}

	d3ddev->EndScene();    // ends the 3D scene

	d3ddev->PresentEx(NULL, NULL, NULL, NULL, NULL);   // displays the created frame on the screen
}



char* ReadINI(char* szSection, char* szKey, const char* szDefaultValue)
{
	char* szResult = new char[255];
	memset(szResult, 0x00, 255);
	GetPrivateProfileString(szSection, szKey,
		szDefaultValue, szResult, 255, ".\\conf.ini");
	return szResult;
}




int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	char * value = "Counter-Strike: Global Offensive";//ReadINI("CONFIGURATION", "WIN_NAME", "none");


	//RECT rc;


	if (getcsPos() == true) {

	}
	else {
		ExitProcess(0);
	}
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)RGB(0, 0, 0);
	wc.lpszClassName = "WindowClass";

	RegisterClassEx(&wc);

	hWnd = CreateWindowEx(0,
		"WindowClass",
		"",
		WS_EX_TOPMOST | WS_POPUP,
		rc.left, rc.top,
		s_width, s_height,
		NULL,
		NULL,
		wc.hInstance,
		NULL);

	Default = (int)GetWindowLong(hWnd, GWL_EXSTYLE);

	SetLayeredWindowAttributes(hWnd, RGB(0, 0, 0), 0, ULW_COLORKEY);
	SetLayeredWindowAttributes(hWnd, 0, 255, LWA_ALPHA);

	ShowWindow(hWnd, nCmdShow);

	ini->setDllPath();
	ini->readIni();
	SetConsoleTitle("Kwell's External");
	pMisc->watermark();

	Mem->Process(XOR("csgo.exe"));

	pMisc->setClientDLL(); //getting DLL's
	pMisc->setEngineDLL();
	pMisc->ClientSize = Mem->ModuleSize("client.dll");
	pMisc->EngineSize = Mem->ModuleSize("engine.dll");

	pMisc->clantagOffset = Mem->SigScan(pLocalPlayer->EngineDLL, pMisc->EngineSize, "\x53\x56\x57\x8B\xDA\x8B\xF9\xFF\x15\x00\x00\x00\x00", "xxxxxxxxx????");
	pMisc->clantagOffset -= pLocalPlayer->EngineDLL;

	pFov->setViewFov();
	pMisc->watermark();
	strcpy(cName, name.c_str());

	GUI_Init();

	HANDLE rghThreads[] = {
		//CreateThread(0, 0, &OnFrame, 0, 0, NULL),
		bhopLoop = CreateThread(0, 0, &bhop, 0, 0, NULL),
		aimLoop = CreateThread(0, 0, &aim, 0, 0, NULL),
		noLoop = CreateThread(0, 0, &no, 0, 0, NULL),
		visLoop = CreateThread(0, 0, &vis, 0, 0, NULL),
		glowLoop = CreateThread(0, 0, &glow, 0, 0, NULL),
		conLoop = CreateThread(0, 0, &console, 0, 0, NULL),
		//fovLoop = CreateThread(0, 0, &clantag, 0, 0, NULL),
		//threadLoop = CreateThread(0, 0, Loop, 0, 0, NULL)
	};

	initD3D(hWnd);
	MSG msg;
	::SetWindowPos(FindWindow(NULL, value), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	while (TRUE)
	{
		::SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

		if (!FindWindow(NULL, value))
			ExitProcess(0);
		render();
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT) {
			ImGui_ImplDX9_Shutdown();
			exit(0);
			//std::exit(0);
		}

	}

	return msg.wParam;
}


extern LRESULT ImGui_ImplDX9_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
bool test = false;
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (GetKeyState(VK_INSERT) == 1) {
		test = !test;
	}
	if (ImGui_ImplDX9_WndProcHandler(hWnd, message, wParam, lParam) && test)
		return true;

	switch (message)
	{
	case WM_PAINT:
	{
		DwmExtendFrameIntoClientArea(hWnd, &margin);
	}break;

	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	} break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

/*BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		threadLoop = CreateThread(0, 0, Loop, 0, 0, NULL);
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		if (threadLoop)
			CloseHandle(threadLoop);
		if (bhopLoop)
			CloseHandle(bhopLoop);
		if (glowLoop)
			CloseHandle(glowLoop);
		if (aimLoop)
			CloseHandle(aimLoop);
		if (noLoop)
			CloseHandle(noLoop);
		if (visLoop)
			CloseHandle(visLoop);
		if (conLoop)
			CloseHandle(conLoop);
		if (fovLoop)
			CloseHandle(fovLoop);
		if (triggerLoop)
			CloseHandle(triggerLoop);
	}
	return TRUE;
}*/
