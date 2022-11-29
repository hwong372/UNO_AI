
#include "Player.h"
#include <iostream>
#include <string>
using namespace std;

Player::Player(int num, int whichAI) {

	for (int i = 0; i < 5; i++) {
		games.push_back(0);
		diff.push_back(0);
		handSizes.push_back(0);
		pointsPerHand.resize(25);
	}

	playerNumber = num;
	switch (whichAI) {
	case 0:
		theAI = new Haley(num);
		break;
	case 1:
		theAI = new TestAI(num);
		break;
		//... imagine there are 19 more rows here for yall's AIs
	case 2:
		theAI = new Haley2(num);
		break;
	case 3:
		theAI = new Haley3(num);
		break;
	case 4:
		theAI = new Haley4(num);
		break;
	case 5:
		theAI = new Haley5(num);
		break;
	case 6:
		theAI = new Haley6(num);
		break;
	case 7:
		theAI = new Haley7(num);
		break;
	}
}

//if you desire to keep track of what cards other people played...
void Player::onOtherPlayerMove(int playerNumber, Card justPlayed, Color choosenCardColor) {
	theAI->onOtherPlayerMove(playerNumber, justPlayed, choosenCardColor);
}
void Player::onOtherPlayerDraw(int playerNumber) {
	theAI->onOtherPlayerDraw(playerNumber);
}

bool Player::validPlay(int index, Card justPlayed, Color choosenCardColor, bool justDrew, vector<int> scores, vector<int> cardAmountsByPlayer, vector<Card> cardsInHand) {
	//cout << index << " " << hand.size() << "\n";

	//a card cannot be played if the card to play doesn't exist or if the player has no cards 
	if (index < -1 || index > hand.size() - 1) {
		return false;
	}
	if (getNewColor() == BLACK || getNewColor() == NONE) {
		cout << "DRAWING Player line 51" << endl; 
		return false;
	}

	if (index == -1) {
		return true;
	}

	//c represents the card that I want to play --> the card at a desired index in my hand (represented as a vector)
	Card c = hand[index];

	//if the card to play is the same color as the top of the pile, move is valid 
	if (choosenCardColor == c.getColor()) {
		return true; 
	} 
	//if the card to play and the card at the top of the pile is the same numbeer AND a black card (wild or draw 4) was NOT just played, move is valid 
	else if (c.getColor() != BLACK && justPlayed.getNumber() == c.getNumber() && justPlayed.getColor() != BLACK) {
		return true; //same number
	}
	//if the card to play is a wild card 
	else if (c.getColor() == BLACK && c.getNumber() == 0) {
		return true; //wild
	}
	//if the card to play is a draw4 card (black with the number 1)
	else if (c.getColor() == BLACK && c.getNumber() == 1) {
		bool hasColor = false;

		//loop through the vector 
		for (int j = 0; j < cardsInHand.size(); j++) {
			//if the chosen card color (at the top of the pile) is the same as any of the cards in my hand then I do have the color in my hand (cannot play draw 4)
			if (choosenCardColor == cardsInHand[j].getColor()) {
				hasColor = true;
			}
		}
		//if there are no cards in my hand that are of the chosen color, then I can play a draw4
		if (!hasColor) {
			return true;
		}
	}
	cout << "DRAWING Player line 90 " << endl;
	return false;
}

//calls the function on player's AI.
int Player::makeMove(Card justPlayed, Color choosenCardColor, bool justDrew, vector<int> scores, vector<int> cardAmountsByPlayer, int direction) //the returned int refers to the index of which card is played in your hand.
{
	int index = theAI->makeMove(justPlayed, choosenCardColor, justDrew, scores, cardAmountsByPlayer, hand, direction);

	if (!validPlay(index, justPlayed, choosenCardColor, justDrew, scores, cardAmountsByPlayer, hand)) {
		//cout << "bad play detected by AI; card not allowed to be played: print out on player.cpp line 90\n";
		//while (true); //pause program execution!
		return -1;
	}

	return index;
}

Color Player::getNewColor() {
	return theAI->getNewColor();
}

void Player::clearHand() {
	hand.clear();
}

void Player::addToHand(Card c) {
	hand.push_back(c);
}

void Player::removeCardFromHand(int indexOfCard) {
	hand.erase(hand.begin() + indexOfCard);
}

vector<Card> Player::getHandCopy() {
	return hand;
}

int Player::updateStats(vector<Player*> thePlayers) {

	for (int i = 0; i < 5; i++) {
		handSizes[thePlayers[i]->playerNumber] += hand.size();
	}

	int points = 0;
	for (int i = 0; i < hand.size(); i++) {

		points += hand[i].getPoints();
	}
	for (int j = 0; j < 5; j++) {
		pointsPerHand[thePlayers[j]->playerNumber].push_back(points);
	}
	for (int i = 0; i < 5; i++) {
		games[thePlayers[i]->playerNumber] ++;
	}

	mostRecent = points;
	return points;
}

void Player::printStats(vector<Player*> thePlayers) {

	cout << "Player: " << playerNumber << "\n";
	cout << "AI: " << theAI->getName() << "\n";

	cout << "handsize on game end, ";
	for (int i = 0; i < 1; i++) {
		cout << handSizes[i] * 1.0f / games[i] << ",";
	}
	cout << "\n";

	cout << "medium points per game, ";
	for (int i = 0; i < 1; i++) {
		sort(pointsPerHand[i].begin(), pointsPerHand[i].end());
		if (pointsPerHand[i].size() == 0) {
			cout << 0 << ",";
		}
		else {
			cout << pointsPerHand[i][pointsPerHand[i].size() / 2] << ",";
		}
	}
	cout << "\n";

	cout << "average points (lower is better), ";

	for (int j = 0; j < 1; j++) {
		int points = 0;
		for (int i = 0; i < pointsPerHand[j].size(); i++) {
			points += pointsPerHand[j][i];
		}
		cout << points * 1.0f / games[j] << ",";
	}
	cout << "\n";

	cout << "avg difference between players (lower is better), ";
	for (int i = 0; i < 1; i++) {
		cout << diff[i] * 1.0f / games[i] << ",";
	}
	cout << "\n";
}


