#include<SFML/Audio.hpp>
#include <Windows.h>
#include "Game.h"
#include "console.h"
#include <iostream>
#include <istream>
#include <fstream>
#include <sstream>
#include <mutex>
#include <Windows.h>
#include <thread>
#include<string>
using namespace std;
int Step;
Game g;
bool IS_RUNNING, IS_DEAD, IS_STOP;
int cnt = 2;
ofstream outFile;

void FixConsoleWindow() {

	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}
void subThreadPeople() {
	while (IS_RUNNING && !IS_DEAD) {
		if (!g.getPeople().isDead()) {
			if (!IS_STOP) g.updatePosPeople(Step);
			Step = ' ';
			g.getPeople().Paint();
			if (g.getPeople().get().Y() < 5) {
				IS_RUNNING = false;
				g.finishGame();

			}
			if (g.isImpact()) {
				//IS_RUNNING = false;
				IS_DEAD = true;
				Sleep(2000);
			}
			Sleep(100);
			g.getPeople().Clean();
		}

	}
}

void SubThread() {

	while (IS_RUNNING && !IS_DEAD) {
		sf::SoundBuffer buffer;
		sf::Sound sound;
		if (g.getMusic()) {
			if (!buffer.loadFromFile("chicken.wav"))
				cout << "NO FOUND" << endl;
		}
		sound.setBuffer(buffer);
		sound.setVolume(10);
		sound.play();
		sound.setLoop(true);

		if (!IS_STOP) {
			g.updatePosVehicle();
			g.updatePosAnimal();
		}

		g.drawGame();
		Sleep(500);
		g.cleanGame();
		sound.stop();
	}

}
void InGame(int cnt, bool m) {
	sf::SoundBuffer buffer;
	sf::Sound sound;
	if (m) {
		if (!buffer.loadFromFile("gameshow.wav"))
			cout << "NO FOUND" << endl;
	}
	sound.setBuffer(buffer);
	sound.setVolume(20);
	sound.play();
	sound.setLoop(true);
	while (cnt <= 4) {
		g = Game(cnt);
		g.setMusic(m);
		IS_RUNNING = true;
		IS_DEAD = false;
		IS_STOP = false;
		clrscr();
		g.levelUP(cnt);
		g.setRound(cnt - 2);
		g.drawFrame();
		thread t1(SubThread);
		thread t2(subThreadPeople);
		while (1) {
			g.updateLight();
			if (IS_DEAD)  g.isDead();
			if (_kbhit()) {
				Step = _getch();

				if (IS_DEAD)
				{

					if (Step == 'y' || Step == 'Y') {
						IS_DEAD = true;
						IS_RUNNING = false;
						break;
					}
				}
				if (Step == 27) {
					IS_STOP = true;
					IS_RUNNING = false;
					t1.join();
					t2.join();
					if (g.exitGame() == 0) {
						Sleep(200);
						return;
					}
					else {
						sound.stop();
						InGame(cnt, m);
					}

				}
				else {
					if (Step == 'p' || Step == 'P') {
						IS_STOP = true;
						g.pauseGame();
						IS_STOP = false;
					}
					else if (Step == 'l' || Step == 'L') {
						IS_STOP = true;
						string filename;
						Mutex::print(90, 22, 14, "Save game");
						Mutex::print(90, 24, 14, "FILE LOCATION:");
						Mutex::Enter(105, 24, filename);
						outFile.open(filename.c_str(), ios::binary | ios::out);
						outFile << cnt;
						outFile.close();
						IS_STOP = false;
						Mutex::print(90, 22, 14, "              ");
						Mutex::print(90, 24, 14, "                          ");

					}
					else if (Step == 't' || Step == 'T') {
						IS_RUNNING = false;
						ifstream ifile;
						int t;
						string s;
						TextColor(14);
						Mutex::print(90, 22, 14, "Load game");
						Mutex::print(90, 24, 14, "FILE LOCATION: ");
						Mutex::Enter(105, 24, s);
						ifile.open(s, ios::binary | ios::in);
						if (ifile.is_open()) {
							ifile >> t;
							cnt = t;
							t1.join();
							t2.join();
							sound.stop();
							InGame(t, m);
							return;
						}
						else {
							Mutex::print(105, 21, 14, "NOT FOUND");
							Mutex::print(90, 22, 14, "              ");
							Mutex::print(90, 24, 14, "                     ");
						}

					}
				}


				while (_kbhit()) _getch();

			}
			if (!IS_RUNNING && cnt < 5) break;

		}

		if (!IS_DEAD) cnt++;
		else cnt = 2;
		if (cnt == 5) {
			if (!g.winner()) cnt = 2;
		}
		t1.join();
		t2.join();

	}
	sound.stop();
}

mutex Mutex::mu;
int main()
{
	FixConsoleWindow();
	g = Game(2);
	char c = g.startGame();

	/******************************************************************************/


	while (c != '1' && c != '2' && c != '4') {
		TextColor(14);

		if (c == '3') {
			clrscr();
			gotoXY(40, 13);
			cout << "***OPTIONS***";
			gotoXY(37, 15);
			cout << "1. TURN ON THE MUSIC.";
			gotoXY(37, 17);
			cout << "2. TURN OFF THE MUSIC.";
			char temp = ' ';
			while (temp != '1' && temp != '2') {
				if (_kbhit()) {
					temp = _getch();
					while (_kbhit()) _getch();
				}
			}
			if (temp = '2') g.setMusic(0);
			clrscr();
		}
		else {
			gotoXY(30, 21);
			cout << "THIS FUNCTION IS NOT AVAILBLE. PLEASE CHOOSE A NEW KEY !";
		}
		c = g.startGame();
	}

	switch (c) {
	case('1'): {
		InGame(cnt, g.getMusic());
		break;
	}
	case('2'): {
		ifstream ifile;
		string s;
		TextColor(14);
		gotoXY(35, 21);
		cout << "FILE LOCATION: ";
		Mutex::Enter(50, 21, s);
		ifile.open(s);
		if (ifile.is_open()) {
			ifile >> cnt;
			InGame(cnt, g.getMusic());
		}
		else {
			gotoXY(50, 21);
			cout << "NOT FOUND: ";
		}
		break;
	}
	case('3'): {

		break;

	}
	case('4'): {
		clrscr();
		break;
	}

	}

	return 0;
}

