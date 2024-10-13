#pragma once

#include <windows.h>
#include "common/Data.h"
#include "common/VectorHelper.h"
#include "RenderHelper.h"
#include <imgui/imgui.h>

class HealthBar
{
private:
	using TimePoint_ = std::chrono::steady_clock::time_point;
private:
	const int ShowBackUpHealthDuration = 500;
	float MaxHealth = 0.f;
	float CurrentHealth = 0.f;
	float LastestBackupHealth = 0.f;
	ImVec2 RectPos{};
	ImVec2 RectSize{};
	bool InShowBackupHealth = false;
	TimePoint_ BackupHealthTimePoint{};
public:
	HealthBar() {}
	void DrawHealthBar_Horizontal(float MaxHealth, float CurrentHealth, ImVec2 Pos, ImVec2 Size, ImColor UseColor, bool InShowBackupHealth = true);
	void DrawHealthBar_Vertical(float MaxHealth, float CurrentHealth, ImVec2 Pos, ImVec2 Size, ImColor UseColor, bool InShowBackupHealth = true);
private:
	ImColor Mix(ImColor Col_1, ImColor Col_2, float t);
	ImColor FirstStageColor = ImColor(96, 246, 113, 220);
	ImColor SecondStageColor = ImColor(247, 214, 103, 220);
	ImColor ThirdStageColor = ImColor(255, 95, 95, 220);
	ImColor BackupHealthColor = ImColor(255, 255, 255, 220);
	ImColor FrameColor = ImColor(45, 45, 45, 220);
	ImColor BackGroundColor = ImColor(90, 90, 90, 0);
};

ImColor HealthBar::Mix(ImColor Col_1, ImColor Col_2, float t)
{
	ImColor Col;
	Col.Value.x = t * Col_1.Value.x + (1 - t) * Col_2.Value.x;
	Col.Value.y = t * Col_1.Value.y + (1 - t) * Col_2.Value.y;
	Col.Value.z = t * Col_1.Value.z + (1 - t) * Col_2.Value.z;
	Col.Value.w = Col_1.Value.w;
	return Col;
}

void HealthBar::DrawHealthBar_Horizontal(float MaxHealth, float CurrentHealth, ImVec2 Pos, ImVec2 Size, ImColor UseColor, bool ShowBackupHealth)
{
	auto InRange = [&](float value, float min, float max) -> bool
	{
		return value > min && value <= max;
	};

	auto DrawList = ImGui::GetWindowDrawList();
	auto CursorScreenPos = ImGui::GetCursorScreenPos();
	/*CursorScreenPos.x -= 8;
	CursorScreenPos.y -= 8;*/

	Pos = {
			CursorScreenPos.x + Pos.x,
			CursorScreenPos.y + Pos.y
	};

	this->MaxHealth = MaxHealth;
	this->CurrentHealth = CurrentHealth;
	this->RectPos = Pos;
	this->RectSize = Size;

	float Proportion = CurrentHealth / MaxHealth;
	float Width = RectSize.x * Proportion;
	ImColor Color;
	float Rounding = 1.0f;

	DrawList->AddRectFilled(RectPos,
		{ RectPos.x + RectSize.x,RectPos.y + RectSize.y },
		BackGroundColor, Rounding, 15);

	float Color_Lerp_t = pow(Proportion, Rounding / 2);
	if (InRange(Proportion, 0.5, 1))
		Color = Mix(FirstStageColor, SecondStageColor, Color_Lerp_t * 3 - 1);
	else
		Color = Mix(SecondStageColor, ThirdStageColor, Color_Lerp_t * 4);

	if (ShowBackupHealth)
	{
		if (LastestBackupHealth == 0
			|| LastestBackupHealth < CurrentHealth)
			LastestBackupHealth = CurrentHealth;

		if (LastestBackupHealth != CurrentHealth)
		{
			if (!InShowBackupHealth)
			{
				BackupHealthTimePoint = std::chrono::steady_clock::now();
				InShowBackupHealth = true;
			}

			std::chrono::steady_clock::time_point CurrentTime = std::chrono::steady_clock::now();
			if (CurrentTime - BackupHealthTimePoint > std::chrono::milliseconds(ShowBackUpHealthDuration))
			{
				LastestBackupHealth = CurrentHealth;
				InShowBackupHealth = false;
			}

			if (InShowBackupHealth)
			{
				float BackupHealthWidth = LastestBackupHealth / MaxHealth * RectSize.x;
				float BackupHealthColorAlpha = 1 - 0.95 * (std::chrono::duration_cast<std::chrono::milliseconds>(CurrentTime - BackupHealthTimePoint).count() / (float)ShowBackUpHealthDuration);
				ImColor BackupHealthColorTemp = BackupHealthColor;
				BackupHealthColorTemp.Value.w = BackupHealthColorAlpha;
				float BackupHealthWidth_Lerp = 1 * (std::chrono::duration_cast<std::chrono::milliseconds>(CurrentTime - BackupHealthTimePoint).count() / (float)ShowBackUpHealthDuration);
				BackupHealthWidth_Lerp *= (BackupHealthWidth - Width);
				BackupHealthWidth -= BackupHealthWidth_Lerp;
				DrawList->AddRectFilled(RectPos,
					{ RectPos.x + BackupHealthWidth,RectPos.y + RectSize.y },
					BackupHealthColorTemp, Rounding);
			}
		}
	}

	if (UseColor != ImColor(0, 0, 0, 0))
	{
		Color = UseColor;
	}

	DrawList->AddRectFilled(RectPos,
		{ RectPos.x + Width,RectPos.y + RectSize.y },
		Color, Rounding);

	DrawList->AddRect(RectPos,
		{ RectPos.x + RectSize.x,RectPos.y + RectSize.y },
		FrameColor, Rounding, 15, 1);
}

