#pragma once
#include <wchar.h>
#include <cstdint>
#include <vector>
#include <string>
#include <iostream>
#include <locale>
#include <basetsd.h>
#include <intrin.h>
#include <DMALibrary/Memory/Memory.h>
#include <Utils/ue4math/ue4math.h>

enum class CharacterState {
	Dead,
	Alive,
	Groggy
};

enum class EGender {
	Male,
	Female,
	EGender_MAX,
};

enum class WheelState {
	Normal,
	FlatTire = 1
};

enum class EWeaponClass : uint8_t {
	Class_None,
	Class_Pistol,
	Class_SMG,
	Class_Rifle,
	Class_Carbine,
	Class_Shotgun,
	Class_Sniper,
	Class_DMR,
	Class_LMG,
	Class_Melee,
	Class_Throwable,
	Class_Shield,
	Class_Crossbow,
	Class_Launcher,
	Class_GrenadeLauncher,
	Class_Mortar,
	EWeaponClass_MAX,
};

struct FText
{
	char buffer[256];
};

struct TArrayData
{
	uint64_t data;
	int count;
};

enum EPartnerLevel : uint8_t {
	None,
	Normal,
	Lead,
	EPartnerLevel_MAX,
};

enum ECharacterState : uint8_t
{
	Unk,
	Fire, // 开枪
	Wounded, // 掉血
	BeHit, // 倒地
	Offline, // 掉线
};

enum class ECharacterIconType : uint8_t {
	Normal,
	Vehicle,
	Parachute,
	Die,
	Groggy,
	Quitter,
	Observer,
	Aircraft,
	EmergencyPickup,
	ECharacterIconType_MAX,
};

enum class EAnimPawnState : uint8_t {
	PS_OnFoot,
	PS_VehicleDriver,
	PS_VehiclePassenger,
	PS_SecondaryLocomotion,
	PS_MortarDriver,
	PS_MAX,
};

enum class ECastAnim : uint8_t {
	None,
	Bandage,
	FirstAid,
	Medkit,
	EnergyDrink,
	Painkiller,
	Adrenaline,
	Door,
	Battery,
	Crafting,
	SuperDrink,
	Key,
	EmergencyPickup,
	SelfRevive,
	MortarInstall,
	BicycleDeploy,
	BulletproofShield,
	VehicleSkin,
	UnlockDoor,
	Custom,
	VehicleRepair,
	ArmorRepair,
	BlueChipTower,
	RevivalTransmitter,
	OpenBox,
	PlantedBomb,
	DefusingBomb,
	BattleReadyKit,
	OpenStrongBox,
	ECastAnim_MAX,
};

enum class ESlateVisibility : uint8_t
{
	Visible = 0,
	Collapsed = 1,
	Hidden = 2,
	HitTestInvisible = 3,
	SelfHitTestInvisible = 4,
	ESlateVisibility_MAX = 5
};

enum class EProjectileExplodeState : uint8_t {
	NotExplode,
	ImpactExplode,
	TimerExplode,
	EProjectileExplodeState_MAX,
};

enum class EProjectileExplosionStartType : uint8_t {
	NotStart,
	Impact,
	Delay,
	ImpactOrDelay,
	EProjectileExplosionStartType_MAX,
};

enum ERelativeTransformSpace : uint8_t
{
	RTS_World,
	RTS_Actor,
	RTS_Component,
	RTS_ParentBoneSpace,
};

enum EWeaponAttachmentSlotID : uint8_t {
	Nones,
	Muzzle,
	LowerRail,
	UpperRail,
	Magazine,
	Stock,
	Angled
};

struct FTslPlayerStatisticsForOwner {
	float TotalMovedDistanceMeter; // 0x00(0x04)
	float TotalGivenDamages; // 0x04(0x04)
	float LongestDistanceKill; // 0x08(0x04)
	int32_t HeadShots; // 0x0c(0x04)
};

