#include "common/Entitys.h"
#include "common/Data.h";
#include <Utils/FNVHash.h>

std::unordered_map<std::string, EntityInfo, FnvHash> EntityPlayerLists = {
    //玩家
    {"PlayerMale_A", {"玩家", EntityType::Player, 0}},
    {"PlayerMale_A_C", {"玩家", EntityType::Player, 0}},
    {"PlayerFemale_A", {"玩家", EntityType::Player, 0}},
    {"PlayerFemale_A_C", {"玩家", EntityType::Player, 0}},
    {"AIPawn_Base_C", {"AI", EntityType::AI, 0}},
    {"AIPawn_Base_Female_C", {"AI", EntityType::AI, 0}},
    {"AIPawn_Base_Male_C", {"AI", EntityType::AI, 0}},
    {"AIPawn_Base_Pillar_C", {"AI", EntityType::AI, 0}},
    {"AIPawn_Base_Female_Pillar_C", {"AI", EntityType::AI, 0}},
    {"AIPawn_Base_Male_Pillar_C", {"AI", EntityType::AI, 0}},
    {"UltAIPawn_Base_C", {"AI", EntityType::AI, 0}},
    {"UltAIPawn_Base_Female_C", {"AI", EntityType::AI, 0}},
    {"UltAIPawn_Base_Male_C", {"AI", EntityType::AI, 0}},
    {"ZDF2_NPC_Runner_C", {"AI", EntityType::AI, 0}},
    {"ZDF2_NPC_Burning_C", {"AI", EntityType::AI, 0}},
    {"ZDF2_NPC_Tanker_C", {"AI", EntityType::AI, 0}},
    {"ZDF2_NPC_Female_C", {"AI", EntityType::AI, 0}},
    {"ZombieNpcNewPawn_Tanker_C", {"AI", EntityType::AI, 0}},
};

