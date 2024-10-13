#pragma once

#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <Common/Data.h>
#include <DMALibrary/Memory/Memory.h>
#include <thread>
#include <Common/Constant.h>
#include <Utils/Utils.h>
#include <Utils/Throttler.h>
#include <Common/Entitys.h>
#include <Common/Offset.h>
#include <Common/VectorHelper.h>
#include <cstdint>

#include <Utils/Engine.h>
#include <Utils/ue4math/rotator.h>
#include <Utils/ue4math/transform.h>
#include <Utils/Timer.h>
#include <Hack/KeyState.h>
#include <Hack/Decrypt.h>
#include <Hack/GNames.h>
#include <Hack/AimBot.h>
#include <Hack/Players.h>
#include <Hack/Actors.h>
#include <Hack/Vehicles.h>
#include <Hack/Items.h>
#include <Hack/Projects.h>
#include <Hack/Radar.h>
#include <Hack/Process.h>
#include <Common/Config.h>

#include <Utils/KmBox.h>
#include <Utils/KmBoxNet.h>
#include <Utils/Lurker.h>
#include <Utils/MoBox.h>
#include <Hack/Rank.h>

class Hack
{
public:

    static void Update()
    {
        auto hScatter = mem.CreateScatterHandle();
        while (true)
        {
            mem.RefreshTLB();

            GameData.UWorld = Decrypt::Xe(mem.Read<uint64_t>(GameData.GameBase + GameData.Offset["UWorld"]));
            GameData.GameInstance = Decrypt::Xe(mem.Read<uint64_t>(GameData.UWorld + GameData.Offset["GameInstance"]));
            GameData.GNames = GNames::GetGNamesPtr();
            if (Utils::ValidPtr(GameData.UWorld) || GameData.Scene != Scene::Gaming)
            {
                Sleep(GameData.ThreadSleep);
                continue;
            }

            GameData.GameState = Decrypt::Xe(mem.Read<uint64_t>(GameData.UWorld + GameData.Offset["GameState"]));
            GameData.LocalPlayer = Decrypt::Xe(mem.Read<uint64_t>(mem.Read<uint64_t>(GameData.GameInstance + GameData.Offset["LocalPlayer"])));
            GameData.PlayerController = Decrypt::Xe(mem.Read<uint64_t>(GameData.LocalPlayer + GameData.Offset["PlayerController"]));
            GameData.AcknowledgedPawn = Decrypt::Xe(mem.Read<uint64_t>(GameData.PlayerController + GameData.Offset["AcknowledgedPawn"]));
            GameData.CurrentLevel = Decrypt::Xe(mem.Read<uint64_t>(GameData.UWorld + GameData.Offset["CurrentLevel"]));
            GameData.ActorArray = Decrypt::Xe(mem.Read<uint64_t>(GameData.CurrentLevel + GameData.Offset["Actors"]));

            uint64_t PlayerCameraManager;
            uint64_t MyHUD;
            BYTE bShowMouseCursor;
            uint64_t PlayerInput;
            uint64_t AntiCheatCharacterSyncManager;
            uint64_t CacheCameraViewTarget;

            mem.AddScatterRead(hScatter, GameData.PlayerController + GameData.Offset["PlayerCameraManager"], &PlayerCameraManager);
            mem.AddScatterRead(hScatter, GameData.PlayerController + GameData.Offset["MyHUD"], &MyHUD);
            mem.AddScatterRead(hScatter, GameData.PlayerController + GameData.Offset["bShowMouseCursor"], &bShowMouseCursor);
            mem.AddScatterRead(hScatter, GameData.PlayerController + GameData.Offset["PlayerInput"], &PlayerInput);
            mem.AddScatterRead(hScatter, GameData.PlayerController + GameData.Offset["AntiCheatCharacterSyncManager"], &AntiCheatCharacterSyncManager);
            mem.AddScatterRead(hScatter, GameData.PlayerCameraManager + GameData.Offset["ViewTarget"], &CacheCameraViewTarget);
            mem.ExecuteReadScatter(hScatter);

            GameData.PlayerCameraManager = PlayerCameraManager;
            GameData.MyHUD = MyHUD;
            GameData.bShowMouseCursor = bShowMouseCursor == 0x25 ? true : false;
            GameData.PlayerInput = PlayerInput;
            GameData.AntiCheatCharacterSyncManager = AntiCheatCharacterSyncManager;

            //GameData.ActorArrayEmpty = mem.Read<uint64_t>(GameData.LocalPlayerInfo.Entity + GameData.Offset["ActorChildren"]);

            if (!Utils::ValidPtr(CacheCameraViewTarget)) {

                int ViewTargetID = Decrypt::CIndex(mem.Read<int>(CacheCameraViewTarget + GameData.Offset["ObjID"]));
                auto ViewTargetEntityInfo = Data::GetGNameListsByIDItem(ViewTargetID);
                if (ViewTargetEntityInfo.Type == EntityType::Player || ViewTargetEntityInfo.Type == EntityType::AI)
                {
                    int TeamID = mem.Read<int>(CacheCameraViewTarget + GameData.Offset["LastTeamNum"]);
                    GameData.CameraViewTarget = CacheCameraViewTarget;
                    GameData.LocalPlayerTeamID = (TeamID >= 100000) ? (TeamID - 100000) : TeamID;
                }
            }

            Players::UpdatePlayerLists();
            Radar::UpdateWorldMapInfo();

            if(false){
                uint64_t InventoryFacade = Decrypt::Xe(mem.Read<uint64_t>(GameData.AcknowledgedPawn + GameData.Offset["InventoryFacade"]));
                uint64_t Inventory = mem.Read<uint64_t>(InventoryFacade + GameData.Offset["Inventory"]);
                auto InventoryItems = mem.Read<TArray<uint64_t>>(Inventory + GameData.Offset["InventoryItems"]);
                struct InventoryItemInfo
                {
                    uint64_t Item;
                    uint64_t ItemTable;
                    int ItemID;
                };
                std::unordered_map<uint64_t, InventoryItemInfo> CacheInventoryItemInfos;
                std::unordered_map<uint64_t, InventoryItemInfo> InventoryItemInfos;
                Utils::Log(1, "InventoryFacade: %p", InventoryFacade);
                Utils::Log(1, "Inventory: %p", Inventory);
                Utils::Log(1, "MaxSpace: %f", mem.Read<float>(Inventory + GameData.Offset["MaxSpace"]));

                for (auto& Item : InventoryItems.GetVector())
                {
                    InventoryItemInfo ItemInfo;
                    ItemInfo.Item = Item;
                    CacheInventoryItemInfos[Item] = ItemInfo;
                }

                auto hScatter = mem.CreateScatterHandle();
                for (auto& Item : CacheInventoryItemInfos)
                {
                    mem.AddScatterRead(hScatter, Item.first + GameData.Offset["ItemTable"], (uint64_t*)&Item.second.ItemTable);
                }
                mem.ExecuteReadScatter(hScatter);
                for (auto& Item : CacheInventoryItemInfos)
                {
                    mem.AddScatterRead(hScatter, Item.second.ItemTable + GameData.Offset["ItemID"], (int*)&Item.second.ItemID);
                }
                mem.ExecuteReadScatter(hScatter);
                mem.CloseScatterHandle(hScatter);

                for (auto& Item : CacheInventoryItemInfos)
                {
                    if (Item.second.ItemID == 0) continue;
                    InventoryItemInfos[Item.first] = Item.second;
                }
            }

            if (false) {
                Utils::Log(1, "GameData.PlayerController: %p", GameData.PlayerController);
                uint64_t ACCharacterSyncManager = mem.Read<uint64_t>(GameData.PlayerController + 0xe18);
                Utils::Log(1, "GameData.ACCharacterSyncManager: %p", ACCharacterSyncManager);

                //uint64_t v1 = mem.Read<uint64_t>(ACCharacterSyncManager + 0x88);
                //uint64_t v2 = mem.Read<uint64_t>(v1 + 0x8);
                //uint64_t v3 = mem.Read<int>(v1 + 0x8 + 0x8);
                //////mem.Write<BYTE>(ACCharacterSyncManager + 0xA8, (BYTE)0);
                ////BYTE v4 = mem.Read<BYTE>(ACCharacterSyncManager + 0x101);

                //Utils::Log(1, "v3: %d", v3);
                ////Utils::Log(1, "v4: %p", v4);
                //for (int i = 0; i < v3; i++)
                //{
                //    uint64_t ptr = v2 + (i * 24);
                //    uint64_t count = mem.Read<int>(ptr + 0x10);
                //    uint64_t count2 = mem.Read<int>(ptr + 0x8 + 0x8);
                //    for (size_t n = 0; n < count; n++)
                //    {
                //        auto p = mem.Read<uint64_t>(ptr + 0x8);
                //        auto id = Decrypt::CIndex(mem.Read<int>(ptr + Offset::ObjID));
                //        auto name = GNames::GetName(id);
                //        std::cout << name << std::endl;
                //        std::cout << std::hex << p << std::endl;
                //        std::cout << id << std::endl;


                //    }
                //    Utils::Log(1, "ptr: %p | count: %d %d", ptr, count, count2);
                //}
            }
            
            if(false) {
                for (int i = 0x490; i < 0x1000; i++)
                {
                    auto ptr = mem.Read<uint64_t>(GameData.PlayerController + i);
                    if (Utils::ValidPtr(ptr))
                    {
                        continue;
                    }
                    auto ObjID = Decrypt::CIndex(mem.Read<int>(ptr + Offset::ObjID));
                    if (ObjID > 3459965)
                    {
                        continue;
                    }
                    auto Name = GNames::GetName(ObjID);

                    if (Name == "ACCharacterSyncManager")
                    {
                        Utils::Log(1, "%p %d %p", ptr, ObjID, i);
                        std::cout << Name << std::endl;
                    }
                }
            }

            Sleep(300);
        }
        mem.CloseScatterHandle(hScatter);
    }

