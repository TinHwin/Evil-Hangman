#include <stdio.h>
#include <stdlib.h>

#include "my_string.h"
#include "generic_vector.h"
#include "associative_array.h"

struct avl
{
  NODE *root;
};

typedef struct avl avl;

int get_height(NODE *pNode)
{
  if (pNode == NULL)
  {
    return 0;
  }
  
  return pNode->height; 
}

int get_balance(NODE *pNode)
{
  if (pNode == NULL)
  {
    return 0;
  }
  
  return get_height(pNode->left) - get_height(pNode->right);
}

int max(int left, int right)
{
  if (left > right)
  {
    return left;
  }

  return right;
}

NODE *left_rotation(NODE *pNode_x)
{
  NODE *pNode_y = pNode_x->right;
  NODE *pNode_y_child = pNode_y->left;

  pNode_y->left = pNode_x;
  pNode_x->right = pNode_y_child;
  
  pNode_x->height = max(get_height(pNode_x->left), get_height(pNode_x->right)) + 1;
  pNode_y->height = max(get_height(pNode_y->left), get_height(pNode_y->right)) + 1;

  return pNode_y;
}

NODE *right_rotation(NODE *pNode_y)
{
  NODE *pNode_x = pNode_y->left;
  NODE *pNode_x_child = pNode_x->right;

  pNode_x->right = pNode_y;
  pNode_y->left = pNode_x_child;

  pNode_y->height = max(get_height(pNode_y->left), get_height(pNode_y->right)) + 1;
  pNode_x->height = max(get_height(pNode_x->left), get_height(pNode_x->right)) + 1;

  return pNode_x;
}

void inorder(NODE *pNode, void function_holder(NODE *))
{
    if (!pNode)
    {
      return;
    }
    
    inorder(pNode->left, function_holder);

    function_holder(pNode);

    inorder(pNode->right, function_holder);
}

void postorder(NODE *pNode, void function_holder(NODE *))
{
    if (!pNode)
    {	
      return;
    }
    
    postorder(pNode->left, function_holder);

    postorder(pNode->right, function_holder);

    function_holder(pNode);
}

NODE *new_node(avl *pAvl, MY_STRING key, MY_STRING word)
{
  NODE *pNew_node = (NODE *)malloc(sizeof(NODE));

  if (pNew_node == NULL)
  {
    return NULL;
  }
  
  pNew_node->left = NULL;
  pNew_node->right = NULL;
  pNew_node->height = 1;
  pNew_node->word_family = my_string_init_default();
  pNew_node->word_list = generic_vector_init_default(my_string_assignment, my_string_destroy);

  for (int i = 0; i < my_string_get_size(key); i++)
  {
    my_string_push_back(pNew_node->word_family, (*my_string_at(key, i)));
  }

  generic_vector_push_back(pNew_node->word_list, word);

  return pNew_node;
}

void free_node(NODE *pNode)
{
  my_string_destroy(&pNode->word_family);

  generic_vector_destroy(&pNode->word_list);
  
  free(pNode);
}

AVL avl_init_default(void)
{
  avl *pAvl = (avl *)malloc(sizeof(avl));

  if (pAvl == NULL)
  {
    return NULL;
  }

  pAvl->root = NULL;

  return pAvl;
}

NODE *avl_insert_support(avl *pAvl, NODE *pNode, MY_STRING key, MY_STRING word)
{
  if (pNode == NULL)
  {
    NODE *pNew_node = new_node(pAvl, key, word);

    if (pNew_node == NULL)
    {
      return NULL;
    }
    
    return pNew_node;
  }
  
  int comparison = my_string_compare(key, pNode->word_family);
  
  if (comparison == -1)
  {
    pNode->left = avl_insert_support(pAvl, pNode->left, key, word);
  }
  else if (comparison == 1)
  {
    pNode->right = avl_insert_support(pAvl, pNode->right, key, word);
  }
  else 
  {
    generic_vector_push_back(pNode->word_list, word);

    return pNode;
  }

  pNode->height = 1 + max(get_height(pNode->left), get_height(pNode->right));
  
  int balance;
  
  balance = get_balance(pNode);

  
  if ((balance > 1) && (my_string_compare(key, pNode->left->word_family) == -1))
  {
    return right_rotation(pNode);
  }

  if ((balance < -1) && (my_string_compare(key, pNode->right->word_family) == 1))
  {
    return left_rotation(pNode);
  }

  if ((balance > 1) && (my_string_compare(key, pNode->left->word_family) == 1))
  {
    pNode->left = left_rotation(pNode->left);

    return right_rotation(pNode);
  }

  if ((balance < -1) && (my_string_compare(key, pNode->right->word_family) == -1))
  {
    pNode->right = right_rotation(pNode->right);

    return left_rotation(pNode);
  }  
  
  return pNode;
}

