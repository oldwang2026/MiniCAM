#include "BoundingBox.h"

BoundingBox::BoundingBox()
{
	constexpr double maxd = std::numeric_limits<double>::max();
	constexpr double mind = std::numeric_limits<double>::lowest();

	MinPoint = Point3D(mind, mind, mind);
	MaxPoint = Point3D(maxd, maxd, maxd);

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

	MinPoint.x = std::max(coord.x, MinPoint.x);
	MinPoint.x = std::max(coord.y, MinPoint.y);
	MinPoint.x = std::max(coord.z, MinPoint.z);
}

BoundingBox::~BoundingBox()
{
}
