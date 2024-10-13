#pragma once
#include <cstdint>
#include "common/Data.h"
#include <nlohmann/json.hpp>
#include <iostream>
#include <string>

namespace Offset
{
	//  世界地址
	// 基址修改开始
	constexpr uint64_t XenuineDecrypt = 0xEBAD428;
	constexpr uint64_t UWorld = 0x10514DE8;
	constexpr uint64_t GNames = 0x10775848;
	constexpr uint64_t CurrentLevel = 0x158;
	constexpr uint64_t Actors = 0x190;
	constexpr uint64_t GameInstance = 0x168;
	constexpr uint64_t LocalPlayer = 0xC8;
	constexpr uint64_t PlayerController = 0x38;
	constexpr uint64_t AcknowledgedPawn = 0x498;
	constexpr uint64_t PlayerCameraManager = 0x4C0;
	constexpr uint64_t PlayerState = 0x410;
	constexpr uint64_t GameState = 0x118;


	//  解密ID
	constexpr uint64_t ObjID = 0x18;
	constexpr uint64_t DecryptNameIndexRor = 0x0;
	constexpr uint64_t DecryptNameIndexXorKey1 = 0xA4D5D5E5;
	constexpr uint64_t DecryptNameIndexRval = 0x5;
	constexpr uint64_t DecryptNameIndexSval = 0x10;
	constexpr uint64_t DecryptNameIndexXorKey2 = 0x7130D5E5;
	constexpr uint64_t ChunkSize = 0x402C;


	constexpr uint64_t ViewTarget = 0x1600;
	constexpr uint64_t CameraCacheLocation = 0xFE8;
	constexpr uint64_t CameraCacheRotation = 0xFD4;
	constexpr uint64_t CameraCacheFOV = 0xFCC;
	constexpr uint64_t LastTeamNum = 0x1390;
	constexpr uint64_t TeamNumber = 0x760;


	constexpr uint64_t SpectatedCount = 0x15B4;
	constexpr uint64_t Position = 0x210;
	constexpr uint64_t CharacterState = 0x165C;
	constexpr uint64_t CharacterName = 0x1040;
	constexpr uint64_t PlayerStatistics = 0x47C;
	constexpr uint64_t TimeTillExplosion = 0x79C;
	constexpr uint64_t DamageDealtOnEnemy = 0x51C;
	constexpr uint64_t bAlwaysCreatePhysicsState = 0x490;


	constexpr uint64_t Eyes = 0x75C;


	//  骨骼
	constexpr uint64_t StaticMesh = 0xAD0;
	constexpr uint64_t ComponentToWorld = 0x200;
	constexpr uint64_t Mesh = 0x5F0;
	constexpr uint64_t ScopingAttachPoint = 0xC90;
	constexpr uint64_t FiringAttachPoint = 0x870;


	constexpr uint64_t SurvivalTier = 0xBA8;
	constexpr uint64_t SurvivalLevel = 0xBAC;
	constexpr uint64_t PartnerLevel = 0x734;


	constexpr uint64_t SafetyZonePosition = 0x6C4;
	constexpr uint64_t SafetyZoneRadius = 0x6C0;
	constexpr uint64_t BlueZoneRadius = 0x620;
	constexpr uint64_t BlueZonePosition = 0x5A4;
	constexpr uint64_t NumAliveTeams = 0x610;
	constexpr uint64_t HeaFlag = 0x31A;
	constexpr uint64_t Health1 = 0xA50;
	constexpr uint64_t Health5 = 0xA45;
	constexpr uint64_t Health3 = 0xA44;
	constexpr uint64_t Health4 = 0xA30;
	constexpr uint64_t Health6 = 0xA40;
	constexpr uint64_t Health2 = 0xA60;
	constexpr uint64_t GroggyHealth = 0x12F0;
	constexpr uint64_t TimeSeconds = 0x9B4;
	constexpr uint64_t PlayerName = 0x428;
	constexpr uint64_t PlayerArray = 0x400;
	constexpr uint64_t AccountId = 0x520;
	constexpr uint64_t PlayerStatusType = 0x438;
	constexpr uint64_t SquadMemberIndex = 0x57C;
	constexpr uint64_t Health_keys0 = 0xCEC7A559;
	constexpr uint64_t Health_keys1 = 0x9B63B2FF;
	constexpr uint64_t Health_keys2 = 0xCA30886A;
	constexpr uint64_t Health_keys3 = 0xFF384852;
	constexpr uint64_t Health_keys4 = 0x30911D0A;
	constexpr uint64_t Health_keys5 = 0x23DDE3B4;
	constexpr uint64_t Health_keys6 = 0x94552C8;
	constexpr uint64_t Health_keys7 = 0x6A6A3E21;
	constexpr uint64_t Health_keys8 = 0xBE37A58;
	constexpr uint64_t Health_keys9 = 0x43EFFF87;
	constexpr uint64_t Health_keys10 = 0xE27588DC;
	constexpr uint64_t Health_keys11 = 0x3B8ADBB0;
	constexpr uint64_t Health_keys12 = 0xBDB0E4D5;
	constexpr uint64_t Health_keys13 = 0xFF935207;
	constexpr uint64_t Health_keys14 = 0x5B099E38;
	constexpr uint64_t Health_keys15 = 0x62622ABA;


