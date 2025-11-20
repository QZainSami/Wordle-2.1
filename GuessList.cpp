#include "GuessList.h"
#include <string>

// DSA: DoublyNode constructor
DoublyNode::DoublyNode(const char g[]) {
    strcpy_s(guess, MAX_WORD_LENGTH, g);
    next = nullptr;
    prev = nullptr;
}

// GuessList constructor
GuessList::GuessList() {
    head = nullptr;
    tail = nullptr;
    size = 0;
}

// DSA: Add a guess to doubly linked list with circular reference
void GuessList::addGuess(const char g[]) {
    DoublyNode* newNode = new DoublyNode(g);

    if (!head) {
        // First node - make it circular
        head = tail = newNode;
        head->next = head;  // Circular: points to itself
        head->prev = head;
    }
    else {
        // Add to end and maintain circular structure
        tail->next = newNode;
        newNode->prev = tail;
        newNode->next = head;  // Circular: last node points to first
        head->prev = newNode;  // Circular: first node's prev points to last
        tail = newNode;
    }
    size++;
}

// Display all guesses (forward traversal)
void GuessList::displayGuesses() {
    if (!head) return;

    cout << "\nYour guesses history:\n";
    DoublyNode* current = head;
    int attempt = 1;

    do {
        cout << attempt++ << ": " << current->guess << endl;
        current = current->next;
    } while (current != head && attempt <= size);
}

// DSA: Display guesses in reverse (demonstrating doubly linked list)
void GuessList::displayReverse() {
    if (!tail) return;

    cout << "\nGuesses in reverse order:\n";
    DoublyNode* current = tail;
    int attempt = size;

    do {
        cout << attempt-- << ": " << current->guess << endl;
        current = current->prev;
    } while (current != tail && attempt >= 1);
}

// DSA: Display circular traversal (demonstrating circular linked list)
void GuessList::displayCircular(int rounds) {
    if (!head) return;

    cout << "\nCircular traversal (" << rounds << " rounds):\n";
    DoublyNode* current = head;
    int totalNodes = rounds * size;

    for (int i = 0; i < totalNodes; i++) {
        cout << (i + 1) << ": " << current->guess << endl;
        current = current->next;
    }
}

// Get size of list
int GuessList::getSize() const {
    return size;
}

// Clear all guesses
void GuessList::clear() {
    if (!head) return;

    // Break circular link first
    if (tail) tail->next = nullptr;

    DoublyNode* current = head;
    while (current) {
        DoublyNode* temp = current;
        current = current->next;
        delete temp;
    }
    head = tail = nullptr;
    size = 0;
}

// Destructor
GuessList::~GuessList() {
    clear();
}
