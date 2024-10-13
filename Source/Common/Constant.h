#pragma once

#include <iostream>
#include <map>
#include <utils/utils.h>
#include <Utils/FNVHash.h>

enum class EntityType
{
	Unknown = 0,// 未知
	Player = 1, // 玩家
	AI = 2, //  AI
	DroppedItem, // 掉落物品
	DroppedItemGroup, // 刷新物品
	Item, // 普通物品
	Vehicle, // 汽车
	Drug, // 药物
	Armor, // 防具
	Accessories, // 配件
	Attached, //装备配件
	Weapon, // 手持武器
	AirDrop,// 空投
	DeadBox, // 死亡盒子
	Grenade, // 投掷物品
	Project, // 投掷物品
	Widget,
	Map,
	Other,
	Wheel
};

enum class WeaponType
{
	AR = 0, // 步枪
	DMR = 1, // 连狙
	SR = 2, // 栓狙
	SG = 3, // 散弹枪
	SMG = 4, // 冲锋枪
	LMG = 5, // 机枪
	HG = 6, // 手枪

	Drug = 7, // 药品

	Armor = 8, // 防具

	Muzzle = 9, // 枪口
	Grip = 10, // 握把
	Magazine = 11, //弹匣
	GunButt = 12, // 枪托
	Sight = 13, // 瞄具
	Bullet = 14, // 子弹

	Grenade = 15, // 投掷物

	Other = 16 // 其它
};

inline std::unordered_map<WeaponType, std::string> WeaponTypeToString = {
	{WeaponType::AR, "AR"},
	{WeaponType::DMR, "DMR"},
	{WeaponType::SR, "SR"},
	{WeaponType::SG, "SG"},
	{WeaponType::SMG, "SMG"},
	{WeaponType::LMG, "LMG"},
	{WeaponType::HG, "HG"},
	{WeaponType::Other, "Other"},
};

struct FMapSize
{
	float Size;
	float ImageSize;
};

inline std::unordered_map<std::string, FMapSize, FnvHash> MapsSize = {
	{"Tiger_Main", {408000.f, 816000.f}},
	{"Kiki_Main", {408000.f, 816000.f}},
	{"Desert_Main", {408000.f, 816000.f}},
	{"Range_Main", {101175.f, 204000.f}},
	{"Summerland_Main", {101175.f, 204000.f}},
	{"Italy_Main", {101175.f, 102000.f}},
	{"Baltic_Main", {406387.5f, 816000.f}},
	{"Neon_Main", {408000.f, 816000.f}},
	{"Heaven_Main", {51420.f, 102000.f}},
	{"Savage_Main", {202387.5f, 408000.f}},
	{"DihorOtok_Main", {408000.f, 816000.f}},
	{"Chimera_Main", {152950.f, 306000.f}},
	{ "Erangel_Main", {101175.f, 204000.f}}
};

inline std::unordered_map<std::string, std::string, FnvHash> RankTierToChinese = {
	{"Unranked", U8("未定级")},
	{"Bronze", U8("青铜")},
	{"Silver", U8("白银")},
	{"Gold", U8("黄金")},
	{"Platinum", U8("铂金")},
	{"Diamond", U8("钻石")},
	{"Master", U8("大师")},
	{"-", U8("-")},
};

inline std::unordered_map<std::string, std::string, FnvHash> RankTierToLChinese = {
	{"Unranked", "未定级"},
	{"Bronze", "青铜"},
	{"Silver", "白银"},
	{"Gold", "黄金"},
	{"Platinum", "铂金"},
	{"Diamond", "钻石"},
	{"Master", "大师"},
	{"-", "-"},
};

enum class Scene
{
	FindProcess = 0,
	Lobby = 1,
	Gaming = 2,
};

enum class TextAlignment {
	Left,
	Center,
	Right
};

