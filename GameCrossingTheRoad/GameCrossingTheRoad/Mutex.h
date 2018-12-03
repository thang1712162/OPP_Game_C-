#pragma once
#include<iostream>
#include<string>
#include<mutex>
#include "console.h"
using namespace std;
class Mutex
{
private:
	static mutex mu;
public:
	static void print(int x, int y, int c, string msg) {
		lock_guard<std::mutex > guard(mu);
		gotoXY(x, y);
		TextColor(c);
		cout << msg;
	}
	static void Enter(int x, int y, string & msg) {
		lock_guard<std::mutex > guard(mu);
		gotoXY(x, y);
		cin >> msg;
		msg += '.txt';
	}
	static void clean(int x, int y) {
		lock_guard<std::mutex > guard(mu);
		HANDLE hOutput = ::GetStdHandle(STD_OUTPUT_HANDLE);
		COORD coord = { x,y };
		::SetConsoleCursorPosition(hOutput, coord);

		char buff[] = "   ";
		::WriteConsoleA(hOutput, buff, 3, NULL, NULL);
	}
public:
	Mutex();
	~Mutex();
};

