#pragma once
#include <DMALibrary/Memory/Memory.h>
#include <Common/Data.h>
#include <Common/Entitys.h>
#include <Common/Constant.h>
#include <Utils/Utils.h>
#include <Utils/Throttler.h>
#include <Hack/GNames.h>
#include <Hack/Decrypt.h>

class Radar
{
public:
    static void UpdateWorldMapInfo()
    {
        auto hScatter = mem.CreateScatterHandle();

        int WorldOriginLocationX;
        int WorldOriginLocationY;

        mem.AddScatterRead(hScatter, GameData.UWorld + GameData.Offset["WorldToMap"], (int*)&WorldOriginLocationX);
        mem.AddScatterRead(hScatter, GameData.UWorld + GameData.Offset["WorldToMap"] + 0x4, (int*)&WorldOriginLocationY);
        mem.ExecuteReadScatter(hScatter);

        GameData.Radar.WorldOriginLocation = { (float)WorldOriginLocationX, (float)WorldOriginLocationY, 0.f };
        GameData.Radar.MapSize = MapsSize[GameData.MapName];

        //Utils::Log(1, "Map: %s %f %f", GameData.MapName, GameData.Radar.MapSize.Size, GameData.Radar.MapSize.ImageSize);

        mem.CloseScatterHandle(hScatter);
    }

    static bool GetMapGrid()
    {
        uint64_t BlockInputWidgetList = mem.Read<uint64_t>(GameData.MyHUD + GameData.Offset["BlockInputWidgetList"]);
        int BlockInputWidgetListCount = mem.Read<int>(GameData.MyHUD + GameData.Offset["BlockInputWidgetList"] + 0x8);
        for (int i = 0; i < BlockInputWidgetListCount; i++)
        {
            uint64_t Widget = mem.Read<uint64_t>(BlockInputWidgetList + i * 8);
            int ID = Decrypt::CIndex(mem.Read<int>(Widget + GameData.Offset["ObjID"]));
            std::string WidgetName = GNames::GetNameByID(ID);
            if (WidgetName == "NewWorldMapWidget_BP_C") {
                GameData.Radar.MapGrid = mem.Read<uint64_t>(Widget + GameData.Offset["TrainingMapGrid"] + 0x10);
                GameData.Radar.MapWidget = Widget;
                return true;
            }
            if (WidgetName == "UI_TrainingWorldMapWidget_C") {
                GameData.Radar.MapGrid = mem.Read<uint64_t>(Widget + GameData.Offset["TrainingMapGrid"]);
                GameData.Radar.MapWidget = Widget;
                return true;
            }
        }
        return false;
    }

    static bool GetMiniMapGrid() {
        auto WidgetStateMap = mem.Read<TMap<FString, FTslWidgetState>>(GameData.MyHUD + GameData.Offset["WidgetStateMap"]);
        for (auto& Elem : WidgetStateMap.GetVector()) {
            auto& Key = Elem.Value.Key;
            auto& Value = Elem.Value.Value;
            if (Utils::ValidPtr(Value.Widget))continue;
            ULONG ID = Decrypt::CIndex(mem.Read<ULONG>(Value.Widget + GameData.Offset["ObjID"]));
            std::string WidgetPtrName = GNames::GetName(ID);
           // std::cout << WidgetPtrName << std::endl;

            if (WidgetPtrName == "MinimapOriginalType_C")
            {
                GameData.Radar.MiniMapWidget = Value.Widget;
                return true;
            }

            if (WidgetPtrName == "UI_OldErangel_MinimapOriginalType_C")
            {
                GameData.Radar.MiniMapWidget = Value.Widget;
                return true;
            }
        }
        return false;
    }

