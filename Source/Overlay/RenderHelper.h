#pragma once
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include "Texture.h"

namespace RenderHelper {
	inline ImU32 GetColorForNumber(int number) {
		switch (number) {
		case 1:  return IM_COL32(247, 248, 19, 255);    // Yellow
		case 2:  return IM_COL32(250, 127, 73, 255);    // Orange
		case 3:  return IM_COL32(90, 198, 227, 255);    // Light Blue
		case 4:  return IM_COL32(90, 189, 77, 255);     // Green
		case 5:  return IM_COL32(225, 99, 120, 255);    // Pink
		case 6:  return IM_COL32(115, 129, 168, 255);   // Purple
		case 7:  return IM_COL32(159, 126, 105, 255);   // Indigo
		case 8:  return IM_COL32(255, 134, 200, 255);   // Light Cyan
		case 9:  return IM_COL32(210, 224, 191, 255);   // Pale Green
		case 10: return IM_COL32(154, 52, 142, 255);    // Violet
		case 11: return IM_COL32(98, 146, 158, 255);       // Red
		case 12: return IM_COL32(226, 214, 239, 255);       // Green
		case 13: return IM_COL32(4, 167, 119, 255);       // Blue
		case 14: return IM_COL32(115, 113, 252, 255);     // Yellow
		case 15: return IM_COL32(255, 0, 255, 255);     // Magenta
		case 16: return IM_COL32(93, 46, 140, 255);     // Cyan
		case 17: return IM_COL32(0, 255, 0, 255);       // Lime
		case 18: return IM_COL32(0, 0, 255, 255);       // Blue
		case 19: return IM_COL32(255, 165, 0, 255);     // Orange
		case 20: return IM_COL32(128, 0, 128, 255);     // Purple
		case 21: return IM_COL32(255, 192, 203, 255);   // Pink
		case 22: return IM_COL32(128, 128, 0, 255);     // Olive
		case 23: return IM_COL32(255, 215, 0, 255);     // Gold
		case 24: return IM_COL32(75, 0, 130, 255);      // Indigo
		case 25: return IM_COL32(0, 191, 255, 255);     // Deep Sky Blue
		case 26: return IM_COL32(255, 105, 180, 255);   // Hot Pink
		case 27: return IM_COL32(139, 69, 19, 255);     // Saddle Brown
		case 28: return IM_COL32(220, 20, 60, 255);     // Crimson
		case 29: return IM_COL32(0, 255, 127, 255);     // Spring Green
		case 30: return IM_COL32(0, 250, 154, 255);     // Medium Spring Green
		case 31: return IM_COL32(72, 61, 139, 255);     // Dark Slate Blue
		case 32: return IM_COL32(143, 188, 143, 255);   // Dark Sea Green
		case 33: return IM_COL32(178, 34, 34, 255);     // Firebrick
		case 34: return IM_COL32(153, 50, 204, 255);    // Dark Orchid
		case 35: return IM_COL32(233, 150, 122, 255);   // Dark Salmon
		case 36: return IM_COL32(148, 0, 211, 255);     // Dark Violet
		case 37: return IM_COL32(95, 158, 160, 255);    // Cadet Blue
		case 38: return IM_COL32(127, 255, 212, 255);   // Aquamarine
		case 39: return IM_COL32(218, 112, 214, 255);   // Orchid
		case 40: return IM_COL32(244, 164, 96, 255);    // Sandy Brown
		case 41: return IM_COL32(210, 105, 30, 255);    // Chocolate
		case 42: return IM_COL32(222, 184, 135, 255);   // Burlywood
		case 43: return IM_COL32(255, 228, 181, 255);   // Moccasin
		case 44: return IM_COL32(255, 239, 213, 255);   // Papaya Whip
		case 45: return IM_COL32(175, 238, 238, 255);   // Pale Turquoise
		case 46: return IM_COL32(100, 149, 237, 255);   // Cornflower Blue
		case 47: return IM_COL32(219, 112, 147, 255);   // Pale Violet Red
		case 48: return IM_COL32(173, 216, 230, 255);   // Light Blue
		case 49: return IM_COL32(240, 128, 128, 255);   // Light Coral
		case 50: return IM_COL32(255, 248, 220, 255);   // Cornsilk
		default: return IM_COL32(102, 102, 102, 255);   // Gray
		}
	}

