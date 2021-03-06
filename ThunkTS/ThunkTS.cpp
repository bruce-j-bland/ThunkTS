//
//  Runs the game
//  ThunkTS
//
//
#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>
#include "Entities.h"

using namespace std;

//Used to prevent double triggering from enter key
void sleep(int milliseconds) {
	std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

void functionalityTest() {
	Board* q = new Board;
	Wall* w = new Wall(q);
	Blank* b = new Blank(q);
	Hole* h = new Hole(q);
	EntityList* e = new EntityList(q);
	e->add(w);
	e->add(b);
	e->add(h);
	cout << w->getID() << '\n';
	cout << b->getID() << '\n';
	cout << h->getID() << '\n';
	cout << e->getID() << '\n';
	cout << w->getChar() << '\n';
	cout << b->getChar() << '\n';
	cout << h->getChar() << '\n';
	cout << e->getChar() << '\n';
	cout << w->isSolid(b) << '\n';
	cout << b->isSolid(b) << '\n';
	cout << h->isSolid(b) << '\n';
	cout << e->isSolid(b) << '\n';
	h->passedOver(b);
	cout << w->getID() << '\n';
	cout << b->getID() << '\n';
	cout << h->getID() << '\n';
	cout << e->getID() << '\n';
	delete w;
	delete b;
	delete h;
	delete e;
	delete q;
}

void gameLogicTest() {
	Board* b = new Board;
	b->makeBoard(1);
	//b->makeBoard(2);
	b->start();
	b->print();
	b->next();
	b->input(Direction::right);
	while (!b->act());
	b->print();
	b->next();
	b->next();
	b->input(Direction::right);
	while (!b->act());
	b->print();
	b->next();
	b->next();
	b->input(up);
	while (!b->act());
	b->print();
	delete b;
}

void clear() {
	for (int i = 0; i<100; i++)
		cout << "\n";
}

//Alpha version help function
void help() {
	clear();
	cout << "Welcome to ThunkTS Alpha version, a simple game for two players.\n"
		<< "You objective is to trap your opponent or trick them into falling into a Hole.\n"
		<< "There are three types of tiles on the basic maps provided: the Players, Holes, and Walls.\n"
		<< "Type anything to continue.\n";

	string s;
	cin >> s;
	cout << "\nPlayer 1 is represented by the character A. Player 2 with character B.\n"
		<< "Holes are represented with the character X and Walls with the character #.\n"
		<< "The outside of the board is labled for your convinience.\n"
		<< "Type anything to continue.\n";
	cin >> s;

	cout << "\nTurns are divided into two phases: Drop and Move. During the Drop Phase, the active player will have the opportunity to drop a new Wall tile onto the board. You are not allowed to place a Wall on top of a player or another wall. Do note that if you place a Wall on top of a Hole, the Wall will be destroyed.\n"
		<< "To place a Wall, follow the prompts. When a Wall has been placed (or destroyed), the move phase will start.\n"
		<< "Type anything to continue.\n";

	cin >> s;
	cout << "\nIn the Move Phase, you will select a direction to move your Player, Up, Down, Left, or Right. Your piece will move until it runs into a Wall, another Player, or a Hole. If you are adjacent to a Wall or a Player, you won't be allowed to move into them. If you run into a Hole or are unable to move, you lose.\n"
		<< "After you make your move, it will be the next player's turn.\n"
		<< "Type anything to continue.\n";
	cin >> s;

	cout << "\nThere are three maps provided in the Alpha version, Classic, Invert, and Chaos.\n"
		<< "The Classic Map is a 9x9 board surrounded by walls. It has a single hole in the center.\n"
		<< "The Invert Map is a 9x9 board surrounded by holes. It has a single wall in the center.\n"
		<< "The Chaos Map is a 9x9 board designed to show off functionality of the game engine. Because of graphical limitations, this game mode is not recommended.\n"
		<< "Type 1 for more detail about the Chaos Map, and anything else to go back to the main menu.\n";
	cin >> s;

	if (s[0] == '1') {
		cout << "\nThe Chaos Map is built to demonstrate the modular nature of the ThunkTS game engine.\n"
			<< "On the Chaos Map, the turn order is altered. Instead of a drop phase followed by a move phase, a single turn begins with a move phase, followed by a drop phase, followed by a second move phase.\n"
			<< "Moreover, the Chaos Map contains three additional object types: Panels, Bumpers, and Fallaways.\n"
			<< "Type anything to continue.\n";
			cin >> s;

		cout << "\nPanels are marked by the characters: >, <, ^, v, !, and ). Moving on top of the Panel will cause the player to change direction and continue moving.\n"
			<< "The ! Panel will cause the player to reverse direction of their motion. The ) Panel will cause the player to turn clockwise.\n"
			<< "The other four will cause the player to move in the indicated direction, no matter which side you enter from.\n"
			<< "You may place Wall tiles on top of Panels.\n"
			<< "Type anything to continue.\n";
		cin >> s;

		cout << "\nBumper Tiles are marked by the character &. They act as special Walls.\n"
			<< "If a player runs into a Bumper, they will be bounced back in the opposite direction.\n"
			<< "A bumper is destroyed the first time it is hit.\n"
			<< "You may not place Wall tiles on Bumpers. Nor can you run into them if you are right next to them.\n"
			<< "Type anything to continue.\n";
		cin >> s;

		cout << "\nFallaway tiles are marked by a number, 1-9. They act as special Holes.\n"
			<< "Every time a player steps on a Fallaway tile, its number decreases by 1. When it reaches 0, it will turn into a regular hole.\n"
			<< "If a player ends their turn on a Fallaway tile, they will not will not fall, even if the countdown is at 1.\n"
			<< "You may place Wall tiles on top of Fallaway tiles. The Wall will not be destroyed unless the countdown has already reached zero.\n"
			<< "Type anything to go back to the main menu.\n";
		cin >> s;
	}

	clear();
}

//Alpha version of the game. Only supports two players and three boards
void play(int i) {
	clear();
	Board* b = new Board;
	b->makeBoard(i);
	b->start();
	Phase p = b->getPhase();
	while (b->getPhase() != Phase::end) {
		clear();
		b->print();
		int t = b->getTurn();
		if (p == Phase::place) {
			cout << "It's Player " << t + 1 << "'s placement phase.\n";
			bool doPrint = true;
			while (true) {
				if (doPrint) {
					cout << "Please enter a column number 1-9 for wall placement.\n";
				}
				else {
					doPrint = true;
				}
				string input = "";
				int x;
				sleep(20);
				getline(cin, input);
				stringstream stream(input);
				if (!(stream >> x)) {
					doPrint = false;
					continue;
				}
				if (x<1 || x >9)
					continue;

				int y;
				doPrint = true;
				while (true) {
					if (doPrint) {
						cout << "Please enter a row number 1-9 for wall placement.\n";
					}
					else {
						doPrint = true;
					}
					sleep(20);
					getline(cin, input);
					stringstream stream(input);
					if (!(stream >> y)){
						doPrint = false;
						continue;
					}
					if (y<1 || y> 9)
						continue;
					break;
				}
				if (b->drop(x, y))
					break;
				else
					cout << "Selected position must not contain a wall or a player.\n";
			}
			while (!(b->act()));
			if (b->isDead(0)) {
				clear();
				b->print();
				cout << "Player 1 is trapped. Player 2 wins.\n";
				break;
			}
			if (b->isDead(1)) {
				clear();
				b->print();
				cout << "Player 2 is trapped. Player 1 wins.\n";
				break;
			}
		}
		if (p == Phase::move) {
			cout << "It's Player " << t + 1 << "'s movement phase.\n";
			Direction dir;
			while (true) {
				cout << "Please enter one of the following directions: ";
				bool u = false;
				if (b->isLegal(Direction::up)) {
					cout << "'up',";
					u = true;
				}
				bool d = false;
				if (b->isLegal(Direction::down)) {
					cout << "'down',";
					d = true;
				}
				bool l = false;
				if (b->isLegal(Direction::left)) {
					cout << "'left',";
					l = true;
				}
				bool r = false;
				if (b->isLegal(Direction::right)) {
					cout << "'right',";
					r = true;
				}
				cout << "\b. You only need the first letter.\n";
				sleep(20);
				string input = "";
				cin >> input;
				char c = input.at(0);
				if (u && (c == 'u' || c == 'U')) {
					dir = Direction::up;
					break;
				}
				if (d && (c == 'd' || c == 'D')) {
					dir = Direction::down;
					break;
				}
				if (l && (c == 'l' || c == 'L')) {
					dir = Direction::left;
					break;
				}
				if (r && (c == 'r' || c == 'R')) {
					dir = Direction::right;
					break;
				}
			}
			b->input(dir);
			while (!(b->act()));
			int w = (t + 1) % 2;
			if (b->isDead(t)) {
				clear();
				b->print();
				cout << "Player " << t + 1 << " fell in a hole. Player " << w + 1 << " wins.\n";
				break;
			}
			if (b->isDead(w)) {
				clear();
				b->print();
				cout << "Player " << w + 1 << " is trapped. Player " << t + 1 << " wins.\n";
				break;
			}
		}
		p = b->next();
	}

	delete b;
	string s;
	cout << "Type anything to go back to the main menu.\n";
	cin >> s;

}

void ASCIImain() {
	cout << "ThunkTS Alpha\nby Bruce Bland\n\n";

	int i = 0;

	while (i != -1) {
		clear();
		cout << "Main Menu:\nHelp: 1\nClassic Map: 2\nInvert Map: 3\nChaos Map: 4\nExit: -1\n";
		string input = "";
		getline(cin, input);
		stringstream stream(input);
		if (!(stream >> i))
			continue;
		if (i == 2 || i == 3 || i == 4)
			play(i - 1);
		if (i == 1)
			help();
	}
}

//Main menu
int main(int argc, const char * argv[])
{
	ASCIImain();

	return 0;
}

