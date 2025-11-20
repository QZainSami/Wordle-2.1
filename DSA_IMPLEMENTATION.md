# Wordle Game - DSA Implementation Documentation

## 📋 Project Overview
This is a C++ implementation of the Wordle game with comprehensive Data Structures and Algorithms (DSA) concepts integrated for CS Lab Project (Semester 3).

## 🎯 Difficulty System (Updated)

### Previous Implementation
- Difficulty based on word complexity (rare vs common words)
- All difficulties used 5-letter words with 6 attempts
- Problem: Players couldn't guess unfamiliar words

### New Implementation
Difficulty now based on **word length** and **attempt count**:

| Difficulty | Word Length | Attempts | Word Count | Description |
|------------|-------------|----------|------------|-------------|
| **Easy**   | 4 letters   | 5 tries  | 300 words  | Common 4-letter words |
| **Medium** | 5 letters   | 6 tries  | 400 words  | Standard 5-letter words |
| **Hard**   | 6 letters   | 7 tries  | 300 words  | Challenging 6-letter words |

**Total Word Library: 1000 words** (300 + 400 + 300)

## 🗂️ Data Structures & Algorithms Implemented

### 1. **Doubly Linked List** (GuessList.h, GuessList.cpp)
**Purpose:** Store and manage player's guess history

**Implementation:**
```cpp
struct DoublyNode {
    char guess[MAX_WORD_LENGTH];
    DoublyNode* next;  // Forward link
    DoublyNode* prev;  // Backward link
};
```

**Features:**
- Forward traversal: Display guesses in order
- Backward traversal: Display guesses in reverse (`displayReverse()`)
- Efficient insertion at tail: O(1) time complexity

**DSA Concepts Demonstrated:**
- Bidirectional traversal
- Node insertion with prev/next pointer management
- Memory management (deletion and cleanup)

---

### 2. **Circular Linked List** (GuessList.h, GuessList.cpp)
**Purpose:** Create circular reference for continuous traversal

**Implementation:**
```cpp
// Last node points back to first node
tail->next = head;
head->prev = tail;
```

**Features:**
- `displayCircular(int rounds)`: Traverse the list multiple times in a loop
- Demonstrates circular nature: After reaching the tail, it wraps to head

**DSA Concepts Demonstrated:**
- Circular structure (no NULL endpoints)
- Infinite loop traversal with controlled exit
- Breaking circular link before deletion

---

### 3. **Stack (LIFO - Last In First Out)** (Wordle.h, Wordle.cpp)
**Purpose:** Track guess history for potential undo functionality

**Implementation:**
```cpp
struct GuessRecord {
    char guess[MAX_WORD_LENGTH];
    int attemptNum;
};
std::stack<GuessRecord> guessStack;
```

**Usage:**
- Every guess is pushed onto the stack
- Most recent guess is at the top (LIFO principle)
- Can be extended to implement "undo last guess" feature

**DSA Concepts Demonstrated:**
- LIFO ordering
- Push operation: Add new guess
- Potential for pop operation: Remove last guess

---

### 4. **Queue (FIFO - First In First Out)** (Wordle.h, Wordle.cpp)
**Purpose:** Manage hint system in order

**Implementation:**
```cpp
struct HintNode {
    int position;
    char letter;
};
std::queue<HintNode> hintQueue;
```

**Usage:**
- All letter positions are added to queue at game start (randomized order)
- `giveHint()` retrieves and removes the front element (FIFO)
- Ensures hints are given in a fair, sequential manner

**DSA Concepts Demonstrated:**
- FIFO ordering
- Enqueue operation: Add hints at initialization
- Dequeue operation: Remove and reveal hint from front

---

### 5. **Singly Linked List** (Already in original code)
**Purpose:** Basic guess history storage

**Implementation:**
- `GuessList` uses doubly linked list, but demonstrates singly linked list principles
- Forward traversal only in basic operations
- Sequential access pattern

---

## 📊 Word Library Structure

### Easy Words (4-letter) - 300 words
```cpp
char easyWords[300][5] = {
    "able", "acid", "aged", "also", "area", ...
};
```
Examples: able, bank, code, duck, exam, food, game, hand, idea, jump

### Medium Words (5-letter) - 400 words
```cpp
char mediumWords[400][6] = {
    "about", "above", "abuse", "actor", "acute", ...
};
```
Examples: about, angel, board, claim, dream, event, frame, glass, heart, judge

### Hard Words (6-letter) - 300 words
```cpp
char hardWords[300][7] = {
    "abroad", "accept", "access", "across", "acting", ...
};
```
Examples: abroad, beauty, change, doctor, effect, family, garden, health, impact, jungle

