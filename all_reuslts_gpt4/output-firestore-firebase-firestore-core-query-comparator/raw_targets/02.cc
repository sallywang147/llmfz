#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "firebase/firestore.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  firebase::firestore::Firestore* firestore = firebase::firestore::Firestore::GetInstance();
  if (firestore == nullptr) {
    return 0;
  }

  // Create a DocumentComparator object
  firebase::firestore::model::DocumentComparator documentComparator;

  // Create a Query object
  firebase::firestore::core::Query query = firestore->Collection("test");

  // Call the Comparator function
  query.Comparator(&documentComparator, &query);

  return 0;
}