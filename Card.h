#include <iostream>
#include <string>
using namespace std;

#pragma once
enum Color { 
	RED = 0, BLUE, GREEN, YELLOW, BLACK, NONE 
};


class Card {
private:
	//0-9 are numbers, 10 is skip, 11 is drawtwo, 12 is reverse
	//for black cards: 0 is wild, 1 is draw four.
	int number; 
	Color theColor;
	Color colorChangedTo;
	int points;

public:
	Card(int num, Color c);
	Card();

	int getNumber();
	Color getColor();
	Color getColorChange();

	void setColorChange(Color newc);

	int getPoints();

	bool operator==(Card& other);
};

string cardTOString(Card c);
