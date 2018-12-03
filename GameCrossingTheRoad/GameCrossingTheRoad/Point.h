#pragma once
#include<iostream>
#include<string>
using namespace std;
class Point
{
private:
	int _x, _y;

public:
	int X() { return _x; }
	int Y() { return _y; }
	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }
public:
	Point();
	Point(int, int);
	~Point();
};

