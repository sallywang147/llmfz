#include <fuzzer/FuzzedDataProvider.h>
#include <capstone/capstone.h>

struct cs_struct {
  // User defined structure
};

extern int ALPHA_global_init(struct cs_struct * ud);

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct cs_struct ud;
  size_t consumed = stream.ConsumeData(&ud, sizeof(ud));

  // Call the function to fuzz
  ALPHA_global_init(&ud);

  return 0;
}