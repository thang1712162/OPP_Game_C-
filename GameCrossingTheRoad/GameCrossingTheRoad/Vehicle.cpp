#include "Vehicle.h"


Vehicle::Vehicle()
{
	_p = Point(0, 0);
}

Vehicle::Vehicle(int x, int y) {
	_p = Point(x, y);
}

void Vehicle::Move() {
	_p.setX(_p.X() - 10 > 4 ? _p.X() - 10 : 76);
}

Vehicle::~Vehicle() {
}
