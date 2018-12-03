#pragma once
#include "Point.h"
#include "console.h"
#include <iostream>
#include <conio.h>
#include "Mutex.h"
using namespace std;
class Vehicle : public Mutex
{
protected:
	Point _p;


public:
	Point get() const { return _p; }
	Point set(const Point & q) { _p = q; }
	void Move();
	virtual bool Crash(int, int) = 0;
public:
	Vehicle();
	Vehicle(int, int);
	~Vehicle();
};

