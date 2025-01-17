#include <fuzzer/FuzzedDataProvider.h>
#include <fmt/core.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Consume some data to create a string
  std::string str = stream.ConsumeRandomLengthString();
  
  // Open a temporary file to write to
  FILE* f = tmpfile();
  if (!f) {
    return 0;
  }

  // Call the function under test
  fmt::v10::detail::print(f, const_cast<char*>(str.c_str()), str.size());

  // Close the file
  fclose(f);

  return 0;
}