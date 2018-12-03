#include<SFML/Audio.hpp>
#include "Game.h"
#include <mutex>
#include <iostream>
#define TY 8
#define DY 13
#define CY 18
#define BY 23
#define N 28
Game::Game() {
	trucks = nullptr;
	cars = nullptr;
	birds = nullptr;
	dinausors = nullptr;
	player = People();
	trafficLight = Traffic();
	round = 0;
	music = 1;
}

Game::Game(int n) {
	_numberOfBurdens = n;
	trucks = new Truck[n];
	cars = new Car[n];
	birds = new Bird[n];
	dinausors = new Dinausor[n];
	for (int i = 0; i < n; i++) {
		trucks[i] = Truck(78 - i * 20, TY);
		cars[i] = Car(78 - i * 20, CY);
		birds[i] = Bird(i * 20 + 5, BY);
		dinausors[i] = Dinausor(i * 20 + 5, DY);
	}
	trafficLight = Traffic(2, TY, 2, CY);
	player = People(40, N - 1, true);
	round = 0;
	music = 1;
}

void Game::drawFrame() {
	sf::SoundBuffer buffer;
	sf::Sound sound;
	if (getMusic()) {
		if (!buffer.loadFromFile("levelup.wav"))
			cout << "NO FOUND" << endl;
	}
	sound.setBuffer(buffer);
	sound.play();
	sound.setLoop(true);
	string s;
	s = char(_numberOfBurdens - 1 + 48);
	Mutex::print(90, 5, 6, "LEVEL: " + s);

	s = char(_numberOfBurdens + 48);
	Mutex::print(90, 7, 6, "OBJECTS: " + s);

	Mutex::print(90, 9, 6, "PRESS L TO SAVE GAME");

	Mutex::print(90, 11, 6, "PRESS T TO LOAD GAME");

	Mutex::print(90, 13, 6, "PRESS P TO PAUSE GAME");

	Mutex::print(90, 15, 6, "PRESS EXC TO EXIT GAME");
	for (int i = 1; i <= N + 2; i++) {

		Mutex::print(1, i, ColorCode_Cyan, "|");
		Mutex::print(82, i, ColorCode_Cyan, "|");
	}

	TextColor(ColorCode_Cyan);
	for (int i = 1; i <= 82; i++) {

		Mutex::print(i, 1, ColorCode_Cyan, "-");

		Mutex::print(i, TY - 3, ColorCode_Cyan, "-");

		Mutex::print(i, CY - 3, ColorCode_Cyan, "-");

		Mutex::print(i, BY - 3, ColorCode_Cyan, "-");

		Mutex::print(i, DY - 3, ColorCode_Cyan, "-");

		Mutex::print(i, N - 3, ColorCode_Cyan, "-");

		Mutex::print(i, N + 2, ColorCode_Cyan, "-");
		Sleep(20);
	}

	sound.stop();


}
Game::Game(const Game & other) {
	_numberOfBurdens = other._numberOfBurdens;
	delete[] trucks;
	delete[] cars;
	delete[] birds;
	delete[] dinausors;
	trucks = new Truck[_numberOfBurdens];
	cars = new Car[_numberOfBurdens];
	birds = new Bird[_numberOfBurdens];
	dinausors = new Dinausor[_numberOfBurdens];
	for (int i = 0; i < _numberOfBurdens; i++) {
		trucks[i] = other.trucks[i];
		cars[i] = other.cars[i];
		birds[i] = other.birds[i];
		dinausors[i] = other.dinausors[i];
	}
	trafficLight = other.trafficLight;
	player = other.player;
	round = other.round;
	music = other.music;

}
Vehicle * Game::getVehicle() {
	return trucks;
}

People Game::getPeople() {
	return player;
}
void Game::updatePosVehicle() {
	if (trafficLight.getLight() == Red) return;
	for (int i = 0; i < _numberOfBurdens; i++) {
		trucks[i].Move();
		cars[i].Move();
	}

}

void Game::updatePosPeople(char x) {
	//cout << x <<"******"<< endl;
	player.Up(x);
	player.Down(x);
	player.Left(x);
	player.Right(x);

}

void Game::isDead() {
	sf::SoundBuffer buffer;
	sf::Sound sound;
	if (getMusic()) {
		if (!buffer.loadFromFile("Over.wav"))
			cout << "NO FOUND" << endl;
	}
	sound.setBuffer(buffer);
	sound.play();
	sound.setLoop(true);
	player.Clean();
	int color = rand() % 16;
	Mutex::print(97, 20, color, "GAME OVER");
	Mutex::print(90, 21, color, "PLEASE PRESS Y TO RESTART");
	for (int i = -3; i <= 3; i++) {
		Mutex::print(player.get().X() + i, player.get().Y() + i, color, "*");
		Mutex::print(player.get().X() - i, player.get().Y() + i, color, "*");
	}
	Sleep(1000);
	sound.stop();
}

