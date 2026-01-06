// MIniCamCore.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。

#pragma once

#include <iostream>
#include <vector>
#include <functional>
#include <Eigen/Dense>

namespace MiniCAM {
	inline constexpr double Tolerance = 1e-6;
	inline constexpr int HE_INVALID = -1;

}

using Point3D = Eigen::Vector3d;
using Vector3D = Eigen::Vector3d;

struct Triangle
{
	Vector3D norm;
	Point3D v1;
	Point3D v2;
	Point3D v3;
};

struct Point3DHash
{
	std::size_t operator()(const Point3D& p) const
	{
		auto hasher = std::hash<long long>{};

		auto hash1 = hasher(std::llround(p.x() / MiniCAM::Tolerance));
		auto hash2 = hasher(std::llround(p.y() / MiniCAM::Tolerance));
		auto hash3 = hasher(std::llround(p.z() / MiniCAM::Tolerance));


		return hash1 ^ (hash2 << 1) ^ (hash3 << 2);
	}
};

//
//    半边数据结构
//
struct HE_Edge;
struct HE_Face;
struct HE_Vert;


struct HE_Edge 
{
	int vert = MiniCAM::HE_INVALID; //指向半边终点
	int next = MiniCAM::HE_INVALID; //下一个半边
	int pair = MiniCAM::HE_INVALID; //对向半边
	int face = MiniCAM::HE_INVALID; //所属HE_Face

};

struct HE_Vert
{
	int edge = MiniCAM::HE_INVALID; //任意一条以该顶点为起点的半边 
	Point3D pos;
	bool is_boundary = false;

};

struct HE_Face
{
	int edge = MiniCAM::HE_INVALID;
	Vector3D facenorm;
};

struct PolyMesh
{
	std::vector<HE_Edge> edges;
	std::vector<HE_Vert> verts;
	std::vector<HE_Face> faces;

	void clear()
	{
		verts.clear();
		edges.clear();
		faces.clear();
	}

	void reserve(size_t edgesize, size_t vertsize, size_t facesize)
	{
		verts.reserve(vertsize);
		edges.reserve(edgesize);
		faces.reserve(facesize);
	}

};
// TODO: 在此处引用程序需要的其他标头。
