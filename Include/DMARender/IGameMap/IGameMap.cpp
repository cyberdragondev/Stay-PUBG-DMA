#include "IGameMap.h"

DMARender::IGameMap::IGameMap(std::string name, std::string filePath)
{
	this->name = name;
	this->filePath = filePath;
}

std::string DMARender::IGameMap::getName()
{
	return name;
}

std::string DMARender::IGameMap::getFilePath()
{
	return filePath;
}
