#pragma once
#ifndef WORDLE_CONFIG_H
#define WORDLE_CONFIG_H

// Shared configuration constants
const int MAX_WORDS = 1000;
const int MAX_WORD_LENGTH = 7;  // Maximum word length + 1 for null terminator

// Difficulty-based configuration
const int EASY_WORD_LEN = 4;
const int MEDIUM_WORD_LEN = 5;
const int HARD_WORD_LEN = 6;

const int EASY_ATTEMPTS = 5;
const int MEDIUM_ATTEMPTS = 6;
const int HARD_ATTEMPTS = 7;

#endif
