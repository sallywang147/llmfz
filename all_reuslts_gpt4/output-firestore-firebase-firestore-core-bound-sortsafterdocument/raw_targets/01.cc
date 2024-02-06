#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "firebase/firestore.h"

struct anon {
  // Define the members of the union here. The actual members will depend on the
  // specific use case. For this example, we will assume that the union contains
  // an integer and a pointer.
  int i;
  void* p;
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize Firestore.
  firebase::AppOptions app_options;
  firebase::App* app = firebase::App::Create(app_options);
  firebase::firestore::Firestore* firestore = firebase::firestore::Firestore::GetInstance(app);

  // Create Bound object.
  firebase::firestore::core::Bound* bound = new firebase::firestore::core::Bound();

  // Create vector.
  std::vector<firebase::firestore::DocumentSnapshot>* vec = new std::vector<firebase::firestore::DocumentSnapshot>();

  // Create union.
  anon* u = new anon();

  // Use the FuzzedDataProvider to fill the union with data.
  if (stream.ConsumeBool()) {
    u->i = stream.ConsumeIntegral<int>();
  } else {
    size_t dataSize = stream.remaining_bytes() > sizeof(void*) ? sizeof(void*) : stream.remaining_bytes();
    u->p = (void*)stream.ConsumeBytes<uint8_t>(dataSize).data();
  }

  // Call the function to fuzz.
  bound->SortsAfterDocument(bound, vec, u);

  // Clean up.
  delete bound;
  delete vec;
  delete u;
  delete firestore;
  delete app;

  return 0;
}