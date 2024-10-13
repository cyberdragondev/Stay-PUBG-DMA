#pragma once
#include <string>
#include "../Vectors/Vector3.h"
#include <imgui/imgui.h>
namespace DMARender {

	class IGameMap {
		std::string name;
		std::string filePath;
	public:
		IGameMap(std::string name, std::string filePath);
		std::string getName();
		std::string getFilePath();

		virtual ImVec2 translatePoint(const Vector3& gamePoint) = 0;
	};
};
