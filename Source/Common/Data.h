#pragma once

#include <windows.h>
#include <iostream>
#include <unordered_map>
#include <shared_mutex>
#include <array>
#include <cmath>
#include <Common/Constant.h>
#include <Common/Entitys.h>
#include <Common/Bone.h>
#include <DMALibrary/Memory/Memory.h>
#include <nlohmann/json.hpp>
#include <Common/Entitys.h>
#include <Utils/Engine.h>
#include <Utils/ue4math/rotator.h>
#include <Utils/ue4math/transform.h>
#include <Common/VectorHelper.h>
#include <imgui/imgui.h>
#include <deque>
#include <Utils/FNVHash.h>

struct FRichCurveKeyArray
{
	uintptr_t Data;
	int32_t Count;
};

class USkeletalMeshSocket
{
public:
	uint64_t pSocket;
	struct FName SocketName; // 0x28(0x08)
	struct FName BoneName; // 0x30(0x08)
	struct FVector RelativeLocation; // 0x38(0x0c)
	struct FRotator RelativeRotation; // 0x44(0x0c)
	struct FVector RelativeScale; // 0x50(0x0c)
};

class WeaponData
{
public:
	uint64_t SkeletalMesh;
	uint64_t Skeleton;
	TArray<uint64_t> SkeletalSockets;
	std::vector<USkeletalMeshSocket> SkeletalMeshSockets;
	uint64_t FiringAttachPointSocketBone;

	FRichCurve FloatCurves;
	std::vector<FRichCurveKey> RichCurveKeys;
	char TrajectoryConfig[0x60];
	bool IsInitialized;
	float TrajectoryGravityZ = -9.8f;
	uint64_t Mesh3P;
	FName FiringAttachPoint;
	FName ScopingAttachPoint;
	FRichCurveKeyArray RichCurveKeyArray;
	FTransform ComponentToWorld;
	uint64_t StaticMesh;
	FWeaponTrajectoryConfig TrajectoryConfigs;

	bool ScopeSocket = false;
	uint64_t ScopeAimCameraSocket;
	uint64_t ScopeStaticMeshComponent;

	template<typename T>
	T GetTrajectoryConfig(uint32_t Offset)
	{
		return *(T*)(this->TrajectoryConfig + Offset);
	}
};

struct GNameInfo {
	int ID;
	std::string Name;
	uint64_t pGName;
	uint64_t pName;
	FText FName;
};

struct GTakeHitInfo {
	float ActualDamage;
	struct FName AttackerWeaponName;
	struct FVector AttackerLocation;
};

struct ActorEntityInfo {
	uint64_t Entity;
	int Index;
	int ID;
	int DecodeID;
	EntityInfo EntityInfo;
};

inline static const std::vector<int> BoneIndex = {
		EBoneIndex::ForeHead,
		EBoneIndex::Head,
		EBoneIndex::Neck_01,
		EBoneIndex::Spine_03,
		EBoneIndex::Pelvis,
		EBoneIndex::Upperarm_L,
		EBoneIndex::Lowerarm_L,
		EBoneIndex::Upperarm_R,
		EBoneIndex::Lowerarm_R,
		EBoneIndex::Hand_L,
		EBoneIndex::Hand_R,
		EBoneIndex::Thigh_L,
		EBoneIndex::Calf_L,
		EBoneIndex::Thigh_R,
		EBoneIndex::Calf_R,
		EBoneIndex::Foot_L,
		EBoneIndex::Foot_R,
};

struct VehicleWheelInfo {
	uint64_t Vehicle;
	uint64_t pWheel;
	uint64_t Wheel;
	uint64_t Mesh;
	FVector Location;
	FVector2D ScreenLocation;
	float Health;
	float DampingRate;
	float ShapeRadius;
	FVector OldLocation;
	FVector Velocity;
	WheelState State;
	float Distance;
	FTransform ComponentToWorld;
};

struct VehicleInfo {
	EntityType Type;
	uint64_t Entity;
	int ObjID;
	std::string Name;
	uint64_t RootComponent;
	uint64_t VehicleMovement;
	uint64_t pWheels;
	int WheelsCount;
	int FlatTireCount;
	std::vector<VehicleWheelInfo> Wheels;
	FVector Location;
	FVector2D ScreenLocation;
	float Distance;
};

struct DroppedItemInfo {
	EntityType Type;
	uint64_t Entity;
	int ID;
	uint64_t pDroppedItem;
	uint64_t RootComponent;
	uint64_t ItemTable;
	FVector Location;
	FVector ScreenLocation;
	float Distance;
};

struct ItemInfo {
	EntityType Type;
	WeaponType ItemType;
	uint64_t Entity;
	uint64_t IsEntity;
	uint64_t RootComponent;
	int ID;
	std::string Name;
	std::string DisplayName;
	uint64_t ItemTable;
	FVector Location;
	FVector2D ScreenLocation;
	float Distance;
	bool bHidden = false;
};

struct DroppedItemGroupItemInfo {
	uint64_t pItemGroupComponent;
	uint64_t ItemGroupComponent;
	uint64_t ItemGroupUItem;
	uint64_t ItemTable;
	int ItemID;
};

struct DroppedItemGroupInfo {
	EntityType Type;
	uint64_t Entity;
	int ID;
	uint64_t pDroppedItemGroup;
	int Count;
	std::vector<DroppedItemGroupItemInfo> Items;
};

struct ProjectInfo {
	EntityType Type;
	uint64_t Entity;
	uint64_t pEntity;
	float Time;
	int ID;
	std::string Name;
	std::string EntityName;
	uint64_t RootComponent;
	uint64_t MeshComponent;
	BYTE bVisible = 0;
	FVector Location;
	FVector2D ScreenLocation;
	float Distance;
	float TimeTillExplosion;
	float PostImpactExplosionTimer;
	FVector LastImpactVelocity;
	EProjectileExplodeState ExplodeState;
};

