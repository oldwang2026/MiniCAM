// MIniCamCore.cpp: 定义应用程序的入口点。
//

#include "GeoTypes.h"
#include <vector>
#include <iostream>
#include "BoundingBox.h"
#include "STLReader.h"
#include <string>
#include <filesystem>
int main()
{
	std::cout << "MiniCAM Day 3" << std::endl;

	BoundingBox Bbox;
	STLReader reader;

	std::filesystem::path rootPath(PROJECT_ROOT_DIR);
	std::filesystem::path fullPath = rootPath / "stl" / "batman.stl";

	std::vector<Triangle> triangles;
	reader.readFile(fullPath.string(), triangles);

	for (auto& tri : triangles)
	{
		Bbox.Update(tri.v1);
		Bbox.Update(tri.v2);
		Bbox.Update(tri.v3);
	}

	std::cout << "The num of triangles is " << triangles.size() << std::endl;
	std::cout << "The boundingbox center point is " << Bbox.GetCenterPoint().x << "," << Bbox.GetCenterPoint().y << "," << Bbox.GetCenterPoint().z << std::endl;

	return 0;
}