---

## 🔧 Configuration Changes

### config.h
```cpp
// Old
const int WORD_LEN = 5;
const int MAX_ATTEMPTS = 6;

// New
const int EASY_WORD_LEN = 4;
const int MEDIUM_WORD_LEN = 5;
const int HARD_WORD_LEN = 6;

const int EASY_ATTEMPTS = 5;
const int MEDIUM_ATTEMPTS = 6;
const int HARD_ATTEMPTS = 7;
```

### Dynamic Configuration
- Word length changes based on difficulty
- Attempt count adjusts automatically
- Separate best score files per difficulty:
  - `bestscore_easy.txt`
  - `bestscore_medium.txt`
  - `bestscore_hard.txt`

---

## 🎮 Game Flow with DSA

1. **Game Initialization**
   - Load word dictionary (Array)
   - Initialize hint queue (Queue - FIFO)
   - Clear guess stack (Stack - LIFO)
   - Clear guess list (Doubly Linked List)

2. **During Gameplay**
   - Player makes guess → Added to:
     - Doubly Linked List (for history display)
     - Stack (for potential undo)
   - Player requests hint → Dequeue from hint queue

3. **Game End**
   - Display guess history (Doubly LL traversal)
   - Optional: Display reverse history (Doubly LL backward)
   - Update best score for current difficulty

---

## 🏗️ File Structure

```
Wordle/
├── main.cpp              # Main menu and game loop
├── Wordle.h              # Wordle class declaration (Stack, Queue)
├── Wordle.cpp            # Wordle logic + 1000-word library
├── GuessList.h           # Doubly/Circular linked list declaration
├── GuessList.cpp         # Doubly/Circular linked list implementation
├── config.h              # Configuration constants
├── colors.h              # Terminal color codes
└── DSA_IMPLEMENTATION.md # This documentation
```

---

## 💡 DSA Concepts Summary

| DSA Concept | Where Used | Purpose |
|-------------|------------|---------|
| **Doubly Linked List** | GuessList | Guess history with bidirectional traversal |
| **Circular Linked List** | GuessList | Demonstrates circular traversal |
| **Stack (LIFO)** | Wordle class | Track guess history (undo potential) |
| **Queue (FIFO)** | Wordle class | Hint system (fair ordering) |
| **Array** | Word storage | Fast random access for word selection |

---

## 🚀 How to Build and Run

### Using Visual Studio
1. Open `Wordle.sln`
2. Build Solution (Ctrl+Shift+B)
3. Run (F5 or Ctrl+F5)

### Command Line (if compiler is set up)
```bash
cl /EHsc /Fe:Wordle.exe main.cpp Wordle.cpp GuessList.cpp
Wordle.exe
```

---

## 📝 Features for Presentation

### DSA Demonstrations You Can Show:

1. **Doubly Linked List**
   - Show forward traversal (normal guess history)
   - Show backward traversal with `displayReverse()`

2. **Circular Linked List**
   - Call `displayCircular(2)` to show 2 complete rounds of traversal

3. **Stack**
   - Explain how each guess is pushed onto stack
   - Demonstrate LIFO concept (last guess is on top)

4. **Queue**
   - Show how hints are given in order
   - First hint initialized is first hint shown

5. **Dynamic Sizing**
   - Easy: 4 letters → less complexity
   - Hard: 6 letters → more complexity

---

## 🎯 Academic Relevance

This project demonstrates:
- ✅ Multiple linked list types (singly, doubly, circular)
- ✅ Stack implementation (LIFO principle)
- ✅ Queue implementation (FIFO principle)
- ✅ Array usage for efficient storage
- ✅ Memory management (new/delete)
- ✅ Pointer manipulation
- ✅ Dynamic data structures
- ✅ Time complexity considerations

---

## 👨‍🎓 Project Info
- **Course:** Data Structures and Algorithms Lab
- **Semester:** 3rd (BS Computer Science)
- **Total Words:** 1000 (300 easy + 400 medium + 300 hard)
- **DSA Concepts:** 5+ (Singly LL, Doubly LL, Circular LL, Stack, Queue)
- **Lines of Code:** ~800+ lines

---

## 📌 Important Notes

1. **CLI Output Preserved:** All terminal colors and formatting remain unchanged
2. **Best Scores:** Tracked separately per difficulty level
3. **Hint System:** Uses queue for fair, ordered hint distribution
4. **Memory Safe:** Proper cleanup in destructors and clear() functions
5. **Extensible:** Stack can be extended for undo functionality

---

**Good luck with your presentation! 🎉**
