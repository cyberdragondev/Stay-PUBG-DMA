#pragma once

#include <winsock2.h>
#include <windows.h>
#include <Common/Data.h>
#include "DMARender.h"
#include "Texture.h"
#include <d3d11.h>

class Map
{
public:
    static float ScaleConversion(float Location)
    {
        float Scale = 1.f;
        if (GameData.MapName == "Baltic_Main") Scale = 0.99609375f;
        return Location / GameData.Radar.MapSize.ImageSize * GameData.Radar.ImageMapHeight * (GameData.Radar.MapSize.ImageSize == 816000.f ? Scale : 1);
    }

    static ImVec2 WorldToRadar(const RECT& Rect, const DMARender::MapTransform& mTransform, FVector WorldLocation)
    {
        WorldLocation.X = ScaleConversion(GameData.Radar.WorldOriginLocation.X + WorldLocation.X);
        WorldLocation.Y = ScaleConversion(GameData.Radar.WorldOriginLocation.Y + WorldLocation.Y);

        ImVec2 MapLocation = { WorldLocation.X, WorldLocation.Y };

        MapLocation.x *= mTransform.mapZoom;
        MapLocation.y *= mTransform.mapZoom;

        MapLocation.x += mTransform.dragOffsetX;
        MapLocation.y += mTransform.dragOffsetY;

        MapLocation.x += (float)Rect.left;
        MapLocation.y += (float)Rect.top;

        return MapLocation;
    }

    static void DrawFPS(const RECT& Rect)
    {
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImVec2 Pos = ImGui::GetWindowPos();
        auto TextPosition = ImVec2(Rect.left + 20, Rect.top + 40);
        RenderHelper::Text(std::format("FPS: {}\nBeta Version", (int)io.Framerate).c_str(), TextPosition, IM_COL32(255, 255, 255, 255), 16, false, false, false);
    }

    static void DrawButton(const RECT& Rect)
    {
        ImGui::SetNextWindowViewport(ImGui::GetMainViewport()->ID);
        ImGui::SetNextWindowPos({(float)Rect.right - 105, (float)Rect.top + 35});
        ImGui::Begin("ButtonLists", nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
        std::string SettingIcon = "Assets/Icons/Radar/Setting.png";
        std::string PlayersIcon = "Assets/Icons/Radar/Players.png";

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(18.f / 255.f, 18.f / 255.f, 18.f / 255.f, 200.f / 255.f));
        if (GameData.Config.Window.Players) ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(149.0f / 255.0f, 1.0f / 255.0f, 247.f / 255.0f, 200.f / 255.f));
        if (ImGui::ImageButton(GImGuiTextureMap[PlayersIcon].Texture, { 25, 25 }, ImVec2(0, 0), ImVec2(1, 1), 5, ImColor(0, 0, 0, 0), ImColor(255, 255, 255, 255)))
        {
            GameData.Config.Window.Players = !GameData.Config.Window.Players;
            ImGui::PopStyleColor();
        }
        if (GameData.Config.Window.Players) ImGui::PopStyleColor();

        ImGui::SameLine();

