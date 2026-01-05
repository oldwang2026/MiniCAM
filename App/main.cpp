// MIniCamCore.cpp: 定义应用程序的入口点。
//

#include "BoundingBox.h"
#include "GeoTypes.h"
#include "Part.h"
#include "STLReader.h"
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

int main()
{
	std::cout << "MiniCAM Day 5" << std::endl;


	std::filesystem::path rootPath(PROJECT_ROOT_DIR);
	std::filesystem::path fullPath = rootPath / "stl" / "cubic.stl";

	if (!std::filesystem::exists(fullPath))
	{
		std::cerr << "[Error] File does not exist: " << fullPath << std::endl;
		return -1; // 直接退出或报错
	}

	Part STLPart(fullPath.string());

	std::cout << "The num of triangles is " << STLPart.GetTriangleCount() << std::endl;
	std::cout << "The boundingbox center point is " << STLPart.GetBoundingBox().GetCenterPoint().x << "," 
													<< STLPart.GetBoundingBox().GetCenterPoint().y << "," 
													<< STLPart.GetBoundingBox().GetCenterPoint().z << std::endl;
	std::cout << "The num of unique vectices is " << STLPart.GetVertexCount();

	return 0;
}