    static void UpdateCamera()
    {
        Throttler Throttlered;
        auto hScatter = mem.CreateScatterHandle();
        CameraData Camera;
        float DeltaSeconds = 0.f;
        float TimeSeconds = 0.f;

        while (true)
        {
            if (GameData.Scene != Scene::Gaming || !GameData.Config.Overlay.UseThread)
            {
                Sleep(GameData.ThreadSleep);
                continue;
            } 

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

        }
        mem.CloseScatterHandle(hScatter);
    }

    static void UpdatePID()
    {
        Throttler Throttlered;
        
        bool GameProcessFound = false;
        bool PrevGameProcessFound = false;

        while (true)
        {
            Throttlered.executeTask("UpdatePID", std::chrono::milliseconds(1500), [&GameProcessFound, &PrevGameProcessFound] {
                DWORD PID = mem.GetTslGamePID();
                if (PID == 0)
                {
                    mem.RefreshAll();
                    GameData.Scene = Scene::FindProcess;
                    GameProcessFound = false;
                    GameData.GameBase = 0;
                    GameData.PID = 0;
                    Decrypt::DestroyXe();

                    if (GameProcessFound != PrevGameProcessFound) {
                        Utils::Log(2, "The game process has ended");
                    }
                }
                else {
                    GameProcessFound = true;
                    if (GameProcessFound != PrevGameProcessFound) {
                        GameData.HookBase = mem.GetHookModuleBase();
                        Utils::Log(1, "Successfully found PlayerUnknown's Battlegrounds game progress [%p]", GameData.PID);
                        EntityInit();
                        Data::SetGNameLists(EntityLists);
                        Data::SetGNameListsByID({});
                    }
                } 
                PrevGameProcessFound = GameProcessFound;
            });

            if (GameData.PID != 0) {
                int MapID = Decrypt::CIndex(mem.Read<uint64_t>(GameData.UWorld + GameData.Offset["ObjID"]));
                Utils::Log(0, "MapID [%d]", MapID);
                GameData.MapName = GNames::GetNameByID(MapID);
                std::cout << GameData.MapName << std::endl;

                if (Utils::IsLobby(GameData.MapName)) {
                    GameData.Scene = Scene::Lobby;
                }
                else {
                    GameData.Scene = Scene::Gaming;
                }
            }

            if (GameData.Scene != GameData.PreviousScene) {
                GameData.PreviousScene = GameData.Scene;
                switch (GameData.Scene) {
                case Scene::FindProcess:
                    break;
                case Scene::Lobby:
                    break;
                case Scene::Gaming:
                    Utils::Log(0, "Entered the game scene, World name is [%s]", GameData.MapName.c_str());
                    Players::ReadPlayerLists();
                    /*while (true)
                    {
                        if (Process::Init(L"TslGame.exe")) { 
                            const uintptr_t start = (uintptr_t)Process::Dump;
                            const uintptr_t end = start + Process::ImageSize;
                            break;
                        }
                    }*/
                    break;
                default:
                    break;
                }
            }

            Sleep(1500);
        }
    }

