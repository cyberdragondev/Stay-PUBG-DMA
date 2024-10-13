#pragma once

#include <unordered_map>
#include <string>
#include "common/Constant.h"
#include <Utils/FNVHash.h>

struct EntityInfo {
    std::string DisplayName = "Unknown";
    EntityType Type = EntityType::Unknown;
    int ID = 0;
    WeaponType WeaponType = WeaponType::Other;
    std::string Name;
};

EntityInfo findEntityInfoByID(int id);
bool hasEntityWithIDZero();
void EntityInit();

extern std::unordered_map<std::string, EntityInfo, FnvHash> EntityLists;