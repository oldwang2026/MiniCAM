// MIniCamCore.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。

#pragma once

#include <iostream>

namespace MiniCAM {
	inline constexpr double Tolerance = 1e-6;
}

struct Point3D
{
	double x, y, z;
	Point3D() : x(0.0), y(0.0), z(0.0) {}
	Point3D(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}

	Point3D& operator+=(const Point3D& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;

		return *this;
	}

	Point3D operator+(const Point3D& other) const
	{
		return Point3D(*this) += other;
	}

	Point3D operator/(const double other) const
	{

		Point3D temp = *this;
		temp.x /= other;
		temp.y /= other;
		temp.z /= other;
		return temp;
	}

	bool operator==(const Point3D& other) const
	{
		return (std::abs(x - other.x) < MiniCAM::Tolerance) &&
			(std::abs(y - other.y) < MiniCAM::Tolerance) &&
			(std::abs(z - other.z) < MiniCAM::Tolerance);
	}
};

using Vector3D = Point3D;


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
		auto hasher = std::hash<double>{};
		auto hash1 = hasher(p.x);
		auto hash2 = hasher(p.y);
		auto hash3 = hasher(p.z);

		return hash1 ^ (hash2 << 1) ^ (hash3 << 2);
	}
};

// TODO: 在此处引用程序需要的其他标头。
