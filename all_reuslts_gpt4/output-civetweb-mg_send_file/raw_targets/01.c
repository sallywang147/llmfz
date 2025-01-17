#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>

#include "mongoose.h"

// Mock function to simulate the creation of a connection.
struct mg_connection* create_mock_connection() {
  return nullptr;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Create a mock connection.
  struct mg_connection* conn = create_mock_connection();
  
  // Consume the remaining bytes as a string for the file path.
  std::string path = provider.ConsumeRemainingBytesAsString();
  
  // Call the function under test.
  mg_send_file(conn, const_cast<char*>(path.c_str()));

  return 0;
}