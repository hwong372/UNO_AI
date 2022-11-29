#include "Haley2.h"
#include <iostream>
using namespace std;

//Differences:
//line 269 is false instead of true

Haley2::Haley2(int playerNumber) : AI(playerNumber)
{

}

//tracks all player moves 
void Haley2::onOtherPlayerMove(int playerNumber, Card justPlayed, Color choosenCardColor) {
	//if the card just played is a reverse card, switch the direction in this local area to ensure the myDirection variable is accurate
	if (justPlayed.getNumber() == 12) {
		//if the direction is currently clockwise, switch the direction to counterclockwise
		if (myDirection == 1) {
			myDirection = -1;
		}
		else if (myDirection == -1) {
			myDirection = 1;
		}
	}



}

//if another player draws
void Haley2::onOtherPlayerDraw(int playerNumber) {
	//Case: when the player before me draws 
	//if the game is going clockwise
	if (myDirection == 1) {
		//if I am player 0, the player before me will be player 4
		if (getNum() == 0 && playerNumber == 4) {
			playerBeforeDrew = true;
		}
		//otherwise, if I am any other player, the player before me will be my number - 1
		else if (playerNumber == getNum() - 1) {
			playerBeforeDrew = true;
		}
	}
	//if the game is going counterclockwise
	else if (myDirection == -1) {
		//if I am player 4, the player before me will be player 0
		if (getNum() == 4 && playerNumber == 0) {
			playerBeforeDrew = true;
		}
		//otherwise, if I am any other player, the player number before me will be my number+1
		else if (playerNumber == getNum() + 1) {
			playerBeforeDrew = true;
		}
	}

	//keep track of who is drawing 
	if (playerNumber == 0) {
		player0Draws++;
	}
	if (playerNumber == 1) {
		player1Draws++;
	}
	if (playerNumber == 2) {
		player2Draws++;
	}
	if (playerNumber == 3) {
		player3Draws++;
	}
	if (playerNumber == 4) {
		player4Draws++;
	}

}
//this function finds the most common color 
Color Haley2::findMostCommonColor(vector<Card> cardsInHand) {
	//this array represents the number of cards that are a certain color 
	//the indices represent different colors: red, green, blue, yellow are 0, 1, 2, 3
	int numOfEachColor[4];

	//assign the initial values in the array -- set them to 0
	for (int i = 0; i < 4; i++) {
		numOfEachColor[i] = 0;
	}

	//loop through all the cards in my hand 
	for (int i = 0; i < cardsInHand.size(); i++) {
		//if the current card is a certain color, update the corresponding value in the vector
		if (cardsInHand[i].getColor() == RED) {
			numOfEachColor[0] += 1;
		}
		else if (cardsInHand[i].getColor() == GREEN) {
			numOfEachColor[1] += 1;
		}
		else if (cardsInHand[i].getColor() == BLUE) {
			numOfEachColor[2] += 1;
		}
		else if (cardsInHand[i].getColor() == YELLOW) {
			numOfEachColor[3] += 1;
		}
	}

	//CHECK that the color array is correct
	for (int i = 0; i < 4; i++) {
		if (i == 0) {
			cout << "There are " << numOfEachColor[i] << " red cards" << endl;
		}
		else if (i == 1) {
			cout << "There are " << numOfEachColor[i] << " green cards" << endl;
		}
		else if (i == 2) {
			cout << "There are " << numOfEachColor[i] << " blue cards" << endl;
		}
		else if (i == 3) {
			cout << "There are " << numOfEachColor[i] << " yellow cards" << endl;
		}
	}

	int indexOfMaxColor = 0;
	//loop through the color vector 
	for (int i = 3; i > 0; i--) {
		if (numOfEachColor[i] > numOfEachColor[i - 1]) {
			indexOfMaxColor = i;
		}
	}

	//once the max index is found, associate the index with the color 
	if (indexOfMaxColor == 0) {
		return RED;
	}
	if (indexOfMaxColor == 1) {
		return GREEN;
	}
	if (indexOfMaxColor == 2) {
		return BLUE;
	}
	if (indexOfMaxColor == 3) {
		return YELLOW;
	}
	else {
		return RED;
	}

}

