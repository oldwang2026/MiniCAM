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
	MinPoint.x = std::min(coord.x, MinPoint.x);
	MinPoint.x = std::min(coord.y, MinPoint.y);
	MinPoint.x = std::min(coord.z, MinPoint.z);

	// 更新最大值 (MaxPoint)
	MaxPoint.x = std::max(MaxPoint.x, coord.x);
	MaxPoint.y = std::max(MaxPoint.y, coord.y);
	MaxPoint.z = std::max(MaxPoint.z, coord.z);
}

BoundingBox::~BoundingBox()
{
}
