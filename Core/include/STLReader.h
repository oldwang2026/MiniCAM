#pragma once

#include <string>
#include <vector>
#include "GeoTypes.h"

class STLReader
{
public:
	STLReader() = default;
	~STLReader() = default;

	bool readFile(const std::string& filename, std::vector<Triangle>& triangles);

private:
	bool loadBinarySTL(const std::string& filePath, std::vector<Triangle>& triangles);

	bool loadASCIISTL(const std::string& filePath, std::vector<Triangle>& triangles);

	bool isASCIISTL(const std::string& filePath);
};