struct Player
{
	EntityType Type;
	int ObjID;
	int Sex = 0;
	uint64_t Entity;
	uint64_t IsMe = false;
	uint64_t IsMyTeam = false;
	bool InScreen = true;
	bool InFog = false;
	uint64_t RootComponent;
	uint64_t CharacterMovement;
	uint64_t MeshComponent;
	uint64_t AnimScriptInstance;
	uint64_t StaticMesh;
	BYTE bVisible = 1;
	UCHAR bAlwaysCreatePhysicsState = 0x1;
	uint64_t BoneMatrix;
	uint64_t BoneArray;
	FTransform ComponentToWorld;
	uint64_t SquadComponent;
	uint64_t AimComponent;
	uint64_t RecoilManager;
	FVector Location;
	CharacterState State;
	int Eyes = 0;
	float Health;
	float Distance;
	float GroggyHealth;
	int KillCount;
	int SurvivalTier;
	int SurvivalLevel;
	EGender Gender;
	BYTE bEncryptedHealth;
	unsigned char EncryptedHealthOffset;
	unsigned char DecryptedHealthOffset;
	EPartnerLevel PartnerLevel;
	float DamageDealtOnEnemy;
	int SpectatedCount = 0;
	int ListType = 0;
	int SquadMemberIndex = 0;
	std::string ClanName;

	GTakeHitInfo TakeHitInfo;
	ECharacterIconType RadarState;

	float LastSubmitTime;
	float LastRenderTime;
	float LastRenderTimeOnScreen;
	bool IsVisible;
	bool IsAimMe = false;
	int TeamID = -100;

	FVector Velocity;
	FRotator AimOffsets;
	uint64_t pCharacterName;
	ECharacterState CharacterState;
	FText CharacterName;
	uint64_t PlayerState;
	uint64_t WeaponProcessor;
	uint64_t EquippedWeapons;
	BYTE CurrentWeaponIndex;
	uint64_t CurrentWeapon;
	uint64_t EncryptWeaponID;
	int WeaponID;
	float ElapsedCookingTime;
	bool IsScoping;
	std::string WeaponName;
	EntityInfo WeaponEntityInfo;
	EAnimPawnState PreEvalPawnState;
	EWeaponClass WeaponClass;

	std::string AccountId;

	std::string Name;
	struct {
		std::unordered_map<int, FTransform> Bones = {
			{EBoneIndex::Root, FTransform()},
			{EBoneIndex::ForeHead, FTransform()},
			{EBoneIndex::Head, FTransform()},
			{EBoneIndex::Neck_01, FTransform()},
			{EBoneIndex::Upperarm_R, FTransform()},
			{EBoneIndex::Lowerarm_R, FTransform()},
			{EBoneIndex::Hand_R, FTransform()},
			{EBoneIndex::Upperarm_L, FTransform()},
			{EBoneIndex::Lowerarm_L, FTransform()},
			{EBoneIndex::Hand_L, FTransform()},
			{EBoneIndex::Spine_01, FTransform()},
			{EBoneIndex::Spine_03, FTransform()},
			{EBoneIndex::Pelvis, FTransform()},
			{EBoneIndex::Thigh_R, FTransform()},
			{EBoneIndex::Calf_R, FTransform()},
			{EBoneIndex::Foot_R, FTransform()},
			{EBoneIndex::Thigh_L, FTransform()},
			{EBoneIndex::Calf_L, FTransform()},
			{EBoneIndex::Foot_L, FTransform()},
		};
		std::unordered_map<int, FVector> LocationBones = {
			{EBoneIndex::Root, FVector()},
			{EBoneIndex::ForeHead, FVector()},
			{EBoneIndex::Head, FVector()},
			{EBoneIndex::Neck_01, FVector()},
			{EBoneIndex::Upperarm_R, FVector()},
			{EBoneIndex::Lowerarm_R, FVector()},
			{EBoneIndex::Hand_R, FVector()},
			{EBoneIndex::Upperarm_L, FVector()},
			{EBoneIndex::Lowerarm_L, FVector()},
			{EBoneIndex::Hand_L, FVector()},
			{EBoneIndex::Spine_01, FVector()},
			{EBoneIndex::Spine_03, FVector()},
			{EBoneIndex::Pelvis, FVector()},
			{EBoneIndex::Thigh_R, FVector()},
			{EBoneIndex::Calf_R, FVector()},
			{EBoneIndex::Foot_R, FVector()},
			{EBoneIndex::Thigh_L, FVector()},
			{EBoneIndex::Calf_L, FVector()},
			{EBoneIndex::Foot_L, FVector()},
		};
		std::unordered_map<int, FVector2D> ScreenBones = {
			{EBoneIndex::Root, FVector2D()},
			{EBoneIndex::ForeHead, FVector2D()},
			{EBoneIndex::Head, FVector2D()},
			{EBoneIndex::Neck_01, FVector2D()},
			{EBoneIndex::Upperarm_R, FVector2D()},
			{EBoneIndex::Lowerarm_R, FVector2D()},
			{EBoneIndex::Hand_R, FVector2D()},
			{EBoneIndex::Upperarm_L, FVector2D()},
			{EBoneIndex::Lowerarm_L, FVector2D()},
			{EBoneIndex::Hand_L, FVector2D()},
			{EBoneIndex::Spine_01, FVector2D()},
			{EBoneIndex::Spine_03, FVector2D()},
			{EBoneIndex::Pelvis, FVector2D()},
			{EBoneIndex::Thigh_R, FVector2D()},
			{EBoneIndex::Calf_R, FVector2D()},
			{EBoneIndex::Foot_R, FVector2D()},
			{EBoneIndex::Thigh_L, FVector2D()},
			{EBoneIndex::Calf_L, FVector2D()},
			{EBoneIndex::Foot_L, FVector2D()},
		};
	} Skeleton;
};

struct AimBotConfig
{
	bool VisibleCheck = false;
	bool AutoSwitch = true;
	bool NoBulletNotAim = false;
	bool HotkeyMerge = true;
	bool AimWheel = true;
	bool NoRecoil = true;
	bool OriginalRecoil = false;
	bool Prediction = true;
	bool DynamicFov = true;
	int InitialValue = 360;
	int FOV = 40;
	int WheelFOV = 60;
	int SwitchingDelay = 0;
	int AimDistance = 800;
	float XSpeed = 0.5f;
	float YSpeed = 0.5f;
	float AimWheelSpeed = 0.8f;
	int RecoilTime = 3;
	int FPS = 500;
	float AimSpeedMaxFactor = 0.2f;
	bool IgnoreGroggy = false;
	bool LineTraceSingle = false;
	int AimWheelBone = 3;

