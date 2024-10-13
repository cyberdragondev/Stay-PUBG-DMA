#pragma once
#include <DMALibrary/Memory/Memory.h>
#include <Common/Data.h>
#include <Common/Entitys.h>
#include <Utils/Utils.h>
#include <Utils/Throttler.h>
#include <Hack/GNames.h>
#include <Utils/FNVHash.h>

class Actors
{
public:
    static void Update()
    {
        auto hScatter = mem.CreateScatterHandle();
        Throttler Throttlered;

        while (true)
        {
            if (GameData.Scene != Scene::Gaming)
            {
                Sleep(GameData.ThreadSleep);
                continue;
            }

            Throttlered.executeTask("UpdateCacheEntitys", std::chrono::milliseconds(2000), [] {
                Data::SetCacheEntitys({}); 
                //Utils::Log(1, "UpdateCacheEntitys");
            });

            //int ActorCount;
            //uint64_t Actor;

            //mem.AddScatterRead(hScatter, GameData.ActorArray + 0x8, (int*)&ActorCount);
            //mem.AddScatterRead(hScatter, GameData.ActorArray, (uint64_t*)&Actor);
            //mem.ExecuteReadScatter(hScatter);

            //if (ActorCount <= 0 || ActorCount >= 10000) {
            //    continue;
            //}

            //GameData.Actor = Actor;
            //GameData.ActorCount = ActorCount;

            std::vector<ActorEntityInfo> Entitys;
            TArray<uint64_t> ActorArray = mem.Read<TArray<uint64_t>>(GameData.ActorArray);
            for (auto Actor : ActorArray.GetVector())
            {
                ActorEntityInfo Entity;
                Entity.Index = 0;
                Entity.Entity = Actor;
                Entity.DecodeID = 0;
                Entity.ID = 0;
                Entitys.emplace_back(Entity);
            }

            std::unordered_map<uint64_t, ActorEntityInfo> CacheEntitys = Data::GetCacheEntitys();
            std::unordered_map<uint64_t, Player> CachePlayers;
            std::unordered_map<uint64_t, VehicleInfo> CacheVehicles;
            std::unordered_map<uint64_t, DroppedItemInfo> CacheDroppedItems;
            std::unordered_map<uint64_t, DroppedItemGroupInfo> CacheDroppedItemGroups;
            std::unordered_map<uint64_t, ProjectInfo> CacheProjects;
            std::unordered_map<uint64_t, PackageInfo> CachePackages;
            std::vector<int> NeedGetNameIDs;

            //for (int i = 0; i < ActorCount; ++i)
            //{
            //    ActorEntityInfo Entity;
            //    Entity.Index = i;
            //    Entity.Entity = 0;
            //    Entity.DecodeID = 0;
            //    Entity.ID = 0;
            //    Entitys.push_back(Entity);
            //}

            /*for (ActorEntityInfo& Entity : Entitys)
            {
                mem.AddScatterRead(hScatter, GameData.Actor + (Entity.Index * 0x8), (uint64_t*)&Entity.Entity);
            }*/

            //mem.ExecuteReadScatter(hScatter);

            for (ActorEntityInfo& Entity : Entitys)
            {
                if (CacheEntitys.count(Entity.Entity) > 0)
                {
                    if (CacheEntitys[Entity.Entity].DecodeID > 0 && CacheEntitys[Entity.Entity].DecodeID < 1000000 && CacheEntitys[Entity.Entity].EntityInfo.Type != EntityType::Player && CacheEntitys[Entity.Entity].EntityInfo.Type != EntityType::AI)
                    {
                        Entity = CacheEntitys[Entity.Entity];
                        continue;
                    }
                }

                mem.AddScatterRead(hScatter, Entity.Entity + GameData.Offset["ObjID"], (int*)&Entity.ID);
            }
            mem.ExecuteReadScatter(hScatter);

            for (ActorEntityInfo& Entity : Entitys)
            {
                if (!Entity.DecodeID) {
                    Entity.DecodeID = Decrypt::CIndex(Entity.ID);
                }

                EntityInfo EntityInfo = Data::GetGNameListsByIDItem(Entity.DecodeID);

                ActorEntityInfo NewActorEntityInfo;
                NewActorEntityInfo.Entity = Entity.Entity;
                NewActorEntityInfo.ID = Entity.ID;
                NewActorEntityInfo.DecodeID = Entity.DecodeID;
                NewActorEntityInfo.EntityInfo = EntityInfo;

                CacheEntitys[Entity.Entity] = NewActorEntityInfo;

                if (EntityInfo.ID == 0) {
                    NeedGetNameIDs.push_back(Entity.DecodeID);
                }
                else {

                    if (EntityInfo.Type == EntityType::Player || EntityInfo.Type == EntityType::AI) {
                        Player Player;
                        Player.Type = EntityInfo.Type;
                        Player.Entity = Entity.Entity;
                        Player.ObjID = Entity.DecodeID;

                        CachePlayers[Player.Entity] = Player;
                    }

                    if (EntityInfo.Type == EntityType::Project) {
                        ProjectInfo Project;
                        Project.Type = EntityInfo.Type;
                        Project.Entity = Entity.Entity;
                        Project.ID = Entity.DecodeID;
                        Project.Name = EntityInfo.DisplayName;
                        Project.EntityName = EntityInfo.Name;

                        CacheProjects[Project.Entity] = Project;
                    }

                    if (EntityInfo.Type == EntityType::Vehicle) {
                        VehicleInfo Vehicle;
                        Vehicle.Type = EntityInfo.Type;
                        Vehicle.Entity = Entity.Entity;
                        Vehicle.ObjID = Entity.DecodeID;
                        Vehicle.Name = EntityInfo.DisplayName;

                        CacheVehicles[Vehicle.Entity] = Vehicle;
                    }

                    if (EntityInfo.Type == EntityType::DroppedItem) {
                        DroppedItemInfo DroppedItem;
                        DroppedItem.Type = EntityInfo.Type;
                        DroppedItem.Entity = Entity.Entity;
                        DroppedItem.ID = Entity.DecodeID;

                        CacheDroppedItems[DroppedItem.Entity] = DroppedItem;
                    }

                    if (EntityInfo.Type == EntityType::DroppedItemGroup) {
                        DroppedItemGroupInfo DroppedItemGroup;
                        DroppedItemGroup.Type = EntityInfo.Type;
                        DroppedItemGroup.Entity = Entity.Entity;
                        DroppedItemGroup.ID = Entity.DecodeID;

                        CacheDroppedItemGroups[DroppedItemGroup.Entity] = DroppedItemGroup;
                    }

                    if (EntityInfo.Type == EntityType::DeadBox || EntityInfo.Type == EntityType::AirDrop)
                    {
                        PackageInfo Package;
                        Package.Type = EntityInfo.Type;
                        Package.Entity = Entity.Entity;
                        Package.ID = Entity.DecodeID;

                        CachePackages[Package.Entity] = Package;
                    }
                }
            }

            Data::SetCachePlayers(CachePlayers);
            Data::SetCacheVehicles(CacheVehicles);
            Data::SetCacheEntitys(CacheEntitys);
            Data::SetCacheDroppedItems(CacheDroppedItems);
            Data::SetCacheDroppedItemGroups(CacheDroppedItemGroups);
            Data::SetCacheProjects(CacheProjects);
            Data::SetCachePackages(CachePackages);

            if (NeedGetNameIDs.size() > 0) {
                GNames::ReadGNames(NeedGetNameIDs);
            }

            Sleep(30);
        }
        mem.CloseScatterHandle(hScatter);
    }
};