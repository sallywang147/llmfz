#include <janet.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // Initialize Janet
  janet_init();

  // Create a FuzzedDataProvider instance
  FuzzedDataProvider stream(data, size);

  // Create a JanetTable
  JanetTable *env = janet_core_env(NULL);

  // Create a buffer to hold the bytes
  std::string buffer = stream.ConsumeRemainingBytesAsString();
  char *bytes = const_cast<char*>(buffer.c_str());

  // Create a Janet union
  Janet janetUnion;

  // Call the function to fuzz
  janet_dobytes(env, bytes, buffer.size(), "fuzz-input", &janetUnion);

  // Deinitialize Janet
  janet_deinit();

  return 0;
}