	int PredictionMode = 0;

	struct
	{
		int Key = VK_RBUTTON;
		bool Bones[17] = {
			true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false
		};
	} First;

	struct
	{
		int Key = VK_SHIFT;
		bool Bones[17] = {
			true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false
		};
	} Second;

	struct
	{
		int Key = 17;
		bool Bones[17] = {
			true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false
		};
	} Groggy;

	struct
	{
		int Key = 20;
	} Wheel;

};

struct ItemDetail
{
	std::string Name;
	std::string DisplayName;
	WeaponType Type;
	int Group = 0;
};

struct AimBotWeaponConfig
{
	int Key;
	std::unordered_map<std::string, AimBotConfig> Weapon;
};

struct CameraData
{
	FVector Location;
	FRotator Rotation;
	float FOV;
};

struct PlayerRankInfo {
	bool Updated;
	std::string Tier = "-";
	std::string SubTier = "";
	int RankPoint = 0;
	float AvgRank = 0;
	float WinRatio = 0;
	float KDA = 0;
	std::string KDAToString = "0.00";
	std::string WinRatioToString = "0.00%";
	std::string TierToString = "-";
	std::string RankPointToString = "-";
};

struct PlayerRankList {
	bool Updated = false;
	std::string AccountId;
	struct PlayerRankInfo FPP;
	struct PlayerRankInfo SquadFPP;
	struct PlayerRankInfo TPP;
	struct PlayerRankInfo SquadTPP;
};

struct GamePlayerInfo {
	uint64_t pPlayerInfo;
	uint64_t pTeam;
	uint64_t pCharacter;
	uint64_t pPlayerName;
	uint64_t pSavedNetworkAddress;
	FText FPlayerName;
	FText FSavedNetworkAddress;
	std::string PlayerName;
	uint64_t pAccountId;
	FText FAccountId;
	FText FNameplateId;
	std::string AccountId;
	int TeamID = 0;
	int SquadMemberIndex = 0;
	bool IsMyTeam = false;
	bool IsSelf = false;
	int PlayerId = 0;
	EPartnerLevel PartnerLevel;
	int KillCount;
	float DamageDealtOnEnemy;
	int StatusType = 8; // 8 = 存活 | 11 = 死亡 || 12 = 人机
	uint64_t pPubgIdData;
	FWuPubgIdData PubgIdData;
	FWuCharacterClanInfo CharacterClanInfo;
	FTslPlayerStatisticsForOwner PlayerStatisticsForOwner;
	uint64_t pClanName;
	FText FClanName;
	std::string ClanName;
	int ListType = 0; // 0 = 默认 | 1 = 黑名单 | 2 = 白名单
};

struct tMapInfo {
	float TimeStamp = 0.0f;

	struct {
		struct PosInfo {
			float Time = 0;
			FVector Pos;
		};
		std::deque<PosInfo> Info;
	} PosInfo;
};

struct FogPlayerInfo
{
	FVector Location;
};

struct PackageItem {
	uint64_t pItem;
	uint64_t Item;
	uint64_t ItemTable;
	int ItemID;
	std::string Name;
	std::string DisplayName;
	EntityType Type;
	WeaponType ItemType;
};

struct PackageInfo {
	EntityType Type;
	uint64_t Entity;
	int ID;
	uint64_t pDroppedItemGroup;
	uint64_t DroppedItemGroup;

	uint64_t pItemArray;

	int ItemCount;

	FVector Location;
	FVector2D ScreenLocation;
	float Distance;

	std::vector<PackageItem> Items;
};

struct FGameData
{
	std::string Version = "1.0.9.7";
	nlohmann::json LGKey;

	int FogPlayerCount = 0;

	int ThreadSleep = 2000;
	bool IsLogin = false;
	c_keys Keyboard;
	DWORD PID = 0;
	uint64_t GameBase = 0;
	bool VirtualProtect = false;
	uint64_t HookBase = 0;
	uint64_t GameSize = 0;
	Scene PreviousScene = Scene::FindProcess;
	Scene Scene = Scene::FindProcess;
	std::string MapName;

	uint64_t UWorld;
	uint64_t GNames;
	uint64_t GameState;
	bool BucksackStatus;
	uint64_t GameInstance;
	uint64_t LocalPlayer;
	uint64_t PlayerController;
	bool bShowMouseCursor;
	uint64_t AcknowledgedPawn;
	uint64_t PlayerInput;
	uint64_t LocalPlayerPawn;
	uint64_t PlayerCameraManager;
	uint64_t CameraViewTarget;
	int LocalPlayerTeamID;
	uint64_t CameraRootComponent;
	FRotator ControlRotation;
	uint64_t MyHUD;
	uint64_t CurrentLevel;
	uint64_t ActorArray;
	uint64_t ActorArrayEmpty;
	uint64_t AntiCheatCharacterSyncManager;
	uint64_t pMatrix;
	BYTE Matrix[64];
	float MatrixVp[4][4];
	D3DMATRIX ViewMatrix;
	int MyTeamID;
	int ActorCount;
	uint64_t Actor;
	Player LocalPlayerInfo;
	float WorldTimeSeconds = 0.f;
	float DeltaSeconds = 0.f;
	float FPS = 0.f;
	bool LineTraceSingle = false;

	CameraData Camera;

	std::unordered_map<std::string, uint64_t, FnvHash> Offset;
	std::unordered_map<std::string, EntityInfo, FnvHash> DefaultEntityLists;
	std::unordered_map<std::string, EntityInfo, FnvHash> GNameLists;
	std::unordered_map<int, EntityInfo> GNameListsByID;

	struct
	{
		FVector WorldOriginLocation;
		float ImageMapSize = 204000.f;
		float ImageMapHeight = 8192.f;

