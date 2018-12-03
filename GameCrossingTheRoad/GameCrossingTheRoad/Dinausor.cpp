
#include "Dinausor.h"

Dinausor::Dinausor() :Animal::Animal()
{
}

Dinausor::Dinausor(int x, int y) : Animal::Animal(x, y)
{
}

void Dinausor::Paint() {

	Mutex::print(_p.X() - 1, _p.Y(), ColorCode_Green, "/");

	Mutex::print(_p.X() + 1, _p.Y(), ColorCode_Green, "/");

	Mutex::print(_p.X() - 3, _p.Y(), ColorCode_Green, "__");

	Mutex::print(_p.X() - 4, _p.Y() + 1, ColorCode_Green, "/");

	Mutex::print(_p.X() - 3, _p.Y() + 1, ColorCode_Green, "__");

	Mutex::print(_p.X(), _p.Y() + 1, ColorCode_Green, "/");

	Mutex::print(_p.X(), _p.Y() - 1, ColorCode_Green, "/");

	Mutex::print(_p.X() + 1, _p.Y() - 1, ColorCode_Green, "*");

	Mutex::print(_p.X() + 2, _p.Y() - 1, ColorCode_Green, "=");


}
void Dinausor::Clean() {
	Point P[] = { Point(-1,0),Point(1,0),Point(-3,0),Point(-4,1),Point(-3,1),Point(0,1),Point(0,-1),Point(1,-1),Point(2,-1) };
	for (int i = 0; i < 8; i++) clean(_p.X() + P[i].X(), _p.Y() + P[i].Y());
}
bool Dinausor::Crash(int x, int y) {
	//	Point P[] = { Point(-1,0),Point(1,0),Point(-3,0),Point(-4,1),Point(-3,1),Point(0,1),Point(0,-1),Point(1,-1),Point(2,-1) };
	Point P[] = { Point(-1, -2), Point(-2, -1), Point(3, -2), Point(2, -2), Point(-1, 0), Point(2, -1), Point(1, -1), Point(1, -2) };
	Point Q[] = { Point(0, 0), Point(-1, 0), Point(1, 0), Point(0, 1), Point(-1, 2), Point(1, 2) };
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 6; j++)
			if (_p.X() + P[i].X() == x + Q[j].X() && _p.Y() + P[i].Y() == y + Q[j].Y()) return true;
	return false;

}
void Dinausor::Move() {
	Animal::Move();
}

Dinausor::~Dinausor()
{
}
