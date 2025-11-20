#include "Wordle.h"
#include "Wordle_wordlists.h"
#include <iostream>
#include <cstring>
// Add near other includes
#include <random>
#include <chrono>

// file-scope RNG seeded once per run
static std::mt19937 rng(static_cast<unsigned int>(
    std::chrono::high_resolution_clock::now().time_since_epoch().count()));

using namespace std;

// Constructor
Wordle::Wordle() {
    srand(static_cast<unsigned int>(time(0)));
    hintsUsed = 0;
    currentWordLen = MEDIUM_WORD_LEN;
    maxAttempts = MEDIUM_ATTEMPTS;
    currentDifficulty = MEDIUM;
}

// DSA: Initialize hint queue with all letter positions
void Wordle::initializeHintQueue() {
    // Clear existing queue
    while (!hintQueue.empty()) {
        hintQueue.pop();
    }

    // Add all positions to queue in random order
    bool used[MAX_WORD_LENGTH] = { false };
    for (int i = 0; i < currentWordLen; i++) {
        int randomPos;
        do {
            randomPos = rand() % currentWordLen;
        } while (used[randomPos]);

        used[randomPos] = true;
        HintNode hint;
        hint.position = randomPos;
        hint.letter = secretWord[randomPos];
        hintQueue.push(hint);
    }
}

// Reset game with difficulty
void Wordle::resetGame(Difficulty diff) {
    currentDifficulty = diff;

    // Set word length and attempts based on difficulty and copy words into dictionary
    int originalCount = 0;
    if (diff == EASY) {
        currentWordLen = EASY_WORD_LEN;
        maxAttempts = EASY_ATTEMPTS;
        originalCount = EASY_WORD_COUNT;
        for (int i = 0; i < originalCount && i < MAX_WORDS; ++i)
            strcpy_s(dictionary[i], MAX_WORD_LENGTH, easyWords[i]);
    }
    else if (diff == MEDIUM) {
        currentWordLen = MEDIUM_WORD_LEN;
        maxAttempts = MEDIUM_ATTEMPTS;
        originalCount = MEDIUM_WORD_COUNT;
        for (int i = 0; i < originalCount && i < MAX_WORDS; ++i)
            strcpy_s(dictionary[i], MAX_WORD_LENGTH, mediumWords[i]);
    }
    else {
        currentWordLen = HARD_WORD_LEN;
        maxAttempts = HARD_ATTEMPTS;
        originalCount = HARD_WORD_COUNT;
        for (int i = 0; i < originalCount && i < MAX_WORDS; ++i)
            strcpy_s(dictionary[i], MAX_WORD_LENGTH, hardWords[i]);
    }

    // Use only the number of words actually copied into `dictionary`
    wordCount = (originalCount > MAX_WORDS) ? MAX_WORDS : originalCount;

    if (wordCount <= 0) {
        cerr << RED << "Error: word list empty for chosen difficulty. Check Wordle_wordlists.cpp or Wordle_wordlists.h" << RESET << endl;
        // Safe fallback
        wordCount = 1;
        strcpy_s(dictionary[0], MAX_WORD_LENGTH, "test");
    }

    // Pick random secret word (now safe because wordCount reflects copied entries)
    std::uniform_int_distribution<int> distIndex(0, wordCount - 1);
    strcpy_s(secretWord, MAX_WORD_LENGTH, dictionary[distIndex(rng)]);

    // Initialize DSA structures
    guesses.clear();
    hintsUsed = 0;

    // Clear stack
    while (!guessStack.empty()) {
        guessStack.pop();
    }

    // Initialize hint queue
    initializeHintQueue();
}

int Wordle::getBestScore(Difficulty diff) {
    string filename;
    if (diff == EASY) filename = "bestscore_easy.txt";
    else if (diff == MEDIUM) filename = "bestscore_medium.txt";
    else filename = "bestscore_hard.txt";

    ifstream in(filename);
    int score;
    if (in >> score) return score;
    return 999;
}

