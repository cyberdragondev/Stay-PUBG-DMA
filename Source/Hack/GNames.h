#pragma once
#include <DMALibrary/Memory/Memory.h>
#include "common/Data.h"
#include "common/Entitys.h"
#include "Decrypt.h"
#include <Utils/FNVHash.h>

class GNames
{
public:
    static void ReadGNames(std::vector<int> ids)
    {
        auto hScatter = mem.CreateScatterHandle();
        std::vector<GNameInfo> gNameInfos;
        for (auto id : ids)
        {
            GNameInfo gNameInfo;
            gNameInfo.ID = id;
            gNameInfos.push_back(gNameInfo);
        }

        for (GNameInfo& gNameInfo : gNameInfos)
        {
            mem.AddScatterRead(hScatter, GameData.GNames + ((int(gNameInfo.ID / GameData.Offset["ChunkSize"])) * 8), (uint64_t*)&gNameInfo.pGName);
        }
        mem.ExecuteReadScatter(hScatter);

        for (GNameInfo& gNameInfo : gNameInfos)
        {
            mem.AddScatterRead(hScatter, gNameInfo.pGName + ((int(gNameInfo.ID % GameData.Offset["ChunkSize"])) * 8), (uint64_t*)&gNameInfo.pName);
        }
        mem.ExecuteReadScatter(hScatter);

        for (GNameInfo& gNameInfo : gNameInfos)
        {
            mem.AddScatterRead(hScatter, gNameInfo.pName + 0x10, (FText*)&gNameInfo.FName);
        }
        mem.ExecuteReadScatter(hScatter);

        auto GNameData = Data::GetGNameListsAndGNameListsByID();

        std::unordered_map<std::string, EntityInfo, FnvHash> GNameLists = GNameData.first;
        std::unordered_map<int, EntityInfo> GNameListsByID = GNameData.second;

        for (GNameInfo& gNameInfo : gNameInfos)
        {
            if (gNameInfo.ID > 0) {
                std::string name = gNameInfo.FName.buffer;

                if (GNameLists.count(name) > 0) {
                    GNameLists[name].ID = gNameInfo.ID;
                    GNameLists[name].Name = name;
                    GNameListsByID[gNameInfo.ID] = GNameLists[name];
                }
                else {
                    EntityInfo entityInfo;
                    entityInfo.ID = gNameInfo.ID;
                    entityInfo.DisplayName = name;
                    entityInfo.Name = name;
                    GNameLists[name] = entityInfo;
                    GNameListsByID[gNameInfo.ID] = GNameLists[name];
                }
            }
        }

        Data::SetGNameListsAndGNameListsByID(GNameLists, GNameListsByID);
        mem.CloseScatterHandle(hScatter);
    }

    static std::string GetName(int ID)
    {


        UINT64 fNamePtr = mem.Read<UINT64>(GameData.GNames + ((int(ID / GameData.Offset["ChunkSize"])) * 8));
        UINT64 fName = mem.Read<UINT64>(fNamePtr + ((int(ID % GameData.Offset["ChunkSize"])) * 8));
        char names_c[258];
        mem.Read(fName + 0x10, names_c, sizeof(names_c));
        std::string names = std::string(names_c);
        if (names == "")
            names = "fail";

        return names;
    }

    static EntityInfo GetInfoByID(int ID)
    {
        EntityInfo entityInfo = Data::GetGNameListsByIDItem(ID);

        if (entityInfo.ID > 0) {
            return entityInfo;
        }

        std::string names = GetName(ID);

        std::unordered_map<std::string, EntityInfo, FnvHash> GNameLists;
        std::unordered_map<int, EntityInfo> GNameListsByID;

        if (names != "fail") {
            EntityInfo GNameItem = Data::GetGNameListsItem(names);

            if (GNameItem.Type != EntityType::Unknown) {
                GNameLists[names] = GNameItem;
                GNameLists[names].ID = ID;
                GNameLists[names].Name = names;
                GNameListsByID[ID] = GNameLists[names];
            }
            else {
                EntityInfo entityInfoData;
                entityInfoData.DisplayName = names;
                entityInfoData.Type = EntityType::Unknown;
                entityInfoData.ID = ID;
                entityInfoData.Name = names;
                GNameLists[names] = entityInfoData;
                GNameListsByID[ID] = entityInfoData;
            }

            Data::SetGNameListsAndGNameListsByID(GNameLists, GNameListsByID);
        }

        return GNameLists[names];
    }

