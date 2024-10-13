#pragma once
#include <DMALibrary/Memory/Memory.h>
#include <Common/Data.h>
#include <Common/Entitys.h>
#include <Utils/Utils.h>
#include <Utils/Throttler.h>
#include <Hack/GNames.h>
#include <Hack/Decrypt.h>

namespace LineTraceHook
{
	typedef struct _BoneInfo {
		FVector BonePos;
		bool Visibility;
	}BoneInfo, * PBoneInfo;
	typedef struct _ShellCodePrarm {
		uint64_t SPoofcall;
		uint64_t LineTraceSingle;
		uint64_t Uworld;
		uint64_t Actors;
		uint64_t IsloopOk;
		FVector SrartPos;
		BoneInfo Bones[28];
	}ShellCodePrarm, * PShellCodePrarm;


	void StartHook()
	{
		
	}

	void EndHook()
	{
		//这里是漏打的我删了的给你讲清楚
			
	}

	bool GetLocation(const Player& TargetCharacter, const EBoneIndex& FirstBoneIndex, EBoneIndex* VisibilityBoneIndex)
	{
		return true;
	}
}


namespace Function
{
	void Function1(ULONG64 AcknowledgedPawn, ULONG64 MyPlayerAddress)
	{

		


	}

}