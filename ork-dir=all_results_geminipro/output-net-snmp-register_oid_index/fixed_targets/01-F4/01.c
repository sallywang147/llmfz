#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

extern "C" {
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/sysinfo.h>
}

extern "C" {
struct variable_list {
  size_t* name;
  size_t name_len;
  size_t* value;
  size_t value_len;
};

struct variable_list* register_oid_index(size_t* name, size_t name_len, size_t* value, size_t value_len);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const size_t name_len = stream.ConsumeIntegral<size_t>();
  const size_t value_len = stream.ConsumeIntegral<size_t>();

  size_t* name = new size_t[name_len];
  size_t* value = new size_t[value_len];

  stream.ConsumeBytes<size_t>(name, name_len);
  stream.ConsumeBytes<size_t>(value, value_len);

  struct variable_list* result = register_oid_index(name, name_len, value, value_len);

  delete[] name;
  delete[] value;

  return 0;
}