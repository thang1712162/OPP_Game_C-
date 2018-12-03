#include "Car.h"

Car::Car() : Vehicle::Vehicle() {
}

Car::Car(int x, int y) : Vehicle::Vehicle(x, y) {}

void Car::Paint() {

	Mutex::print(_p.X(), _p.Y() - 1, ColorCode_Pink, "_");

	Mutex::print(_p.X(), _p.Y(), ColorCode_Pink, "_");

	Mutex::print(_p.X() - 1, _p.Y(), ColorCode_Pink, "/");

	Mutex::print(_p.X() + 1, _p.Y(), ColorCode_Pink, "\\");

	Mutex::print(_p.X() - 2, _p.Y(), ColorCode_Pink, "_");

	Mutex::print(_p.X() + 2, _p.Y(), ColorCode_Pink, "_");

	Mutex::print(_p.X() + 2, _p.Y() + 1, ColorCode_Pink, "o");

	Mutex::print(_p.X(), _p.Y() + 1, ColorCode_Pink, "--");

	Mutex::print(_p.X() - 1, _p.Y() + 1, ColorCode_Pink, "o");



}
void Car::Clean() {
	Point P[] = { Point(0, -1), Point(0, 0), Point(-1, 0), Point(1, 0), Point(-2, 0), Point(2, 0), Point(1, 1), Point(0, 1), Point(-1, 1) };
	for (int i = 0; i < 9; i++) clean(_p.X() + P[i].X(), _p.Y() + P[i].Y());
}
bool Car::Crash(int x, int y) {
	Point P[] = { Point(-1, -2), Point(-2, -1), Point(3, -2), Point(2, -2), Point(-1, 0), Point(2, -1), Point(1, -1), Point(1, -2) };
	Point Q[] = { Point(0, 0), Point(-1, 0), Point(1, 0), Point(0, 1), Point(-1, 2), Point(1, 2) };
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 6; j++)
			if (_p.X() + P[i].X() == x + Q[j].X() && _p.Y() + P[i].Y() == y + Q[j].Y()) return true;
	return false;
}

void Car::Move() {
	Vehicle::Move();
}

Car::~Car()
{
}
