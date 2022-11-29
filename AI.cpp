#include "AI.h"
#include <iostream>
using namespace std; 

AI::AI(int num) {
	myPlayerNumber = num;
}

//this function returns the cards that I can play (in terms of the card that is at the top of the pile) represented as a vector 
vector<Card> AI::getPlayableCardsInHand(Card justPlayed, Color choosenCardColor, vector<Card> cardsInHand) {
	//this is the vector that will be returned 
	vector<Card> cardsCanPlay;

	//loop through the vector that holds all of the cards that i have 
	for (int i = 0; i < cardsInHand.size(); i++) {
		//if the chosen color matches the current card's color, I can play that card 
		if (choosenCardColor == cardsInHand[i].getColor()) {
			//cout << "A"<< cardsCanPlay.size() << choosenCardColor;
			cardsCanPlay.push_back(cardsInHand[i]); 
		}
		//if the card at the top of the deck is not a black card (wild or draw4) and the current card's number is the same, I can play that card 
		else if (cardsInHand[i].getColor() != BLACK && justPlayed.getNumber() == cardsInHand[i].getNumber() && justPlayed.getColor() != BLACK) {
			//cout << "B" << cardsCanPlay.size() << choosenCardColor;
			cardsCanPlay.push_back(cardsInHand[i]); 
		}
		//if the current card is a wild card (can always play wild cards) 
		else if (cardsInHand[i].getColor() == BLACK && cardsInHand[i].getNumber() == 0) {
			//cout << "C" << cardsCanPlay.size() << choosenCardColor;
			cardsCanPlay.push_back(cardsInHand[i]); //wild
		}
		//if the current card is a draw 4 card (there are special terms to determine if I can play this card, must be because I do not have the correct color)
		else if (cardsInHand[i].getColor() == BLACK && cardsInHand[i].getNumber() == 1) {
			//cout << "D" << cardsCanPlay.size() << choosenCardColor;
			bool hasColor = false;
			for (int j = 0; j < cardsInHand.size(); j++) {
				//if any of the cards in my deck have the same color as the chosen card color, set the boolean check to true 
				if (choosenCardColor == cardsInHand[j].getColor()) {
					hasColor = true;
				}
			}
			//if there are no cards with the color I need, I can play draw4 
			if (!hasColor) {
				cardsCanPlay.push_back(cardsInHand[i]);
			}
		}
	}
	return cardsCanPlay;
}