template<class T>
class TArray {
private:
	T* Data;
	int32_t Count;
	int32_t Max;

	friend struct FString;
public:
	size_t size(size_t MaxSize = 0x2000) const {
		return Count < MaxSize ? Count : MaxSize;
	}

	bool GetValue(int i, T& value) const {
		if (i < 0 || i >= size(0x2000)) return false;
		//return memcpy(&value, (PVOID)(Data + sizeof(T) * i), sizeof(T));
		return mem.Read(reinterpret_cast<uintptr_t>((Data + sizeof(T) * i)), &value, sizeof(T));
	}

	bool GetValues(T& value, size_t MaxSize = 0x2000) const {
		return mem.Read(reinterpret_cast<uintptr_t>(Data), &value, sizeof(T) * size(MaxSize));
		//return memcpy(&value, (PVOID)Data, sizeof(T) * size(MaxSize));
	}

	std::vector<T> GetVector(size_t MaxSize = 0x2000) const {
		std::vector<T> v(size(MaxSize));
		if (!GetValues(v[0], MaxSize))
			v.clear();

		return v;
	}

	operator std::vector<T>() const { return GetVector(); }

	T operator [](int i) const {
		T Value;
		if (!GetValue(i, Value))
			ZeroMemory(&Value, sizeof(Value));
		return Value;
	}
};

template<class TEnum>
class TEnumAsByte
{
public:
	typedef TEnum EnumType;
	TEnumAsByte() = default;
	TEnumAsByte(const TEnumAsByte&) = default;
	TEnumAsByte& operator=(const TEnumAsByte&) = default;
	FORCEINLINE TEnumAsByte(TEnum InValue) : Value(static_cast<uint8_t>(InValue)) {}
	explicit FORCEINLINE TEnumAsByte(int32_t InValue) : Value(static_cast<uint8_t>(InValue)) {}
	explicit FORCEINLINE TEnumAsByte(uint8_t InValue) : Value(InValue) {}
	bool operator==(TEnum InValue) const { return static_cast<TEnum>(Value) == InValue; }
	bool operator==(TEnumAsByte InValue) const { return Value == InValue.Value; }
	operator TEnum() const { return (TEnum)Value; }
	TEnum GetValue() const { return (TEnum)Value; }
private:
	uint8_t Value;
};

template<class T>
struct TSetElement {
	T Value;//0
	int HashNextId;//9
	int HashIndex;//A
};

template<class T>
class TSet : public TArray<TSetElement<T>> {};

template<class KeyType, class ValueType>
struct TPair {
	KeyType Key;
	ValueType Value;
};

template<class KeyType, class ValueType>
class TMap : public TSet<TPair<KeyType, ValueType>> {
public:
	bool GetValue(const KeyType& Key, ValueType& Value) const {

		for (const auto& Elem : this->GetVector()) {
			if (Elem.Value.Key == Key) {
				Value = Elem.Value.Value;
				return true;
			}
		}
		return false;
	}
};

struct FString : public TArray<wchar_t>
{
	FString() = default;

	explicit FString(const wchar_t* other)
	{
		Max = Count = *other ? std::wcslen(other) + 1 : 0;

		if (Count)
		{
			Data = const_cast<wchar_t*>(other);
		}
	};

	inline bool IsValid() const
	{
		return Data != nullptr;
	}

	inline const wchar_t* cw_str() const
	{
		return Data;
	}

	inline const char* c_str() const
	{
		return (const char*)Data;
	}

	std::string ToString() const
	{
		size_t length = std::wcslen(Data);
		std::string str(length, '\0');
		std::use_facet<std::ctype<wchar_t>>(std::locale()).narrow(Data, Data + length, '?', &str[0]);

		return str;
	}

	std::wstring ToWString() const
	{
		std::wstring str(Data);
		return str;
	}
};