std::unordered_map<std::string, EntityInfo, FnvHash> EntityItemLists = {
    //盒子
    {"DeathDropItemPackage_C", {"盒子", EntityType::DeadBox, 0}},
    {"Carapackage_RedBox_C", {"空投", EntityType::AirDrop, 0}},
    {"Carapackage_SmallPackage_C", {"小空投", EntityType::AirDrop, 0}},

    //物品
    {"DroppedItem", {"DroppedItem", EntityType::DroppedItem, 0}},
    {"DroppedItemGroup", {"DroppedItemGroup", EntityType::DroppedItemGroup, 0}},

    //刷新物品
    {"Item_Weapon_Groza_C", {"Groza", EntityType::Item, 0, WeaponType::AR}},
    {"Item_Weapon_BerylM762_C", {"Beryl M762", EntityType::Item, 0, WeaponType::AR}},
    {"Item_Weapon_ACE32_C", {"ACE32", EntityType::Item, 0, WeaponType::AR}},
    {"Item_Weapon_HK416_C", {"M416", EntityType::Item, 0, WeaponType::AR}},
    {"Item_Weapon_Duncans_M416_C", {"M416", EntityType::Item, 0, WeaponType::AR}},
    {"Item_Weapon_AUG_C", {"AUG", EntityType::Item, 0, WeaponType::AR}},
    {"Item_Weapon_AK47_C", {"AKM", EntityType::Item, 0, WeaponType::AR}},
    {"Item_Weapon_Lunchmeats_AK47_C", {"AKM", EntityType::Item, 0, WeaponType::AR}},
    {"Item_Weapon_SCAR-L_C", {"SCAR-L", EntityType::Item, 0, WeaponType::AR}},
    {"Item_Weapon_G36C_C", {"G36C", EntityType::Item, 0, WeaponType::AR}},
    {"Item_Weapon_QBZ95_C", {"QBZ95", EntityType::Item, 0, WeaponType::AR}},
    {"Item_Weapon_K2_C", {"K2", EntityType::Item, 0, WeaponType::AR}},
    {"Item_Weapon_Mk47Mutant_C", {"Mk47", EntityType::Item, 0, WeaponType::AR}},
    {"Item_Weapon_M16A4_C", {"M16A4", EntityType::Item, 0, WeaponType::AR}},

    {"Item_Weapon_MG3_C", {"MG3", EntityType::Item, 0, WeaponType::LMG}},
    {"Item_Weapon_DP28_C", {"DP28", EntityType::Item, 0, WeaponType::LMG}},
    {"Item_Weapon_M249_C", {"M249", EntityType::Item, 0, WeaponType::LMG}},

    {"Item_Weapon_L6_C", {"巴雷特", EntityType::Item, 0, WeaponType::SR}},
    {"Item_Weapon_AWM_C", {"AWM", EntityType::Item, 0, WeaponType::SR}},
    {"Item_Weapon_M24_C", {"M24", EntityType::Item, 0, WeaponType::SR}},
    {"Item_Weapon_Julies_Kar98k_C", {"Kar98k", EntityType::Item, 0, WeaponType::SR}},
    {"Item_Weapon_Kar98k_C", {"Kar98k", EntityType::Item, 0, WeaponType::SR}},
    {"Item_Weapon_Mosin_C", {"莫辛甘纳", EntityType::Item, 0, WeaponType::SR}},
    {"Item_Weapon_Win1894_C", {"Win94", EntityType::Item, 0, WeaponType::SR}},
    {"Item_Weapon_Crossbow_C", {"弩", EntityType::Item, 0, WeaponType::SR}},

    {"Item_Weapon_Mk14_C", {"Mk14", EntityType::Item, 0, WeaponType::DMR}},
    {"Item_Weapon_FNFal_C", {"SLR", EntityType::Item, 0, WeaponType::DMR}},
    {"Item_Weapon_Mk12_C", {"Mk12", EntityType::Item, 0, WeaponType::DMR}},
    {"Item_Weapon_SKS_C", {"SKS", EntityType::Item, 0, WeaponType::DMR}},
    {"Item_Weapon_Mads_QBU88_C", {"QBU", EntityType::Item, 0, WeaponType::DMR}},
    {"Item_Weapon_QBU88_C", {"QBU", EntityType::Item, 0, WeaponType::DMR}},
    {"Item_Weapon_Dragunov_C", {"德拉贡诺夫", EntityType::Item, 0, WeaponType::DMR}},
    {"Item_Weapon_Mini14_C", {"Mini14", EntityType::Item, 0, WeaponType::DMR}},
    {"Item_Weapon_VSS_C", {"VSS", EntityType::Item, 0, WeaponType::DMR}},

    {"Item_Weapon_OriginS12_C", {"O12", EntityType::Item, 0, WeaponType::SG}},
    {"Item_Weapon_DP12_C", {"DBS", EntityType::Item, 0, WeaponType::SG}},
    {"Item_Weapon_Saiga12_C", {"S12K", EntityType::Item, 0, WeaponType::SG}},
    {"Item_Weapon_Winchester_C", {"S1897", EntityType::Item, 0, WeaponType::SG}},
    {"Item_Weapon_Berreta686_C", {"S686", EntityType::Item, 0, WeaponType::SG}},
    {"Item_Weapon_Sawnoff_C", {"锯齿短喷", EntityType::Weapon, 0, WeaponType::SG}},

    {"Item_Weapon_P90_C", {"P90", EntityType::Item, 0, WeaponType::SMG}},
    {"Item_Weapon_Vector_C", {"Vector", EntityType::Item, 0, WeaponType::SMG}},
    {"Item_Weapon_UZI_C", {"UZI", EntityType::Item, 0, WeaponType::SMG}},
    {"Item_Weapon_UMP_C", {"UMP", EntityType::Item, 0, WeaponType::SMG}},
    {"Item_Weapon_Thompson_C", {"汤姆逊", EntityType::Item, 0, WeaponType::SMG}},
    {"Item_Weapon_BizonPP19_C", {"野牛PP19", EntityType::Item, 0, WeaponType::SMG}},
    {"Item_Weapon_JS9_C", {"JS9", EntityType::Item, 0, WeaponType::SMG}},
    {"Item_Weapon_MP5K_C", {"MP5K", EntityType::Item, 0, WeaponType::SMG}},

    {"Item_Weapon_G18_C", {"P18C", EntityType::Item, 0, WeaponType::HG}},
    {"Item_Weapon_StunGun_C", {"电击枪", EntityType::Item, 0, WeaponType::HG}},
    {"Item_Weapon_M1911_C", {"P1911", EntityType::Item, 0, WeaponType::HG}},
    {"Item_Weapon_M9_C", {"P92", EntityType::Item, 0, WeaponType::HG}},
    {"Item_Weapon_NagantM1895_C", {"R1895", EntityType::Item, 0, WeaponType::HG}},
    {"Item_Weapon_Rhino_C", {"R45", EntityType::Item, 0, WeaponType::HG}},
    {"Item_Weapon_DesertEagle_C", {"沙漠之鹰", EntityType::Item, 0, WeaponType::HG}},
    {"Item_Weapon_vz61Skorpion_C", {"蝎式手枪", EntityType::Item, 0, WeaponType::HG}},

    //药品
    {"Item_Heal_MedKit_C", {"医疗箱", EntityType::Item, 0, WeaponType::Drug}},
    {"Item_Heal_FirstAid_C", {"急救包", EntityType::Item, 0, WeaponType::Drug}},
    {"Item_Heal_Bandage_C", {"绷带", EntityType::Item, 0, WeaponType::Drug}},
    {"Item_Weapon_TraumaBag_C", {"医疗套件", EntityType::Item, 0, WeaponType::Drug}},
    {"Item_Weapon_TacPack_C", {"医疗套件", EntityType::Item, 0, WeaponType::Drug}},

    {"Item_Boost_AdrenalineSyringe_C", {"肾上腺激素", EntityType::Item, 0, WeaponType::Drug}},
    {"Item_Boost_EnergyDrink_C", {"能量饮料", EntityType::Item, 0, WeaponType::Drug}},
    {"Item_Boost_PainKiller_C", {"止疼药", EntityType::Item, 0, WeaponType::Drug}},

    //装备
    {"Item_Head_E_01_Lv1_C", {"头盔Lv1", EntityType::Item, 0, WeaponType::Armor}},
    {"Item_Head_E_02_Lv1_C", {"头盔Lv1", EntityType::Item, 0, WeaponType::Armor}},
    {"Item_Head_F_01_Lv2_C", {"头盔Lv2", EntityType::Item, 0, WeaponType::Armor}},
    {"Item_Head_F_02_Lv2_C", {"头盔Lv2", EntityType::Item, 0, WeaponType::Armor}},
    {"Item_Head_G_01_Lv3_C", {"头盔Lv3", EntityType::Item, 0, WeaponType::Armor}},

    {"Item_Armor_E_01_Lv1_C", {"防弹衣Lv1", EntityType::Item, 0, WeaponType::Armor}},
    {"Item_Armor_D_01_Lv2_C", {"防弹衣Lv2", EntityType::Item, 0, WeaponType::Armor}},
    {"Item_Armor_C_01_Lv3_C", {"防弹衣Lv3", EntityType::Item, 0, WeaponType::Armor}},

    {"Item_Back_BlueBlocker", {"电波干扰背包", EntityType::Item, 0, WeaponType::Armor}},
    {"Item_Back_E_02_Lv1_C", {"背包Lv1", EntityType::Item, 0, WeaponType::Armor}},
    {"Item_Back_E_01_Lv1_C", {"背包Lv1", EntityType::Item, 0, WeaponType::Armor}},
    {"Item_Back_F_02_Lv2_C", {"背包Lv2", EntityType::Item, 0, WeaponType::Armor}},
    {"Item_Back_F_01_Lv2_C", {"背包Lv2", EntityType::Item, 0, WeaponType::Armor}},
    {"Item_Back_C_02_Lv3_C", {"背包Lv3", EntityType::Item, 0, WeaponType::Armor}},
    {"Item_Back_C_01_Lv3_C", {"背包Lv3", EntityType::Item, 0, WeaponType::Armor}},
    {"Item_Back_B_08_Lv3_C", {"背包Lv3", EntityType::Item, 0, WeaponType::Armor}},

    {"Item_Ghillie_01_C", {"吉利服", EntityType::Item, 0, WeaponType::Armor}},
    {"Item_Ghillie_02_C", {"吉利服", EntityType::Item, 0, WeaponType::Armor}},
    {"Item_Ghillie_03_C", {"吉利服", EntityType::Item, 0, WeaponType::Armor}},
    {"Item_Ghillie_04_C", {"吉利服", EntityType::Item, 0, WeaponType::Armor}},
    {"Item_Ghillie_05_C", {"吉利服", EntityType::Item, 0, WeaponType::Armor}},
    {"Item_Ghillie_06_C", {"吉利服", EntityType::Item, 0, WeaponType::Armor}},
    {"Item_Back_B_08_Lv3_C", {"吉利服", EntityType::Item, 0, WeaponType::Armor}},


    //枪口
    { "Item_Attach_Weapon_Muzzle_Compensator_Large_C", {"补偿器 (步枪)", EntityType::Item, 0, WeaponType::Muzzle} },
    { "Item_Attach_Weapon_Muzzle_FlashHider_Large_C", {"消焰器 (步枪)", EntityType::Item, 0, WeaponType::Muzzle} },
    { "Item_Attach_Weapon_Muzzle_Suppressor_Large_C", {"消音器 (步枪/连狙)", EntityType::Item, 0, WeaponType::Muzzle} },

    { "Item_Attach_Weapon_Muzzle_Compensator_SniperRifle_C", {"补偿器 (狙击枪)", EntityType::Item, 0, WeaponType::Muzzle} },
    { "Item_Attach_Weapon_Muzzle_FlashHider_SniperRifle_C", {"消焰器 (狙击枪)", EntityType::Item, 0, WeaponType::Muzzle} },
    { "Item_Attach_Weapon_Muzzle_Suppressor_SniperRifle_C", {"消音器 (狙击枪)", EntityType::Item, 0, WeaponType::Muzzle} },

    { "Item_Attach_Weapon_Muzzle_Compensator_Medium_C", {"补偿器 (冲锋枪)", EntityType::Item, 0, WeaponType::Muzzle} },
    { "Item_Attach_Weapon_Muzzle_FlashHider_Medium_C", {"消焰器 (冲锋枪)", EntityType::Item, 0, WeaponType::Muzzle} },
    { "Item_Attach_Weapon_Muzzle_Suppressor_Medium_C", {"消音器 (冲锋枪)", EntityType::Item, 0, WeaponType::Muzzle} },

    { "Item_Attach_Weapon_Muzzle_Suppressor_Small_C", {"消音器 (手枪)", EntityType::Item, 0, WeaponType::Muzzle} },


    //瞄具
    { "Item_Attach_Weapon_Upper_DotSight_01_C", {"红点", EntityType::Item, 0, WeaponType::Sight} },
    { "Item_Attach_Weapon_Upper_Holosight_C", {"全息", EntityType::Item, 0, WeaponType::Sight} },
    { "Item_Attach_Weapon_Upper_Aimpoint_C", {"2倍镜", EntityType::Item, 0, WeaponType::Sight} },
    { "Item_Attach_Weapon_Upper_Scope3x_C", {"3倍镜", EntityType::Item, 0, WeaponType::Sight} },
    { "Item_Attach_Weapon_Upper_ACOG_01_C", {"4倍镜", EntityType::Item, 0, WeaponType::Sight} },
    { "Item_Attach_Weapon_Upper_Scope6x_C", {"6倍镜", EntityType::Item, 0, WeaponType::Sight} },
    { "Item_Attach_Weapon_Upper_CQBSS_C", {"8倍镜", EntityType::Item, 0, WeaponType::Sight} },
    { "Item_Attach_Weapon_Upper_PM2_01_C", {"15倍镜", EntityType::Item, 0, WeaponType::Sight} },
    { "Item_Attach_Weapon_Upper_PM2_01_C", {"15倍镜", EntityType::Item, 0, WeaponType::Sight} },
    { "Item_Attach_Weapon_Upper_Thermal4X_C", {"热成像瞄准镜", EntityType::Item, 0, WeaponType::Sight} },

    //枪托
    { "Item_Attach_Weapon_Stock_AR_Composite_C", {"战术枪托", EntityType::Item, 0, WeaponType::GunButt} },
    { "Item_Attach_Weapon_Stock_AR_HeavyStock_C", {"重型枪托", EntityType::Item, 0, WeaponType::GunButt} },
    { "Item_Attach_Weapon_Stock_SniperRifle_CheekPad_C", {"托腮板", EntityType::Item, 0, WeaponType::GunButt} },
    { "Item_Attach_Weapon_Stock_SniperRifle_BulletLoops_C", {"子弹带", EntityType::Item, 0, WeaponType::GunButt} },

    //握把
    {"Item_Attach_Weapon_Lower_Foregrip_C", {"垂直握把", EntityType::Item, 0, WeaponType::Grip}},
    { "Item_Attach_Weapon_Lower_AngledForeGrip_C", {"三角握把", EntityType::Item, 0, WeaponType::Grip} },
    { "Item_Attach_Weapon_Lower_HalfGrip_C", {"半截握把", EntityType::Item, 0, WeaponType::Grip} },
    { "Item_Attach_Weapon_Lower_LightweightForeGrip_C", {"轻型握把", EntityType::Item, 0, WeaponType::Grip} },
    { "Item_Attach_Weapon_Lower_ThumbGrip_C", {"拇指握把", EntityType::Item, 0, WeaponType::Grip} },

    //弹匣
    {"Item_Attach_Weapon_Magazine_ExtendedQuickDraw_Large_C", {"快速扩容弹匣 (步枪)", EntityType::Item, 0, WeaponType::Magazine}},
    {"Item_Attach_Weapon_Magazine_Extended_Large_C", {"扩容弹匣 (步枪)", EntityType::Item, 0, WeaponType::Magazine}},
    { "Item_Attach_Weapon_Magazine_QuickDraw_Large_C", {"快速换弹 (步枪)", EntityType::Item, 0, WeaponType::Magazine} },

    { "Item_Attach_Weapon_Magazine_ExtendedQuickDraw_SniperRifle_C", {"快速扩容弹匣 (狙击枪)", EntityType::Item, 0, WeaponType::Magazine} },
    { "Item_Attach_Weapon_Magazine_Extended_SniperRifle_C", {"扩容弹匣 (狙击枪)", EntityType::Item, 0, WeaponType::Magazine} },
    { "Item_Attach_Weapon_Magazine_QuickDraw_SniperRifle_C", {"快速换弹 (狙击枪)", EntityType::Item, 0, WeaponType::Magazine} },

    { "Item_Attach_Weapon_Magazine_ExtendedQuickDraw_Medium_C", {"快速扩容弹匣 (冲锋枪)", EntityType::Item, 0, WeaponType::Magazine} },
    { "Item_Attach_Weapon_Magazine_Extended_Medium_C", {"扩容弹匣 (冲锋枪)", EntityType::Item, 0, WeaponType::Magazine} },
    { "Item_Attach_Weapon_Magazine_QuickDraw_Medium_C", {"快速换弹 (冲锋枪)", EntityType::Item, 0, WeaponType::Magazine} },

    { "Item_Attach_Weapon_Magazine_ExtendedQuickDraw_Small_C", {"快速扩容弹匣 (手枪)", EntityType::Item, 0, WeaponType::Magazine} },
    { "Item_Attach_Weapon_Magazine_Extended_Small_C", {"扩容弹匣 (手枪)", EntityType::Item, 0, WeaponType::Magazine} },
    { "Item_Attach_Weapon_Magazine_QuickDraw_Small_C", {"快速换弹 (手枪)", EntityType::Item, 0, WeaponType::Magazine} },


    //子弹
    { "Item_Ammo_Mortar_C", {"60mm", EntityType::Item, 0, WeaponType::Bullet} },
    { "Item_Ammo_Bolt_C", {"箭", EntityType::Item, 0, WeaponType::Bullet} },
    { "Item_Ammo_Flare_C", {"信号弹", EntityType::Item, 0, WeaponType::Bullet} },
    { "Item_Ammo_57mm_C", {"5.7mm", EntityType::Item, 0, WeaponType::Bullet} },
    { "Item_Ammo_300Magnum_C", {".300马格南", EntityType::Item, 0, WeaponType::Bullet} },
    { "Item_Ammo_556mm_C", {"5.56mm", EntityType::Item, 0, WeaponType::Bullet} },
    { "Item_Ammo_762mm_C", {"7.62mm", EntityType::Item, 0, WeaponType::Bullet} },
    { "Item_Ammo_40mm_C", {"40mm", EntityType::Item, 0, WeaponType::Bullet} },
    { "Item_Ammo_9mm_C", {"9mm", EntityType::Item, 0, WeaponType::Bullet} },
    { "Item_Ammo_12Guage_C", {"12口径", EntityType::Item, 0, WeaponType::Bullet} },
    { "Item_Ammo_45ACP_C", {".45", EntityType::Item, 0, WeaponType::Bullet} },

    //投掷物
    { "Item_Weapon_C4_C", {"C4", EntityType::Item, 0, WeaponType::Grenade} },
    { "Item_Weapon_BluezoneGrenade_C", {"蓝圈手雷", EntityType::Item, 0, WeaponType::Grenade} },
    { "Item_Weapon_BZGrenade_C", {"蓝圈手雷", EntityType::Item, 0, WeaponType::Grenade} },
    { "Item_Weapon_Grenade_C", {"手雷", EntityType::Item, 0, WeaponType::Grenade} },
    { "Item_Weapon_Grenade_Warmode_C", {"手雷", EntityType::Item, 0, WeaponType::Grenade} },
    { "Item_Weapon_FlashBang_C", {"闪光弹", EntityType::Item, 0, WeaponType::Grenade} },
    { "Item_Weapon_StickyGrenade_C", {"粘性炸弹", EntityType::Item, 0, WeaponType::Grenade} },
    { "Item_Weapon_Molotov_C", {"燃烧瓶", EntityType::Item, 0, WeaponType::Grenade} },
    { "Item_Weapon_SmokeBomb_C", {"烟雾弹", EntityType::Item, 0, WeaponType::Grenade} },
    { "Item_Weapon_SpikeTrap_C", {"尖刺陷阱", EntityType::Item, 0, WeaponType::Grenade} },
    { "Item_Weapon_DecoyGrenade_C", {"诱饵手雷", EntityType::Item, 0, WeaponType::Grenade} },

    //其它
    { "Item_Weapon_Pan_C", { "平底锅", EntityType::Item, 0, WeaponType::Other } },
    { "Item_Weapon_Mortar_C", {"迫击炮", EntityType::Item, 0, WeaponType::Other} },
    { "Item_Weapon_FlareGun_C", {"信号枪", EntityType::Item, 0, WeaponType::Other} },
    { "Item_Weapon_M79_C", {"M79", EntityType::Item, 0, WeaponType::Other} },
    { "Item_Weapon_PanzerFaust100M_C", {"火箭筒", EntityType::Item, 0, WeaponType::Other} },

    { "Item_Heaven_Key_C", {"钥匙", EntityType::Item, 0, WeaponType::Other} },
    { "Item_Chimera_Key_C", {"钥匙", EntityType::Item, 0, WeaponType::Other} },
    { "Item_Tiger_Key_C", {"钥匙", EntityType::Item, 0, WeaponType::Other} },

    { "Item_JerryCan_C", {"汽油桶", EntityType::Item, 0, WeaponType::Other} },
    { "Item_EmergencyPickup_C", {"紧急呼救器", EntityType::Item, 0, WeaponType::Other} },
    { "Item_Weapon_BlueChipDetector_C", {"蓝色精片", EntityType::Item, 0, WeaponType::Other} },
    { "Item_BulletproofShield_C", {"折叠盾", EntityType::Item, 0, WeaponType::Other} },
    { "InstantRevivalKit_C", {"自救器", EntityType::Item, 0, WeaponType::Other} },
    { "Item_Tiger_SelfRevive_C", {"自救器", EntityType::Item, 0, WeaponType::Other} },
    { "Item_Mountainbike_C", {"折叠自行车", EntityType::Item, 0, WeaponType::Other} },
    { "Item_Weapon_Drone_C", {"无人机", EntityType::Item, 0, WeaponType::Other} },

    { "Vehicle_Repair_Kit_C", {"车辆修理包", EntityType::Item, 0, WeaponType::Other} },
    { "Helmet_Repair_Kit_C", {"头盔修理包", EntityType::Item, 0, WeaponType::Other} },
    { "Armor_Repair_Kit_C", {"防具修理包", EntityType::Item, 0, WeaponType::Other} },

    { "Item_Weapon_Spotter_Scope_C", {"望远镜", EntityType::Item, 0, WeaponType::Other} },
    { "Item_Weapon_TacPack_C", {"战术背包", EntityType::Item, 0, WeaponType::Other} },
};

