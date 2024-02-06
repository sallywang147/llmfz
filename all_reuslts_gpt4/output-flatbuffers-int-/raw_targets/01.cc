#include <fuzzer/FuzzedDataProvider.h>
#include <flatbuffers/flatbuffers.h>
#include <flatbuffers/idl.h>
#include <flatbuffers/util.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize JsonPrinter
  flatbuffers::IDLOptions options;
  flatbuffers::Parser parser(options);
  flatbuffers::JsonPrinter printer(parser, true);

  // Consume data for parameters
  std::string buffer1 = stream.ConsumeRandomLengthString();
  char* buffer1_ptr = const_cast<char*>(buffer1.c_str());

  std::string buffer2 = stream.ConsumeRandomLengthString();
  char* buffer2_ptr = const_cast<char*>(buffer2.c_str());

  int int_arg = stream.ConsumeIntegral<int>();

  flatbuffers::Type type = static_cast<flatbuffers::Type>(stream.ConsumeIntegralInRange<int>(0, 15));

  // Call the target function
  printer.PrintVector<flatbuffers::Offset64<void>, unsigned int>(&printer, buffer1_ptr, &type, int_arg, buffer2_ptr);

  return 0;
}