	constexpr uint64_t bIsReloading_CP = 0x990;
	constexpr uint64_t bIsScoping_CP = 0xDC6;
	constexpr uint64_t LeanLeftAlpha_CP = 0xEA4;
	constexpr uint64_t LeanRightAlpha_CP = 0xEA8;
	constexpr uint64_t CurrentAmmoData = 0xAA8;




	constexpr uint64_t DroppedItem = 0x448;


	constexpr uint64_t DroppedItemGroup = 0x330;
	constexpr uint64_t ItemPackageItems = 0x580;
	constexpr uint64_t DroppedItemGroupUItem = 0x7E8;
	constexpr uint64_t ItemTable = 0xB0;
	constexpr uint64_t ItemID = 0x268 + 4;
	constexpr uint64_t AimOffsets = 0x1C18;
	constexpr uint64_t WorldToMap = 0x9C4;


	constexpr uint64_t RootComponent = 0x190;
	constexpr uint64_t ComponentLocation = 0x210;
	constexpr uint64_t InputYawScale = 0x63C;
	constexpr uint64_t bShowMouseCursor = 0x648;


	constexpr uint64_t WeaponProcessor = 0x990;
	constexpr uint64_t CurrentWeaponIndex = 0x311;
	constexpr uint64_t EquippedWeapons = 0x208;
	constexpr uint64_t WeaponTrajectoryData = 0x10E0;
	constexpr uint64_t WeaponAttachmentData = 0x140;
	constexpr uint64_t TrajectoryConfig = 0x108;
	constexpr uint64_t TrajectoryGravityZ = 0xFE4;
	constexpr uint64_t BallisticCurve = 0x28;
	constexpr uint64_t FloatCurves = 0x38;
	constexpr uint64_t LastUpdateVelocity = 0x3E0;
	constexpr uint64_t CharacterMovement = 0x190;


	constexpr uint64_t VehicleMovement = 0x460;
	constexpr uint64_t VehicleRiderComponent = 0x21F0;
	constexpr uint64_t LastVehiclePawn = 0x270;
	constexpr uint64_t ReplicatedMovement = 0x70;
	constexpr uint64_t SeatIndex = 0x230;


	constexpr uint64_t Wheels = 0x328;
	constexpr uint64_t WheelLocation = 0x100;
	constexpr uint64_t DampingRate = 0x54;
	constexpr uint64_t ShapeRadius = 0x48;


	constexpr uint64_t AnimScriptInstance = 0xC70;
	constexpr uint64_t PreEvalPawnState = 0x6E0;
	constexpr uint64_t CharacterClanInfo = 0x4C0;
	constexpr uint64_t AttachedItems = 0x818;
	constexpr uint64_t ExplodeState = 0x578;
	constexpr uint64_t ControlRotation_CP = 0x7FC;
	constexpr uint64_t RecoilADSRotation_CP = 0xA9C;
	constexpr uint64_t AntiCheatCharacterSyncManager = 0x7F0;
	constexpr uint64_t AttachedStaticComponentMap = 0x11D0;
	constexpr uint64_t WeaponConfig_WeaponClass = 0x51D;
	constexpr uint64_t ElapsedCookingTime = 0xB8C;
	constexpr uint64_t PlayerInput = 0x538;
	constexpr uint64_t InputAxisProperties = 0x138;
	constexpr uint64_t StaticSockets = 0xC8;
	constexpr uint64_t StaticSocketName = 0x30;
	constexpr uint64_t StaticRelativeScale = 0x50;
	constexpr uint64_t StaticRelativeLocation = 0x38;
	constexpr uint64_t StaticRelativeRotation = 0x44;


