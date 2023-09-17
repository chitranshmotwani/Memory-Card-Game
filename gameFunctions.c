/*
CMPT 125 Assignment 4 Game
Author: Chitransh Motwani
Student ID: 301435651
SFU email: cma115@sfu.ca
Academic honesty statement: I hereby confirm that this is my own work and I have
not violated any of SFU's Code of Academic Integrity and Good Conduct (S10.01).
Description: This is the file that contains some function definitions
regarding the game functions.
*/
#include "card_LList.h"
#include "gameObjects.h"
#include "gameFunctions.h"
//a function that adds the card to the player's winning pile by calling
// the appropriate function from card_LList and update the cards won.
// Also marks the card as taken ('0').
void addCardToPlayer(Player* thePlayer, Card* theCard){
	thePlayer->cardsWon=thePlayer->cardsWon+1;
	insertEndCard_LList(&thePlayer->winPile, theCard);
	theCard->value=0;
}

//a function that checks if the user choice is valid:
// if any of the choices are invalid, report that and return false.
bool checkPlayerInput(Deck* theDeck, Player* thePlayer, char row, char col){
  int index=0;
  int column = ((int) row)-48;
  if (column > 0){
    for (int col = 1; col <= column; col++){
      index += 13;
    }
  }
  index += col - 'a';
  if (row >= '0' && row <= '3'){
    if (col >= 'a' && col <= 'm'){
      if ((theDeck->cards[index].value)!=0){
          return true;
      }
      printf("Player picks a card that is already won.");
      return false;
    }
    printf("Player picks a card with invalid indexes (out of bound).");
	return false;
  }
  printf("Player picks a card with invalid indexes (out of bound).");
  return false;
}

//a function that checks if there is a match:
// if the two choices are the same, report it and return false.
// if there is a match, return true; otherwise, return false.
bool checkForMatch(Deck* theDeck, Player* thePlayer, char r1, char c1, char r2, char c2){
  int index1=0;
  int column1 = ((int) r1)-48;
  if (column1 > 0){
    for (int c1 = 1; c1 <= column1; c1++){
      index1 += 13;
    }
  }
  index1 += c1 - 'a';
  int index2=0;
  int column2 = ((int) r2)-48;
  if (column2 > 0){
    for (int c2 = 1; c2 <= column2; c2++){
      index2 += 13;
    }
  }
  index2 += c2 - 'a';
  if (theDeck->cards[index1].value == theDeck->cards[index2].value){
    if (theDeck->cards[index1].suit == theDeck->cards[index2].suit){
      return false;
      printf("Player picks the same card in their round.");
    }
    return true;
  }
  return false;
  printf("Player picks the same card in their round.");
}

//a function that checks if the game has a winner
// (all cards in the deck is taken)
bool checkForWinner(const Deck* theDeck){
    bool flag;
    for (int index = 0; index < 52; index++){
            if(theDeck->cards[index].value == 0){
                flag= 1;
            }
            else{
                flag=0;
                return flag;
            }
        }
    return flag;
}