	ImColor GetTeamColor(int TeamID)
	{
		switch (TeamID)
		{
		case 0:
			return ImColor(247, 174, 9);
		case 1:
			return ImColor(5, 179, 250);
		case 2:
			return ImColor(124, 4, 251);
		case 3:
			return ImColor(252, 61, 250);
		case 4:
			return ImColor(252, 63, 38);
		}
		return ImColor(0, 229, 255);
	}

	struct PlayerColor {
		ImColor infoUseColor;
		ImColor skeletonUseColor;
		bool isUseTeamNumberColor;
		ImColor teamNumberColor;
	};

	inline PlayerColor GetPlayerColor(const Player player)
	{
		auto teamNumberColor = GetColorForNumber(player.TeamID);
		bool isUseTeamNumberColor = false;
		auto infoColor = GameData.Config.ESP.Color.Default.Info;
		auto skeletonColor = GameData.Config.ESP.Color.Default.Skeleton;

		if (player.Health == 0 and player.GroggyHealth <= 100)
		{
			infoColor = GameData.Config.ESP.Color.Groggy.Info;
			skeletonColor = GameData.Config.ESP.Color.Groggy.Skeleton;
		}
		else if (player.ListType == 1)
		{
			infoColor = GameData.Config.ESP.Color.Blacklist.Info;
			skeletonColor = GameData.Config.ESP.Color.Blacklist.Skeleton;
		}
		else if (player.ListType == 2)
		{
			infoColor = GameData.Config.ESP.Color.Whitelist.Info;
			skeletonColor = GameData.Config.ESP.Color.Whitelist.Skeleton;
		}
		else if (player.PartnerLevel > 0)
		{
			infoColor = GameData.Config.ESP.Color.Partner.Info;
			skeletonColor = GameData.Config.ESP.Color.Partner.Skeleton;
		}
		else if (player.KillCount > 4)
		{
			infoColor = GameData.Config.ESP.Color.Dangerous.Info;
			skeletonColor = GameData.Config.ESP.Color.Dangerous.Skeleton;
		}
		else if (player.Type == EntityType::AI)
		{
			infoColor = GameData.Config.ESP.Color.AI.Info;
			skeletonColor = GameData.Config.ESP.Color.AI.Skeleton;
		}
		else if (player.IsVisible && GameData.Config.ESP.VisibleCheck)
		{
			infoColor = GameData.Config.ESP.Color.Visible.Info;
			skeletonColor = GameData.Config.ESP.Color.Visible.Skeleton;
		}
		else {
			isUseTeamNumberColor = true;
		}

		auto infoUseColor = ImGui::ColorConvertFloat4ToU32(Utils::FloatToImColor(infoColor));
		auto skeletonUseColor = ImGui::ColorConvertFloat4ToU32(Utils::FloatToImColor(skeletonColor));

		PlayerColor playerColor = {
			infoUseColor,
			skeletonUseColor,
			isUseTeamNumberColor,
			teamNumberColor
		};
		return playerColor;
	}