//this function returns the color with only 1 card left, returns BLACK if no card colors only have 1 left 
Color Haley2::countCardsOfEachColor(vector<Card> cardsInHand) {
	//this is a suspicious initalization, might be a source of an error...
	Color toReturn = BLACK;

	//this array represents the number of cards that are a certain color 
	//the indices represent different colors: red, green, blue, yellow are 0, 1, 2, 3
	int numOfEachColor[4];

	//assign the initial values in the array -- set them to 0
	for (int i = 0; i < 4; i++) {
		numOfEachColor[i] = 0;
	}

	//loop through all the cards in my hand 
	for (int i = 0; i < cardsInHand.size(); i++) {
		//if the current card is a certain color, update the corresponding value in the vector
		if (cardsInHand[i].getColor() == RED) {
			numOfEachColor[0] += 1;
		}
		else if (cardsInHand[i].getColor() == GREEN) {
			numOfEachColor[1] += 1;
		}
		else if (cardsInHand[i].getColor() == BLUE) {
			numOfEachColor[2] += 1;
		}
		else if (cardsInHand[i].getColor() == YELLOW) {
			numOfEachColor[3] += 1;
		}
	}

	//loop through the values in the array and see if any of them are 1
	for (int i = 0; i < 4; i++) {
		//if i have a color of 1 card only 
		if (numOfEachColor[i] == 1) {
			if (i == 0) {
				toReturn = RED;
			}
			else if (i == 1) {
				toReturn = GREEN;
			}
			else if (i == 2) {
				toReturn = BLUE;
			}
			else if (i == 3) {
				toReturn = YELLOW;
			}
		}
	}
	return toReturn;
}

