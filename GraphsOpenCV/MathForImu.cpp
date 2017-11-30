#include "MathForIMU.h"
#include <iostream>

Quaternion::Quaternion(double a, double b, double c, double d): _w(a), _x(b), _y(c), _z(d)
{
}

void quaternionToEulerianAngle(const Quaternion& q, double& roll, double& pitch, double& yaw)
{
	const double ysqr = q._y * q._y;
	// roll (x-axis rotation)
	const double t0 = 2. * (q._w * q._x + q._y * q._z);
	const double t1 = 1. - 2. * (q._x * q._x + ysqr);
	roll = std::atan2(t0, t1);

	// pitch (y-axis rotation)
	double t2 = 2. * (q._w * q._y - q._z * q._x);
	t2 = t2 > 1. ? 1. : t2;
	t2 = t2 < -1. ? -1. : t2;
	pitch = std::asin(t2);

	// yaw (z-axis rotation)
	const double t3 = 2. * (q._w * q._z + q._x * q._y);
	const double t4 = 1. - 2. * (ysqr + q._z * q._z);
	yaw = std::atan2(t3, t4);
}
