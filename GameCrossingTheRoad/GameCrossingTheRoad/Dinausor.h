#pragma once
#include "Animal.h"
class Dinausor : public Animal
{
public:
	void Move();
	void Paint();
	void Clean();
	bool Crash(int, int);
public:
	Dinausor();
	Dinausor(int, int);
	~Dinausor();
};

