#include "IOverlay.h"

bool DMARender::IOverlay::WorldToScreen(const _D3DMATRIX& view_matrix, const DMARender::Vector3& position, DMARender::Vector2& outScreenPos, const float& renderWidth, const float& renderHeight)
{
	DMARender::Vector3 transform = { view_matrix._14, view_matrix._24, view_matrix._34 };
	DMARender::Vector3 right = { view_matrix._11, view_matrix._21, view_matrix._31 };
	DMARender::Vector3 up = { view_matrix._12, view_matrix._22, view_matrix._32 };

	float w = transform.Dot(position) + view_matrix._44;

	if (w < 0.099f)
		return false;

	float x = right.Dot(position) + view_matrix._41;
	float y = up.Dot(position) + view_matrix._42;

	outScreenPos.x = (renderWidth / 2) * (1.f + x / w);
	outScreenPos.y = (renderHeight / 2) * (1.f - y / w);

	return true;
}

void DMARender::IOverlay::drawBoundingBox(const Vector2& top, const Vector2& bottom, float width, const ImU32& color) {

	auto drawList = ImGui::GetWindowDrawList();
	auto p = ImGui::GetCursorScreenPos();

	ImVec2 tmpLineOrder[5] = {
			ImVec2(p.x + top.x + width / 2, p.y + top.y),
			ImVec2(p.x + bottom.x + width / 2, p.y + bottom.y),
			ImVec2(p.x + bottom.x - width / 2, p.y + bottom.y),
			ImVec2(p.x + top.x - width / 2, p.y + top.y),
			ImVec2(p.x + top.x + width / 2, p.y + top.y)
	};

	drawList->AddPolyline(tmpLineOrder, 5, color, 0, 1);
}

void DMARender::IOverlay::drawFilledCircle(const Vector2& point, const float& radius, const ImU32& color) {
	auto drawList = ImGui::GetWindowDrawList();
	auto p = ImGui::GetCursorScreenPos();
	drawList->AddCircleFilled(ImVec2(p.x + point.x, p.y + point.y), radius, color, 16);
}

void DMARender::IOverlay::drawText(const std::string& text, const Vector2& point, const float& size, const ImU32& color) {
	auto drawList = ImGui::GetWindowDrawList();
	auto p = ImGui::GetCursorScreenPos();
	drawList->AddText(ImGui::GetFont(), size, ImVec2(p.x + point.x, p.y + point.y), color, text.c_str());

}

void DMARender::IOverlay::drawTextList(const std::vector<std::string>& strings, const Vector2& pos, const float& size, const ImU32& color) {
	int offsetCounter = 0;
	auto drawList = ImGui::GetWindowDrawList();
	auto p = ImGui::GetCursorScreenPos();
	for (const std::string& str : strings) {
		drawList->AddText(ImGui::GetFont(), size, ImVec2(p.x + pos.x, p.y + pos.y + offsetCounter), color, str.c_str());
		offsetCounter += size;
	}
}