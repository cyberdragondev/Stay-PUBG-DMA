#pragma once
#include <DMALibrary/Memory/Memory.h>
#include <Common/Data.h>
#include <Common/Entitys.h>
#include <Utils/Utils.h>
#include <Utils/Throttler.h>
#include <Hack/Decrypt.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>
#include <Hack/GNames.h>
#include <Utils/Timer.h>
#include <Hack/Process.h>

inline std::queue<std::pair<std::string, PlayerRankList>> RankWorkQueue;
inline std::mutex RankQueueMutex;
inline std::condition_variable RankQueueCondition;
inline int PlayerRankWorkCount = 0;

inline uint8_t* xe_decrypt_container = (uint8_t*)VirtualAlloc(nullptr, 0x100, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);


class Players
{
public:
    
    static bool xe_init(const uint64_t offset)
    {
        const uintptr_t decrypt_ptr = *(uintptr_t*)(Process::Dump + offset);
        if (!decrypt_ptr)
            return false;

        uint8_t backup_bytes[0x100];

        mem.Read(decrypt_ptr, (void*)backup_bytes, sizeof(backup_bytes));

        *(uint16_t*)(xe_decrypt_container + 0x0) = static_cast<uint16_t>(0xB848);
        *(uintptr_t*)(xe_decrypt_container + 0x2) = decrypt_ptr + mem.Read<int32_t>((void*)(decrypt_ptr + 0x3)) + 7;

        memcpy(&xe_decrypt_container[0xA], &backup_bytes[0x7], 0x100 - 0xA);
    }

    static uintptr_t xe_decrypt(const uintptr_t encrypted)
    {
        typedef uintptr_t(__fastcall* xe_decrypt_fn_t)(uint64_t, uintptr_t);
        return xe_decrypt_fn_t(xe_decrypt_container)(0, encrypted);
    }

    static void LoadLists(int type)
    {
        std::unordered_map <std::string, int> PlayerWhiteLists;
        std::unordered_map <std::string, int> PlayerBlackLists;
        std::string filename = "Config/BlackLists.txt";
        if (type == 2) {
            filename = "Config/WhiteLists.txt";
        }

        std::ifstream file(filename);
        if (!file.is_open()) {
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            if (type == 2) {
                PlayerWhiteLists[line] = 1;
            }
            else {
                PlayerBlackLists[line] = 1;
            }
        }

        if (type == 2) {
            Data::SetPlayerWhiteLists(PlayerWhiteLists);
        }
        else {
            Data::SetPlayerBlackLists(PlayerBlackLists);
        }

        file.close();
    }

    static void SaveLists(int type) {

        std::unordered_map <std::string, int> PlayerWhiteLists = Data::GetPlayerWhiteLists();
        std::unordered_map <std::string, int> PlayerBlackLists = Data::GetPlayerBlackLists();
        std::string filename;
        std::unordered_map<std::string, int> currentList;

        if (type == 2) {
            filename = "Config/WhiteLists.txt";
            currentList = PlayerWhiteLists;
        }
        else {
            filename = "Config/BlackLists.txt";
            currentList = PlayerBlackLists;
        }

        std::ofstream file(filename);
        if (!file.is_open()) {
            return;
        }

        for (const auto& entry : currentList) {
            file << entry.first << std::endl;
        }

        file.close();
    }

    static void AddToBlackList(const std::string& name) {
        Data::DeletePlayerWhiteListsItem(name);
        SaveLists(2);
        Data::SetPlayerBlackListsItem(name, 1);
        SaveLists(1);
    }

    static void AddToWhiteList(const std::string& name) {
        Data::DeletePlayerBlackListsItem(name);
        SaveLists(1);
        Data::SetPlayerWhiteListsItem(name, 1);
        SaveLists(2);
    }

    static void RemoveList(const std::string& name) {
        Data::DeletePlayerBlackListsItem(name);
        Data::DeletePlayerWhiteListsItem(name);
        SaveLists(1);
        SaveLists(2);
    }

    static void ReadPlayerLists()
    {
        LoadLists(1);
        LoadLists(2);
    }

    static void UpdateFogPlayers()
    {
        while (true)
        {
            if (GameData.Scene != Scene::Gaming)
            {
                Sleep(GameData.ThreadSleep);
                continue;
            }

            std::unordered_map<uint64_t, FogPlayerInfo> FogPlayerInfos;
            TArray<uint64_t> DormantCharacterClientList = mem.Read<TArray<uint64_t>>(GameData.AntiCheatCharacterSyncManager + GameData.Offset["DormantCharacterClientList"]);
            for (auto FogPlayerEntity : DormantCharacterClientList.GetVector())
            {
                FogPlayerInfo FogPlayer;
                FogPlayerInfos[FogPlayerEntity] = FogPlayer;
            }

            Data::SetFogPlayers(FogPlayerInfos);

            std::this_thread::sleep_for(std::chrono::microseconds(1));
        }
    }

