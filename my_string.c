#include <stdio.h>
#include <stdlib.h>

#include "my_string.h"
#include "generic.h"
#include "status.h"

struct My_string
{
  int size;
  int capacity;
  char *data;
};

typedef struct My_string My_string;

MY_STRING my_string_init_default(void)
{
  My_string *pMy_string = (My_string *)malloc(sizeof(My_string));
  
    pMy_string->size = 0;
    pMy_string->capacity = 7;
    
    pMy_string->data = (char *)malloc(pMy_string->capacity * sizeof(char));
    
    if (pMy_string->data == NULL)
    {
      return NULL;
    }
    else
    {
        return pMy_string;
    }
}

MY_STRING my_string_init_c_string(const char * c_string)
{
  My_string *pMy_string = (My_string *)malloc(sizeof(My_string));

  pMy_string->size = 0;
  pMy_string->capacity = 1;
  
  while (*c_string != '\0')
  {      
        pMy_string->size += 1;
        c_string++;
  }
    
  c_string = c_string - pMy_string->size;
  
  char *pString = (char *)malloc((pMy_string->size + pMy_string->capacity) * sizeof(char));
  int i = 0;
    
  while (*c_string != '\0')
  {      
    pString[i] = *c_string;
    c_string++;
    i++;      
  }
    
  pString[i] = *c_string;
  c_string = c_string - pMy_string->size;
    
  pMy_string->data = pString;
  pMy_string->capacity += pMy_string->size;
  
  // printf("String: %s\n", pMy_string->data);
  // printf("Size: %d\n", pMy_string->size);
  // printf("Capacity: %d\n", pMy_string->capacity);
  
  if (pMy_string == NULL)
  {      
    free(pMy_string);

    return NULL;
  }
  else
  { 
    return pMy_string;
  }
}

void my_string_destroy(Item* pItem)
{
  My_string *pMy_string = (My_string *)*pItem;

  free(pMy_string->data);
  free(pMy_string);

  *pItem = NULL;
}

int my_string_get_capacity(MY_STRING hMy_string)
{
  My_string *pMy_string = (My_string *)hMy_string;

  //  printf("Capacity: %d\n", pMy_string->capacity);
  
  return pMy_string->capacity;
}

int my_string_get_size(MY_STRING hMy_string)
{
  My_string *pMy_string = (My_string *)hMy_string;

  // printf("Size: %d\n", pMy_string->size);
  
  return pMy_string->size;
}

int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string)
{    
  char *pleft_string = (((My_string *)hLeft_string)->data);
  char *pright_string = (((My_string *)hRight_string)->data);

  MY_STRING left_string_copy = my_string_init_default();
  MY_STRING right_string_copy = my_string_init_default();

  my_string_assignment(&left_string_copy, ((My_string *)hLeft_string));
  my_string_assignment(&right_string_copy, ((My_string *)hRight_string));

  my_string_push_back(left_string_copy, '\0');
  my_string_push_back(right_string_copy, '\0');
  
  char *left_string = (((My_string *)left_string_copy)->data);
  char *right_string = (((My_string *)right_string_copy)->data);

  int left_string_check = 0;
  int right_string_check = 0;

  while ((*left_string != '\0') || (*right_string != '\0'))
  {    
    left_string_check += *left_string;
    right_string_check += *right_string;

    if (left_string_check == right_string_check)
    {        
      left_string++;
      right_string++;
    }
    else if ((left_string_check < right_string_check))
    {
      my_string_destroy(&left_string_copy);
      my_string_destroy(&right_string_copy);
      
      return -1;
    }
    else if ((left_string_check > right_string_check))
    {
      my_string_destroy(&left_string_copy);
      my_string_destroy(&right_string_copy);

      return 1;
    }
  }

  if (*left_string == '\0' && *right_string != '\0')
  {
    my_string_destroy(&left_string_copy);
    my_string_destroy(&right_string_copy);
    
    return -1;
  }
    
  if (*left_string != '\0' && *right_string == '\0')
  {
    my_string_destroy(&left_string_copy);
    my_string_destroy(&right_string_copy);
    
    return 1;
  }

  my_string_destroy(&left_string_copy);
  my_string_destroy(&right_string_copy);
  
  return 0;
}

Status my_string_extraction(MY_STRING hMy_string, FILE* fp)
{
  My_string *pMy_string = (My_string *)hMy_string;
  pMy_string->size = 0;
  
  char character;
  int valid_check = 0;
  int character_conversion = 0;
  char *pTemp;
  int i = 0;

  valid_check = fscanf(fp, " %c", &character);
  character_conversion = character;

  if (valid_check == -1)
  {
    return FAILURE;
  }
      
  while (character_conversion != 32 && character_conversion != 10)
  {
    pMy_string->data[pMy_string->size] = character;
    pMy_string->size += 1;
    
    if (pMy_string->size >= pMy_string->capacity)
    {
      
      pTemp = (char *)malloc((2 * pMy_string->capacity) * sizeof(char));

      if (pTemp == NULL)  
      {
	printf("Failed to allocate memory.");

	return FAILURE;
      }

      for (i = 0; i < pMy_string->size; i++)
      {
	pTemp[i] = pMy_string->data[i];
      }

      free(pMy_string->data);
      pMy_string->data = pTemp;

      pMy_string->capacity *= 2;
    }
    
    valid_check = fscanf(fp, "%c", &character);
    character_conversion = character;
 
    if (valid_check == -1)
    {
      my_string_insertion(pMy_string, stdout);

      return FAILURE;
    }
  }

  if ((character_conversion == 32 || character_conversion == 10) && pMy_string->size != 0)
  {
    ungetc(character, fp);

    return SUCCESS;
  } 
       
  if (valid_check <= 0)
  {

    return SUCCESS;
  }
 
    return SUCCESS; 
}

