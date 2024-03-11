#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#include "my_string.h"
#include "generic.h"
#include "generic_vector.h"
#include "associative_array.h"

#include "Evil_Hangman.h"

int evil_hangman(GENERIC_VECTOR hList_vector, int length, int guesses)
{
  GENERIC_VECTOR original_list_vector = (GENERIC_VECTOR *)hList_vector;
  GENERIC_VECTOR update_list_vector = generic_vector_init_default(my_string_assignment, my_string_destroy);

  GENERIC_VECTOR replace_list_vector = generic_vector_init_default(my_string_assignment, my_string_destroy);
  
  MY_STRING choosen_letter = my_string_init_default();

  MY_STRING current_key = my_string_init_default();

  MY_STRING new_key = my_string_init_default();

  MY_STRING replace_current_key = my_string_init_default();
  
  int guesses_left = guesses;
  int match = 0;
  int play = 0;
  int print = 0;
  
  AVL avl_tree = avl_init_default();

  NODE *pNode = NULL;

  srand(time(0));

  print = number_of_words_remaining();

  for (int i = 0; i < length; i++)
  {
    my_string_push_back(current_key, '-');
  }

  for (int i = 0; i < generic_vector_get_size(original_list_vector); i++)
  {
    generic_vector_push_back(update_list_vector, *generic_vector_at(original_list_vector, i));
  }

  /*
  for (int i = 0; i < generic_vector_get_size(update_list_vector); i++)
  {
    my_string_insertion(*generic_vector_at(update_list_vector, i), stdout);
    printf("\n");
  }
  */
  
  while (guesses_left != 0)
  {
    char letter;
    int max;
    
    letter = letter_guess(choosen_letter);
    
    for (int i = 0; i < generic_vector_get_size(update_list_vector); i++)
    {      
      get_word_key_value(*generic_vector_at(update_list_vector, i), new_key, current_key, letter);
      
      avl_insert_main(avl_tree, new_key, *generic_vector_at(update_list_vector, i));

      my_string_destroy(&new_key);

      new_key = my_string_init_default();
    }
    
    max = avl_inorder_find_largest_family(avl_tree);
    
    pNode = find_largest_family(avl_tree, max);
    
    my_string_destroy(&current_key);
    current_key = my_string_init_default();
    
    for (int i = 0; i < my_string_get_size(pNode->word_family); i++)
    {
	my_string_push_back(current_key, *my_string_at(pNode->word_family, i));
    }
    
    for (int i = 0; i < generic_vector_get_size(pNode->word_list); i++)
    {
	generic_vector_push_back(replace_list_vector, *generic_vector_at(pNode->word_list, i));
    }
    
    generic_vector_destroy(&update_list_vector);
    update_list_vector = generic_vector_init_default(my_string_assignment, my_string_destroy);
       
    for (int i = 0; i < generic_vector_get_size(replace_list_vector); i++)
    {
      generic_vector_push_back(update_list_vector, *generic_vector_at(replace_list_vector, i));
    }
    
    for (int i = 0; i < generic_vector_get_size(update_list_vector); i++)
    {
      get_word_key_value((*generic_vector_at(update_list_vector, i)), replace_current_key, current_key, letter);
      
      for (int i = 0; i < my_string_get_size(replace_current_key); i++)
      {
	if (max != 1)
	{
	  if (*my_string_at(*generic_vector_at(update_list_vector, i), i) == letter)
	  {
	    match = 1;
	  }
	}

	if (max == 1)
	{
	  if (*my_string_at(*generic_vector_at(update_list_vector, 0), i) == letter)
	  {
	    match = 1;
	  }
	}
      }
      
      my_string_destroy(&replace_current_key);

      replace_current_key = my_string_init_default();
    }
    
    my_string_push_back(choosen_letter, letter);
    my_string_push_back(choosen_letter, ' ');
    
    generic_vector_destroy(&replace_list_vector);
    replace_list_vector = generic_vector_init_default(my_string_assignment, my_string_destroy);

    if (match == 1)
    {
      if (my_string_compare(current_key, *generic_vector_at(update_list_vector, 0)) == 0)
      {
	printf("Congrats, you guessed the word.\n");

	avl_destroy(&avl_tree);

	my_string_destroy(&choosen_letter);
	my_string_destroy(&current_key);
	my_string_destroy(&new_key);
	my_string_destroy(&replace_current_key);

	generic_vector_destroy(&update_list_vector);
	generic_vector_destroy(&replace_list_vector);

	my_string_destroy(&pNode->word_family);
	generic_vector_destroy(&pNode->word_list);

	free(pNode);
	
	play = play_again();

	if (play == 1)
	{
	  return 1;
	}

	if (play == 0)
	{
	  return 0;
	}
	
	return -1;
      }
    }

    avl_print(avl_tree, print);

    printf("\n");
    
    printf("You have %d guesses left.\n", guesses_left - 1);
    printf("Used letters: ");

    my_string_insertion(choosen_letter, stdout);

    printf("\n");

    printf("Word: %s\n", my_string_c_str(current_key));

    if (print == 1)
    {
      printf("The computer has %d possibilities remaining.\n", generic_vector_get_size(pNode->word_list));
    }
    
    printf("\n");
        
    avl_destroy(&avl_tree);
    avl_tree = avl_init_default();

    if (match == 0)
    {
      printf("I'm sorry, there is no letter %c in the word.\n", letter);
      guesses_left--;
    }
    
    match = 0;
  }

  printf("\nI'm sorry, the word I was thinking of was: ");
  
  my_string_insertion(*generic_vector_at(pNode->word_list, (rand() % generic_vector_get_size(pNode->word_list))), stdout);

  printf("\n");

  
  avl_destroy(&avl_tree);

  my_string_destroy(&choosen_letter);
  my_string_destroy(&current_key);
  my_string_destroy(&new_key);
  my_string_destroy(&replace_current_key);

  generic_vector_destroy(&update_list_vector);
  generic_vector_destroy(&replace_list_vector);
  
  my_string_destroy(&pNode->word_family);
  generic_vector_destroy(&pNode->word_list);

  free(pNode);

  play = play_again();

  if (play == 1)
  {
    return 1;
  }

  if (play == 0)
  {
    return 0;
  }
  
  return -1;
}

