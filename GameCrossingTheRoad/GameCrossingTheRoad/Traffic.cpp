
#include "Traffic.h"



Traffic::Traffic() {
	_p = _q = Point(0, 0);
}

Traffic::Traffic(int x, int y, int z, int t) {

	_p = Point(x, y);
	_q = Point(z, t);
	light = Green;
	flag = 0;
}


void Traffic::Paint() {
	string s;
	s = char(219);
	if (light == Red) {

		Mutex::print(_p.X(), _p.Y(), ColorCode_Red, s);
		Mutex::print(_q.X(), _q.Y(), ColorCode_Red, s);
	}
	else {
		Mutex::print(_p.X(), _p.Y(), ColorCode_Green, s);
		Mutex::print(_q.X(), _q.Y(), ColorCode_Green, s);
	}

}

Traffic::~Traffic()
{
}
