#include "IRadar.h"
#include <vector>
ImVec2 DMARender::IRadar::WorldToRadar(IGameMap* curMap, const MapTransform& mTransform, Vector3 gamePos)
{
    //Get point on image
    ImVec2 imagePos = curMap->translatePoint(gamePos);

    //Apply zoom + offset transformations
    imagePos.x *= mTransform.mapZoom;
    imagePos.y *= mTransform.mapZoom;

    imagePos.x += mTransform.dragOffsetX;
    imagePos.y += mTransform.dragOffsetY;

    return imagePos;
}

void DMARender::IRadar::drawBlip(const ImVec2& screenPos, const float& size, const ImU32& color, float fontSize, float borderSize, const std::vector<std::string>& text)
{
    ImDrawList* bgDraw = ImGui::GetBackgroundDrawList();
    
    if(borderSize > 0)
        bgDraw->AddCircleFilled(screenPos, size, IM_COL32_BLACK, 16);
    bgDraw->AddCircleFilled(screenPos, size - borderSize, color, 16);
    float textSize = ImGui::GetTextLineHeight();
    for (int i = 0; i < text.size(); i++) {

        float textY = screenPos.y - (fontSize/2) - (i * fontSize);
        float textX = screenPos.x + size + 2;

        drawOutlinedText(text[i], ImVec2(textX, textY), fontSize, color);
    }
}

void DMARender::IRadar::drawBlipDirectional(const ImVec2& screenPos, const float& size, const ImU32& color, float fontSize, float borderSize, const std::vector<std::string>& text, float direction)
{
    drawBlip(screenPos, size, color, fontSize, borderSize, text);
    ImDrawList* bgDraw = ImGui::GetBackgroundDrawList();

    bgDraw->AddLine(screenPos, ImVec2(screenPos.x + sinf(direction * (std::numbers::pi / 180.0f)) * 35, screenPos.y + cosf(direction * (std::numbers::pi / 180.0f)) * 35), IM_COL32_WHITE, 3.0f);
}

void DMARender::IRadar::drawOutlinedText(std::string text, const ImVec2& screenPos, const float& size, const ImU32& color)
{
    ImDrawList* bgDraw = ImGui::GetBackgroundDrawList();

    bgDraw->AddText(ImGui::GetFont(), size, ImVec2(screenPos.x - 1, screenPos.y), IM_COL32_BLACK, text.c_str());
    bgDraw->AddText(ImGui::GetFont(), size, ImVec2(screenPos.x + 1, screenPos.y), IM_COL32_BLACK, text.c_str());
    bgDraw->AddText(ImGui::GetFont(), size, ImVec2(screenPos.x, screenPos.y - 1), IM_COL32_BLACK, text.c_str());
    bgDraw->AddText(ImGui::GetFont(), size, ImVec2(screenPos.x, screenPos.y + 1), IM_COL32_BLACK, text.c_str());

    bgDraw->AddText(ImGui::GetFont(), size, screenPos, color, text.c_str());
}