Status my_string_insertion(MY_STRING hMy_string, FILE* fp)
{
  My_string *pMy_string = (My_string *)hMy_string;
  int i = 0;

  if (pMy_string == NULL)
  {
    return FAILURE;
  }
   
  while (i < pMy_string->size)
  {
    fprintf(stdout, "%c", pMy_string->data[i]);
    i++;
  }

  return SUCCESS;
}

Status my_string_push_back(MY_STRING hMy_string, char item)
{
  My_string *pMy_string = (My_string *)hMy_string;
  char *pTemp;
  int i;

  if (pMy_string->size >= pMy_string->capacity)
  {
    pTemp = (char *)malloc((pMy_string->capacity * 2) * sizeof(char));
    
    if (pTemp == NULL)
    {
      printf("Failed to allocate memory.");

      return FAILURE;
    }

    for (i = 0; i < pMy_string->size; i++)
    {
      pTemp[i] = pMy_string->data[i];
    }

    free(pMy_string->data);
    pMy_string->data = pTemp;
    pMy_string->capacity *= 2;
  }

  pMy_string->data[pMy_string->size] = item;
  pMy_string->size += 1;

  return SUCCESS;
}

Status my_string_pop_back(MY_STRING hMy_string)
{
  My_string *pMy_string = (My_string *)hMy_string;

  if (my_string_empty(hMy_string))
  {
    return FAILURE;
  }

  pMy_string->size -= 1;

  return SUCCESS;
}

char* my_string_at(MY_STRING hMy_string, int index)
{
  My_string *pMy_string = (My_string *)hMy_string;

  if (index < 0 || index >= pMy_string->size)
  {
    return NULL;
  }

  return pMy_string->data + index;
}

char* my_string_c_str(MY_STRING hMy_string)
{
  
  My_string *pMy_string = (My_string *)hMy_string;
  char *pTemp;
  int i;
 
  if (pMy_string->size >= pMy_string->capacity) // Could be bug
  {
    pTemp = (char *)malloc((pMy_string->capacity + 1) * sizeof(char));

    if (pTemp == NULL)
    {
      printf("Failed to allocate memory.");

      return NULL;
    }

    for (i = 0; i < pMy_string->size; i++)
    {
      pTemp[i] = pMy_string->data[i];
    }
  
    free(pMy_string->data);
    pMy_string->data = pTemp;
    pMy_string->capacity += 1;
  }

  pMy_string->data[pMy_string->size] = '\0';
  
  return pMy_string->data;
 }

Status my_string_concat(MY_STRING hResult, MY_STRING hAppend)
{
  My_string *pResult = (My_string *)hResult;
  My_string *pAppend = (My_string *)hAppend;
  char *pTemp;
  int i;
  int j;
  int totalCapacity = pResult->capacity + pAppend->capacity;

  if (totalCapacity >= pResult->capacity)
  {
    pTemp = (char *)malloc((totalCapacity * 2) * sizeof(char));

    if (pTemp == NULL)
    {
      printf("Failed to allocate memory.\n");
      free(pTemp);
      return FAILURE;
    }

    pResult->capacity = totalCapacity * 2;

    for (i = 0; i < pResult->size; i++) // Could be bug, <=
    {
      pTemp[i] = pResult->data[i];
    }

    for (j = 0; j < pAppend->size; j++, i++) // Could be bug, <= 
    {
      pTemp[i] = pAppend->data[j];
    }
  }

  free(pResult->data);
  pResult->data = pTemp;
  pResult->size = i;

  return SUCCESS;
}

Boolean my_string_empty(MY_STRING hMy_string)
{
  My_string *pMy_string = (My_string *)hMy_string;

  if (pMy_string->size <= 0)
  {
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}

Status my_string_assignment(Item* pLeft, Item Right)
{
  My_string *left = (My_string *)*pLeft;
  My_string *pRight = (My_string *)Right;

  if (left == NULL)
  {
    left = my_string_init_default();
  }

  if (left->capacity < pRight->size)
  {
    if (left->data != NULL)
    {
      free(left->data);
    }
    
    left->data = (char *)malloc(pRight->size * sizeof(char));

    if (left->data == NULL)
    {
      printf("Failed to allocate memory.\n");

      free(left->data);
      
      return FAILURE; //changes
    }
    else
    {
      left->capacity = pRight->size;
    }
  }
      
  for (int i = 0; i < pRight->size; i++)
  {
    left->data[i] = pRight->data[i];

    left->size += 1;
  }

  *pLeft = (My_string *)left;

  return SUCCESS; //changes
}