std::unordered_map<std::string, EntityInfo, FnvHash> EntityWeaponLists = {
    //武器
    {"WeapFlashBang_C", {"闪光弹", EntityType::Weapon, 0}},
    {"WeapBluezoneGrenade_C", {"篮圈手雷", EntityType::Weapon, 0}},
    {"WeapGrenade_C", {"手雷", EntityType::Weapon, 0}},
    {"WeapStickyGrenade_C", {"粘性炸弹", EntityType::Weapon, 0}},
    {"WeapC4_C", {"C4", EntityType::Weapon, 0}},
    {"WeapMolotov_C", {"燃烧瓶", EntityType::Weapon, 0}},
    {"WeapSmokeBomb_C", {"烟雾弹", EntityType::Weapon, 0}},
    {"WeapC4_C", {"C4", EntityType::Weapon, 0}},
    {"WeapDecoyGrenade_C", {"诱饵手雷", EntityType::Weapon, 0}},
    {"WeapBluezoneGrenade_C", {"毒圈手雷", EntityType::Weapon, 0}},
    {"WeapSpikeTrap_C", {"尖刺陷阱", EntityType::Weapon, 0}},

    // Melee
    {"WeapCowbar_C", {"撬棍", EntityType::Weapon, 0}},
    {"WeapPan_C", {"平底锅", EntityType::Weapon, 0}},
    {"WeapSickle_C", {"镰刀", EntityType::Weapon, 0}},
    {"WeapMachete_C", {"砍刀", EntityType::Weapon, 0}},
    {"WeapCowbarProjectile_C", {"撬棍", EntityType::Weapon, 0}},
    {"WeapMacheteProjectile_C", {"Machete", EntityType::Weapon, 0}},
    {"WeapPanProjectile_C", {"平底锅", EntityType::Weapon, 0}},
    {"WeapSickleProjectile_C", {"镰刀", EntityType::Weapon, 0}},

    // AR
    {"WeapLunchmeatsAK47_C", {"AKM", EntityType::Weapon, 0, WeaponType::AR}},
    {"WeapAK47_C", {"AKM", EntityType::Weapon, 0, WeaponType::AR}},
    {"WeapGroza_C", {"Groza", EntityType::Weapon, 0, WeaponType::AR}},
    {"WeapDuncansHK416_C", {"M416", EntityType::Weapon, 0, WeaponType::AR}},
    {"WeapHK416_C", {"M416", EntityType::Weapon, 0, WeaponType::AR}},
    {"WeapM16A4_C", {"M16A4", EntityType::Weapon, 0, WeaponType::AR}},
    {"WeapSCAR-L_C", {"SCAR-L", EntityType::Weapon, 0, WeaponType::AR}},
    {"WeapACE32_C", {"ACE", EntityType::Weapon, 0, WeaponType::AR}},
    {"WeapAUG_C", {"AUG", EntityType::Weapon, 0, WeaponType::AR}},
    {"WeapBerylM762_C", {"BerylM762", EntityType::Weapon, 0, WeaponType::AR}},
    {"WeapG36C_C", {"G36C", EntityType::Weapon, 0, WeaponType::AR}},
    {"WeapQBZ95_C", {"QBZ95", EntityType::Weapon, 0, WeaponType::AR}},
    {"WeapK2_C", {"K2", EntityType::Weapon, 0, WeaponType::AR}},
    {"WeapMk47Mutant_C", {"Mk47", EntityType::Weapon, 0, WeaponType::AR}},

    // SR
    {"WeapAWM_C", {"AWM", EntityType::Weapon, 0, WeaponType::SR}},
    {"WeapJuliesM24_C", {"M24", EntityType::Weapon, 0, WeaponType::SR}},
    {"WeapM24_C", {"M24", EntityType::Weapon, 0, WeaponType::SR}},
    {"WeapJuliesKar98k_C", {"Kar98k", EntityType::Weapon, 0, WeaponType::SR}},
    {"WeapKar98k_C", {"Kar98k", EntityType::Weapon, 0, WeaponType::SR}},
    {"WeapWin94_C", {"Win94", EntityType::Weapon, 0, WeaponType::SR}},
    {"WeapL6_C", {"Lynx", EntityType::Weapon, 0, WeaponType::SR}},
    {"WeapMosinNagant_C", {"莫辛甘纳", EntityType::Weapon, 0, WeaponType::SR}},
    {"WeapCrossbow_1_C", {"弩", EntityType::Weapon, 0, WeaponType::SR}},

    // SG
    {"Weapon_OriginS12_C", {"O12", EntityType::Weapon, 0, WeaponType::SG}},
    {"WeapBerreta686_C", {"S686", EntityType::Weapon, 0, WeaponType::SG}},
    {"WeapSaiga12_C", {"S12K", EntityType::Weapon, 0, WeaponType::SG}},
    {"WeapWinchester_C", {"S1897", EntityType::Weapon, 0, WeaponType::SG}},
    {"WeapDP12_C", {"DBS", EntityType::Weapon, 0, WeaponType::SG}},
    {"WeapSawnoff_C", {"锯齿短喷", EntityType::Weapon, 0, WeaponType::SG}},

    // PISTOL
    {"WeapG18_C", {"P18C", EntityType::Weapon, 0, WeaponType::HG}},
    {"WeapM1911_C", {"P1911", EntityType::Weapon, 0, WeaponType::HG}},
    {"WeapM9_C", {"P92", EntityType::Weapon, 0, WeaponType::HG}},
    {"WeapNagantM1895_C", {"R1895", EntityType::Weapon, 0, WeaponType::HG}},
    {"WeapRhino_C", {"R45", EntityType::Weapon, 0, WeaponType::HG}},
    {"WeapDesertEagle_C", {"沙漠之鹰", EntityType::Weapon, 0, WeaponType::HG}},
    {"Weapvz61Skorpion_C", {"蝎式手枪", EntityType::Weapon, 0, WeaponType::HG}},
    {"WeapStunGun_C", {"电击枪", EntityType::Weapon, 0, WeaponType::HG}},

    // LMG
    {"WeapM249_C", {"M249", EntityType::Weapon, 0, WeaponType::LMG}},
    {"WeapMG3_C", {"MG3", EntityType::Weapon, 0, WeaponType::LMG}},
    {"WeapDP28_C", {"DP28", EntityType::Weapon, 0, WeaponType::LMG}},

    // DMR
    {"WeapDragunov_C", {"德拉贡诺夫", EntityType::Weapon, 0, WeaponType::DMR}},
    {"WeapMini14_C", {"Mini14", EntityType::Weapon, 0, WeaponType::DMR}},
    {"WeapMk14_C", {"Mk14", EntityType::Weapon, 0, WeaponType::DMR}},
    {"WeapSKS_C", {"SKS", EntityType::Weapon, 0, WeaponType::DMR}},
    {"WeapFNFal_C", {"SLR", EntityType::Weapon, 0, WeaponType::DMR}},
    {"WeapMadsFNFal_C", {"SLR", EntityType::Weapon, 0, WeaponType::DMR}},
    {"WeapMadsQBU88_C", {"QBU", EntityType::Weapon, 0, WeaponType::DMR}},
    {"WeapQBU88_C", {"QBU", EntityType::Weapon, 0, WeaponType::DMR}},
    {"WeapMk12_C", {"Mk12", EntityType::Weapon, 0, WeaponType::DMR}},
    {"WeapVSS_C", {"VSS", EntityType::Weapon, 0, WeaponType::DMR}},

    // SMG
    {"WeapThompson_C", {"汤姆逊", EntityType::Weapon, 0, WeaponType::SMG}},
    {"WeapUMP_C", {"UMP", EntityType::Weapon, 0, WeaponType::SMG}},
    {"WeapUZI_C", {"UZI", EntityType::Weapon, 0, WeaponType::SMG}},
    {"WeapUziPro_C", {"UZI", EntityType::Weapon, 0, WeaponType::SMG}},
    {"WeapVector_C", {"Vector", EntityType::Weapon, 0, WeaponType::SMG}},
    {"WeapBizonPP19_C", {"野牛PP19", EntityType::Weapon, 0, WeaponType::SMG}},
    {"WeapMP5K_C", {"MP5K", EntityType::Weapon, 0, WeaponType::SMG}},
    {"WeapP90_C", {"P90", EntityType::Weapon, 0, WeaponType::SMG}},
    {"WeapJS9_C", {"JS9", EntityType::Weapon, 0, WeaponType::SMG}},
    {"WeapMP9_C", {"MP9", EntityType::Weapon, 0, WeaponType::SMG}},

    // Special
    {"WeapMortar_C", {"Mortar", EntityType::Weapon, 0}},
    {"WeapFlareGun_C", {"信号枪", EntityType::Weapon, 0}},
    {"WeapPanzerFaust100M1_C", {"火箭筒", EntityType::Weapon, 0}},
    {"WeapJerryCan_C", {"汽油桶", EntityType::Weapon, 0}},
    {"WeapDrone_C", {"无人机", EntityType::Weapon, 0}},
    {"WeapTraumaBag_C", {"医疗套件", EntityType::Weapon, 0}},
    {"WeapSpotterScope_C", {"望远镜", EntityType::Weapon, 0}},
    {"WeapTacPack_C", {"战术背包", EntityType::Weapon, 0}},
    {"WeapM79_C", {"M79", EntityType::Weapon, 0}},
};

