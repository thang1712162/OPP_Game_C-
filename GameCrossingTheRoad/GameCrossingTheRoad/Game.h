#pragma once
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib,"Winmm.lib")
#include "console.h"
#include "Truck.h"
#include <conio.h>
#include <iostream>
#include "Car.h"
#include "Dinausor.h"
#include "Animal.h"
#include <Windows.h>
#include "Vehicle.h"
#include "Bird.h"
#include "People.h"
#include "Traffic.h"

class Game
{
private:
	int _numberOfBurdens;
	People player;
	Truck * trucks;
	Car * cars;
	Bird * birds;
	Dinausor * dinausors;
	Traffic trafficLight;
	int round;
	bool music;
public:
	int getNumberOfBurdens() {
		return _numberOfBurdens;
	}
	void setMusic(bool x) { music = x; }
	bool getMusic() { return music; }
	void setRound(int x) { round = x; }
	bool isImpact();
	Vehicle * getVehicle();
	Animal * getAnimal();
	People getPeople();
	Traffic getTrafficLight() { return trafficLight; };
	void drawGame();
	void cleanGame();
	void drawFrame();
	void updatePosVehicle();
	void updatePosAnimal();
	void updatePosPeople(char);
	void updateLight();
	Game & operator = (const Game &);
	int startGame();
	void levelUP(int);
	void isDead();
	void finishGame();
	int exitGame();
	void pauseGame();
	int winner();
public:
	Game();
	Game(const Game &);
	Game(int);
	~Game();
};

