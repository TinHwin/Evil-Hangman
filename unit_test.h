#ifndef UNIT_TEST_H
#define UNIT_TEST_H
#include "my_string.h"

Status test_init_default_returns_nonNULL(char* buffer, int length);
Status test_get_size_on_init_default_returns_0(char* buffer, int length);

Status test_thuynh_init_c_string_size(char* buffer, int length);
Status test_thuynh_init_c_string_capacity(char* buffer, int length);

Status test_thuynh_compare_smaller(char* buffer, int length);
Status test_thuynh_compare_larger(char* buffer, int length);
Status test_thuynh_compare_equal(char* buffer, int length);

Status test_thuynh_extraction_resize_not_needed(char* buffer, int length);
Status test_thuynh_extraction_resize_needed(char* buffer, int length);

Status test_thuynh_insertion_with_NULL(char* buffer, int length);
Status test_thuynh_insertion_without_NULL(char* buffer, int length);

Status test_thuynh_push_back_empty(char* buffer, int length);
Status test_thuynh_push_back_resize_needed(char* buffer, int length);
Status test_thuynh_push_back_size(char* buffer, int length);

Status test_thuynh_pop_back_empty(char* buffer, int length);
Status test_thuynh_pop_back(char* buffer, int length);

Status test_thuynh_at_index_less_zero(char* buffer, int length);
Status test_thuynh_at_index_more_than_size(char* buffer, int length);
Status test_thuynh_at_zero(char* buffer, int length);

Status test_thuynh_c_str_empty_string(char* buffer, int length);
Status test_thuynh_c_str_string_size(char* buffer, int length);

Status test_thuynh_concat_empty(char* buffer, int length);
Status test_thuynh_concat_resize_needed(char* buffer, int length);

Status test_thuynh_empty_not_empty(char* buffer, int length);
Status test_thuynh_empty(char* buffer, int length);

#endif