		FMapSize MapSize;
		uint64_t MapGrid;
		uint64_t MapWidget;
		uint64_t MiniMapWidget;
		uint64_t Slot;
		bool Visibility;
		FMargin Layout;
		FVector2D Alignment;
		FVector2D Position;
		float ZoomFactor;
		FVector2D WorldCenterLocation;
		float MapSizeFactored;
		FVector SafetyZonePosition;
		float SafetyZoneRadius;
		FVector BlueZonePosition;
		float BlueZoneRadius;
		int SelectMinimapSizeIndex;
		float VehicleSpeed;
		float MiniRadarDistance;
		bool bRadarExtended;
		FVector2D MiniRadarSizeLarge;
		FVector2D MiniRadarFromLarge;
		FVector2D MiniRadarSizeNormal;
		FVector2D MiniRadarFromNormal;
		bool MiniRadarVisibility;
	} Radar;

	struct {
		uint64_t Target;
		EntityType Type = EntityType::Player;
		bool Lock;
		float ScreenDistance = 1000.f;
		int Bone;
		Player TargetPlayerInfo;
		FVector PredictedPos;
	} AimBot;

	mutable std::shared_mutex EnemyInfoMapMutex;
	std::unordered_map<uint64_t, tMapInfo> EnemyInfoMap;

	struct
	{
		mutable std::shared_mutex GNameListsMutex;

		mutable std::shared_mutex CacheEntitysMutex;
		std::unordered_map<uint64_t, ActorEntityInfo> CacheEntitys;

		mutable std::shared_mutex CachePlayersMutex;
		std::unordered_map<uint64_t, Player> CachePlayers;

		mutable std::shared_mutex PlayersDataMutex;
		std::unordered_map<uint64_t, Player> PlayersData;

		mutable std::shared_mutex PlayersMutex;
		std::unordered_map<uint64_t, Player> Players;

		mutable std::shared_mutex CacheVehiclesMutex;
		std::unordered_map<uint64_t, VehicleInfo> CacheVehicles;

		mutable std::shared_mutex VehiclesMutex;
		std::unordered_map<uint64_t, VehicleInfo> Vehicles;

		mutable std::shared_mutex VehicleWheelsMutex;
		std::unordered_map<uint64_t, VehicleWheelInfo> VehicleWheels;

		mutable std::shared_mutex CacheDroppedItemsMutex;
		std::unordered_map<uint64_t, DroppedItemInfo> CacheDroppedItems;

		mutable std::shared_mutex CacheDroppedItemGroupsMutex;
		std::unordered_map<uint64_t, DroppedItemGroupInfo> CacheDroppedItemGroups;

		mutable std::shared_mutex ItemsMutex;
		std::unordered_map<uint64_t, ItemInfo> Items;

		mutable std::shared_mutex CacheProjectsMutex;
		std::unordered_map<uint64_t, ProjectInfo> CacheProjects; 
		
		mutable std::shared_mutex ProjectsMutex;
		std::unordered_map<uint64_t, ProjectInfo> Projects;

		mutable std::shared_mutex FogPlayersMutex;
		std::unordered_map<uint64_t, FogPlayerInfo> FogPlayers;

		mutable std::shared_mutex CachePackagesMutex;
		std::unordered_map<uint64_t, PackageInfo> CachePackages;

		mutable std::shared_mutex PackagesMutex;
		std::unordered_map<uint64_t, PackageInfo> Packages;
	} Actors;

	struct
	{
		struct
		{
			bool Enable = true;
			bool FusionMode = false;
			bool UseLastFrameCameraCache = false;
			bool UseThread = false;
			int MonitorCurrentIdx = 0;
			int ScreenWidth = 1728;// 1728;
			int ScreenHeight = 1080;// 1028;
			int ScreenX = 0;
			int ScreenY = 0;
			bool ShowFPS = true;
			bool VSync = true;
			HWND hWnd = NULL;
			FVector2D SettingSize = {};
			FVector2D SettingPos = {};
			FVector2D AuthSize = {};
			FVector2D AuthPos = {};
			bool Click = false;
		} Overlay;

		struct
		{
			bool Enable = true;
			int Mode = 0;
			int ConfigIndex = 0;
			int Controller = 0;
			int COM = 0;
			int Delay = 0;
			char IP[256] = "192.168.2.188";
			char Port[256] = "";
			char UUID[256] = "";
			bool Connected = false;
			bool ShowFOV = false;
			float FOVColor[4] = { 255.0f, 255.0f, 255.0f, 1.0f };
			bool ShowWheelFOV = false;
			float WheelFOVColor[4] = { 184.f / 255.f, 134.f / 255.f, 11.f / 255.f, 1.0f };
			bool ShowPoint = false;
			int PointSize = 2;
			float PointColor[4] = { 255 / 255.f, 0.f / 255.f, 0.f / 255.f, 1.0f };

			std::unordered_map<int, AimBotWeaponConfig> Configs = {
				{0, {VK_F2, {
					{"AR", AimBotConfig()},
					{"DMR", AimBotConfig()},
					{"SR", AimBotConfig()},
					{"HG", AimBotConfig()},
					{"LMG", AimBotConfig()},
					{"SG", AimBotConfig()},
					{"SMG", AimBotConfig()}
				}}},
				{1, {VK_F3, {
					{"AR", AimBotConfig()},
					{"DMR", AimBotConfig()},
					{"SR", AimBotConfig()},
					{"HG", AimBotConfig()},
					{"LMG", AimBotConfig()},
					{"SG", AimBotConfig()},
					{"SMG", AimBotConfig()}
				}}},
			};
		} AimBot;

		struct
		{
			int ClearKey = VK_F9;
		} Function;

		struct
		{
			bool Enable = true;
			bool Stroke = true;
			int DistanceStyle = 1;
			int HealthBarStyle = 0;
			bool VisibleCheck = true;
			bool AimExpandInfo = true;
			bool DynamicHealthColor = true;
			bool TargetedRay = true;
			bool VisibleCheckRay = false;
			bool LockedHiddenBones = false;

			int RankMode = 0;
			char RankSize[256] = "30";
			std::string RankModeUrl = "";
			bool Tier = true;
			bool RankPoint = true;
			bool KDA = true;

			bool ShowInfos[17] = {
				true, false, true, true, true, false, true, true, false, true, true, false, false, false, true, false, false
			};
			int DistanceMax = 1000;
			int SkeletonWidth = 1;
			int FontSize = 14;
			int WeaponDistanceMax = 100;
			int InfoDistanceMax = 100;
			int RayWidth = 2;
			int FocusModeKey = 192;
			bool FocusMode = false;

