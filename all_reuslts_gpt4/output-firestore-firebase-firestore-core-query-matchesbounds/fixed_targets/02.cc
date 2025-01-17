#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "firebase/firestore.h"

struct union_anon {
  int a;
  char b;
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  firebase::firestore::core::Query query;

  union_anon ua;
  ua.a = stream.ConsumeIntegral<int>();
  ua.b = stream.ConsumeIntegral<char>();

  query.MatchesBounds(&query, &ua);

  return 0;
}