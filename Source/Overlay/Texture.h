#pragma once

#include <d3d11.h>
#include "imgui/imgui.h"
#include <unordered_map>
#include <iostream>
#include <filesystem>
#include <sstream>
#include "utils/utils.h"

struct ImGuiTextureInfo
{
    ID3D11ShaderResourceView* Texture;
    int Width;
    int Height;
};

extern std::unordered_map<std::string, ImGuiTextureInfo> GImGuiTextureMap;

class Texture {
public:
    static inline std::vector<std::string> TEXTURE_EXTENSIONS = { "png", "jpg", "jpeg" };

    static ImGuiTextureInfo LoadTexture(ID3D11Device* g_pd3dDevice, std::string path);

    static void LoadTextures(ID3D11Device* g_pd3dDevice, const std::string folderPath, bool removeColor = false);

    static bool LoadTextureFromFile(ID3D11Device* g_pd3dDevice, const char* filename, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height, bool removeColor = false);
};