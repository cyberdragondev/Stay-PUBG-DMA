#include "MapManager.h"

DMARender::MapManager::MapManager(ID3D11Device** g_pd3dDevice)
{
	this->g_pd3dDevice = g_pd3dDevice;
}

void DMARender::MapManager::addMap(std::shared_ptr<IGameMap> mp)
{
	maps.push_back(mp);
}

std::vector<std::shared_ptr<DMARender::IGameMap>> DMARender::MapManager::getMaps()
{
	return maps;
}

void DMARender::MapManager::selectMap(int index)
{
	if (index >= maps.size())
		return;
	if (index < 0)
		return;
	if (index == selectedIndex)
		return;
	this->img = std::shared_ptr<ImageAllocator>(new ImageAllocator(*g_pd3dDevice, maps[index]->getFilePath()));
	this->selectedIndex = index;
}

void DMARender::MapManager::clearMap()
{
	this->selectedIndex = -1;
	this->img = nullptr;
}

std::shared_ptr<DMARender::IGameMap> DMARender::MapManager::getSelectedGameMap()
{
	if (!isMapSelected())
		return nullptr;
	return maps[selectedIndex];
}

bool DMARender::MapManager::isMapSelected()
{
	return selectedIndex >= 0;
}

std::shared_ptr<DMARender::ImageAllocator> DMARender::MapManager::getSelectedAllocator()
{
	return img;
}
