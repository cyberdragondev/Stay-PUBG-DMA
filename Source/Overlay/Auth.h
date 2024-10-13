#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS

#include <imgui/imgui.h>
#include <imgui/imgui_impl_win32.h>
#include <imgui/imgui_impl_dx11.h>
#include <imgui/imgui_internal.h>
#include <d3d11.h>
#include <tchar.h>

#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <D3DX11tex.h>
#pragma comment(lib, "D3DX11.lib")

#include <Common/Data.h>
#include <Common/Config.h>
#include <BSPHP/stdafx.h>

#include <dwmapi.h>

bool isAuthFirstTime = true;
char loginUsername[128];
char loginPassword[128];
char regUsername[128];
char regPassword[128];
char key[128];

class Auth {
public:
    static void Draw(ImFontAtlas*& fontAtlas)
	{
        static float tab_size = 0.f;
        {
            ImGuiStyle* s = &ImGui::GetStyle();

            s->WindowPadding = ImVec2(0, 0), s->WindowBorderSize = 0;
            s->ItemSpacing = ImVec2(20, 20);

            s->ScrollbarSize = 8.f;

            ImVec2 AuthSize = ImVec2(350, 240);
            if (isAuthFirstTime) {
                std::string AccountConfigText = Utils::ReadConfigFile("Config/Account.pak");

                if (AccountConfigText != "")
                {
                    auto AccountConfig = nlohmann::json::parse(DecryptionAES(AccountConfigText));

                    if (AccountConfig.contains("username"))
                    {
                        sprintf(loginUsername, "%s", Utils::StringToUTF8(AccountConfig["username"]).c_str());
                    }
                    if (AccountConfig.contains("password"))
                    {
                        sprintf(loginPassword, "%s", Utils::StringToUTF8(AccountConfig["password"]).c_str());
                    }
                }

                ImGuiViewport* viewport = ImGui::GetMainViewport();
                ImVec2 center = ImVec2(viewport->WorkPos.x + (viewport->WorkSize.x - AuthSize.x) * 0.5f,
                    viewport->WorkPos.y + (viewport->WorkSize.y - AuthSize.y) * 0.5f);
                ImGui::SetNextWindowPos(center);
                isAuthFirstTime = false;
            }
            ImGui::SetNextWindowSize(AuthSize);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(25, 25));
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 6.f);
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(50, 50));
            ImGui::Begin("OXO AUTH", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoSavedSettings);
            {
                const ImVec2& pos = ImGui::GetWindowPos();
                const auto& p = ImGui::GetWindowPos();
                const ImVec2 spacing = ImGui::GetStyle().ItemSpacing;

                ImGui::GetBackgroundDrawList()->AddRectFilled(pos, pos + AuthSize + ImVec2(tab_size, 0), ImGui::GetColorU32(c::bg::background), c::bg::rounding);
                ImGui::GetBackgroundDrawList()->AddRect(pos, pos + AuthSize + ImVec2(tab_size, 0), ImGui::GetColorU32(c::bg::outline_background), c::bg::rounding);

                ImGui::PushStyleColor(ImGuiCol_Text, ImGui::GetColorU32(Style::AccentTextColor));

                ImGui::SetCursorPos(ImVec2(25, 25));
                ImGui::PushFont(fontAtlas->Fonts[1]);
                ImGui::Text("OXO AUTH");
                ImGui::PopFont();
                ImGui::SetCursorPos(ImVec2(22, 60));

                static int tab = 0;
                ImVec2 min, max;
                static CString Res;
                static bool showPopup = false;
                static bool showDatePopup = false;
                static std::string VIPDate = "";

                if (ImGui::BeginTabBar(U8("##登录选项卡")))
                {
                    if (ImGui::BeginTabItem(U8("登录")))
                    {
                        tab = 0;
                        min = ImGui::GetItemRectMin();
                        max = ImGui::GetItemRectMax();

                        ImGui::InputText(U8("账号"), loginUsername, sizeof(loginUsername));
                        ImGui::InputText(U8("密码"), loginPassword, sizeof(loginPassword), ImGuiInputTextFlags_Password);

                        if (ImGui::Button(U8("登录"), ImVec2(ImGui::GetContentRegionMax().x - s->WindowPadding.x, 25))) {
                            Res = BSLogin(loginUsername, loginPassword);
                            CString strTmp = Res.Mid(0, 7);

                            GameData.Config.Overlay.Click = true;
                            showPopup = true;

                            if (strTmp == "01|1011") {
                                showPopup = false;
                                nlohmann::json json;
                                json["username"] = loginUsername;
                                json["password"] = loginPassword;

                                VIPDate = GetVIPDate();

                                showDatePopup = true;

                                Utils::WriteConfigFile("Config/Account.pak", EncryptionAES(json.dump()));
                            }
                        }

                        ImGui::EndTabItem();
                    }
                    if (ImGui::BeginTabItem(U8("注册")))
                    {
                        tab = 2;
                        min = ImGui::GetItemRectMin();
                        max = ImGui::GetItemRectMax();

                        ImGui::InputText(U8("账号"), regUsername, sizeof(regUsername));
                        ImGui::InputText(U8("密码"), regPassword, sizeof(regPassword), ImGuiInputTextFlags_Password);

                        if (ImGui::Button(U8("注册"), ImVec2(ImGui::GetContentRegionMax().x - s->WindowPadding.x, 25))) {
                            Res = Reg(regUsername, regPassword, "");
                            GameData.Config.Overlay.Click = true;
                            showPopup = true;
                        }

                        ImGui::EndTabItem();
                    }

                    if (ImGui::BeginTabItem(U8("激活")))
                    {
                        tab = 1;
                        min = ImGui::GetItemRectMin();
                        max = ImGui::GetItemRectMax();

                        ImGui::InputText(U8("账号"), loginUsername, sizeof(loginUsername));
                        ImGui::InputText(U8("卡号"), key, sizeof(key), ImGuiInputTextFlags_Password);

                        if (ImGui::Button(U8("激活"), ImVec2(ImGui::GetContentRegionMax().x - s->WindowPadding.x, 25))) {
                            Res = Pay(loginUsername, "", key, "");
                            GameData.Config.Overlay.Click = true;
                            showPopup = true;
                        }

                        ImGui::EndTabItem();
                    }

                    ImDrawList* draw_list = ImGui::GetWindowDrawList();
                    draw_list->AddLine(ImVec2(min.x + 4, max.y), ImVec2(max.x - 4, max.y), IM_COL32(255, 255, 255, 255), 3);

                    if (showPopup) {
                        ImGui::OpenPopup(U8("信息"));
                        showPopup = false;
                    }

                    if (ImGui::BeginPopupModal(U8("信息"), NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
                        ImGui::Text("%s", (LPCTSTR)Res);
                        if (ImGui::Button(U8("确定"), ImVec2(100, 25))) {
                            GameData.Config.Overlay.Click = false;
                            ImGui::CloseCurrentPopup();
                        }
                        ImGui::EndPopup();
                    }

                    if (showDatePopup) {
                        ImGui::OpenPopup(U8("OXO"));
                        showDatePopup = false;
                    }

                    if (ImGui::BeginPopupModal(U8("OXO"), NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
                        ImGui::Text(U8("%s"), VIPDate.c_str());
                        if (ImGui::Button(U8("GO"), ImVec2(100, 25))) {
                            GameData.Config.Overlay.Click = false;
                            ImGui::CloseCurrentPopup();
                            ::SendMessageA(GameData.Config.Overlay.hWnd, WM_CLOSE, 0, 0);
                            GameData.IsLogin = true;
                        }
                        ImGui::EndPopup();
                    }

                    ImGui::EndTabBar();
                }

                GameData.Config.Overlay.AuthPos = { ImGui::GetWindowPos().x, ImGui::GetWindowPos().y };
                GameData.Config.Overlay.AuthSize = { ImGui::GetWindowSize().x, ImGui::GetWindowSize().y };

                ImGui::PopStyleVar(1);
            }
            ImGui::End();

            ImGui::PopStyleVar(2);
        }
	};
};

