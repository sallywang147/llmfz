#include <fuzzer/FuzzedDataProvider.h>
#include <protobuf-c/protobuf-c.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t field_descriptor_count = stream.ConsumeIntegral<size_t>();
  std::vector<ProtobufCFieldDescriptor*> field_descriptors;
  for (size_t i = 0; i < field_descriptor_count; i++) {
    field_descriptors.push_back(
        reinterpret_cast<ProtobufCFieldDescriptor*>(stream.ConsumeIntegral<uint64_t>()));
  }
  const size_t count = stream.ConsumeIntegral<size_t>();
  const size_t member_size = stream.ConsumeIntegral<size_t>();
  std::vector<char> member(member_size);
  stream.ConsumeBytes<char>(member.data(), member.size());
  ProtobufCBuffer buffer;
  protobuf_c_buffer_init(&buffer, 0, nullptr);
  for (size_t i = 0; i < field_descriptor_count; i++) {
    const size_t packed_size = protobuf_c_message_pack_to_buffer(
        field_descriptors[i], count, member.data(), &buffer);
    protobuf_c_buffer_free(&buffer);
    protobuf_c_buffer_init(&buffer, 0, nullptr);
    member.resize(packed_size);
  }
  protobuf_c_buffer_free(&buffer);
  return 0;
}