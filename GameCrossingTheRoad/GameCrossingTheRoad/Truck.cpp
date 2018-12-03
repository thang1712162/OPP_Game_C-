
#include "Truck.h"


Truck::Truck() : Vehicle::Vehicle() {
}

Truck::Truck(int x, int y) : Vehicle::Vehicle(x, y) {
}

void Truck::Paint() {

	Mutex::print(_p.X() - 3, _p.Y() - 1, ColorCode_Red, "___");

	Mutex::print(_p.X(), _p.Y(), ColorCode_Red, "|");

	Mutex::print(_p.X() - 4, _p.Y(), ColorCode_Red, "|");

	Mutex::print(_p.X() - 3, _p.Y() + 1, ColorCode_Red, "o");

	Mutex::print(_p.X() - 2, _p.Y() + 1, ColorCode_Red, "-");

	Mutex::print(_p.X() - 1, _p.Y() + 1, ColorCode_Red, "o");

	Mutex::print(_p.X() - 5, _p.Y(), ColorCode_Red, "[");

}

void Truck::Clean() {

	Point P[] = { Point(-3,-1), Point(0,0), Point(-4,0), Point(-3,1), Point(-2,1), Point(-1,1), Point(-5,0) };
	for (int i = 0; i < 7; i++) clean(_p.X() + P[i].X(), _p.Y() + P[i].Y());

}

bool Truck::Crash(int x, int y) {

	Point P[] = { Point(-1, -2), Point(-2, -1), Point(3, -2), Point(2, -2), Point(-1, 0), Point(2, -1), Point(1, -1), Point(1, -2) };
	Point Q[] = { Point(0, 0), Point(-1, 0), Point(1, 0), Point(0, 1), Point(-1, 2), Point(1, 2) };
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 6; j++)
			if (_p.X() + P[i].X() == x + Q[j].X() && _p.Y() + P[i].Y() == y + Q[j].Y()) return true;
	return false;

}

void Truck::Move() {
	Vehicle::Move();
}

Truck::~Truck() {
}
