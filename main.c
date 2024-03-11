#include <stdio.h>
#include <stdlib.h>

#include "my_string.h"
#include "generic.h"
#include "generic_vector.h"
#include "associative_array.h"

#include "Evil_Hangman.h"

int main(int agrc, char* argv[])
{
  FILE* fp;

  fp = fopen("dictionary.txt", "r");
  
  GENERIC_VECTOR hGeneric_Vector[30] = {NULL};

  MY_STRING hMy_string = NULL;

  int size;
  int length;
  int guesses;

  int play_again = 1;

  hMy_string = my_string_init_default();
  
  for (int i = 0; i <= 29; i++)
  {
    hGeneric_Vector[i] = generic_vector_init_default(my_string_assignment, my_string_destroy);
  }

  while (my_string_extraction(hMy_string, fp))
  {
    size = my_string_get_size(hMy_string);

    generic_vector_push_back(hGeneric_Vector[size], hMy_string);
  }

  /*
  for (int i = 0; i <= 29; i++)
  {
    printf("%d: %d\n", i, generic_vector_get_size(hGeneric_Vector[i]));
  }
  */
  
  //length = word_length();
  //guesses = number_of_guesses();

  //printf("%d\n", length);
  //printf("%d\n", guesses);

  /*
  MY_STRING one = my_string_init_default();

  my_string_push_back(one, 'a');

  MY_STRING two = my_string_init_c_string("b");

  printf("%d", my_string_compare(one, two));
  */

  /*
  AVL avl_tree = avl_init_default();

  MY_STRING key = my_string_init_c_string("aaa");
 
  avl_insert_main(avl_tree, key, key);

  avl_print(avl_tree);
  */

  
  while (play_again == 1)
  {
    length = word_length();
    guesses = number_of_guesses();
    
    play_again = evil_hangman(hGeneric_Vector[length], length, guesses);
  }
  
  /*
  MY_STRING old_key = NULL;
  MY_STRING word = NULL;
  MY_STRING new_key = NULL;
  
  char guess = 't';
 
  old_key = my_string_init_c_string("---");
  word = my_string_init_c_string("The");
  new_key = my_string_init_default();

  get_word_key_value(word, new_key, old_key, guess);

  my_string_insertion(old_key, stdout);
  printf(" ");
  my_string_insertion(word, stdout);
  printf(" ");
  printf("%c ", guess);
  my_string_insertion(new_key, stdout);
  printf("\n");
  
  MY_STRING old_key_two = NULL;
  MY_STRING word_two = NULL;
  MY_STRING new_key_two = NULL;

  char guess_two = 'r';

  old_key_two = my_string_init_c_string("_____");
  word_two = my_string_init_c_string("Truck");
  new_key_two = my_string_init_default();

  get_word_key_value(word_two, new_key_two, old_key_two, guess_two);

  my_string_insertion(old_key_two, stdout);
  printf(" ");
  my_string_insertion(word_two, stdout);
  printf(" ");
  printf("%c ", guess_two);
  my_string_insertion(new_key_two, stdout);
  printf("\n");
  
  MY_STRING old_key_three = NULL;
  MY_STRING word_three = NULL;
  MY_STRING new_key_three = NULL;

  char guess_three = 'h';

  old_key_three = my_string_init_c_string("--ppy");
  word_three = my_string_init_c_string("Happy");
  new_key_three = my_string_init_default();

  get_word_key_value(word_three, new_key_three, old_key_three, guess_three);

  my_string_insertion(old_key_three, stdout);
  printf(" ");
  my_string_insertion(word_three, stdout);
  printf(" ");
  
  printf("%c ", guess_three);
  my_string_insertion(new_key_three, stdout);
  printf("\n");
  
  MY_STRING old_key_four = NULL;
  MY_STRING word_four = NULL;
  MY_STRING new_key_four = NULL;

  char guess_four = 'z';
  
  old_key_four = my_string_init_c_string("--e---e");
  word_four = my_string_init_c_string("awesome");
  new_key_four = my_string_init_default();

  get_word_key_value(word_four, new_key_four, old_key_four, guess_four);

  my_string_insertion(old_key_four, stdout);
  printf(" ");
  my_string_insertion(word_four, stdout);
  printf(" ");
  printf("%c ", guess_four);
  my_string_insertion(new_key_four, stdout);
  printf("\n");

    
  //evilHangman(hGeneric_Vector[length], length, guesses);

  my_string_destroy(&word);
  my_string_destroy(&old_key);
  my_string_destroy(&new_key);

  my_string_destroy(&word_two);
  my_string_destroy(&old_key_two);
  my_string_destroy(&new_key_two);

  my_string_destroy(&word_three);
  my_string_destroy(&old_key_three);
  my_string_destroy(&new_key_three);

  my_string_destroy(&word_four);
  my_string_destroy(&old_key_four);
  my_string_destroy(&new_key_four);
  */


  for (int i = 0; i <= 29; i++)
  {
    generic_vector_destroy(&hGeneric_Vector[i]);
  }

  my_string_destroy(&hMy_string);
 
  
  fclose(fp);
  
  return 0;
}

 
/*
  MY_STRING array[100];

  for (int i = 0; i < 100; i++)
  {
    array[i] = NULL;
  }

  array[0] = my_string_init_c_string("COPY ME!");

  for (int i = 1; i < 100; i++)
  {
    my_string_assignment(&array[i], array[0]);
  }

  for (int i = 0; i < 100; i++)
  {
    printf("%d ", i + 1);
    
    my_string_insertion(array[i], stdout);

    printf("\n");
    
    my_string_destroy(&array[i]);
  }
  
  return 0;
}
 
*/























  
  /*      
  MY_STRING testing = NULL;
   
  testing = my_string_init_c_string("Testing");
   
  if (my_string_push_back(testing, 'g'))
  {
    my_string_insertion(testing, stdout);
    printf("\n");
  }
  
  if (my_string_pop_back(testing))
  {
    my_string_insertion(testing, stdout);
    printf("\n");
  }
  
  char *pTesting;
  
  pTesting = my_string_at(testing, 2);
  printf("%c\n", *pTesting);

  MY_STRING pTestingTwo = NULL;
  char* pTestingThree;

  pTestingTwo = my_string_init_c_string("NullTerminator");
  pTestingThree = my_string_c_str(pTestingTwo);

  while (*pTestingThree != '\0')
  {
    printf("%c", *pTestingThree);
    pTestingThree++;
  }
  printf("\n");
  
  MY_STRING empty_string = NULL;

  empty_string = my_string_init_c_string("NotEmpty");
  
  if (my_string_empty(empty_string))
  {
    printf("The string is empty.\n");
  }
  else
  {
    printf("The string is not empty.\n");
  }
  
  MY_STRING hLeft_string = NULL;
  MY_STRING hRight_string = NULL;
  
  hLeft_string = my_string_init_c_string("This is");
  hRight_string = my_string_init_c_string(" test");

  if (my_string_concat(hLeft_string, hRight_string))
  {
    my_string_insertion(hLeft_string, stdout);
    printf("\n");
  }
  
  my_string_destroy(&testing);
  my_string_destroy(&empty_string);
  my_string_destroy(&hLeft_string);
  my_string_destroy(&hRight_string);
  my_string_destroy(&pTestingTwo);
  return 0;
}
  */


  /*  
  MY_STRING hMy_string = NULL;
  FILE *fp;
  int size;
  
  hMy_string = my_string_init_default();

  fp = fopen("dictionary.txt", "r");

  while (my_string_extraction(hMy_string, fp))
  {
      size = my_string_get_size(hMy_string);

      if (size == 5)
      {
	  my_string_insertion(hMy_string, stdout);
	  printf("\n");
      }
  }

  my_string_destroy(&hMy_string);

  fclose(fp);
  
  return 0;
}   
  */
  /*        
  MY_STRING hMy_string = NULL;

  FILE *fp;

  hMy_string = my_string_init_default();

  fp = fopen("simple.txt", "r");

  while (my_string_extraction(hMy_string, fp))
  {
      my_string_insertion(hMy_string, stdout);

      printf("\n");

      if (fgetc(fp) == ' ')
      {
	  printf("Found a space after the string\n");
      }
  }

  my_string_destroy(&hMy_string);

  fclose(fp);
 
  return 0;
}
  */
  /*
  MY_STRING hMy_string = NULL;
 
  MY_STRING left_string = NULL, right_string = NULL;
    
  hMy_string = my_string_init_default();
  //  my_string_get_size(hMy_string);
  //my_string_get_capacity(hMy_string);
 
  //left_string = my_string_init_default("apd");
  //right_string = my_string_init_default("apple");
 
  //printf("%d ", my_string_compare(left_string, right_string));
 
  my_string_destroy(&hMy_string);
  //my_string_destroy(&left_string);
  //my_string_destroy(&right_string);
  
  int column = 20, row = 30, count = 0;

  int **pArr;
  pArr = (int **)malloc(column * sizeof(int *));

  for (int i = 0; i < column; i++) {

    pArr[i] = (int *)malloc(row * sizeof(int *));
  }

  for (int i = 0; i < column; i++) {
    for (int j = 0; j < row; j++) {

      pArr[i][j] = count + j;
      printf("%2d ", pArr[i][j]);
    }
    count++;
    printf("\n");
  }

  for (int i = 0; i < column; i++) {

    free(pArr[i]);
  }

  free(pArr);
  */
  
