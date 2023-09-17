/*
CMPT 125 Assignment 4 Game
Author: Chitransh Motwani
Student ID: 301435651
SFU email: cma115@sfu.ca
Academic honesty statement: I hereby confirm that this is my own work and I have
not violated any of SFU's Code of Academic Integrity and Good Conduct (S10.01).
Description: This is the file that contains function definitions
for the game related functions.
*/
#include "gameObjects.h"
//a function that initializes all the fields of a Deck.
// For each suit, the values of the cards are
// ‘A’, ‘2’, ‘3’, …, ‘9’, ,'T', ‘J’, ‘Q’, ‘K’.
void initializeDeck(Deck* theDeck, char* brandName){
	theDeck->brand = brandName;
	char card_values[13] = {'A', '2', '3', '4', '5', '6','7','8','9','T','J','Q','K'};
	int index = 0;

	for (int i = 0; i < 4; i++){
		for (int x = 0; x < 13; x++){
			theDeck->cards[index].suit = i;
			theDeck->cards[index].value = card_values[x];
			index++;
		}
	}
}

//a function that shuffles the deck
void shuffleDeck(Deck* theDeck){

	for (size_t i = 0; i < NUM_OF_CARDS_IN_DECK; i++){
		size_t j = i + rand() / (RAND_MAX / (NUM_OF_CARDS_IN_DECK - i) + 1);
		Card temp = theDeck->cards[j];
		theDeck->cards[j] = theDeck->cards[i];
		theDeck->cards[i] = temp;
	} 
}

//a function that prints the content of a Deck.
//accepts a second bool parameter:
//if true, print face up, if false, print face down.
//if the card is won by a player, leave it blank.
void printDeck(const Deck* theDeck, bool faceUp){
	int index = 0;
	printf("   a  b  c  d  e  f  g  h  i  j  k  l  m\n");
	for (int i = 0; i < 4; i++){
		printf ("%d ",i);
		if (faceUp==1){
			for (int x = 0; x < 13; x++){
				if (theDeck->cards[index].value==0){
					printf("  ");
				}
				else{
				printf("%c", theDeck->cards[index].value);
				if(theDeck->cards[index].suit == 0){	
					printf("\u2660");
				}
				if(theDeck->cards[index].suit == 1){	
					printf("\u2661");
				}
				if(theDeck->cards[index].suit == 2){	
					printf("\u2663");
				}
				if(theDeck->cards[index].suit == 3){	
					printf("\u2662");
				}
				if(x != 12){
					printf(" ");
				}
				}
				index++;
			}
			printf("\n");
		}
		else if (faceUp==0){
			for (int x = 0; x < 13; x++){
				if (theDeck->cards[index].value==0){
					printf("  ");
				}
				else{
				printf("%c",'?');
				if(theDeck->cards[index].suit == 0){	
					printf("\u218c");
				}
				if(theDeck->cards[index].suit == 1){	
					printf("\u218c");
				}
				if(theDeck->cards[index].suit == 2){	
					printf("\u218c");
				}
				if(theDeck->cards[index].suit == 3){	
					printf("\u218c");
				}
				if(x != 12){
					printf(" ");
				}
				}
				index++;
			}
			printf("\n");
		}
	}
}

//a function that initializes all the fields of a Player.
void initializePlayer(Player* thePlayer, char* theName){
	thePlayer->name = theName;
	thePlayer->cardsWon=0;
	thePlayer->winPile.head=NULL;
	thePlayer->winPile.tail=NULL;
}

//a function clears the winning pile of the player by calling the necessary
// function on a Card_LList.
void clearPlayer(Player* thePlayer){
	thePlayer->cardsWon=0;
	clearCard_LList(&thePlayer->winPile);
}