    static void UpdatePlayerLists()
    {
        if (GameData.Scene == Scene::Gaming)
        {
            auto PlayerBlackLists = Data::GetPlayerBlackLists();
            auto PlayerWhiteLists = Data::GetPlayerWhiteLists();
            auto LocalPlayerInfo = GameData.LocalPlayerInfo;
            auto ScatterHandle = mem.CreateScatterHandle();

            std::unordered_map<std::string, GamePlayerInfo> GPlayerLists;
            std::unordered_map<std::string, PlayerRankList> PlayerRankLists = Data::GetPlayerRankLists();

            std::vector<GamePlayerInfo> playerLists;
            GameData.PlayerCount = mem.Read<int>(GameData.GameState + GameData.Offset["PlayerArray"] + 0x8);
            if (GameData.PlayerCount <= 0)
            {
                return;
            }
            uint64_t* PlayerArrayBuffer = new uint64_t[GameData.PlayerCount];
            mem.Read(mem.Read<uint64_t>(GameData.GameState + GameData.Offset["PlayerArray"]), PlayerArrayBuffer, sizeof(uint64_t) * GameData.PlayerCount);
            std::vector<uint64_t> PlayerArray(PlayerArrayBuffer, PlayerArrayBuffer + GameData.PlayerCount);

            for (auto& pPlayerInfo : PlayerArray)
            {
                GamePlayerInfo player;
                player.pPlayerInfo = pPlayerInfo;
                playerLists.push_back(player);
            }

            for (GamePlayerInfo& player : playerLists)
            {
                mem.AddScatterRead(ScatterHandle, player.pPlayerInfo + GameData.Offset["PlayerName"], (uint64_t*)&player.pPlayerName);
                mem.AddScatterRead(ScatterHandle, player.pPlayerInfo + GameData.Offset["PlayerStatusType"], (BYTE*)&player.StatusType);
                mem.AddScatterRead(ScatterHandle, player.pPlayerInfo + GameData.Offset["AccountId"], (uint64_t*)&player.pAccountId);
                mem.AddScatterRead(ScatterHandle, player.pPlayerInfo + GameData.Offset["TeamNumber"], (int*)&player.TeamID);
                mem.AddScatterRead(ScatterHandle, player.pPlayerInfo + GameData.Offset["SquadMemberIndex"], (int*)&player.SquadMemberIndex);
                mem.AddScatterRead(ScatterHandle, player.pPlayerInfo + GameData.Offset["PartnerLevel"], (EPartnerLevel*)&player.PartnerLevel);
                mem.AddScatterRead(ScatterHandle, player.pPlayerInfo + GameData.Offset["PubgIdData"], (FWuPubgIdData*)&player.PubgIdData);
                mem.AddScatterRead(ScatterHandle, player.pPlayerInfo + GameData.Offset["PlayerStatistics"], (int*)&player.KillCount);
                mem.AddScatterRead(ScatterHandle, player.pPlayerInfo + GameData.Offset["DamageDealtOnEnemy"], (float*)&player.DamageDealtOnEnemy);
                mem.AddScatterRead(ScatterHandle, player.pPlayerInfo + GameData.Offset["CharacterClanInfo"] + 0x20, (uint64_t*)&player.pClanName);
            }

            mem.ExecuteReadScatter(ScatterHandle);

            for (GamePlayerInfo& player : playerLists)
            {
                mem.AddScatterRead(ScatterHandle, player.pClanName, (FText*)&player.FClanName);
                mem.AddScatterRead(ScatterHandle, player.pPlayerName, (FText*)&player.FPlayerName);
                mem.AddScatterRead(ScatterHandle, player.pAccountId, (FText*)&player.FAccountId);
            }

            mem.ExecuteReadScatter(ScatterHandle);

            for (GamePlayerInfo& player : playerLists)
            {
                player.ClanName = Utils::UnicodeToAnsi(player.FClanName.buffer);
                player.AccountId = Utils::UnicodeToAnsi(player.FAccountId.buffer);
                player.PlayerName = Utils::UnicodeToAnsi(player.FPlayerName.buffer);
                player.TeamID = (player.TeamID >= 100000) ? (player.TeamID - 100000) : player.TeamID;
                player.IsMyTeam = GameData.LocalPlayerInfo.TeamID == player.TeamID;
                player.IsSelf = LocalPlayerInfo.Name == player.PlayerName;

                if (PlayerBlackLists.find(player.AccountId) != PlayerBlackLists.end()) {
                    player.ListType = 1;
                }
                else if (PlayerWhiteLists.find(player.AccountId) != PlayerWhiteLists.end()) {
                    player.ListType = 2;
                }

                if (player.PubgIdData.SurvivalTier > 0) player.PubgIdData.SurvivalLevel = (player.PubgIdData.SurvivalTier - 1) * 500 + player.PubgIdData.SurvivalLevel;

            }

            for (GamePlayerInfo& player : playerLists)
            {
                if (player.PlayerName == "") {
                    continue;
                }

                GPlayerLists[player.PlayerName] = player;

                if (PlayerRankLists.count(player.PlayerName) == 0 && (player.StatusType == 8 || player.StatusType == 12))
                {
                    PlayerRankList playerRankList;
                    PlayerRankLists[player.PlayerName] = playerRankList;
                    Data::SetPlayerRankListsItem(player.PlayerName, {});
                }
            }

            Data::SetPlayerLists(GPlayerLists);

            mem.CloseScatterHandle(ScatterHandle);

        }
        else {
            Data::SetPlayerLists({});
        }
    }

