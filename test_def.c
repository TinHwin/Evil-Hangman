#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "my_string.h"
#include "unit_test.h"
#include "generic.h"

Status test_init_default_returns_nonNULL(char* buffer, int length)
{
  MY_STRING hString = NULL;

  hString = my_string_init_default();

  if (hString == NULL)
  {
    strncpy (buffer, "test_init_default_returns_nonNULL\n""my_string_string_init_default returns NULL\n", length);

    return FAILURE;
  }
  else
  {
    my_string_destroy(&hString);
    strncpy(buffer, "test_init_default_returns_nonNULL\n", length);

    return SUCCESS;
  }
}

Status test_get_size_on_init_default_returns_0(char* buffer, int length)
{
  MY_STRING hString = NULL; Status status;

  hString = my_string_init_default();

  if(my_string_get_size(hString) != 0)
  {
    status = FAILURE;
    printf("Expected a size of 0 but got %d\n", my_string_get_size(hString));
    strncpy(buffer, "test_get_size_on_init_default_returns_0\n""Did not receive 0 from get_size after init_default\n", length);
  }
  else
  {
    status = SUCCESS;
    strncpy(buffer, "test_get_size_on_init_default_returns_0\n"	    , length);
  }

  my_string_destroy(&hString);

  return status;
}

Status test_thuynh_init_c_string_size(char* buffer, int length)
{
  MY_STRING hString = NULL; Status status;

  hString = my_string_init_c_string("Testing");

  if (my_string_get_size(hString) != 7)
  {
    status = FAILURE;
    printf("Expected a size of 7 but got %d\n", my_string_get_size(hString));
    strncpy(buffer, "test_thuynh_init_c_string_size\n""Did not receive size of 7 afrer my_string_init_c_string\n", length);
  }
  else
  {
    status = SUCCESS;
    strncpy(buffer, "test_thuynh_init_c_string_size\n", length);
  }

  my_string_destroy(&hString);

  return status;
}

Status test_thuynh_init_c_string_capacity(char* buffer, int length)
{
  MY_STRING hString = NULL; Status status;

  hString = my_string_init_c_string("Testing");

  if (my_string_get_capacity(hString) != my_string_get_size(hString) + 1)
  {
    status = FAILURE;
    printf("Expected a capacity of 8 but got %d\n", my_string_get_size(hString));
    strncpy(buffer, "test_thuynh_init_c_string_capacity\n""Did not recieve capacity of 8 after my_string_init_c_string\n", length);
  }
  else
  {
    status = SUCCESS;
    strncpy(buffer, "test_thuynh_init_c_string_size\n", length);
  }

  my_string_destroy(&hString);

  return status;
}

Status test_thuynh_compare_smaller(char* buffer, int length)
{
  MY_STRING hLeftString = NULL; MY_STRING hRightString = NULL; Status status;

  hLeftString = my_string_init_c_string("Left");
  hRightString = my_string_init_c_string("Right");

  if (my_string_compare(hLeftString, hRightString) != -1)
  {
    status = FAILURE;
    printf("Expected -1 as left string was smaller than right string but got %d\n", my_string_compare(hLeftString, hRightString));
    strncpy(buffer, "test_thuynh_compare_smaller\n""Did not receive -1 after my_string_compare\n", length);
  }
  else
  {
    status = SUCCESS;
    strncpy(buffer, "test_thuynh_compare_smaller\n", length);
  }

  my_string_destroy(&hLeftString);
  my_string_destroy(&hRightString);

  return status;
}

Status test_thuynh_compare_larger(char* buffer, int length)
{
  MY_STRING hLeftString = NULL; MY_STRING hRightString = NULL; Status status;

  hLeftString = my_string_init_c_string("Right");
  hRightString = my_string_init_c_string("Left");

  if (my_string_compare(hLeftString, hRightString) != 1)
  {
    status = FAILURE;
    printf("Expected 1 as left string was larger than right string but got %d\n", my_string_compare(hLeftString, hRightString));
    strncpy(buffer, "test_thuynh_compare_larger\n""Did not receive 1 after my_string_compare\n", length);
  }
  else
  {
    status = SUCCESS;
    strncpy(buffer, "test_thuynh_compare_larger\n", length);
  }

  my_string_destroy(&hLeftString);
  my_string_destroy(&hRightString);

  return status;
}