std::unordered_map<std::string, EntityInfo, FnvHash> EntityVehicleLists = {
    //车辆
    {"BP_EmPickup_Aircraft_C", {"直升机", EntityType::Vehicle, 0}},
    {"BP_EmergencyPickupVehicle_C", {"紧急呼救器", EntityType::Vehicle, 0}},
    {"TransportAircraft_Chimera_C", {"飞机", EntityType::Vehicle, 0}},
    {"BP_Bicycle_C", {"自行车", EntityType::Vehicle, 0}},
    {"BP_BRDM_C", {"装甲车", EntityType::Vehicle, 0}},
    {"Uaz_Armored_C", {"吉普", EntityType::Vehicle, 0}},
    {"BP_Mirado_Open_05_C", {"皮卡", EntityType::Vehicle, 0}},
    {"BP_Motorglider_C", {"滑翔机", EntityType::Vehicle, 0}},
    {"BP_Motorglider_Blue_C", {"滑翔机", EntityType::Vehicle, 0}},
    {"BP_Motorglider_Green_C", {"滑翔机", EntityType::Vehicle, 0}},
    {"BP_Motorglider_Orange_C", {"滑翔机", EntityType::Vehicle, 0}},
    {"BP_Motorglider_Red_C", {"滑翔机", EntityType::Vehicle, 0}},
    {"BP_Motorglider_Teal_C", {"滑翔机", EntityType::Vehicle, 0}},
    {"BP_LootTruck_C", {"物资车", EntityType::Vehicle, 0}},
    {"AquaRail_A_01_C", {"摩托艇", EntityType::Vehicle, 0}},
    {"AquaRail_A_02_C", {"摩托艇", EntityType::Vehicle, 0}},
    {"AquaRail_A_03_C", {"摩托艇", EntityType::Vehicle, 0}},
    {"Boat_PG117_C", {"快艇", EntityType::Vehicle, 0}},
    {"PG117_A_01_C", {"快艇", EntityType::Vehicle, 0}},
    {"AirBoat_V2_C", {"汽艇", EntityType::Vehicle, 0}},
    {"BP_M_Rony_A_01_C", {"皮卡车", EntityType::Vehicle, 0}},
    {"BP_M_Rony_A_02_C", {"皮卡车", EntityType::Vehicle, 0}},
    {"BP_M_Rony_A_03_C", {"皮卡车", EntityType::Vehicle, 0}},
    {"BP_Mirado_C", {"跑车", EntityType::Vehicle, 0}},
    {"BP_Mirado_A_01_C", {"跑车", EntityType::Vehicle, 0}},
    {"BP_Mirado_A_02_C", {"跑车", EntityType::Vehicle, 0}},
    {"BP_Mirado_A_03_C", {"跑车", EntityType::Vehicle, 0}},
    {"BP_Mirado_A_03_Esports_C", {"跑车", EntityType::Vehicle, 0}},
    {"BP_Mirado_A_04_C", {"跑车", EntityType::Vehicle, 0}},
    {"BP_Mirado_Open_C", {"超跑", EntityType::Vehicle, 0}},
    {"BP_Mirado_Open_01_C", {"超跑", EntityType::Vehicle, 0}},
    {"BP_Mirado_Open_02_C", {"超跑", EntityType::Vehicle, 0}},
    {"BP_Mirado_Open_03_C", {"超跑", EntityType::Vehicle, 0}},
    {"BP_Mirado_Open_04_C", {"超跑", EntityType::Vehicle, 0}},
    {"BP_Motorbike_04_C", {"摩托车", EntityType::Vehicle, 0}},
    {"BP_Motorbike_04_Desert_C", {"摩托车", EntityType::Vehicle, 0}},
    {"BP_Motorbike_Solitario_C", {"摩托车", EntityType::Vehicle, 0}},
    {"BP_Motorbike_04_SideCar_C", {"摩托车", EntityType::Vehicle, 0}},
    {"BP_Motorbike_04_SideCar_Desert_C", {"摩托车", EntityType::Vehicle, 0}},
    {"BP_Niva_01_C", {"雪地吉普", EntityType::Vehicle, 0}},
    {"BP_Niva_02_C", {"雪地吉普", EntityType::Vehicle, 0}},
    {"BP_Niva_03_C", {"雪地吉普", EntityType::Vehicle, 0}},
    {"BP_Niva_04_C", {"雪地吉普", EntityType::Vehicle, 0}},
    {"BP_Niva_05_C", {"雪地吉普", EntityType::Vehicle, 0}},
    {"BP_Niva_06_C", {"雪地吉普", EntityType::Vehicle, 0}},
    {"BP_Niva_07_C", {"雪地吉普", EntityType::Vehicle, 0}},
    {"BP_Niva_Esports_C", {"雪地吉普", EntityType::Vehicle, 0}},
    {"BP_PickupTruck_A_01_C", {"皮卡", EntityType::Vehicle, 0}},
    {"BP_PickupTruck_A_02_C", {"皮卡", EntityType::Vehicle, 0}},
    {"BP_PickupTruck_A_03_C", {"皮卡", EntityType::Vehicle, 0}},
    {"BP_PickupTruck_A_04_C", {"皮卡", EntityType::Vehicle, 0}},
    {"BP_PickupTruck_A_05_C", {"皮卡", EntityType::Vehicle, 0}},
    {"BP_PickupTruck_A_esports_C", {"皮卡", EntityType::Vehicle, 0}},
    {"BP_PickupTruck_B_01_C", {"皮卡", EntityType::Vehicle, 0}},
    {"BP_PickupTruck_B_02_C", {"皮卡", EntityType::Vehicle, 0}},
    {"BP_PickupTruck_B_03_C", {"皮卡", EntityType::Vehicle, 0}},
    {"BP_PickupTruck_B_04_C", {"皮卡", EntityType::Vehicle, 0}},
    {"BP_PickupTruck_B_05_C", {"皮卡", EntityType::Vehicle, 0}},
    {"BP_TukTukTuk_A_01_C", {"摩托车", EntityType::Vehicle, 0}},
    {"BP_TukTukTuk_A_02_C", {"摩托车", EntityType::Vehicle, 0}},
    {"BP_TukTukTuk_A_03_C", {"摩托车", EntityType::Vehicle, 0}},
    {"BP_Van_A_01_C", {"公交车", EntityType::Vehicle, 0}},
    {"BP_Van_A_02_C", {"公交车", EntityType::Vehicle, 0}},
    {"BP_Van_A_03_C", {"公交车", EntityType::Vehicle, 0}},
    {"BP_MiniBus_C", {"公交车", EntityType::Vehicle, 0}},
    {"BP_Scooter_01_A_C", {"踏板车", EntityType::Vehicle, 0}},
    {"BP_Scooter_02_A_C", {"踏板车", EntityType::Vehicle, 0}},
    {"BP_Scooter_03_A_C", {"踏板车", EntityType::Vehicle, 0}},
    {"BP_Scooter_04_A_C", {"踏板车", EntityType::Vehicle, 0}},
    {"BP_Snowbike_01_C", {"雪地摩托", EntityType::Vehicle, 0}},
    {"BP_Snowbike_02_C", {"雪地摩托", EntityType::Vehicle, 0}},
    {"BP_Snowmobile_01_C", {"雪地摩托", EntityType::Vehicle, 0}},
    {"BP_Snowmobile_02_C", {"雪地摩托", EntityType::Vehicle, 0}},
    {"BP_Snowmobile_03_C", {"雪地摩托", EntityType::Vehicle, 0}},
    {"Buggy_A_01_C", {"沙地车", EntityType::Vehicle, 0}},
    {"Buggy_A_02_C", {"沙地车", EntityType::Vehicle, 0}},
    {"Buggy_A_03_C", {"沙地车", EntityType::Vehicle, 0}},
    {"Buggy_A_04_C", {"沙地车", EntityType::Vehicle, 0}},
    {"Buggy_A_05_C", {"沙地车", EntityType::Vehicle, 0}},
    {"Buggy_A_06_C", {"沙地车", EntityType::Vehicle, 0}},
    {"Dacia_A_01_v2_C", {"汽车", EntityType::Vehicle, 0}},
    {"Dacia_A_01_v2_snow_C", {"汽车", EntityType::Vehicle, 0}},
    {"Dacia_A_02_v2_C", {"汽车", EntityType::Vehicle, 0}},
    {"Dacia_A_03_v2_C", {"汽车", EntityType::Vehicle, 0}},
    {"Dacia_A_03_v2_Esports_C", {"汽车", EntityType::Vehicle, 0}},
    {"Dacia_A_04_v2_C", {"汽车", EntityType::Vehicle, 0}},
    {"Uaz_A_01_C", {"吉普", EntityType::Vehicle, 0}},
    {"Uaz_B_01_C", {"吉普", EntityType::Vehicle, 0}},
    {"Uaz_B_01_esports_C", {"吉普", EntityType::Vehicle, 0}},
    {"Uaz_C_01_C", {"吉普", EntityType::Vehicle, 0}},
    {"BP_Dirtbike_C", {"越野摩托", EntityType::Vehicle, 0}},
    {"BP_CoupeRB_C", {"双人跑车", EntityType::Vehicle, 0}},
    {"BP_ATV_C", {"全地形摩托车", EntityType::Vehicle, 0}},
    {"BP_PonyCoupe_C", {"跑车", EntityType::Vehicle, 0}},
    {"BP_Porter_C", {"货车", EntityType::Vehicle, 0}},
    {"BP_Pillar_Car_C", {"警车", EntityType::Vehicle, 0}},
    {"BP_Food_Truck_C", {"食品运输车", EntityType::Vehicle, 0}},
    {"BP_Blanc_C", {"BLANC", EntityType::Vehicle, 0}},
    {"BP_McLarenGT_C", {"迈凯伦", EntityType::Vehicle, 0}},
    { "ABP_McLarenGT_C", {"迈凯伦", EntityType::Vehicle, 0} },
    { "BP_McLarenGT_Lx_Yellow_C", {"迈凯伦", EntityType::Vehicle, 0} },
    { "BP_McLarenGT_St_black_C", {"迈凯伦", EntityType::Vehicle, 0} },
    { "BP_McLarenGT_St_white_C", {"迈凯伦", EntityType::Vehicle, 0} },
    { "BP_DBX_LGD_C", {"阿斯顿SUV", EntityType::Vehicle, 0} },
    { "BP_Vantage_EP_C", {"阿斯顿轿跑", EntityType::Vehicle, 0} },
    { "BP_Vantage_LGD_C", {"阿斯顿敞篷", EntityType::Vehicle, 0} },
    { "BP_PicoBus_C", {"电动巴士", EntityType::Vehicle, 0} },
};

