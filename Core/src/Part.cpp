#include "Part.h"
#include "STLReader.h"
#include <filesystem>
#include <unordered_map>


Part::Part(const std::string filedir)
{
	LoadFile(filedir);
}

bool Part::LoadFile(const std::string filedir)
{
	if (filedir.empty()) return false;

	STLReader reader;

	m_triangles.clear();
	if (!reader.readFile(filedir, m_triangles))
	{
		return false; // 读取失败
	}
	m_bbox.Update(m_triangles);

	
	m_name = std::filesystem::path(filedir).filename().string();

	BuildTopology();

	return true;
}

const BoundingBox& Part::GetBoundingBox() const
{
	return m_bbox;
}

size_t Part::GetTriangleCount() const
{
	return m_triangles.size();
}

const std::string& Part::GetName() const
{
	return m_name;
}

const std::vector<Triangle>& Part::GetTriangles() const
{
	return m_triangles;
}

const size_t Part::GetVertexCount() const
{
	return m_uniquevertices.size();
}

void Part::BuildTopology()
{
	m_uniquevertices.clear();

	std::unordered_map<Point3D, int, Point3DHash> vertices;

	for (auto& tri : m_triangles)
	{
		Point3D vert[3] = { tri.v1,tri.v2,tri.v3 };
		for (size_t i = 0; i < 3; i++)
		{
			if (vertices.find(vert[i]) == vertices.end())
			{
				int newindex = static_cast<int>(m_uniquevertices.size());
				vertices[vert[i]] = newindex;

				m_uniquevertices.push_back(vert[i]);

			}
		}
	}
}
