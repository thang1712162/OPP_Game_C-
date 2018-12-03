#pragma once
#include "Animal.h"
#include "Vehicle.h"
#include "Point.h"
#include <SFML/Audio.hpp>

class People : public Mutex
{
private:
	Point _p;
	int _State;
	int dem;

public:

	Point get() const { return _p; }
	void Up(int);
	void Left(int);
	void Right(int);
	void Down(int);
	void Paint();
	void Clean();
	bool getState() { return _State; }
	void setState(int x) { _State = x;  cout << _State << endl; }
	int isDead();
public:
	People();
	People(int, int, int);
	People(const People &);
	~People();
};

