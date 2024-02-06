#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
#include <string.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t object_size = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  char *object = new char[object_size];
  stream.ConsumeBytes(object, object_size);
  char *result = Manage(object);
  delete[] object;
  delete[] result;
  return 0;
}

// Definition of the Manage function
extern "C" char *Manage(char *object) {
  // Do something with the object
  return object;
}