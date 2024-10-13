#pragma once
#include "../IGameMap/IGameMap.h"
#include "../RenderWindow/MapTransform.h"
#include <imgui/imgui.h>
#include <vector>
#include <numbers>
namespace DMARender {
	class IRadar {
	protected:
		ImVec2 WorldToRadar(IGameMap* curMap, const MapTransform& mTransform, Vector3 gamePos);
		void drawBlip(const ImVec2& screenPos, const float& size, const ImU32& color, float fontSize, float borderSize = 1.0f, const std::vector<std::string>& text = {});
		void drawBlipDirectional(const ImVec2& screenPos, const float& size, const ImU32& color, float fontSize, float borderSize = 1.0f, const std::vector<std::string>& text = {}, float direction = 0.0f);
		void drawOutlinedText(std::string text, const ImVec2& screenPos, const float& size, const ImU32& color);
	public:
		virtual void DrawOverlay(IGameMap* curMap, const MapTransform& mTransform) = 0;
		virtual void createFonts() {};

	};
}