    static std::string GetNameByID(int ID)
    {
        EntityInfo entityInfo = Data::GetGNameListsByIDItem(ID);
        if (entityInfo.ID > 0) {
            return entityInfo.Name;
        }

        auto names = GetName(ID);

        std::unordered_map<std::string, EntityInfo, FnvHash> GNameLists;
        std::unordered_map<int, EntityInfo> GNameListsByID;

        if (names != "fail") {

            EntityInfo GNameItem = Data::GetGNameListsItem(names);

            if (GNameItem.Type != EntityType::Unknown) {
                GNameLists[names] = GNameItem;
                GNameLists[names].ID = ID;
                GNameLists[names].Name = names;
                GNameListsByID[ID] = GNameLists[names];
            }
            else {
                EntityInfo entityInfoData;
                entityInfoData.DisplayName = names;
                entityInfoData.Type = EntityType::Unknown;
                entityInfoData.ID = ID;
                entityInfoData.Name = names;
                GNameLists[names] = entityInfoData;
                GNameListsByID[ID] = entityInfoData;
            }

            Data::SetGNameListsAndGNameListsByID(GNameLists, GNameListsByID);
        }

        return names;
    }

    static uint64_t GetGNamesPtr()
    {
        uint64_t gnames = 0;
        uint64_t tmp = mem.Read<uint64_t>(GameData.GameBase + GameData.Offset["GNames"]);
    
        DWORD64 v11 = Decrypt::Xe(tmp);
        //v11 = mem.Read<uint64_t>(v11);
        //DWORD64 v12 = Decrypt::Xe(v11);
        //v12 = mem.Read<uint64_t>(v12);
        //DWORD64 v13 = Decrypt::Xe(v12);

        gnames = mem.Read<uint64_t>(v11+0x10);
        gnames = Decrypt::Xe(gnames);

        tmp = gnames;
        return gnames;
    }

    static void GetGNameLists()
    {
        auto hScatter = mem.CreateScatterHandle();

        struct GNameInfo {
            uint64_t Offset;
            uint64_t Entity;
            uint64_t pEntity;
            FText FName;
            std::string Name;
            int ID;
        };

        std::vector<GNameInfo> GNameInfos;
        for (int i = 700000; i < 900000; ++i)
        {
            GNameInfo Info;
            Info.Offset = GameData.GNames + ((int(i / GameData.Offset["ChunkSize"])) * 8);
            Info.ID = i;
            GNameInfos.push_back(Info);
        }

        for (GNameInfo& Item : GNameInfos)
        {
            mem.AddScatterRead(hScatter, Item.Offset, (uint64_t*)&Item.Entity);
        }
        mem.ExecuteReadScatter(hScatter);

        for (GNameInfo& Item : GNameInfos)
        {
            mem.AddScatterRead(hScatter, Item.Entity + ((int(Item.ID % GameData.Offset["ChunkSize"])) * 8), (uint64_t*)&Item.pEntity);
        }
        mem.ExecuteReadScatter(hScatter);

        for (GNameInfo& Item : GNameInfos)
        {
            mem.AddScatterRead(hScatter, Item.pEntity + 0x10, (FText*)&Item.FName);
        }
        mem.ExecuteReadScatter(hScatter);

        std::unordered_map<std::string, EntityInfo, FnvHash> GNameLists = Data::GetGNameLists();
        std::unordered_map<int, EntityInfo> GNameListsByID;

        for (GNameInfo& Item : GNameInfos)
        {
            Item.Name = std::string(Item.FName.buffer);
            if (GNameLists.count(Item.Name) > 0)
            {
                GNameLists[Item.Name].ID = Item.ID;
                GNameLists[Item.Name].Name = Item.Name;
                GNameListsByID[Item.ID] = GNameLists[Item.Name];
            }
        }

        Data::SetGNameListsByID(GNameListsByID);
        Data::SetGNameLists(GNameLists);

        mem.CloseScatterHandle(hScatter);
    }
};