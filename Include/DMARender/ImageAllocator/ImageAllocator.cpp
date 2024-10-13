#include "ImageAllocator.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

bool DMARender::ImageAllocator::LoadTextureFromFile(const char* filename, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height)
{
    // Load from disk into a raw RGBA buffer
    int image_width = 0;
    int image_height = 0;
    unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
    if (image_data == NULL)
        return false;

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
    if (pTexture == NULL)
        return false;
    g_pd3dDevice->CreateShaderResourceView(pTexture, &srvDesc, out_srv);
    pTexture->Release();

    *out_width = image_width;
    *out_height = image_height;
    stbi_image_free(image_data);

    return true;
}

bool DMARender::ImageAllocator::loadImage()
{
    return LoadTextureFromFile(filePath.c_str(), &texture, &image_width, &image_height);
}

DMARender::ImageAllocator::ImageAllocator(ID3D11Device* g_pd3dDevice, std::string filePath)
{
    this->filePath = filePath;
    this->g_pd3dDevice = g_pd3dDevice;
}

DMARender::ImageAllocator::~ImageAllocator()
{
    freeImage();
}

ID3D11ShaderResourceView* DMARender::ImageAllocator::getImage()
{
    if (texture == nullptr) {
        if (!loadImage())
            return nullptr;
    }
    return texture;
}

int DMARender::ImageAllocator::getWidth()
{
    if (texture == nullptr)
        if(!loadImage())
            return 0;
    return image_width;
}


int DMARender::ImageAllocator::getHeight()
{
    if (texture == nullptr)
        if(!loadImage())
            return 0;
    return image_height;
}

void DMARender::ImageAllocator::freeImage()
{
    if (texture != nullptr) {
        texture->Release();
        texture = nullptr;
    }
}