    static FVector2D WorldToRadarLocation(FVector Location)
    {
        const FVector2D WorldLocation = {
            Location.X + GameData.Radar.WorldOriginLocation.X,
            Location.Y + GameData.Radar.WorldOriginLocation.Y
        };
        const FVector2D RadarPos = WorldLocation - GameData.Radar.WorldCenterLocation;
        FVector2D ScreenCenter = FVector2D(GameData.Config.Overlay.ScreenWidth / 2, GameData.Config.Overlay.ScreenHeight / 2);
        const FVector2D RadarScreenPos = ScreenCenter + FVector2D{
            RadarPos.X / GameData.Radar.MapSizeFactored * ScreenCenter.Y,
                RadarPos.Y / GameData.Radar.MapSizeFactored * ScreenCenter.Y
        };

        return RadarScreenPos;
    }

    static FVector2D WorldToMiniRadarLocation(FVector Location)
    {
        const FVector2D ScreenCenter = { (float)GameData.Config.Overlay.ScreenWidth / 2, (float)GameData.Config.Overlay.ScreenHeight / 2};
        const FVector2D RadarSize = GameData.Radar.bRadarExtended ? GameData.Radar.MiniRadarSizeLarge : GameData.Radar.MiniRadarSizeNormal;
        const FVector2D RadarFrom = GameData.Radar.bRadarExtended ? GameData.Radar.MiniRadarFromLarge : GameData.Radar.MiniRadarFromNormal;
        const FVector MiniRadarPos = (Location - GameData.LocalPlayerInfo.Location) * 0.01f;
        //const FVector MiniRadarPos = FVector(MiniRadarWorldPos.X, MiniRadarWorldPos.Y, MiniRadarWorldPos.Z);
        //Utils::Log(1, "GameData.LocalPlayerInfo.Location: %f %f", GameData.LocalPlayerInfo.Location.X, GameData.LocalPlayerInfo.Location.Y);
        FVector2D MiniRadarScreenLocation = {
            RadarFrom.X * ScreenCenter.X * 2 + ((1.0f + MiniRadarPos.X / GameData.Radar.MiniRadarDistance) * RadarSize.X / 2.0f) * ScreenCenter.X * 2,
            RadarFrom.Y * ScreenCenter.Y * 2 + ((1.0f + MiniRadarPos.Y / GameData.Radar.MiniRadarDistance) * RadarSize.Y / 2.0f) * ScreenCenter.Y * 2
        };

        if (GameData.Config.Overlay.ScreenWidth == 2560 && GameData.Config.Overlay.ScreenHeight == 1440)
        {
            MiniRadarScreenLocation.Y -= 4.0f;
        }
        if (GameData.Config.Overlay.ScreenWidth == 2304 && GameData.Config.Overlay.ScreenHeight == 1440)
        {
            MiniRadarScreenLocation.X -= 38.0f;
            MiniRadarScreenLocation.Y -= 3.0f;
        }
        if (GameData.Config.Overlay.ScreenWidth == 1920 && GameData.Config.Overlay.ScreenHeight == 1080)
        {
            MiniRadarScreenLocation.X += 3.0f;
        }
        if (GameData.Config.Overlay.ScreenWidth == 1728 && GameData.Config.Overlay.ScreenHeight == 1080)
        {
            MiniRadarScreenLocation.X -= 28.0f;
            MiniRadarScreenLocation.Y -= 3.0f;
        }
        if (GameData.Config.Overlay.ScreenWidth == 1920 && GameData.Config.Overlay.ScreenHeight == 1200)
        {
            MiniRadarScreenLocation.X -= 28.0f;
            MiniRadarScreenLocation.Y -= 3.0f;
        }

        return MiniRadarScreenLocation;
    }