//returns the index of the card to play
int Haley2::makeMove(Card justPlayed, Color choosenCardColor, bool justDrew, vector<int> scores, vector<int> cardAmountsByPlayer, vector<Card> cardsInHand, int direction) {
	int toReturn = -1;

	/*for (int i = 0; i < cardAmountsByPlayer.size(); i++)
	{
		cout << cardAmountsByPlayer[i] <<"\n";
	}*/

	vector<Card> cards = getPlayableCardsInHand(justPlayed, choosenCardColor, cardsInHand);
	cout << "The number of playable cards is: " << cards.size() << endl;

	if (cards.size() == 0) {
		return -1; //draw
	}

	//SPECIAL CASES: based on the actions/situations of the other players 
	//CASE: if the player after me has 1 card left
	//FIRST determine which player is after me 
	//if the direction is going clockwise 
	if (myDirection == 1) {
		//special case for when my number is 4
		if (getNum() == 4) {
			playerAfterMe = 0;
		}
		else {
			playerAfterMe = getNum() + 1;
		}
	}
	//if the direction is going counter clockwise
	if (myDirection == -1) {
		//special case for when my number is 0
		if (getNum() == 0) {
			playerAfterMe = 4;
		}
		else {
			playerAfterMe = getNum() - 1;
		}
	}

	//once I know the player after me, determine if that player has 1 cards 
	if (cardAmountsByPlayer[playerAfterMe] == 1) {
		cout << "LOOK HERE I'M PLAYING A SPECIAL" << endl;
		cout << "Player after me is " << playerAfterMe << endl;

		//play a special card if possible 
		//loop through the cards in hand to find any special card that is a valid card to play 
		for (int i = 0; i < cardsInHand.size(); i++) {
			//try to play a draw2 first 
			if (cardsInHand[i].getColor() == choosenCardColor && cardsInHand[i].getNumber() == 11) {
				//return the index of the reverse card to play the reverse card 
				return i;
			}
			//if cannot play a draw2, play a skip  
			else if (cardsInHand[i].getColor() == choosenCardColor && cardsInHand[i].getNumber() == 10) {
				//return the index of the reverse card to play the reverse card 
				return i;
			}
			//if cannot play a draw2 or a skip --> play a reverse card 
			else if (cardsInHand[i].getColor() == choosenCardColor && cardsInHand[i].getNumber() == 12) {
				//return the index of the reverse card to play the reverse card 
				return i;
			}
		}
	}
	//CASE: if any players have 3 cards or less in their hand, start playing wild cards and draw4 cards 
	//loop through the array where each index represents the player number and the value represents the number of cards they have 
	for (int i = 0; i < cardAmountsByPlayer.size(); i++) {
		//if any player has <= 4 cards
		if (cardAmountsByPlayer[i] <= 4) {
			cout << "The game is ending!!!" << endl;
			// play a special card if possible 
			//loop through the cards in hand to find any special card that is a valid card to play 
			for (int i = 0; i < cardsInHand.size(); i++) {
				if (cardsInHand[i].getColor() == justPlayed.getColor()) {
					canPlayDraw4 = false;
					break;
				}
				//try to play a draw4 first -- can only play this card as a last option
				if (canPlayDraw4) {
					if (cardsInHand[i].getColor() == BLACK && cardsInHand[i].getNumber() == 1) {
						cout << "I have a black card! I will play it because the game is ending" << endl;
						//return the index of the draw4 card to play the draw4 card
						toReturn = i;
						return toReturn;
					}
				}
				//try to play a wild next  
				else if (cardsInHand[i].getColor() == BLACK && cardsInHand[i].getNumber() == 0) {
					savedColor = findMostCommonColor(cardsInHand);
					cout << "Playing a wild card and changing the color to " << savedColor << endl;

					//reset the number of draws for each player 
					player0Draws = 0;
					player0Draws = 1;
					player0Draws = 2;
					player0Draws = 3;
					player0Draws = 4;

					//return the index of the reverse card to play the reverse card 
					return i;
				}
				//try to play a draw2 next 
				else  if (cardsInHand[i].getColor() == choosenCardColor && cardsInHand[i].getNumber() == 11) {
					//return the index of the reverse card to play the reverse card 
					return i;
				}
				//try to play a skip next
				else if (cardsInHand[i].getColor() == choosenCardColor && cardsInHand[i].getNumber() == 10) {
					//return the index of the reverse card to play the reverse card 
					return i;
				}
				//try to play a reverse card
				else if (cardsInHand[i].getColor() == choosenCardColor && cardsInHand[i].getNumber() == 12) {
					//return the index of the reverse card to play the reverse card 
					return i;
				}
			}
		}

	}
	//CASE: if the player before me draws 
	if (playerBeforeDrew) {
		//play a reverse card if possible 
		//loop through the cards in hand to find any reverse card that is a valid card to play 
		for (int i = 0; i < cardsInHand.size(); i++) {
			//if th current card matches the color at the top of the stack and is a number 12 (reverse card) 
			if (cardsInHand[i].getColor() == choosenCardColor && cardsInHand[i].getNumber() == 12) {
				//return the index of the reverse card to play the reverse card 
				return i;
			}
		}
	}

	//CASE: if the color has stayed the same and any player has not drawn 


	//GENERAL CASE: play the highest value card 
	int indexOfHighestCard = 0;
	//loop through the number of the playable cards
	for (int i = 0; i < cards.size(); i++) {
		//if the current card has a higher value than the current highest card, reset the index of the highest card 
		//only check the cards with numbers (not the special cards like skip, draw2, reverse or the black cards)
		if (cards[i].getNumber() < 10 && cards[i].getColor() != BLACK) {
			if (cards[i].getNumber() > cards[indexOfHighestCard].getNumber()) {
				indexOfHighestCard = i;
			}
		}
	}

	//loop thorough the number of cards in hand to find the card to play 
	for (int i = 0; i < cardsInHand.size(); i++) {
		//if the card is found (should always be found)
		if (cardsInHand[i] == cards[indexOfHighestCard]) {
			//return the index of the card with the highest value 
			toReturn = i;
		}
	}

	//loop through the cards that I have to determine which card is being played 
	for (int i = 0; i < cardsInHand.size(); i++) {
		//if I am playing a reverse card
		if (cardsInHand[i].getNumber() == 12) {
			//control the direction when I play a reverse card 
				//if the card just played is a reverse card 
			if (justPlayed.getNumber() == 12) {
				//if the direction is currently clockwise, switch the direction to counterclockwise
				if (myDirection == 1) {
					myDirection = -1;
				}
				else if (myDirection == -1) {
					myDirection = 1;
				}
			}
		}
	}

	//if the card that I have decided to play is the last card I have of that color 
	if (cardsInHand[toReturn].getColor() == countCardsOfEachColor(cardsInHand)) {
		for (int i = 0; i < cardsInHand.size(); i++) {
			//if I can, switch the color to the most common color 
			//first check if I have a number of that color
			//if the current number is the same as the number just played (valid move)
			if (cardsInHand[i].getNumber() == justPlayed.getNumber()) {
				//if the matching number has the same color has the most common color 
				if (cardsInHand[i].getColor() == findMostCommonColor(cardsInHand)) {
					cout << "Switching the color to the most common color so I still have 1 of each color" << endl;
					//play that card instead
					toReturn = i;
				}
				else {
					cout << "Switching the color so I still have 1 of each color" << endl;
					toReturn = i;
				}
			}
		}
	}

	return toReturn;

	/*
	for (int i = 0; i < cardsInHand.size(); i++) {
		if (cardsInHand[i].getColor() == YELLOW && choosenCardColor == YELLOW) {
			return i;
		}
	}
	*/



	//special card key
	//reverse = 12, skip = 10, and draw2 = 11 of any of red/blue/green/yellow.
	//wild is black 0, draw4 is black 1

	savedColor = YELLOW; //if I am playing a draw4 or wild, i set this variable to set the new color i am picking; yellow is the perfect color to choose every time i play a draw4/wild for this ai! I guess?


	//should not get here in my AI???
	cerr << "bbaaaad happeeeened\n";
	return -1;
}

string Haley2::getName()
{
	return "Haley2";
}



Color Haley2::getNewColor()
{
	return savedColor;
}


