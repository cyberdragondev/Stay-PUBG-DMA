#pragma once
#include <vector>
#include <memory>
#include "../../../IGameMap/IGameMap.h"
#include "../../../ImageAllocator/ImageAllocator.h"
namespace DMARender {
	class MapManager {
		std::vector<std::shared_ptr<IGameMap>> maps;
		std::shared_ptr<ImageAllocator> img = nullptr;
		ID3D11Device** g_pd3dDevice;
		int selectedIndex = -1;
	public:
		MapManager(ID3D11Device** g_pd3dDevice);
		void addMap(std::shared_ptr<IGameMap> mp);
		std::vector<std::shared_ptr<IGameMap>> getMaps();
		void selectMap(int index);
		void clearMap();
		std::shared_ptr<IGameMap> getSelectedGameMap();
		bool isMapSelected();
		std::shared_ptr<ImageAllocator> getSelectedAllocator();
	};
}