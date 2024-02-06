#include <fuzzer/FuzzedDataProvider.h>
#include <cstdint>
#include <cstddef>
#include <pb_encode.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the pb_ostream_s structure
  pb_ostream_s pb_stream;
  pb_stream.callback = nullptr;
  pb_stream.state = nullptr;
  pb_stream.max_size = stream.ConsumeIntegralInRange<size_t>(0, 100);
  pb_stream.bytes_written = stream.ConsumeIntegralInRange<size_t>(0, pb_stream.max_size);

  // Initialize the pb_msgdesc_s structure
  pb_msgdesc_s pb_fields;
  pb_fields.msgid = stream.ConsumeIntegral<uint32_t>();
  pb_fields.field_count = stream.ConsumeIntegralInRange<uint32_t>(0, 100);
  pb_fields.fields_array = nullptr;
  pb_fields.default_value = nullptr;

  // Initialize the source structure
  std::string src_struct = stream.ConsumeRemainingBytesAsString();

  // Initialize the flags
  int flags = stream.ConsumeIntegral<int>();

  // Call the function to be fuzzed
  pb_encode_ex(&pb_stream, &pb_fields, const_cast<char*>(src_struct.c_str()), flags);

  return 0;
}