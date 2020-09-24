#pragma once

template<typename T>
class Vec3T
{
public:
	T x;
	T y;
	T z;

	Vec3T<T>(){
		x = {};
		y = {};
		z = {};
	};

	Vec3T<T>(T x, T y, T z) {
		this->x = x;
		this->y = y;
		this->z = z;
	};

	Vec3T<T> ADD(Vec3T<T> v) {
		Vec3T<T> a;
		a.x = this->x + v.x;
		a.y = this->y + v.y;
		a.z = this->z + v.z;

		return a;
	}
};

