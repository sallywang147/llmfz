#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "onigmo.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string input = stream.ConsumeRemainingBytesAsString();
  const std::string pattern = stream.ConsumeRemainingBytesAsString();
  const char* start = input.c_str();
  const char* end = input.c_str() + input.length();
  const char* orig_range = input.c_str();
  const int lead = stream.ConsumeIntegral<int>();
  const int option = stream.ConsumeIntegral<int>();
  struct OnigMatchParamStruct* mps = nullptr;
  int* rmatch_pos = nullptr;

  struct OnigRegSetStruct* set = onig_regset_new();
  onig_regset_add_default_syntax(set);
  onig_regset_set_default_syntax(set, ONIG_SYNTAX_DEFAULT);
  onig_regset_set_default_options(set, ONIG_OPTION_DEFAULT);
  onig_regset_set_case_fold_flag(set, ONIG_CASE_FOLD_OFF);
  onig_regset_set_multi_line_flag(set, ONIG_MULTILINE_OFF);
  onig_regset_set_single_line_flag(set, ONIG_SINGLELINE_OFF);
  onig_regset_set_find_longest_flag(set, ONIG_FIND_LONGEST_OFF);
  onig_regset_set_find_not_longest_flag(set, ONIG_FIND_NOT_LONGEST_OFF);
  onig_regset_set_find_min_length_flag(set, ONIG_FIND_MIN_LENGTH_OFF);
  onig_regset_set_find_position_flag(set, ONIG_FIND_POSITION_OFF);
  onig_regset_set_find_start_position_flag(set, ONIG_FIND_START_POSITION_OFF);
  onig_regset_set_find_end_position_flag(set, ONIG_FIND_END_POSITION_OFF);
  onig_regset_set_find_regexp_flag(set, ONIG_FIND_REGEXP_OFF);
  onig_regset_set_find_range_flag(set, ONIG_FIND_RANGE_OFF);
  onig_regset_set_find_reverse_flag(set, ONIG_FIND_REVERSE_OFF);
  onig_regset_set_find_continue_flag(set, ONIG_FIND_CONTINUE_OFF);
  onig_regset_set_find_not_continue_flag(set, ONIG_FIND_NOT_CONTINUE_OFF);
  onig_regset_set_find_real_range_flag(set, ONIG_FIND_REAL_RANGE_OFF);
  onig_regset_set_find_string_last_flag(set, ONIG_FIND_STRING_LAST_OFF);
  onig_regset_set_find_string_segment_flag(set, ONIG_FIND_STRING_SEGMENT_OFF);
  onig_regset_set_find_empty_string_flag(set, ONIG_FIND_EMPTY_STRING_OFF);
  onig_regset_set_find_null_string_flag(set, ONIG_FIND_NULL_STRING_OFF);
  onig_regset_set_find_fixed_string_flag(set, ONIG_FIND_FIXED_STRING_OFF);
  onig_regset_set_find_precompiled_string_flag(set, ONIG_FIND_PRECOMPILED_STRING_OFF);
  onig_regset_set_find_optimized_string_flag(set, ONIG_FIND_OPTIMIZED_STRING_OFF);
  onig_regset_set_find_number_flag(set, ONIG_FIND_NUMBER_OFF);
  onig_regset_set_find_number_ref_flag(set, ONIG_FIND_NUMBER_REF_OFF);
  onig_regset_set_find_by_number_flag(set, ONIG_FIND_BY_NUMBER_OFF);
  onig_regset_set_find_by_number_ref_flag(set, ONIG_FIND_BY_NUMBER_REF_OFF);
  onig_regset_set_find_by_name_flag(set, ONIG_FIND_BY_NAME_OFF);
  onig_regset_set_find_by_name_ref_flag(set, ONIG_FIND_BY_NAME_REF_OFF);
  onig_regset_set_find_by_ascii_name_flag(set, ONIG_FIND_BY_ASCII_NAME_OFF);
  onig_regset_set_find_by_ascii_name_ref_flag(set, ONIG_FIND_BY_ASCII_NAME_REF_OFF);
  onig_regset_set_find_by_name_with_backref_flag(set, ONIG_FIND_BY_NAME_WITH_BACKREF_OFF);
  onig_regset_set_find_by_ascii_name_with_backref_flag(set, ONIG_FIND_BY_ASCII_NAME_WITH_BACKREF_OFF);
  onig_regset_set_find_by_name_with_backref_semi_fixed_flag(set, ONIG_FIND_BY_NAME_WITH_BACKREF_SEMI_FIXED_OFF);
  onig_regset_set_find_by_ascii_name_with_backref_semi_fixed_flag(set, ONIG_FIND_BY_ASCII_NAME_WITH_BACKREF_SEMI_FIXED_OFF);
  onig_regset_set_find_by_name_with_backref_fixed_flag(set, ONIG_FIND_BY_NAME_WITH_BACKREF_FIXED_OFF);
  onig_regset_set_find_by_ascii_name_with_backref_fixed_flag(set, ONIG_FIND_BY_ASCII_NAME_WITH_BACKREF_FIXED_OFF);
  onig_regset_set_find_by_number_with_backref_flag(set, ONIG_FIND_BY_NUMBER_WITH_BACKREF_OFF);
  onig_regset_set_find_by_number_with_backref_semi_fixed_flag(set, ONIG_FIND_BY_NUMBER_WITH_BACKREF_SEMI_FIXED_OFF);
  onig_regset_set_find_by_number_with_backref_fixed_flag(set, ONIG_FIND_BY_NUMBER_WITH_BACKREF_FIXED_OFF);
  onig_regset_set_find_by_number_with_backref_semi_fixed_flag(set, ONIG_FIND_BY_NUMBER_WITH_BACKREF_SEMI_FIXED_OFF);
  onig_regset_set_find_by_number_with_backref_fixed_flag(set, ONIG_FIND_BY_NUMBER_WITH_BACKREF_FIXED_OFF);
  onig_regset_set_find_by_name_and_number_flag(set, ONIG_FIND_BY_NAME_AND_NUMBER_OFF);
  onig_regset_set_find_by_name_and_number_ref_flag(set, ONIG_FIND_BY_NAME_AND_NUMBER_REF_OFF);
  onig_regset_set_find_by_ascii_name_and_number_flag(set, ONIG_FIND_BY_ASCII_NAME_AND_NUMBER_OFF);
  onig_regset_set_find_by_ascii_name_and_number_ref_flag(set, ONIG_FIND_BY_ASCII_NAME_AND_NUMBER_REF_OFF);
  onig_regset_set_find_by_name_and_number_with_backref_flag(set, ONIG_FIND_BY_NAME_AND_NUMBER_WITH_BACKREF_OFF);
  onig_regset_set_find_by_ascii_name_and_number_with_backref_flag(set, ONIG_FIND_BY_ASCII_NAME_AND_NUMBER_WITH_BACKREF_OFF);
  onig_regset_set_find_by_name_and_number_with_backref_semi_fixed_flag(set, ONIG_FIND_BY_NAME_AND_NUMBER_