void  Game::finishGame() {
	sf::SoundBuffer buffer;
	sf::Sound sound;
	if (getMusic()) {
		if (!buffer.loadFromFile("level.wav"))
			cout << "NO FOUND" << endl;
	}
	sound.setBuffer(buffer);
	sound.play();
	sound.setLoop(true);
	round++;
	if (round < 3) {
		for (int i = 0; i <= 100; i++) {
			Mutex::print(35, 15, rand() % 15 + 1, " LEVEL UP !!!");
			Sleep(20);
		}
	}
	cleanGame();
	getPeople().Clean();
	Sleep(400);
	sound.stop();
	clrscr();
}

int Game::exitGame() {
	clrscr();
	int t = -1;
	char c = ' ';
	Mutex::print(30, 15, ColorCode_Yellow, "DO YOU REALLY WANT TO EXIT GAME?");
	Mutex::print(37, 17, ColorCode_Yellow, "1. YES");
	Mutex::print(37, 19, ColorCode_Yellow, "2. NO");
	while (c != '1' && c != '2') {
		if (_kbhit()) {
			c = _getch();
			while (_kbhit()) _getch();
		}
		t = c - '1';
	}
	clrscr();
	if (t == 0) Mutex::print(30, 15, ColorCode_Yellow, "EXITING FROM THE GAME...");
	return t;


}
void Game::pauseGame() {
	char c = ' ';
	while (c != 'R' && c != 'r') {
		if (_kbhit()) {
			c = _getch();
			while (_kbhit()) _getch();
		}
		int color = rand() % 16;
		Mutex::print(97, 22, color, "PAUSE GAME");
		Mutex::print(90, 23, color, "PLEASE PRESS R TO RESUME GAME");
		Sleep(50);
	}
	Mutex::print(97, 22, ColorCode_Back, "          ");
	Mutex::print(90, 23, ColorCode_Back, "                             ");
}
bool Game::isImpact() {
	for (int i = 0; i < _numberOfBurdens; i++) {
		if (birds[i].Crash(player.get().X(), player.get().Y())) return true;
		if (dinausors[i].Crash(player.get().X(), player.get().Y())) return true;
		if (cars[i].Crash(player.get().X(), player.get().Y())) return true;
		if (trucks[i].Crash(player.get().X(), player.get().Y())) return true;
	}
	return false;
}

void Game::updatePosAnimal() {


	for (int i = 0; i < _numberOfBurdens; i++) {
		birds[i].Move();
		dinausors[i].Move();
	}
}

void Game::cleanGame() {
	for (int i = 0; i < _numberOfBurdens; i++) {
		if (trafficLight.getLight() == Green) {
			trucks[i].Clean();
			cars[i].Clean();
		}
		birds[i].Clean();
		dinausors[i].Clean();
	}
	//player.Clean();
}

void Game::drawGame() {

	//drawFrame();
	trafficLight.Paint();
	for (int i = 0; i < _numberOfBurdens; i++) {
		trucks[i].Paint();
		cars[i].Paint();
		birds[i].Paint();
		dinausors[i].Paint();
	}
	//player.Paint();

}


void Game::levelUP(int c) {
	//drawFrame();
	//drawGame();
	int color = rand() % 15 + 1;
	for (int i = 35; i <= 70; i++) {
		Mutex::print(i, 3, color, "*");
		Mutex::print(i, 21, color, "*");
	}
	for (int i = 3; i <= 21; i++) {
		Mutex::print(35, i, color, "*");
		Mutex::print(70, i, color, "*");
	}
	string s;
	s = char(_numberOfBurdens - 1 + 48);
	Mutex::print(40, 5, color, "LEVEL: " + s);

	s = char(_numberOfBurdens + 48);
	Mutex::print(40, 7, color, "OBJECTS: " + s);

	Mutex::print(40, 9, color, "PRESS L TO SAVE GAME");

	Mutex::print(40, 11, color, "PRESS T TO LOAD GAME");

	Mutex::print(40, 13, color, "PRESS P TO PAUSE GAME");

	Mutex::print(40, 15, color, "PRESS EXC TO EXIT GAME");

	Mutex::print(40, 17, color, "Loading Game...");

	for (int i = 40; i <= 65; i++) {
		Mutex::print(i, 18, color, "_");
		Mutex::print(i, 19, color, "_");
	}

	Mutex::print(40, 19, color, "|");
	Mutex::print(65, 19, color, "|");

	for (int i = 0; i <= 3; i++) {
		Mutex::print(40 + 6 * i, 19, color, "////////");
		Sleep(1000);
	}
	Sleep(1000);
	clrscr();
}
int Game::winner() {
	sf::SoundBuffer buffer;
	sf::Sound sound;
	if (getMusic()) {
		if (!buffer.loadFromFile("Congrat.wav"))
			cout << "NO FOUND" << endl;
	}
	sound.setBuffer(buffer);
	sound.play();
	sound.setLoop(true);
	clrscr();
	char c = ' ';
	int t = -1;
	while (c != '1' && c != '2') {
		int color = 1 + rand() % 15;
		Mutex::print(35, 12, color, "CONGRATURATION YOU ARE THE WINNER!!!");
		Mutex::print(35, 14, color, "1. Play again");
		Mutex::print(35, 16, color, "2. Exit game");
		if (_kbhit()) {
			c = _getch();
			while (_kbhit()) _getch();
		}
		t = c - '1';
		if (t == 0) Mutex::print(30, 15, ColorCode_Yellow, "EXITING FROM THE GAME...");
		Sleep(100);
	}
	sound.stop();
	return t;
}
void Game::updateLight() {
	trafficLight.setFlag(trafficLight.getFlag() + 1);
	if (trafficLight.getFlag() > 200000) {
		if (trafficLight.getLight() == Red) {
			trafficLight.setLight(Green);
		}
		else trafficLight.setLight(Red);
		trafficLight.setFlag(0);
	}
}


