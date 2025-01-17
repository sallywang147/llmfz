#include <fuzzer/FuzzedDataProvider.h>
#include <expat.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0)
    return 0;

  FuzzedDataProvider stream(data, size);

  XML_Parser parser = XML_ParserCreate(nullptr);
  if (!parser)
    return 0;

  // Split the data into two parts to use as parameters for the target function
  size_t half_size = size / 2;
  std::string param1 = stream.ConsumeBytesAsString(half_size);
  std::string param2 = stream.ConsumeRemainingBytesAsString();

  // Create a dummy parameter for the last argument
  char *dummy_params[] = {nullptr};

  // Call the target function
  externalEntityInitProcessor2(parser, const_cast<char*>(param1.c_str()), const_cast<char*>(param2.c_str()), dummy_params);

  XML_ParserFree(parser);

  return 0;
}