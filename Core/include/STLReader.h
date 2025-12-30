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
	bool loadBinarySTL(std::ifstream& file, std::vector<Triangle>& triangles);

	bool loadASCIISTL(std::ifstream& file, std::vector<Triangle>& triangles);

	bool isASCIISTL(std::ifstream& file);
};

