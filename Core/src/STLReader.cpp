#include "STLReader.h"
#include <fstream>
#include <iostream>
#include <filesystem>


bool STLReader::isASCIISTL(const std::string& filePath)
{
	//读前5个字节
	std::ifstream file(filePath,std::ios::binary);

	if (!file.is_open())
	{
		return false;
	}

	char header[6] = { 0 };
	file.read(header, 5);

	std::string headerstart(header);

	if(headerstart != "solid")
	{
		return false;
	}

	// Size = 80字节(头) + 4字节(数量) + N * 50字节(每个三角形)
	// A. 获取文件总大小
	file.seekg(0, std::ios::end); // 移动到文件末尾
	std::streamsize fileSize = file.tellg(); // 获取当前位置（即文件大小）

	if (fileSize < 84) {
		return true; // 文件太小，不符合二进制最小标准，当作 ASCII 里的坏文件处理或直接返回 ASCII
	}

	// B. 读取三角形数量
	file.seekg(80, std::ios::beg); // 移动到存储三角形数量的位置
	uint32_t triangleCount = 0;
	file.read(reinterpret_cast<char*>(&triangleCount), sizeof(uint32_t));

	// C. 计算预期的二进制文件大小
	std::streamsize expectedsize = 80 + 4 + static_cast<std::streamsize>(triangleCount) * 50;

	if (fileSize == expectedsize)
	{
		return false;
	}

	return true;
}

bool STLReader::loadBinarySTL(const std::string& filePath, std::vector<Triangle>& triangles)
{
	std::ifstream file(filePath, std::ios::binary);
	if (!file.is_open()) return false;

	file.seekg(80, std::ios::beg); 

	uint32_t triangleCount = 0;
	file.read(reinterpret_cast<char*>(&triangleCount), sizeof(uint32_t));

	if (triangleCount == 0)
	{
		return true;
	}

	triangles.clear();
	triangles.reserve(triangleCount);
	
	
	const size_t SingleTrianglesize = 4 * 3 * sizeof(float) + 2;
	size_t buffersize = SingleTrianglesize * static_cast<size_t>(triangleCount);

	std::vector<uint8_t> buffer;
	buffer.resize(buffersize);

	if (!file.read(reinterpret_cast<char*>(buffer.data()), buffersize))
	{
		return false;
	}


	uint8_t* ptr = buffer.data();

	for (uint32_t i = 0; i < triangleCount; i++)
	{
		float data[12];
		memcpy(data, ptr, 12 * sizeof(float));

		Triangle t;
		t.norm = Vector3D(data[0], data[1], data[2]);
		t.v1 = Point3D(data[3], data[4], data[5]);
		t.v2 = Point3D(data[6], data[7], data[8]);
		t.v3 = Point3D(data[9], data[10], data[11]);

		triangles.push_back(t);

		ptr += SingleTrianglesize;
	}
	

	file.close();
	std::cout << "successfully loaded " << triangles.size() << " triangles from binary STL file." << std::endl;
	return true;

}

bool STLReader::loadASCIISTL(const std::string& filePath, std::vector<Triangle>& triangles)
{
	std::ifstream file(filePath);
	if (!file.is_open()) return false;

	std::string word;
	Triangle tempT;
	int vCount = 0;

	// 使用 >> 操作符会自动跳过所有空格、制表符和换行符
	while (file >> word)
	{
		if (word == "facet")
		{
			file >> word; // 跳过 "normal"
			// 直接读入 double。虽然 STL 存的是 float，但读入 double 是安全的
			file >> tempT.norm.x >> tempT.norm.y >> tempT.norm.z;
		}
		else if (word == "vertex")
		{
			Point3D p;
			file >> p.x >> p.y >> p.z;

			if (vCount == 0)      tempT.v1 = p;
			else if (vCount == 1) tempT.v2 = p;
			else if (vCount == 2) tempT.v3 = p;

			vCount++;
			if (vCount == 3)
			{
				triangles.push_back(tempT);
				vCount = 0; // 重置计数
			}
		}
	}

	file.close();
	std::cout << "Successfully loaded " << triangles.size() << " triangles from ASCII STL." << std::endl;
	return true;
}

bool STLReader::readFile(const std::string& filename, std::vector<Triangle>& triangles)
{
	if (isASCIISTL(filename))
	{
		return loadASCIISTL(filename, triangles);
	}
	else
	{
		return loadBinarySTL(filename, triangles);
	}
}