Status test_thuynh_compare_equal(char* buffer, int length)
{
  MY_STRING hLeftString = NULL; MY_STRING hRightString = NULL; Status status;

  hLeftString = my_string_init_c_string("Equal");
  hRightString = my_string_init_c_string("Equal");

  if (my_string_compare(hLeftString, hRightString) != 0)
  {
    status = FAILURE;
    printf("Expected 0 as both string is equal but got %d\n", my_string_compare(hLeftString, hRightString));
    strncpy(buffer, "test_thuynh_compare_equal\n""Did not receive 0 after my_string_compare\n", length);
  }
  else
  {
    status = SUCCESS;
    strncpy(buffer, "test_thuynh_compare_larger\n", length);
  }

  my_string_destroy(&hLeftString);
  my_string_destroy(&hRightString);

  return status;
}

Status test_thuynh_extraction_resize_not_needed(char* buffer, int length)
{
  MY_STRING hString = NULL; FILE* fp; int size; Status status;

  hString = my_string_init_default();
  fp = fopen("dictionary.txt", "r");
 
  if (my_string_extraction(hString, fp))
  {
    size = my_string_get_size(hString);

    if (size != 2)
    {
      status = FAILURE;
      printf("Expected size of 2 as the first word of the directionary is aa but got size of %d\n", my_string_get_size(hString));
      strncpy(buffer, "test_thuynh_extraction_resize_not_needed\n""Did not receive 2 after my_string_get_size\n", length);
    }
    else
    {
      status = SUCCESS;
      strncpy(buffer, "test_thuynh_extraction_resize_not_needed\n", length);
    }
  }
  else
  {
    status = FAILURE;
    printf("Expected SUCCESS but got FAILURE\n");
    strncpy(buffer, "test_thuynh_extraction_resize_not_needed\n""Did not receive SUCCESS after my_string_extraction\n", length);
  }

  my_string_destroy(&hString);
  fclose(fp);
  
  return status;
}

Status test_thuynh_extraction_resize_needed(char* buffer, int length)
{
  MY_STRING hString = NULL; FILE* fp; int size; Status status;

  hString = my_string_init_c_string("");
  fp = fopen("dictionary.txt", "r");

  if (my_string_extraction(hString, fp))
  {
    size = my_string_get_size(hString);

    if (size != 2)
    {
      status = FAILURE;
      printf("Expected size of 2 as the first word of the directionary is aa but got size of %d\n", my_string_get_size(hString));
      strncpy(buffer, "test_thuynh_extraction_resize_needed\n""Did not receive 2 after my_string_get_size\n", length);
    }
    else
    {
      status = SUCCESS;
      strncpy(buffer, "test_thuynh_extraction_resize_needed\n", length);
    }
  }
  else
  {
    status = FAILURE;
    printf("Expected SUCCESS but got FAILURE\n");
    strncpy(buffer, "test_thuynh_extraction_resize_needed\n""Did not receive SUCCESS after my_string_extraction\n", length);
  }

  my_string_destroy(&hString);
  fclose(fp);
  
  return status;
}

Status test_thuynh_insertion_with_NULL(char* buffer, int length)
{
  MY_STRING hString = NULL; FILE* fp; Status status;

  fp = fopen("dictionary.txt", "r");
  
  if (my_string_insertion(hString, fp))
  {
    status = FAILURE;
    printf("Expected FAILURE as variable is not intialized, but got SUCCESS\n");
    strncpy(buffer, "test_thuynh_insertion_with_NULL\n""Did not receive FAILURE after my_string_insertion\n", length);
    my_string_destroy(&hString);
  }
  else
  {
    status = SUCCESS;
    strncpy(buffer, "test_thuynh_insertion_with_NULL\n", length);
  }

  fclose(fp);

  return status;
}