    static uint64_t Xe(uint64_t Encrypted)
    {
        return Encrypted != NULL ? ((uint64_t(__fastcall*)(uint64_t, uint64_t))(*(uint64_t*)(Process::Dump + GameData.Offset["XenuineDecrypt"])))(0, Encrypted) : NULL;
    };

    static bool LineTraceSingle(FVector TraceStart, FVector TraceEnd)
    {
        FHitResult UnKnowFHitResult = { 0 };
        typedef bool(__fastcall* fnLineTraceSingle)(
            void* WorldContextObject,
            FVector Start,
            FVector End,
            ETraceTypeQuery TraceChannel,
            bool bTraceComplex,
            void* ActorsToIgnore,
            EDrawDebugTrace DrawDebugType,
            FHitResult* Outhit,
            bool bIgnoreSelf,
            FLinearColor TraceColor,
            FLinearColor TraceHitColor,
            float DrawTime
        );
        fnLineTraceSingle pfnLineTraceSingle = fnLineTraceSingle((void*)(Process::Dump + 0x7C34554));
        //pfnLineTraceSingle(nullptr, TraceStart, TraceEnd, ETraceTypeQuery::TraceTypeQuery1,true, nullptr, EDrawDebugTrace__None, &UnKnowFHitResult, true, FLinearColor(), FLinearColor(), 0.f);
        return 1;
        //return !spoof_call<bool>(Process::Dump + 0x7C34554, GameData.UWorld, &TraceStart, &TraceEnd, 0, true, GameData.ActorArray, 0, &UnKnowFHitResult, true);
    }

    //91E2B0 3-20
    static void DecryptedFloat(float* a1, unsigned int a2, char a3) {
        uint32_t v7[16] = { GameData.Offset["DecryptedHealthOffsets0"], GameData.Offset["DecryptedHealthOffsets1"], GameData.Offset["DecryptedHealthOffsets2"], GameData.Offset["DecryptedHealthOffsets3"],
                            GameData.Offset["DecryptedHealthOffsets4"], GameData.Offset["DecryptedHealthOffsets5"], GameData.Offset["DecryptedHealthOffsets6"], GameData.Offset["DecryptedHealthOffsets7"],
                            GameData.Offset["DecryptedHealthOffsets8"], GameData.Offset["DecryptedHealthOffsets9"], GameData.Offset["DecryptedHealthOffsets10"], GameData.Offset["DecryptedHealthOffsets11"],
                            GameData.Offset["DecryptedHealthOffsets12"], GameData.Offset["DecryptedHealthOffsets13"], GameData.Offset["DecryptedHealthOffsets14"], GameData.Offset["DecryptedHealthOffsets15"]};

        auto* ptr = reinterpret_cast<unsigned char*>(a1); // 将float指针转换为字节指针
        for (unsigned int i = 0; i < a2; ++i) {
            char v5 = i + a3;
            ptr[i] ^= reinterpret_cast<char*>(v7)[v5 & 0x3F];
        }
    }

