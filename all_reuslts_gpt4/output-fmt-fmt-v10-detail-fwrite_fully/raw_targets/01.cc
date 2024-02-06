#include <fuzzer/FuzzedDataProvider.h>
#include <fmt/format.h>
#include <cstdio>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Extract a string. You MUST use .c_str() to use result as pointer
  std::string str = stream.ConsumeRandomLengthString();
  char* ptr = const_cast<char*>(str.c_str());
  size_t count = str.size();

  // Use a temporary file for the fuzzing
  FILE* tmpfile = std::tmpfile();
  if (!tmpfile) {
    return 0;
  }

  // Call the function to fuzz
  fmt::v10::detail::fwrite_fully(ptr, count, tmpfile);

  // Close the temporary file
  std::fclose(tmpfile);

  return 0;
}