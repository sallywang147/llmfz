#include <fuzzer/FuzzedDataProvider.h>
#include <pg_query.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string str = stream.ConsumeRandomLengthString();
  char *ptr = const_cast<char*>(str.c_str());

  int int_arg = stream.ConsumeIntegral<int>();

  PgQueryProtobufParseResult result;
  pg_query_parse_protobuf_opts(&result, ptr, int_arg);

  return 0;
}