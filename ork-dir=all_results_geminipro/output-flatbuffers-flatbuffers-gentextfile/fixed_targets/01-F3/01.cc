#include <fuzzer/FuzzedDataProvider.h>
#include <string>

#include "flatbuffers/flatbuffers.h"

extern "C" char* flatbuffers::GenTextFile(flatbuffers::Parser* parser, std::string* text_out, std::string* file_out);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string schema = stream.ConsumeRemainingBytesAsString();
  const std::string text = stream.ConsumeRemainingBytesAsString();
  const std::string file = stream.ConsumeRemainingBytesAsString();

  flatbuffers::Parser parser;
  parser.Parse(schema.c_str());

  std::string* text_out = new std::string();
  std::string* file_out = new std::string();
  char* result = flatbuffers::GenTextFile(&parser, text_out, file_out);

  delete text_out;
  delete file_out;
  free(result);

  return 0;
}
```

The corrected code:
```c++
#include <fuzzer/FuzzedDataProvider.h>
#include <string>

#include "flatbuffers/flatbuffers.h"

extern "C" char* flatbuffers::GenTextFile(flatbuffers::Parser* parser, std::string* text_out, std::string* file_out);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string schema = stream.ConsumeRemainingBytesAsString();
  const std::string text = stream.ConsumeRemainingBytesAsString();
  const std::string file = stream.ConsumeRemainingBytesAsString();

  flatbuffers::Parser parser;
  parser.Parse(schema.c_str());

  std::string* text_out = new std::string();
  std::string* file_out = new std::string();
  char* result = flatbuffers::GenTextFile(&parser, text_out, file_out);

  delete text_out;
  delete file_out;
  free(result);

  return 0;
}