void HealthBar::DrawHealthBar_Vertical(float MaxHealth, float CurrentHealth, ImVec2 Pos, ImVec2 Size, ImColor UseColor, bool ShowBackupHealth)
{
	auto InRange = [&](float value, float min, float max) -> bool
	{
		return value > min && value <= max;
	};

	auto DrawList = ImGui::GetWindowDrawList();
	auto CursorScreenPos = ImGui::GetCursorScreenPos();
	//CursorScreenPos.x -= 8;
	//CursorScreenPos.y -= 8;

	Pos = {
			CursorScreenPos.x + Pos.x,
			CursorScreenPos.y + Pos.y
	};

	this->MaxHealth = MaxHealth;
	this->CurrentHealth = CurrentHealth;
	this->RectPos = Pos;
	this->RectSize = Size;

	float Proportion = CurrentHealth / MaxHealth;
	float Height = RectSize.y * Proportion;
	ImColor Color;
	float Rounding = 1.0f;

	DrawList->AddRectFilled(RectPos,
		{ RectPos.x + RectSize.x,RectPos.y + RectSize.y },
		BackGroundColor, Rounding, 15);

	float Color_Lerp_t = pow(Proportion, 2.5);
	if (InRange(Proportion, 0.5, 1))
		Color = Mix(FirstStageColor, SecondStageColor, Color_Lerp_t * 3 - 1);
	else
		Color = Mix(SecondStageColor, ThirdStageColor, Color_Lerp_t * 4);

	if (ShowBackupHealth)
	{
		if (LastestBackupHealth == 0
			|| LastestBackupHealth < CurrentHealth)
			LastestBackupHealth = CurrentHealth;

		if (LastestBackupHealth != CurrentHealth)
		{
			if (!InShowBackupHealth)
			{
				BackupHealthTimePoint = std::chrono::steady_clock::now();
				InShowBackupHealth = true;
			}

			std::chrono::steady_clock::time_point CurrentTime = std::chrono::steady_clock::now();
			if (CurrentTime - BackupHealthTimePoint > std::chrono::milliseconds(ShowBackUpHealthDuration))
			{
				LastestBackupHealth = CurrentHealth;
				InShowBackupHealth = false;
			}

			if (InShowBackupHealth)
			{
				float BackupHealthHeight = LastestBackupHealth / MaxHealth * RectSize.y;
				float BackupHealthColorAlpha = 1 - 0.95 * (std::chrono::duration_cast<std::chrono::milliseconds>(CurrentTime - BackupHealthTimePoint).count() / (float)ShowBackUpHealthDuration);
				ImColor BackupHealthColorTemp = BackupHealthColor;
				BackupHealthColorTemp.Value.w = BackupHealthColorAlpha;
				float BackupHealthHeight_Lerp = 1 * (std::chrono::duration_cast<std::chrono::milliseconds>(CurrentTime - BackupHealthTimePoint).count() / (float)ShowBackUpHealthDuration);
				BackupHealthHeight_Lerp *= (BackupHealthHeight - Height);
				BackupHealthHeight -= BackupHealthHeight_Lerp;
				DrawList->AddRectFilled({ RectPos.x,RectPos.y + RectSize.y - BackupHealthHeight },
					{ RectPos.x + RectSize.x,RectPos.y + RectSize.y },
					BackupHealthColorTemp, Rounding);
			}
		}
	}

	if (UseColor != ImColor(0, 0, 0, 0))
	{
		Color = UseColor;
	}

	DrawList->AddRectFilled({ RectPos.x,RectPos.y + RectSize.y - Height },
		{ RectPos.x + RectSize.x,RectPos.y + RectSize.y },
		Color, Rounding);

	DrawList->AddRect(RectPos,
		{ RectPos.x + RectSize.x,RectPos.y + RectSize.y },
		FrameColor, Rounding, 15, 1);
}

