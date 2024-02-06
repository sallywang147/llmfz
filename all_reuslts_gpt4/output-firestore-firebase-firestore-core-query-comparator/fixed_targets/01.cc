#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "firebase/firestore.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize Firebase Firestore
  firebase::AppOptions app_options;
  firebase::App* app = firebase::App::Create(app_options);
  firebase::firestore::Firestore* firestore = firebase::firestore::Firestore::GetInstance(app);

  // Create a DocumentComparator
  firebase::firestore::model::DocumentComparator document_comparator;

  // Create a Query
  firebase::firestore::core::Query query = firestore->Collection("test");

  // Call the Comparator function
  query.Comparator(&document_comparator, &query);

  // Clean up
  delete firestore;
  delete app;

  return 0;
}