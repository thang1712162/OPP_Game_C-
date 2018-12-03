#pragma once
#include "Point.h"
#include "Mutex.h"
#include "console.h"
#include <iostream>
#include <conio.h>
class Animal : public Mutex
{
protected:
	Point _p;
public:
	Point get() { return _p; }
	void  set(const Point & q) { _p = q; }
	void Move();
	virtual bool Crash(int, int) = 0;

public:
	Animal();
	Animal(int, int);
	~Animal();
};