Game & Game:: operator=(const Game &other) {
	_numberOfBurdens = other._numberOfBurdens;
	delete[] trucks;
	delete[] cars;
	delete[] birds;
	delete[] dinausors;
	trucks = new Truck[_numberOfBurdens];
	cars = new Car[_numberOfBurdens];
	birds = new Bird[_numberOfBurdens];
	dinausors = new Dinausor[_numberOfBurdens];
	for (int i = 0; i < _numberOfBurdens; i++) {
		trucks[i] = other.trucks[i];
		cars[i] = other.cars[i];
		birds[i] = other.birds[i];
		dinausors[i] = other.dinausors[i];
	}
	player = other.player;
	trafficLight = other.trafficLight;
	return *this;
	round = other.round;
	music = other.music;
}
int Game::startGame() {
	sf::SoundBuffer buffer;
	sf::Sound sound;
	if (getMusic()) {
		if (!buffer.loadFromFile("test.wav"))
			cout << "NO FOUND" << endl;
	}
	sound.setBuffer(buffer);
	sound.play();
	sound.setLoop(true);
	gotoXY(40, 15);
	TextColor(ColorCode_Cyan);
	cout << "  *** MENU *** " << endl;
	gotoXY(40, 16);
	TextColor(ColorCode_Cyan);
	cout << "| 1. New game   |" << endl;
	gotoXY(40, 17);
	cout << "| 2. Load game  |" << endl;
	gotoXY(40, 18);
	cout << "| 3. Settings   |" << endl;
	gotoXY(40, 19);
	cout << "| 4. Exit game  |" << endl;
	gotoXY(5, 25);
	TextColor(ColorCode_Yellow);
	cout << "CONTACT\n";
	gotoXY(5, 26);
	cout << "EMAIL: 1712162@student.humus.edu.vn\n";
	gotoXY(5, 27);
	cout << "SDT  : 0905617076\n";
	gotoXY(80, 25);
	cout << "SUBJECT   : OBJECT ORIENTED PROGRAMMING\n";
	gotoXY(80, 26);
	cout << "FULL NAME : VO QUOC THANG\n";
	gotoXY(80, 27);
	cout << "STUDENT ID: 1712162\n";
	gotoXY(80, 28);
	cout << "17CNTN - UNIVERSITY OF SCIENCE\n";
	gotoXY(80, 29);
	cout << "LECTURER  : NGUYEN MINH HUY\n";
	char key = ' ';
	while (key == ' ') {
		if (_kbhit()) {
			key = _getch();
			while (_kbhit()) _getch();
		}
		int temp = rand() % 16;

		gotoXY(20, 2);
		TextColor(temp);
		cout << "_|_|_|_|  _|_|_|_|_|  _|_|_|_|  _|_|_|_|  _|_|_|_|  _|_|_|_|_|" << endl;
		gotoXY(20, 3);
		cout << "_|            _|      _|    _|  _|        _|            _|    " << endl;
		gotoXY(20, 4);
		cout << "_|_|_|_|      _|      _|_|_|_|  _|_|_|_|  _|_|_|_|      _|    " << endl;
		gotoXY(20, 5);
		cout << "      _|      _|      _|  _|    _|        _|            _|    " << endl;
		gotoXY(20, 6);
		cout << "_|_|_|_|      _|      _|    _|  _|_|_|_|  _|_|_|_|      _|    " << endl;
		gotoXY(15, 8);
		cout << "_|_|_|_|  _|_|_|_|  _|_|_|_|  _|_|_|_|  _|_|_|_|  _|  _|       _|  _|_|_|_|  " << endl;
		gotoXY(15, 9);
		cout << "_|        _|    _|  _|    _|  _|        _|        _|  _| _|    _|  _|        " << endl;
		gotoXY(15, 10);
		cout << "_|        _|_|_|_|  _|    _|  _|_|_|_|  _|_|_|_|  _|  _|   _|  _|  _|  _|_|_|" << endl;
		gotoXY(15, 11);
		cout << "_|        _|  _|    _|    _|        _|        _|  _|  _|     _|_|  _|    _|  " << endl;
		gotoXY(15, 12);
		cout << "_|_|_|_|  _|_   _|  _|_|_|_|  _|_|_|_|  _|_|_|_|  _|  _|       _|  _|_|_|_|" << endl;
		Sleep(200);
	}
	sound.stop();
	return key;

}
Game::~Game() {
	delete[] trucks;
	delete[] cars;
	delete[] birds;
	delete[] dinausors;
}