	inline void DrawDashboardProgress(ImVec2 center, float radius, float thickness, int num_ticks, float tick_length, float progress, ImColor color)
	{
		ImDrawList* draw_list = ImGui::GetWindowDrawList();
		auto CursorScreenPos = ImGui::GetCursorScreenPos();

		center.x += CursorScreenPos.x;
		center.y += CursorScreenPos.y;

		float radiu_num = 5.0f;
		float min_angle = -PI / radiu_num; // 起始角度（弧度）
		float max_angle = PI / radiu_num; // 结束角度（弧度）

		// 调整进度条半径，使其在视觉上更接近于刻度线
		float progress_radius = radius - tick_length / 2;

		// 计算进度条覆盖的弧度范围，基于进度
		float progress_min_angle = PI / radiu_num; // 进度条起始角度保持不变
		float progress_max_angle = progress_min_angle + (-PI / (radiu_num / 2)) * progress; // 根据进度调整结束角度

		// 绘制进度条
		draw_list->PathArcTo(center, progress_radius, progress_min_angle, progress_max_angle, 100); // 使用100个分段来平滑圆弧
		draw_list->PathStroke(color, 0, tick_length - 2); // 绘制进度条，颜色为红色

		// 大刻度的长度和厚度
		float major_tick_length = tick_length; // 大刻度的长度
		float major_tick_thickness = thickness; // 大刻度的厚度

		// 计算每个大刻度的位置
		int ticks_per_major_tick = num_ticks / 4; // 因为需要在起始和结束位置之间均匀分布4个大刻度，所以我们将总刻度数分成3段

		for (int i = 0; i <= num_ticks; ++i) {
			float fraction = (float)i / (float)num_ticks;
			float angle = min_angle + (max_angle - min_angle) * fraction;

			// 判断当前刻度是否为大刻度的位置
			bool is_major_tick = i % ticks_per_major_tick == 0 || i == num_ticks;
			float current_tick_length = is_major_tick ? major_tick_length : tick_length;
			float current_thickness = is_major_tick ? major_tick_thickness : thickness;

			// 刻度的起点和终点
			ImVec2 tick_start(
				center.x + cos(angle) * (radius - current_tick_length),
				center.y + sin(angle) * (radius - current_tick_length)
			);
			ImVec2 tick_end(
				center.x + cos(angle) * radius,
				center.y + sin(angle) * radius
			);

			// 绘制刻度线
			draw_list->AddLine(tick_start, tick_end, is_major_tick ? IM_COL32(255, 255, 255, 255) : IM_COL32(255, 255, 255, 0), current_thickness);
		}

		// 绘制右半圆形的外围轮廓
		draw_list->PathArcTo(center, radius, min_angle, max_angle, num_ticks);
		draw_list->PathStroke(IM_COL32(255, 255, 255, 255), 0, thickness);
	}

	inline void DrawInvertedTriangle(ImVec2 position, float size, ImColor color) {
		ImDrawList* draw_list = ImGui::GetWindowDrawList();
		auto DrawList = ImGui::GetWindowDrawList();

		auto CursorScreenPos = ImGui::GetCursorScreenPos();
		//CursorScreenPos.x -= 8;
		//CursorScreenPos.y -= 8;

		ImVec2 p1 = ImVec2(position.x, position.y + size / 2);
		ImVec2 p2 = ImVec2(position.x + size / 2, position.y - size / 2);
		ImVec2 p3 = ImVec2(position.x - size / 2, position.y - size / 2);


		draw_list->AddTriangle(p1, p2, p3, ImColor(45, 45, 45, 220), 1.0f);

		draw_list->AddTriangleFilled(p1, p2, p3, color);
	};

	inline void Line(ImVec2 Pos1, ImVec2 Pos2, ImU32 Color, float Thickness)
	{
		auto DrawList = ImGui::GetWindowDrawList();
		auto CursorScreenPos = ImGui::GetCursorScreenPos();
		//CursorScreenPos.x -= 8;
		//CursorScreenPos.y -= 8;

		Pos1 = {
			CursorScreenPos.x + Pos1.x,
			CursorScreenPos.y + Pos1.y
		};

		Pos2 = {
			CursorScreenPos.x + Pos2.x,
			CursorScreenPos.y + Pos2.y
		};

		DrawList->AddLine(Pos1, Pos2, Color, Thickness);
	}

	inline void PolyLine(std::vector<ImVec2> Points, ImU32 Color, float Thickness)
	{
		if (Points.empty()) {
			return;
		}

		auto DrawList = ImGui::GetWindowDrawList();
		//DrawList->PathClear();

		auto CursorScreenPos = ImGui::GetCursorScreenPos();
		//CursorScreenPos.x -= 8;
		//CursorScreenPos.y -= 8;

		for (auto& Point : Points)
		{
			Point.x += CursorScreenPos.x;
			Point.y += CursorScreenPos.y;

			//DrawList->PathLineTo(Point);
		}

		//DrawList->PathStroke(Color, true, Thickness);
		DrawList->AddPolyline(Points.data(), Points.size(), Color, ImDrawFlags_None, Thickness);
	}

