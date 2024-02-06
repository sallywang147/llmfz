#include <fuzzer/FuzzedDataProvider.h>
#include <pg_query.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string str = stream.ConsumeRemainingBytesAsString();
  char *query = const_cast<char *>(str.c_str());

  PgQueryProtobufParseResult result;
  pg_query_parse_protobuf(&result, query);

  pg_query_protobuf_parse_free(result);

  return 0;
}