struct FTslWidgetStateOld
{
	unsigned char Pad[0x30];
	uint64_t WidgetClass;	                                                                             // 0x0030(0x0008) (CPF_ZeroConstructor, CPF_Transient, CPF_IsPlainOldData)
	unsigned char                                      UnknownData00[0x8];                                       // 0x0038(0x0008) MISSED OFFSET
	uint64_t Widget;                                                                               // 0x0040(0x0008) (CPF_ExportObject, CPF_ZeroConstructor, CPF_Transient, CPF_InstancedReference, CPF_IsPlainOldData)
	unsigned char                                      UnknownData01[0x18];                                      // 0x0048(0x0018) MISSED OFFSET
};

struct FTslWidgetState
{
	unsigned char Pad[0x30];
	unsigned char WidgetClass[0x8];
	unsigned char pad_38[0x8];
	ULONG64 Widget;
	unsigned char pad_48[0x20];
};

struct FMargin
{
	float                                              Left;                                                     // 0x0000(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              Top;                                                      // 0x0004(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              Right;                                                    // 0x0008(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              Bottom;                                                   // 0x000C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
};

struct FWeaponTrajectoryConfig3
{
	float                                              InitialSpeed;                                             // 0x0000(0x0004) (CPF_Edit, CPF_ZeroConstructor, CPF_DisableEditOnInstance, CPF_IsPlainOldData)
	float                                               HitDamage;                                                // 0x0004(0x0004) (CPF_Edit, CPF_ZeroConstructor, CPF_DisableEditOnInstance, CPF_IsPlainOldData)
	float                                              LowerClampDamage;                                         // 0x0008(0x0004) (CPF_Edit, CPF_ZeroConstructor, CPF_DisableEditOnInstance, CPF_IsPlainOldData)
	unsigned long long                                 BallisticCurve;                                           // 0x0010(0x0008) (CPF_Edit, CPF_ZeroConstructor, CPF_DisableEditOnInstance, CPF_IsPlainOldData)
	float                                              RangeModifier;                                            // 0x0018(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_BlueprintReadOnly, CPF_ZeroConstructor, CPF_DisableEditOnInstance, CPF_IsPlainOldData)
	float                                              ReferenceDistance;                                        // 0x001C(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_BlueprintReadOnly, CPF_ZeroConstructor, CPF_DisableEditOnInstance, CPF_IsPlainOldData)
	float                                              TravelDistanceMax;                                        // 0x0020(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_BlueprintReadOnly, CPF_ZeroConstructor, CPF_DisableEditOnInstance, CPF_IsPlainOldData)
	unsigned char                                      bUseMaxDamageDistance : 1;                                // 0x0024(0x0001) (CPF_Edit, CPF_BlueprintVisible, CPF_BlueprintReadOnly, CPF_ZeroConstructor, CPF_DisableEditOnInstance, CPF_IsPlainOldData)
	float                                              SimulationSubstepTime;                                    // 0x0028(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_BlueprintReadOnly, CPF_ZeroConstructor, CPF_DisableEditOnInstance, CPF_IsPlainOldData)
	float                                              VDragCoefficient;                                         // 0x002C(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_BlueprintReadOnly, CPF_ZeroConstructor, CPF_DisableEditOnInstance, CPF_IsPlainOldData)
	float                                              BDS;                                                      // 0x0030(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_BlueprintReadOnly, CPF_ZeroConstructor, CPF_DisableEditOnInstance, CPF_IsPlainOldData)
	unsigned char                                      bUseAdvancedBallistics : 1;                               // 0x0034(0x0001) (CPF_Edit, CPF_BlueprintVisible, CPF_BlueprintReadOnly, CPF_ZeroConstructor, CPF_DisableEditOnInstance, CPF_IsPlainOldData)
	unsigned char                                      bCanProduceCrackSound : 1;                                // 0x0035(0x0001) (CPF_Edit, CPF_BlueprintVisible, CPF_BlueprintReadOnly, CPF_ZeroConstructor, CPF_DisableEditOnInstance, CPF_IsPlainOldData)
	unsigned char                                      IsPenetrable : 1;                                         // 0x0036(0x0001) (CPF_Edit, CPF_ZeroConstructor, CPF_DisableEditOnInstance, CPF_IsPlainOldData)
	unsigned long long                                 DamageType;                                               // 0x0038(0x0008) (CPF_Edit, CPF_ZeroConstructor, CPF_DisableEditOnInstance, CPF_IsPlainOldData)
	unsigned char                                      bIsTrajectoryReplicationEnabled : 1;                      // 0x0040(0x0001) (CPF_Edit, CPF_DisableEditOnInstance)
};