int word_length(void)
{
  int length;

  printf("Please enter a word length: ");
    
  scanf("%d", &length);
    
  clearKeyboardBuffer();
    
  while (length <= 1 || length == 23 ||  length == 25 || length == 26 || length == 27 || length >= 30)
  {
    printf("Please enter a valid word length: ");

    if (scanf("%d", &length) != 1)
    {
      clearKeyboardBuffer();
    }
  }

  return length;
}

int number_of_guesses(void)
{
  int guesses;

  printf("Please enter the number of guesses:\n");

  scanf("%d", &guesses);

  clearKeyboardBuffer();
  
  while (guesses <= 0 || guesses > 26)
  {
    printf("Please enter a valid number of guesses:\n");

    if (scanf("%d", &guesses) != 1)
    {
      clearKeyboardBuffer();
    }
  }

  return guesses;
}

char letter_guess(MY_STRING letter_guessed)
{
  char letter;
  
  printf("Please enter a letter:\n");

  scanf("%c", &letter);

  clearKeyboardBuffer();
  
  for (int i = 0; i < my_string_get_size(letter_guessed); i++)
  {
    if ((tolower(*my_string_at(letter_guessed, i))) == letter)
    {
      printf("Letter used already, please enter a different letter:\n");

      scanf("%c", &letter);

      clearKeyboardBuffer();
      
      i = 0;
    }
  }

  return letter;
}

void clearKeyboardBuffer(void) {
    
    char ch;
    int ret;
     
    ret = scanf("%c", &ch);
     
    while (ret == 1 && ch != '\n' && ch != '\0') {
        ret = scanf ("%c", &ch);
    }
}

Status get_word_key_value(MY_STRING current_word_family, MY_STRING new_key, MY_STRING word, char guess)
{
 int word_length;
 char guessCheck = tolower(guess);
 
 word_length = my_string_get_size(word);

 for (int i = 0; i < word_length; i++)
 {
   if ((tolower(*my_string_at(current_word_family, i))) == guessCheck)
   {
     my_string_push_back(new_key, guessCheck);
   }
   else
   {
     my_string_push_back(new_key, tolower(*my_string_at(word, i)));
   }
 }

 return SUCCESS;
}

int play_again(void)
{
  char letter;

  printf("Would you like to play again? (y/n): ");

  scanf("%c", &letter);

  clearKeyboardBuffer();

  letter = tolower(letter);

  while (letter != 'y' && letter != 'n')
  {
    printf("Please enter a valid character (y/n): ");

    scanf("%c", &letter);

    clearKeyboardBuffer();

    letter = tolower(letter);
  }

  if (letter == 'y')
  {
    return 1;
  }

  if (letter == 'n')
  {
    return 0;
  }

  return -1;
}

int number_of_words_remaining(void)
{
  char letter;

  printf("Would you like to see the remaining number of words? (y/n): ");

  scanf("%c", &letter);

  clearKeyboardBuffer();

  letter = tolower(letter);

  while (letter != 'y' && letter != 'n')
  {
    printf("Please enter a valid character (y/n): ");

    scanf("%c", &letter);

    clearKeyboardBuffer();

    letter = tolower(letter);
  }

  if (letter == 'y')
  {
    return 1;
  }

  if (letter == 'n')
  {
    return 0;
  }

  return -1;
}