Status test_thuynh_insertion_without_NULL(char* buffer, int length)
{
  MY_STRING hString = NULL; FILE* fp; Status status;

  hString = my_string_init_default();
  fp = fopen("dictionary.txt", "r");
  
  if (my_string_insertion(hString, fp))
  {
    status = SUCCESS;
    strncpy(buffer, "test_thuynh_insertion_without_NULL\n", length);
  }
  else
  {
    status = FAILURE;
    printf("Expected SUCCESS as variable is initialized, but got FAILURE\n");
    strncpy(buffer, "test_thuynh_insertion_without_NULL\n""Did not receive SUCCESS after my_string_insertion\n", length);
  }
  
  my_string_destroy(&hString);
  fclose(fp);

  return status;
}

Status test_thuynh_push_back_empty(char* buffer, int length)
{
  MY_STRING hString = NULL; MY_STRING hStringTwo = NULL; Status status;
  
  hString = my_string_init_default();
  hStringTwo = my_string_init_c_string("c");
  
  my_string_push_back(hString, 'c');

  my_string_c_str(hString);
  my_string_c_str(hStringTwo);
  
  if (my_string_compare(hString, hStringTwo) == 0)
  {
    status = SUCCESS;
    strncpy(buffer, "test_thuynh_push_empty\n", length);
  }
  else
  {
    status = FAILURE;
    printf("Expected 0 from compare string after push back but receive %d\n", my_string_compare(hString, hStringTwo));
    strncpy(buffer, "test_thuynh_push_empty\n""Did not recieve 0 after my_string_compare to check if push back match up with the expected outcome\n", length);
  }

  my_string_destroy(&hString);
  my_string_destroy(&hStringTwo);
  
  return status;
}

Status test_thuynh_push_back_resize_needed(char* buffer, int length)
{
  MY_STRING hString = NULL; MY_STRING hStringTwo = NULL; Status status;

  hString = my_string_init_c_string("Test");
  hStringTwo = my_string_init_c_string("Testing");
  
  my_string_push_back(hString, 'i');
  my_string_push_back(hString, 'n');
  my_string_push_back(hString, 'g');

  my_string_c_str(hString);
  my_string_c_str(hStringTwo);
  
  if (my_string_compare(hString, hStringTwo) == 0)
  {
    status = SUCCESS;
    strncpy(buffer, "test_thuynh_push_back_resize_needed\n", length);
  }
  else
  {
    status = FAILURE;
    printf("Expected my_string_compare to return 0 after push back but receive %d\n", my_string_compare(hString, hStringTwo));
    strncpy(buffer, "test_thuynh_push_back_resize_needed\n""Did not recieve 0 after my_string_compare to check if push back match up with the expected outcome\n", length);
  }

  my_string_destroy(&hString);
  my_string_destroy(&hStringTwo);
  
  return status;
}

Status test_thuynh_push_back_size(char* buffer, int length)
{
  MY_STRING hString = NULL; Status status;

  hString = my_string_init_c_string("Testin");
  my_string_push_back(hString, 'g');

  if (my_string_get_size(hString) == 7)
  {
    status = SUCCESS;
    strncpy(buffer, "test_thuynh_push_back\n", length);
  }
  else
  {
    status = FAILURE;
    printf("Expected my_string_get_size to return 7, but receive %d\n", my_string_get_size(hString));
    strncpy(buffer, "test_thuynh_push_back_resize_needed\n""Did not recieve 7 after my_string_get_size to see if the string is successfully push back\n", length);
  }

  my_string_destroy(&hString);
 
  return status;
}

