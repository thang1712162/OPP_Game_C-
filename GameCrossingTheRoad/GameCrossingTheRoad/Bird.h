#pragma once
#include "Animal.h"
#include <conio.h>
class Bird : public Animal
{
public:
	void Move();
	void Paint();
	void Clean();
	bool Crash(int, int);
public:
	Bird();
	Bird(int, int);
	~Bird();
};

