#include "fuzzer/FuzzedDataProvider.h"
#include "scanner.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Create a scanner
  void* scanner;
  hsql_lex_init(&scanner);
  
  // Create a new buffer state
  struct yy_buffer_state* new_buffer = hsql__scan_string(stream.ConsumeRemainingBytesAsString().c_str(), scanner);
  
  // Call the function
  hsql_push_buffer_state(new_buffer, (char*)scanner);
  
  // Clean up
  hsql__delete_buffer(new_buffer, scanner);
  hsql_lex_destroy(scanner);
  
  return 0;
}