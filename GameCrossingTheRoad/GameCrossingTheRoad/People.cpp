
#include "People.h"



People::People()
{
	_p = Point(0, 0);
	_State = true;
	dem = 1;
}


People::People(int x, int y, int z) {
	_p = Point(x, y);
	_State = z;
	dem = 1;
}

void People::Up(int x) {
	if ((x == 'w' || x == 'W') && _p.Y() - 5>0) {
		_p.setY(_p.Y() - 5);
	}
}

void People::Down(int x) {
	if ((x == 's' || x == 'S') && _p.Y() + 5< 28) {
		_p.setY(_p.Y() + 5);
	}
}

void People::Left(int x) {
	if ((x == 'a' || x == 'A') && _p.X() - 1 >2) {
		_p.setX(_p.X() - 1);
	}
}

void People::Right(int x) {
	if ((x == 'd' || x == 'D') && _p.X() + 1<81) {
		_p.setX(_p.X() + 1);
	}
}

People::People(const People &other) {
	_p = other._p;
	_State = other._State;
}



void People::Clean() {
	Point P[] = { Point(0, 0), Point(-1, 0), Point(1, 0), Point(0, 1), Point(-1, 2), Point(1, 2) };
	for (int i = 0; i < 6; i++)
		Mutex::clean(_p.X() + P[i].X(), _p.Y() + P[i].Y());

}

int People::isDead() {
	return !(_State);
}
void People::Paint() {

	Mutex::print(_p.X(), _p.Y(), ColorCode_DarkWhite, "O");
	Mutex::print(_p.X() - 1, _p.Y(), ColorCode_DarkWhite, "_");
	Mutex::print(_p.X() + 1, _p.Y(), ColorCode_DarkWhite, "_");
	Mutex::print(_p.X(), _p.Y() + 1, ColorCode_DarkWhite, "|");
	Mutex::print(_p.X() - 1, _p.Y() + 2, ColorCode_DarkWhite, "/");
	Mutex::print(_p.X() + 1, _p.Y() + 2, ColorCode_DarkWhite, "\\");

}
People::~People()
{
}
