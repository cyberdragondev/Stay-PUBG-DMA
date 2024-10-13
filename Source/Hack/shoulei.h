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

bool  ÷¿◊∑∂Œß = true;
int  ÷¿◊∑∂Œßƒ£ Ω = 0;
int  ÷¿◊∑∂Œßi = 53;

enum _Cache_Flag : int {
	CacheFlag__Grenade = 1,
	CacheFlag__BlueZoneGrenade,
	CacheFlag__StickyGrenade,
	CacheFlag__C4,
	CacheFlag__Molotov,
	CacheFlag__ProjSmokeBomb_C,
	CacheFlag__VehWheel,
	CacheFlag__FootBall,
	CacheFlag__Flare,
	CacheFlag__HandWeap_No_zhCN,
	CacheFlag__HandWeap_Grenade,
	CacheFlag__HandWeap_C4,
	CacheFlag__HandWeap_Knife,
	CacheFlag__HandWeap_PanzerFaust,
	CacheFlag__BoatVehicle,
	CacheFlag__Porter,
	CacheFlag__LootTruck,
	CacheFlag__Range_Main,
	CacheFlag__Baltic_Main,
	CacheFlag__Desert_Main,
	CacheFlag__Tiger_Main,
	CacheFlag__Savage_Main,
	CacheFlag__DihorOtok_Main,
	CacheFlag__Chimera_Main,
	CacheFlag__Summerland_Main,
	CacheFlag__WorldMap,
	CacheFlag__InventoryWidget,
	CacheFlag__RadioMessageLogWidget,
	CacheFlag__BP_Preset,
	CacheFlag__MatchResultWidget,
	CacheFlag__HUD_Lobby,
	CacheFlag__HUD_Shooter,
	CacheFlag__Nothing = 32768
};


//FVector2D Calc_Vector3_(FVector2D V, FVector2D angle, float len) {
//	float Y = sinf(angle.Y); return FVector2D(V.X + sinf(angle.X) * Y * len, V.Y + cosf(angle.X) * Y * len, V.Z + cosf(angle.Y) * len);
//}
//
//Vector3 Calc_Vector3_(Vector3 V, float angleX, float len) {
//	return Vector3(V.X + vSpoof_sin(angleX) * len, V.Y + vSpoof_cos(angleX) * len, V.Z);
//}
//
//// sin”‡œ“ cos’˝œ“
//void DrawGrenadeRange_2D(Vector3 vPosition, float Range, FLinearColor Color) {
//	Vector2 A, P1, P2;
//	Vector3 Buff = Calc_Vector3_(vPosition, 0, Range);
//	//SDK::WorldToScreen(Buff, &P1);
//	for (int i = 0; i < G. ÷¿◊∑∂Œßi; i++) {
//		//SDK::WorldToScreen(Calc_Vector3_(vPosition, i * (360 / G. ÷¿◊∑∂Œßi), Range), &P2);
//		//Renderer::DrawLine(P1.X, P1.Y, P2.X, P2.Y, Color, 2.F);
//		P1 = P2;
//	}
//}
//
//void DrawGrenadeRange_3D(Vector3 vPosition, float Range, FLinearColor Color) {
//	Vector2 A, P1, P2;
//	for (int i = 0; i < G. ÷¿◊∑∂Œßi; i++) {
//		for (int j = 0; j < G. ÷¿◊∑∂Œßi; j++) {
//			A.X = j * (360 / G. ÷¿◊∑∂Œßi); A.Y = i * (360 / G. ÷¿◊∑∂Œßi);
//			//SDK::WorldToScreen(Calc_Vector3_(vPosition, A, Range), &P2);
//			A.X = (j + 1) * (360 / G. ÷¿◊∑∂Œßi); A.Y = (i + 1) * (360 / G. ÷¿◊∑∂Œßi);
//			//SDK::WorldToScreen(Calc_Vector3_(vPosition, A, Range), &P1);
//			//Renderer::DrawLine(P1.X, P1.Y, P2.X, P2.Y, Color, 0.35F);
//		}
//	}
//}