	void AddImageRotated(ImTextureID tex_id, ImVec2 center, ImVec2 size, float angle, bool isWindowDrawList = true) {
		ImDrawList* DrawList;

		if (!isWindowDrawList)
		{
			DrawList = ImGui::GetBackgroundDrawList();
		}
		else {
			DrawList = ImGui::GetWindowDrawList();
			auto CursorScreenPos = ImGui::GetCursorScreenPos();
			center = {
				CursorScreenPos.x + center.x,
				CursorScreenPos.y + center.y
			};
		}

		float sin_a = sinf(angle), cos_a = cosf(angle);  
		ImVec2 pos[4] = {
			ImRotate(ImVec2(-size.x * 0.5f, -size.y * 0.5f), cos_a, sin_a),
			ImRotate(ImVec2(+size.x * 0.5f, -size.y * 0.5f), cos_a, sin_a),
			ImRotate(ImVec2(+size.x * 0.5f, +size.y * 0.5f), cos_a, sin_a),
			ImRotate(ImVec2(-size.x * 0.5f, +size.y * 0.5f), cos_a, sin_a)
		};

		for (int n = 0; n < 4; n++) {
			pos[n].x += center.x;
			pos[n].y += center.y;
		}

		DrawList->AddImageQuad(tex_id, pos[0], pos[1], pos[2], pos[3]);
	}

	inline void Image(const ImTextureID& Texture, ImVec2 Pos, ImVec2 Size, bool UseColorOverlay = false, const ImU32& Color = IM_COL32(255, 255, 255, 255), bool isWindowDrawList = true)
	{
		ImDrawList* DrawList;

		if (!isWindowDrawList)
		{
			DrawList = ImGui::GetBackgroundDrawList();
		}
		else {
			DrawList = ImGui::GetWindowDrawList();
			auto CursorScreenPos = ImGui::GetCursorScreenPos();

			Pos = {
				CursorScreenPos.x + Pos.x,
				CursorScreenPos.y + Pos.y
			};
		}

		Size = ImVec2(Pos.x + Size.x, Pos.y + Size.y);
		if (UseColorOverlay)
		{
			DrawList->AddImage((void*)Texture, Pos, Size, ImVec2(0, 0), ImVec2(1, 1), Color);
		}
		else {
			DrawList->AddImage((void*)Texture, Pos, Size);
		}
	}

	inline void Circle(ImVec2 Pos, float Radius, ImColor Color, float Thickness, int Num)
	{
		auto DrawList = ImGui::GetForegroundDrawList();
		auto CursorScreenPos = ImGui::GetCursorScreenPos();
		//CursorScreenPos.x -= 8;
		//CursorScreenPos.y -= 8;

		Pos = {
			CursorScreenPos.x + Pos.x,
			CursorScreenPos.y + Pos.y
		};

		DrawList->AddCircle(Pos, Radius, Color, Num, Thickness);
	}

	inline void CircleFilled(ImVec2 Pos, float Radius, ImColor Color, int Num)
	{
		auto DrawList = ImGui::GetForegroundDrawList();
		auto CursorScreenPos = ImGui::GetCursorScreenPos();
		//CursorScreenPos.x -= 8;
		//CursorScreenPos.y -= 8;

		Pos = {
			CursorScreenPos.x + Pos.x,
			CursorScreenPos.y + Pos.y
		};

		DrawList->AddCircleFilled(Pos, Radius, Color, Num);
	}

	inline ImVec2 OSText(const char* Text, ImVec2 Pos, ImColor Color, float FontSize, bool Centered, bool AdjustHeight)
	{
		auto DrawList = ImGui::GetWindowDrawList();
		auto CursorScreenPos = ImGui::GetCursorScreenPos();
		//CursorScreenPos.x -= 8;
		//CursorScreenPos.y -= 8;

		Pos = {
			CursorScreenPos.x + Pos.x,
			CursorScreenPos.y + Pos.y
		};

		if (!Centered && !AdjustHeight)
		{
			const ImVec2 TextSize = ImGui::GetFont()->CalcTextSizeA(FontSize, FLT_MAX, 0.f, Text);
			DrawList->AddText(ImGui::GetFont(), FontSize, {Pos.x, Pos.y}, Color, Text);
			return TextSize;
		}
		else
		{
			float TextWidth = ImGui::GetFont()->CalcTextSizeA(FontSize, FLT_MAX, 0.f, Text).x;
			const ImVec2 TextSize = ImGui::GetFont()->CalcTextSizeA(FontSize, FLT_MAX, 0.f, Text);

			const auto HorizontalOffset = Centered ? TextSize.x / 2 : 0.0f;
			const auto VerticalOffset = AdjustHeight ? TextSize.y : 0.0f;

			ImVec2 Pos_ = { Pos.x - HorizontalOffset, Pos.y - VerticalOffset };
			DrawList->AddText(ImGui::GetFont(), FontSize, Pos_, Color, Text);
			return TextSize;
		}
	}