    static void Update()
    {
        Throttler Throttlered;
        Throttler ThrottleredSleep;
        auto hScatter = mem.CreateScatterHandle();
        std::unordered_map<uint64_t, tMapInfo> EnemyInfoMap;
        float TimeSeconds = 0.f;
        while (true)
        {
            if (GameData.Scene != Scene::Gaming)
            {
                TimeSeconds = 0.f;
                GameData.FogPlayerCount = 0;
                EnemyInfoMap.clear();
                Data::SetPlayerLists({});
                GameData.LocalPlayerInfo = Player();
                Sleep(GameData.ThreadSleep);
                continue;
            }

            //ThrottleredSleep.executeTaskWithSleep("PlayersSleep", std::chrono::milliseconds(2), [] {});

            //if (GameData.VirtualProtect)
            //{
            //    Utils::Log(1, "Process::Dump: %p", Process::Dump);
            //    LineTraceSingle(GameData.Camera.Location, GameData.Camera.Location);
            //   /* auto UWorld = *(uint64_t*)(Process::Dump + GameData.Offset["UWorld"]);
            //    Utils::Log(1, "UWorld %p %p", Decrypt::Xe(UWorld), GameData.UWorld);*/
            //    /*uintptr_t data[3]{ 0, (uintptr_t)0, 0 };
            //    static auto func = (uintptr_t)Process::Dump + 0x77950C0;
            //    auto result = ((uint64_t(__fastcall*)(uintptr_t*))func)(data);
            //    Utils::Log(1, "result: %p", result);*/
            //   // Utils::Log(1, "%p", *(uint64_t*)(Process::Dump + GameData.Offset["XenuineDecrypt"]));
            //}

            int FogPlayerCount = 0;

            std::unordered_map<uint64_t, Player> CachePlayers = Data::GetCachePlayers();
            std::unordered_map<uint64_t, Player> PlayersData = Data::GetPlayersData();
            std::unordered_map<uint64_t, FogPlayerInfo> FogPlayers = Data::GetFogPlayers();

            Throttlered.executeTask("UpdatePlayersData", std::chrono::milliseconds(88), [&hScatter, &CachePlayers, &PlayersData] {
                for (auto& Item : CachePlayers)
                {
                    Player& Player = Item.second;

                    mem.AddScatterRead(hScatter, Player.Entity + GameData.Offset["RootComponent"], (uint64_t*)&Player.RootComponent);
                    mem.AddScatterRead(hScatter, Player.Entity + GameData.Offset["CharacterMovement"], (uint64_t*)&Player.CharacterMovement);
                    mem.AddScatterRead(hScatter, Player.Entity + GameData.Offset["Mesh"], (uint64_t*)&Player.MeshComponent);
                    mem.AddScatterRead(hScatter, Player.Entity + GameData.Offset["PlayerState"], (uint64_t*)&Player.PlayerState);
                    mem.AddScatterRead(hScatter, Player.Entity + GameData.Offset["GroggyHealth"], (float*)&Player.GroggyHealth);
                    mem.AddScatterRead(hScatter, Player.Entity + GameData.Offset["SpectatedCount"], (int*)&Player.SpectatedCount);
                    mem.AddScatterRead(hScatter, Player.Entity + GameData.Offset["LastTeamNum"], (int*)&Player.TeamID);
                    mem.AddScatterRead(hScatter, Player.Entity + GameData.Offset["CharacterName"], (uint64_t*)&Player.pCharacterName);
                    mem.AddScatterRead(hScatter, Player.Entity + GameData.Offset["CharacterState"], (ECharacterState*)&Player.CharacterState);
                    mem.AddScatterRead(hScatter, Player.Entity + GameData.Offset["AimOffsets"], (FRotator*)&Player.AimOffsets);
                    mem.AddScatterRead(hScatter, Player.Entity + GameData.Offset["WeaponProcessor"], (uint64_t*)&Player.WeaponProcessor);
                    mem.AddScatterRead(hScatter, Player.Entity + GameData.Offset["Gender"], (EGender*)&Player.Gender);
                    mem.AddScatterRead(hScatter, Player.Entity + GameData.Offset["bEncryptedHealth"], (BYTE*)&Player.bEncryptedHealth);
                    mem.AddScatterRead(hScatter, Player.Entity + GameData.Offset["EncryptedHealthOffset"], (unsigned char*)&Player.EncryptedHealthOffset);
                    mem.AddScatterRead(hScatter, Player.Entity + GameData.Offset["DecryptedHealthOffset"], (unsigned char*)&Player.DecryptedHealthOffset);
                }
                mem.ExecuteReadScatter(hScatter);

                for (auto& Item : CachePlayers)
                {
                    Player& Player = Item.second;

                    // Utils::Log(1, "Player.Gender: %d", Player.Gender);

                    Player.RootComponent = Decrypt::Xe(Player.RootComponent);
                    Player.CharacterMovement = Decrypt::Xe(Player.CharacterMovement);

                    //Utils::Log(1, "%p", Player.PlayerState);
                    Player.PlayerState = Decrypt::Xe(Player.PlayerState);

                   //Utils::Log(1, "%p", Player.PlayerState);

                    mem.AddScatterRead(hScatter, Player.pCharacterName, (FText*)&Player.CharacterName);
                    mem.AddScatterRead(hScatter, Player.MeshComponent + GameData.Offset["AnimScriptInstance"], (uint64_t*)&Player.AnimScriptInstance);
                    mem.AddScatterRead(hScatter, Player.RootComponent + GameData.Offset["ComponentLocation"], (FVector*)&Player.Location);
                }
                mem.ExecuteReadScatter(hScatter);

                auto GamePlayerLists = Data::GetPlayerLists();

                for (auto& Item : CachePlayers)
                {
                    Player& Player = Item.second;

                    if (Player.Entity == GameData.CameraViewTarget) Player.IsMe = true;
                    Player.TeamID = (Player.TeamID >= 100000) ? (Player.TeamID - 100000) : Player.TeamID;
                    Player.IsMyTeam = Player.TeamID == GameData.LocalPlayerTeamID;
                    Player.InScreen = true;
                    Player.Name = Utils::RemoveBracketsAndTrim(Utils::UnicodeToAnsi(Player.CharacterName.buffer));

                    GamePlayerInfo PlayerInfo = GamePlayerLists[Player.Name];

                    Player.ClanName = PlayerInfo.ClanName;
                    Player.SurvivalLevel = PlayerInfo.PubgIdData.SurvivalLevel;
                    Player.PartnerLevel = PlayerInfo.PartnerLevel;
                    Player.DamageDealtOnEnemy = PlayerInfo.DamageDealtOnEnemy;
                    Player.KillCount = PlayerInfo.KillCount;
                    Player.ListType = PlayerInfo.ListType;
                    Player.SquadMemberIndex = PlayerInfo.SquadMemberIndex;
                    Player.AccountId = PlayerInfo.AccountId;

                    FVector2D WorldToScreen = VectorHelper::WorldToScreen(Player.Location);

                    if (!Player.IsMe && (WorldToScreen.X < -100 || WorldToScreen.X > GameData.Config.Overlay.ScreenWidth + 100 || WorldToScreen.Y < -100 || WorldToScreen.Y > GameData.Config.Overlay.ScreenHeight + 100))
                    {
                        Player.InScreen = false;
                        continue;
                    }

                    mem.AddScatterRead(hScatter, Player.AnimScriptInstance + GameData.Offset["PreEvalPawnState"], (EAnimPawnState*)&Player.PreEvalPawnState);
                    mem.AddScatterRead(hScatter, Player.WeaponProcessor + GameData.Offset["EquippedWeapons"], (uint64_t*)&Player.EquippedWeapons);
                    mem.AddScatterRead(hScatter, Player.WeaponProcessor + GameData.Offset["CurrentWeaponIndex"], (BYTE*)&Player.CurrentWeaponIndex);
                }

                mem.ExecuteReadScatter(hScatter);

                for (auto& Item : CachePlayers)
                {
                    Player& Player = Item.second;

                    if (!Player.InScreen)
                    {
                        continue;
                    }

                    if (Player.CurrentWeaponIndex >= 0 && Player.CurrentWeaponIndex < 8)
                    {
                        mem.AddScatterRead(hScatter, Player.EquippedWeapons + Player.CurrentWeaponIndex * 8, (uint64_t*)&Player.CurrentWeapon);
                    }
                }

                mem.ExecuteReadScatter(hScatter);

                for (auto& Item : CachePlayers)
                {
                    Player& Player = Item.second;

                    if (!Player.InScreen)
                    {
                        continue;
                    }

                    if (Player.CurrentWeapon > 0)
                    {
                        mem.AddScatterRead(hScatter, Player.CurrentWeapon + GameData.Offset["ObjID"], (int*)&Player.WeaponID);
                        mem.AddScatterRead(hScatter, Player.CurrentWeapon + GameData.Offset["WeaponConfig_WeaponClass"], (EWeaponClass*)&Player.WeaponClass);

                        if (Player.IsMe) { 
                            mem.AddScatterRead(hScatter, Player.CurrentWeapon + GameData.Offset["ElapsedCookingTime"], (float*)&Player.ElapsedCookingTime);
                            mem.AddScatterRead(hScatter, Player.AnimScriptInstance + GameData.Offset["bIsScoping_CP"], (bool*)&Player.IsScoping);
                        }
                    }
                }

                mem.ExecuteReadScatter(hScatter);

                for (auto& Item : CachePlayers)
                {
                    Player& Player = Item.second;

                    Player.WeaponID = Decrypt::CIndex(Player.WeaponID);
                    Player.WeaponEntityInfo = Data::GetGNameListsByIDItem(Player.WeaponID);
                    Player.WeaponName = Player.WeaponEntityInfo.DisplayName;

                    PlayersData[Player.Entity] = Player;
                }
                });

            for (auto& Item : CachePlayers)
            {
                Player& Player = Item.second;

                if (PlayersData.count(Player.Entity) > 0)
                {
                    Player = PlayersData[Player.Entity];
                    Player.InScreen = true;
                }
            }

            for (auto& Item : CachePlayers)
            {
                Player& Player = Item.second;

                if (Player.bEncryptedHealth == 0)
                {
                    mem.AddScatterRead(hScatter, Player.Entity + GameData.Offset["Health"], (float*)&Player.Health);
                }
                else {
                    mem.AddScatterRead(hScatter, Player.Entity + GameData.Offset["Health"] + Player.EncryptedHealthOffset, (float*)&Player.Health);
                }

                mem.AddScatterRead(hScatter, Player.MeshComponent + GameData.Offset["Eyes"], (int*)&Player.Eyes);
                //mem.AddScatterRead(hScatter, Player.Entity + GameData.Offset["Health"], (float*)&Player.Health);
                mem.AddScatterRead(hScatter, Player.MeshComponent + GameData.Offset["StaticMesh"], (uint64_t*)&Player.StaticMesh);
                //mem.AddScatterRead(hScatter, Player.MeshComponent + GameData.Offset["bVisible"], (uint64_t*)&Player.bVisible);
                mem.AddScatterRead(hScatter, Player.MeshComponent + GameData.Offset["bAlwaysCreatePhysicsState"], (UCHAR*)&Player.bAlwaysCreatePhysicsState);
                mem.AddScatterRead(hScatter, Player.MeshComponent + GameData.Offset["ComponentToWorld"], (FTransform*)&Player.ComponentToWorld);
                mem.AddScatterRead(hScatter, Player.RootComponent + GameData.Offset["ComponentLocation"], (FVector*)&Player.Location);

                //if (Player.Name == "Crazyultiamann")
                //{
                //    Utils::Log(1, "Entity: %p | %p | %d", Player.Entity, Player.RootComponent, mem.Read<int>(Player.Entity + GameData.Offset["FogIndex"]));
                //    //Utils::Log(1, "RootComponent: %p", Player.RootComponent);
                //}
                //Utils::Log(1, "Entity: %p | %p | %d", Player.Entity, Player.RootComponent, mem.Read<int>(Player.Entity + 0x09D0));

            }

            mem.ExecuteReadScatter(hScatter);

            for (auto& Item : CachePlayers)
            {
                Player& Player = Item.second;

                if (Player.bEncryptedHealth != 0) {
                    DecryptedFloat(&Player.Health, sizeof(Player.Health), Player.DecryptedHealthOffset);
                }

                FVector2D WorldToScreen = VectorHelper::WorldToScreen(Player.Location);

                /*Player.bVisible = 1;

                if (FogPlayers.count(Player.Entity) > 0)
                {
                    Player.bVisible = 0;
                }*/

                if (Player.bAlwaysCreatePhysicsState == 4)
                {
                    //Utils::Log(1, "%s %f %f %f", Player.Name, Player.ComponentToWorld.Translation.X, Player.ComponentToWorld.Translation.Y , Player.ComponentToWorld.Translation.Z);
                    Player.InFog = true;
                    Player.InScreen = false;
                    FogPlayerCount++;
                }
                else {

                    if (!Player.IsMe && (WorldToScreen.X < -100 || WorldToScreen.X > GameData.Config.Overlay.ScreenWidth + 100 || WorldToScreen.Y < -100 || WorldToScreen.Y > GameData.Config.Overlay.ScreenHeight + 100))
                    {
                        Player.InScreen = false;
                        continue;
                    }
                }

                if (!Player.InScreen || Player.IsMe || Player.IsMyTeam)
                {
                    continue;
                }

                for (EBoneIndex Bone : SkeletonLists::Bones)
                {
                    int BoneIndex = Bone;
                    //if (/*Player.Sex == 0*/Player.Gender == EGender::Male && (Bone == EBoneIndex::Thigh_L || Bone == EBoneIndex::Calf_L || Bone == EBoneIndex::Foot_L || Bone == EBoneIndex::Thigh_R || Bone == EBoneIndex::Calf_R || Bone == EBoneIndex::Foot_R))
                    //{
                    //    BoneIndex -= 4;
                    //}
                    mem.AddScatterRead(hScatter, Player.StaticMesh + (static_cast<unsigned long long>(BoneIndex) * 0x30), (FTransform*)&Player.Skeleton.Bones[Bone]);
                }
            }

            mem.ExecuteReadScatter(hScatter);

            /*float ActualDamage;
            uint64_t PlayerInstigator;
            FVector AttackerLocation;
            FName AttackerWeaponName;
            int ID;
            int ID2;
            mem.AddScatterRead(hScatter, GameData.LocalPlayerInfo.Entity + 0x16e0 + 0x0, (float*)&ActualDamage);
            mem.AddScatterRead(hScatter, GameData.LocalPlayerInfo.Entity + 0x16e0 + 0x50, (FVector*)&AttackerLocation);
            mem.AddScatterRead(hScatter, GameData.LocalPlayerInfo.Entity + 0x16e0 + 0x48, (FName*)&AttackerWeaponName);
            mem.AddScatterRead(hScatter, GameData.LocalPlayerInfo.Entity + 0x16e0 + 0x1c, (int*)&ID);
            mem.AddScatterRead(hScatter, GameData.LocalPlayerInfo.PlayerState + 0xcf0, (int*)&ID2);
            mem.AddScatterRead(hScatter, GameData.LocalPlayerInfo.Entity + 0x960, (uint64_t*)&PlayerInstigator);
            mem.ExecuteReadScatter(hScatter);*/
           // PlayerInstigator *= 24;
           // Utils::Log(1, "ActualDamage: %f | %p | %d | %d", ActualDamage, PlayerInstigator, ID, ID2);
            //Utils::Log(1, "AttackerLocation: %f %f %f", AttackerLocation.X, AttackerLocation.Y, AttackerLocation.Z);

            if (!GameData.AimBot.Lock)
            {
                GameData.AimBot.Type = EntityType::Player;
                GameData.AimBot.Target = 0;
                GameData.AimBot.Bone = 0;
                GameData.AimBot.ScreenDistance = 1000.0f;
            }

            AimBotConfig Config = GameData.Config.AimBot.Configs[GameData.Config.AimBot.ConfigIndex].Weapon[WeaponTypeToString[GameData.LocalPlayerInfo.WeaponEntityInfo.WeaponType]];
            if (Config.DynamicFov) {
                Config.FOV = Config.FOV * (90.0f / GameData.Camera.FOV);
                Config.WheelFOV = Config.FOV * (90.0f / GameData.Camera.FOV);
            }

            bool IsWheelKeyDown = GameData.Keyboard.IsKeyDown(Config.Wheel.Key);

            for (auto& Item : CachePlayers)
            {
                Player& Player = Item.second;

                Player.IsVisible = Player.Eyes >= GameData.LocalPlayerInfo.Eyes;
                Player.Distance = GameData.Camera.Location.Distance(Player.Location) / 100.0f;
                Player.IsAimMe = false;
                Player.State =
                    Player.Health > 0.0f ? CharacterState::Alive :
                    Player.GroggyHealth > 0.0f ? CharacterState::Groggy :
                    CharacterState::Dead;

                if (Player.CharacterState == ECharacterState::Offline)
                {
                    //掉线
                    Player.RadarState = ECharacterIconType::Quitter;
                }
                else if (Player.State == CharacterState::Groggy)
                {
                    //倒地
                    Player.RadarState = ECharacterIconType::Groggy;
                }
                //else if (Player.PreEvalPawnState == EAnimPawnState::PS_VehicleDriver || Player.PreEvalPawnState == EAnimPawnState::PS_VehiclePassenger)
                //{
                //    //开车&&坐车
                //    Player.RadarState = ECharacterIconType::Vehicle;
                //}
                //else if (Player.PreEvalPawnState == EAnimPawnState::PS_SecondaryLocomotion)
                //{
                //    //跳伞
                //    
                //    Player.RadarState = ECharacterIconType::Parachute;
                //}

                Player.Location = Player.ComponentToWorld.Translation;

                float TimeStampDelta = GameData.WorldTimeSeconds - EnemyInfoMap[Player.Entity].TimeStamp;
                EnemyInfoMap[Player.Entity].TimeStamp = GameData.WorldTimeSeconds;
                //PosInfo
                [&] {
                    auto& PosInfo = EnemyInfoMap[Player.Entity].PosInfo.Info;

                    if (Player.State == CharacterState::Dead) {
                        PosInfo.clear();
                    }
                    else {

                        if (TimeStampDelta)
                            PosInfo.push_front({ GameData.WorldTimeSeconds, Player.Location });

                        if (PosInfo.size() > 200)
                            PosInfo.pop_back();

                        float SumTimeDelta = 0.0f;
                        FVector SumPosDif;

                        for (size_t i = 1; i < PosInfo.size(); i++) {
                            const float DeltaTime = PosInfo[i - 1].Time - PosInfo[i].Time;
                            const FVector DeltaPos = PosInfo[i - 1].Pos - PosInfo[i].Pos;
                            const FVector DeltaVelocity = DeltaPos * (1.0f / DeltaTime);
                            const float DeltaSpeedPerHour = DeltaVelocity.Length() / 100.0f * 3.6f;

                            if (DeltaTime > 0.05f || DeltaSpeedPerHour > 500.0f) {
                                PosInfo.clear();
                            }
                            else {
                                SumTimeDelta = SumTimeDelta + DeltaTime;
                                SumPosDif = SumPosDif + DeltaPos;

                                if (SumTimeDelta > 0.15f)
                                    break;
                            }
                        }
                        if (SumTimeDelta > 0.1f) {
                            Player.Velocity = SumPosDif * (1.0f / SumTimeDelta);
                        }
                    }
                    }();

                PlayersData[Player.Entity] = Player;

                if (Player.IsMe)
                {
                   /* GTakeHitInfo GTakeHitInfo;

                    mem.AddScatterRead(hScatter, Player.Entity + 0x16e0 + 0x0, (float*)&GTakeHitInfo.ActualDamage);
                    mem.AddScatterRead(hScatter, Player.Entity + 0x16e0 + 0x50, (FVector*)&GTakeHitInfo.AttackerLocation);
                    mem.AddScatterRead(hScatter, Player.Entity + 0x16e0 + 0x48, (FName*)&GTakeHitInfo.AttackerWeaponName);
                    mem.ExecuteReadScatter(hScatter);

                    Player.TakeHitInfo = GTakeHitInfo;*/

                    GameData.LocalPlayerInfo = Player;
                    GameData.LocalPlayerTeamID = Player.TeamID;
                }

                if (!Player.InScreen || Player.IsMe || Player.IsMyTeam)
                {
                    continue;
                }

                FVector AimFov = VectorHelper::CalculateAngles(Player.Location, GameData.LocalPlayerInfo.Location);
                FRotator AmiMz = Player.AimOffsets;
                AmiMz.Clamp();
                int32_t AimX = int32_t(abs(AimFov.X - AmiMz.Yaw));
                int32_t AimY = int32_t(abs(AimFov.Y - AmiMz.Pitch));

                if (AimX <= 2 && AimY <= 2)
                {
                    Player.IsAimMe = true;
                }

                for (EBoneIndex Bone : SkeletonLists::Bones)
                {
                    Player.Skeleton.LocationBones[Bone] = VectorHelper::GetBoneWithRotation(Player.Skeleton.Bones[Bone], Player.ComponentToWorld);
                    Player.Skeleton.ScreenBones[Bone] = VectorHelper::WorldToScreen(Player.Skeleton.LocationBones[Bone]);
                }

                //自瞄筛选
                if ((!GameData.AimBot.Lock || Utils::ValidPtr(GameData.AimBot.Target)) && !IsWheelKeyDown)
                {
                    bool AllowAim = Player.State != CharacterState::Dead;
                    auto Bones = Config.First.Bones;

                    bool firstKeyCondition = GameData.Keyboard.IsKeyDown(Config.First.Key);
                    bool secondKeyCondition = GameData.Keyboard.IsKeyDown(Config.Second.Key);

                    if (firstKeyCondition && Config.HotkeyMerge && secondKeyCondition)
                    {
                        Bones = Config.Second.Bones;
                    }
                    else if (!Config.HotkeyMerge && secondKeyCondition)
                    {
                        Bones = Config.Second.Bones;
                    }

                    if (GameData.Keyboard.IsKeyDown(Config.Groggy.Key))
                    {
                        Bones = Config.Groggy.Bones;
                        AllowAim = Player.State == CharacterState::Groggy;
                    }

                    if (AllowAim && !Player.IsMyTeam && !Player.IsMe)
                    {
                        for (int i = 0; i < 17; i++)
                        {
                            if (Bones[i])
                            {
                                FVector2D ScreenLocation = Player.Skeleton.ScreenBones[BoneIndex[i]];
                                float Distance = Utils::CalculateDistance(GameData.Config.Overlay.ScreenWidth / 2, GameData.Config.Overlay.ScreenHeight / 2, ScreenLocation.X, ScreenLocation.Y);
                                if (Distance <= Config.FOV) {
                                    if (Distance < GameData.AimBot.ScreenDistance) {
                                        GameData.AimBot.ScreenDistance = Distance;
                                        GameData.AimBot.Target = Player.Entity;
                                        GameData.AimBot.Bone = BoneIndex[i];
                                        GameData.AimBot.Type = EntityType::Player;
                                        //Utils::Log(1, "%f", GameData.AimBot.ScreenDistance);
                                    }
                                }
                            }
                        }
                    }
                }

                if (GameData.AimBot.Target == Player.Entity) {
                    GameData.AimBot.TargetPlayerInfo = Player;
                }
            }

            if ((!GameData.AimBot.Lock || Utils::ValidPtr(GameData.AimBot.Target)) && IsWheelKeyDown && Config.AimWheel)
            {
                std::unordered_map<uint64_t, VehicleWheelInfo> VehicleWheels = Data::GetVehicleWheels();

                for (auto& Item : VehicleWheels)
                {
                    auto& Wheel = Item.second;

                    bool AllowAim = Wheel.State == WheelState::Normal;

                    Wheel.ScreenLocation = VectorHelper::WorldToScreen(Wheel.Location);
                    float Distance = Utils::CalculateDistance(GameData.Config.Overlay.ScreenWidth / 2, GameData.Config.Overlay.ScreenHeight / 2, Wheel.ScreenLocation.X, Wheel.ScreenLocation.Y);
                    if (Distance <= Config.WheelFOV) {
                        if (Distance < GameData.AimBot.ScreenDistance) {
                            GameData.AimBot.ScreenDistance = Distance;
                            GameData.AimBot.Target = Wheel.Wheel;
                            GameData.AimBot.Bone = 0;
                            GameData.AimBot.Type = EntityType::Wheel;
                        }
                    }
                }
            }

            Data::SetPlayers(CachePlayers);
            Data::SetPlayersData(PlayersData);
            GameData.FogPlayerCount = FogPlayerCount;
        }
        mem.CloseScatterHandle(hScatter);
    }
};