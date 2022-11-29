#pragma once
#pragma once
#include "AI.h"
#include <iostream>
using namespace std;

class Haley4 : public AI {

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

	bool canPlayDraw4 = true;
	bool canPlayWild; 

	bool player0PlayedWild; 
	Color p0ColorChoice;
	bool player1PlayedWild;
	Color p1ColorChoice;
	bool player2PlayedWild;
	Color p2ColorChoice;
	bool player3PlayedWild;
	Color p3ColorChoice;
	bool player4PlayedWild;
	Color p4ColorChoice;



	Color findMostCommonColor(Card justPlayed, Color chosenColor, vector<Card> cardsInHand);
	Color countCardsOfEachColor(Card justPlayed, Color chosenColor, vector<Card> cardsInHand);

	//this function takes the index of the card to play (from the playableCards vector) and uses it to find the index of where
	//that card is in the cardsInHand vector --> returns the correct index 
	int findFinalCardIndex(vector<Card>cardsInHand, int indexInPlayableCards, Card justPlayed, Color chosenCardColor);

public:
	Haley4(int playerNumber);

	void onOtherPlayerMove(int playerNumber, Card justPlayed, Color choosenCardColor);

	void onOtherPlayerDraw(int playerNumber);

	//returns the index of the card to play
	int makeMove(Card justPlayed, Color choosenCardColor, bool justDrew, vector<int> scores, vector<int> cardAmountsByPlayer, vector<Card> cardsInHand, int direction);

	string getName();

	Color getNewColor();

};
