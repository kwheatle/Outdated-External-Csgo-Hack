#include "window.h"
#include "imgui.h"
#include "D:\1abc - Stuff\ImGUI\DX9\imgui_impl_dx9.cpp"


static LPDIRECT3DDEVICE9        m_pD3DDevice = NULL;
static D3DPRESENT_PARAMETERS    m_pD3Dpp;
LPDIRECT3D9						m_pD3D;

C_GUIWindow::C_GUIWindow() {};
C_GUIWindow::~C_GUIWindow() {};

extern LRESULT ImGui_ImplDX9_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT __stdcall C_GUIWindow::WndProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	if (ImGui_ImplDX9_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;

	switch (msg)
	{
	case WM_SIZE:
		if (m_pD3DDevice != NULL && wParam != SIZE_MINIMIZED)
		{
			ImGui_ImplDX9_InvalidateDeviceObjects();
			m_pD3Dpp.BackBufferWidth = LOWORD(lParam);
			m_pD3Dpp.BackBufferHeight = HIWORD(lParam);
			HRESULT hr = m_pD3DDevice->Reset(&m_pD3Dpp);
			if (hr == D3DERR_INVALIDCALL)
				IM_ASSERT(0);
			ImGui_ImplDX9_CreateDeviceObjects();
		}
		return 0;
	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
			return 0;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

bool C_GUIWindow::Create() {
	wc = { sizeof(WNDCLASSEX), 
			CS_CLASSDC, WndProcedure, 
			0L, 0L, GetModuleHandle(NULL), 
			NULL, LoadCursor(NULL, IDC_ARROW), 
			NULL, NULL, WINDOW_NAME, NULL };

	RegisterClassEx(&wc);
	m_hWnd = CreateWindow(WINDOW_NAME, WINDOW_NAME, WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX, 100, 100, m_nSize[0], m_nSize[1], NULL, NULL, wc.hInstance, NULL);

	return InitDirectX();
}

bool C_GUIWindow::InitDirectX() {
	if ((m_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL) {
		UnregisterClass(WINDOW_NAME, wc.hInstance);
		return false;
	}

	ZeroMemory(&m_pD3Dpp, sizeof(m_pD3Dpp));
	m_pD3Dpp.Windowed = TRUE;
	m_pD3Dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_pD3Dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	m_pD3Dpp.EnableAutoDepthStencil = TRUE;
	m_pD3Dpp.AutoDepthStencilFormat = D3DFMT_D16;
	m_pD3Dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	if (m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &m_pD3Dpp, &m_pD3DDevice) < 0) {
		m_pD3D->Release();
		UnregisterClass((WINDOW_NAME), wc.hInstance);
		return false;
	}

	ImGui_ImplDX9_Init(m_hWnd, m_pD3DDevice);


	ZeroMemory(&msg, sizeof(msg));
	ShowWindow(m_hWnd, SW_SHOWDEFAULT);
	UpdateWindow(m_hWnd);

	return true;
}

DWORD LastFrameTime = 0;
DWORD currentTime;

void C_GUIWindow::OnFrame(int framerate) {
	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			continue;
		}

		HRESULT DeviceState = m_pD3DDevice->TestCooperativeLevel();
		if (DeviceState != D3D_OK) {
			ImGui_ImplDX9_InvalidateDeviceObjects();
			m_pD3DDevice->Reset(&m_pD3Dpp);
			ImGui_ImplDX9_CreateDeviceObjects();
		}

		ImVec4 clear_col = ImColor(45, 45, 45);

		ImGui_ImplDX9_NewFrame();
		for (auto& pOnFrame : OnFrameVec) {
			if (pOnFrame) {
				pOnFrame();
			}
		}
		
		m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, false);
		m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		m_pD3DDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, false);
		D3DCOLOR clear_col_dx = D3DCOLOR_RGBA((int)(clear_col.x*255.0f), (int)(clear_col.y*255.0f), (int)(clear_col.z*255.0f), (int)(clear_col.w*255.0f));
		m_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, clear_col_dx, 1.0f, 0);

		if (m_pD3DDevice->BeginScene() >= 0) {
			ImGui::Render();
			m_pD3DDevice->EndScene();
		}

		m_pD3DDevice->Present(0, 0, 0, 0);
	}
}