        if (GameData.Config.Window.Setting) ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(149.0f / 255.0f, 1.0f / 255.0f, 247.f / 255.0f, 200.f / 255.f));
        if (ImGui::ImageButton(GImGuiTextureMap[SettingIcon].Texture, { 25, 25 }, ImVec2(0, 0), ImVec2(1, 1), 5, ImColor(0, 0, 0, 0), ImColor(255, 255, 255, 255)))
        {
            GameData.Config.Window.Setting = !GameData.Config.Window.Setting;
            ImGui::PopStyleColor();
        }
        if (GameData.Config.Window.Setting) ImGui::PopStyleColor();
        ImGui::PopStyleColor();
        ImGui::End();
    }

    static void DrawStates(const RECT& Rect, const ImFontAtlas* FontAtlas)
    {
        ImGui::PushFont(FontAtlas->Fonts[4]);
        ImVec2 CenterPosition = { float(Rect.left + Rect.right) / 2, float(Rect.top + Rect.bottom) / 2 };
        std::string Text = U8("寻找游戏进程中");
        switch (GameData.Scene)
        {
        case Scene::Lobby:
            Text = U8("等待进入游戏");
            break;
        case Scene::Gaming:
            Text = Utils::StringToUTF8(std::format("游戏中 ({})", Utils::FormatMinutes(GameData.WorldTimeSeconds)));
            break;
        default:
            break;
        }

        //RenderHelper::Text(U8("PUBG HELPER"), CenterPosition, IM_COL32(255, 255, 255, 255), 60, true, true, false);
        std::string IconUrl = "Assets/Icons/Radar/T_TitleScreen_Logo.png";
        CenterPosition.y -= 20;
        if (GImGuiTextureMap[IconUrl].Width > 0) {
            float Zoom = 0.4f;
            ImVec2 IconSize = { GImGuiTextureMap[IconUrl].Width * Zoom, GImGuiTextureMap[IconUrl].Height * Zoom };
            RenderHelper::AddImageRotated(GImGuiTextureMap[IconUrl].Texture, CenterPosition, IconSize, 0, false);
        }
        CenterPosition.y += 85;
        RenderHelper::Text(Text.c_str(), CenterPosition, IM_COL32(255, 255, 255, 180), 30, true, true, false);
        ImGui::PopFont();
    }

    static void DrawOverlay(const RECT& Rect, DMARender::MapTransform& mTransform)
    {
        //ImDrawList* fgDrawList = ImGui::GetBackgroundDrawList();

        auto Players = Data::GetPlayers();
        for (auto Item : Players)
        {
            auto Player = Item.second;
            auto MapLocation = WorldToRadar(Rect, mTransform, Player.Location);
            RenderHelper::Text(std::format("{}", Player.Name).c_str(), MapLocation, IM_COL32(255, 255, 255, 255), 12, true, true, false);
        }
    }

	static void Render(ID3D11Device* g_pd3dDevice, const ImFontAtlas* FontAtlas)
	{
        ImGui::SetNextWindowViewport(ImGui::GetMainViewport()->ID);
        ImGui::Begin("Map", nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);

        RECT Rect;
        GetWindowRect(GameData.Config.Overlay.hWnd, &Rect);

        DrawStates(Rect, FontAtlas);
        //std::string MapFile = "Assets/Maps/" + GameData.MapName + ".png";
        //if (MapsSize[GameData.MapName].Size > 0 && GetFileAttributesA(MapFile.c_str()) != INVALID_FILE_ATTRIBUTES) {
        //    auto Allocator = Texture::LoadTexture(g_pd3dDevice, "Assets/Maps/" + GameData.MapName + ".png");
        //    GameData.Radar.ImageMapHeight = Allocator.Height;
        //    static DMARender::MapTransform mTrans = DMARender::MapTransform();

        //    if (mTrans.mapZoom < 0) {
        //        float mapSize = fmaxf(Allocator.Width, Allocator.Height);
        //        float screenSize = fminf(Rect.right - Rect.left, Rect.bottom - Rect.top);
        //        mTrans.mapZoom = screenSize / mapSize;
        //        mTrans.mapHeight = Allocator.Height;
        //        mTrans.mapWidth = Allocator.Width;
        //    }

        //    auto mousePos = ImGui::GetMousePos();
        //    static float lastMousePosX = mousePos.x;
        //    static float lastMousePosY = mousePos.y;

        //    if (ImGui::IsMouseDown(ImGuiMouseButton_Left) && !ImGui::GetIO().WantCaptureMouse) {
        //        mTrans.dragOffsetX += mousePos.x - lastMousePosX;
        //        mTrans.dragOffsetY += mousePos.y - lastMousePosY;
        //    }
        //    if (ImGui::GetIO().MouseWheel != 0.0f) {
        //        float oldZoom = mTrans.mapZoom;
        //        //Zoom in/out
        //        mTrans.mapZoom *= (1 + (ImGui::GetIO().MouseWheel * .05));
        //        if (mTrans.mapZoom < 0.01)
        //            mTrans.mapZoom = 0.01;

        //        //Zoom toward cursor
        //        float deltaX = (Allocator.Width * oldZoom) - (Allocator.Width * mTrans.mapZoom);
        //        float deltaY = (Allocator.Height * oldZoom) - (Allocator.Height * mTrans.mapZoom);

        //        float percX = (mousePos.x - Rect.left - mTrans.dragOffsetX) / ((Allocator.Width * mTrans.mapZoom));
        //        float percY = (mousePos.y - Rect.top - mTrans.dragOffsetY) / ((Allocator.Width * mTrans.mapZoom));

        //        mTrans.dragOffsetX += (deltaX * percX);
        //        mTrans.dragOffsetY += (deltaY * percY);
        //    }

        //    lastMousePosX = mousePos.x;
        //    lastMousePosY = mousePos.y;

        //    ImDrawList* fgDrawList = ImGui::GetBackgroundDrawList();
        //    fgDrawList->AddImage(
        //        Allocator.Texture,
        //        ImVec2(
        //            Rect.left + mTrans.dragOffsetX,
        //            Rect.top + mTrans.dragOffsetY
        //        ),
        //        ImVec2(
        //            Rect.left + mTrans.dragOffsetX + (Allocator.Width * mTrans.mapZoom),
        //            Rect.top + mTrans.dragOffsetY + (Allocator.Height * mTrans.mapZoom)
        //        )
        //    );

        //    DrawOverlay(Rect, mTrans);
        //}
        //else {
        //    DrawStates(Rect, FontAtlas);
        //}


        DrawFPS(Rect);

        ImGui::End();

        DrawButton(Rect);


    }

private:

};