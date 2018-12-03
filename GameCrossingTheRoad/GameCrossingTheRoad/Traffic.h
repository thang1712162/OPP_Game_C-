#pragma once
#include "console.h"
#include "Point.h"
#include "Mutex.h"
#include <conio.h>
#include <iostream>

using namespace std;
enum Light { Red, Green };
class Traffic : public Mutex
{
private:
	Light light;
	Point _p;
	Point _q;
	int flag;
public:
	int getFlag() { return flag; }
	void setFlag(int x) { flag = x; }
	Light getLight() { return light; }
	void setLight(Light x) { light = x; }
	void Paint();
public:
	Traffic();
	Traffic(int, int, int, int);
	~Traffic();
};

