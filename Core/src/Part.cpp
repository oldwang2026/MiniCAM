#include "Part.h"
#include "STLReader.h"
#include <filesystem>

Part::Part(const std::string filedir)
{
	if (filedir.size() == 0) return;
	STLReader reader;
	reader.readFile(filedir, m_triangles);
	m_bbox.Update(m_triangles);
	m_name = filedir;
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

