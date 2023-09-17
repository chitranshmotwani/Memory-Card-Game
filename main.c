/*
CMPT 125 Assignment 4 Game
Author: Chitransh Motwani
Student ID: 301435651
SFU email: cma115@sfu.ca
Academic honesty statement: I hereby confirm that this is my own work and I have
not violated any of SFU's Code of Academic Integrity and Good Conduct (S10.01).
Description: This is the source code for the game. In implements the main
function that is the driver of the program. In also includes a clear function
that attemps to "push" the face up print up beyond the screen.
*/

#include <stdio.h>
#include <stdlib.h> //for the use of system and srand and rand
#include "gameObjects.h"
#include "gameFunctions.h"
#include "card_LList.h"

#define MAX_CHAR_NUMBER 16 //each input should have at most 15 characters
//helper function to get the index of the
//card that has been chosen by the player.
int getSpecific_index(char cols, char rows){
  int index=0;
  int column = ((int)rows)-48;
  if (column > 0){
    for (int cols = 1; cols <= column; cols++){
      index += 13;
    }
  }
  index += cols - 'a';
  return index;
}
//helper function to print the card chosen
//by the player using it's index.
void printSpecific_card ( Deck* theDeck, char cols, char rows){
  int index = getSpecific_index( cols,  rows);
  printf("%d", (theDeck->cards[index].value)-48);
  if (theDeck->cards[index].suit == Spades){
    printf("\u2660");
  }
  else if (theDeck->cards[index].suit == Clubs){
    printf("\u2663");
  }
  else if (theDeck->cards[index].suit == Hearts){
    printf("\u2661");
  }
  else {
    printf("\u2662");
  }
}
//a helper function that clears the screen, works for both unix and Windows,
//though behaviour might be different.
//reference: https://stackoverflow.com/questions/2347770/
//            how-do-you-clear-the-console-screen-in-c
void clear() {
  #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    system("printf '\33[H\33[2J'");
  #endif

  #if defined(_WIN32) || defined(_WIN64)
    system("cls");
  #endif
}

int main() {
  //set the random seed to 0, it'll generate the same sequence
  //normally it is srand(time(NULL)) so the seed is different in every run
  //using 0 makes it deterministic so it is easier to mark
  //do not change it
  srand(0);

  //variables to store user input
  char userInput1[MAX_CHAR_NUMBER];
  char userInput2[MAX_CHAR_NUMBER];
//  int whereInDeck = 0; //handy for indexing which card based on user input

  //set up the players
  Player player1, player2;
  initializePlayer(&player1, "Player 1");
  initializePlayer(&player2, "Player 2");
  Player* currentPlayer = &player1; //this pointer remembers who's turn it is

  //set up the deck: initalize & shuffle
  Deck myDeck;
  initializeDeck(&myDeck, "Bicycle");
  shuffleDeck(&myDeck);

  printDeck(&myDeck, true); //print the shuffled deck, face up
  printf("\n");
  clear(); //clear the screen

  /*
  Implement this part for the game to work.
  It is essentially a do-while loop that repeatedly print the deck,
  ask for user inputs, and do some checking. Ends if someone wins.
  */
  int round=0; int play=0;
  do {
    /////////////////////
    // 1 Round
    ////////////////////
    //Step 1: print the shuffled deck, face down
	printDeck(&myDeck, 0);

    //Step 2: print who's turn it is by showing the player's name
	play=2;
	if (round%2==0){
		play=1;
	}
	printf("Player%d's turn.\n", play);

    //Step 3.1 get first input from player,
    // keep asking until the input is valid (hint: use a do-while loop)
    // you can assume that the format is correct (a digit<space>a letter)
	do{
		printf("Pick the first card you want to turn (e.g., 0 a) then press enter:");
		fgets(userInput1, MAX_CHAR_NUMBER, stdin);
	} while (!checkPlayerInput(&myDeck, currentPlayer, userInput1[0], userInput1[2]));

    //Step 3.2: get second input from player,
    // keep asking until the input is valid (hint: use a do-while loop)
    // you can assume that the format is correct (a digit<space>a letter)
	do{
		printf("Pick the second card you want to turn (e.g., 1 b) then press enter:");
		fgets(userInput2, MAX_CHAR_NUMBER, stdin);
	} while (!checkPlayerInput(&myDeck, currentPlayer, userInput2[0], userInput2[2]));
	
    //Step 4: print the 2 cards the player picks
	printf("First card picked: ");
	printSpecific_card(&myDeck, userInput1[2],userInput1[0]);
	printf("\n");
	printf("Second card picked: ");
	printSpecific_card(&myDeck, userInput2[2],userInput2[0]);
	printf("\n");

    //Step 5: call the checkForMatch function to see if the player has picked
    // a matching pair. If so, print the corresponding message and add the cards
    // to the player's winning pile (Player.winPile).
    // Keep the current player as a match leads to an extra round.
    // Otherwise, print the corresponding message and switch player.
if (play == 1){
      int index1 = getSpecific_index(userInput1[2], userInput1[0]);
      int index2 = getSpecific_index(userInput2[2], userInput2[0]);
      if (checkForMatch(&myDeck, &player1, userInput1[0], userInput1[2], userInput2[0], userInput2[2]) == true){
        addCardToPlayer(&player1, &myDeck.cards[index1]);
        addCardToPlayer(&player1, &myDeck.cards[index2]);//add to win pile
        printf("Player 1 has found a match! Earns an extra turn.\n");
        myDeck.cards[index1].value = 0;
        myDeck.cards[index2].value = 0;
        round--;//round -- so that there will be an extra round since current player has won
      }
      else {
        printf("Player 1 has not found a match.\n");
      }

    }
    if (play == 2){
      int index1 = getSpecific_index(userInput1[2], userInput1[0]);
      int index2 = getSpecific_index(userInput2[2], userInput2[0]);
      if (checkForMatch(&myDeck, &player2, userInput1[0], userInput1[2], userInput2[0], userInput2[2]) == true){
        addCardToPlayer(&player2, &myDeck.cards[index1]);//add to win pile
        addCardToPlayer(&player2, &myDeck.cards[index2]);
        printf("Player 2 has found a match! Earns an extra turn.\n");
        myDeck.cards[index1].value = 0;
        myDeck.cards[index2].value = 0;
        round--;
      }
      else {
        printf("Player 2 has not found a match.\n");
      }
    }

    round ++;

  } while (!checkForWinner(&myDeck));

  //Step 6: find out who won the game and announce the winner
  printf("Player 1 has won %d cards.\n", player1.cardsWon);
  printf("Player 2 has won %d cards.\n", player2.cardsWon);
  	if (player1.cardsWon > player2.cardsWon){
    printf("Player 1 has won.\n");
 	}
  	else if (player1.cardsWon < player2.cardsWon){
    printf("Player 2 has won.\n");
  	}
	else{
    printf("It was a tie.\n");
  	}


  //Step 7: clean up player's winning piles
	clearPlayer(&player1);
  	clearPlayer(&player2);

  return 0;
}
