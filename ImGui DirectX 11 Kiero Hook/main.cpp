#define _WINSOCKAPI_

#include "includes.h"
#include "dots.h"


extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;

ImFont* manaFont;

void InitImGui()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.Framerate = 60.f;
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	manaFont = io.Fonts->AddFontFromFileTTF("C:/Users/yi6de/Documents/ImGui-DirectX-11-Kiero-Hook-master/Montserrat-Medium.ttf", 18.f);
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(pDevice, pContext);
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

bool manabar = false;
ImColor manaColor = { 0, 0, 0, 0, };

void drawManaBar(float x, float y, float value, float value2) {
	ImGui::PushFont(manaFont);
	auto draw = ImGui::GetBackgroundDrawList();
	std::string text = std::to_string((int)value) + " / " + std::to_string((int)value2);

	float perc = value / (value2 / 100);
	float wf = perc * 1.2;

	draw->AddRectFilled(ImVec2(x, y), ImVec2(x + 120, y + 20), ImColor(17, 17, 17, 255), 3.0f, ImDrawCornerFlags_All);
	draw->AddRectFilled(ImVec2(x, y), ImVec2(x + wf, y + 20), manaColor, 3.0f, ImDrawCornerFlags_All); //ImColor(27, 54, 150, 255)
	auto textWidth = ImGui::CalcTextSize(text.data()).x;
	int textPosX = x + (120 / 2 - (int)textWidth / 2);
	draw->AddText(ImVec2(textPosX, y + 1), ImColor(255, 255, 255, 255), text.data());
	ImGui::PopFont();
}



bool init = false;
HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!init)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)& pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)& pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			InitImGui();
			init = true;
		}

		else
			return oPresent(pSwapChain, SyncInterval, Flags);
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (InGame && manabar) {
		for (int i = 0; i < 5; i++)
		{	
			Enemy hero = Enemies[i];

			std::time_t tnow = std::time(0);

			if (hero.isAlive && hero.onScreen){
				drawManaBar((float)hero.x, (float)hero.y, hero.mana, hero.maxMana);
			}
		}
	}

	ImGui::Begin("hack");
	ImGui::Checkbox("manabar", &manabar);
	ImGui::ColorEdit4("mana color", (float*)&manaColor);
	ImGui::End();

	ImGui::Render();

	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	return oPresent(pSwapChain, SyncInterval, Flags);
}

DWORD WINAPI MainThread(LPVOID lpReserved)
{
	bool init_hook = false;
	do
	{
		if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
		{
			kiero::bind(8, (void**)& oPresent, hkPresent);
			init_hook = true;
		}
	} while (!init_hook);
	return TRUE;
}

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hMod);
			
		Logger::INFO("Injecting....");

		CreateThread(nullptr, 0, MainThread, hMod, 0, nullptr);
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)OnInject, hMod, 0, nullptr);
		break;
	case DLL_PROCESS_DETACH:
		kiero::shutdown();
		break;
	}
	return TRUE;
}