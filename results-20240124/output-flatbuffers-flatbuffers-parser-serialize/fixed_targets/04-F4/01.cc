#include <locale.h>
#include <flatbuffers/flatbuffers.h>

extern "C" {
#include <stddef.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  setlocale(LC_ALL, "en_US.UTF-8");
  flatbuffers::Parser parser;
  parser.Parse(data, size);
  parser.Serialize(nullptr);
  return 0;
}