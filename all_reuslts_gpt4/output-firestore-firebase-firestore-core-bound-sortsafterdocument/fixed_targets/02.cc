#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "firebase/firestore.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  firebase::firestore::core::Bound bound;
  std::vector<firebase::firestore::model::FieldPath> field_paths;
  union.anon anon;

  // We don't know the exact structure of union.anon, but we can fill it with random bytes.
  size_t anon_size = sizeof(anon);
  if (stream.remaining_bytes() < anon_size) {
    return 0;  // Not enough data to proceed.
  }
  std::memcpy(&anon, stream.ConsumeBytes<uint8_t>(anon_size).data(), anon_size);

  // We don't know the exact usage of the vector, but we can fill it with random FieldPaths.
  while (stream.remaining_bytes() > 0) {
    std::string path = stream.ConsumeRandomLengthString();
    field_paths.push_back(firebase::firestore::model::FieldPath::FromServerFormat(path));
  }

  bound.SortsAfterDocument(&bound, &field_paths, &anon);

  return 0;
}