	inline ImVec2 StrokeText(const char* Text, ImVec2 Pos, ImColor Color, float FontSize, bool Centered = true, bool AdjustHeight = true)
	{
		if (GameData.Config.ESP.Stroke)
		{
			OSText(Text, ImVec2(Pos.x - 1, Pos.y + 1), ImColor(45, 45, 45, 220), FontSize, Centered, AdjustHeight);
			OSText(Text, ImVec2(Pos.x - 1, Pos.y - 1), ImColor(45, 45, 45, 220), FontSize, Centered, AdjustHeight);
			OSText(Text, ImVec2(Pos.x + 1, Pos.y + 1), ImColor(45, 45, 45, 220), FontSize, Centered, AdjustHeight);
			OSText(Text, ImVec2(Pos.x + 1, Pos.y - 1), ImColor(45, 45, 45, 220), FontSize, Centered, AdjustHeight);
		}
		return OSText(Text, Pos, Color, FontSize, Centered, AdjustHeight);
	}

	inline void DrawTriangle(ImVec2& p1, ImVec2& p2, ImVec2& p3, ImU32 col, bool filled = false) {
		ImDrawList* draw_list = ImGui::GetWindowDrawList();
		auto CursorScreenPos = ImGui::GetCursorScreenPos();

		p1.x += CursorScreenPos.x;
		p1.y += CursorScreenPos.y;

		p2.x += CursorScreenPos.x;
		p2.y += CursorScreenPos.y;

		p3.x += CursorScreenPos.x;
		p3.y += CursorScreenPos.y;

		if (filled) {
			draw_list->AddTriangleFilled(p1, p2, p3, col);
		}
		else {
			draw_list->AddTriangle(p1, p2, p3, col);
		}
	}

	inline void DrawRadarPlayerCircleWithText(const char* text, ImU32 circle_col, float radius, ImVec2 position, float angle, ECharacterIconType RadarState) {
		ImDrawList* draw_list = ImGui::GetWindowDrawList();
		auto CursorScreenPos = ImGui::GetCursorScreenPos();

		const float fontSize = radius * 1.5f;

		const ImVec2 textSize = ImGui::GetFont()->CalcTextSizeA(fontSize, FLT_MAX, 0.f, text);

		position.x += CursorScreenPos.x;
		position.y += CursorScreenPos.y;

		ImVec2 textPos = ImVec2(
			position.x - textSize.x / 2,
			position.y - textSize.y / 2
		);

		std::string IconUrl = "Assets/Icons/Radar/team03_mapplayer_arrow.png";
		if (GImGuiTextureMap[IconUrl].Width > 0) {
			ImVec2 IconPos = ImVec2(
				position.x - CursorScreenPos.x,
				position.y - CursorScreenPos.y
			);
			float IconSize = radius * 10.3f;
			RenderHelper::AddImageRotated(GImGuiTextureMap[IconUrl].Texture, IconPos, ImVec2(IconSize, IconSize), angle);
		}

		draw_list->AddCircleFilled(position, radius, circle_col, radius * 2);

		if (RadarState != ECharacterIconType::Normal)
		{
			std::string RadarStateIconUrl = "Assets/Icons/Radar/indicator_onscreen_status_vehicle.png";
			switch (RadarState)
			{
			case ECharacterIconType::Quitter:
				RadarStateIconUrl = "Assets/Icons/Radar/indicator_onscreen_status_disconnect.png";
				break;
			case ECharacterIconType::Groggy:
				RadarStateIconUrl = "Assets/Icons/Radar/indicator_onscreen_status_DBNO.png";
				break;
			case ECharacterIconType::Parachute:
				RadarStateIconUrl = "Assets/Icons/Radar/indicator_onscreen_status_parachute.png";
				break;
			default:
				break;
			}

			if (GImGuiTextureMap[RadarStateIconUrl].Width > 0) {
				ImVec2 IconPos = ImVec2(
					position.x - CursorScreenPos.x,
					position.y - CursorScreenPos.y
				);
				float IconSize = radius * 7.3f;
				if (RadarState == ECharacterIconType::Quitter) IconSize = radius * 4.f;
				RenderHelper::AddImageRotated(GImGuiTextureMap[RadarStateIconUrl].Texture, IconPos, ImVec2(IconSize, IconSize), 0);
			}
		}
		else {
			draw_list->AddText(ImGui::GetFont(), fontSize, ImVec2(textPos.x - 1, textPos.y + 1), ImColor(45, 45, 45, 220), text);
			draw_list->AddText(ImGui::GetFont(), fontSize, ImVec2(textPos.x - 1, textPos.y - 1), ImColor(45, 45, 45, 220), text);
			draw_list->AddText(ImGui::GetFont(), fontSize, ImVec2(textPos.x + 1, textPos.y + 1), ImColor(45, 45, 45, 220), text);
			draw_list->AddText(ImGui::GetFont(), fontSize, ImVec2(textPos.x + 1, textPos.y - 1), ImColor(45, 45, 45, 220), text);
			draw_list->AddText(ImGui::GetFont(), fontSize, textPos, IM_COL32_WHITE, text);
		}
	}

