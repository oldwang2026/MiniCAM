#pragma once

#include <string>
#include "GeoTypes.h"
#include "STLReader.h"
#include <vector>

#include "BoundingBox.h"
class Part
{
public:
	Part() = default;
	~Part() = default;

	explicit Part(const std::string filedir);

	bool LoadFile(const std::string filedir);

	const BoundingBox& GetBoundingBox() const;

	size_t GetTriangleCount() const;

	const std::string& GetName() const;

	const std::vector<Triangle>& GetTriangles() const; 
	
	const size_t GetVertexCount() const;


private:
	std::vector<Triangle> m_triangles;

	std::vector<Point3D> m_uniquevertices;
	std::string m_name;
	BoundingBox m_bbox;
	PolyMesh m_mesh;

	void BuildTopology();

};