struct FName
{
	int ComparisonIndex = 0;
	int Number = 0;
	bool operator == (const FName& rhs) const { return ComparisonIndex == rhs.ComparisonIndex && Number == rhs.Number; }
	bool operator != (const FName& rhs) const { return !(*this == rhs); }
};

struct FInputAxisProperties {
	//float DEADZONE; // 0x00(0x04)
	//float OuterDeadZone; // 0x04(0x04)
	//float Sensitivity; // 0x08(0x04)
	//float Exponent; // 0x0c(0x04)
	//char bInvert : 1; // 0x10(0x01)
	//char pad_10[0x8]; // 0x10(0x01)
	//struct UCurveFloat* MultiplierAxisValueCurve; // 0x18(0x08)


	float DEADZONE; // 0x00(0x04)
	float OuterDeadZone; // 0x04(0x04)
	float Sensitivity; // 0x08(0x04)
	float Exponent; // 0x0c(0x04)
	char bInvert : 1; // 0x10(0x01)
	char pad_10_1 : 7; // 0x10(0x01)
	char pad_11[0x7]; // 0x11(0x07)
	struct UCurveFloat* MultiplierAxisValueCurve; // 0x18(0x08)





};

struct FInputAxisConfigEntry {
	struct FName AxisKeyName; // 0x00(0x08)
	struct FInputAxisProperties AxisProperties; // 0x08(0x20)
};

struct FWeaponTrajectoryConfig
{
	float                                              InitialSpeed;                                             // 0x0000(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              HitDamage;                                                // 0x0004(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              pad_AAA; // 0x08(0x04)
	char                                               pad_C[0x4]; // 0x0c(0x04)
	char                                               pad_47[0x10];                                             // 0x0008(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              VehicleDamageScalar;                                      // 0x0008(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              LowerClampDamage;                                         // 0x000C(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	ULONG64	 										   BallisticCurve;                                           // 0x0010(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              RangeModifier;                                            // 0x0018(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              ReferenceDistance;                                        // 0x001C(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              TravelDistanceMax;                                        // 0x0020(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               bUseMaxDamageDistance;                                    // 0x0024(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x0025(0x0003) MISSED OFFSET
	float                                              SimulationSubstepTime;                                    // 0x0028(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              VDragCoefficient;                                         // 0x002C(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              BDS;                                                      // 0x0030(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               bUseAdvancedBallistics;                                   // 0x0034(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	char                                               pad_4C[0x1]; // 0x4c(0x01)
	bool                                               bCanProduceCrackSound;                                    // 0x0035(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               IsPenetrable;                                             // 0x0036(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x1];                                       // 0x0037(0x0001) MISSED OFFSET
	ULONG64											   DamageType;                                               // 0x0038(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      bIsTrajectoryReplicationEnabled : 1;
	unsigned char                                      pad_50_1 : 7;                                             // 0x0040(0x0001) (Edit, DisableEditOnInstance)
	unsigned char                                      UnknownData02[0x3];                                       // 0x0041(0x0003) MISSED OFFSET
	float                                              WeaponSpread;                                             // 0x0044(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
};



