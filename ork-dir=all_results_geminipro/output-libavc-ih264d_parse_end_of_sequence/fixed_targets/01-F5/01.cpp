#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <map>
#include <set>
#include <utility>
#include <tuple>
#include <functional>
#include <random>
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <future>
#include <optional>
#include <variant>
#include <any>
#include <memory>
#include <type_traits>
#include <climits>
#include <cfloat>
#include <cstddef>
#include <cinttypes>
#include <ctime>
#include <cmath>
#include <complex>
#include <valarray>
#include <array>
#include <list>
#include <forward_list>
#include <deque>
#include <stack>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <iterator>
#include <memory_resource>
#include <execution>
#include <span>
#include <version>

#include "ih264d_api.h"

extern "C" {
#include "ih264d_parse.h"
}

using namespace std;

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct _DecStruct dec;
  memset(&dec, 0, sizeof(dec));

  dec.p_sps = NULL;
  dec.p_pps = NULL;
  dec.p_sei = NULL;
  dec.p_nalu = NULL;
  dec.p_cur_nalu = NULL;
  dec.p_cur_nalu_end = NULL;
  dec.p_cur_nalu_next = NULL;
  dec.p_cur_nalu_prev = NULL;
  dec.p_cur_nalu_tmp = NULL;
  dec.p_cur_nalu_tmp_end = NULL;
  dec.p_cur_nalu_tmp_next = NULL;
  dec.p_cur_nalu_tmp_prev = NULL;
  dec.p_ref_nalu = NULL;
  dec.p_ref_nalu_end = NULL;
  dec.p_ref_nalu_next = NULL;
  dec.p_ref_nalu_prev = NULL;
  dec.p_ref_nalu_tmp = NULL;
  dec.p_ref_nalu_tmp_end = NULL;
  dec.p_ref_nalu_tmp_next = NULL;
  dec.p_ref_nalu_tmp_prev = NULL;
  dec.p_cur_pic = NULL;
  dec.p_cur_pic_end = NULL;
  dec.p_cur_pic_next = NULL;
  dec.p_cur_pic_prev = NULL;
  dec.p_ref_pic = NULL;
  dec.p_ref_pic_end = NULL;
  dec.p_ref_pic_next = NULL;
  dec.p_ref_pic_prev = NULL;
  dec.p_cur_mb = NULL;
  dec.p_cur_mb_end = NULL;
  dec.p_cur_mb_next = NULL;
  dec.p_cur_mb_prev = NULL;
  dec.p_ref_mb = NULL;
  dec.p_ref_mb_end = NULL;
  dec.p_ref_mb_next = NULL;
  dec.p_ref_mb_prev = NULL;
  dec.p_cur_slice = NULL;
  dec.p_cur_slice_end = NULL;
  dec.p_cur_slice_next = NULL;
  dec.p_cur_slice_prev = NULL;
  dec.p_ref_slice = NULL;
  dec.p_ref_slice_end = NULL;
  dec.p_ref_slice_next = NULL;
  dec.p_ref_slice_prev = NULL;
  dec.p_cur_mb_slice = NULL;
  dec.p_cur_mb_slice_end = NULL;
  dec.p_cur_mb_slice_next = NULL;
  dec.p_cur_mb_slice_prev = NULL;
  dec.p_ref_mb_slice = NULL;
  dec.p_ref_mb_slice_end = NULL;
  dec.p_ref_mb_slice_next = NULL;
  dec.p_ref_mb_slice_prev = NULL;
  dec.p_cur_mb_data = NULL;
  dec.p_cur_mb_data_end = NULL;
  dec.p_cur_mb_data_next = NULL;
  dec.p_cur_mb_data_prev = NULL;
  dec.p_ref_mb_data = NULL;
  dec.p_ref_mb_data_end = NULL;
  dec.p_ref_mb_data_next = NULL;
  dec.p_ref_mb_data_prev = NULL;
  dec.p_cur_mb_tmp = NULL;
  dec.p_cur_mb_tmp_end = NULL;
  dec.p_cur_mb_tmp_next = NULL;
  dec.p_cur_mb_tmp_prev = NULL;
  dec.p_ref_mb_tmp = NULL;
  dec.p_ref_mb_tmp_end = NULL;
  dec.p_ref_mb_tmp_next = NULL;
  dec.p_ref_mb_tmp_prev = NULL;
  dec.p_cur_mb_data_tmp = NULL;
  dec.p_cur_mb_data_tmp_end = NULL;
  dec.p_cur_mb_data_tmp_next = NULL;
  dec.p_cur_mb_data_tmp_prev = NULL;
  dec.p_ref_mb_data_tmp = NULL;
  dec.p_ref_mb_data_tmp_end = NULL;
  dec.p_ref_mb_data_tmp_next = NULL;
  dec.p_ref_mb_data_tmp_prev = NULL;
  dec.p_cur_mb_tmp_data = NULL;
  dec.p_cur_mb_tmp_data_end = NULL;
  dec.p_cur_mb_tmp_data_next = NULL;
  dec.p_cur_mb_tmp_data_prev = NULL;
  dec.p_ref_mb_tmp_data = NULL;
  dec.p_ref_mb_tmp_data_end = NULL;
  dec.p_ref_mb_tmp_data_next = NULL;
  dec.p_ref_mb_tmp_data_prev = NULL;
  dec.p_cur_mb_tmp_data_tmp = NULL;
  dec.p_cur_mb_tmp_data_tmp_end = NULL;
  dec.p_cur_mb_tmp_data_tmp_next = NULL;
  dec.p_cur_mb_tmp_data_tmp_prev = NULL;
  dec.p_ref_mb_tmp_data_tmp = NULL;
  dec.p_ref_mb_tmp_data_tmp_end = NULL;
  dec.p_ref_mb_tmp_data_tmp_next = NULL;
  dec.p_ref_mb_tmp_data_tmp_prev = NULL;
  dec.p_cur_mb_tmp_tmp = NULL;
  dec.p_cur_mb_tmp_tmp_end = NULL;
  dec.p_cur_mb_tmp_tmp_next = NULL;
  dec.p_cur_mb_tmp_tmp_prev = NULL;
  dec.p_ref_mb_tmp_tmp = NULL;
  dec.p_ref_mb_tmp_tmp_end = NULL;
  dec.p_ref_mb_tmp_tmp_next = NULL;
  dec.p_ref_mb_tmp_tmp_prev = NULL;
  dec.p_cur_mb_tmp_tmp_data = NULL;
  dec.p_cur_mb_tmp_tmp_data_end = NULL;
  dec.p_cur_mb_tmp_tmp_data_next = NULL;
  dec.p_cur_mb_tmp_tmp_data_prev = NULL;
  dec.p_ref_