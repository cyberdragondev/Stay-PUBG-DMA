// Dear ImGui: standalone example application for DirectX 11

// Learn about Dear ImGui:
// - FAQ                  https://dearimgui.com/faq
// - Getting Started      https://dearimgui.com/getting-started
// - Documentation        https://dearimgui.com/docs (same as your local docs/ folder).
// - Introduction, links and more at the top of imgui.cpp

#include "Overlay.h"
#include "ESP.h"
#include "Texture.h";
#include <Common/Data.h>
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include <imgui/imgui_impl_win32.h>
#include <imgui/imgui_impl_dx11.h>
#include <d3d11.h>
#include <tchar.h>
#include <Utils/Throttler.h>
#include <Overlay/Menu/Menu.h>
#include "Style.h"
#include "Map.h"
#include "MThreadRenderer.h"
#include <thread>

// Data
static ID3D11Device* g_pd3dDevice = nullptr;
static ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
static IDXGISwapChain* g_pSwapChain = nullptr;
static UINT                     g_ResizeWidth = 0, g_ResizeHeight = 0;
static ID3D11RenderTargetView* g_mainRenderTargetView = nullptr;

// Forward declarations of helper functions
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void CreateRenderTarget();
void CleanupRenderTarget();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void EnableMouseTransparency()
{
    HWND hWnd = (HWND)ImGui::GetCurrentWindow()->Viewport->PlatformHandle;
    LONG_PTR exStyle = GetWindowLongPtr(hWnd, GWL_EXSTYLE);
    exStyle |= WS_EX_TRANSPARENT | WS_EX_LAYERED;
    SetWindowLongPtr(hWnd, GWL_EXSTYLE, exStyle);
}

void Overlay::DrawOverlayHandler()
{
    if (GameData.Config.Overlay.Enable) {
        auto selectedMonitor = ImGui::GetPlatformIO().Monitors[GameData.Config.Overlay.MonitorCurrentIdx];
        ImGui::SetNextWindowSize(ImVec2(selectedMonitor.MainSize.x, selectedMonitor.MainSize.y));
        ImGui::SetNextWindowPos((ImVec2(selectedMonitor.MainPos.x, selectedMonitor.MainPos.y)));

        ImGuiWindowClass WindowClass;
        WindowClass.ClassId = ImHashStr("ESP Overlay");

        ImGuiViewportFlags WindowClassFlags = 0;
        WindowClassFlags |= ImGuiViewportFlags_NoDecoration;
        WindowClassFlags |= ImGuiViewportFlags_NoInputs;
        WindowClassFlags |= ImGuiViewportFlags_NoRendererClear;
        //WindowClassFlags |= ImGuiViewportFlags_IsPlatformWindow;
        WindowClassFlags |= ImGuiViewportFlags_NoAutoMerge;

        ImGuiWindowFlags WindowFlags = 0;
        WindowFlags |= ImGuiWindowFlags_NoTitleBar;
        WindowFlags |= ImGuiWindowFlags_NoResize;
        WindowFlags |= ImGuiWindowFlags_NoScrollbar;
        WindowFlags |= ImGuiWindowFlags_NoCollapse;
        WindowFlags |= ImGuiWindowFlags_NoInputs;
        WindowFlags |= ImGuiWindowFlags_NoDecoration;
        WindowFlags |= ImGuiWindowFlags_NoNav;

        if (!GameData.Config.Overlay.FusionMode)
        {
            WindowFlags |= ImGuiWindowFlags_NoBackground;
            WindowClassFlags |= ImGuiViewportFlags_TopMost;
        }

        ImGuiStyle& style = ImGui::GetStyle();
        float OriginalBorderSize = style.WindowBorderSize;
        ImVec4 OriginalWindowBgColor = style.Colors[ImGuiCol_WindowBg];
        ImVec2 OriginalWindowPadding = style.WindowPadding;

        style.WindowBorderSize = 0.0f;
        style.WindowPadding = { 0.f, 0.f };
        style.Colors[ImGuiCol_WindowBg] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);

        WindowClass.ViewportFlagsOverrideSet = WindowClassFlags;
        ImGui::SetNextWindowClass(&WindowClass);

        ImGui::Begin("ESP Overlay", nullptr, WindowFlags);
        {
            if(!GameData.Config.Overlay.FusionMode) EnableMouseTransparency();
            ImGuiIO& io = ImGui::GetIO(); (void)io;

            ESP::DrawFPS(io);
            ESP::DrawESP();
        }
        ImGui::End();

        style.WindowBorderSize = OriginalBorderSize;
        style.WindowPadding = OriginalWindowPadding;
        style.Colors[ImGuiCol_WindowBg] = OriginalWindowBgColor;
    }
}

