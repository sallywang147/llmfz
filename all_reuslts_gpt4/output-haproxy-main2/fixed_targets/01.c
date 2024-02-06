#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>

extern "C" int main2(int argc, char ** argv);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // We will simulate command line arguments. We will have at least one argument (the program name).
  // We limit the number of arguments to 10 and the length of any argument to 50 characters.
  const int argc = stream.ConsumeIntegralInRange<int>(1, 10);
  char* argv[10];

  // The first argument is the program name. We set it to a static string.
  argv[0] = strdup("program");

  for (int i = 1; i < argc; ++i) {
    std::string arg = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange<size_t>(0, 50));
    argv[i] = strdup(arg.c_str());
  }

  // Call the target function.
  main2(argc, argv);

  // Free the memory we allocated.
  for (int i = 0; i < argc; ++i) {
    free(argv[i]);
  }

  return 0;
}