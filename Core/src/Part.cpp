#include "Part.h"
#include "STLReader.h"
#include <filesystem>
#include <unordered_map>
#include <Eigen/Dense>
#include <map>


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
	return m_vertices.size();
}

void Part::BuildBasicTopology()
{
	m_vertices.clear();
	m_faces.clear();

	const size_t tri_count = m_triangles.size(); //face num

	m_faces.reserve(tri_count);
	m_vertices.reserve(tri_count * 3);

	std::unordered_map<Point3D, int, Point3DHash> unique_map;

	for (const auto& tri : m_triangles)
	{
		Point3D tempv[3] = { tri.v1, tri.v2, tri.v3 };
		Eigen::Vector3i face_indices;
		for (size_t i = 0; i < 3; i++)
		{
			auto [iter,insterted] = unique_map.try_emplace( tempv[i], static_cast<int>(m_vertices.size()) );

			if (insterted)
			{
				m_vertices.push_back(tempv[i]);
			}

			face_indices[i] = iter->second;
		}
		
		m_faces.push_back(face_indices);
	}
	
}

void Part::BuildHalfedgeTopology()
{
	m_mesh.clear();

	m_mesh.edges.resize(m_faces.size() * 3);
	m_mesh.faces.reserve(m_faces.size());
	m_mesh.verts.reserve(m_vertices.size());

	// 初始化顶点

	for (const auto& v : m_vertices)
	{
		HE_Vert hv;
		hv.pos = v;
		hv.is_boundary = false;
		m_mesh.verts.push_back(hv);
	}

	//
	std::map<std::pair<int, int>, int> edge_history;
	const auto facesize = m_faces.size();

	for (size_t i = 0; i < facesize; i++)
	{
		const auto& face_indices = m_faces[i];

		//chuang jian mian 
		HE_Face f;
		f.edge = 3 * i;
		m_mesh.faces.push_back(f);

		//chuang jian 3 tiao bian 
		for (size_t j = 0;j < 3; j++)
		{
			int u = face_indices[j]; //起点
			int v = face_indices[(j + 1) % 3];//终点

			int current_idx = 3 * i + j;

			//填充半边属性
			m_mesh.edges[current_idx].vert = v;      // 半边指向终点
			m_mesh.edges[current_idx].face = i;      // 所属面
			m_mesh.edges[current_idx].next = 3 * i + (j + 1) % 3; // 同样的逻辑，指向下一条
			m_mesh.edges[current_idx].pair = -1;     // 暂时标记为无邻居(边界)

			//
			// 记录“以 u 为起点的边”。只需要记录任意一条即可。
			if (m_mesh.verts[u].edge == -1)
			{
				m_mesh.verts[u].edge = current_idx;
			}

			// 我们当前创建了 u -> v。
			// 即使是两个相邻三角形，它们的边方向一定是相反的 (u->v 和 v->u)。
			// 检查历史记录里，是否有 v -> u 在等待配对？

			std::pair<int, int> reverse_key = { v, u };
			auto it = edge_history.find(reverse_key);

			if (it != edge_history.end())
			{
				// 找到了！说明那是我的邻居
				int pair_idx = it->second;

				// 互相认领
				m_mesh.edges[current_idx].pair = pair_idx;
				m_mesh.edges[pair_idx].pair = current_idx;
			}
			else
			{
				// 没找到，说明我是先来的。
				// 把我自己 (u -> v) 登记在册，等我的另一半 (v -> u) 出现。
				edge_history[{ u, v }] = current_idx;
			}

		}
	}
	std::cout << "Half-Edge Built: " << m_mesh.edges.size() << " edges." << std::endl;
}

void Part::BuildTopology()
{
	BuildBasicTopology();
	BuildHalfedgeTopology();
}

std::vector<int> Part::GetOneRingNeighbors(int vert_idx) const
{
	std::vector<int> neighbors;

	if (m_vertices.size() == 0) return neighbors;
	
	auto centralVertex = m_mesh.verts[vert_idx];
	
	auto start_edge = m_mesh.edges[centralVertex.edge];
	
	
	return neighbors;;
}