			struct
			{
				struct
				{
					float Line[4] = { 225.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f, 255.0f / 255.0f };
				} Ray;

				struct
				{
					float Info[4] = { 225.0f / 255.0f, 225.0f / 255.0f, 225.0f / 255.0f, 255.0f / 255.0f };
					float Skeleton[4] = { 225.0f / 255.0f, 225.0f / 255.0f, 225.0f / 255.0f, 255.0f / 255.0f };
				} Default;

				struct
				{
					float Info[4] = { 168.0f / 255.0f, 255.0f / 255.0f, 130.0f / 255.0f, 255.0f / 255.0f };
					float Skeleton[4] = { 168.0f / 255.0f, 255.0f / 255.0f, 130.0f / 255.0f, 255.0f / 255.0f };
				} Partner;

				struct
				{
					float Info[4] = { 255.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f, 255.0f / 255.0f };
					float Skeleton[4] = { 255.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f, 255.0f / 255.0f };
				} Groggy;

				struct
				{
					float Info[4] = { 197.0f / 255.0f, 132.0f / 255.0f, 253.0f / 255.0f, 255.0f / 255.0f };
					float Skeleton[4] = { 197.0f / 255.0f, 132.0f / 255.0f, 253.0f / 255.0f, 255.0f / 255.0f };
				} Dangerous;

				struct
				{
					float Info[4] = { 247.0f / 255.0f, 101.0f / 255.0f, 101.0f / 255.0f, 255.0f / 255.0f };
					float Skeleton[4] = { 247.0f / 255.0f, 101.0f / 255.0f, 101.0f / 255.0f, 255.0f / 255.0f };
				} Blacklist;

				struct
				{
					float Info[4] = { 79.0f / 255.0f, 120.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f };
					float Skeleton[4] = { 79.0f / 255.0f, 120.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f };
				} Whitelist;

				struct
				{
					float Info[4] = { 218.0f / 255.0f, 101.0f / 255.0f, 167.0f / 255.0f, 255.0f / 255.0f };
					float Skeleton[4] = { 218.0f / 255.0f, 101.0f / 255.0f, 167.0f / 255.0f, 255.0f / 255.0f };
				} AI;

				struct
				{
					float Info[4] = { 184.f / 255.0f, 255.0f / 255.0f, 249.0f / 255.0f, 255.0f / 255.0f };
					float Skeleton[4] = { 184.f / 255.0f, 255.0f / 255.0f, 249.0f / 255.0f, 255.0f / 255.0f };
				} Visible;
			} Color;
		} ESP;

		struct
		{
			bool Enable = true;
			int EnableKey = VK_F1;
			int GroupKey = VK_F1;
			int DistanceMax = 50;
			int FontSize = 13;
			bool Combination = false;
			bool ShowIcon = true;
			bool ShowDistance = true;
			bool AccessoriesFilter = true;
			int ThresholdX = 80;
			int ThresholdY = 15;
			int GroupAKey = VK_NUMPAD0;
			int GroupBKey = VK_NUMPAD1;
			int GroupCKey = VK_NUMPAD2;
			int GroupDKey = VK_NUMPAD3;	
			int ShowGroup = 0;
			float GroupAColor[4] = { 255.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f, 255.0f / 255.0f };
			float GroupBColor[4] = { 220.f / 255.0f, 220.0f / 255.0f, 170.0f / 255.0f, 255.0f / 255.0f };
			float GroupCColor[4] = { 190.0f / 255.0f, 183.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f };
			float GroupDColor[4] = { 176.f / 255.0f, 206.0f / 255.0f, 156.0f / 255.0f, 255.0f / 255.0f };

			std::unordered_map<std::string, ItemDetail, FnvHash> Lists = {

			};
		} Item;

		struct
		{
			struct
			{
				bool ShowPlayer = true;
				bool ShowVehicle = true;
				bool ShowAirDrop = true;
				bool ShowDeadBox = true;
				int FontSize = 14;
			} Main;

			struct
			{
				bool ShowPlayer = true;
				bool ShowVehicle = true;
				bool ShowAirDrop = true;
				bool ShowDeadBox = true;
				int FontSize = 10;
			} Mini;
		} Radar;

		struct
		{
			bool Enable = true;
			int DistanceMax = 100;
			int FontSize = 14;
			bool ShowChareTime = true;
			int ChareFontSize = 14;
			float Color[4] = { 255.0f / 255.0f, 0.f / 255.0f, 0.f / 255.0f, 255.0f / 255.0f };
			float ChareColor[4] = { 255.0f / 255.0f, 0.f / 255.0f, 0.f / 255.0f, 255.0f / 255.0f };
		} Project;

		struct
		{
			bool Enable = false;
			int EnableKey = VK_F4;
			int DistanceMax = 600;
			int FontSize = 14;
			float Color[4] = { 255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f };
		} Vehicle;

		struct
		{
			bool Enable = true;
			bool ShowItems = true;
			int EnableKey = VK_F5;
			int DistanceMax = 1000;
			int FontSize = 14;
			float Color[4] = { 255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f };
		} AirDrop;

		struct
		{
			bool Enable = false;
			bool ShowItems = true;
			int EnableKey = VK_F6;
			int DistanceMax = 100;
			int FontSize = 14;
			float Color[4] = { 255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f };
		} DeadBox;

		struct
		{
			bool Enable = false;
			bool ShowDistance = true;
			int DistanceMax = 200;
			int FontSize = 14;
		} Early;

		struct
		{
			bool Show = true;
			int ShowKey = VK_HOME;
		} Menu;

		struct
		{
			bool Setting = true;
			bool Players = false;
			bool Main = true;
			bool IsLogin = false;
			struct
			{
				char LoginUsername[128];
				char LoginPassword[128];
				char RegUsername[128];
				char RegPassword[128];
				char UnBindLoginUsername[128];
				char UnBindLoginPassword[128];
				char Key[128];
			} LoginForm;
		} Window;

		struct
		{
			int RankMode = 2;
			int MarkKey = VK_MBUTTON;
		} PlayerList;