// Main code
int Overlay::Init()
{
    WNDCLASSEXW wc = { sizeof(wc), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, L"Class", nullptr };
    ::RegisterClassExW(&wc);
    HWND hwnd = ::CreateWindowW(wc.lpszClassName, L"Commander", WS_OVERLAPPEDWINDOW, 0, 0, 1280, 720, nullptr, nullptr, wc.hInstance, nullptr);

    GameData.Config.Overlay.hWnd = hwnd;

    // Initialize Direct3D
    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    Texture::LoadTextures(g_pd3dDevice, "Assets/Icons");
    Texture::LoadTextures(g_pd3dDevice, "Assets/Icons/Item/All", true);

    // Show the window
    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    //io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
    //io.ConfigViewportsNoAutoMerge = true;
    io.ConfigViewportsNoDefaultParent = true;
    io.ConfigViewportsNoAutoMerge = true;
    io.ConfigViewportsNoTaskBarIcon = true;
    //io.ConfigViewportsNoDefaultParent = true;
    //io.ConfigDockingAlwaysTabBar = true;
    //io.ConfigDockingTransparentPayload = true;
    //io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleFonts;     // FIXME-DPI: Experimental. THIS CURRENTLY DOESN'T WORK AS EXPECTED. DON'T USE IN USER APP!
    //io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleViewports; // FIXME-DPI: Experimental.

    ImFontAtlas* FontAtlas = new ImFontAtlas();
    ImFontConfig arialConfig;
    arialConfig.FontDataOwnedByAtlas = false;//Assets/Font/Default.ttf
    ImFont* ArialFont = FontAtlas->AddFontFromFileTTF("c:\\Windows\\Fonts\\msyhbd.ttc", 20.0f, &arialConfig, io.Fonts->GetGlyphRangesChineseFull());
    ImFont* TitleFont = FontAtlas->AddFontFromFileTTF("c:\\Windows\\Fonts\\msyhbd.ttc", 24.0f, &arialConfig, io.Fonts->GetGlyphRangesChineseFull());
    ImFont* MenuFont = FontAtlas->AddFontFromFileTTF("c:\\Windows\\Fonts\\msyhbd.ttc", 15.0f, &arialConfig, io.Fonts->GetGlyphRangesChineseFull());
    ImFont* PlayersFont = FontAtlas->AddFontFromFileTTF("c:\\Windows\\Fonts\\msyhbd.ttc", 14.0f, &arialConfig, io.Fonts->GetGlyphRangesChineseFull());
    ImFont* MapFont = FontAtlas->AddFontFromFileTTF("c:\\Windows\\Fonts\\msyhbd.ttc", 30.0f, &arialConfig, io.Fonts->GetGlyphRangesChineseFull());

    io.Fonts = FontAtlas;

    // Setup Dear ImGui style
   // ImGui::StyleColorsClassic_1111();
    
    ImGui::StyleColorsLight();

    ImGuiSetStyle();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    style.ScrollbarSize = 10.0f;
    style.ScrollbarRounding = 12.0f;
    //style.WindowPadding = { 0.f, 0.f };
    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.f, 0.f, 0.f, 0.f);


    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 1.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.f;
        //style.WindowBorderSize = 0.0f;
    }

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != nullptr);

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(32.f / 255.0f, 32.f / 255.0f, 32.f / 255.0f, 1.00f);
    const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
    Throttler Throttlered;

    // Main loop
    bool done = false;
    bool Clear = false;

    CameraData Camera;
    float TimeSeconds = 0.f;

    while (!done)
    {
        MSG msg;

        while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }

        if (done)
            break;
         
        if (g_ResizeWidth != 0 && g_ResizeHeight != 0)
        {
            CleanupRenderTarget();
            g_pSwapChain->ResizeBuffers(0, g_ResizeWidth, g_ResizeHeight, DXGI_FORMAT_UNKNOWN, 0);
            g_ResizeWidth = g_ResizeHeight = 0;
            CreateRenderTarget();
        }

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();

        ImGui::NewFrame();

        if (GameData.Config.Window.IsLogin) {
            if (!GameData.Config.Overlay.UseThread) {
                auto hScatter = mem.CreateScatterHandle();
                if (!GameData.Config.Overlay.UseLastFrameCameraCache)
                {
                    mem.AddScatterRead(hScatter, GameData.PlayerCameraManager + GameData.Offset["CameraCacheLocation"], &Camera.Location);
                    mem.AddScatterRead(hScatter, GameData.PlayerCameraManager + GameData.Offset["CameraCacheRotation"], &Camera.Rotation);
                    mem.AddScatterRead(hScatter, GameData.PlayerCameraManager + GameData.Offset["CameraCacheFOV"], &Camera.FOV);

                }
                else {
                    mem.AddScatterRead(hScatter, GameData.PlayerCameraManager + GameData.Offset["LastFrameCameraCacheLocation"], &Camera.Location);
                    mem.AddScatterRead(hScatter, GameData.PlayerCameraManager + GameData.Offset["LastFrameCameraCacheRotation"], &Camera.Rotation);
                    mem.AddScatterRead(hScatter, GameData.PlayerCameraManager + GameData.Offset["LastFrameCameraCacheFOV"], &Camera.FOV);
                }
                mem.AddScatterRead(hScatter, GameData.UWorld + GameData.Offset["TimeSeconds"], &TimeSeconds);
                mem.ExecuteReadScatter(hScatter);

                GameData.Camera = Camera;
                GameData.WorldTimeSeconds = TimeSeconds;

                mem.CloseScatterHandle(hScatter);
            }

            DrawOverlayHandler();
  /*          Menu::DrawMain(FontAtlas);*/
            Map::Render(g_pd3dDevice, FontAtlas);
        }

        ImGui::Render();

        g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, nullptr);
        g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        g_pSwapChain->Present((GameData.Config.Overlay.FusionMode && !GameData.Config.Overlay.VSync) ? 0 : 1, 0);
    }

    // Cleanup
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd); 
    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);

    GameData.Config.Window.Main = false;

    return 0;
}

