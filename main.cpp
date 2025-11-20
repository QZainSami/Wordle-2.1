#include "Wordle.h"
#include "colors.h"
#include <iostream>
using namespace std;

void printBorder() {
    cout << BLUE;
    for (int i = 0; i < 60; i++) cout << "=";
    cout << RESET << endl;
}

void howToPlay() {
    cout << "\n";
    printBorder();
    cout << YELLOW << "\n              HOW TO PLAY WORDLE\n" << RESET;
    printBorder();

    cout << "\n" << BLUE << "  DIFFICULTY LEVELS:" << RESET << endl;
    cout << "   " << GREEN << "► Easy:" << RESET << "   4-letter words, 5 attempts" << endl;
    cout << "   " << YELLOW << "► Medium:" << RESET << " 5-letter words, 6 attempts" << endl;
    cout << "   " << RED << "► Hard:" << RESET << "   6-letter words, 7 attempts" << endl;

    cout << "\n" << BLUE << "  COLOR CODING:" << RESET << endl;
    cout << "   " << GREEN << "█" << RESET << " Green  = Correct letter in correct position" << endl;
    cout << "   " << YELLOW << "█" << RESET << " Yellow = Correct letter, wrong position" << endl;
    cout << "   " << GRAY << "█" << RESET << " Gray   = Letter not in the word" << endl;

    cout << "\n" << BLUE << "  HINTS:" << RESET << endl;
    cout << "   " << YELLOW << "►" << RESET << " Type 'hint' to reveal a letter" << endl;
    cout << "   " << GREEN << "►" << RESET << " 1st hint is FREE!" << endl;
    cout << "   " << RED << "►" << RESET << " Additional hints cost 1 life each" << endl;

    cout << "\n";
    printBorder();
    cout << "\n";
}

int main() {
    while (true) {
        cout << "\n";
        printBorder();
        cout << GREEN << "  W" << YELLOW << "O" << BLUE << "R" << RED << "D" << GREEN << "L" << YELLOW << "E" << RESET << GRAY << " - Main Menu" << RESET << endl;
        printBorder();

        cout << "\n   " << GREEN << "1." << RESET << " 🎮 Play Wordle\n";
        cout << "   " << BLUE << "2." << RESET << " ❓ How to Play\n";
        cout << "   " << RED << "3." << RESET << " 🚪 Exit\n";
        cout << "\n   " << YELLOW << "► Choose option: " << RESET;
        int choice; cin >> choice;

        if (choice == 1) {
            // Choose difficulty
            cout << "\n";
            printBorder();
            cout << YELLOW << "\n           SELECT DIFFICULTY\n" << RESET;
            printBorder();

            cout << "\n   " << GREEN << "1." << RESET << " 🟢 Easy   - 4 letters, 5 attempts\n";
            cout << "   " << YELLOW << "2." << RESET << " 🟡 Medium - 5 letters, 6 attempts\n";
            cout << "   " << RED << "3." << RESET << " 🔴 Hard   - 6 letters, 7 attempts\n";
            cout << "\n   " << YELLOW << "► Choose difficulty: " << RESET;
            int diffChoice; cin >> diffChoice;

            if (diffChoice < 1 || diffChoice > 3) {
                cout << RED << "Invalid difficulty! Defaulting to Easy.\n" << RESET;
                diffChoice = 1;
            }

            Wordle game;
            game.resetGame(static_cast<Difficulty>(diffChoice));
            game.play();

            cout << "\nDo you want to play again? (y/n): ";
            char again; cin >> again;
            if (again == 'y' || again == 'Y') continue;
            else break;
        }
        else if (choice == 2) {
            howToPlay();
        }
        else if (choice == 3) {
            break;
        }
        else {
            cout << RED << "Invalid option!" << RESET << endl;
        }
    }
    cout << "\nThanks for playing Wordle! Goodbye.\n";
    return 0;
}