    static void Update()
    {
        auto hScatter = mem.CreateScatterHandle();
        Throttler Throttlered;
        const FVector2D DefaultSize = { 1080.0f, 1080.0f };
        int SleepTime = 4;
        while (true)
        {
            if (GameData.Scene != Scene::Gaming || GameData.Radar.MapSize.Size <= 0)
            {
                GameData.Radar.MapSize = {};
                GameData.Radar.MapGrid = 0;
                GameData.Radar.MiniMapWidget = 0;
                Sleep(GameData.ThreadSleep);
                continue;
            }

            Throttlered.executeTaskWithSleep("RadarUpdateSleep", std::chrono::milliseconds(SleepTime), [] {});

            if (Utils::ValidPtr(GameData.Radar.MapGrid)) {
                Radar::GetMapGrid(); 
            }

            if (Utils::ValidPtr(GameData.Radar.MiniMapWidget)) {
                Radar::GetMiniMapGrid();
            }

            {
                uint64_t Slot;
                ESlateVisibility Visibility;
                ESlateVisibility MiniRadarVisibility;
                FMargin Layout;
                FVector2D Alignment;
                FVector SafetyZonePosition;
                float SafetyZoneRadius;
                FVector BlueZonePosition;
                float BlueZoneRadius;
                int SelectMinimapSizeIndex;

                mem.AddScatterRead(hScatter, GameData.GameState + GameData.Offset["SafetyZonePosition"], (FVector*)&SafetyZonePosition);
                mem.AddScatterRead(hScatter, GameData.GameState + GameData.Offset["SafetyZoneRadius"], (float*)&SafetyZoneRadius);
                mem.AddScatterRead(hScatter, GameData.GameState + GameData.Offset["BlueZonePosition"], (FVector*)&BlueZonePosition);
                mem.AddScatterRead(hScatter, GameData.GameState + GameData.Offset["BlueZoneRadius"], (float*)&BlueZoneRadius);
                mem.AddScatterRead(hScatter, GameData.Radar.MiniMapWidget + GameData.Offset["SelectMinimapSizeIndex"], (int*)&SelectMinimapSizeIndex);
                mem.AddScatterRead(hScatter, GameData.Radar.MiniMapWidget + GameData.Offset["Visibility"], (ESlateVisibility*)&MiniRadarVisibility);
                mem.AddScatterRead(hScatter, GameData.Radar.MapGrid + GameData.Offset["Slot"], (uint64_t*)&Slot);
                mem.AddScatterRead(hScatter, GameData.Radar.MapWidget + GameData.Offset["Visibility"], (ESlateVisibility*)&Visibility);
                mem.ExecuteReadScatter(hScatter);

                mem.AddScatterRead(hScatter, GameData.Radar.Slot + GameData.Offset["LayoutData"] + GameData.Offset["Offsets"], (FMargin*)&Layout);
                mem.AddScatterRead(hScatter, GameData.Radar.Slot + GameData.Offset["LayoutData"] + GameData.Offset["Offsets"] + GameData.Offset["Alignment"], (FVector2D*)&Alignment);
                mem.ExecuteReadScatter(hScatter);

                GameData.Radar.Slot = Slot;
                GameData.Radar.Visibility = Visibility == ESlateVisibility::SelfHitTestInvisible;
                GameData.Radar.MiniRadarVisibility = MiniRadarVisibility == ESlateVisibility::SelfHitTestInvisible;
                GameData.Radar.Layout = Layout;
                GameData.Radar.Alignment = Alignment;
                GameData.Radar.SafetyZonePosition = SafetyZonePosition;
                GameData.Radar.SafetyZoneRadius = SafetyZoneRadius;
                GameData.Radar.BlueZonePosition = BlueZonePosition;
                GameData.Radar.BlueZoneRadius = BlueZoneRadius;
                GameData.Radar.SelectMinimapSizeIndex = SelectMinimapSizeIndex;

                if (GameData.Radar.Visibility)
                {
                    SleepTime = 0;
                }
                else {
                    SleepTime = 4;
                }

                const FVector2D CurrentSize = { GameData.Radar.Layout.Right, GameData.Radar.Layout.Bottom };
                GameData.Radar.ZoomFactor = CurrentSize.X / DefaultSize.X;

                const FVector2D CurrentPos = {
                    GameData.Radar.Layout.Right * (Alignment.X - 0.5f) - GameData.Radar.Layout.Left,
                    GameData.Radar.Layout.Bottom * (Alignment.Y - 0.5f) - GameData.Radar.Layout.Top
                };
                GameData.Radar.Position = { CurrentPos.X / DefaultSize.X / GameData.Radar.ZoomFactor * 2.0f, CurrentPos.Y / DefaultSize.Y / GameData.Radar.ZoomFactor * 2.0f };
            
                GameData.Radar.MapSizeFactored = GameData.Radar.MapSize.Size / GameData.Radar.ZoomFactor;
                GameData.Radar.WorldCenterLocation = { GameData.Radar.MapSize.Size * (1.0f + GameData.Radar.Position.X), GameData.Radar.MapSize.Size * (1.0f + GameData.Radar.Position.Y) };

                if (GameData.Radar.MiniRadarVisibility) {
                    FVector2D FHD = { (float)GameData.Config.Overlay.ScreenWidth, (float)GameData.Config.Overlay.ScreenHeight };
                    FVector2D RadarTo_FHD = { GameData.Config.Overlay.ScreenWidth * 0.846875f, GameData.Config.Overlay.ScreenHeight * 0.7351851851852f };
                    float RadarSizeNormalWidth = GameData.Config.Overlay.ScreenHeight * 0.2407407407407f;
                    RadarTo_FHD = { RadarTo_FHD.X + RadarSizeNormalWidth + 1.0f, RadarTo_FHD.Y + RadarSizeNormalWidth };
                    const float RadarSizeNormal_FHD = RadarSizeNormalWidth + 1.0f;
                    const float RadarSizeLarge_FHD = RadarSizeNormalWidth * 1.769230769230769f + 1.0f;
                    const FVector2D RadarTo = { RadarTo_FHD.X / FHD.X , RadarTo_FHD.Y / FHD.Y };
                    const FVector2D RadarSizeNormal = { RadarSizeNormal_FHD / FHD.X, RadarSizeNormal_FHD / FHD.Y };
                    const FVector2D RadarFromNormal = { RadarTo.X - RadarSizeNormal.X , RadarTo.Y - RadarSizeNormal.Y };
                    const FVector2D RadarSizeLarge = { RadarSizeLarge_FHD / FHD.X, RadarSizeLarge_FHD / FHD.Y };
                    const FVector2D RadarFromLarge = { RadarTo.X - RadarSizeLarge.X, RadarTo.Y - RadarSizeLarge.Y };
                    const bool bRadarExtended = GameData.Radar.SelectMinimapSizeIndex > 0;

                    const float SpeedPerHour = GameData.Radar.VehicleSpeed;
                    float RadarDistance =
                        SpeedPerHour < 30.0f ? 200.0f :
                        SpeedPerHour < 70.0f ? 250.0f :
                        SpeedPerHour < 95.0f ? 300.0f :
                        400.0f;

                    if (bRadarExtended)
                        RadarDistance *= RadarSizeLarge_FHD / RadarSizeNormal_FHD;

                    GameData.Radar.MiniRadarDistance = RadarDistance;
                    GameData.Radar.bRadarExtended = bRadarExtended;
                    GameData.Radar.MiniRadarSizeLarge = RadarSizeLarge;
                    GameData.Radar.MiniRadarFromLarge = RadarFromLarge;
                    GameData.Radar.MiniRadarSizeNormal = RadarSizeNormal;
                    GameData.Radar.MiniRadarFromNormal = RadarFromNormal;
                    //Utils::Log(1, "MiniRadarLocation: %f %f %f", RadarDistance, RadarSizeNormal.X, RadarSizeNormal.Y);

                }

                //Utils::Log(1, "%d %f %f %f", GameData.Radar.Visibility, GameData.Radar.ZoomFactor, GameData.Radar.Position.X, GameData.Radar.Position.Y);
            }
        }
        mem.CloseScatterHandle(hScatter);
    }
};