#pragma once

#include <string>
#include <iostream>

using namespace std;

class Vec2 {
public:
	float x = 0.00f;
	float y = 0.00f;

	Vec2(){}
	Vec2(float x, float y)
	{
		this-> x = x;
		this-> y = y;
	}

	Vec2 Add(Vec2 v)
	{
		Vec2 xy;
		xy.x = this->x + v.x;
		xy.y = this->y + v.y;
		
	}

	void incr(Vec2 *v)
	{
		(*v).x = this->x;
	}
	
	void incr(Vec2 &v)
	{
		v.x = this->x;
	}
};