    static void WriteFunction()
    {
        auto hScatter = mem.CreateScatterHandle();
        while (true)
        {
            /*if (GameData.Scene != Scene::Gaming)
            {
                Sleep(GameData.ThreadSleep);
                continue;
            }*/

            if (!Utils::ValidPtr(GameData.GameInstance))
            {
                Utils::Log(1, "GameData.GameInstance: %p", GameData.GameInstance);
                //Utils::Log(1, "Read: %d", mem.Read<int>(GameData.GameInstance + 0x17fd));
                int Value = 2;
                mem.AddScatterRead(hScatter, GameData.GameInstance + 0x17fd, (int*)&Value);
                mem.ExecuteWriteScatter(hScatter);
                Utils::Log(1, "Read: %d", mem.Read<int>(GameData.GameInstance + 0x17fd));
            }

            Sleep(100);

            /*std::unordered_map<uint64_t, VehicleWheelInfo> VehicleWheels = Data::GetVehicleWheels();
            for (auto& Item : VehicleWheels)
            {
                VehicleWheelInfo& Wheel = Item.second;


            }*/

            /*if (GameData.AimBot.Lock && GameData.AimBot.Type == EntityType::Wheel)
            {
                Utils::Log(1, "%p", GameData.AimBot.Target);
                float Value = 1.f;
                VehicleWheelInfo Wheel = Data::GetVehicleWheelsItem(GameData.AimBot.Target);
                mem.AddScatterWrite(hScatter, Wheel.Wheel + GameData.Offset["DampingRate"], Value);
            }
            mem.ExecuteWriteScatter(hScatter);*/

            //mem.Write<int>(GameData.AcknowledgedPawn + 0x9d0, 0);
            //Utils::Log(1, "ID: %d", mem.Read<int>(GameData.AcknowledgedPawn + 0x9d0));

            //float InputYawScale, InputPitchScale;
            /*if (!Utils::ValidPtr(GameData.AntiCheatCharacterSyncManager)) {
                float Value = 0.f;
                mem.AddScatterRead(hScatter, GameData.AntiCheatCharacterSyncManager + 0x80 + 0x8, (float*)&Value);
                mem.AddScatterRead(hScatter, GameData.AntiCheatCharacterSyncManager + 0x80 + 0x8 + 0x4, (float*)&Value);
                mem.AddScatterRead(hScatter, GameData.AntiCheatCharacterSyncManager + 0x80 + 0x8 + 0x8, (float*)&Value);
                mem.ExecuteReadScatter(hScatter);
            }*/

            //Utils::Log(1, "InputScale: %f %f", InputYawScale, InputPitchScale);

            //Sleep(10);

           // uint64_t ACCharacterSyncManager = mem.Read<uint64_t>(GameData.PlayerController + 0x0C50);
            //mem.Write<BYTE>(ACCharacterSyncManager + 0xA8, (BYTE)0);

           /* WeaponData CurrentWeaponData;
            mem.AddScatterRead(hScatter, GameData.LocalPlayerInfo.CurrentWeapon + GameData.Offset["Mesh3P"], (uint64_t*)&CurrentWeaponData.Mesh3P);
            mem.ExecuteReadScatter(hScatter);

            CurrentWeaponData.Mesh3P = Decrypt::Xe(CurrentWeaponData.Mesh3P);

            auto SkeletalMesh = mem.Read<UINT64>(CurrentWeaponData.Mesh3P + GameData.Offset["SkeletalMesh"]);
            Utils::Log(1, "SkeletalMesh: %p", SkeletalMesh);

            Sleep(1000);*/

            /*if (GameData.Keyboard.IsKeyDown(VK_LBUTTON) && GameData.Config.Function.NoRecoil)
            {
                float Value = 0.f;
                mem.AddScatterWrite(hScatter, GameData.PlayerController + GameData.Offset["InputYawScale"], 0.1f);
                mem.AddScatterWrite(hScatter, GameData.PlayerController + GameData.Offset["InputYawScale"] + 0x4, Value);
                mem.ExecuteWriteScatter(hScatter);
            }
            else {
                Sleep(1);
            }*/
        }

        mem.CloseScatterHandle(hScatter);
    }

