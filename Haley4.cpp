#include "Haley4.h"
#include "Card.h"
#include <iostream>
using namespace std;

//Differences:
//line 269 is false instead of true

Haley4::Haley4(int playerNumber) : AI(playerNumber)
{

}

//tracks all player moves 
void Haley4::onOtherPlayerMove(int playerNumber, Card justPlayed, Color choosenCardColor) {
	//if the card just played is a reverse card, switch the direction in this local area to ensure the myDirection variable is accurate
	if (justPlayed.getNumber() == 12) {
		//if the direction is currently clockwise, switch the direction to counterclockwise
		if (myDirection == 1) {
			cout << "switching the direction" << endl;
			myDirection = -1;
		}
		else if (myDirection == -1) {
			cout << "switching the direction" << endl;
			myDirection = 1;
		}
	}

	//keep track of the cards that each player just played 
	if (playerNumber == 0) {
		if (justPlayed.getColor() == BLACK && justPlayed.getNumber() == 0) {
			player0PlayedWild = true; 
			p0ColorChoice == justPlayed.getColor(); 
		}
	}
	if (playerNumber == 1) {
		if (justPlayed.getColor() == BLACK && justPlayed.getNumber() == 1) {
			player1PlayedWild = true;
			p1ColorChoice == justPlayed.getColor();
		}
	}
	if (playerNumber == 2) {
		if (justPlayed.getColor() == BLACK && justPlayed.getNumber() == 2) {
			player2PlayedWild = true;
			p2ColorChoice == justPlayed.getColor();
		}
	}
	if (playerNumber == 3) {
		if (justPlayed.getColor() == BLACK && justPlayed.getNumber() == 3) {
			player3PlayedWild = true;
			p3ColorChoice == justPlayed.getColor();
		}
	}
	if (playerNumber == 4) {
		if (justPlayed.getColor() == BLACK && justPlayed.getNumber() == 4) {
			player4PlayedWild = true;
			p4ColorChoice == justPlayed.getColor();
		}
	}
}