void Wordle::saveBestScore(int score, Difficulty diff) {
    string filename;
    if (diff == EASY) filename = "bestscore_easy.txt";
    else if (diff == MEDIUM) filename = "bestscore_medium.txt";
    else filename = "bestscore_hard.txt";

    ofstream out(filename);
    out << score;
}

// Helper function to print border
void Wordle::printBorder(int width) {
    cout << BLUE;
    for (int i = 0; i < width; i++) cout << "=";
    cout << RESET << endl;
}

// Helper function to print centered text
void Wordle::printCentered(const string& text, int width) {
    int padding = (width - text.length()) / 2;
    for (int i = 0; i < padding; i++) cout << " ";
    cout << text << endl;
}

// DSA: Give hint using queue (FIFO - reveals letters in order)
// Returns true if hint costs a life, false if it's free
bool Wordle::giveHint() {
    if (hintQueue.empty()) {
        cout << "\n" << RED << "   ✗ No more hints available!" << RESET << endl;
        return false;
    }

    // Get next hint from queue
    HintNode hint = hintQueue.front();
    hintQueue.pop();

    hintsUsed++;

    if (hintsUsed == 1) {
        // First hint is FREE
        cout << "\n" << YELLOW << "   ✓ FREE HINT: " << RESET;
        cout << "Letter at position " << YELLOW << hint.position + 1 << RESET
            << " is " << GREEN << "'" << hint.letter << "'" << RESET << endl;
        cout << GRAY << "   (Next hint will cost 1 life!)" << RESET << endl;
        return false;
    }
    else {
        // Additional hints cost a life
        cout << "\n" << YELLOW << "   💡 HINT (Costs 1 life): " << RESET;
        cout << "Letter at position " << YELLOW << hint.position + 1 << RESET
            << " is " << GREEN << "'" << hint.letter << "'" << RESET << endl;
        return true;
    }
}

void Wordle::checkGuess(char* guess) {
    bool usedSecret[MAX_WORD_LENGTH] = { false };
    bool usedGuess[MAX_WORD_LENGTH] = { false };

    cout << "\n   ";
    // First pass: mark exact matches (green) with boxes
    for (int i = 0; i < currentWordLen; i++) {
        if (guess[i] == secretWord[i]) {
            cout << GREEN << " " << (char)toupper(guess[i]) << " " << RESET;
            usedSecret[i] = true;
            usedGuess[i] = true;
        }
        else {
            cout << GRAY << " _ " << RESET;
        }
    }
    cout << "\n" << endl;

    // Second pass: check for yellow (letter in word but wrong position)
    bool hasYellow = false;
    bool hasGray = false;

    for (int i = 0; i < currentWordLen; i++) {
        if (!usedGuess[i]) {
            bool found = false;
            for (int j = 0; j < currentWordLen; j++) {
                if (!usedSecret[j] && guess[i] == secretWord[j]) {
                    found = true;
                    usedSecret[j] = true;
                    break;
                }
            }
            if (found) {
                if (!hasYellow) cout << "   ";
                cout << YELLOW << (char)toupper(guess[i]) << RESET << " ";
                hasYellow = true;
            }
        }
    }
    if (hasYellow) cout << YELLOW << "← in word, wrong spot" << RESET << endl;

    for (int i = 0; i < currentWordLen; i++) {
        if (!usedGuess[i]) {
            bool found = false;
            for (int j = 0; j < currentWordLen; j++) {
                if (!usedSecret[j] && guess[i] == secretWord[j]) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                if (!hasGray) cout << "   ";
                cout << GRAY << (char)toupper(guess[i]) << RESET << " ";
                hasGray = true;
            }
        }
    }
    if (hasGray) cout << GRAY << "← not in word" << RESET << endl;
}

