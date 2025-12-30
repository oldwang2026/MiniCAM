// MIniCamCore.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。

#pragma once

#include <iostream>

struct Point3D
{
	double x, y, z;
	Point3D() : x(0.0), y(0.0), z(0.0) {}
	Point3D(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}

};

using Vector3D = Point3D;

struct Triangle
{
	Vector3D norm;
	Point3D v1;
	Point3D v2;
	Point3D v3;
};



// TODO: 在此处引用程序需要的其他标头。
