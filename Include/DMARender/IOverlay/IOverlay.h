#pragma once
#include <d3dtypes.h>
#include "../Vectors/Vector3.h"
#include "../Vectors/Vector2.h"
#include <imgui/imgui.h>
#include <string>
#include <vector>
namespace DMARender {
	struct IOverlay
	{
	protected:
		bool WorldToScreen(const _D3DMATRIX& view_matrix, const DMARender::Vector3& position, DMARender::Vector2& outScreenPos, const float& renderWidth, const float& renderHeight);
		void drawBoundingBox(const Vector2& top, const Vector2& bottom, float width, const ImU32& color);
		void drawFilledCircle(const Vector2& point, const float& radius, const ImU32& color);
		void drawText(const std::string& text, const Vector2& point, const float& size, const ImU32& color);
		void drawTextList(const std::vector<std::string>& strings, const Vector2& pos, const float& size, const ImU32& color);
	public:
		virtual void DrawOverlay() = 0;
		virtual void createFonts() {};
	};
}


