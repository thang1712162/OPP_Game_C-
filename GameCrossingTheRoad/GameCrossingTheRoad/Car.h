#pragma once
#include "Vehicle.h"
class Car : public Vehicle
{
public:
	void Move();
	void Paint();
	void Clean();
	bool Crash(int, int);
public:
	Car();
	Car(int, int);
	~Car();
};