		struct
		{
			std::string cardKey;
			char globalBuf[1024] = "\0";
		} eyou;

	} Config;

	mutable std::shared_mutex PlayerRankListsMutex;
	mutable std::shared_mutex PlayerBlackListsMutex;
	mutable std::shared_mutex PlayerWhiteListsMutex;
	mutable std::shared_mutex PlayerListsMutex;

	std::unordered_map<std::string, GamePlayerInfo> PlayerLists;
	std::unordered_map<std::string, PlayerRankList> PlayerRankLists;
	std::unordered_map<std::string, int> PlayerBlackLists;
	std::unordered_map<std::string, int> PlayerWhiteLists;

	int PlayerCount = 0;
};

extern FGameData GameData;

namespace Data
{
	inline void SetCachePackages(std::unordered_map<uint64_t, PackageInfo> value)
	{
		std::unique_lock<std::shared_mutex> lock(GameData.Actors.CachePackagesMutex);
		if (value.size() == 0)
		{
			GameData.Actors.CachePackages.clear();
		}
		else {
			GameData.Actors.CachePackages = value;
		}
	}

	inline std::unordered_map<uint64_t, PackageInfo> GetCachePackages()
	{
		std::shared_lock<std::shared_mutex> lock(GameData.Actors.CachePackagesMutex);
		return GameData.Actors.CachePackages;
	}

	inline void SetPackages(std::unordered_map<uint64_t, PackageInfo> value)
	{
		std::unique_lock<std::shared_mutex> lock(GameData.Actors.PackagesMutex);
		if (value.size() == 0)
		{
			GameData.Actors.Packages.clear();
		}
		else {
			GameData.Actors.Packages = value;
		}
	}

	inline std::unordered_map<uint64_t, PackageInfo> GetPackages()
	{
		std::shared_lock<std::shared_mutex> lock(GameData.Actors.PackagesMutex);
		return GameData.Actors.Packages;
	}

	inline std::unordered_map<uint64_t, tMapInfo> GetEnemyInfoMap()
	{
		std::shared_lock<std::shared_mutex> lock(GameData.EnemyInfoMapMutex);
		return GameData.EnemyInfoMap;
	}

	inline void SetEnemyInfoMap(std::unordered_map<uint64_t, tMapInfo> value)
	{
		std::unique_lock<std::shared_mutex> lock(GameData.EnemyInfoMapMutex);
		if (value.size() == 0)
		{
			GameData.EnemyInfoMap.clear();
		}
		else {
			GameData.EnemyInfoMap = value;
		}
	}

	inline std::unordered_map<std::string, GamePlayerInfo> GetPlayerLists()
	{
		std::shared_lock<std::shared_mutex> lock(GameData.PlayerListsMutex);
		return GameData.PlayerLists;
	}

	inline void SetPlayerLists(std::unordered_map<std::string, GamePlayerInfo> value)
	{
		std::unique_lock<std::shared_mutex> lock(GameData.PlayerListsMutex);
		if (value.size() == 0)
		{
			GameData.PlayerLists.clear();
		}
		else {
			GameData.PlayerLists = value;
		}
	}

	inline std::unordered_map<std::string, PlayerRankList> GetPlayerRankLists()
	{
		std::shared_lock<std::shared_mutex> lock(GameData.PlayerRankListsMutex);
		return GameData.PlayerRankLists;
	}

	inline void SetPlayerRankLists(std::unordered_map<std::string, PlayerRankList> value)
	{
		std::unique_lock<std::shared_mutex> lock(GameData.PlayerRankListsMutex);
		GameData.PlayerRankLists = value;
	}

	inline PlayerRankList GetPlayerRankListsItem(std::string key)
	{
		std::shared_lock<std::shared_mutex> lock(GameData.PlayerRankListsMutex);
		return GameData.PlayerRankLists[key];
	}

	inline void SetPlayerRankListsItem(std::string key, PlayerRankList value)
	{
		std::unique_lock<std::shared_mutex> lock(GameData.PlayerRankListsMutex);
		GameData.PlayerRankLists[key] = value;
	}

	inline int GetPlayerWhiteListsItem(std::string key)
	{
		std::shared_lock<std::shared_mutex> lock(GameData.PlayerWhiteListsMutex);
		if (GameData.PlayerWhiteLists.count(key) > 0)
		{
			return GameData.PlayerWhiteLists[key];
		}

		return 0;
	}

	inline void DeletePlayerWhiteListsItem(std::string key)
	{
		std::unique_lock<std::shared_mutex> lock(GameData.PlayerWhiteListsMutex);
		GameData.PlayerWhiteLists.erase(key);
	}

	inline void SetPlayerWhiteListsItem(std::string key, int value)
	{
		std::unique_lock<std::shared_mutex> lock(GameData.PlayerWhiteListsMutex);
		GameData.PlayerWhiteLists[key] = value;
	}

	inline void SetPlayerWhiteLists(std::unordered_map<std::string, int> value)
	{
		std::unique_lock<std::shared_mutex> lock(GameData.PlayerWhiteListsMutex);
		GameData.PlayerWhiteLists = value;
	}

	inline std::unordered_map<std::string, int> GetPlayerWhiteLists()
	{
		std::shared_lock<std::shared_mutex> lock(GameData.PlayerWhiteListsMutex);
		return GameData.PlayerWhiteLists;
	}

	inline int GetPlayerBlackListsItem(std::string key)
	{
		std::shared_lock<std::shared_mutex> lock(GameData.PlayerBlackListsMutex);
		if (GameData.PlayerBlackLists.count(key) > 0)
		{
			return GameData.PlayerBlackLists[key];
		}

		return 0;
	}

	inline void DeletePlayerBlackListsItem(std::string key)
	{
		std::unique_lock<std::shared_mutex> lock(GameData.PlayerBlackListsMutex);
		GameData.PlayerBlackLists.erase(key);
	}

	inline void SetPlayerBlackListsItem(std::string key, int value)
	{
		std::unique_lock<std::shared_mutex> lock(GameData.PlayerBlackListsMutex);
		GameData.PlayerBlackLists[key] = value;
	}

