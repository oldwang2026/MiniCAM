// MIniCamCore.cpp: 定义应用程序的入口点。
//

#include "GeoTypes.h"
#include <vector>
#include <iostream>
#include "BoundingBox.h"

int main()
{
	std::cout << "MiniCAM Day 1" << std::endl;
	std::cout << "size of Double " << sizeof(double) << "byte" << std::endl;
	std::cout << "size of Double " << sizeof(Point3D) << "byte" << std::endl;
	std::cout << "size of Double " << sizeof(Triangle) << "byte" << std::endl;

	std::vector<Triangle> triangles;
	triangles.reserve(3);

	Triangle t1;
	t1.norm = Vector3D(0.0, 0.0, 1.0);;
	t1.v1 = Point3D(0, 0, 0);
	t1.v2 = Point3D(1, 0, 0);
	t1.v3 = Point3D(0, 1, 0);

	triangles.push_back(t1);

	std::cout << "Successfully created a mesh with " << triangles.size() << " triangle." << std::endl;

	return 0;
}
