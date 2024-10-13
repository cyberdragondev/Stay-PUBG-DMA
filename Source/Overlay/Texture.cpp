#define STB_IMAGE_IMPLEMENTATION

#include <Utils/stb_image.h>

#include "Texture.h"
#include <d3d11.h>
#include <imgui/imgui.h>
#include <unordered_map>
#include <iostream>
#include <filesystem>
#include <sstream>
#include <utils/utils.h>

std::unordered_map<std::string, ImGuiTextureInfo> GImGuiTextureMap = {};

void Texture::LoadTextures(ID3D11Device* g_pd3dDevice, const std::string folderPath, bool removeColor) {
    for (auto& file : std::filesystem::recursive_directory_iterator(folderPath)) {
        std::stringstream ss;
        ss << file;

        if (Utils::Contains(TEXTURE_EXTENSIONS, ss.str().substr(ss.str().length() - 4, 3))) {
            ImGuiTextureInfo Info;
            std::string key = ss.str().substr(1, ss.str().length() - 2);
            bool Ret = Texture::LoadTextureFromFile(g_pd3dDevice, key.c_str(), &Info.Texture, &Info.Width, &Info.Height, removeColor);
            IM_ASSERT(Ret);
            
            key = Utils::ReplaceAll(key.c_str(), "\\\\", "/");
            if (removeColor) key += "_RemoveColor";
            GImGuiTextureMap[key] = Info;
        }
    }
}

ImGuiTextureInfo Texture::LoadTexture(ID3D11Device* g_pd3dDevice, std::string path) {
    ImGuiTextureInfo Info;

    if (GImGuiTextureMap.count(path) > 0)
    {
        Info = GImGuiTextureMap[path];
    }
    else {
        bool Ret = Texture::LoadTextureFromFile(g_pd3dDevice, path.c_str(), &Info.Texture, &Info.Width, &Info.Height);
        IM_ASSERT(Ret);
        path = Utils::ReplaceAll(path.c_str(), "\\\\", "/");
        GImGuiTextureMap[path] = Info;
    }

    return Info;
}

bool Texture::LoadTextureFromFile(ID3D11Device* g_pd3dDevice, const char* filename, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height, bool removeColor)
{
    // Load from disk into a raw RGBA buffer
    int image_width = 0;
    int image_height = 0;
    unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
    if (image_data == NULL)
        return false;

    // Convert all pixels to black while preserving alpha (transparency)
    if (removeColor)
    {
        int totalPixels = image_width * image_height;
        for (int i = 0; i < totalPixels; i++)
        {
            int index = i * 4; // Each pixel has 4 components (RGBA)
            image_data[index + 0] = 255; // R
            image_data[index + 1] = 255; // G
            image_data[index + 2] = 255; // B
            // Alpha (image_data[index + 3]) remains unchanged to preserve transparency
        }
    }

    // Create texture
    D3D11_TEXTURE2D_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.Width = image_width;
    desc.Height = image_height;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    desc.CPUAccessFlags = 0;

    ID3D11Texture2D* pTexture = NULL;
    D3D11_SUBRESOURCE_DATA subResource;
    subResource.pSysMem = image_data;
    subResource.SysMemPitch = desc.Width * 4;
    subResource.SysMemSlicePitch = 0;
    g_pd3dDevice->CreateTexture2D(&desc, &subResource, &pTexture);

    // Create texture view
    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
    ZeroMemory(&srvDesc, sizeof(srvDesc));
    srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = desc.MipLevels;
    srvDesc.Texture2D.MostDetailedMip = 0;
    g_pd3dDevice->CreateShaderResourceView(pTexture, &srvDesc, out_srv);
    pTexture->Release();

    *out_width = image_width;
    *out_height = image_height;
    stbi_image_free(image_data);

    return true;
}