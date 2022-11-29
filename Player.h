#pragma once
#include <vector>
#include <algorithm>
using namespace std;

#include "Card.h"
#include "AI.h"
#include "Haley.h"
#include "Haley2.h"
#include "Haley3.h"
#include "Haley4.h"
#include "Haley5.h"
#include "Haley6.h"
#include "Haley7.h"
#include "TestAI.h"

class Player
{

protected:
	vector<Card> hand;

	int playerNumber;

	AI* theAI;

	vector<int> handSizes;
	vector<vector<int>> pointsPerHand;
	vector<int> games;

	bool validPlay(int index, Card justPlayed, Color choosenCardColor, bool justDrew, vector<int> scores, vector<int> cardAmountsByPlayer, vector<Card> cardsInHand);

public:
	Player(int num, int whichAI);

	//if you desire to keep track of what cards other people played...
	void onOtherPlayerMove(int playerNumber, Card justPlayed, Color choosenCardColor);
	void onOtherPlayerDraw(int playerNumber);

	//the returned int refers to the index of which card is played in your hand.
	int makeMove(Card justPlayed, Color choosenCardColor, bool justDrew, vector<int> scores, vector<int> cardAmountsByPlayer, int direction); 

	Color getNewColor();

	void clearHand();

	//this will add cards to the vector if the player must draw 
	void addToHand(Card c);

	//this will remove cards from the vector depending on the card played 
	void removeCardFromHand(int indexOfCard);

	vector<Card> getHandCopy();

	int mostRecent = 0;
	//int whichAI;

	vector<float> diff;

	int updateStats(vector<Player*> thePlayers);

	void printStats(vector<Player*> thePlayers);

	string getName() { return theAI->getName(); }
	int getNum() { 
		return theAI->getNum(); 
	}
}; 