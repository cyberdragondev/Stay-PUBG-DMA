#pragma once
#include "stb_image.h"
#include <string>
#include <d3d11.h>

namespace DMARender {
	class ImageAllocator {
		std::string filePath;
		ID3D11Device* g_pd3dDevice;
		bool LoadTextureFromFile(const char* filename, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height);
		ID3D11ShaderResourceView* texture = nullptr;
		int image_width = 0;
		int image_height = 0;
		bool loadImage();
	public:
		ImageAllocator(ID3D11Device* g_pd3dDevice, std::string filePath);
		~ImageAllocator();
		ID3D11ShaderResourceView* getImage();
		int getWidth();
		int getHeight();
		void freeImage();
	};
}