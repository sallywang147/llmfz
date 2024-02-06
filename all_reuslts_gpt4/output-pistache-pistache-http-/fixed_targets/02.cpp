#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "pistache/http.h"
#include "pistache/stream.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  Pistache::Http::Uri::Query query;
  Pistache::ArrayStreamBuf buffer;

  // We need to create a valid Query object and ArrayStreamBuf object for fuzzing
  // Let's use the FuzzedDataProvider to generate these objects
  size_t querySize = stream.ConsumeIntegralInRange<size_t>(0, size);
  std::string queryString = stream.ConsumeBytesAsString(querySize);
  query.add(queryString, "");

  size_t bufferSize = stream.ConsumeIntegralInRange<size_t>(0, size);
  std::string bufferString = stream.ConsumeBytesAsString(bufferSize);
  buffer.write(bufferString.c_str(), bufferSize);

  // Call the function with the generated objects
  Pistache::Http::serialize(&query, &buffer);

  return 0;
}