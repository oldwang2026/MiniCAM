#pragma once
#include <limits>
#include <algorithm>
#include <math.h>
#include "GeoTypes.h"
#include <vector>


class BoundingBox
{
public:
	BoundingBox();
	~BoundingBox();
	//BoundingBox(stlmodel) in future

	void SetMinPoint(Point3D coord);

	void SetMaxPoint(Point3D coord);

	Point3D GetCenterPoint() const;

	Point3D GetMinPoint() const;//Minimum corner of box

	Point3D GetMaxPoint() const;
	std::vector<double> GetDistances();//Distances to move along directions from minpoint

	void Update(const Point3D coord);
	
	//void UpdatebySTL(stlmodel) in future
private:
	Point3D MinPoint;

	Point3D MaxPoint;

};//Axis aligned Box