struct FKeyHandleMap
{
	unsigned char                                      UnknownData00[0x50];                                      // 0x0000(0x0050) MISSED OFFSET
};
struct FIndexedCurve
{
	unsigned char                                      UnknownData00[0x8];                                       // 0x0000(0x0008) MISSED OFFSET
	struct FKeyHandleMap                               KeyHandlesToIndices;                                      // 0x0008(0x0050) (Transient)
};
struct FRichCurve : public FIndexedCurve
{
	BYTE		                                       PreInfinityExtrap;                                        // 0x0058(0x0001) (ZeroConstructor, IsPlainOldData)
	BYTE		                                       PostInfinityExtrap;                                       // 0x0059(0x0001) (ZeroConstructor, IsPlainOldData)
	BYTE		                                       UnknownData00[0x2];                                       // 0x005A(0x0002) MISSED OFFSET
	float                                              DefaultValue;                                             // 0x005C(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	ULONG64						                       Keys;                                                     // 0x0060(0x0010) (Edit, EditFixedSize, ZeroConstructor)
};
struct FRichCurveKey
{
	BYTE		                                       InterpMode;                                               // 0x0000(0x0001) (ZeroConstructor, IsPlainOldData)
	BYTE		                                       TangentMode;                                              // 0x0001(0x0001) (ZeroConstructor, IsPlainOldData)
	BYTE		                                       TangentWeightMode;                                        // 0x0002(0x0001) (ZeroConstructor, IsPlainOldData)
	BYTE		                                       UnknownData00[0x1];                                       // 0x0003(0x0001) MISSED OFFSET
	float                                              Time;                                                     // 0x0004(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              Value;                                                    // 0x0008(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              ArriveTangent;                                            // 0x000C(0x0004) (ZeroConstructor, IsPlainOldData)
	float                                              ArriveTangentWeight;                                      // 0x0010(0x0004) (ZeroConstructor, IsPlainOldData)
	float                                              LeaveTangent;                                             // 0x0014(0x0004) (ZeroConstructor, IsPlainOldData)
	float                                              LeaveTangentWeight;                                       // 0x0018(0x0004) (ZeroConstructor, IsPlainOldData)
};

//struct FWuPubgIdData
//{
//	char pad[0x16];
//	int                                                SurvivalTier;                                             // 0x0000(0x0004) (ZeroConstructor, IsPlainOldData)
//	int                                                SurvivalLevel;                                            // 0x0004(0x0004) (ZeroConstructor, IsPlainOldData)
//	int  ReputationLevel;
//	ULONG64 NameplateId; // 0x08(0x10)
//	ULONG64 EmblemId; // 0x18(0x10)
//	ULONG64 MedalOne; // 0x28(0x10)
//	ULONG64 MedalTwo; // 0x38(0x10)
//	ULONG64 ClanplateId; // 0x48(0x10)
//};

struct FWuPubgIdData
{
	class FString                                      AccountId;                                                // 0x0000(0x0010) (ZeroConstructor)
	class FString                                      Nickname;                                                 // 0x0010(0x0010) (ZeroConstructor)
	int                                                SurvivalTier;                                             // 0x0020(0x0004) (ZeroConstructor, IsPlainOldData)
	int                                                SurvivalLevel;                                            // 0x0024(0x0004) (ZeroConstructor, IsPlainOldData)
	int                                                ReputationLevel;                                          // 0x0028(0x0004) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x002C(0x0004) MISSED OFFSET
	class FString                                      NameplateId;                                              // 0x0030(0x0010) (ZeroConstructor)
	class FString                                      EmblemId;                                                 // 0x0040(0x0010) (ZeroConstructor)
	class FString                                      MedalOne;                                                 // 0x0050(0x0010) (ZeroConstructor)
	class FString                                      MedalTwo;                                                 // 0x0060(0x0010) (ZeroConstructor)
	class FString                                      ClanTag;                                                  // 0x0070(0x0010) (ZeroConstructor)
	class FString                                      ClanplateId;                                              // 0x0080(0x0010) (ZeroConstructor)
};

