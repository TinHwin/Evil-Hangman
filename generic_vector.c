#include <stdio.h>
#include <stdlib.h>
#include "generic_vector.h"
//#include "generic.h"

//known type
struct generic_vector
{
  int size;
  int capacity;
  ITEM* data;
  Status(*item_assignment)(ITEM* phLeft, ITEM hRight);
  void(*item_destroy)(ITEM* phItem);
};

typedef struct generic_vector Generic_vector;

GENERIC_VECTOR generic_vector_init_default(Status(*item_assignment)(ITEM* phLeft, ITEM hRight), void(*item_destroy)(ITEM* phItem))
{
  int i;
  Generic_vector* pVector;

  pVector = (Generic_vector*)malloc(sizeof(Generic_vector));

  if (pVector != NULL)
  {
    pVector->size = 0;
    pVector->capacity = 1;
    pVector->item_assignment = item_assignment;
    pVector->item_destroy = item_destroy;
    pVector->data = (ITEM*)malloc(sizeof(ITEM) * pVector->capacity);

    if (pVector->data == NULL)
    {
      free(pVector);

      return NULL;
    }

    for (i = 0; i < pVector->capacity; i++)
    {
      pVector->data[i] = NULL;
    }
  }

  return pVector;
}

Status generic_vector_push_back(GENERIC_VECTOR hVector, ITEM hItem)
{
  Generic_vector* pVector = (Generic_vector*)hVector;
  ITEM* temp;
  int i;

  //if there is not enough room then make room

  if (pVector->size >= pVector->capacity)
  {
    temp = (ITEM*)malloc(sizeof(ITEM) * pVector->capacity * 2);
    if (temp == NULL)
    {
      return FAILURE;
    }

    for (i = 0; i < pVector->size; i++)
    {
      temp[i] = pVector->data[i];
    }

    for (; i < pVector->capacity * 2; i++)
    {
      temp[i] = NULL;
    }

    free(pVector->data);

    pVector->data = temp;
    pVector->capacity *= 2;
  }

  //Old way...that will not work anymore
  //pVector->data[pVector->size] = hItem;

  if (pVector->item_assignment(pVector->data + pVector->size, hItem) == FAILURE)
  {
    return FAILURE;
  }

  pVector->size++;

  return SUCCESS;
}

Status generic_vector_pop_back(GENERIC_VECTOR hVector)
{
  Generic_vector* pVector = (Generic_vector*)hVector;

  if (generic_vector_is_empty(hVector))
  {
    return FAILURE;
  }

  pVector->item_destroy(pVector->data + pVector->size - 1);
  pVector->size--;

  return SUCCESS;

  //START HERE by testing this function
}

ITEM* generic_vector_at(GENERIC_VECTOR hVector, int index)
{
  Generic_vector* pVector = (Generic_vector*)hVector;

  if (index < 0 || index >= pVector->size)
  {
    return NULL;
  }

  return pVector->data + index;
}

int generic_vector_get_size(GENERIC_VECTOR hVector)
{
  Generic_vector* pVector = (Generic_vector*)hVector;

  return pVector->size;
}

int generic_vector_get_capacity(GENERIC_VECTOR hVector)
{
  Generic_vector* pVector = (Generic_vector*)hVector;

  return pVector->capacity;
}


Boolean generic_vector_is_empty(GENERIC_VECTOR hVector)
{
  Generic_vector* pVector = (Generic_vector*)hVector;

  return (Boolean)pVector->size <= 0;
}

void generic_vector_destroy(GENERIC_VECTOR* phVector)
{
  Generic_vector* pVector = (Generic_vector*)*phVector;
  int i;

  for (i = 0; i < pVector->size; i++)
  {
    pVector->item_destroy(pVector->data + i);
  }

  free(pVector->data);
  free(pVector);
  *phVector = NULL;
}


