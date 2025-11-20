#pragma once
#ifndef WORDLE_H
#define WORDLE_H

#include "config.h"
#include "GuessList.h"
#include "colors.h"
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <queue>

// Difficulty levels
enum Difficulty { EASY = 1, MEDIUM = 2, HARD = 3 };

// DSA: Stack for undo functionality (tracks guesses)
struct GuessRecord {
    char guess[MAX_WORD_LENGTH];
    int attemptNum;
};

// DSA: Queue for hint system (letters to reveal)
struct HintNode {
    int position;
    char letter;
};

class Wordle {
private:
    char dictionary[MAX_WORDS][MAX_WORD_LENGTH];  // Holds chosen difficulty's words
    int wordCount;                                // Number of words in current dictionary
    char secretWord[MAX_WORD_LENGTH];
    int currentWordLen;                           // Current word length based on difficulty
    int maxAttempts;                              // Max attempts based on difficulty
    Difficulty currentDifficulty;
    GuessList guesses;                            // Singly linked list for guess history
    int hintsUsed;                                // Track number of hints used

    // DSA: Stack for storing guess history (for potential undo)
    std::stack<GuessRecord> guessStack;

    // DSA: Queue for hint system
    std::queue<HintNode> hintQueue;

    void initializeHintQueue();                   // Initialize queue with letter positions

public:
    Wordle();
    void resetGame(Difficulty diff);              // Reset with difficulty choice
    int getBestScore(Difficulty diff);            // Get best score for specific difficulty
    void saveBestScore(int score, Difficulty diff); // Save best score for specific difficulty
    bool giveHint();                              // Returns true if hint costs a life
    void checkGuess(char* guess);
    void play();
    void printBorder(int width);
    void printCentered(const string& text, int width);
};

#endif