void avl_insert_main(AVL hAvl, MY_STRING key, MY_STRING word)
{
  avl *pAvl = (avl *)hAvl;

  pAvl->root = avl_insert_support(pAvl, pAvl->root, key, word);
}

NODE *avl_find(AVL hAvl, int size)
{
    avl *pAvl = (avl*)hAvl;
    NODE *pNode = pAvl->root;
    
    while (pNode)
    {
      if (size < generic_vector_get_size(pNode->word_list))
      {
        pNode = pNode->left;

	size = generic_vector_get_size(pNode->word_list);
      }
      else if (size > generic_vector_get_size(pNode->word_list))
      {
	pNode = pNode->right;

	size = generic_vector_get_size(pNode->word_list);
      }
      else
      {
	size = generic_vector_get_size(pNode->word_list);
	
	return pNode;
      }
    }

    return NULL;
}

NODE *avl_root(AVL hAvl)
{
  avl *pAvl = (avl*)hAvl;

  return pAvl->root;
}

void avl_inorder(AVL hAvl, void function_holder(NODE *))
{
    avl *pAvl = (avl*)hAvl;

    NODE *pNode = pAvl->root;

    inorder(pNode, function_holder);
}

void avl_postorder(AVL hAvl, void function_holder(NODE *))
{
    avl *pAvl = (avl*)hAvl;
    
    NODE *pNode = pAvl->root;

    postorder(pNode, function_holder);
}

void print_node(NODE *pNode)
{
  my_string_insertion(pNode->word_family, stdout);

  printf(" %d", generic_vector_get_size(pNode->word_list));

  printf("\n"); 
}

void print_node_two(NODE *pNode)
{
  for (int i = 0; i < generic_vector_get_size(pNode->word_list); i++)
  {
    my_string_insertion(*generic_vector_at(pNode->word_list, i), stdout);

    printf(": ");

    my_string_insertion(pNode->word_family, stdout);

    printf("\n");
  }
}

void avl_print(AVL hAvl, int print)
{
  if (print == 1)
  {
    avl_inorder(hAvl, print_node_two);
  }

  if (print == 1)
  {
    avl_inorder(hAvl, print_node);
  }
}

void avl_destroy(AVL *phAvl)
{
  avl *pAvl = (avl *)*phAvl;

  avl_postorder(*phAvl, free_node);

  free(pAvl);

  *phAvl = NULL;
}

void inorder_find_largest_family(NODE *pNode, int *largest)
{
  if (!pNode)
  {
    return;
  }

  inorder_find_largest_family(pNode->left, largest);

  if (*largest < generic_vector_get_size(pNode->word_list))
  {
    *largest = generic_vector_get_size(pNode->word_list);
  }
  
  inorder_find_largest_family(pNode->right, largest);
}

int avl_inorder_find_largest_family(AVL hAvl)
{
  avl *pAvl = (avl *)hAvl;

  NODE *pNode = pAvl->root;

  int largest = 0;
  
  inorder_find_largest_family(pNode, &largest);
  
  return largest;
}

void avl_find_largest_family(NODE *pNode, NODE *pNew_node, int largest)
{
  if (!pNode)
  {
    return;
  }

  avl_find_largest_family(pNode->left, pNew_node, largest);

  if (largest == generic_vector_get_size(pNode->word_list))
  {
    for (int i = 0; i < my_string_get_size(pNode->word_family); i++)
    {
      my_string_push_back(pNew_node->word_family, *my_string_at(pNode->word_family, i));
    }

    for (int i = 0; i < generic_vector_get_size(pNode->word_list); i++)
    {
      generic_vector_push_back(pNew_node->word_list, *generic_vector_at(pNode->word_list, i));
    }
  }
  
  avl_find_largest_family(pNode->right, pNew_node, largest);
}

NODE *find_largest_family(AVL hAvl, int largest)
{
  avl *pAvl = (avl *)hAvl;

  NODE *pNode = pAvl->root;
  NODE *pNew_node = (NODE *)malloc(sizeof(NODE));

  pNew_node->left = NULL;
  pNew_node->right = NULL;
  pNew_node->height = 1;
  pNew_node->word_family = my_string_init_default();
  pNew_node->word_list = generic_vector_init_default(my_string_assignment, my_string_destroy);
  
  avl_find_largest_family(pNode, pNew_node, largest);
  
  return pNew_node;
}