	inline void SetPlayerBlackLists(std::unordered_map<std::string, int> value)
	{
		std::unique_lock<std::shared_mutex> lock(GameData.PlayerBlackListsMutex);
		GameData.PlayerBlackLists = value;
	}

	inline void SetPlayerListsItem(std::string name, GamePlayerInfo value)
	{
		std::unique_lock<std::shared_mutex> lock(GameData.PlayerListsMutex);
		GameData.PlayerLists[name] = value;
	}

	inline std::unordered_map<std::string, int> GetPlayerBlackLists()
	{
		std::shared_lock<std::shared_mutex> lock(GameData.PlayerBlackListsMutex);
		return GameData.PlayerBlackLists;
	}

	inline void SetCachePlayers(std::unordered_map<uint64_t, Player> value)
	{
		std::unique_lock<std::shared_mutex> lock(GameData.Actors.CachePlayersMutex);
		if (value.size() == 0)
		{
			GameData.Actors.CachePlayers.clear();
		}
		else {
			GameData.Actors.CachePlayers = value;
		}
	}

	inline std::unordered_map<uint64_t, Player> GetCachePlayers()
	{
		std::shared_lock<std::shared_mutex> lock(GameData.Actors.CachePlayersMutex);
		return GameData.Actors.CachePlayers;
	}

	inline void SetCacheEntitys(std::unordered_map<uint64_t, ActorEntityInfo> value)
	{
		std::unique_lock<std::shared_mutex> lock(GameData.Actors.CacheEntitysMutex);
		if (value.size() == 0)
		{
			GameData.Actors.CacheEntitys.clear();
		}
		else {
			GameData.Actors.CacheEntitys = value;
		}
	}

	inline std::unordered_map<uint64_t, ActorEntityInfo> GetCacheEntitys()
	{
		std::shared_lock<std::shared_mutex> lock(GameData.Actors.CacheEntitysMutex);
		return GameData.Actors.CacheEntitys;
	}

	inline void SetPlayersData(std::unordered_map<uint64_t, Player> value)
	{
		std::unique_lock<std::shared_mutex> lock(GameData.Actors.PlayersDataMutex);
		if (value.size() == 0)
		{
			GameData.Actors.PlayersData.clear();
		}
		else {
			GameData.Actors.PlayersData = value;
		}
	}

	inline std::unordered_map<uint64_t, Player> GetPlayersData()
	{
		std::shared_lock<std::shared_mutex> lock(GameData.Actors.PlayersDataMutex);
		return GameData.Actors.PlayersData;
	}

	inline void SetPlayers(std::unordered_map<uint64_t, Player> value)
	{
		std::unique_lock<std::shared_mutex> lock(GameData.Actors.PlayersMutex);
		if (value.size() == 0)
		{
			GameData.Actors.Players.clear();
		}
		else {
			GameData.Actors.Players = value;
		}
	}

	inline std::unordered_map<uint64_t, Player> GetPlayers()
	{
		std::shared_lock<std::shared_mutex> lock(GameData.Actors.PlayersMutex);
		return GameData.Actors.Players;
	}

	inline Player GetPlayersItem(uint64_t Key)
	{
		std::shared_lock<std::shared_mutex> lock(GameData.Actors.PlayersMutex);
		return GameData.Actors.Players[Key];
	}

	inline void SetVehicles(std::unordered_map<uint64_t, VehicleInfo> value)
	{
		std::unique_lock<std::shared_mutex> lock(GameData.Actors.VehiclesMutex);
		if (value.size() == 0)
		{
			GameData.Actors.Vehicles.clear();
		}
		else {
			GameData.Actors.Vehicles = value;
		}
	}

	inline std::unordered_map<uint64_t, VehicleInfo> GetVehicles()
	{
		std::shared_lock<std::shared_mutex> lock(GameData.Actors.VehiclesMutex);
		return GameData.Actors.Vehicles;
	}

	inline void SetCacheVehicles(std::unordered_map<uint64_t, VehicleInfo> value)
	{
		std::unique_lock<std::shared_mutex> lock(GameData.Actors.CacheVehiclesMutex);
		if (value.size() == 0)
		{
			GameData.Actors.CacheVehicles.clear();
		}
		else {
			GameData.Actors.CacheVehicles = value;
		}
	}

	inline std::unordered_map<uint64_t, VehicleInfo> GetCacheVehicles()
	{
		std::shared_lock<std::shared_mutex> lock(GameData.Actors.CacheVehiclesMutex);
		return GameData.Actors.CacheVehicles;
	}

	inline void SetVehiclWheels(std::unordered_map<uint64_t, VehicleWheelInfo> value)
	{
		std::unique_lock<std::shared_mutex> lock(GameData.Actors.VehicleWheelsMutex);
		if (value.size() == 0)
		{
			GameData.Actors.VehicleWheels.clear();
		}
		else {
			GameData.Actors.VehicleWheels = value;
		}
	}

	inline std::unordered_map<uint64_t, VehicleWheelInfo> GetVehicleWheels()
	{
		std::shared_lock<std::shared_mutex> lock(GameData.Actors.VehicleWheelsMutex);
		return GameData.Actors.VehicleWheels;
	}

	inline VehicleWheelInfo GetVehicleWheelsItem(uint64_t Key)
	{
		std::shared_lock<std::shared_mutex> lock(GameData.Actors.VehicleWheelsMutex);
		return GameData.Actors.VehicleWheels[Key];
	}

	inline std::unordered_map<std::string, EntityInfo, FnvHash> GetGNameLists()
	{
		std::shared_lock<std::shared_mutex> lock(GameData.Actors.GNameListsMutex);
		return GameData.GNameLists;
	}

	inline std::pair<std::unordered_map<std::string, EntityInfo, FnvHash>, std::unordered_map<int, EntityInfo>> GetGNameListsAndGNameListsByID()
	{
		std::shared_lock<std::shared_mutex> lock(GameData.Actors.GNameListsMutex);
		return { GameData.GNameLists, GameData.GNameListsByID };
	}

	inline void SetGNameLists(std::unordered_map<std::string, EntityInfo, FnvHash> value)
	{
		std::unique_lock<std::shared_mutex> lock(GameData.Actors.GNameListsMutex);
		GameData.GNameLists = value;
	}