void Wordle::play() {
    string diffName;
    if (currentDifficulty == EASY) diffName = "EASY";
    else if (currentDifficulty == MEDIUM) diffName = "MEDIUM";
    else diffName = "HARD";

    // Enhanced header
    cout << "\n";
    printBorder(60);
    cout << BLUE << "   ";
    cout << GREEN << "W" << YELLOW << "O" << BLUE << "R" << RED << "D" << GREEN << "L" << YELLOW << "E" << RESET;
    cout << GRAY << " - C++ CLI Edition" << RESET << endl;
    printBorder(60);

    cout << "\n   " << YELLOW << "► DIFFICULTY: " << RESET << diffName << endl;
    cout << "   " << BLUE << "► WORD LENGTH: " << RESET << currentWordLen << " letters" << endl;
    cout << "   " << GREEN << "► ATTEMPTS: " << RESET << maxAttempts << endl;
    cout << "   " << YELLOW << "► HINT: " << RESET << "Type 'hint' (1st free, rest cost 1 life)\n" << endl;

    printBorder(60);

    for (int attempt = 1; attempt <= maxAttempts; attempt++) {
        char guess[MAX_WORD_LENGTH];

        // Display lives
        int livesLeft = maxAttempts - attempt + 1;
        cout << "\n   ";
        for (int i = 0; i < livesLeft; i++) {
            cout << RED << "♥ " << RESET;
        }
        for (int i = livesLeft; i < maxAttempts; i++) {
            cout << GRAY << "♡ " << RESET;
        }
        cout << GRAY << " (" << livesLeft << "/" << maxAttempts << ")" << RESET << endl;

        cout << "   " << BLUE << "Attempt #" << attempt << " ► " << RESET;

        string input;
        if (!(cin >> input)) {
            cout << RED << "\n   Input error." << RESET << endl;
            return;
        }

        if (input == "hint") {
            bool costsLife = giveHint();
            if (costsLife) {
                // Hint costs a life, don't decrement attempt (it will naturally increment)
                cout << RED << "   ⚠ You lost 1 life for this hint!" << RESET << endl;
            }
            else {
                // Free hint, decrement attempt so it doesn't count
                attempt--;
            }
            continue;
        }

        if (input.length() != currentWordLen) {
            cout << RED << "   ✗ Word must be " << currentWordLen << " letters long!" << RESET << endl;
            attempt--;
            continue;
        }

        // Copy input to guess buffer
        strcpy_s(guess, MAX_WORD_LENGTH, input.c_str());

        // DSA: Add to doubly linked list (guess history)
        guesses.addGuess(guess);

        // DSA: Push to stack (for potential undo feature)
        GuessRecord record;
        strcpy_s(record.guess, MAX_WORD_LENGTH, guess);
        record.attemptNum = attempt;
        guessStack.push(record);

        checkGuess(guess);

        if (strcmp(guess, secretWord) == 0) {
            // WIN!
            cout << "\n";
            printBorder(60);
            cout << GREEN << "\n";
            printCentered("★ ★ ★ CONGRATULATIONS! ★ ★ ★", 60);
            cout << RESET;

            cout << "\n   You guessed the word: " << GREEN << "\"" << secretWord << "\"" << RESET << endl;
            cout << "   Attempts used: " << YELLOW << attempt << "/" << maxAttempts << RESET << endl;
            cout << "   Hints used: " << YELLOW << hintsUsed << RESET << endl;

            printBorder(60);
            guesses.displayGuesses();

            int score = attempt;
            int best = getBestScore(currentDifficulty);

            cout << "\n";
            if (score < best) {
                cout << YELLOW << "   ⭐ NEW BEST SCORE: " << score << " attempts!" << RESET << endl;
                saveBestScore(score, currentDifficulty);
            }
            else {
                cout << "   Best Score: " << GREEN << best << RESET << " attempts" << endl;
            }
            cout << "\n";
            return;
        }
    }

    // GAME OVER
    cout << "\n";
    printBorder(60);
    cout << RED << "\n";
    printCentered("☠ GAME OVER ☠", 60);
    cout << RESET;

    cout << "\n   The word was: " << GREEN << "\"" << secretWord << "\"" << RESET << endl;
    cout << RED << "   Better luck next time!" << RESET << endl;

    printBorder(60);
    guesses.displayGuesses();
    cout << "\n";
}
