#pragma once
#define NOMINMAX

#include <windows.h>
#include <algorithm>
#include <iostream>
#include "Data.h"
#include "VectorHelper.h"
#include <Utils/Engine.h>
#include <Utils/ue4math/matrix.h>

FVector VectorHelper::RotateVector(const FMatrix& RotationMatrix, const FVector& Vec) {
	FVector AxisX = RotationMatrix.GetScaledAxisX();
	FVector AxisY = RotationMatrix.GetScaledAxisY();
	FVector AxisZ = RotationMatrix.GetScaledAxisZ();

	return FVector{
		Vec.X * AxisX.X + Vec.Y * AxisY.X + Vec.Z * AxisZ.X,
		Vec.X * AxisX.Y + Vec.Y * AxisY.Y + Vec.Z * AxisZ.Y,
		Vec.X * AxisX.Z + Vec.Y * AxisY.Z + Vec.Z * AxisZ.Z
	};
}

FVector VectorHelper::GetBoneWithRotation(FTransform BoneArray, FTransform ComponentToWorld)
{
	FVector& Bone = BoneArray.Translation;
	if (std::max(std::max(abs(Bone.X), abs(Bone.Y)), abs(Bone.Z)) >= 500)
	{
		return FVector(INFINITY, INFINITY, INFINITY);
	}
	FMatrix Matrix = BoneArray.ToMatrixWithScale() * ComponentToWorld.ToMatrixWithScale();
	return FVector(Matrix._41, Matrix._42, Matrix._43);
}

FVector2D VectorHelper::WorldToScreen(const FVector& WorldLocation) {
	FVector2D ScreenLocation;

	FMatrix RotationMatrix = GameData.Camera.Rotation.GetMatrix();

	FVector AxisX = RotationMatrix.GetScaledAxisX();
	FVector AxisY = RotationMatrix.GetScaledAxisY();
	FVector AxisZ = RotationMatrix.GetScaledAxisZ();

	FVector vDelta(WorldLocation - GameData.Camera.Location);
	FVector vTransformed(vDelta | AxisY, vDelta | AxisZ, vDelta | AxisX);

	if (vTransformed.Z == 0.0f)
		vTransformed.Z = -0.001f;

	auto VieW = vTransformed.Z;

	if (vTransformed.Z < 0.0f)
		vTransformed.Z = -vTransformed.Z;

	float ScreenCenterX = GameData.Config.Overlay.ScreenWidth / 2.0f;
	float ScreenCenterY = GameData.Config.Overlay.ScreenHeight / 2.0f;
	float TangentFOV = tanf(ConvertToRadians(GameData.Camera.FOV / 2.0f));

	ScreenLocation.X = (ScreenCenterX + vTransformed.X * (ScreenCenterX / TangentFOV) / vTransformed.Z);
	ScreenLocation.Y = (ScreenCenterY - vTransformed.Y * (ScreenCenterX / TangentFOV) / vTransformed.Z);

	if (VieW != INFINITY && VieW > 0.0f)
		return ScreenLocation;
	return FVector2D(INFINITY, INFINITY);
}

bool VectorHelper::IsInScreen(const FVector2D WorldToScreen) {
	if ((WorldToScreen.X < -100 || WorldToScreen.X > GameData.Config.Overlay.ScreenWidth + 100 || WorldToScreen.Y < -100 || WorldToScreen.Y > GameData.Config.Overlay.ScreenHeight + 100))
	{
		return false;
	}
	return true;
}

bool VectorHelper::WorldToScreen(FVector Position, FVector2D& Screen, D3DMATRIX ViewMatrix)
{
	float ScreenW = (ViewMatrix._14 * Position.X) + (ViewMatrix._24 * Position.Y) + (ViewMatrix._34 * Position.Z + ViewMatrix._44);
	if (ScreenW < 0.0001f) return FALSE;

	ScreenW = 1 / ScreenW;
	float SightX = GameData.Config.Overlay.ScreenWidth / 2;
	float SightY = GameData.Config.Overlay.ScreenHeight / 2;

	Screen.X = (SightX + (ViewMatrix._11 * Position.X + ViewMatrix._21 * Position.Y + ViewMatrix._31 * Position.Z + ViewMatrix._41) * ScreenW * SightX);
	Screen.Y = (SightY - (ViewMatrix._12 * Position.X + ViewMatrix._22 * Position.Y + ViewMatrix._32 * Position.Z + ViewMatrix._42) * ScreenW * SightY);

	return TRUE;
}

bool VectorHelper::MatrixToScreen(const FVector& objectCoord, FVector2D& returnCoord, const float ViewWorld[4][4]) {
	float SightX = GameData.Config.Overlay.ScreenWidth / 2;
	float SightY = GameData.Config.Overlay.ScreenHeight / 2;
	float ViewWg = ViewWorld[0][3] * objectCoord.X + ViewWorld[1][3] * objectCoord.Y + ViewWorld[2][3] * objectCoord.Z + ViewWorld[3][3];

	if (ViewWg < 0.01) {
		return false;
	}

	ViewWg = 1.0f / ViewWg;

	float BoxXg = SightX + (ViewWorld[0][0] * objectCoord.X + ViewWorld[1][0] * objectCoord.Y + ViewWorld[2][0] * objectCoord.Z + ViewWorld[3][0]) * ViewWg * SightX;
	float BoxYg = SightY - (ViewWorld[0][1] * objectCoord.X + ViewWorld[1][1] * objectCoord.Y + ViewWorld[2][1] * objectCoord.Z + ViewWorld[3][1]) * ViewWg * SightY;

	returnCoord.X = BoxXg;
	returnCoord.Y = BoxYg;

	return true;
}