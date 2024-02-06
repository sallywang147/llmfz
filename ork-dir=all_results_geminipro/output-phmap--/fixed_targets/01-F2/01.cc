#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "parallel_hashmap/phmap_dump.h"
#include <fuzzer/FuzzedDataProvider.h>

using namespace std;
using phmap::flat_hash_map;

extern "C" {
void phmap::priv::Deallocate<8ul, std::__1::allocator<std::__1::pair<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > const, std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > > > >(phmap::priv::HashtablezInfoHandle * alloc, char * p, size_t n) {
  free(p);
}
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);
  const int num_items = fuzzed_data.ConsumeIntegral<int16_t>();
  phmap::flat_hash_map<std::string, std::string> table;
  for (int i = 0; i < num_items; ++i) {
    table.insert(typename phmap::flat_hash_map<std::string, std::string>::value_type(fuzzed_data.ConsumeRandomLengthString(), fuzzed_data.ConsumeRandomLengthString()));
  }
  phmap::BinaryOutputArchive ar_out("/tmp/dump.data");
  table.phmap_dump(ar_out);
  phmap::flat_hash_map<std::string, std::string> table_in;
  phmap::BinaryInputArchive ar_in("/tmp/dump.data");
  table_in.phmap_load(ar_in);
  return 0;
}