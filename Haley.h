#pragma once
#include "AI.h"
#include <iostream>
using namespace std; 

class Haley : public AI {

private:
	Color savedColor = RED;

	bool playerBeforeDrew = false; 
	int myDirection = 1; 
	int playerAfterMe; 

	bool changeColorNow = false; 
	int player0Draws = 0; 
	int player1Draws = 0; 
	int player2Draws = 0; 
	int player3Draws = 0; 
	int player4Draws = 0; 

	bool canPlayDraw4 = false; 

	Color findMostCommonColor(vector<Card> cardsInHand); 
	Color countCardsOfEachColor(vector<Card> cardsInHand); 
	

public:
	Haley(int playerNumber);

	void onOtherPlayerMove(int playerNumber, Card justPlayed, Color choosenCardColor);

	void onOtherPlayerDraw(int playerNumber);

	//returns the index of the card to play
	int makeMove(Card justPlayed, Color choosenCardColor, bool justDrew, vector<int> scores, vector<int> cardAmountsByPlayer, vector<Card> cardsInHand, int direction);

	string getName();

	Color getNewColor();

};