struct FWuCharacterClanInfo
{
	FString                                            ClanId;                                                   // 0x0000(0x0010) (ZeroConstructor)
	FString                                            ClanName;                                                 // 0x0010(0x0010) (ZeroConstructor)
	FString											   ClanTag;                                                  // 0x0020(0x0010) (ZeroConstructor)
	int                                                ClanLevel;                                                // 0x0030(0x0004) (ZeroConstructor, IsPlainOldData)
};

struct FMeshBoneInfo
{
	FName Name;
	int32_t ParentIndex;
	int32_t pad;
};

enum class ESight
{
	Iron,
	RedDot,
	Holo,
	X2,
	X3,
	X4,
	X6,
	X8,
	X15
};

enum ERichCurveExtrapolation : uint8_t
{
	RCCE_Cycle = 0,
	RCCE_CycleWithOffset = 1,
	RCCE_Oscillate = 2,
	RCCE_Linear = 3,
	RCCE_Constant = 4,
	RCCE_None = 5,
	RCCE_MAX = 6
};

enum ERichCurveInterpMode : uint8_t
{
	RCIM_Linear = 0,
	RCIM_Constant = 1,
	RCIM_Cubic = 2,
	RCIM_None = 3,
	RCIM_MAX = 4
};

typedef  int	 		int32;		// 32-bit signed.
__forceinline int32 FloorToInt(float F)
{
	return _mm_cvt_ss2si(_mm_set_ss(F + F - 0.5f)) >> 1;
}

template< class T >
constexpr __forceinline T Abs(const T A)
{
	return (A >= (T)0) ? A : -A;
}

struct FHitResult
{
	unsigned char                                      _0x000000[0x88];                               // 0x0084(0x0004) MISSED OFFSET
};

enum ETraceTypeQuery
{
	TraceTypeQuery1 = 0,
	TraceTypeQuery2 = 1,
	TraceTypeQuery3 = 2,
	TraceTypeQuery4 = 3,
	TraceTypeQuery5 = 4,
	TraceTypeQuery6 = 5,
	TraceTypeQuery7 = 6,
	TraceTypeQuery8 = 7,
	TraceTypeQuery9 = 8,
	TraceTypeQuery10 = 9,
	TraceTypeQuery11 = 10,
	TraceTypeQuery12 = 11,
	TraceTypeQuery13 = 12,
	TraceTypeQuery14 = 13,
	TraceTypeQuery15 = 14,
	TraceTypeQuery16 = 15,
	TraceTypeQuery17 = 16,
	TraceTypeQuery18 = 17,
	TraceTypeQuery19 = 18,
	TraceTypeQuery20 = 19,
	TraceTypeQuery21 = 20,
	TraceTypeQuery22 = 21,
	TraceTypeQuery23 = 22,
	TraceTypeQuery24 = 23,
	TraceTypeQuery25 = 24,
	TraceTypeQuery26 = 25,
	TraceTypeQuery27 = 26,
	TraceTypeQuery28 = 27,
	TraceTypeQuery29 = 28,
	TraceTypeQuery30 = 29,
	TraceTypeQuery31 = 30,
	TraceTypeQuery32 = 31,
	TraceTypeQuery_MAX = 32,
	ETraceTypeQuery_MAX = 33
};

enum EDrawDebugTrace
{
	EDrawDebugTrace__None = 0,
	EDrawDebugTrace__ForOneFrame = 1,
	EDrawDebugTrace__ForDuration = 2,
	EDrawDebugTrace__Persistent = 3,
	EDrawDebugTrace__EDrawDebugTrace_MAX = 4
};

struct FLinearColor
{
	float                                              R;                                                        // 0x0000(0x0004) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)
	float                                              G;                                                        // 0x0004(0x0004) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)
	float                                              B;                                                        // 0x0008(0x0004) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)
	float                                              A;                                                        // 0x000C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)

	inline FLinearColor()
		: R(0), G(0), B(0), A(0)
	{ }

	inline FLinearColor(float r, float g, float b, float a)
		: R(r),
		G(g),
		B(b),
		A(a)
	{ }

};
