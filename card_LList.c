/*
CMPT 125 Assignment 4 Game
Author: Chitransh Motwani
Student ID: 301435651
SFU email: cma115@sfu.ca
Academic honesty statement: I hereby confirm that this is my own work and I have
not violated any of SFU's Code of Academic Integrity and Good Conduct (S10.01).
Description: This is the file that contains function definitions
for the Linked List related functions
*/
#include "Card_LList.h"
//a function that creates a new Card_LList, which is an empty linked list.
Card_LList* createCard_LList(){
  Card_LList* cardList;
  cardList = (Card_LList*)malloc(sizeof(Card_LList));
  cardList->head = NULL;
  cardList->tail = NULL;
  return cardList;
}

//a function that removes all the nodes from the list
// by freeing them one by one. The result is an empty linked list.
void clearCard_LList(Card_LList* theList){
	struct Node *temp;
	while(theList->head!= NULL)
    {
        temp = theList->head;
        theList->head = theList->head->next;

        free(temp);
    }
}

//a function that checks if the list is empty.
// If it is empty, return true; otherwise return false.
bool isEmptyCard_LList(Card_LList* theList){
	if (theList->head !=NULL) return true;
    else return false;
}

//a function that inserts the card as a part of a node
// (the node itself doesn't store the card, but the address of the card).
// This method encapsulates the inner workings of the linked list and
// there is no need to duplicate the card.
void insertFrontCard_LList(Card_LList* theList, Card* theCard){
	struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
	new_node->card  = theCard;
	new_node->next = theList->head;
	theList->head= new_node;
}

//a function that inserts the card as a part of a node
// (the node itself doesn't store the card, but the address of the card).
// This method encapsulates the inner workings of the linked list and
// there is no need to duplicate the card.
void insertEndCard_LList(Card_LList* theList, Card* theCard){
	struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
	//struct Node *last = theList->head;
	new_node->card  = theCard;
	new_node->next=NULL;
	if (theList->head == NULL)
    {
       theList->head = new_node;
    }
    else theList->tail->next =new_node;
    theList->tail = new_node;
    return;
}

//a function that returns the address of the card stored in the node.
// This method encapsulates the inner workings of the linked list and
// there is no need to duplicate the card.
// Freeing of the node memory is done here.
Card* removeFrontCard_LList(Card_LList* theList){
    	struct Node* temp = theList->head;
    	theList->head = temp->next;   // Change head
		free(temp);               // free old head
        return temp->card;
}

//a function that returns the address of the card stored in the node.
// This method encapsulates the inner workings of the linked list and
// there is no need to duplicate the card.
// Freeing of the node memory is done here.
Card* removeEndCard_LList(Card_LList* theList){
    // Find the second last node
    struct Node* second_last = theList->head;
    while (second_last->next->next != NULL){
        second_last = second_last->next;}
    free(second_last->next);
    second_last->next = NULL;
    return second_last->card;
}
