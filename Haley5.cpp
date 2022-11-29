#include "Haley5.h"
#include "Card.h"
#include <iostream>
using namespace std;


Haley5::Haley5(int playerNumber) : AI(playerNumber)
{

}

//tracks all player moves --> justPlayed is the card that the player is playing 
void Haley5::onOtherPlayerMove(int playerNumber, Card justPlayed, Color choosenCardColor) {
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
	//keep track of the cards that each player just played and see if a wild card is played, update the player's color of choice
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
void Haley5::onOtherPlayerDraw(int playerNumber) {
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
//this function returns a vector that holds the number of cards for each color
//order: red, green, blue, yellow
vector<int> Haley5::countCardsOfEachColor(vector<Card>cardsInHand) {
	//loop through cards in hand
	for (int i = 0; i < cardsInHand.size(); i++) {
		if (cardsInHand[i].getColor() == RED) {
			reds++; 
		}
		else if (cardsInHand[i].getColor() == GREEN) {
			greens++;
		}
		else if (cardsInHand[i].getColor() == BLUE) {
			blues++;
		}
		else if (cardsInHand[i].getColor() == YELLOW) {
			yellows++;
		}
	}

	//CHECK that the counting is correct
	cout << "reds: " << reds << endl;
	cout << "greens: " << greens << endl;
	cout << "blues: " << blues << endl;
	cout << "yellows: " << yellows << endl;

	vector<int> toReturn; 
	toReturn.push_back(reds); 
	toReturn.push_back(greens);
	toReturn.push_back(blues);
	toReturn.push_back(yellows);

	return toReturn; 

}


//this function finds the most common color 
Color Haley5::findMostCommonColor(Card justPlayed, Color chosenColor, vector<Card> cardsInHand) {		
	cout << "I have this number of cards in my hand: " << cardsInHand.size() << endl; 
	//cout << "The cards in my hand are: " << cardTOString(cardsInHand[0]) << cardTOString(cardsInHand[1]) << endl; 
	
	vector<int>numberOfCardsOfEachColor = countCardsOfEachColor(cardsInHand); 

	//2 2 3 1
	int highestIndex = 0;
	int sameHighestIndex = 0; 
	//find the biggest value in the vector 
	for (int i = 0; i < 4; i++) {
		if (numberOfCardsOfEachColor[i] > highestIndex) {
			highestIndex = i; 
		}
		else if (numberOfCardsOfEachColor[i] == highestIndex) {
			sameHighestIndex = i; 
		}
	}

	//CASE: if there is a tie 
	Color color1; 
	Color color2; 

	//assign color1 to the corresponding index 
	if (highestIndex == 0) {
		color1 = RED; 
	}
	else if (highestIndex == 1) {
		color1 = GREEN;
	}
	else if (highestIndex == 2) {
		color1 = BLUE;
	}
	else if (highestIndex == 3) {
		color1 = YELLOW;
	}

	//assign color2 to the corresponding index 
	if (highestIndex == 0) {
		color2 = RED;
	}
	else if (highestIndex == 1) {
		color2 = GREEN;
	}
	else if (highestIndex == 2) {
		color2 = BLUE;
	}
	else if (highestIndex == 3) {
		color2 = YELLOW;
	}

	int color1Total = 0; 
	int color2Total = 0; 

	//check if there is a tie
	if (numberOfCardsOfEachColor[highestIndex] == numberOfCardsOfEachColor[sameHighestIndex]) {
		cout << "there is a tie!" << endl; 

		//if there is a tie, I want to play the color that has the highest combined total 
		//(the color that is accumulating the most number of points)
		//add the numbers up by looping through the cards in hand 
		for (int i = 0; i < cardsInHand.size(); i++) {
			if (cardsInHand[i].getColor() == color1) {
				color1Total++; 
			}
			else if (cardsInHand[i].getColor() == color2) {
				color2Total++; 
			}
		}

		//once there is a total, determine the final color 
		//if color1Total is more than color2Total, return that color 
		if (color1Total > color2Total) {
			return color1; 
		}
		return color2; 
	}
	//if there is not a tie, do it normally and return the most common color 
	if (highestIndex == 0) {
		cout << "most common color is red" << endl; 
		return RED;
	}
	else if (highestIndex == 1) {
		cout << "most common color is green" << endl;
		return GREEN;
	}
	else if (highestIndex == 2) {
		cout << "most common color is blue" << endl;
		return BLUE;
	}
	cout << "most common color is yellow" << endl;
	return YELLOW; 
	
}

//this function returns the color with only 1 card left, returns BLACK if no card colors only have 1 left 
Color Haley5::findLastCardOfAColor(Card justPlayed, Color chosenColor, vector<Card> cardsInHand) {
	//vector that holds the number of cards for each color
	vector<int>numberOfCardsOfEachColor = countCardsOfEachColor(cardsInHand);

	int colorIndex = -1; 
	for (int i = 0; i < numberOfCardsOfEachColor.size(); i++) {
		//if a color only has 1 card left 
		if (numberOfCardsOfEachColor[i] == 1) {
			colorIndex = i; 
		}
	}

	if (colorIndex == 0) {
		return RED; 
	}
	else if (colorIndex == 1) {
		return GREEN; 
	}
	else if (colorIndex == 2) {
		return BLUE; 
	}
	else if (colorIndex == 3) {
		return YELLOW; 
	}
	//if none of the colors have only one card left, return BLACK
	return BLACK; 

}
int Haley5::findFinalCardIndex(vector<Card>cardsInHand, int indexInPlayableCards, Card justPlayed, Color chosenCardColor) {
	//use playable cards vector
	vector<Card> playableCards = getPlayableCardsInHand(justPlayed, chosenCardColor, cardsInHand);
	//loop through all the cards that are in my hand 
	for (int i = 0; i < cardsInHand.size(); i++) {
		//if the card that I am looking for is the same one as the one I want to play from the playable cards vector
		if (cardsInHand[i].getColor() == playableCards[indexInPlayableCards].getColor() && cardsInHand[i].getNumber() == playableCards[indexInPlayableCards].getNumber()) {
			//return the index from the card in hand vector
			return i;
		}
	}
	//should never get here
	return -1;
}

//returns the index of the card to play
int Haley5::makeMove(Card justPlayed, Color choosenCardColor, bool justDrew, vector<int> scores, vector<int> cardAmountsByPlayer, vector<Card> cardsInHand, int direction) {
	//reset the card color count before a move is made because my hand will look differently each time 
	reds = 0; 
	greens = 0; 
	blues = 0; 
	yellows = 0; 

	int toReturn = -1; 
	if (roundsPlayed == 5) {
		roundsPlayed = 0; 
	}
	roundsPlayed++; 

	vector<Card> playableCards = getPlayableCardsInHand(justPlayed, choosenCardColor, cardsInHand);
	cout << "The number of playable cards is: " << playableCards.size() << endl;

	if (playableCards.size() == 0) {
		cout << "I AM DRAWING" << endl;
		return -1; //draw
	}
	//to speed it up, if I only have 1 playable card, play that card 
	if (playableCards.size() == 1) {
		return findFinalCardIndex(cardsInHand, 0, justPlayed, choosenCardColor); 
	}


	//first determine if I can play a draw4 card -- only if I don't have the correct color 
	if (playableCards.size() == 1 && playableCards[0].getColor() == BLACK && playableCards[0].getNumber() == 1) {
		canPlayDraw4 = true;
	}

	
	//SPECIAL CASES: based on the actions/situations of the other players 
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
		//try to play a draw2 first 
		for (int i = 0; i < playableCards.size(); i++) {
			if (playableCards[i].getColor() == choosenCardColor) {
				if (playableCards[i].getNumber() == 11) {
					cout << "I am trying to play " << cardTOString(playableCards[i]) << endl;
					return findFinalCardIndex(cardsInHand, i, justPlayed, choosenCardColor);
				}
			}
		}
		//try to play a skip next 
		for (int i = 0; i < playableCards.size(); i++) {
			//try to play a draw2 first
			if (playableCards[i].getColor() == choosenCardColor) {
				if (playableCards[i].getNumber() == 10) {
					cout << "I am trying to play " << cardTOString(playableCards[i]) << endl;
					return findFinalCardIndex(cardsInHand, i, justPlayed, choosenCardColor);
				}
			}
		}
		//try to play a reverse next 
		for (int i = 0; i < playableCards.size(); i++) {
			if (playableCards[i].getNumber() == 12) {
				cout << "I am trying to play " << cardTOString(playableCards[i]) << endl;
				myDirection * -1;
				cout << "Reverse card was played, switching the direction  297" << endl;
				return findFinalCardIndex(cardsInHand, i, justPlayed, choosenCardColor);

			}
		}
	}


	//CASE: if any players have 2 cards or less in their hand and they play a Wild Card --> change the color 
	//find which player has less than 2 cards 
	int playerWithLessThan2 = -1; 
	Color mostCommonColor = findMostCommonColor(justPlayed, choosenCardColor, cardsInHand); 
	for (int i = 0; i < cardAmountsByPlayer.size(); i++) {
		if (cardAmountsByPlayer[i] <= 2) {
			playerWithLessThan2 = i; 
		}
	}
	//if player 0 is the one with less than 2 cards
	if (playerWithLessThan2 == 0) {
		//if player0 played a wild and their color choice is not the most common color for me 
		if (player0PlayedWild && p0ColorChoice != mostCommonColor) {
			for (int i = 0; i < playableCards.size(); i++) {
				//try to play a wild card to change the color of the deck 
				if (playableCards[i].getColor() == BLACK && playableCards[i].getNumber() == 1) {
					savedColor = findMostCommonColor(justPlayed, choosenCardColor, cardsInHand); 
					return findFinalCardIndex(cardsInHand, i, justPlayed, choosenCardColor);

				}
			}
		}
	}
	//if player 1 is the one less than 2 cards 
	else if (playerWithLessThan2 == 1) {
		//if player0 played a wild and their color choice is not the most common color for me 
		if (player0PlayedWild && p0ColorChoice != mostCommonColor) {
			for (int i = 0; i < playableCards.size(); i++) {
				//try to play a wild card to change the color of the deck 
				if (playableCards[i].getColor() == BLACK && playableCards[i].getNumber() == 1) {
					savedColor = findMostCommonColor(justPlayed, choosenCardColor, cardsInHand);
					return findFinalCardIndex(cardsInHand, i, justPlayed, choosenCardColor);

				}
			}
		}
	}
	//if player 2 is the one less than 2 cards 
	else if (playerWithLessThan2 == 2) {
		//if player0 played a wild and their color choice is not the most common color for me 
		if (player0PlayedWild && p0ColorChoice != mostCommonColor) {
			for (int i = 0; i < playableCards.size(); i++) {
				//try to play a wild card to change the color of the deck 
				if (playableCards[i].getColor() == BLACK && playableCards[i].getNumber() == 1) {
					savedColor = findMostCommonColor(justPlayed, choosenCardColor, cardsInHand);
					return findFinalCardIndex(cardsInHand, i, justPlayed, choosenCardColor);

				}
			}
		}
	}
	//if player 3 is the one less than 2 cards 
	else if (playerWithLessThan2 == 3) {
		//if player0 played a wild and their color choice is not the most common color for me 
		if (player0PlayedWild && p0ColorChoice != mostCommonColor) {
			for (int i = 0; i < playableCards.size(); i++) {
				//try to play a wild card to change the color of the deck 
				if (playableCards[i].getColor() == BLACK && playableCards[i].getNumber() == 1) {
					savedColor = findMostCommonColor(justPlayed, choosenCardColor, cardsInHand);
					return findFinalCardIndex(cardsInHand, i, justPlayed, choosenCardColor);

				}
			}
		}
	}

	//CASE: if any players have 4 cards or less in their hand, start playing wild cards and draw4 cards 
	//loop through the array where each index represents the player number and the value represents the number of cards they have 
	
	//THIS IS SUSPICIOUS because
	//I am getting the correct most common color BUT i am not playing a card from there if I can 
	//is that another strategy? 
	//ex. card on top YelD with 5 Blue cards and a BluD and 1 yellow card and I am playing the yellow card
	//but i need to be playing the BluD

	for (int i = 0; i < cardAmountsByPlayer.size(); i++) {
		if (cardAmountsByPlayer[i] <= 4) {
			gameIsEnding = true; 
		}
	}
	if (gameIsEnding) {
		cout << "The game is ending!!! 448" << endl;
		// play a special card if possible 
		//loop through the cards in hand to find any special card that is a valid card to play 
		for (int i = 0; i < playableCards.size(); i++) {
			//try to play a draw4 first -- can only play this card as a last option
			if (canPlayDraw4) {
				//cout << "I AM HERE LOOK AT ME line 467" << endl; 
				if (playableCards[i].getColor() == BLACK && playableCards[i].getNumber() == 1) {
					//THIS IS NEW -- I need to pick a color when I play a draw4 card
					savedColor = findMostCommonColor(justPlayed, choosenCardColor, cardsInHand);
					cout << "I am playing a draw4 and changing the color to " << playableCards[i].getColor() << endl;
					//return the index of the draw4 card to play the draw4 card
					return findFinalCardIndex(cardsInHand, i, justPlayed, choosenCardColor);
				}
			}
		}
		for (int i = 0; i < playableCards.size(); i++) {
			//try to play a wild next  
			if (playableCards[i].getColor() == BLACK && playableCards[i].getNumber() == 0) {
				savedColor = findMostCommonColor(justPlayed, choosenCardColor, cardsInHand);
				cout << "Playing a wild card and changing the color to " << savedColor << endl;

				//return the index of the wild card
				return findFinalCardIndex(cardsInHand, i, justPlayed, choosenCardColor);
			}
		}
		for (int i = 0; i < playableCards.size(); i++) {
			//try to play a draw2 next 
			//THIS IS SUSPICIOUS --> i am changing it to be an OR instead of an ANd --> but actually it just needs to be an 11 for it to be a valid play because the color doesn't matter 
			if (playableCards[i].getColor() == choosenCardColor && playableCards[i].getNumber() == 11) {
				//return the index of the draw2 card to play the reverse card 
				cout << "Playing a draw2 card" << endl;
				return findFinalCardIndex(cardsInHand, i, justPlayed, choosenCardColor);
			}
		}
		for (int i = 0; i < playableCards.size(); i++) {
			//try to play a skip next
			if (playableCards[i].getColor() == choosenCardColor && playableCards[i].getNumber() == 10) {
				//return the index of the skip card
				cout << "Playing a skip card" << endl;
				return findFinalCardIndex(cardsInHand, i, justPlayed, choosenCardColor);
			}
		}
		for (int i = 0; i < playableCards.size(); i++) {
			//try to play a reverse card
			if (playableCards[i].getColor() == choosenCardColor && playableCards[i].getNumber() == 12) {
				//change the direction 
				myDirection * -1;
				cout << "switching the direction 425" << endl;
				//return the index of the reverse card to play the reverse card 
				return findFinalCardIndex(cardsInHand, i, justPlayed, choosenCardColor);
			}
		}
	}

	//check if any players have less than 4 cards
	for (int i = 0; i < cardAmountsByPlayer.size(); i++) {
		if (cardAmountsByPlayer[i] <= 4) {
			gameIsEnding = true;
		}
	}
	if (gameIsEnding) {
		cout << "The game is ending and I am here because I couldn't play a special card !!! 439" << endl;
		// play a special card if possible 
		//loop through the cards in hand to find any special card that is a valid card to play 
		for (int i = 0; i < playableCards.size(); i++) {
			//try to play a draw4 first -- can only play this card as a last option
			if (canPlayDraw4) {
				if (playableCards[i].getColor() == BLACK && playableCards[i].getNumber() == 1) {
					//THIS IS NEW -- I need to pick a color when I play a draw4 card
					savedColor = findMostCommonColor(justPlayed, choosenCardColor, cardsInHand);
					cout << "I am playing a draw4 and changing the color to " << playableCards[i].getColor() << endl;
					//return the index of the draw4 card to play the draw4 card
					return findFinalCardIndex(cardsInHand, i, justPlayed, choosenCardColor);
				}
			}
		}
		for (int i = 0; i < playableCards.size(); i++) {
			//try to play a wild next  
			if (playableCards[i].getColor() == BLACK && playableCards[i].getNumber() == 0) {
				savedColor = findMostCommonColor(justPlayed, choosenCardColor, cardsInHand);
				cout << "Playing a wild card and changing the color to " << savedColor << endl;

				//return the index of the wild card
				return findFinalCardIndex(cardsInHand, i, justPlayed, choosenCardColor);
			}
		}
		for (int i = 0; i < playableCards.size(); i++) {
			//try to play a draw2 next 
			if (playableCards[i].getColor() == choosenCardColor && playableCards[i].getNumber() == 11) {
				//return the index of the reverse card to play the reverse card 
				cout << "Playing a reverse card" << endl;
				return findFinalCardIndex(cardsInHand, i, justPlayed, choosenCardColor);
			}
		}
		for (int i = 0; i < playableCards.size(); i++) {
			//try to play a skip next
			if (playableCards[i].getColor() == choosenCardColor && playableCards[i].getNumber() == 10) {
				//return the index of the skip card
				cout << "Playing a skip card" << endl;
				return findFinalCardIndex(cardsInHand, i, justPlayed, choosenCardColor);
			}
		}
		for (int i = 0; i < playableCards.size(); i++) {
			//try to play a reverse card
			if (playableCards[i].getColor() == choosenCardColor && playableCards[i].getNumber() == 12) {
				//change the direction 
				myDirection * -1;
				cout << "switching the direction 340" << endl;
				//return the index of the reverse card to play the reverse card 
				return findFinalCardIndex(cardsInHand, i, justPlayed, choosenCardColor);
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
				cout << "switching the direction 501" << endl;
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
		if (cardsInHand[finalIndex].getColor() == findLastCardOfAColor(justPlayed, choosenCardColor, cardsInHand)) {
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

	//savedColor = YELLOW; //if I am playing a draw4 or wild, i set this variable to set the new color i am picking; yellow is the perfect color to choose every time i play a draw4/wild for this ai! I guess?


	//should not get here in my AI???
	cerr << "bbaaaad happeeeened\n";
	return -1;
}

string Haley5::getName()
{
	return "Haley5";
}



Color Haley5::getNewColor()
{
	return savedColor;
}


