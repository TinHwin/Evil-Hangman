#ifndef EVIL_HANGMAN_H
#define EVIL_HANGMAN_H

#include "my_string.h"
#include "generic_vector.h"

int evil_hangman(GENERIC_VECTOR hList_vector, int length, int guesses);

int word_length(void);

int number_of_guesses(void);

char letter_guess(MY_STRING letter_guessed);

void clearKeyboardBuffer(void);

Status get_word_key_value(MY_STRING current_word_family, MY_STRING new_key, MY_STRING word, char guess);

int play_again(void);

int number_of_words_remaining(void);

#endif
