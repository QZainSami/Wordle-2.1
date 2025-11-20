#pragma once
#ifndef GUESSLIST_H
#define GUESSLIST_H

#include "config.h"
#include <iostream>
#include <cstring>
using namespace std;

// DSA: Doubly Linked List Node with Circular Reference
struct DoublyNode {
    char guess[MAX_WORD_LENGTH];
    DoublyNode* next;
    DoublyNode* prev;
    DoublyNode(const char g[]);
};

// DSA: Doubly & Circular Linked List for Guess History
class GuessList {
private:
    DoublyNode* head;   // First guess
    DoublyNode* tail;   // Last guess (tail->next points to head for circular)
    int size;           // Track number of guesses

public:
    GuessList();
    void addGuess(const char g[]);        // Add guess to doubly linked list
    void displayGuesses();                // Display all guesses
    void displayReverse();                // Display guesses in reverse (doubly LL feature)
    void displayCircular(int rounds);     // Display circular traversal (circular LL feature)
    int getSize() const;                  // Get number of guesses
    void clear();                          // Clear all guesses
    ~GuessList();                         // Destructor
};

#endif