std::unordered_map<std::string, EntityInfo, FnvHash> EntityProjectLists = {
    //投掷物
    {"ProjGrenade_C", {"手雷", EntityType::Project, 0}},
    {"ProjBluezoneGrenade_C", {"篮圈手雷", EntityType::Project, 0}},
    {"ProjBZGrenade_C", {"篮圈手雷", EntityType::Project, 0}},
    {"ProjFlashBang_C", {"闪光弹", EntityType::Project, 0}},
    {"ProjMolotov_C", {"燃烧瓶", EntityType::Project, 0}},
};

std::unordered_map<std::string, EntityInfo, FnvHash> EntityOtherLists = {
    {"ScopeAimCamera", {"ScopeAimCamera", EntityType::Other, 0} },
    {"MouseX", {"MouseX", EntityType::Other, 0} },
    {"MouseY", {"MouseY", EntityType::Other, 0} },
};

std::unordered_map<std::string, EntityInfo, FnvHash> EntityLists = {
};

void EntityInit()
{
    EntityLists.clear();
    EntityLists.insert(EntityOtherLists.begin(), EntityOtherLists.end());
    EntityLists.insert(EntityPlayerLists.begin(), EntityPlayerLists.end());
    EntityLists.insert(EntityWeaponLists.begin(), EntityWeaponLists.end());
    EntityLists.insert(EntityItemLists.begin(), EntityItemLists.end());
    EntityLists.insert(EntityVehicleLists.begin(), EntityVehicleLists.end());
    EntityLists.insert(EntityProjectLists.begin(), EntityProjectLists.end());
}