	inline void DrawRadarPlayerCircleWithText(const char* text, ImU32 circle_col, float radius, ImVec2 position, float angle) {
		ImDrawList* draw_list = ImGui::GetWindowDrawList();
		auto CursorScreenPos = ImGui::GetCursorScreenPos();

		const float fontSize = radius * 1.5f;

		const ImVec2 textSize = ImGui::GetFont()->CalcTextSizeA(fontSize, FLT_MAX, 0.f, text);

		position.x += CursorScreenPos.x;
		position.y += CursorScreenPos.y;

		ImVec2 textPos = ImVec2(
			position.x - textSize.x / 2,
			position.y - textSize.y / 2
		);

		draw_list->AddCircleFilled(position, radius, circle_col, radius * 2);
	    draw_list->AddText(ImGui::GetFont(), fontSize, ImVec2(textPos.x - 1, textPos.y + 1), ImColor(45, 45, 45, 220), text);
	    draw_list->AddText(ImGui::GetFont(), fontSize, ImVec2(textPos.x - 1, textPos.y - 1), ImColor(45, 45, 45, 220), text);
	    draw_list->AddText(ImGui::GetFont(), fontSize, ImVec2(textPos.x + 1, textPos.y + 1), ImColor(45, 45, 45, 220), text);
	    draw_list->AddText(ImGui::GetFont(), fontSize, ImVec2(textPos.x + 1, textPos.y - 1), ImColor(45, 45, 45, 220), text);
	    draw_list->AddText(ImGui::GetFont(), fontSize, textPos, IM_COL32_WHITE, text);

	}


    inline ImVec2 Text(const char* text, ImVec2 pos, ImU32 color = IM_COL32(255, 255, 255, 255), int size = 14, bool centered = true, bool adjustHeight = true, bool isWindowDrawList = true) noexcept
    {
        //const auto textSize = ImGui::CalcTextSize(text);
		const ImVec2 textSize = ImGui::GetFont()->CalcTextSizeA(size, FLT_MAX, 0.f, text);

        const auto horizontalOffset = centered ? textSize.x / 2 : 0.0f;
        const auto verticalOffset = adjustHeight ? textSize.y : 0.0f;

        unsigned int uintColor = color;
        unsigned int alphaOnlyColor = uintColor & IM_COL32_A_MASK;

		ImDrawList* DrawList;
		if (!isWindowDrawList)
		{
			DrawList = ImGui::GetBackgroundDrawList();
		}
		else {
			DrawList = ImGui::GetWindowDrawList();
			auto CursorScreenPos = ImGui::GetCursorScreenPos();
			//CursorScreenPos.x -= 8;
			//CursorScreenPos.y -= 8;

			pos = {
				CursorScreenPos.x + pos.x,
				CursorScreenPos.y + pos.y,
			};
		}

		DrawList->AddText(ImGui::GetFont(), size, { pos.x - horizontalOffset + 1.0f, pos.y - verticalOffset + 1.0f }, uintColor & IM_COL32_A_MASK, text);
		DrawList->AddText(ImGui::GetFont(), size, { pos.x - horizontalOffset, pos.y - verticalOffset }, color, text);

        return textSize;
    }
};

