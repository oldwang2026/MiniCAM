// MIniCamCore.cpp: 定义应用程序的入口点。
//

#include "GeoTypes.h"
#include <vector>
#include <iostream>
#include "BoundingBox.h"
#include "STLReader.h"
#include "Part.h"
#include <string>
#include <filesystem>

int main()
{
	std::cout << "MiniCAM Day 4" << std::endl;


	std::filesystem::path rootPath(PROJECT_ROOT_DIR);
	std::filesystem::path fullPath = rootPath / "stl" / "batman.stl";

	
	Part STLPart(fullPath.string());

	std::cout << "The num of triangles is " << STLPart.GetTriangleCount() << std::endl;
	std::cout << "The boundingbox center point is " << STLPart.GetBoundingBox().GetCenterPoint().x << "," 
													<< STLPart.GetBoundingBox().GetCenterPoint().y << "," 
													<< STLPart.GetBoundingBox().GetCenterPoint().z << std::endl;

	return 0;
}