//if another player draws
void Haley4::onOtherPlayerDraw(int playerNumber) {
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
Color Haley4::findMostCommonColor(Card justPlayed, Color chosenColor, vector<Card> cardsInHand) {
	vector<Card> playableCards = getPlayableCardsInHand(justPlayed, chosenColor, cardsInHand);

	//this array represents the number of cards that are a certain color 
	//the indices represent different colors: red, green, blue, yellow are 0, 1, 2, 3
	int numOfEachColor[4];

	//assign the initial values in the array -- set them to 0
	for (int i = 0; i < 4; i++) {
		numOfEachColor[i] = 0;
	}

	//loop through all the cards in my hand 
	for (int i = 0; i < playableCards.size(); i++) {
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
Color Haley4::countCardsOfEachColor(Card justPlayed, Color chosenColor, vector<Card> cardsInHand) {
	vector<Card>playableCards = getPlayableCardsInHand(justPlayed, chosenColor, cardsInHand);

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
	for (int i = 0; i < playableCards.size(); i++) {
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
int Haley4::findFinalCardIndex(vector<Card>cardsInHand, int indexInPlayableCards, Card justPlayed, Color chosenCardColor) {
	vector<Card> playableCards = getPlayableCardsInHand(justPlayed, chosenCardColor, cardsInHand);
	for (int i = 0; i < cardsInHand.size(); i++) {
		if (cardsInHand[i].getColor() == playableCards[indexInPlayableCards].getColor() && cardsInHand[i].getNumber() == playableCards[indexInPlayableCards].getNumber()) {
			return i;
		}
	}
	return -1;
}

//returns the index of the card to play
int Haley4::makeMove(Card justPlayed, Color choosenCardColor, bool justDrew, vector<int> scores, vector<int> cardAmountsByPlayer, vector<Card> cardsInHand, int direction) {
	int toReturn = -1;

	vector<Card> playableCards = getPlayableCardsInHand(justPlayed, choosenCardColor, cardsInHand);
	cout << "The number of playable cards is: " << playableCards.size() << endl;

	if (playableCards.size() == 0) {
		cout << "I AM DRAWING" << endl;
		return -1; //draw
	}

	//if I have one card left 
	if (playableCards.size() == 1) {

	}


	//SPECIAL CASES: based on the actions/situations of the other player
	//CASE: if the player after me has 1 card left, play a draw2, skip, or reverse 
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
		cout << "LOOK HERE I'M TRYING TO PLAY A SPECIAL" << endl;
		cout << "Player after me is " << playerAfterMe << endl;

		//play a special card if possible 
		//loop through the cards in hand to find any special card that is a valid card to play 
		for (int i = 0; i < playableCards.size(); i++) {
			//try to play a draw2 first
			if (playableCards[i].getColor() == choosenCardColor) {
				//try to play a draw2
				if (playableCards[i].getNumber() == 11) {
					cout << "I am trying to play " << cardTOString(playableCards[i]) << endl;
					return findFinalCardIndex(cardsInHand, i, justPlayed, choosenCardColor);
				}
				//or try to play a skip 
				else if (playableCards[i].getNumber() == 10) {
					cout << "I am trying to play " << cardTOString(playableCards[i]) << endl;
					return findFinalCardIndex(cardsInHand, i, justPlayed, choosenCardColor);

				}
				//or try to reverse
				else if (playableCards[i].getNumber() == 12) {
					cout << "I am trying to play " << cardTOString(playableCards[i]) << endl;
					toReturn = i;
					myDirection * -1;
					cout << "Reverse card was played, switching the direction  277" << endl;
					return findFinalCardIndex(cardsInHand, i, justPlayed, choosenCardColor);

				}
			}
		}
	}

	//CASE: if any players have 2 cards or less in their hand and they play a Wild Card --> change the color 
	for (int i = 0; i < cardAmountsByPlayer.size(); i++) {
		//if any player has <= 3 cards
		if (cardAmountsByPlayer[i] <= 2) {
			//find which player played a wild 
			if (player0PlayedWild) {
				//if the color they played is NOT my most common color 
				if (p0ColorChoice != findMostCommonColor(justPlayed, choosenCardColor, cardsInHand)) {
					//try to change the color 
					for (int i = 0; i < playableCards.size(); i++) {
						//try to play a wild card
						if (playableCards[i].getColor() == BLACK && playableCards[i].getNumber() == 1) {
							savedColor = findMostCommonColor(justPlayed, choosenCardColor, playableCards);

							//return the index of the wild card
							return findFinalCardIndex(cardsInHand, i, justPlayed, choosenCardColor);
						}
						//or try to change the color with a matching number
						else if (playableCards[i].getNumber() == justPlayed.getNumber()) {
							return findFinalCardIndex(cardsInHand, i, justPlayed, choosenCardColor);
						}
					}
				}
				
			}
			else if (player1PlayedWild) {
				//if the color they played is NOT my most common color 
				if (p1ColorChoice != findMostCommonColor(justPlayed, choosenCardColor, cardsInHand)) {
					//try to change the color 
					for (int i = 0; i < playableCards.size(); i++) {
						//try to play a wild card
						if (playableCards[i].getColor() == BLACK && playableCards[i].getNumber() == 1) {
							savedColor = findMostCommonColor(justPlayed, choosenCardColor, playableCards);

							//return the index of the wild card
							return findFinalCardIndex(cardsInHand, i, justPlayed, choosenCardColor);
						}
						//or try to change the color with a matching number
						else if (playableCards[i].getNumber() == justPlayed.getNumber()) {
							return findFinalCardIndex(cardsInHand, i, justPlayed, choosenCardColor);
						}
					}
				}

			}
			else if (player2PlayedWild) {
				//if the color they played is NOT my most common color 
				if (p2ColorChoice != findMostCommonColor(justPlayed, choosenCardColor, cardsInHand)) {
					//try to change the color 
					for (int i = 0; i < playableCards.size(); i++) {
						//try to play a wild card
						if (playableCards[i].getColor() == BLACK && playableCards[i].getNumber() == 1) {
							savedColor = findMostCommonColor(justPlayed, choosenCardColor, playableCards);

							//return the index of the wild card
							return findFinalCardIndex(cardsInHand, i, justPlayed, choosenCardColor);
						}
						//or try to change the color with a matching number
						else if (playableCards[i].getNumber() == justPlayed.getNumber()) {
							return findFinalCardIndex(cardsInHand, i, justPlayed, choosenCardColor);
						}
					}
				}

			}
			else if (player3PlayedWild) {
				//if the color they played is NOT my most common color 
				if (p3ColorChoice != findMostCommonColor(justPlayed, choosenCardColor, cardsInHand)) {
					//try to change the color 
					for (int i = 0; i < playableCards.size(); i++) {
						//try to play a wild card
						if (playableCards[i].getColor() == BLACK && playableCards[i].getNumber() == 1) {
							savedColor = findMostCommonColor(justPlayed, choosenCardColor, playableCards);

							//return the index of the wild card
							return findFinalCardIndex(cardsInHand, i, justPlayed, choosenCardColor);
						}
						//or try to change the color with a matching number
						else if (playableCards[i].getNumber() == justPlayed.getNumber()) {
							return findFinalCardIndex(cardsInHand, i, justPlayed, choosenCardColor);
						}
					}
				}

			}
			else if (player4PlayedWild) {
				//if the color they played is NOT my most common color 
				if (p4ColorChoice != findMostCommonColor(justPlayed, choosenCardColor, cardsInHand)) {
					//try to change the color 
					for (int i = 0; i < playableCards.size(); i++) {
						//try to play a wild card
						if (playableCards[i].getColor() == BLACK && playableCards[i].getNumber() == 1) {
							savedColor = findMostCommonColor(justPlayed, choosenCardColor, playableCards);

							//return the index of the wild card
							return findFinalCardIndex(cardsInHand, i, justPlayed, choosenCardColor);
						}
						//or try to change the color with a matching number
						else if (playableCards[i].getNumber() == justPlayed.getNumber()) {
							return findFinalCardIndex(cardsInHand, i, justPlayed, choosenCardColor);
						}
					}
				}

			}
		}
	}
	

	//CASE: if any players have 4 cards or less in their hand, start playing wild cards and draw4 cards 
	//loop through the array where each index represents the player number and the value represents the number of cards they have 
	//first determine if I can play a draw4 card -- only if I don't have the correct color 
	//loop through my playable cards and see if i have the color, if I do set to false and break
	for (int i = 0; i < playableCards.size(); i++) {
		if (playableCards[i].getColor() == choosenCardColor) {
			canPlayDraw4 = false;
		}
	}

	//check if any players have less than 4 cards
	for (int i = 0; i < cardAmountsByPlayer.size(); i++) {
		//if any player has <= 4 cards
		if (cardAmountsByPlayer[i] <= 4) {
			cout << "The game is ending!!!" << endl;
			// play a special card if possible 
			//loop through the cards in hand to find any special card that is a valid card to play 
			for (int i = 0; i < playableCards.size(); i++) {
				//try to play a draw4 first -- can only play this card as a last option
				if (canPlayDraw4) {
					if (playableCards[i].getColor() == BLACK && playableCards[i].getNumber() == 1) {
						//THIS IS NEW -- I need to pick a color when I play a draw4 card
						savedColor = findMostCommonColor(justPlayed, choosenCardColor, playableCards);
						cout << "I have a black card! I will play it because the game is ending" << endl;
						//return the index of the draw4 card to play the draw4 card
						return findFinalCardIndex(cardsInHand, i, justPlayed, choosenCardColor);
					}
				}
				//try to play a wild next  
				else if (playableCards[i].getColor() == BLACK && playableCards[i].getNumber() == 0) {
					savedColor = findMostCommonColor(justPlayed, choosenCardColor, playableCards);
					cout << "Playing a wild card and changing the color to " << savedColor << endl; 

					//return the index of the wild card
					return findFinalCardIndex(cardsInHand, i, justPlayed, choosenCardColor);
				}
				//try to play a draw2 next 
				else if (playableCards[i].getColor() == choosenCardColor && playableCards[i].getNumber() == 11) {
					//return the index of the reverse card to play the reverse card 
					return findFinalCardIndex(cardsInHand, i, justPlayed, choosenCardColor);;
				}
				//try to play a skip next
				else if (playableCards[i].getColor() == choosenCardColor && playableCards[i].getNumber() == 10) {
					//return the index of the skip card
					return findFinalCardIndex(cardsInHand, i, justPlayed, choosenCardColor);
				}
				//try to play a reverse card
				else if (playableCards[i].getColor() == choosenCardColor && playableCards[i].getNumber() == 12) {
					//change the direction 
					myDirection * -1;
					cout << "switching the direction 340" << endl;
					//return the index of the reverse card to play the reverse card 
					return findFinalCardIndex(cardsInHand, i, justPlayed, choosenCardColor);
				}
			}
			
		}

	}
	//CASE: if the player before me draws, reverse it
	if (playerBeforeDrew) {
		//play a reverse card if possible 
		//loop through the cards in hand to find any reverse card that is a valid card to play 
		for (int i = 0; i < playableCards.size(); i++) {
			//if th current card matches the color at the top of the stack and is a number 12 (reverse card) 
			if (playableCards[i].getColor() == choosenCardColor && playableCards[i].getNumber() == 12) {
				//update the direction 
				myDirection * -1;
				cout << "switching the direction 357" << endl;
				//return the index of the reverse card to play the reverse card 
				return findFinalCardIndex(cardsInHand, i, justPlayed, choosenCardColor);;
			}
		}
	}

	//CASE: if the color has stayed the same and any player has not drawn 


	//THIS IS GOOD
	//GENERAL CASE: play the highest value card 
	//if toReturn has not been assigned a value yet, then check the general case 
	int indexOfHighestCard = 0;
	int finalIndex; 
	if (toReturn == -1) {
		//loop through the number of the playable cards
		for (int i = 0; i < playableCards.size(); i++) {
			//if the current card has a higher value than the current highest card, reset the index of the highest card 
			//only check the cards with numbers (not the special cards like skip, draw2, reverse or the black cards)
			if (playableCards[i].getNumber() < 10 && playableCards[i].getColor() != BLACK) {
				//if the current number is larger than the curren highest number, reset the highest number
				if (playableCards[i].getNumber() > playableCards[indexOfHighestCard].getNumber()) {
					indexOfHighestCard = i;
				}
			}
		}
		finalIndex = findFinalCardIndex(cardsInHand, indexOfHighestCard, justPlayed, choosenCardColor);

		//case: if the card I want to play is the last card of that color then I want to play a different card if possible
		//right now I will playing the highest number card regardless of the color 
		//if the color of the card I am going to play is the last one of its color 
		if (cardsInHand[finalIndex].getColor() == countCardsOfEachColor(justPlayed, choosenCardColor, cardsInHand)) {
			//check to see if I can change the color by playing a card that has a matching number of the card on top 
			//loop through my playable cards 
			for (int i = 0; i < playableCards.size(); i++) {
				//make sure the card I am checking isn't already the one I was trying to play (they will be the same color but a different number
				if (playableCards[i].getNumber() != cardsInHand[finalIndex].getNumber()) {
					//if the card I am checking has the same number as the card on top 
					if (playableCards[i].getNumber() == justPlayed.getNumber()) {
						//and if the current card's color is the most common color 
						if (playableCards[i].getColor() == findMostCommonColor(justPlayed, choosenCardColor, cardsInHand)) {
							//play that card instead 
							cout << "I am going to play a different card instead so I have one of each color" << endl; 
							return findFinalCardIndex(cardsInHand, i, justPlayed, choosenCardColor);

						}

					}
				}
			}
		}

		return finalIndex; 

	}

	return findFinalCardIndex(cardsInHand, toReturn, justPlayed, choosenCardColor);


	//special card key
	//reverse = 12, skip = 10, and draw2 = 11 of any of red/blue/green/yellow.
	//wild is black 0, draw4 is black 1

	savedColor = YELLOW; //if I am playing a draw4 or wild, i set this variable to set the new color i am picking; yellow is the perfect color to choose every time i play a draw4/wild for this ai! I guess?


	//should not get here in my AI???
	cerr << "bbaaaad happeeeened\n";
	return -1;
}

string Haley4::getName()
{
	return "Haley4";
}



Color Haley4::getNewColor()
{
	return savedColor;
}


