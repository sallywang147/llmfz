#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstring>

extern "C" int omain(int argc, char ** argv);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // We will simulate command line arguments, so we need at least 1 argument for the program name
  if (stream.remaining_bytes() < 1) {
    return 0;
  }

  // We will limit the number of arguments to avoid excessive memory allocation
  const int argc = stream.ConsumeIntegralInRange<int>(1, 10);
  char** argv = new char*[argc];

  // The first argument is the program name
  std::string prog_name = stream.ConsumeRandomLengthString();
  argv[0] = strdup(prog_name.c_str());

  // Generate the rest of the arguments
  for (int i = 1; i < argc; ++i) {
    std::string arg = stream.ConsumeRandomLengthString();
    argv[i] = strdup(arg.c_str());
  }

  omain(argc, argv);

  // Free the allocated memory
  for (int i = 0; i < argc; ++i) {
    free(argv[i]);
  }
  delete[] argv;

  return 0;
}