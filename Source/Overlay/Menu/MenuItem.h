#pragma once

#include <DMALibrary/Memory/Memory.h>
#include <Common/Data.h>
#include <Common/Entitys.h>
#include <Utils/Utils.h>
#include <Utils/Throttler.h>
#include <imgui/imgui.h>
#include <Overlay/Texture.h>

inline std::vector<std::string> MenuItemTypes = {
        U8("全部"),
        U8("步枪"),
        U8("连狙"),
        U8("栓狙"),
        U8("散弹"),
        U8("冲锋"),
        U8("机枪"),
        U8("手枪"),
        U8("药品"),
        U8("装备"),
        U8("枪口"),
        U8("握把"),
        U8("弹匣"),
        U8("枪托"),
        U8("瞄具"),
        U8("子弹"),
        U8("投掷"),
        U8("其它")
};

inline std::vector<WeaponType> MenuItemTypeIndexs = {
       WeaponType::AR,
       WeaponType::AR,
       WeaponType::DMR,
       WeaponType::SR,
       WeaponType::SG,
       WeaponType::SMG,
       WeaponType::LMG,
       WeaponType::HG,
       WeaponType::Drug,
       WeaponType::Armor,
       WeaponType::Muzzle,
       WeaponType::Grip,
       WeaponType::Magazine,
       WeaponType::GunButt,
       WeaponType::Sight,
       WeaponType::Bullet,
       WeaponType::Grenade,
       WeaponType::Other
};

inline static int SelectedItem = 0;

