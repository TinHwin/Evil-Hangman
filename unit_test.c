#include <stdio.h>
#include "unit_test.h"

int main(int argc, char* argv[])
{
  Status (*tests[])(char*, int) =
    {
     test_init_default_returns_nonNULL,
     test_get_size_on_init_default_returns_0,
     test_thuynh_init_c_string_size,
     test_thuynh_init_c_string_capacity,
     test_thuynh_compare_smaller,
     test_thuynh_compare_larger,
     test_thuynh_compare_equal,
     test_thuynh_extraction_resize_not_needed,
     test_thuynh_extraction_resize_needed,
     test_thuynh_insertion_with_NULL,
     test_thuynh_insertion_without_NULL,     
     test_thuynh_push_back_empty,
     test_thuynh_push_back_resize_needed,
     test_thuynh_push_back_size,
     test_thuynh_pop_back_empty,
     test_thuynh_pop_back,    
     test_thuynh_at_index_less_zero,
     test_thuynh_at_index_more_than_size,
     test_thuynh_at_zero,
     test_thuynh_c_str_empty_string,
     test_thuynh_c_str_string_size,
     test_thuynh_concat_empty,
     test_thuynh_concat_resize_needed,
     test_thuynh_empty_not_empty,
     test_thuynh_empty,
     
    };
  int number_of_functions = sizeof(tests)/sizeof(tests[0]);
  int i;
  char buffer[500];
  int success_count = 0;
  int failure_count = 0;

  for (i = 0; i < number_of_functions; i++)
    {
      if (tests[i](buffer, 500) == FAILURE)
	{
	  printf("FAILED: Test %d failed miserable\n", i);
	  printf("\t%s\n", buffer);
	  failure_count++;
	}
      else
	{
	  printf("PASS:Test %d passed\n", i);
	  printf("\t%s\n", buffer);
	  success_count++;
	}
    }
  printf("Total number of tests: %d\n", number_of_functions);
  printf("%d/%d Pass, %d/%d Failure\n", success_count, number_of_functions, failure_count , number_of_functions);

  return 0;
}