Status test_thuynh_pop_back_empty(char* buffer, int length)
{
  MY_STRING hString = NULL; Status status;

  hString = my_string_init_default();
 
  if (my_string_pop_back(hString))
  {
    status = FAILURE;

    printf("Expected my_string_pop_back to return FAILURE but got SUCCESS\n");
    strncpy(buffer, "test_thuynh_pop_back_empty\n""Did not recieve FAILURE after my_string_pop_back to see if it check to see if the string is empty\n", length);
  }
  else
  {
    status = SUCCESS;
    strncpy(buffer, "test_thuynh_pop_back_empty\n", length);
  }

  my_string_destroy(&hString);

  return status;
}

Status test_thuynh_pop_back(char* buffer, int length)
{
  MY_STRING hString = NULL; MY_STRING hStringTwo = NULL; Status status;

  hString = my_string_init_c_string("Testi");
  hStringTwo = my_string_init_c_string("Test");

  my_string_pop_back(hString);
  
  my_string_c_str(hString);
  my_string_c_str(hStringTwo);
  
  if (my_string_compare(hString, hStringTwo) == 0)
  {
    status = SUCCESS;

    strncpy(buffer, "test_thuynh_pop_back\n", length);
  }
  else
  {
    status = FAILURE;
    printf("Expected my_string_compare to return 0 after pop back, but receive %d\n", my_string_compare(hString, hStringTwo));
    strncpy(buffer, "test_thuynh_pop_back\n""Did not recieve 0 after my_string_compare to check if pop back is successful\n", length);
  }

  my_string_destroy(&hString);
  my_string_destroy(&hStringTwo);
  
  return status;
}

Status test_thuynh_at_index_less_zero(char* buffer, int length)
{
  MY_STRING hString = NULL; Status status;

  hString = my_string_init_c_string("Testing");
  
  if (my_string_at(hString, -1) != NULL)
  {
    status = FAILURE;
    printf("Expected my_string_at to return NULL, but receive %s\n", my_string_at(hString, -1));
    strncpy(buffer, "test_thuynh_at_index_less_zero\n""Did not recieve NULL after my_string_at to check if it is out of bound\n", length);
  }
  else
  {
    status = SUCCESS;
    strncpy(buffer, "test_thuynh_at_index_less_zero\n", length);
  }

  my_string_destroy(&hString);

  return status;
}

Status test_thuynh_at_index_more_than_size(char* buffer, int length)
{
  MY_STRING hString = NULL; Status status;

  hString = my_string_init_c_string("Testing");

  if (my_string_at(hString, 8) != NULL)
  {
    status = FAILURE;
  }
  else
  {
    status = SUCCESS;
  }

  my_string_destroy(&hString);

  return status;
}
Status test_thuynh_at_zero(char* buffer, int length)
{
  MY_STRING hString = NULL; MY_STRING hStringTwo = NULL; Status status;

  hString = my_string_init_c_string("T");
  hStringTwo = my_string_init_c_string("T");

  if (my_string_compare(hString, hStringTwo) != 0)
  {
    status = FAILURE;
    printf("Expected char to be 'T'\n");
    strncpy(buffer, "Expected char to return T at index 0 to compare with a set character to see if it is successful\n", length);
  }
  else
  {
    status = SUCCESS;
    strncpy(buffer, "test_thuynh_at_zero\n", length);
  }

  my_string_destroy(&hString);
  my_string_destroy(&hStringTwo);
  
  return status;
}

Status test_thuynh_c_str_empty_string(char* buffer, int length)
{
  MY_STRING hString = NULL; Status status;

  hString = my_string_init_c_string("");
  
  if (my_string_c_str(hString) != NULL)
  {
    status = SUCCESS;
    strncpy(buffer, "test_thuynh_c_str_empty_string\n", length);
  }
  else
  {
    status = FAILURE;

    printf("Expected my_string_c_str to not return NULL, but recieve %s\n", my_string_c_str(hString));
    strncpy(buffer, "Expected my_string_c_str to not return NULL due the string being empty\n", length);
  }

  my_string_destroy(&hString);

  return status;
}

