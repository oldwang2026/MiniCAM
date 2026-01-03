#include "BoundingBox.h"

BoundingBox::BoundingBox()
{
	constexpr double maxd = std::numeric_limits<double>::max();
	constexpr double mind = std::numeric_limits<double>::lowest();

	MinPoint = Point3D(maxd, maxd, maxd);
	MaxPoint = Point3D(mind, mind, mind);

}

void BoundingBox::SetMinPoint(Point3D coord)
{
	MinPoint = coord;
}

void BoundingBox::SetMaxPoint(Point3D coord)
{
	MaxPoint = coord;
}

Point3D BoundingBox::GetCenterPoint() const
{
	return (MinPoint + MaxPoint) / 2.0;
}

Point3D BoundingBox::GetMinPoint() const
{
	return MinPoint;
}

Point3D BoundingBox::GetMaxPoint() const
{
	return MaxPoint;
}
std::vector<double> BoundingBox::GetDistances()
{
	std::vector<double> distances;
	distances.reserve(3);
	distances.push_back(MaxPoint.x - MinPoint.x);
	distances.push_back(MaxPoint.y - MinPoint.y);
	distances.push_back(MaxPoint.z - MinPoint.z);

	return distances;
}

void BoundingBox::Update(const Point3D coord)
{
	// === 修复点 1: 确保赋值给对应的 .x, .y, .z ===
	MinPoint.x = std::min(coord.x, MinPoint.x);
	MinPoint.y = std::min(coord.y, MinPoint.y); // <--- 必须是 MinPoint.y
	MinPoint.z = std::min(coord.z, MinPoint.z); // <--- 必须是 MinPoint.z

	// === 修复点 2: MaxPoint 也要对应 ===
	MaxPoint.x = std::max(MaxPoint.x, coord.x);
	MaxPoint.y = std::max(MaxPoint.y, coord.y);
	MaxPoint.z = std::max(MaxPoint.z, coord.z);
}

void BoundingBox::Update(const std::vector<Triangle>& triangles)
{
	for (auto& tri : triangles)
	{
		Update(tri.v1);
		Update(tri.v2);
		Update(tri.v3);
	}
}
BoundingBox::~BoundingBox()
{
}