	constexpr uint64_t Slot = 0x38;
	constexpr uint64_t MyHUD = 0x4B8;
	constexpr uint64_t Mesh3P = 0x7C0;
	constexpr uint64_t LayoutData = 0x40;
	constexpr uint64_t Alignment = 0x20;
	constexpr uint64_t Keys = 0x60;
	constexpr uint64_t Offsets = 0x0;
	constexpr uint64_t Visibility = 0xA9;
	constexpr uint64_t WidgetStateMap = 0x4F0;
	constexpr uint64_t TrainingMapGrid = 0x6C0;
	constexpr uint64_t BlockInputWidgetList = 0x558;
	constexpr uint64_t SelectMinimapSizeIndex = 0x5B0;

	constexpr uint32_t MouseX = 16301;
	constexpr uint32_t MouseY = 16302;
	//修改结束

	constexpr uint32_t Health = Health4;
	constexpr uint32_t Gender = 0xac0;
	constexpr uint32_t bEncryptedHealth = Health + 0x15;
	constexpr uint32_t EncryptedHealthOffset = Health + 0x14;

	constexpr uint32_t DecryptedHealthOffset = Health + 0x10;


	inline void Init()
	{

		//GameData.Offset["DecryptedHealthOffsets"] = DecryptedHealthOffsets;
		//for (size_t i = 0; i < 16; i++)
		//{
		//	GameData.Offset["DecryptedHealthOffsets" + std::to_string(i)] = DecryptedHealthOffsets[i];
		//}

		GameData.Offset["HeaFlag"] = HeaFlag;
		GameData.Offset["Health1"] = Health1;
		GameData.Offset["Health2"] = Health2;
		GameData.Offset["Health3"] = Health3;
		GameData.Offset["Health4"] = Health4;
		GameData.Offset["Health5"] = Health5;
		GameData.Offset["Health6"] = Health6;
		GameData.Offset["DecryptedHealthOffsets0"] = Health_keys0;
		GameData.Offset["DecryptedHealthOffsets1"] = Health_keys1;
		GameData.Offset["DecryptedHealthOffsets2"] = Health_keys2;
		GameData.Offset["DecryptedHealthOffsets3"] = Health_keys3;
		GameData.Offset["DecryptedHealthOffsets4"] = Health_keys4;
		GameData.Offset["DecryptedHealthOffsets5"] = Health_keys5;
		GameData.Offset["DecryptedHealthOffsets6"] = Health_keys6;
		GameData.Offset["DecryptedHealthOffsets7"] = Health_keys7;
		GameData.Offset["DecryptedHealthOffsets8"] = Health_keys8;
		GameData.Offset["DecryptedHealthOffsets9"] = Health_keys9;
		GameData.Offset["DecryptedHealthOffsets10"] = Health_keys10;
		GameData.Offset["DecryptedHealthOffsets11"] = Health_keys11;
		GameData.Offset["DecryptedHealthOffsets12"] = Health_keys12;
		GameData.Offset["DecryptedHealthOffsets13"] = Health_keys13;
		GameData.Offset["DecryptedHealthOffsets14"] = Health_keys14;
		GameData.Offset["DecryptedHealthOffsets15"] = Health_keys15;


		GameData.Offset["MouseX"] = MouseX;
		GameData.Offset["MouseY"] = MouseY;

		GameData.Offset["bAlwaysCreatePhysicsState"] = bAlwaysCreatePhysicsState;


		GameData.Offset["XenuineDecrypt"] = XenuineDecrypt;
		GameData.Offset["UWorld"] = UWorld;

		GameData.Offset["GNames"] = GNames;
		GameData.Offset["ChunkSize"] = ChunkSize;

		GameData.Offset["DecryptNameIndexRor"] = DecryptNameIndexRor;
		GameData.Offset["DecryptNameIndexXorKey1"] = DecryptNameIndexXorKey1;
		GameData.Offset["DecryptNameIndexXorKey2"] = DecryptNameIndexXorKey2;
		GameData.Offset["DecryptNameIndexRval"] = DecryptNameIndexRval;
		GameData.Offset["DecryptNameIndexSval"] = DecryptNameIndexSval;



		GameData.Offset["ObjID"] = ObjID;
		GameData.Offset["GameInstance"] = GameInstance;
		GameData.Offset["LocalPlayer"] = LocalPlayer;
		GameData.Offset["Actors"] = Actors;
		//GameData.Offset["ActorsForGC"] = ActorsForGC;
		GameData.Offset["ComponentToWorld"] = ComponentToWorld;
		GameData.Offset["ComponentLocation"] = ComponentLocation;

		GameData.Offset["TimeSeconds"] = TimeSeconds;
		GameData.Offset["WorldToMap"] = WorldToMap;
		GameData.Offset["CurrentLevel"] = CurrentLevel;
		GameData.Offset["Mesh"] = Mesh;
		GameData.Offset["CharacterMovement"] = CharacterMovement;
		GameData.Offset["LastUpdateVelocity"] = LastUpdateVelocity;
		GameData.Offset["RootComponent"] = RootComponent;
		GameData.Offset["PlayerController"] = PlayerController;
		GameData.Offset["PlayerInput"] = PlayerInput;
		GameData.Offset["InputYawScale"] = InputYawScale;
		GameData.Offset["bShowMouseCursor"] = bShowMouseCursor;
		GameData.Offset["AcknowledgedPawn"] = AcknowledgedPawn;

		GameData.Offset["MyHUD"] = MyHUD;
		GameData.Offset["InputAxisProperties"] = InputAxisProperties;
		GameData.Offset["AntiCtCharacterSyncManager"] = AntiCheatCharacterSyncManager;
		//GameData.Offset["DormantCharacterClientList"] = DormantCharacterClientList;





		GameData.Offset["GameState"] = GameState;
		GameData.Offset["SafetyZoneRadius"] = SafetyZoneRadius;
		GameData.Offset["SafetyZonePosition"] = SafetyZonePosition;
		GameData.Offset["BlueZoneRadius"] = BlueZoneRadius;
		GameData.Offset["BlueZonePosition"] = BlueZonePosition;
		GameData.Offset["PlayerArray"] = PlayerArray;

		GameData.Offset["PlayerCameraManager"] = PlayerCameraManager;
		GameData.Offset["ViewTarget"] = ViewTarget;
		GameData.Offset["CameraCacheFOV"] = CameraCacheFOV;
		GameData.Offset["CameraCacheRotation"] = CameraCacheRotation;
		GameData.Offset["CameraCacheLocation"] = CameraCacheLocation;
		//GameData.Offset["LastFrameCameraCacheFOV"] = LastFrameCameraCacheFOV;
		//GameData.Offset["LastFrameCameraCacheRotation"] = LastFrameCameraCacheRotation;
		//GameData.Offset["LastFrameCameraCacheLocation"] = LastFrameCameraCacheLocation;

		//GameData.Offset["Gender"] = Gender;





		GameData.Offset["GroggyHealth"] = GroggyHealth;

		GameData.Offset["CharacterName"] = CharacterName;
		GameData.Offset["LastTeamNum"] = LastTeamNum;

		GameData.Offset["SpectatedCount"] = SpectatedCount;
		GameData.Offset["PlayerState"] = PlayerState;
		GameData.Offset["CharacterState"] = CharacterState;





		GameData.Offset["AnimScriptInstance"] = AnimScriptInstance;
		GameData.Offset["PreEvalPawnState"] = PreEvalPawnState;
		GameData.Offset["StaticMesh"] = StaticMesh;
		GameData.Offset["Eyes"] = Eyes;

		GameData.Offset["AimOffsets"] = AimOffsets;



		GameData.Offset["PlayerStatistics"] = PlayerStatistics;
		GameData.Offset["DamageDealtOnEnemy"] = DamageDealtOnEnemy;
		GameData.Offset["PartnerLevel"] = PartnerLevel;
		GameData.Offset["TeamNumber"] = TeamNumber;
		GameData.Offset["PlayerName"] = PlayerName;
		GameData.Offset["PlayerStatusType"] = PlayerStatusType;
		GameData.Offset["SquadMemberIndex"] = SquadMemberIndex;
		GameData.Offset["AccountId"] = AccountId;
		//GameData.Offset["PubgIdData"] = PubgIdData;
		GameData.Offset["SurvivalTier"] = SurvivalTier;
		GameData.Offset["SurvivalLevel"] = SurvivalLevel;


		//GameData.Offset["MedalOne"] = MedalOne;


		GameData.Offset["CharacterClanInfo"] = CharacterClanInfo;





		GameData.Offset["VehicleRiderComponent"] = VehicleRiderComponent;
		GameData.Offset["ReplicatedMovement"] = ReplicatedMovement;
		GameData.Offset["SeatIndex"] = SeatIndex;
		GameData.Offset["LastVehiclePawn"] = LastVehiclePawn;
		GameData.Offset["VehicleMovement"] = VehicleMovement;
		GameData.Offset["Wheels"] = Wheels;
		GameData.Offset["WheelLocation"] = WheelLocation;


		GameData.Offset["DampingRate"] = DampingRate;
		GameData.Offset["ShapeRadius"] = ShapeRadius;

		GameData.Offset["WidgetStateMap"] = WidgetStateMap;
		GameData.Offset["TrainingMapGrid"] = TrainingMapGrid;
		GameData.Offset["LayoutData"] = LayoutData;
		GameData.Offset["Visibility"] = Visibility;
		GameData.Offset["Slot"] = Slot;
		GameData.Offset["Offsets"] = Offsets;
		GameData.Offset["Alignment"] = Alignment;

		GameData.Offset["BlockInputWidgetList"] = BlockInputWidgetList;
		GameData.Offset["SelectMinimapSizeIndex"] = SelectMinimapSizeIndex;

		GameData.Offset["ItemID"] = ItemID;
		GameData.Offset["ItemTable"] = ItemTable;
		GameData.Offset["ItemPackageItems"] = ItemPackageItems;
		GameData.Offset["DroppedItemGroup"] = DroppedItemGroup;

		GameData.Offset["DroppedItem"] = DroppedItem;
		GameData.Offset["DroppedItemGroupUItem"] = DroppedItemGroupUItem;

		GameData.Offset["TimeTillExplosion"] = TimeTillExplosion;


		GameData.Offset["ExplodeState"] = ExplodeState;

		GameData.Offset["WeaponProcessor"] = WeaponProcessor;
		GameData.Offset["CurrentAmmoData"] = CurrentAmmoData;
		GameData.Offset["CurrentWeaponIndex"] = CurrentWeaponIndex;
		GameData.Offset["EquippedWeapons"] = EquippedWeapons;
		GameData.Offset["WeaponTrajectoryData"] = WeaponTrajectoryData;
		GameData.Offset["TrajectoryGravityZ"] = TrajectoryGravityZ;
		GameData.Offset["BallisticCurve"] = BallisticCurve;
		GameData.Offset["FloatCurves"] = FloatCurves;
		GameData.Offset["Keys"] = Keys;

		//GameData.Offset["WeaponConfig"] = WeaponConfig;
		//GameData.Offset["WeaponClass"] = WeaponClass; 
		GameData.Offset["Weapon"] = WeaponConfig_WeaponClass;
		GameData.Offset["Mesh3P"] = Mesh3P;
		GameData.Offset["FiringAttachPoint"] = FiringAttachPoint;
		GameData.Offset["AttachedStaticComponentMap"] = AttachedStaticComponentMap;
		GameData.Offset["AttachedItems"] = AttachedItems;
		GameData.Offset["WeaponAttachmentData"] = WeaponAttachmentData;





		GameData.Offset["ScopingAttachPoint"] = ScopingAttachPoint;
		GameData.Offset["ElapsedCookingTime"] = ElapsedCookingTime;


		GameData.Offset["ControlRotation_CP"] = ControlRotation_CP;
		GameData.Offset["RecoilADSRotation_CP"] = RecoilADSRotation_CP;
		GameData.Offset["LeanLeftAlpha_CP"] = LeanLeftAlpha_CP;
		GameData.Offset["LeanRightAlpha_CP"] = LeanRightAlpha_CP;
		GameData.Offset["bIsScoping_CP"] = bIsScoping_CP;
		GameData.Offset["bIsReloading_CP"] = bIsReloading_CP;

		GameData.Offset["StaticSockets"] = StaticSockets;
		GameData.Offset["StaticSocketName"] = StaticSocketName;
		GameData.Offset["StaticRelativeLocation"] = StaticRelativeLocation;
		GameData.Offset["StaticRelativeRotation"] = StaticRelativeRotation;
		GameData.Offset["StaticRelativeScale"] = StaticRelativeScale;









	}
}