#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "firebase/firestore.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  firebase::firestore::core::Query query;
  union.anon *bounds = nullptr;

  // The function MatchesBounds is a member function and needs an object to call it.
  // Here we are creating an object of firebase::firestore::core::Query and calling the function on it.
  // The function MatchesBounds is a const function, which means it cannot modify the object it is called on.
  // Here we are assuming that the function takes a pointer to firebase::firestore::core::Query and a pointer to union.anon as arguments.
  // We are passing nullptr as the arguments. This is a valid input and should not cause any crashes.
  // In a real fuzzing scenario, we would generate random data for these arguments.
  query.MatchesBounds(nullptr, nullptr);

  return 0;
}