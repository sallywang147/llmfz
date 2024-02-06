#include <fuzzer/FuzzedDataProvider.h>
#include <pg_query.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size == 0)
    return 0;

  FuzzedDataProvider stream(data, size);

  // Extracting parameters for the function call
  int int_arg = stream.ConsumeIntegral<int>();
  std::string str_arg = stream.ConsumeRemainingBytesAsString();

  // Initialize the result struct
  PgQueryProtobufParseResult result;

  // Call the target function
  pg_query_parse_protobuf_opts(&result, const_cast<char*>(str_arg.c_str()), int_arg);

  return 0;
}