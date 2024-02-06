#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "flatbuffers/flatbuffers.h"
#include "flatbuffers/idl.h"
#include "flatbuffers/util.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  flatbuffers::IDLOptions idl_opts;
  flatbuffers::Parser parser(idl_opts);
  flatbuffers::JsonPrinter printer;
  FuzzedDataProvider provider(data, size);

  // Extract integral values
  int int_arg = provider.ConsumeIntegral<int>();
  int int_arg_in_range = provider.ConsumeIntegralInRange(-100, 100);

  // Extract a string. You MUST use .c_str() to use result as pointer
  std::string str = provider.ConsumeBytesAsString(provider.ConsumeIntegralInRange(0, size));
  char *ptr = str.c_str();

  // Extract to user defined object
  flatbuffers::Type type_obj;
  size_t consumed = provider.ConsumeData(&type_obj, sizeof(type_obj));

  // Call the target function
  printer.PrintVector<flatbuffers::Offset64<void>, unsigned int>(&printer, ptr, &type_obj, int_arg, ptr);

  return 0;
}