// Helper functions
bool CreateDeviceD3D(HWND hWnd)
{
    // Setup swap chain
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;
    //createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
    HRESULT res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
    if (res == DXGI_ERROR_UNSUPPORTED) // Try high-performance WARP software driver if hardware is not available.
        res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
    if (res != S_OK)
        return false;

    CreateRenderTarget();
    return true;
}

void CleanupDeviceD3D()
{
    CleanupRenderTarget();
    if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = nullptr; }
    if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = nullptr; }
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = nullptr; }
}

void CreateRenderTarget()
{
    ID3D11Texture2D* pBackBuffer;
    g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_mainRenderTargetView);
    pBackBuffer->Release();
}

void CleanupRenderTarget()
{
    if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = nullptr; }
}

#ifndef WM_DPICHANGED
#define WM_DPICHANGED 0x02E0 // From Windows SDK 8.1+ headers
#endif

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (wParam == SIZE_MINIMIZED)
            return 0;
        g_ResizeWidth = (UINT)LOWORD(lParam); // Queue resize
        g_ResizeHeight = (UINT)HIWORD(lParam);
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    case WM_DPICHANGED:
        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DpiEnableScaleViewports)
        {
            //const int dpi = HIWORD(wParam);
            //printf("WM_DPICHANGED to %d (%.0f%%)\n", dpi, (float)dpi / 96.0f * 100.0f);
            const RECT* suggested_rect = (RECT*)lParam;
            ::SetWindowPos(hWnd, nullptr, suggested_rect->left, suggested_rect->top, suggested_rect->right - suggested_rect->left, suggested_rect->bottom - suggested_rect->top, SWP_NOZORDER | SWP_NOACTIVATE);
        }
        break;
    }
    return ::DefWindowProcW(hWnd, msg, wParam, lParam);
}