Status test_thuynh_c_str_string_size(char* buffer, int length)
{
  MY_STRING hString = NULL; MY_STRING hStringTwo = NULL; Status status; 

  hString = my_string_init_c_string("Testing");
  hStringTwo = my_string_init_c_string("Testing");
  
  my_string_c_str(hString);

  if (my_string_get_size(hString) == my_string_get_size(hStringTwo))
  {
    status = SUCCESS;
    strncpy(buffer, "test_thuynh_c_str_string_size\n", length);
  }
  else
  {
    status = FAILURE;
    printf("Expected my_string_get_size to be 7 but receive %d\n", my_string_get_size(hString));
    strncpy(buffer, "Expected my_string_get_size to equal since '\0' does not count as an increase size\n", length);
  }

  my_string_destroy(&hString);
  my_string_destroy(&hStringTwo);

  return status;
}

Status test_thuynh_concat_empty(char* buffer, int length)
{
  MY_STRING hString = NULL; MY_STRING hStringTwo = NULL; MY_STRING hStringThree = NULL; Status status;

  hString = my_string_init_c_string("");
  hStringTwo = my_string_init_c_string("");

  hStringThree = my_string_init_c_string("");
  
  my_string_concat(hString, hStringTwo);

  my_string_c_str(hString);
  my_string_c_str(hStringThree);
  
  if (my_string_compare(hString, hStringThree) == 0)
  {
    status = SUCCESS;
    strncpy(buffer, "test_thuynh_concat_empty\n", length);
  }
  else
  {
    status = FAILURE;
    printf("Expected my_string_compare to return 0 but receive %d\n", my_string_compare(hString, hStringThree));
    strncpy(buffer, "Expected my_string_compare to show that concat is equal to the set string\n", length);
  }

  my_string_destroy(&hString);
  my_string_destroy(&hStringTwo);
  my_string_destroy(&hStringThree);

  return status;
}
Status test_thuynh_concat_resize_needed(char* buffer, int length)
{
  MY_STRING hString = NULL; MY_STRING hStringTwo = NULL; MY_STRING hStringThree = NULL; Status status;

  hString = my_string_init_c_string("Test");
  hStringTwo = my_string_init_c_string("ing");

  hStringThree = my_string_init_c_string("Testing");

  my_string_concat(hString, hStringTwo);

  my_string_c_str(hString);
  my_string_c_str(hStringThree);
  
  if (my_string_compare(hString, hStringThree) == 0)
  {
    status = SUCCESS;
    strncpy(buffer, "test_thuynh_concat_resize_needed\n", length);
  }
  else
  {
    status = FAILURE;
    printf("Expected my_string_compare to return 0 but recieve %d\n", my_string_compare(hString, hStringThree));
    strncpy(buffer, "Expected my_string_compare to return 0 as it show that concat is successfully in matching with the set string.\n", length);
  }

  my_string_destroy(&hString);
  my_string_destroy(&hStringTwo);
  my_string_destroy(&hStringThree);

  return status;
}

Status test_thuynh_empty_not_empty(char* buffer, int length)
{
  MY_STRING hString = NULL; Status status;

  hString = my_string_init_c_string("Test");

  if (my_string_empty(hString))
  {
    status = FAILURE;
    printf("Expected my_string_empty to be FAILURE\n");
    strncpy(buffer, "Expected my_string_empty to be FAILURE since the string is not empty\n", length);
  }
  else
  {
    status = SUCCESS;
    strncpy(buffer, "test_thuynh_empty_not_empty\n", length);
  }

  my_string_destroy(&hString);

  return status;
}

Status test_thuynh_empty(char* buffer, int length)
{
  MY_STRING hString = NULL; Status status;

  hString = my_string_init_c_string("");

  if (my_string_empty(hString))
  {
    status = SUCCESS;
    strncpy(buffer, "test_thuynh_empty\n", length);
  }
  else
  {
    status = FAILURE;
    printf("Expected my_string_empty to return SUCCESS\n");
    strncpy(buffer, "Expected my_string_empty to return SUCCESS since the string is empty\n", length);
  }

  my_string_destroy(&hString);

  return status;
}