	inline void ClearGNameListsAndGNameListsByID()
	{
		std::unique_lock<std::shared_mutex> lock(GameData.Actors.GNameListsMutex);
		//GameData.GNameLists = EntityLists;
		GameData.GNameListsByID.clear();
	}

	inline void SetGNameListsAndGNameListsByID(const std::unordered_map<std::string, EntityInfo, FnvHash>& value, const std::unordered_map<int, EntityInfo>& value1)
	{
		std::unique_lock<std::shared_mutex> lock(GameData.Actors.GNameListsMutex);
		for (auto item : value)
		{
			GameData.GNameLists[item.first] = item.second;
		}
		for (auto item : value1)
		{
			GameData.GNameListsByID[item.first] = item.second;
		}
	}

	inline void SetGNameListsAndGNameListsByIDItem(std::string key, EntityInfo value, int key1, EntityInfo value1)
	{
		std::unique_lock<std::shared_mutex> lock(GameData.Actors.GNameListsMutex);
		GameData.GNameLists[key] = value;
		GameData.GNameListsByID[key1] = value1;
	}

	inline std::unordered_map<int, EntityInfo> GetGNameListsByID()
	{
		std::shared_lock<std::shared_mutex> lock(GameData.Actors.GNameListsMutex);
		return GameData.GNameListsByID;
	}

	inline void SetGNameListsByID(std::unordered_map<int, EntityInfo> value)
	{
		std::unique_lock<std::shared_mutex> lock(GameData.Actors.GNameListsMutex);
		GameData.GNameListsByID = value;
	}

	inline EntityInfo GetGNameListsByIDItem(int key)
	{
		std::unique_lock<std::shared_mutex> lock(GameData.Actors.GNameListsMutex);
		if (GameData.GNameListsByID.count(key) > 0)
		{
			return GameData.GNameListsByID[key];
		}

		return EntityInfo{ "Unknown", EntityType::Unknown, 0, WeaponType::Other };
	}

	inline EntityInfo GetGNameListsItem(std::string key)
	{
		std::unique_lock<std::shared_mutex> lock(GameData.Actors.GNameListsMutex);
		if (GameData.GNameLists.count(key) > 0)
		{
			return GameData.GNameLists[key];
		}

		return EntityInfo{ "Unknown", EntityType::Unknown, 0, WeaponType::Other };
	}

	inline void SetCacheDroppedItems(std::unordered_map<uint64_t, DroppedItemInfo> value)
	{
		std::unique_lock<std::shared_mutex> lock(GameData.Actors.CacheDroppedItemsMutex);
		if (value.size() == 0)
		{
			GameData.Actors.CacheDroppedItems.clear();
		}
		else {
			GameData.Actors.CacheDroppedItems = value;
		}
	}

	inline std::unordered_map<uint64_t, DroppedItemInfo> GetCacheDroppedItems()
	{
		std::shared_lock<std::shared_mutex> lock(GameData.Actors.CacheDroppedItemsMutex);
		return GameData.Actors.CacheDroppedItems;
	}

	inline void SetCacheDroppedItemGroups(std::unordered_map<uint64_t, DroppedItemGroupInfo> value)
	{
		std::unique_lock<std::shared_mutex> lock(GameData.Actors.CacheDroppedItemGroupsMutex);
		if (value.size() == 0)
		{
			GameData.Actors.CacheDroppedItemGroups.clear();
		}
		else {
			GameData.Actors.CacheDroppedItemGroups = value;
		}
	}

	inline std::unordered_map<uint64_t, DroppedItemGroupInfo> GetCacheDroppedItemGroups()
	{
		std::shared_lock<std::shared_mutex> lock(GameData.Actors.CacheDroppedItemGroupsMutex);
		return GameData.Actors.CacheDroppedItemGroups;
	}

	inline void SetItems(std::unordered_map<uint64_t, ItemInfo> value)
	{
		std::unique_lock<std::shared_mutex> lock(GameData.Actors.ItemsMutex);
		if (value.size() == 0)
		{
			GameData.Actors.Items.clear();
		}
		else {
			GameData.Actors.Items = value;
		}
	}

	inline std::unordered_map<uint64_t, ItemInfo> GetItems()
	{
		std::shared_lock<std::shared_mutex> lock(GameData.Actors.ItemsMutex);
		return GameData.Actors.Items;
	}

	inline void SetCacheProjects(std::unordered_map<uint64_t, ProjectInfo> value)
	{
		std::unique_lock<std::shared_mutex> lock(GameData.Actors.CacheProjectsMutex);
		if (value.size() == 0)
		{
			GameData.Actors.CacheProjects.clear();
		}
		else {
			GameData.Actors.CacheProjects = value;
		}
	}

	inline std::unordered_map<uint64_t, ProjectInfo> GetCacheProjects()
	{
		std::shared_lock<std::shared_mutex> lock(GameData.Actors.CacheProjectsMutex);
		return GameData.Actors.CacheProjects;
	}

	inline void SetProjects(std::unordered_map<uint64_t, ProjectInfo> value)
	{
		std::unique_lock<std::shared_mutex> lock(GameData.Actors.ProjectsMutex);
		if (value.size() == 0)
		{
			GameData.Actors.Projects.clear();
		}
		else {
			GameData.Actors.Projects = value;
		}
	}

	inline std::unordered_map<uint64_t, ProjectInfo> GetProjects()
	{
		std::shared_lock<std::shared_mutex> lock(GameData.Actors.ProjectsMutex);
		return GameData.Actors.Projects;
	}

	inline std::unordered_map<uint64_t, FogPlayerInfo> GetFogPlayers()
	{
		std::shared_lock<std::shared_mutex> lock(GameData.Actors.FogPlayersMutex);
		return GameData.Actors.FogPlayers;
	}

	inline void SetFogPlayers(std::unordered_map<uint64_t, FogPlayerInfo> value)
	{
		std::unique_lock<std::shared_mutex> lock(GameData.Actors.FogPlayersMutex);
		if (value.size() == 0)
		{
			GameData.Actors.FogPlayers.clear();
		}
		else {
			GameData.Actors.FogPlayers = value;
		}
	}
}