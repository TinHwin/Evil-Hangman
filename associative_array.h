#ifndef ASSOCIATIVE_ARRAY
#define ASSOCIATIVE_ARRAY

#include <stdio.h>
#include <stdlib.h>

#include "my_string.h"
#include "generic_vector.h"

typedef void* AVL;

typedef struct node NODE;

struct node
{
  NODE *left;
  NODE *right;

  int height;

  MY_STRING word_family;
  
  GENERIC_VECTOR word_list;
};

AVL avl_init_default(void);

void avl_insert_main(AVL hAvl, MY_STRING key, MY_STRING word);

NODE *avl_root(AVL hAvl);

NODE *avl_find(AVL hAvl, int size);

NODE *avl_root(AVL hAvl);

void avl_inorder(AVL hAvl, void function_holder(NODE *));

void avl_postorder(AVL hAvl, void function_holder(NODE *));

void avl_print(AVL hAvl, int print);

void avl_print_two(AVL hAvl, int print);

void avl_destroy(AVL* phAvl);

int avl_inorder_find_largest_family(AVL hAvl);

NODE *find_largest_family(AVL hAvl, int largest);

#endif