    static void Init()
    {
        while (true)
        {
            if (!GameData.Config.Window.IsLogin)
            {
                Sleep(10);
                continue;
            }
            break;
        }

        Offset::Init();

        EntityInit();

        for (const auto& item : EntityLists)
        {
            if (item.second.Type == EntityType::Item)
            {
                ItemDetail Detail;
                Detail.Name = item.first;
                Detail.DisplayName = item.second.DisplayName;
                Detail.Type = item.second.WeaponType;

                if (Detail.Type == WeaponType::AR || Detail.Type == WeaponType::DMR || Detail.Type == WeaponType::SR)
                {
                    Detail.Group = 1;
                }
                else if (Detail.Type == WeaponType::Sight)
                {
                    Detail.Group = 2;
                }
                else if (Detail.Type == WeaponType::Drug)
                {
                    Detail.Group = 4;
                }
                else if (Detail.Type == WeaponType::Armor)
                {
                    Detail.Group = 3;
                }

                GameData.Config.Item.Lists[item.first] = Detail;
            }
        }

        Config::Load();

        if (!mem.Init("TslGame.exe", true, false))
        {
            Utils::Log(2, "Failed to initilize DMA");
            system("pause");
        }
        else {
            Utils::Log(1, "DMA initilize success");
        }

        KeyState::Init();

        Data::SetGNameLists(EntityLists);
        Data::SetGNameListsByID({});

        std::thread UpdatePIDThread(UpdatePID);
        std::thread UpdateThread(Update);
        std::thread UpdateKeyStateThread(KeyState::Update);
        std::thread UpdateActorsThread(Actors::Update);
        std::thread UpdatePlayersThread(Players::Update);
        std::thread UpdatePlayerFogsThread(Players::UpdateFogPlayers);
        std::thread UpdateVehiclesThread(Vehicles::Update);
        std::thread AimBotRunThread(AimBot::Run);
        std::thread UpdateCameraThread(UpdateCamera);
        std::thread UpdateItemsThread(Items::Update);
        std::thread UpdateProjectsThread(Projects::Update);
        std::thread UpdateRadarThread(Radar::Update);
        std::thread UpdateRankThread(Rank::Update);
        //std::thread WriteFunctionThread(WriteFunction); 
        
        UpdatePIDThread.join();
    }
};