#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include <fuzzer/FuzzedDataProvider.h>

extern "C" char *Manage(char *p_object);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t object_size = stream.ConsumeIntegralInRange<size_t>(0, 1000);
  char *p_object = new char[object_size + 1];
  stream.ConsumeBytes(p_object, object_size);
  p_object[object_size] = '\0';
  char *result = Manage(p_object);
  delete[] p_object;
  delete[] result;
  return 0;
}