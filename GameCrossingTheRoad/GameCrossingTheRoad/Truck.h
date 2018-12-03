#pragma once
#include "Vehicle.h"
class Truck : public Vehicle
{
	/*private:
	Point P[] = { Point(-3,-1), Point(0,0), Point(-4,0), Point(-3,1), Point(-2,1), Point(-1,1), Point(+1,0) };*/
public:
	void Move();
public:
	void Paint();
	void Clean();
	bool Crash(int, int);
public:
	Truck();
	Truck(int, int);
	~Truck();
};

